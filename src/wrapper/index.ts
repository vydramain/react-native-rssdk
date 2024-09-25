import {NativeModules} from 'react-native';

const {RsSdkReactJavaModule} = NativeModules;

export const rs_sdk_device_create = async () => {
  try {
    return await RsSdkReactJavaModule.rs_create_device();
  } catch (e) {
    console.error('Error of rs_create_device: ' + e);
  }
};

export const rs_sdk_destroy_device = async (device_id: string) => {
  try {
    return await RsSdkReactJavaModule.rs_destroy_device(device_id);
  } catch (e) {
    console.error('Error of rs_destroy_device: ' + e);
  }
};

/**
 * Login device:
 *
 * There are different types of value: `p2p type` for cameras.
 * They all differ slightly with respect to the type of id. He listed three of them:
 *    - `tut` - contains 20 characters
 *    - `vv` - contains 16 or 17 characters
 *    - `srvv` - id necessarily begins with the characters 'RSV'
 *    - All other types of id he said should be treated as rs.
 *
 * Also, there are different types of value `oem type`.
 * This field should always keep `optimus` because most of the devices for use works with 'Optimus' OS type.
 *
 * @param device_id Is icd of device from `rs_create_device` function
 * @param login_param Is JSON object like:
 *                    "ip or id": "E9N862FV5MG378S4111A",
 *                    "port": 443,
 *                    "user": "admin",
 *                    "password": "Qwerty123",
 *                    "ddns id server addr": "",
 *                    "p2p type": "tutk",
 *                    "oem type": "optimus",
 *                    "protocol": "auto"
 *
 */
export const rs_sdk_device_login = async (device_id: string, login_param: string) => {
  try {
    return await RsSdkReactJavaModule.rs_device_login(device_id, login_param);
  } catch (e) {
    console.error('Error of rs_device_login: ' + e);
  }
};

export const rs_sdk_device_logout = async (device_id: string) => {
  try {
    return await RsSdkReactJavaModule.rs_device_logout(device_id);
  } catch (e) {
    console.error('Error of rs_device_logout: ' + e);
  }
};

/**
 *
 * @param param    Is JSON object with fields:
 *                 - "oem type": "default", "optimus"
 *                 - "start ip": if you use udp point to point search, fill this, such as "172.18.12.2",
 *                 otherwise if you use lan broadcast, just ignore this value or fill ""
 *                 - "stop ip": if you use udp point to point search, fill this, such as "172.18.12.254",
 *                 otherwise if you use lan broadcast, just ignore this value or fill ""
 */
export const rs_sdk_search_device = async (param: string) => {
  try {
    return await RsSdkReactJavaModule.rs_search_device(param);
  } catch (e) {
    console.error('Error of rs_search_device: ' + e);
  }
};

/**
 *
 * @param device_id Is id of device from `rs_create_device` function
 * @param param Is JSON object with fields:
 *              "channel": (uin32_t) 0 1 2 3 4 and so on,
 *              "stream type": "main stream" "sub stream" "mobile stream",
 *              "auto connect": (bool) automatic reconnect or not,
 *              "cached decoded frame": (int) Used for android, just fill 0
 */
export const rs_sdk_start_preview = async (device_id: string, param: string) => {
  try {
    return await RsSdkReactJavaModule.rs_start_preview(device_id, param);
  } catch (e) {
    console.error('Error of rs_start_preview: ' + e);
  }
};

export const rs_sdk_stop_preview = async (device_id: string) => {
  try {
    return await RsSdkReactJavaModule.rs_stop_preview(device_id);
  } catch (e) {
    console.error('Error of rs_stop_preview: ' + e);
  }
};
