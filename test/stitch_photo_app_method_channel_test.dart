import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:stitch_photo_app/stitch_photo_app_method_channel.dart';

void main() {
  MethodChannelStitchPhotoApp platform = MethodChannelStitchPhotoApp();
  const MethodChannel channel = MethodChannel('stitch_photo_app');

  TestWidgetsFlutterBinding.ensureInitialized();

  setUp(() {
    channel.setMockMethodCallHandler((MethodCall methodCall) async {
      return '42';
    });
  });

  tearDown(() {
    channel.setMockMethodCallHandler(null);
  });

  test('getPlatformVersion', () async {
    expect(await platform.getPlatformVersion(), '42');
  });
}
