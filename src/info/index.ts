import { rsSdkExecuteSearchSubModuleFlow } from '../module/flowSubModules/rsSdkExecuteSearchSubModuleFlow';

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

export async function hasLogin() {
  return new Promise(() => {});
}

export async function searchDevicesInLocalSubnet() {
  return new Promise(async () => {
    return (await rsSdkExecuteSearchSubModuleFlow())?.search_devices_list ?? [];
  });
}
