#include "login_manager.h"
#include <gtest/gtest.h>

#include <stdio.h>
#include <config.h>
#include <boost/filesystem.hpp>

namespace constant {
	const std::string user("user1");
	const std::string password("pass");
	const std::string password2("pass2");

	const std::string enc_user("%$7\"ft");
	}

namespace os = boost::filesystem;
class login_manager_test : public testing::Test {
public:
	login_manager_test()
	{
		EXPECT_TRUE(lm.setup());
	}

	~login_manager_test()
	{
		os::remove_all(constant::default_config_path);
	}
	login_manager lm;

};

	//create test class
TEST_F(login_manager_test, add_ok)
{
	EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_pass));
	EXPECT_FALSE(lm.add(constant::user, constant::password, constant::root_pass));
}

TEST_F(login_manager_test, add_erase)
{
	EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_pass));
	EXPECT_TRUE(lm.remove(constant::user, constant::root_pass));
	EXPECT_FALSE(lm.remove(constant::user, constant::root_pass));
}

TEST_F(login_manager_test, add_validate)
{
	EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_pass));
	EXPECT_TRUE(lm.validate(constant::user, constant::password));
}

TEST_F(login_manager_test, validate_no_user_in_db_nok)
{
	EXPECT_FALSE(lm.validate(constant::user, constant::password));
}

TEST_F(login_manager_test, validate_wrong_password_nok)
{
	EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_pass));
	EXPECT_FALSE(lm.validate(constant::user, constant::password2));
}

TEST_F(login_manager_test, change_password)
{
	EXPECT_TRUE(lm.add(constant::user, constant::password, constant::root_pass));
	EXPECT_FALSE(lm.validate(constant::user, constant::password2));
	EXPECT_TRUE(lm.validate(constant::user, constant::password));

	//wrong user password
	EXPECT_FALSE(lm.change_password(constant::user, constant::password2, constant::password2));

	EXPECT_TRUE(lm.change_password(constant::user, constant::password, constant::password2));

	EXPECT_FALSE(lm.validate(constant::user, constant::password));
	EXPECT_TRUE(lm.validate(constant::user, constant::password2));
}



//TEST_F(login_manager_test, crypt)
//{
	//login_manager lm;

	//EXPECT_STREQ(constant::enc_user.c_str(),
	 //lm.crypt(constant::user).c_str());

	//EXPECT_STRNE(constant::user.c_str(),
	 //lm.crypt(constant::user).c_str());
//}

//int main(int argc, char **argv) {
    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
//}
