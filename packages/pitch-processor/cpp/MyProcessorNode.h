#pragma once
#include <audioapi/core/AudioNode.h>

namespace audioapi {
    class BaseAudioContext;
    class AudioBus;

    class MyProcessorNode : public AudioNode {
    public:
      explicit MyProcessorNode(std::shared_ptr<BaseAudioContext> context);
      double getGain() const;
      void setGain(double value);

    protected:
      std::shared_ptr<AudioBus> processNode(const std::shared_ptr<AudioBus> &bus,
                    int framesToProcess) override;

    private:
      double gain; // value responsible for gain value
    };
} // namespace audioapi
