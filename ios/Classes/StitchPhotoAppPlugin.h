#import <Flutter/Flutter.h>

@interface StitchPhotoAppPlugin : NSObject <FlutterPlugin>
- (void)verticalStitchWithInputImagePath1:(NSString *)inputImagePath1 inputImagePath2:(NSString *)inputImagePath2 outputPath:(NSString *)outputPath line1:(NSString *)line1 line2:(NSString *)line2;
@end
