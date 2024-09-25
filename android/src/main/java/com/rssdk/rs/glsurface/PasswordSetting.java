package com.rssdk.rs.glsurface;

import com.blankj.utilcode.util.ConvertUtils;
import com.blankj.utilcode.util.EncodeUtils;
import com.blankj.utilcode.util.Utils;

import com.google.gson.reflect.TypeToken;

import com.rs.network.rs.api.ApiDefine;
import com.rs.network.rs.api.ApiLoginInfo;
import com.rs.network.rs.base.BaseEncPassword;
import com.rs.network.rs.base.BaseRequestBean;
import com.rs.network.rs.base.BaseResponseBean;
import com.rs.network.rs.base.NoAttributeBean;
import com.rs.network.rs.bean.TransKeyResponseBean;
import com.rs.network.rs.bean.remotesetting.system.user.UserInfoRangeBean;
import com.rs.network.rs.bean.remotesetting.system.user.UserInfoResponseBean;
import com.rs.network.rs.function.TransKeyFunction;
import com.rs.network.rs.function.UserFunction;
import com.rs.network.rs.util.GsonUtil;

import com.rssdk.rs.common.log.RSLog;
import com.rssdk.rs.glsurface.encrypt.PasswordEncrypt;

import org.bouncycastle.crypto.InvalidCipherTextException;

import java.io.IOException;
import java.lang.reflect.Type;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import io.reactivex.Observable;
import io.reactivex.ObservableSource;
import io.reactivex.functions.Function;

/**
 * Copyright (c) 2021 Raysharp.cn. All rights reserved.
 * <p>
 * PasswordSetting
 *
 * @author huangdewen
 * @date 2021-11-08
 */
public class PasswordSetting {

    private static final String TAG = "PasswordSetting";

    private static final String BASE_SALT = "base_salt";
    private static final String BASE_X_PUBLIC = "base_x_public";
    private ApiLoginInfo mApiLoginInfo;
    private String mCurrentUserKey;
    private String mCurrentUserName;
    private TransKeyResponseBean.KeyLists baseSaltKey;
    private TransKeyResponseBean.KeyLists basexKey;
    private UserInfoResponseBean mUserInfoResponseBean;

    private UserInfoResponseBean.UserInfo mUserInfo;
    private UserInfoRangeBean mUserInfoRangeBean;

    public void setApiLoginInfo(ApiLoginInfo apiLoginInfo) {
        mApiLoginInfo = apiLoginInfo;
    }

    public void setCurrentUserKey(String userKey) {
        mCurrentUserKey = userKey;
        removeOtherUser(userKey);
        mUserInfo = mUserInfoResponseBean.getUserInfo().get(userKey);
        if (mUserInfo != null) {
            mCurrentUserName = mUserInfo.getUsername();
        }
    }

    public void setCurrentUserName(String userName) {
        mCurrentUserName = userName;
        removeOtherUserByUsername(userName);
    }

    public UserInfoResponseBean.UserInfo getUserInfo() {
        return mUserInfo;
    }

    public String getCurrentUserName() {
        return mCurrentUserName;
    }

    public String getCurrentUserKey() {
        return mCurrentUserKey;
    }

    public Observable<Boolean> loadUser() {
        return queryUserInfo();
    }

    private Observable<Boolean> queryUserInfo() {
        BaseRequestBean<NoAttributeBean> requestBean = new BaseRequestBean<>();
        return Observable.zip(UserFunction.getUserRange(Utils.getApp(), requestBean, mApiLoginInfo),
                UserFunction.getUser(Utils.getApp(), requestBean, mApiLoginInfo),
                (userInfoRangeBean, userInfoResponseBean) -> {
                    if (ApiDefine.Result.SUCCESS.equals(userInfoRangeBean.getResult())
                            && ApiDefine.Result.SUCCESS.equals(userInfoResponseBean.getResult())) {
                        mUserInfoRangeBean = userInfoRangeBean.getData();
                        mUserInfoResponseBean = userInfoResponseBean.getData();
                        return true;
                    }
                    return false;
                });
    }

    public Observable<BaseResponseBean<NoAttributeBean>> savePassword(String password, String originPassword) {
        return savePassword(true, password, originPassword, mCurrentUserName);
    }

