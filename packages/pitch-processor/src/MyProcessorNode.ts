import { AudioNode, BaseAudioContext } from "react-native-audio-api";
import {
  IAudioNode,
  IBaseAudioContext,
} from "react-native-audio-api/lib/typescript/interfaces";

export interface IMyProcessorNode extends IAudioNode {
  gain: number;
}

export class MyProcessorNode extends AudioNode {
  constructor(context: BaseAudioContext, node: IMyProcessorNode) {
    super(context, node);
  }

  public set gain(value: number) {
    (this.node as IMyProcessorNode).gain = value;
  }

  public get gain(): number {
    return (this.node as IMyProcessorNode).gain;
  }
}

declare global {
  var createCustomProcessorNode: (context: IBaseAudioContext) => IMyProcessorNode;
}
