#import <Foundation/Foundation.h>

#ifdef RCT_NEW_ARCH_ENABLED
#import <pitchprocessor/pitchprocessor.h>
#import <ReactCommon/RCTTurboModuleWithJSIBindings.h>

@interface NativeAudioProcessingModuleProvider : NSObject <NativeAudioProcessingModuleSpec, RCTTurboModuleWithJSIBindings>
#else
#import <React/RCTBridgeModule.h>

@interface NativeAudioProcessingModuleProvider : NSObject <RCTBridgeModule>
#endif

@end
