#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	VideoCapture capture(0);

	namedWindow("pretreated", 0);

	Mat original,midImage;
	vector<Vec3f> circles;

	while (1){
		capture >> original;
		cvtColor(original, midImage, CV_BGR2GRAY);
		GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
		HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 180, 70, 0, 0);
		for (size_t i = 0; i < circles.size(); ++i){
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			circle(original, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			circle(original, center, radius, Scalar(155, 50, 255), 3, 8, 0);
		}
		imshow("pretreated", original);
		
		char key;
		int i = 0;
		if (key = waitKey(30)>=0) break;
		switch (key){
		case 's':
			i++;
			string filename = format("E:\\EnglishLocate\\BianCheng\\PRACTISE\\opencv_findPingPong\\opencv_findPingPong\\%d.jpg", i);
			imwrite(filename, original);
			
		}
	}
}