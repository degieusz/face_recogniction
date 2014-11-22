#include <iostream>

#include <boost/thread/thread.hpp>
#include "face.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
namespace constant {
	const std::string test_img("capture.jpg");
}

	bool load_img_from_path(std::string path, cv::Mat& read_img)
	{
		read_img = cv::imread(path);
		if (!read_img.data) {
			std::cout << "image " << path << " not read.\n";
			return false;
		}

	}

// Main program
int main(int argc, char *argv[])
{
	face fa;
	fa.load_face_cascade();
	cv::Mat capture;
	load_img_from_path(constant::test_img, capture);

	std::vector<cv::Mat> detected_faces(5);

	//detected_faces.empty();

	//capture = cv::imread("capture.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	if (!capture.data) {
		std::cout << "CANNOT load img";
	}

	cv::namedWindow("Display", CV_WINDOW_AUTOSIZE);
	if (fa.detect(detected_faces, capture)) {
		//cv::imshow("Display", detected_faces[0]);
		cv::imshow("Display", detected_faces[0]);
	}
	cv::waitKey(0);
  return 0;
}
