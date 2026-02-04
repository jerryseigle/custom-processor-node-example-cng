#include "ProcessorInstaller.h"
#include "PitchProcessorNode.h"
#include "PitchProcessorNodeHostObject.h"
#include <audioapi/HostObjects/BaseAudioContextHostObject.h>

namespace pitchprocessor {

void InstallCustomProcessor(facebook::jsi::Runtime &runtime) {
  auto installer = facebook::jsi::Function::createFromHostFunction(
      runtime,
      facebook::jsi::PropNameID::forAscii(runtime, "createCustomProcessorNode"),
      0,
      [](facebook::jsi::Runtime &runtime, const facebook::jsi::Value &thisVal,
         const facebook::jsi::Value *args, size_t count) {
        auto object = args[0].getObject(runtime);
        auto context =
            object.getHostObject<audioapi::BaseAudioContextHostObject>(runtime);
        if (context != nullptr) {
          auto node =
              std::make_shared<audioapi::PitchProcessorNode>(context->context_);
          auto nodeHostObject =
              std::make_shared<audioapi::PitchProcessorNodeHostObject>(node);
          return facebook::jsi::Object::createFromHostObject(runtime,
                                                             nodeHostObject);
        }
        return facebook::jsi::Object::createFromHostObject(runtime, nullptr);
      });

  runtime.global().setProperty(runtime, "createCustomProcessorNode", installer);
}

} // namespace pitchprocessor
