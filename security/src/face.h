#ifndef FACE_H
#define FACE_H

#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"


//TODO: face identificator
//face trainer : input(username)
//
//usage in login manager
//validate
//face trainer train -> output face_recognizer with trained elemnts
//face_identificator input: face_recognizer from face trainer and output recognize yes or
//no
//
class face
{
public:
	bool detect(std::vector<cv::Mat>& detected_faces, cv::Mat& input);

	bool recognize(cv::Mat detected_face);



	bool load_face_cascade();
private:
	cv::CascadeClassifier cascade;
	cv::Mat frame_to_auth;
};

#endif // FACE_H
