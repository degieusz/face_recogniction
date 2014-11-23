#include "recognizer.h"
#include <gtest/gtest.h>
#include <fstream>

#include <boost/filesystem.hpp>

#include "trainer.h"
namespace face {

namespace os = boost::filesystem;
namespace constant {
	const std::string test_img("capture.jpg");
	const std::string user("user");
	const std::string test_data_dir("../data");
}

class recognizer_test : public testing::Test {
public:
	recognizer recognizer_;

	bool load_img_from_path(std::string path, cv::Mat& read_img)
	{
		read_img = cv::imread(path);
		if (!read_img.data) {
			std::cout << "image " << path << " not read.\n";
			return false;
		}
	}
};

TEST_F(recognizer_test, detect)
{
	EXPECT_TRUE(recognizer_.load_face_cascade());
	cv::Mat capture;
	load_img_from_path(constant::test_img, capture);

	std::vector<cv::Mat> detected_faces;
	EXPECT_TRUE(recognizer_.detect(detected_faces, capture));
	//cv::namedWindow("Display", CV_WINDOW_AUTOSIZE);
	//cv::imshow("Display", detected_faces[0]);
	//cv::waitKey(0);
	EXPECT_FALSE(detected_faces.empty());
}

TEST_F(recognizer_test, recognize_ok)
{
	EXPECT_TRUE(recognizer_.load_face_cascade());
	cv::Mat capture;
	load_img_from_path(constant::test_img, capture);

	std::vector<cv::Mat> detected_faces;
	EXPECT_TRUE(recognizer_.detect(detected_faces, capture));
	//cv::namedWindow("Display", CV_WINDOW_AUTOSIZE);
	//cv::imshow("Display", detected_faces[0]);
	//cv::waitKey(0);
	EXPECT_FALSE(detected_faces.empty());



	const std::string user_dir(constant::main_img_dir + "/" + constant::user);
	ASSERT_TRUE(os::create_directories(user_dir));

	for (unsigned int i = 0; i < constant::learned_faces_no; ++i) {
		std::ostringstream oss;
		oss << i;
		const std::string img_file_name(constant::det_face + oss.str() + "." + constant::img_ext);
		const std::string img_in(constant::test_data_dir + "/" + img_file_name);
		const std::string img_out(user_dir + "/" +  img_file_name);
		os::copy(img_in, img_out);
	}

	trainer t;
	EXPECT_TRUE(t.get_data(constant::user));
	cv::Ptr<cv::FaceRecognizer> trained_cv_recognizer;
	EXPECT_TRUE(trained_cv_recognizer.empty());
	EXPECT_TRUE(t.train(trained_cv_recognizer));
	EXPECT_FALSE(trained_cv_recognizer.empty());



	recognizer_.recognize(detected_faces[0], trained_cv_recognizer);
	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}

}
