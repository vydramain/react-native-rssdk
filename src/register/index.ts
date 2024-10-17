export type UserCheckParams = {
  username: string;
};

export function userCheck(_params: UserCheckParams): Promise<any> {
  return new Promise(function () {});
}

export type SendEmailCodeParams = {
  email: string;
};

export function sendEmailCode(_params: SendEmailCodeParams): Promise<any> {
  return new Promise(function () {});
}

export type SendPhoneCodeParams = {
  username: string;
  phoneNumber: string;
};

export function sendPhoneCode(_params: SendPhoneCodeParams): Promise<any> {
  return new Promise(function () {});
}

export type RegisterByPhoneParams = {
  username: string;
  password: string;
  verifyCode: string;
  phoneNumber: string;
};

export function registerByPhone(_params: RegisterByPhoneParams): Promise<any> {
  return new Promise(function () {});
}

export type RegisterByEmailParams = {
  username: string;
  password: string;
  email: string;
  verifyCode: string;
};

export function registerByEmail(_params: RegisterByEmailParams): Promise<any> {
  return new Promise(function () {});
}

export type RegisterByNotBindParams = {
  username: string;
  password: string;
};

export function registerByNotBind(
  _params: RegisterByNotBindParams
): Promise<any> {
  return new Promise(function () {});
}
