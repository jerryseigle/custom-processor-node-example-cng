#include "PitchProcessorNode.h"
#include <audioapi/core/BaseAudioContext.h>
#include <audioapi/utils/AudioBus.h>
#include <audioapi/utils/AudioArray.h>

namespace audioapi {
    PitchProcessorNode::PitchProcessorNode(std::shared_ptr<BaseAudioContext> context)
        : AudioNode(std::move(context)), gain(0.5) {
        isInitialized_ = true;
    }

    double PitchProcessorNode::getGain() const {
      return gain;
    }

    void PitchProcessorNode::setGain(double value) {
      gain = value;
    }

    std::shared_ptr<AudioBus> PitchProcessorNode::processNode(const std::shared_ptr<AudioBus> &bus,
                                    int framesToProcess) {
      for (int channel = 0; channel < bus->getNumberOfChannels(); ++channel) {
        auto *audioArray = bus->getChannel(channel);
        for (size_t i = 0; i < framesToProcess; ++i) {
          // Apply gain to each sample in the audio array
          (*audioArray)[i] *= gain;
        }
      }
      return bus;
    }
} // namespace audioapi
