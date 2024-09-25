export type LoginByAccountParams = {
  username: string;
  password: string;
};

/**
 * does not work
 */
export function loginByAccount(params: LoginByAccountParams): Promise<any> {
  return new Promise(function () {});
}

export type LoginByLocalParams = {};

/**
 * does not work
 */
export function loginByLocal(params: LoginByLocalParams): Promise<any> {
  return new Promise(function () {});
}

export type LoginByAPParams = {};

/**
 * does not work
 */
export function loginByAP(params: LoginByAPParams): Promise<any> {
  return new Promise(function () {});
}
