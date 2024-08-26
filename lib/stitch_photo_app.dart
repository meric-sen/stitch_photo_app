import 'stitch_photo_app_platform_interface.dart';

class StitchPhotoApp {
  Future<String?> getPlatformVersion() {
    return StitchPhotoAppPlatform.instance.getPlatformVersion();
  }

  Future<void> setVerticalStitching(
      {required String inputPath, required String inputPath2, required String outputPath, required String line1, required String line2}) {
    return StitchPhotoAppPlatform.instance
        .setVerticalStitching(inputPath: inputPath, inputPath2: inputPath2, outputPath: outputPath, line1: line1, line2: line2);
  }
}
