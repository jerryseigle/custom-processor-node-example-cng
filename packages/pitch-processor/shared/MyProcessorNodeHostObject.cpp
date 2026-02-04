#include "MyProcessorNodeHostObject.h"

#include <memory>

namespace audioapi {

MyProcessorNodeHostObject::MyProcessorNodeHostObject(
    const std::shared_ptr<MyProcessorNode> &node)
    : AudioNodeHostObject(node) {
  addGetters(JSI_EXPORT_PROPERTY_GETTER(MyProcessorNodeHostObject, gain));
  addSetters(JSI_EXPORT_PROPERTY_SETTER(MyProcessorNodeHostObject, gain));
}

JSI_PROPERTY_GETTER_IMPL(MyProcessorNodeHostObject, gain) {
  auto processorNode = std::static_pointer_cast<MyProcessorNode>(node_);
  return {processorNode->getGain()};
}

JSI_PROPERTY_SETTER_IMPL(MyProcessorNodeHostObject, gain) {
  auto processorNode = std::static_pointer_cast<MyProcessorNode>(node_);
  processorNode->setGain(value.getNumber());
}

} // namespace audioapi
