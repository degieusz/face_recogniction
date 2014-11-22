#include "trainer.h"
#include <gtest/gtest.h>
#include <boost/thread/thread.hpp>

namespace face {

namespace constant {
	const std::string user("user");
}

class trainer_test : public testing::Test {
public:
	trainer t;

	bool load_img_from_path(std::string path, cv::Mat& read_img)
	{
		read_img = cv::imread(path);
		if (!read_img.data) {
			std::cout << "image " << path << " not read.\n";
			return false;
		}

	}
};

TEST_F(trainer_test, create)
{
	EXPECT_TRUE(t.get_data(constant::user));
	//EXPECT_TRUE(fa.load_face_cascade());
	//cv::Mat capture;
	//load_img_from_path(constant::test_img, capture);

	//std::vector<cv::Mat> detected_faces(5);
	//EXPECT_TRUE(fa.detect(detected_faces, capture));
	//EXPECT_FALSE(detected_faces.empty());
}

}
