#include "login_manager.cpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace constant {
	const std::string user("user1");
	const std::string password("pass");
	const std::string password2("pass2");
	const std::string root_password("root_pass");

	const std::string enc_user("%$7\"ft");
	}


	//create test class
TEST(login_manager_test, add)
{
	login_manager lm;
	EXPECT_TRUE(lm.add(constant::user, constant::password));
	EXPECT_FALSE(lm.add(constant::user, constant::password));
}

TEST(login_manager_test, add_erase)
{
	login_manager lm;
	EXPECT_TRUE(lm.add(constant::user, constant::password));
	EXPECT_TRUE(lm.remove(constant::user, constant::password));
	EXPECT_FALSE(lm.remove(constant::user, constant::password));
}

TEST(login_manager_test, add_validate)
{
	login_manager lm;
	EXPECT_TRUE(lm.add(constant::user, constant::password));
	EXPECT_TRUE(lm.validate(constant::user, constant::password));
}

TEST(login_manager_test, validate_no_user_in_db_nok)
{
	login_manager lm;
	EXPECT_FALSE(lm.validate(constant::user, constant::password));
}

TEST(login_manager_test, validate_wrong_password_nok)
{
	login_manager lm;
	EXPECT_TRUE(lm.add(constant::user, constant::password));
	EXPECT_FALSE(lm.validate(constant::user, constant::password2));
}

TEST(login_manager_test, change_password)
{
	login_manager lm;
	EXPECT_TRUE(lm.add(constant::user, constant::password));
	EXPECT_FALSE(lm.validate(constant::user, constant::password2));
	EXPECT_TRUE(lm.validate(constant::user, constant::password));

	//wrong root password
	EXPECT_FALSE(lm.change_password(constant::user, constant::password, constant::password2,
	   constant::password));

	//wrong user password
	EXPECT_FALSE(lm.change_password(constant::user, constant::password2,
	 constant::password2, constant::root_password));

	EXPECT_TRUE(lm.change_password(constant::user, constant::password, constant::password2,
	   constant::root_password));

	EXPECT_FALSE(lm.validate(constant::user, constant::password));
	EXPECT_TRUE(lm.validate(constant::user, constant::password2));
}



//TEST(login_manager_test, crypt)
//{
	//login_manager lm;

	//EXPECT_STREQ(constant::enc_user.c_str(),
	 //lm.crypt(constant::user).c_str());

	//EXPECT_STRNE(constant::user.c_str(),
	 //lm.crypt(constant::user).c_str());
//}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
