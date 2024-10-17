package com.rssdk.glsurface;

import com.blankj.utilcode.util.Utils;
import com.google.gson.reflect.TypeToken;

import java.io.IOException;
import java.lang.reflect.Type;
import java.util.List;

import io.reactivex.Observable;
import io.reactivex.ObservableSource;
import io.reactivex.functions.Function;

import com.rssdk.glsurface.encrypt.PasswordEncrypt;
import com.rs.network.rs.api.ApiDefine;
import com.rs.network.rs.api.ApiLoginInfo;
import com.rs.network.rs.base.BaseEncPassword;
import com.rs.network.rs.base.BaseRequestBean;
import com.rs.network.rs.base.BaseResponseBean;
import com.rs.network.rs.base.NoAttributeBean;
import com.rs.network.rs.bean.DevicePasswordBean;
import com.rs.network.rs.bean.TransKeyResponseBean;
import com.rs.network.rs.function.PasswordChangeFunction;
import com.rs.network.rs.function.TransKeyFunction;
import com.rs.network.rs.util.GsonUtil;

import org.bouncycastle.crypto.InvalidCipherTextException;

/**
 * Copyright (c) 2021 Raysharp.cn. All rights reserved.
 * <p>
 * FirstPasswordSetting
 *
 * @author huangdewen
 * @date 2021-11-16
 */
public class FirstPasswordSetting {

    private final ApiLoginInfo mApiLoginInfo;
    private TransKeyResponseBean.KeyLists basexKey;

    public FirstPasswordSetting(ApiLoginInfo apiLoginInfo) {
        this.mApiLoginInfo = apiLoginInfo;
    }

    public Observable<BaseResponseBean<NoAttributeBean>> savePassword(String newPassword) {

        if (mApiLoginInfo.isPasswordEnc()) {
            return TransKeyFunction.getLoginTransKey(Utils.getApp(), mApiLoginInfo, TransKeyFunction.TYPE_X_PUB)
                    .flatMap((Function<BaseResponseBean<TransKeyResponseBean>, ObservableSource<BaseResponseBean<NoAttributeBean>>>) transKeyResponseBean -> {
                        if (ApiDefine.Result.SUCCESS.equals(transKeyResponseBean.getResult())) {
                            List<TransKeyResponseBean.KeyLists> list = transKeyResponseBean.getData().getKeyLists();
                            for (TransKeyResponseBean.KeyLists key : list) {
                                if (TransKeyFunction.TYPE_X_PUB.equals(key.getType())) {
                                    basexKey = key;
                                }
                            }
                            if (basexKey == null) {
                                return genError();
                            }
                            return encrypt(newPassword, basexKey);
                        }
                        return genError();
                    });
        } else {
            DevicePasswordBean devicePasswordBean = new DevicePasswordBean();
            devicePasswordBean.setPassword(newPassword);
            BaseRequestBean<DevicePasswordBean> baseRequestBean = new BaseRequestBean<>();
            baseRequestBean.setData(devicePasswordBean);
            return PasswordChangeFunction.setFirstPassword(Utils.getApp(), baseRequestBean, mApiLoginInfo);
        }
    }

    private Observable<BaseResponseBean<NoAttributeBean>> encrypt(String password,
                                                                  TransKeyResponseBean.KeyLists basexKey) throws IOException, InvalidCipherTextException {
        BaseEncPassword baseEncPassword = PasswordEncrypt.encryptPassword(basexKey.getKey(), password, basexKey.getSeq());

        DevicePasswordBean devicePasswordBean = new DevicePasswordBean();
        devicePasswordBean.setBaseEncPassword(baseEncPassword);
        devicePasswordBean.setSupportRecoverPwd(false);
        BaseRequestBean<DevicePasswordBean> baseRequestBean = new BaseRequestBean<>();
        baseRequestBean.setData(devicePasswordBean);
        return PasswordChangeFunction.setFirstPassword(Utils.getApp(), baseRequestBean, mApiLoginInfo);
    }

    private Observable<BaseResponseBean<NoAttributeBean>> genError() {
        String s = "{\"result\":\"failed\"}";
        Type type = new TypeToken<BaseResponseBean<NoAttributeBean>>() {
        }.getType();
        BaseResponseBean<NoAttributeBean> responseBean = GsonUtil.getGson().fromJson(s, type);
        return Observable.just(responseBean);
    }
}
