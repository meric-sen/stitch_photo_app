import 'package:flutter_test/flutter_test.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';
import 'package:stitch_photo_app/stitch_photo_app.dart';
import 'package:stitch_photo_app/stitch_photo_app_method_channel.dart';
import 'package:stitch_photo_app/stitch_photo_app_platform_interface.dart';

class MockStitchPhotoAppPlatform with MockPlatformInterfaceMixin implements StitchPhotoAppPlatform {
  @override
  Future<String?> getPlatformVersion() => Future.value('42');

  @override
  Future<void> setVerticalStitching(
      {required String inputPath, required String inputPath2, required String outputPath, required String line1, required String line2}) {
    // TODO: implement setVerticalStitching
    throw UnimplementedError();
  }
}

void main() {
  final StitchPhotoAppPlatform initialPlatform = StitchPhotoAppPlatform.instance;

  test('$MethodChannelStitchPhotoApp is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelStitchPhotoApp>());
  });

  test('getPlatformVersion', () async {
    StitchPhotoApp stitchPhotoAppPlugin = StitchPhotoApp();
    MockStitchPhotoAppPlatform fakePlatform = MockStitchPhotoAppPlatform();
    StitchPhotoAppPlatform.instance = fakePlatform;

    expect(await stitchPhotoAppPlugin.getPlatformVersion(), '42');
  });
}
