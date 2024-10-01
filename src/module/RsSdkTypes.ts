import {
  RsSdkConnctionCallbackEnum,
  RsSdkOemTypeEnum,
  RsSdkP2PTypeEnum,
  RsSdkProtocolEnum,
} from './RsSdkEnums';

export type RsSdkLoginSubModuleParams = {
  'ip or id': string;
  'port': number;
  'user': string;
  'password': string;
  'p2p type': RsSdkP2PTypeEnum;
  'oem type': RsSdkOemTypeEnum;
  'protocol': RsSdkProtocolEnum;
};

export type RsSdkLoginSubModuleResponse = {
  device_id: string;
  login_result: any;
};

export type RsSdkLogoutSubModuleResponse = {
  logout_result: number;
  destroy_result: number;
};

export type RsSdkSearchSubModuleResponse = {
  search_devices_result: string;
  search_devices_list: RsSdkFoundDevicesParams[];
};

export type RsSdkStartPreviewSubModuleParams = {
  device_id: string;
  params: {
    'channel': number;
    'stream type': string;
    'auto connect': boolean;
  };
};

export type RsSdkStopPreviewSubModuleParams = {
  session_id: string;
};

export type RsSdkLoginResult = {
  login_devices_result: number;
  login_devices_callback_params_list: RsSdkLoginConnctionCallbackParams[];
};

export type RsSdkLoginConnctionCallbackParams =
  | {
      info: {
        activation_pwd: boolean;
        channel_info: string;
        cookie: string;
        device_info: string;
        ip: string;
        is_https: number;
        password_enc: number;
        port: number;
        protocol: string;
        real_ip_or_id: string;
        real_port: number;
        support_recover_password: number;
        syn_activation_pwd_enable: boolean;
        token: string;
        use_recover_password: number;
      };
      status: RsSdkConnctionCallbackEnum;
    }
  | {
      status: RsSdkConnctionCallbackEnum;
    };

export type RsSdkFoundDevicesParams = {
  'analogy channel number': number;
  'channel number': number;
  'device id': number;
  'device name': string;
  'device type': string;
  'device type ull': number;
  'device version': string;
  'dns1': string;
  'dns2': string;
  'gateway': string;
  'host name': string;
  'http_api_version'?: string; // Optional based on the sample you provided
  'https_port'?: number; // Optional
  'ip': string;
  'is first login': number;
  'mac addr': string;
  'manufacture': string;
  'media port': number;
  'net interface': number;
  'netmask': string;
  'network mode': string;
  'p2p id': string;
  'rtsp port': number;
  'serialnum': string;
  'support_http_api_config_net'?: number; // Optional
  'sys_channel_num': number;
  'version': number;
  'web port': number;
};

export type deviceCommonParamsType = {
  deviceId?: string;
  username?: string;
  password?: string;
  deviceName?: string;
  deviceIp?: string;
  port?: number;
  deviceIdNum?: number;
};
