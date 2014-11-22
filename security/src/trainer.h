#ifndef TRAINER_H
#define TRAINER_H

#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"

#include <boost/filesystem.hpp>
namespace face {

//TODO: trainer identificator
//trainer trainer : input(username)
//
//usage in login manager
//validate
//trainer trainer train -> output face_recognizer with trained elemnts
//face_identificator input: face_recognizer from trainer trainer and output recognize yes or
//no
//
class trainer
{
public:
	bool get_data(std::string user);

	bool set_data();

	bool train(cv::Ptr<cv::FaceRecognizer> trained_recognizer);



private:
};

}

#endif // TRAINER_H
