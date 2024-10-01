import * as sdk from '../RsSdkWrapperModule';
import * as console from 'node:console';

export const deviceIdInstance = (() => {
  let instance: DeviceIdSingleton | null = null;

  class DeviceIdSingleton {
    private readonly _device_id: string;

    private constructor(deviceId: string) {
      this._device_id = deviceId;
    }

    static async init(): Promise<DeviceIdSingleton> {
      if (!instance) {
        const device_id = await sdk.rs_sdk_device_create();
        console.log("RN called rs_sdk_device_create's result: " + device_id);
        instance = new DeviceIdSingleton(device_id);
      }
      return instance;
    }

    get device_id(): string {
      return this._device_id;
    }
  }

  return DeviceIdSingleton.init();
})();
