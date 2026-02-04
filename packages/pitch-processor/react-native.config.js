module.exports = {
  dependency: {
    platforms: {
      android: {
        cmakeListsPath: "CMakeLists.txt",
        cxxModuleHeaderName: "NativeAudioProcessingModule",
      },
      ios: {
        podspecPath: "pitch-processor.podspec",
      },
    },
  },
};
