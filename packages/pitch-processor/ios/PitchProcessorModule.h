#import <Foundation/Foundation.h>

#ifdef RCT_NEW_ARCH_ENABLED
#import <pitchprocessor/pitchprocessor.h>
#import <ReactCommon/RCTTurboModuleWithJSIBindings.h>

@interface PitchProcessorModule : NSObject <NativeAudioProcessingModuleSpec, RCTTurboModuleWithJSIBindings>
#else
#import <React/RCTBridgeModule.h>

@interface PitchProcessorModule : NSObject <RCTBridgeModule>
#endif

@end
