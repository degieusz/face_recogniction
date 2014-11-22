#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "opencv2/contrib/contrib.hpp"
namespace face {

//TODO: recognizer identificator
//recognizer trainer : input(username)
//
//usage in login manager
//validate
//recognizer trainer train -> output face_recognizer with trained elemnts
//face_identificator input: face_recognizer from recognizer trainer and output recognize yes or
//no
//
class recognizer
{
public:
	bool detect(std::vector<cv::Mat>& detected_faces, cv::Mat& input);

	bool recognize(cv::Mat detected_face, cv::Ptr<cv::FaceRecognizer> trained_recognizer);



	bool load_face_cascade();
private:
	cv::CascadeClassifier cascade;
	cv::Mat frame_to_auth;
};

}

#endif // RECOGNIZER_H
