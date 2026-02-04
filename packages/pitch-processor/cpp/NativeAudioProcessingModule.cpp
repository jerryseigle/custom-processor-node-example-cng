#include "NativeAudioProcessingModule.h"
#include "ProcessorInstaller.h"

namespace facebook::react {

NativeAudioProcessingModule::NativeAudioProcessingModule(
    std::shared_ptr<CallInvoker> jsInvoker)
    : NativeAudioProcessingModuleCxxSpec(std::move(jsInvoker)) {}

void NativeAudioProcessingModule::injectCustomProcessorInstaller(
    jsi::Runtime &runtime) {
  pitchprocessor::InstallCustomProcessor(runtime);
}

} // namespace facebook::react
