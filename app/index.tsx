import React from "react";
import { Button, View } from "react-native";
import { AudioContext, AudioManager } from "react-native-audio-api";
import {
  PitchProcessorNode,
  NativeAudioProcessingModule,
} from "pitch-processor";

export default function App() {
  const audioContextRef = React.useRef<AudioContext | null>(null);
  const processorRef = React.useRef<PitchProcessorNode | null>(null);
  const [gain, setGain] = React.useState(0.5);

  const handlePlay = async () => {
    NativeAudioProcessingModule.injectCustomProcessorInstaller();
    await AudioManager.setAudioSessionActivity(true);
    const preferredSampleRate = AudioManager.getDevicePreferredSampleRate();
    const audioContext = new AudioContext({
      sampleRate: preferredSampleRate > 0 ? preferredSampleRate : 48000,
    });
    audioContextRef.current = audioContext;

    const audioBuffer = await fetch(
      "https://software-mansion.github.io/react-native-audio-api/audio/music/example-music-01.mp3",
    )
      .then((response) => response.arrayBuffer())
      .then((arrayBuffer) => audioContext.decodeAudioData(arrayBuffer));

    const playerNode = audioContext.createBufferSource();
    playerNode.buffer = audioBuffer;

    const processor = new PitchProcessorNode(
      audioContext,
      global.createCustomProcessorNode(audioContext.context),
    );
    processor.gain = gain;
    processorRef.current = processor;

    playerNode.connect(processor);
    processor.connect(audioContext.destination);
    playerNode.start(audioContext.currentTime);
  };

  const adjustGain = (delta: number) => {
    const nextGain = Math.max(0, Math.min(2, gain + delta));
    setGain(nextGain);
    if (processorRef.current) {
      processorRef.current.gain = nextGain;
    }
  };

  return (
    <View style={{ flex: 1, justifyContent: "center", alignItems: "center" }}>
      <Button onPress={handlePlay} title="Play sound!" />
      <View style={{ height: 16 }} />
      <Button onPress={() => adjustGain(-0.1)} title="Gain -" />
      <View style={{ height: 8 }} />
      <Button onPress={() => adjustGain(0.1)} title="Gain +" />
    </View>
  );
}
