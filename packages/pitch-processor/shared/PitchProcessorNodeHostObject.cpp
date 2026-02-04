#include "PitchProcessorNodeHostObject.h"

#include <memory>

namespace audioapi {

PitchProcessorNodeHostObject::PitchProcessorNodeHostObject(
    const std::shared_ptr<PitchProcessorNode> &node)
    : AudioNodeHostObject(node) {
  addGetters(JSI_EXPORT_PROPERTY_GETTER(PitchProcessorNodeHostObject, gain));
  addSetters(JSI_EXPORT_PROPERTY_SETTER(PitchProcessorNodeHostObject, gain));
}

JSI_PROPERTY_GETTER_IMPL(PitchProcessorNodeHostObject, gain) {
  auto processorNode = std::static_pointer_cast<PitchProcessorNode>(node_);
  return {processorNode->getGain()};
}

JSI_PROPERTY_SETTER_IMPL(PitchProcessorNodeHostObject, gain) {
  auto processorNode = std::static_pointer_cast<PitchProcessorNode>(node_);
  processorNode->setGain(value.getNumber());
}

} // namespace audioapi
