import type {
  DeviceIdParams,
  DeviceManagerPromiseSuccessType,
  EFUN_ATTR,
} from './types';

type IsDeviceFunctionSupportParams = {
  deviceId: string;
  functionName: string;
  functionCommandStr: string;
};

export function isDeviceFunctionSupport(
  _params: IsDeviceFunctionSupportParams
): Promise<
  DeviceManagerPromiseSuccessType & {
    value: boolean;
  }
> {
  return new Promise(function () {});
}

export function getDeviceModel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getSoftWareVersion(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getBuildTime(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getHardWare(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType & { value: string }> {
  return new Promise(function () {});
}

export function getDigChannel(_params: DeviceIdParams): Promise<
  DeviceManagerPromiseSuccessType & {
    value: number;
  }
> {
  return new Promise(function () {});
}

export function getExtraChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getVideoInChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getTalkInChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getAlarmInChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getAlarmOutChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getCombineSwitch(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getVideoOutChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getAudioInChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getTalkOutChannel(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getUpdataTime(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getEncryptVersion(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getDeviceRunTime(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getHardWareVersion(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getMcuVersion(
  _params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

// public static final int CONNECT_TYPE_P2P = 0;
// public static final int CONNECT_TYPE_TRANSMIT = 1;
// public static final int CONNECT_TYPE_IP = 2;
// public static final int CONNECT_TYPE_RPS = 5;
// public static final int CONNECT_TYPE_RTS_P2P = 6;
// public static final int CONNECT_TYPE_RTS = 7;
// 0:p2p连接，1转发模式 2:IP地址直连
export enum networkMode {
  P2P,
  FORWARDING,
  IP,
  RPS = 5,
  RTS_P2P,
  RTS,
}

export function getNetworkMode(
  _params: DeviceIdParams
): Promise<{ value: networkMode }> {
  return new Promise(function () {});
}

export function getAccessToken(): Promise<string> {
  return new Promise(function () {});
}

export type SecretPromiseSuccessType = {
  timeMillis: string;
  secret: string;
  uuid: string;
  appKey: string;
  appSecret: string;
  movedCard: number;
};

export function getSecret(): Promise<SecretPromiseSuccessType> {
  return new Promise(function () {});
}

export function getFunStrAttr(_params: {
  FunStrAttr: EFUN_ATTR;
}): Promise<string> {
  return new Promise(function () {});
}

export function devGetLocalUserName(_params: DeviceIdParams): Promise<string> {
  return new Promise(function () {});
}

export function getDevType(_params: DeviceIdParams): Promise<number> {
  return new Promise(function () {});
}

export function devGetLocalEncToken(_params: DeviceIdParams): Promise<string> {
  return new Promise(function () {});
}
