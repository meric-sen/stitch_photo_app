//
//  vertical_stitch.cpp
//  Pods
//
//  Created by Kaan Gumus on 2.02.2023.
//

#include "vertical_stitch.hpp"
#import <opencv2/opencv.hpp>
#include <chrono>

#ifdef __ANDROID__

#include <android/log.h>

#endif

using namespace cv;
using namespace std;

 

cv::Mat output_final;


void platform_log(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
#ifdef __ANDROID__
    __android_log_vprint(ANDROID_LOG_VERBOSE, "FFI Logger: ", fmt, args);
#else
    vprintf(fmt, args);
#endif
    va_end(args);
}

__attribute__((visibility("default"))) __attribute__((used))
const char *getOpenCVVersion() {
    return CV_VERSION;
}


cv::Mat getPerspectiveFromPoints(cv::Mat input,Point2f points[4]){
    
    Point2f inputQuad[4];
    Point2f outputQuad[4];
    cv::Mat output;
    
    Point2f pt_a,pt_b,pt_c,pt_d;
    pt_a = points[0];
    pt_b = points[1];
    pt_c = points[2];
    pt_d = points[3];
   
    float width_ad,width_bc,maxWidth;
    float height_ab,height_cd,maxHeight;

    width_ad = sqrt(pow((pt_a.x-pt_d.x),2)+pow((pt_a.y-pt_d.y),2));
    width_bc = sqrt(pow((pt_b.x-pt_c.x),2)+pow((pt_b.y-pt_c.y),2));
    
    height_ab = sqrt(pow((pt_a.x-pt_b.x),2)+pow((pt_a.y-pt_b.y),2));
    height_cd = sqrt(pow((pt_c.x-pt_d.x),2)+pow((pt_c.y-pt_d.y),2));

    maxWidth = max(width_ad,width_bc);
    maxHeight = max(height_ab,height_cd);

    inputQuad[0] = pt_a;
    inputQuad[1] = pt_b;
    inputQuad[2] = pt_c;
    inputQuad[3] = pt_d;
    // The 4 points where the mapping is to be done , from top-left in clockwise order
    outputQuad[0] = Point2f( 0,0 );
    outputQuad[1] = Point2f( 0,maxHeight-1);
    outputQuad[2] = Point2f( maxWidth-1,maxHeight-1);
    outputQuad[3] = Point2f( maxWidth-1,0  );

    
    cv::Mat lambda = cv::getPerspectiveTransform( inputQuad, outputQuad );
    cv::warpPerspective(input,output,lambda,cv::Size(maxWidth,maxHeight));

    return output;

}



class LineEquation{       // The class
  public:             // Access specifier
    Point2f p1;        // Attribute (int variable)
    Point2f p2;
    float slope;
    
   LineEquation(Point2f p1, Point2f p2) {
       this->p1=p1;
       this->p2=p2;
       this->slope= (this->p2.y-this->p1.y)/(this->p2.x-this->p1.x);
   }
   
   int getX(int y){
       return static_cast<int>(((y-this->p1.y)/this->slope)+this->p1.x);
   }
   
   int getY(int x){
       return static_cast<int>(((x-this->p1.x)*this->slope)+this->p1.y);
   }
};


Point2f * getPerspectivePoints(cv::Mat image,Point2f lineCoor[2]){

    Point2f* points = new Point2f[4];


    int height = image.rows;
    //int width = input.size().width;

    Point2f startPoint,endPoint;
    startPoint = lineCoor[0];
    endPoint = lineCoor[1];

    int avg_row;
    avg_row = (int)((startPoint.y+startPoint.y)/2);

    if((height/2)<avg_row){
        platform_log("if____: %d", 0);
        points[0]=Point2f((int)startPoint.x,0);
        points[1]=Point2f((int)startPoint.x,(int)startPoint.y);
        points[2]=Point2f((int)endPoint.x,(int)endPoint.y);
        points[3]=Point2f((int)endPoint.x,0);
        return points;
    }else{
        platform_log("if___: %d", 1);
        points[0]=Point2f((int)startPoint.x,(int)startPoint.y);
        points[1]=Point2f((int)startPoint.x,(int)height);
        points[2]=Point2f((int)endPoint.x,(int)height);
        points[3]=Point2f((int)endPoint.x,(int)endPoint.y);
        return points;
    }

    
}

cv::Mat imageResizeInterpolation(cv::Mat& img,cv::Size size){
    cv::Mat resizedImage;
    cv::resize(img, resizedImage, size, 0, 0, cv::INTER_CUBIC);
    return resizedImage;
}


void startStitch(cv::Mat img1,cv::Mat img2,std::string outputPath){
    int height1 = img1.size().height;
    int width1 = img1.size().width;
    int height2 = img2.size().height;
    int width2 = img2.size().width;
    cv::Mat result;

    if(width2>=width1){
        cv::Mat new_img1= imageResizeInterpolation(img1,cv::Size(width2,height1));
        cv::vconcat(new_img1,img2,result);
    }else{
        cv::Mat new_img2= imageResizeInterpolation(img2,cv::Size(width1,height2));
        cv::vconcat(img1,new_img2,result);
    }
    cv::imwrite(outputPath, result);
}

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}






__attribute__((visibility("default"))) __attribute__((used))
void verticalStitch(char *inputImagePath,char *inputImagePath2, char *outputPath,char *line_1,char *line_2) {
    platform_log("PATH %s: ", inputImagePath);
    platform_log("PATH %s: ", inputImagePath2);
    
    cv::Mat img1 = cv::imread(inputImagePath);
    platform_log("Length img1: %d", img1.rows);
    cv::Mat img2 = cv::imread(inputImagePath2);
    platform_log("Length img2: %d", img2.rows);
    
    
    string delimiter = ",";
    vector<string> list_line1 = split (line_1, delimiter);
    vector<string> list_line2 = split (line_2, delimiter);

    Point2f line1[2];
    line1[0] = Point2f(std::stof(list_line1[0]),std::stof(list_line1[1]));
    line1[1] = Point2f(std::stof(list_line1[2]),std::stof(list_line1[3]));

    //line1[0]=Point2f(148.0,1632.0);
    //line1[1]=Point2f(2298.0,1638.0);


    Point2f line2[2];

    line2[0] = Point2f(std::stof(list_line2[0]),std::stof(list_line2[1]));
    line2[1] = Point2f(std::stof(list_line2[2]),std::stof(list_line2[3]));

    //line2[0]=Point2f(168.0,78.0);
    //line2[1]=Point2f(2277.0,93.0);

    Point2f *perspectivePoints1,*perspectivePoints2;
    cv::Mat perspective_image1,perspective_image2;


    perspectivePoints1 = getPerspectivePoints(img1,line1);

   
    platform_log("PerspectivePoints2: %d", (int)perspectivePoints1[2].x);
    platform_log("PerspectivePoints2: %d", (int)perspectivePoints1[2].y);

    perspectivePoints2 = getPerspectivePoints(img2,line2);

    perspective_image1= getPerspectiveFromPoints(img1,perspectivePoints1);

    perspective_image2= getPerspectiveFromPoints(img2,perspectivePoints2);


    startStitch(perspective_image1,perspective_image2,outputPath);
}


