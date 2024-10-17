import type {
  DeviceCredentialParams,
  DeviceIdParams,
  DeviceInfoType,
  DeviceManagerPromiseSuccessType,
  EPTZCMD,
} from './types';

export function loginDevice(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export type LoginDeviceWithCredentialResponse =
  DeviceManagerPromiseSuccessType & { value: DeviceInfoType };

export function loginDeviceWithCredential(
  _params: DeviceCredentialParams
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

export function logoutDevice(_params: DeviceIdParams): Promise<true> {
  return new Promise(function () {});
}

export function getChannelInfo(_params: DeviceIdParams): Promise<
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

export function getChannelCount(_params: DeviceIdParams): Promise<number> {
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
  _params: ModifyDevicePasswordParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export type ModifyDeviceNameParams = DeviceIdParams & {
  deviceName: string;
};

export function modifyDeviceName(
  _params: ModifyDeviceNameParams
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
  _params: DevicePTZControlParams
): Promise<boolean> {
  // const withDefaultParams: Required<DevicePTZControlParams> = {
  //   speed: 4,
  //   ...params,
  // };

  return new Promise(function () {});
}

export function resetDeviceConfig(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function rebootDevice(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export type CaptureFromDeviceAndSaveToDeviceParams = {
  deviceId: string;
  deviceChannel: number;
};

export function captureFromDeviceAndSaveToDevice(
  _params: CaptureFromDeviceAndSaveToDeviceParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}
