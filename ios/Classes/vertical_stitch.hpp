//
//  vertical_stitch.hpp
//  Pods
//
//  Created by Kaan Gumus on 2.02.2023.
//
/*
#ifndef vertical_stitch_hpp
#define vertical_stitch_hpp

#include <stdio.h>

class VerticalStitirchstitchPhotoApp {
public:
    void verticalStitch(char *inputImagePath,char *inputImagePath2, char *outputPath,char *line_1,char *line_2);
}; */
// #endif /* vertical_stitch_hpp */

#ifndef vertical_stitch_h
#define vertical_stitch_h

#ifdef __cplusplus
extern "C"
{
#endif

    void verticalStitch(char *inputImagePath, char *inputImagePath2, char *outputPath, char *line_1, char *line_2);

#ifdef __cplusplus
}
#endif

#endif /* vertical_stitch_h */
