import * as sdk from '../RsSdkWrapperModule';
import { deviceIdInstance } from '../deviceSingleton';
import type { RsSdkLogoutSubModuleResponse } from '../RsSdkTypes';

export const rsSdkExecuteLogoutSubModuleFlow = async (): Promise<
  RsSdkLogoutSubModuleResponse | undefined
> => {
  try {
    const { device_id } = await deviceIdInstance;

    const logout_result = await sdk.rs_sdk_device_logout(device_id);
    console.log("RN called rs_sdk_device_logout's result: " + logout_result);

    const destroy_result = await sdk.rs_sdk_destroy_device(device_id);
    console.log("RN called rs_sdk_destroy_device's result: " + destroy_result);

    return {
      logout_result,
      destroy_result,
    };
  } catch (error) {
    console.error(
      'Error occurred while RS SDK logout search sub module flow with error: ',
      error
    );
    return undefined;
  }
};
