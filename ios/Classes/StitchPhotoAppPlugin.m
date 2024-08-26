#import "StitchPhotoAppPlugin.h"
#import "vertical_stitch.hpp"
#if __has_include(<stitch_photo_app/stitch_photo_app-Swift.h>)
#import <stitch_photo_app/stitch_photo_app-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "stitch_photo_app-Swift.h"
#endif

@implementation StitchPhotoAppPlugin
- (void)verticalStitchWithInputImagePath1:(NSString *)inputImagePath1 inputImagePath2:(NSString *)inputImagePath2 outputPath:(NSString *)outputPath line1:(NSString *)line1 line2:(NSString *)line2 {
    const char *inputImagePath1CString = [inputImagePath1 cStringUsingEncoding:NSUTF8StringEncoding];
       const char *inputImagePath2CString = [inputImagePath2 cStringUsingEncoding:NSUTF8StringEncoding];
       const char *outputPathCString = [outputPath cStringUsingEncoding:NSUTF8StringEncoding];
       const char *line1CString = [line1 cStringUsingEncoding:NSUTF8StringEncoding];
       const char *line2CString = [line2 cStringUsingEncoding:NSUTF8StringEncoding];
       verticalStitch((char *)inputImagePath1CString, (char *)inputImagePath2CString, (char *)outputPathCString, (char *)line1CString, (char *)line2CString);
}

+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftStitchPhotoAppPlugin registerWithRegistrar:registrar];
}
@end
