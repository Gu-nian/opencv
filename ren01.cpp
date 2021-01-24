#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/types_c.h>
#include<iostream>
#include<math.h>
#include<sstream>
using namespace cv;
using namespace std;

#define Focal 435.675
#define Big 42
#define Small 17
#define Height 200
#define Transformation 25.4

int main()
{
    Mat img,mid,dst,dst1,dst2,all_dst;
    size_t count,count1,count2;

    vector<vector<Point>> contours;
    Rect re;
    double end;

    vector<vector<Point>> contours1;
    Rect re1;
    double end1;

    vector<vector<Point>> contours2;
    Rect re2;
    double end2;

    String text;
    String text1;
    String text2;

    img = imread("1.jpg");
    all_dst = Mat(600,600,img.type());
    cvtColor(img,mid,CV_BGR2HSV);
    inRange(mid,Scalar(162,64,53),Scalar(180,255,255),dst);//hong
    inRange(mid,Scalar(0,0,150),Scalar(180,62,222),dst1);//bai
    inRange(mid,Scalar(16,44,116),Scalar(27,252,254),dst2);//huang


    findContours(dst,contours,RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    findContours(dst1,contours1,RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    findContours(dst2,contours2,RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    count = contours.size();
    count1 = contours1.size();
    count2 = contours2.size();

    for(auto i=0;i<MAX(count,MAX(count1,count2));i++)
    {
        if(i<contours.size())
        {
            re = boundingRect(contours[i]);
            if(re.width*re.height>80000)
            {
                end = ((Big*Focal)/((MAX(re.height,re.width)/Focal)*Transformation)+(tan(CV_PI/6)*Height));
                drawContours(img,contours,i,Scalar(0,0,255),50);
                rectangle(img,re,Scalar(255),30);
                circle(all_dst,Point((600*re.x/img.cols+600*re.br().x/img.cols)/2,600-end),(600*re.width/img.rows)/2,Scalar(255),3);
                text = to_string(end/10);
                putText(img,text,Point(re.x,re.y-100),FONT_HERSHEY_SIMPLEX,10,Scalar(0,255,0),30);
            }
        }
         if(i<contours1.size())
        {
            re1 = boundingRect(contours1[i]);
            if(re1.width*re1.height>30000&&re1.width*re1.height<1000000)
            {
                end1 = ((Small*Focal)/((MAX(re1.width,re1.height)/Focal)*Transformation)+(tan(CV_PI/6)*Height));
                drawContours(img,contours1,i,Scalar(0,0,255),50);
                rectangle(img,re1,Scalar(255),30);
                circle(all_dst,Point((600*re1.x/img.cols+600*re1.br().x/img.cols)/2,600-end1),(600*re1.width/img.rows)/2,Scalar(255),-1);
                text1 = to_string(end1/10);
                putText(img,text1,Point(re1.x,re1.y-100),FONT_HERSHEY_SIMPLEX,10,Scalar(0,255,0),30);
            }
        }
         if(i<contours2.size())
        {
            re2 = boundingRect(contours2[i]);
            if(re2.width*re2.height>1000000)
            {
                end2 = ((Big*Focal)/((MAX(re2.width,re2.height)/Focal)*Transformation)+(tan(CV_PI/6)*Height));
                drawContours(img,contours2,i,Scalar(0,0,255),50);
                rectangle(img,re2,Scalar(255),30);
                circle(all_dst,Point((600*re2.x/img.cols+600*re2.br().x/img.cols)/2,600-end2),(600*re2.width/img.rows)/2,Scalar(255),3);
                text2 = to_string(end2/10);
                putText(img,text2,Point(re2.x,re2.y-100),FONT_HERSHEY_SIMPLEX,10,Scalar(0,255,0),30);
            }
        }
    }

//    for(auto i=0;i<contours1.size();i++)
//    {
//        re1 = boundingRect(contours1[i]);
//        if(re1.width*re1.height>30000&&re1.width*re1.height<1000000)
//        {
//            end1 = ((Small*Focal)/((MAX(re1.width,re1.height)/Focal)*Transformation)+(tan(CV_PI/6)*Height));
//            drawContours(img,contours1,i,Scalar(0,0,255),50);
//            rectangle(img,re1,Scalar(255),30);
//            circle(all_dst,Point((600*re1.x/img.cols+600*re1.br().x/img.cols)/2,600-end1),(600*re1.width/img.rows)/2,Scalar(255),-1);
//            text1 = to_string(end1/10);
//            putText(img,text1,Point(re1.x,re1.y-100),FONT_HERSHEY_SIMPLEX,10,Scalar(0,255,0),30);
//        }
//    }

//    for(auto i=0;i<contours2.size();i++)
//    {
//        re2 = boundingRect(contours2[i]);
//        if(re2.width*re2.height>1000000)
//        {
//            end2 = ((Big*Focal)/((MAX(re2.width,re2.height)/Focal)*Transformation)+(tan(CV_PI/6)*Height));
//            drawContours(img,contours2,i,Scalar(0,0,255),50);
//            rectangle(img,re2,Scalar(255),30);
//            circle(all_dst,Point((600*re2.x/img.cols+600*re2.br().x/img.cols)/2,600-end2),(600*re2.width/img.rows)/2,Scalar(255),3);
//            text2 = to_string(end2/10);
//            putText(img,text2,Point(re2.x,re2.y-100),FONT_HERSHEY_SIMPLEX,10,Scalar(0,255,0),30);
//        }
//    }



    namedWindow("dst",0);
    imshow("dst",all_dst);

    namedWindow("img",0);
    imshow("img",img);
    waitKey();



}
