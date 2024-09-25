import { NativeModules } from 'react-native';

const { RsSdkReactJavaModule } = NativeModules;

// previous
// export type AddDeviceParams = {
//   deviceId: string;
//   username: string;
//   password: string;
//   deviceName: string;
//   deviceType: string;
// };

export type AddDeviceParams = {
  // SerialNumber / IP / DNS
  deviceId?: string;
  username?: string;
  password?: string;
  deviceName?: string;
  deviceType?: any;
  deviceIp?: string;
  DMZTcpPort?: number;
  deviceIdNum?: number;
};

/**
 * deviceId can be as:
 *
 * SerialNumber / IP / DNS
 *
 *
 * add dev by deviceId:
 *
 *  deviceId: string;
 *  username: string;
 *  password: string;
 *  deviceName: string;
 */
export function addDevice(params: AddDeviceParams): Promise<any> {
  return new Promise(function () {});
}

export type DeleteDeviceParams = {
  deviceId: string;
};

/**
 * status number in answer
 */
export function deleteDevice(params: DeleteDeviceParams): Promise<number> {
  return new Promise(function () {});
}
