#ifdef __cplusplus
#import "react-native-rssdk.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNRssdkSpec.h"

@interface Rssdk : NSObject <NativeRssdkSpec>
#else
#import <React/RCTBridgeModule.h>

@interface Rssdk : NSObject <RCTBridgeModule>
#endif

@end
