export function getDeviceList(): Promise<any> {
  return new Promise(function () {});
}

export type GetDeviceStateParams = {
  deviceId: string;
};

// OFF_LINE：0  offline
// ON_LINE：1 online
// SLEEP：2 Sleeping (low-power devices)
// WAKE_UP：3 Waking up (low power device)
// WAKE：4  Woke up (low power device)
// SLEEP_UNWAKE：5  Unwakeable during sleep (low power device)
// PREPARE_SLEEP：6 Preparing for Sleep (low power device)

/*
 * deviceId: string;
 */
export function getDeviceState(_params: GetDeviceStateParams): Promise<any> {
  return new Promise(function () {});
}

export type DetailDeviceType = {
  devId: string;
  devIp: string;
  devIpPort: string;
  devName: string;
  devPort: number;
  devState: number;
  devType: any; // Incompatible param
};

export function getDetailDeviceList(): Promise<DetailDeviceType[]> {
  return new Promise(function () {});
}

export function updateAllDevStateFromServer(): Promise<any> {
  return new Promise(function () {});
}
