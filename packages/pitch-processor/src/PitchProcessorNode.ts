import { AudioNode, BaseAudioContext } from "react-native-audio-api";
import {
  IAudioNode,
  IBaseAudioContext,
} from "react-native-audio-api/lib/typescript/interfaces";

export interface IPitchProcessorNode extends IAudioNode {
  gain: number;
}

export class PitchProcessorNode extends AudioNode {
  constructor(context: BaseAudioContext, node: IPitchProcessorNode) {
    super(context, node);
  }

  public set gain(value: number) {
    (this.node as IPitchProcessorNode).gain = value;
  }

  public get gain(): number {
    return (this.node as IPitchProcessorNode).gain;
  }
}

declare global {
  var createCustomProcessorNode: (context: IBaseAudioContext) => IPitchProcessorNode;
}