    public Observable<BaseResponseBean<NoAttributeBean>> savePassword(boolean enable, String password, String originPassword, String userName) {
        mCurrentUserName = userName;
        if (mUserInfoResponseBean == null) {
            return genError();
        }
        if (mUserInfo == null) {
            return genError();
        }

        if (mApiLoginInfo.isPasswordEnc()) {
            return TransKeyFunction.getTransKey(Utils.getApp(), mApiLoginInfo)
                    .flatMap((Function<BaseResponseBean<TransKeyResponseBean>, ObservableSource<BaseResponseBean<NoAttributeBean>>>) transKeyResponseBean -> {
                        if (ApiDefine.Result.SUCCESS.equals(transKeyResponseBean.getResult())) {
                            List<TransKeyResponseBean.KeyLists> list = transKeyResponseBean.getData().getKeyLists();
                            for (TransKeyResponseBean.KeyLists key : list) {
                                if (BASE_SALT.equals(key.getType())) {
                                    baseSaltKey = key;
                                } else if (BASE_X_PUBLIC.equals(key.getType())) {
                                    basexKey = key;
                                }
                            }
                            if (basexKey == null || baseSaltKey == null) {
                                return genError();
                            }
                            return encrypt(enable, password, originPassword);
                        }
                        return genError();
                    });
        } else {
            if (enable) {
                mUserInfo.setPassword(password);
                mUserInfo.setConfirmPassword(password);
            } else {
                mUserInfo.setPasswordEmpty(true);
            }
            mUserInfo.setUserEnable(enable);
            mUserInfoResponseBean.setType(UserFunction.SaveType.SAVE_PASSWORD);
            mUserInfoResponseBean.setSecondaryAuthentication(originPassword);
            BaseRequestBean<UserInfoResponseBean> baseRequestBean = new BaseRequestBean<>();
            baseRequestBean.setData(mUserInfoResponseBean);
            return UserFunction.setUser(Utils.getApp(), baseRequestBean, mApiLoginInfo);
        }
    }

    private Observable<BaseResponseBean<NoAttributeBean>> encrypt(boolean enable, String password, String originPassword) throws IOException, InvalidCipherTextException {
        if (enable) {
            BaseEncPassword baseEncPassword = PasswordEncrypt.encryptPassword(basexKey.getKey(), password, basexKey.getSeq());
            mUserInfo.setBaseEncPassword(baseEncPassword);
        } else {
            mUserInfo.setPasswordEmpty(true);
        }

        mUserInfo.setUsername(mCurrentUserName);
        mUserInfo.setUserEnable(enable);

        byte[] bytes = EncodeUtils.base64Decode(baseSaltKey.getKey());
        byte[] pbkdf2Cipher = PasswordEncrypt.pbkdf2(originPassword, bytes, baseSaltKey.getIter(), 32);
        byte[] testEncode = EncodeUtils.base64Encode(pbkdf2Cipher);
        String baseSaltCipher = ConvertUtils.bytes2String(testEncode);

        BaseEncPassword baseSecondary = mUserInfoResponseBean.getBaseSecondaryAuthentication();
        if (baseSecondary == null) {
            baseSecondary = new BaseEncPassword();
        }
        baseSecondary.cipher = baseSaltCipher;
        baseSecondary.seq = baseSaltKey.getSeq();
        mUserInfoResponseBean.setBaseSecondaryAuthentication(baseSecondary);

        mUserInfoResponseBean.setType(UserFunction.SaveType.SAVE_PASSWORD);
        BaseRequestBean<UserInfoResponseBean> baseRequestBean = new BaseRequestBean<>();
        baseRequestBean.setData(mUserInfoResponseBean);
        return UserFunction.setUser(Utils.getApp(), baseRequestBean, mApiLoginInfo);
    }

    private void removeOtherUser(String userKey) {
        if (mUserInfoResponseBean == null) {
            return;
        }
        Map<String, UserInfoResponseBean.UserInfo> map = mUserInfoResponseBean.getUserInfo();
        for (String s : UserFunction.sUserKeyArray) {
            if (!s.equals(userKey)) {
                map.remove(s);
            }
        }
    }

    private void removeOtherUserByUsername(String username) {
        if (mUserInfoResponseBean == null) {
            return;
        }
        Map<String, UserInfoResponseBean.UserInfo> map = mUserInfoResponseBean.getUserInfo();
        Iterator<Map.Entry<String, UserInfoResponseBean.UserInfo>> it = map.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<String, UserInfoResponseBean.UserInfo> entry = it.next();
            if (entry.getValue().getUsername().equals(username)) {
                mCurrentUserKey = entry.getKey();
                mUserInfo = entry.getValue();
            } else {
                it.remove();
            }
        }
    }

    public UserInfoResponseBean getUserInfoResponseBean() {
        return mUserInfoResponseBean;
    }

    public int getPasswordMinLen() {
        try {
            return mUserInfoRangeBean.getUserInfo().getItems().get(mCurrentUserKey).getItems().getPassword().getMinLen();
        } catch (NullPointerException e) {
            RSLog.e(TAG, "getPasswordMinLen: " + e.getMessage());
        }
        return 0;
    }

    public int getPasswordMaxLen() {
        try {
            return mUserInfoRangeBean.getUserInfo().getItems().get(mCurrentUserKey).getItems().getPassword().getMaxLen();
        } catch (NullPointerException e) {
            RSLog.e(TAG, "getPasswordMaxLen: " + e.getMessage());
        }
        return 0;
    }

    public UserInfoRangeBean.UserInfo.UserDetailItem.Items.Permission.PermissionItems getUserPermissionRange() {
        return mUserInfoRangeBean.getUserInfo().getItems().get(mCurrentUserKey).getItems().getPermission().getItems();
    }

    private Observable<BaseResponseBean<NoAttributeBean>> genError() {
        String s = "{\"result\":\"failed\"}";
        Type type = new TypeToken<BaseResponseBean<NoAttributeBean>>() {
        }.getType();
        BaseResponseBean<NoAttributeBean> responseBean = GsonUtil.getGson().fromJson(s, type);
        return Observable.just(responseBean);
    }
}
