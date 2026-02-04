#pragma once

#include "MyProcessorNode.h"
#include <audioapi/HostObjects/AudioNodeHostObject.h>

#include <memory>
#include <vector>

namespace audioapi {
using namespace facebook;

class MyProcessorNodeHostObject : public AudioNodeHostObject {
public:
  explicit MyProcessorNodeHostObject(
      const std::shared_ptr<MyProcessorNode> &node);

  JSI_PROPERTY_GETTER_DECL(gain);
  JSI_PROPERTY_SETTER_DECL(gain);
};
} // namespace audioapi
