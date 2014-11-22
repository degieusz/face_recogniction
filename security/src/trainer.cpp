#include "trainer.h"
#include <string>
#include <iostream>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"

#include <boost/filesystem.hpp>
namespace face {

namespace constant {
	const std::string data_dir(".face_recognizer");

}
namespace os = boost::filesystem;

bool trainer::get_data(std::string user)
{
	if (!os::exists(constant::data_dir)) {
		std::cout << "no data available";
		return false;
	}
	else {
		if (!os::is_directory(constant::data_dir)) {
			std::cout << constant::data_dir <<
			 " is not a directory. Delete the file and restart application.";
			 return false;
		}
		else {
			//get_data_impl();
		}
	}
	return true;
}

bool trainer::train(cv::Ptr<cv::FaceRecognizer> trained_recognizer)
{
	return true;
}

}

