import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'stitch_photo_app_method_channel.dart';

abstract class StitchPhotoAppPlatform extends PlatformInterface {
  /// Constructs a StitchPhotoAppPlatform.
  StitchPhotoAppPlatform() : super(token: _token);

  static final Object _token = Object();

  static StitchPhotoAppPlatform _instance = MethodChannelStitchPhotoApp();

  /// The default instance of [StitchPhotoAppPlatform] to use.
  ///
  /// Defaults to [MethodChannelStitchPhotoApp].
  static StitchPhotoAppPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [StitchPhotoAppPlatform] when
  /// they register themselves.
  static set instance(StitchPhotoAppPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  Future<void> setVerticalStitching(
      {required String inputPath, required String inputPath2, required String outputPath, required String line1, required String line2}) {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
