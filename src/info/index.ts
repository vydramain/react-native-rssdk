import type { deviceCommonParamsType, RsSdkLoginConnctionCallbackParams } from '../module/RsSdkTypes';
import { rsSdkExecuteLoginSubModuleFlow } from '../module/flowSubModules/rsSdkExecuteLoginSubModuleFlow';
import { rsSDKParseP2PType } from '../module/RsSdkUtils';
import { RsSdkOemTypeEnum, RsSdkProtocolEnum } from '../module/RsSdkEnums';
import { rsSdkExecuteLogoutSubModuleFlow } from '../module/flowSubModules/rsSdkExecuteLogoutSubModuleFlow';

export function logout(): Promise<any> {
  return new Promise(() => {});
}

export function getUserId(): Promise<any> {
  return new Promise(() => {});
}

export function getUserName(): Promise<any> {
  return new Promise(() => {});
}

export function getEmail(): Promise<any> {
  return new Promise(() => {});
}

export function getPhoneNo(): Promise<any> {
  return new Promise(() => {});
}

export async function hasLogin(params: deviceCommonParamsType | undefined) {
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
      'Error occurred while executing utility add rs sdk device function: ',
      error
    );
    return;
  }
}
