/**
 * Just empty function because RS doesn't support external device management
 */
export function addDevice(): Promise<any> {
  return new Promise(() => {
    return true;
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
