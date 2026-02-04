# pitch-processor

Custom pitch processor TurboModule built on top of `react-native-audio-api`.

This package is designed to work with Expo development builds and EAS. Native changes are applied via the config plugin on Android, so you should not have to manually edit `android/` unless you are intentionally bypassing Expo’s plugin system.

## Install (Expo / EAS)

```
npm install pitch-processor react-native-audio-api
```

Add the plugins to `app.json` (order matters):

```
"plugins": [
  "react-native-audio-api",
  "pitch-processor"
]
```

Ensure the New Architecture is enabled in `app.json`:

```
"newArchEnabled": true
```

Then rebuild your dev client (required any time native code or plugins change):

```
eas build --profile development --platform android
```

Install the new dev client and run the app.


## Usage

```
import { AudioContext } from "react-native-audio-api";
import { MyProcessorNode, NativeAudioProcessingModule } from "pitch-processor";

NativeAudioProcessingModule.injectCustomProcessorInstaller();
const audioContext = new AudioContext();
const processor = new MyProcessorNode(
  audioContext,
  global.createCustomProcessorNode(audioContext.context)
);
```

## What The Plugin Does (Android)

The Expo config plugin injects Gradle logic into `android/app/build.gradle` that enforces build order:

1. `react-native-audio-api` native libs must be built first.
2. This package’s codegen must run before app CMake compiles.

This prevents missing `.so` files and missing codegen headers when the CMake step runs.

## Troubleshooting (Read This First)

Most failures are build order or plugin application issues. Do not start by editing native code.

### 1) “Failed to install react-native-audio-api: native module not found”
This means the app binary does not include native modules. Common causes:
- Running in Expo Go instead of a dev client.
- Not rebuilding the dev client after adding native deps or changing plugins.

Fix: rebuild the dev client with EAS and reinstall.

### 2) Missing `.so` or CMake errors (Android)
This usually means `react-native-audio-api` did not build before this package’s CMake step.

What to check:
- `app.json` has `"react-native-audio-api"` before `"pitch-processor"` in `plugins`.
- The plugin injected build order logic in `android/app/build.gradle`.
- You rebuilt the dev client after changes.

If you are not using Expo, add the build-order snippet manually (below).

### 3) Codegen header include errors (e.g. missing `pitchprocessorJSI.h`)
This means codegen didn’t run before CMake.

What to check:
- Plugin applied.
- Clean rebuild after codegen changes.

### 4) iOS build errors about missing `pitchprocessor.h`
This means iOS codegen output wasn’t generated or headers aren’t on the search path.

What to check:
- You rebuilt the dev client (EAS or local) after native changes.
- The podspec is present (`pitch-processor.podspec`) and autolinking is enabled.
- Clean the iOS build folder and rebuild.

## Manual Android Setup (No Expo)

If you are not using Expo plugins, add this to your app’s `android/app/build.gradle`:

```
// pitch-processor audio-api deps
evaluationDependsOn(":react-native-audio-api")
evaluationDependsOn(":pitch-processor")

afterEvaluate {
  def audioApiProject = findProject(":react-native-audio-api")
  if (audioApiProject != null) {
    def mergeDebug = audioApiProject.tasks.findByName("mergeDebugNativeLibs")
    def mergeRelease = audioApiProject.tasks.findByName("mergeReleaseNativeLibs")

    def buildCMakeDebug = tasks.findByName("buildCMakeDebug")
    if (buildCMakeDebug != null && mergeDebug != null) {
      buildCMakeDebug.dependsOn(mergeDebug)
    }

    def buildCMakeRelWithDebInfo = tasks.findByName("buildCMakeRelWithDebInfo")
    if (buildCMakeRelWithDebInfo != null && mergeRelease != null) {
      buildCMakeRelWithDebInfo.dependsOn(mergeRelease)
    }

    def buildCMakeRelease = tasks.findByName("buildCMakeRelease")
    if (buildCMakeRelease != null && mergeRelease != null) {
      buildCMakeRelease.dependsOn(mergeRelease)
    }
  }

  def pitchProcessorProject = findProject(":pitch-processor")
  if (pitchProcessorProject != null) {
    def codegenTask = pitchProcessorProject.tasks.findByName("generateCodegenArtifactsFromSchema")
    if (codegenTask != null) {
      def buildCMakeDebug = tasks.findByName("buildCMakeDebug")
      if (buildCMakeDebug != null) {
        buildCMakeDebug.dependsOn(codegenTask)
      }

      def buildCMakeRelWithDebInfo = tasks.findByName("buildCMakeRelWithDebInfo")
      if (buildCMakeRelWithDebInfo != null) {
        buildCMakeRelWithDebInfo.dependsOn(codegenTask)
      }

      def buildCMakeRelease = tasks.findByName("buildCMakeRelease")
      if (buildCMakeRelease != null) {
        buildCMakeRelease.dependsOn(codegenTask)
      }
    }
  }
}
```

## C++ Integration

The native C++ sources live in `shared/` and are built via:

- Android: `android/CMakeLists.txt`

Both platforms compile the same shared C++ sources.
