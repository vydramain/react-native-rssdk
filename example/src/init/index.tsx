import React from 'react';

import { Platform } from 'react-native';
import {
  SDKInit,
  loginByAccount,
  updateAllDevStateFromServer,
  getDetailDeviceList,
  loginDeviceWithCredential, addDevice,
} from 'react-native-rssdk';

const delay = (ms: number) => {
  return new Promise((resolve) => setTimeout(resolve, ms));
};

export const useInit = () => {
  const [isInit, setIsInit] = React.useState(false);
  const [statusText, setStatusText] = React.useState<null | {
    text: string;
    value?: any;
  }>(null);

  const handleSetStatus = (text: string, value?: any) => {
    setStatusText({
      text,
      value,
    });
  };

  const reinit = async () => {
    try {
      // const res = await loginByAccount({
      //   username: '',
      //   password: '',
      // });
      console.log('start somefunc');
      handleSetStatus('start somefunc');
      const res = await loginByAccount({
        username: 'USER_NAME',
        password: 'USER_PASSWORD',
      });
      // const res = await registerByNotBind({
      //   username: '',
      //   password: '',
      // });
      console.log('res somefunc: ', res);
      handleSetStatus('res somefunc: ', res);
      // await someInfos();
    } catch (error) {
      console.log('error in someFuncs: ', error);
      handleSetStatus('error in someFuncs: ', (error as Error)?.message);
    }
  };

  React.useEffect(() => {
    if (isInit) {
      return;
    }

    // funSDKInit({});
    if (Platform.OS === 'ios') {
      SDKInit({
        customPwdType: 0,
        customPwd: 'PWD',
        customServerAddr: 'SERVER_ADDR',
        customPort: 80,
        // TODO: удалить then
      }).then((res) => {
        console.log('res: ', res);
        // setIsInit(true);
      });
    }

    if (Platform.OS === 'android') {
      SDKInit({
        customPwdType: 0,
        customPwd: 'PWD',
        customServerAddr: 'SERVER_ADDR',
        customPort: 80,
        // TODO: удалить then
      });
      // setIsInit(true);
    }
    const someFuncs = async () => {
      try {
        // const res = await loginByAccount({
        //   username: '',
        //   password: '',
        // });
        console.log('start somefunc');
        handleSetStatus('start somefunc');
        const res = await loginByAccount({
          username: 'USER_NAME',
          password: 'USER_PASSWORD',
        });
        // const res = await registerByNotBind({
        //   username: USER_NAME,
        //   password: USER_PASSWORD,
        // });
        console.log('res somefunc: ', res);
        handleSetStatus('res somefunc: ', res);
        await someInfos();
      } catch (error) {
        console.log('error in someFuncs: ', error);
        handleSetStatus('error in someFuncs: ', (error as Error)?.message);
      }
    };
    const someInfos = async () => {
      try {
        await delay(100);
        // const userId = await getUserId();
        //   const userName = await getUserName();
        //   const deviceList = await getDeviceList();
        //   console.log('res someinfos: ', userId, userName, deviceList);
        //   handleSetStatus('res someinfos: ', { userId, userName, deviceList });
        await addDeviceTest();
        const updatedStatus = await updateAllDevStateFromServer();
        console.log('updatedStatus: ', updatedStatus);
        handleSetStatus('updatedStatus: ', updatedStatus);

        await delay(100);
        const detailedList = await getDetailDeviceList();
        console.log('detailedList: ', detailedList);
        handleSetStatus('detailedList: ', detailedList);

        const loginstatus = await loginDeviceWithCredential({
          deviceId: 'DEVICE_ID',
          deviceLogin: 'DEVICE_LOGIN',
          devicePassword: 'DEVICE_PASSWORD',
        });
        console.log('loginstatus: ', loginstatus);
        handleSetStatus('loginstatus: ', loginstatus);
        // setIsInit(true);
      } catch (error) {
        console.log('error: ', error);
      } finally {
        setIsInit(true);
      }
    };
    const addDeviceTest = async () => {
      try {
        const addedDevice = await addDevice({
          deviceId: 'DEVICE_ID',
          username: 'DEVICE_LOGIN',
          password: 'DEVICE_PASSWORD',
          // deviceType: 'no need',
          deviceName: 'supername2',
        });
        console.log('addedDevice: ', addedDevice);
        // const deviceList = await getDeviceList();
        // console.log('deviceList: ', deviceList);
      } catch (error) {
        console.log('error on add device: ', error);
      }
    };
    setTimeout(() => {
      someFuncs();
    }, 3000);
  }, [isInit]);

  return { isInit, statusText, reinit };
};
