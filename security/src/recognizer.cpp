#include "recognizer.h"
#include <string>
#include <iostream>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/contrib/contrib.hpp"
namespace face {

namespace constant {
	const std::string cascade("haarcascade_frontalface_alt.xml");

}

bool recognizer::load_face_cascade()
{
	if (!cascade.load(constant::cascade)) {
		std::cout << "cannot load recognizer cascade:" << constant::cascade << "\n";
		return false;
	}
	return true;
}

bool recognizer::detect(std::vector<cv::Mat>& detected_faces, cv::Mat& input)
{
	cv::Mat gray_input;
	cv::cvtColor(input, gray_input, CV_BGR2GRAY);

	//cv::equalizeHist(gray_input, gray_input);

	std::vector<cv::Rect> faces;
	cascade.detectMultiScale(gray_input, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(50, 50));


	for(unsigned int i = 0; i < faces.size(); i++ ) {
		detected_faces[i] = gray_input(faces[i]);
		//cv::Rect rect_face( faces[i] );
		//cv::rectangle(input, rect_face, cv::Scalar( 120, 5, 86 ), 2, 2, 0  ); //draw rectangle
	}
}

bool recognizer::recognize(cv::Mat detected_face, cv::Ptr<cv::FaceRecognizer> trained_recognizer)
{
	//cv::Mat gray_input;
	//cv::cvtColor(input, gray_input, CV_BGR2GRAY);

	////cv::equalizeHist(gray_input, gray_input);

	//std::vector<cv::Rect> faces;
	//cascade.detectMultiScale(gray_input, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(50, 50));


	//for(unsigned int i = 0; i < faces.size(); i++ ) {
		//detected_faces[i] = gray_input(faces[i]);
		////cv::Rect rect_face( faces[i] );
		////cv::rectangle(input, rect_face, cv::Scalar( 120, 5, 86 ), 2, 2, 0  ); //draw rectangle
		//}
}
}

