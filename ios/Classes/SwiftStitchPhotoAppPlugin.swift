import Flutter
import UIKit

public class SwiftStitchPhotoAppPlugin: NSObject, FlutterPlugin {
  public static func register(with registrar: FlutterPluginRegistrar) {
    let channel = FlutterMethodChannel(name: "stitch_photo_app", binaryMessenger: registrar.messenger())
    let instance = SwiftStitchPhotoAppPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
      if call.method.elementsEqual("verticalStitch"){
          let stitchPhotoAppOpencvPlugin = StitchPhotoAppPlugin()
          let arguments :  NSDictionary = call.arguments as! NSDictionary
          stitchPhotoAppOpencvPlugin.verticalStitch(withInputImagePath1: arguments["inputPath"] as? String, inputImagePath2:(arguments["inputPath2"] as? String), outputPath:arguments["outputPath"] as? String, line1:arguments["line1"] as? String, line2:arguments["line2"] as? String)
      }
    result("iOS " + UIDevice.current.systemVersion)
  }
}
