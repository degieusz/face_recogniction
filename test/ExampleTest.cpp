#include "gmock/gmock.h"
#include <string_check.h>

class TestCaseFixture : public testing::Test {
public:

};

TEST_F(TestCaseFixture, string_check) {
	std::string letters_only("AdsdvJLkjlfsdkjLS");
	std::string not_letters1("AdsdvJLk;jlfsdkjLS");
	std::string not_letters2("AdsdvJLk5jlfsdkjLS");
	EXPECT_TRUE(str_only_letters(letters_only));
	EXPECT_FALSE(str_only_letters(not_letters1));
	EXPECT_FALSE(str_only_letters(not_letters2));

}

