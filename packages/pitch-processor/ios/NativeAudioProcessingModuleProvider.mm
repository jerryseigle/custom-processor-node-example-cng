#import "NativeAudioProcessingModuleProvider.h"

#import <React/RCTBridgeModule.h>
#import <memory>

#ifdef RCT_NEW_ARCH_ENABLED
#import "ProcessorInstaller.h"
#import <jsi/jsi.h>
#endif

#ifdef RCT_NEW_ARCH_ENABLED
@implementation NativeAudioProcessingModuleProvider {
  facebook::jsi::Runtime *_runtime;
  BOOL _jsiInstalled;
}
#else
@implementation NativeAudioProcessingModuleProvider
#endif

RCT_EXPORT_MODULE(NativeAudioProcessingModule)

RCT_EXPORT_METHOD(injectCustomProcessorInstaller)
{
#ifdef RCT_NEW_ARCH_ENABLED
  // JSI bindings are installed in installJSIBindingsWithRuntime to ensure
  // they are created on the JS runtime thread.
  (void)_runtime;
#endif
}

#ifdef RCT_NEW_ARCH_ENABLED
- (void)installJSIBindingsWithRuntime:(facebook::jsi::Runtime &)runtime
                          callInvoker:(const std::shared_ptr<facebook::react::CallInvoker> &)callInvoker
{
  _runtime = &runtime;
  (void)callInvoker;
  if (!_jsiInstalled) {
    pitchprocessor::InstallCustomProcessor(runtime);
    _jsiInstalled = YES;
  }
}

- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
    (const facebook::react::ObjCTurboModule::InitParams &)params
{
  return std::make_shared<facebook::react::NativeAudioProcessingModuleSpecJSI>(params);
}
#endif

@end
