import { RsSdkP2PTypeEnum } from '../enums';


// Regular expression for IPv4
const ipv4Regex = /^(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)(\.(25[0-5]|2[0-4]\d|1\d{2}|[1-9]?\d)){3}$/;

// Regular expression for IPv6
const ipv6Regex = /^(([0-9a-fA-F]{1,4}):){7}([0-9a-fA-F]{1,4})$/;

export const rsSDKParseP2PType = (id: string): RsSdkP2PTypeEnum => {
  switch (true) {
    case ipv4Regex.test(id) || ipv6Regex.test(id):
      return RsSdkP2PTypeEnum.IP;
    case id.startsWith('RSV'):
      return RsSdkP2PTypeEnum.RSVV;
    case id.length === 20:
      return RsSdkP2PTypeEnum.TUTK;
    case id.length === 16 || id.length === 17:
      return RsSdkP2PTypeEnum.VV;
    default:
      return RsSdkP2PTypeEnum.RS;
  }
};
