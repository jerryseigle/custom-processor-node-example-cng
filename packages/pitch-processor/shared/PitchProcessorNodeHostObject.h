#pragma once

#include "PitchProcessorNode.h"
#include <audioapi/HostObjects/AudioNodeHostObject.h>

#include <memory>
#include <vector>

namespace audioapi {
using namespace facebook;

class PitchProcessorNodeHostObject : public AudioNodeHostObject {
public:
  explicit PitchProcessorNodeHostObject(
      const std::shared_ptr<PitchProcessorNode> &node);

  JSI_PROPERTY_GETTER_DECL(gain);
  JSI_PROPERTY_SETTER_DECL(gain);
};
} // namespace audioapi
