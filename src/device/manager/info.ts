import { NativeModules } from 'react-native';

const { RsSdkReactJavaModule } = NativeModules;

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
  params: IsDeviceFunctionSupportParams
): Promise<
  DeviceManagerPromiseSuccessType & {
    value: boolean;
  }
> {
  return new Promise(function () {});
}

export function getDeviceModel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getSoftWareVersion(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getBuildTime(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getHardWare(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType & { value: string }> {
  return new Promise(function () {});
}

export function getDigChannel(params: DeviceIdParams): Promise<
  DeviceManagerPromiseSuccessType & {
    value: number;
  }
> {
  return new Promise(function () {});
}

export function getExtraChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getVideoInChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getTalkInChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getAlarmInChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getAlarmOutChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getCombineSwitch(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getVideoOutChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getAudioInChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getTalkOutChannel(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getUpdataTime(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getEncryptVersion(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getDeviceRunTime(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getHardWareVersion(
  params: DeviceIdParams
): Promise<DeviceManagerPromiseSuccessType> {
  return new Promise(function () {});
}

export function getMcuVersion(
  params: DeviceIdParams
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
  params: DeviceIdParams
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

export function getFunStrAttr(params: {
  FunStrAttr: EFUN_ATTR;
}): Promise<string> {
  return new Promise(function () {});
}

export function devGetLocalUserName(params: DeviceIdParams): Promise<string> {
  return new Promise(function () {});
}

export function getDevType(params: DeviceIdParams): Promise<number> {
  return new Promise(function () {});
}

export function devGetLocalEncToken(params: DeviceIdParams): Promise<string> {
  return new Promise(function () {});
}
