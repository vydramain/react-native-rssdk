import * as sdk from '../RsSdkWrapperModule';
import type {
  RsSdkLoginSubModuleParams,
  RsSdkLoginSubModuleResponse,
} from '../RsSdkTypes';
import { deviceIdInstance } from '../deviceSingleton';

export const rsSdkExecuteLoginSubModuleFlow = async (
  params: RsSdkLoginSubModuleParams | undefined
): Promise<RsSdkLoginSubModuleResponse | undefined> => {
  if (!params) {
    return undefined;
  }

  try {
    const { device_id } = await deviceIdInstance;

    const login_result = await sdk.rs_sdk_device_login(
      device_id,
      JSON.stringify(params)
    );
    console.log(
      "RN called rs_sdk_device_login's result: " + JSON.stringify(login_result)
    );

    return {
      device_id,
      login_result: JSON.parse(login_result),
    };
  } catch (error) {
    console.error(
      'Error occurred while RS SDK executing login sub module flow with error: ',
      error
    );
    return undefined;
  }
};
