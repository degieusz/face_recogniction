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
	if (input.empty()) {
		std::cout << "Input object empty\n";
		return false;
	}
	return detect_impl(detected_faces, input);
}

bool recognizer::detect_impl(std::vector<cv::Mat>& detected_faces, cv::Mat& input)
{
	cv::Mat gray_input;
	cv::cvtColor(input, gray_input, CV_BGR2GRAY);

	//cv::equalizeHist(gray_input, gray_input);

	std::vector<cv::Rect> faces;
	cascade.detectMultiScale(gray_input, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(50, 50));

	for(unsigned int i = 0; i < faces.size(); i++ ) {
		cv::Mat detected_face = gray_input(faces[i]);

		cv::resize(detected_face, detected_face, cv::Size(250, 250), 1.0, 1.0, cv::INTER_CUBIC);
		detected_faces.push_back(detected_face);
		//cv::Rect rect_face( faces[i] );
		//cv::rectangle(input, rect_face, cv::Scalar( 120, 5, 86 ), 2, 2, 0  ); //draw rectangle
	}
	return !detected_faces.empty();

}

bool recognizer::recognize(cv::Mat detected_face, cv::Ptr<cv::FaceRecognizer> trained_recognizer)
{
	int label = -1;
	double confidence = -1.0;
	trained_recognizer->predict(detected_face, label, confidence);

	std::cout << "plabel = " << label;
	std::cout << "\n conf" << confidence << "\n";
	return confidence < 4000;
}
}

