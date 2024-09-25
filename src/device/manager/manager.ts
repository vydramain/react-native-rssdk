import { NativeModules } from 'react-native';

const { RsSdkReactJavaModule } = NativeModules;

import type {
  DeviceCredentialParams,
  DeviceIdParams,
  DeviceInfoType,
  DeviceManagerPromiseSuccessType,
  EPTZCMD,
} from './types';

export function loginDevice(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export type LoginDeviceWithCredentialResponse =
  DeviceManagerPromiseSuccessType & { value: DeviceInfoType };

export function loginDeviceWithCredential(
  params: DeviceCredentialParams
): Promise<LoginDeviceWithCredentialResponse> {
  return new Promise(function () {});
}

// export function loginDeviceByLowPower(
//   params: DeviceCredentialParams
// ): Promise<DeviceManagerPromiseSuccessType> {
//   return funsdk.loginDeviceByLowPower(params);
// }

// export function loginDeviceByLowPowerWithCredential(
//   params: DeviceCredentialParams
// ): Promise<DeviceManagerPromiseSuccessType> {
//   return funsdk.loginDeviceByLowPowerWithCredential(params);
// }

// export function wakeUpAndSendCtrl(
//   params: DeviceCredentialParams
// ): Promise<DeviceManagerPromiseSuccessType> {
//   return funsdk.loginDeviceByLowPowerWithCredential(params);
// }

export function logoutDevice(params: DeviceIdParams): Promise<true> {
  return new Promise(function () {});
}

export function getChannelInfo(params: DeviceIdParams): Promise<
  DeviceManagerPromiseSuccessType & {
    value: {
      canUsedChannelSize: number;
      isComOpen: boolean;
      nChnCount: number;
      st_channelTitle: string[];
    };
  }
> {
  return new Promise(function () {});
}

export function getChannelCount(params: DeviceIdParams): Promise<number> {
  return new Promise(function () {});
}

// export function setLocalDeviceUserPassword(
//   params: DeviceCredentialParams
// ): Promise<'success'> {
//   return funsdk.getChannelCount(params);
// }

export type LocalLoginInfoParams = DeviceCredentialParams & {
  token: string;
};

// export function setLocalLoginInfo(
//   params: LocalLoginInfoParams
// ): Promise<'success'> {
//   return funsdk.setLocalLoginInfo(params);
// }

export type ModifyDevicePasswordParams = DeviceCredentialParams & {
  deviceNewPassword: string;
};

export function modifyDevicePassword(
  params: ModifyDevicePasswordParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export type ModifyDeviceNameParams = DeviceIdParams & {
  deviceName: string;
};

export function modifyDeviceName(
  params: ModifyDeviceNameParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export type DevicePTZControlParams = {
  deviceId: string;
  command: EPTZCMD;
  bStop: boolean;
  deviceChannel: number;
  speed?: 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | number; // default 4
};

export function devicePTZcontrol(
  params: DevicePTZControlParams
): Promise<boolean> {
  const withDefaultParams: Required<DevicePTZControlParams> = {
    speed: 4,
    ...params,
  };

  return new Promise(function () {});
}

export function resetDeviceConfig(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function rebootDevice(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export type CaptureFromDeviceAndSaveToDeviceParams = {
  deviceId: string;
  deviceChannel: number;
};

export function captureFromDeviceAndSaveToDevice(
  params: CaptureFromDeviceAndSaveToDeviceParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}
