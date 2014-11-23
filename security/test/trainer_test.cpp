#include <gtest/gtest.h>
#include <boost/thread/thread.hpp>
#include <boost/filesystem.hpp>
#include <fstream>

//INFO: testing purposes. I believe in ut it is not bad:)
#define private public
#include "trainer.h"
namespace face {

namespace os = boost::filesystem;

namespace constant {
	const std::string user("user");
	const std::string user2("user2");
	const std::string test_data_dir("../data");
}

class trainer_test : public testing::Test
{
public:
	trainer t;
};

TEST_F(trainer_test, get_data_no_dir_nok)
{
	EXPECT_FALSE(t.get_data(constant::user));
}

TEST_F(trainer_test, get_data_no_main_dir_nok)
{
	ASSERT_TRUE(os::create_directory(constant::main_img_dir));
	EXPECT_FALSE(t.get_data(constant::user));

	ASSERT_TRUE(os::remove(constant::main_img_dir));
}

TEST_F(trainer_test, get_data_no_images)
{
	ASSERT_TRUE(os::create_directories(constant::main_img_dir + "/" + constant::user));
	EXPECT_FALSE(t.get_data(constant::user));

	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}

TEST_F(trainer_test, get_data_not_all_images_nok)
{
	const std::string user_dir(constant::main_img_dir + "/" + constant::user);
	ASSERT_TRUE(os::create_directories(user_dir));

	for (unsigned int i = 0; i < constant::learned_faces_no - 1; ++i) {
		std::ostringstream oss;
		oss << i;
		const std::string img_file_name(constant::det_face + oss.str() + "." + constant::img_ext);
		const std::string img_in(constant::test_data_dir + "/" + img_file_name);
		const std::string img_out(user_dir + "/" +  img_file_name);
		os::copy(img_in, img_out);
	}

	EXPECT_FALSE(t.get_data(constant::user));

	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}

TEST_F(trainer_test, get_data_images_ok)
{
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

	EXPECT_TRUE(t.get_data(constant::user));

	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}

TEST_F(trainer_test, train_no_faces_nok)
{
	cv::Ptr<cv::FaceRecognizer> face_recognizer;
	EXPECT_FALSE(t.train(face_recognizer));
}

TEST_F(trainer_test, train_faces_ok)
{
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

	EXPECT_TRUE(t.get_data(constant::user));
	cv::Ptr<cv::FaceRecognizer> face_recognizer;
	EXPECT_TRUE(face_recognizer.empty());
	EXPECT_TRUE(t.train(face_recognizer));
	EXPECT_FALSE(face_recognizer.empty());

	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}

TEST_F(trainer_test, prepare_data_output_dir_exists_nok)
{
	const std::string user_dir(constant::main_img_dir + "/" + constant::user);
	ASSERT_TRUE(os::create_directories(user_dir));

	trainer::img_vec captured_faces;
	EXPECT_FALSE(t.prepare_data(constant::user, captured_faces));

	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}

TEST_F(trainer_test, prepare_data_empty_input_container)
{
	trainer::img_vec captured_faces;

	EXPECT_FALSE(t.prepare_data(constant::user, captured_faces));
}

TEST_F(trainer_test, prepare_data_ok)
{
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

	EXPECT_TRUE(t.get_data(constant::user));
	trainer trainer;
	trainer.prepare_data(constant::user2, t.faces);

	const std::string user2_dir(constant::main_img_dir + "/" + constant::user2);
	for (unsigned int i = 0; i < constant::learned_faces_no; ++i) {
		std::ostringstream oss;
		oss << i;
		const std::string img_file_name(constant::det_face + oss.str() + "." + constant::img_ext);
		const std::string img_out(user2_dir + "/" +  img_file_name);
		EXPECT_TRUE(os::exists(img_out));
	}

	ASSERT_TRUE(os::remove_all(constant::main_img_dir));
}


}
