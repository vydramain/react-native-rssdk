import { rsSdkExecuteLogoutSubModuleFlow } from '../../module/flowSubModules/rsSdkExecuteLogoutSubModuleFlow';
import { rsSdkExecuteLoginSubModuleFlow } from '../../module/flowSubModules/rsSdkExecuteLoginSubModuleFlow';

import type { RsSdkLoginConnctionCallbackParams } from '../../types';
import { RsSdkOemTypeEnum, RsSdkProtocolEnum } from '../../enums';
import { rsSDKParseP2PType } from '../../utils';

export type AddDeviceCommonParamsType = {
  deviceId?: string;
  username?: string;
  password?: string;
  deviceName?: string;
  deviceType?: any;
  deviceIp?: string;
  port?: number;
  deviceIdNum?: number;
};

/**
 * Async login and logout for check is device available
 */
export function addDevice(
  params: AddDeviceCommonParamsType | undefined
): Promise<any> {
  return new Promise(async () => {
    if (!params) {
      return;
    }

    const { deviceId = '', port = 80, username = '', password = '' } = params;

    try {
      const loginResponse = await rsSdkExecuteLoginSubModuleFlow({
        'ip or id': deviceId,
        'port': port,
        'user': username,
        'password': password,
        'p2p type': rsSDKParseP2PType(deviceId),
        'oem type': RsSdkOemTypeEnum.optimus,
        'protocol': RsSdkProtocolEnum.auto,
      });

      const loginDevicesCallbacksParamsList: RsSdkLoginConnctionCallbackParams[] =
        loginResponse?.login_result.login_devices_callback_params_list;

      let is_login_successful = false;
      loginDevicesCallbacksParamsList.forEach(
        (device: RsSdkLoginConnctionCallbackParams) => {
          if (device.status === 'success') {
            is_login_successful = true;
          }
        }
      );

      if (!is_login_successful) {
        console.error("Login response isn't success");
        return;
      }

      return !!(await rsSdkExecuteLogoutSubModuleFlow());
    } catch (error) {
      console.error(
        'Error occurred while logging in and logging out device: ' +
          JSON.stringify(error, null, 2)
      );
      return;
    }
  });
}

export type DeleteDeviceParams = {
  deviceId: string;
};

/**
 * Just empty function because RS doesn't support external device management
 */
export function deleteDevice(): Promise<number> {
  return new Promise(() => {
    return true;
  });
}
