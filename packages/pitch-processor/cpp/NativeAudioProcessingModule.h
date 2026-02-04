#pragma once

#include <pitchprocessorJSI.h>

#include <jsi/jsi.h>
#include <memory>
#include <string>

namespace facebook::react {

class NativeAudioProcessingModule
    : public NativeAudioProcessingModuleCxxSpec<NativeAudioProcessingModule> {
public:
  NativeAudioProcessingModule(std::shared_ptr<CallInvoker> jsInvoker);
  void injectCustomProcessorInstaller(jsi::Runtime &runtime);
};

} // namespace facebook::react
