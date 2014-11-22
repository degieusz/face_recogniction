#include "face.h"
#include <gtest/gtest.h>
#include <boost/thread/thread.hpp>

namespace constant {
	const std::string test_img("capture.jpg");
}

class face_auth_test : public testing::Test {
public:
	face fa;

	bool load_img_from_path(std::string path, cv::Mat& read_img)
	{
		read_img = cv::imread(path);
		if (!read_img.data) {
			std::cout << "image " << path << " not read.\n";
			return false;
		}

	}
	boost::mutex mutex_;

};

TEST_F(face_auth_test, add)
{
	EXPECT_TRUE(fa.load_face_cascade());
	cv::Mat capture;
	load_img_from_path(constant::test_img, capture);

	std::vector<cv::Mat> detected_faces;
	EXPECT_TRUE(fa.detect(detected_faces, capture));
	EXPECT_FALSE(detected_faces.empty());
}

//TEST_F(face_auth_test, add_erase)
//{
	//EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_password));
	//EXPECT_TRUE(lm.remove(constant::user, constant::password, constant::root_password));
	//EXPECT_FALSE(lm.remove(constant::user, constant::password, constant::root_password));
//}

//TEST_F(face_auth_test, add_validate)
//{
	//EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_password));
	//EXPECT_TRUE(lm.validate(constant::user, constant::password));
//}

//TEST_F(face_auth_test, validate_no_user_in_db_nok)
//{
	//EXPECT_FALSE(lm.validate(constant::user, constant::password));
//}

//TEST_F(face_auth_test, validate_wrong_password_nok)
//{
	//EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_password));
	//EXPECT_FALSE(lm.validate(constant::user, constant::password2));
//}

//TEST_F(face_auth_test, change_password)
//{
	//EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_password));
	//EXPECT_FALSE(lm.validate(constant::user, constant::password2));
	//EXPECT_TRUE(lm.validate(constant::user, constant::password));

	////wrong root password
	//EXPECT_FALSE(lm.change_password(constant::user, constant::password, constant::password2,
	   //constant::password));

	////wrong user password
	//EXPECT_FALSE(lm.change_password(constant::user, constant::password2,
	 //constant::password2, constant::root_password));

	//EXPECT_TRUE(lm.change_password(constant::user, constant::password, constant::password2,
	   //constant::root_password));

	//EXPECT_FALSE(lm.validate(constant::user, constant::password));
	//EXPECT_TRUE(lm.validate(constant::user, constant::password2));
//}



////TEST_F(face_auth_test, crypt)
////{
	////face lm;

	////EXPECT_STREQ(constant::enc_user.c_str(),
	 ////lm.crypt(constant::user).c_str());

	////EXPECT_STRNE(constant::user.c_str(),
	 ////lm.crypt(constant::user).c_str());
////}

////int main(int argc, char **argv) {
    ////testing::InitGoogleTest(&argc, argv);
    ////return RUN_ALL_TESTS();
////}
