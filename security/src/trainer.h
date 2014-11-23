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

namespace constant {
	const std::string main_img_dir(".face_recognizer");
	const unsigned int learned_faces_no = 10;
	const std::string det_face("detected_face");
	const std::string img_ext("jpg");
}

class trainer
{
public:
	typedef std::vector<cv::Mat> img_vec;

	trainer(unsigned int learned_faces_no_ = constant::learned_faces_no);
	bool get_data(std::string user);

	bool set_data();

	bool train(cv::Ptr<cv::FaceRecognizer>&  face_recognizer);



private:
	bool dir_exists(const std::string path);
	bool get_data_impl(std::string user);
	img_vec faces;
	unsigned int learned_faces_no;
};

}

#endif // TRAINER_H
