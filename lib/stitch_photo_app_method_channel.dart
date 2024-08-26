import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'stitch_photo_app_platform_interface.dart';

/// An implementation of [StitchPhotoAppPlatform] that uses method channels.
class MethodChannelStitchPhotoApp extends StitchPhotoAppPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('stitch_photo_app');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

  @override
  Future<void> setVerticalStitching(
      {required String inputPath, required String inputPath2, required String outputPath, required String line1, required String line2}) async {
    await methodChannel.invokeMethod<void>(
        'verticalStitch', {"inputPath": inputPath, "inputPath2": inputPath2, "outputPath": outputPath, "line1": line1, "line2": line2});
  }
}
