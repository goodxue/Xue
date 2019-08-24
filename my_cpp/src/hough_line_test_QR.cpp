#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {
    Mat src,dst,hsv,copy,out;
    src = imread("/home/xue/Desktop/Untitled/5.png");
    namedWindow("src",0);
    namedWindow("plines",0);
    imshow("src",src);
    int range_hsv[6]={1,2,3,4,5,6};
    namedWindow("dst",0);
    createTrackbar("H1:","src",&range_hsv[0],180,0,0);
    createTrackbar("S1:","src",&range_hsv[1],255,0,0);
    createTrackbar("V1:","src",&range_hsv[2],255,0,0);
    createTrackbar("H2:","src",&range_hsv[3],180,0,0);
    createTrackbar("S2:","src",&range_hsv[4],255,0,0);
    createTrackbar("V2:","src",&range_hsv[5],255,0,0);

    std::cout<<"waiting for you to press \'q\' to quite..."<<std::endl;
    char aim = 'q',key = ' ';

    while(1){
        copy = src.clone();
        cv::cvtColor(src,hsv,CV_BGR2GRAY);

        cv::threshold(hsv,dst,range_hsv[1],255,CV_THRESH_BINARY);
        // cvtColor(dst,hsv,cv::COLOR_BGR2HSV);
        // cv::inRange(hsv,cv::Scalar(range_hsv[0],range_hsv[1],range_hsv[2]),cv::Scalar(range_hsv[3],range_hsv[4],range_hsv[5]),dst);
        imshow("dst",dst);

        std::vector<std::vector<cv::Point> > contours;
        std::vector<Vec4i> hierarchy;
        std::vector<cv::Point> big_counter;

        for (int i = 0; i < contours.size();i++) {
            for (int j = 0;j < contours[i].size();j++){
                big_counter.push_back(contours[i][j]);
            }
        }
        RotatedRect mr = minAreaRect(big_counter);

        Mat DrawImg(src.size(), src.type(), Scalar(255, 255, 255));
        Point2f vectpoint[4];
        mr.points(vectpoint);
        for (int i = 0; i<4; i++)
        {
            line(DrawImg, vectpoint[i], vectpoint[(i + 1) % 4], Scalar(255, 0, 0), 2);
        }
    
        imshow("drawimg", DrawImg);
        waitKey();
        float angle = 0.0;
        Size si = mr.size;
        if (mr.size.width <= mr.size.height)
        {
            angle = mr.angle + 90;
            int tm = si.width;
            si.width = si.height;
            si.height = tm;
            //swap(si.width, si.height);
        }
        else
        {
            angle = mr.angle;
        }
        Mat rotmat = getRotationMatrix2D(mr.center, angle, 1);
        Mat deal_img;
        warpAffine(copy, deal_img, rotmat, copy.size(), CV_INTER_CUBIC);


        cv::findContours(dst, contours, hierarchy,cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        int idx = 0;
        for( ; idx >= 0; idx = hierarchy[idx][0] )
        {
            Scalar color( 0,255,0 );
            drawContours( copy, contours, idx, color, CV_FILLED, 8, hierarchy );
        }

        // std::vector<Vec4f> plines;
        // HoughLinesP(dst,plines,1,CV_PI / 180,10,0,10);

        // for (int i = 0;i < plines.size();i++){
        //     Vec4f line = plines[i];
        //     cv::line(copy,Point(line[0],line[1]),Point(line[2],line[3]),Scalar(0,0,255),1);
        // }
        imshow("plines",copy);
        waitKey(1);
    }
    return 0;
}