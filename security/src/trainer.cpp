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
#include <sstream>
namespace face {

namespace os = boost::filesystem;

trainer::trainer(unsigned int learned_faces_no_):
  learned_faces_no(learned_faces_no_)
{ }

bool trainer::get_data(std::string user)
{
	if (!dir_exists(constant::main_img_dir)) {
		return false;
	}

	return get_data_impl(user);
}

bool trainer::get_data_impl(std::string user)
{
	const std::string user_data_path(constant::main_img_dir + "/" + user + "/");
	if (!dir_exists(user_data_path)) {
		return false;
	}

	bool all_loaded = true;
	for (unsigned int i = 0; i < learned_faces_no; ++i) {
		std::ostringstream oss;
		oss << i;
		std::string img_path(user_data_path + constant::det_face + oss.str() + "." + constant::img_ext);
		if (os::exists(img_path)) {
			faces.push_back(cv::imread(img_path));
		}
		else {
			std::cout << "Cannot load image " << img_path << " for training purposes.\n";
			all_loaded = false;
		}
	}
	return all_loaded;
}

bool trainer::dir_exists(const std::string path)
{
	if (!os::exists(path) || !os::is_directory(path)) {
		std::cout << "Cannot find directory " << path << "\n";
		return false;
	}
	return true;
}

// INFO: if face_recognizer is not pass by ref,  ptr object is empty when it should not be-
//  what kind of ptr is that?
bool trainer::train(cv::Ptr<cv::FaceRecognizer>& face_recognizer)
{
	if (faces.size() != learned_faces_no) {
		std::cout << "No faces prepared for training.\n";
		return false;
	}

	face_recognizer = cv::createEigenFaceRecognizer();
	std::vector<int> labels(learned_faces_no, 1);
	face_recognizer->train(faces, labels);
	return true;
}

}

