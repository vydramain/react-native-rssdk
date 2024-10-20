// import { NativeModules, Platform } from 'react-native';
//
// const LINKING_ERROR =
//   `The package 'react-native-rssdk' doesn't seem to be linked. Make sure: \n\n` +
//   Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
//   '- You rebuilt the app after installing the package\n' +
//   '- You are not using Expo Go\n';
//
// const Rssdk = NativeModules.Rssdk
//   ? NativeModules.Rssdk
//   : new Proxy(
//       {},
//       {
//         get() {
//           throw new Error(LINKING_ERROR);
//         },
//       }
//     );
//
// export function multiply(a: number, b: number): Promise<number> {
//   return Rssdk.multiply(a, b);
// }

export * from './core';
export * from './device';
export * from './enums';
export * from './info';
export * from './login';
export * from './monitor';
export * from './register';
export * from './types';
export * from './utils';
