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

TEST_F(recognizer_test, ut_recognize_ok)
{
	std::vector<cv::Mat> learned_faces;
	int learned_face_no = 0;
	for (; learned_face_no < 10 ; ++learned_face_no) {
		std::ostringstream oss;
		oss << learned_face_no;
		learned_faces.push_back(cv::imread("../data/1/detected_face" + oss.str() + ".jpg"));
	}

	std::vector<cv::Mat>::iterator it;
	for (it = learned_faces.begin(); it != learned_faces.end(); ++it) {
		cv::cvtColor(*it, *it, CV_BGR2GRAY);
	}

	cv::Ptr<cv::FaceRecognizer> trained_cv_recognizer = cv::createEigenFaceRecognizer();
	std::vector<int> labels(10, 1);
	trained_cv_recognizer->train(learned_faces, labels);


	for(unsigned int i = 1; i < 9; ++i) {
		std::ostringstream oss;
		oss << i;
	cv::Mat capture2;
	load_img_from_path("../data/3/detected_face" + oss.str() +".jpg", capture2);
	cv::Mat gray_input2;
	cv::cvtColor(capture2, gray_input2,  CV_BGR2GRAY);

	EXPECT_FALSE(recognizer_.recognize(gray_input2, trained_cv_recognizer));
	}

	for(unsigned int i = 1; i < 9; ++i) {
		std::ostringstream oss;
		oss << i;
	cv::Mat capture2;
	load_img_from_path("../data/2/detected_face" + oss.str() +".jpg", capture2);
	cv::Mat gray_input2;
	cv::cvtColor(capture2, gray_input2,  CV_BGR2GRAY);

	EXPECT_TRUE(recognizer_.recognize(gray_input2, trained_cv_recognizer));
	}
}

TEST_F(recognizer_test, mt_recognize_ok)
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



	cv::Mat capture2;
	load_img_from_path("../data/3/detected_face1.jpg", capture2);
	//cv::namedWindow("Display", CV_WINDOW_AUTOSIZE);
	//cv::imshow("Display", capture2);
	//cv::waitKey(0);
	cv::Mat gray_input2;
	cv::cvtColor(capture2, gray_input2,  CV_BGR2GRAY);

	recognizer_.recognize(gray_input2, trained_cv_recognizer);
	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}

}
