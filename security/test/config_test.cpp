#include "config.h"
#include <gtest/gtest.h>
#include <map>
#include <fstream>
#include <streambuf>
#include <stdio.h>

namespace constant {
	const std::string path("file_path.txt");
	const std::string
	 expected_config("::user1::password1::\n::user2::password2::\n::user3::password2::\n");
	}

class config_test : public testing::Test {
public:
	config_test()
	{ }

	~config_test()
	{
		remove(constant::path.c_str());
		remove(constant::default_config_path.c_str());
	}

	bool file_content_equal(std::string path, std::string expected_content)
	{
		std::ifstream file(path.c_str());

		if (!file) {
			std::cout << path << "could not be open\n";
			return false;

	}
	std::string content((std::istreambuf_iterator<char>(file)),
	              std::istreambuf_iterator<char>());

	EXPECT_STREQ(expected_content.c_str(), content.c_str());
	return true;
	}

};

TEST_F(config_test, write)
{
	config::db_type conf_info;
	conf_info.insert(std::make_pair("user1", "password1"));
	conf_info.insert(std::make_pair("user2", "password2"));
	conf_info.insert(std::make_pair("user3", "password2"));
	config cfg(constant::path);
	cfg.write(conf_info);
	file_content_equal(constant::path, constant::expected_config);
}

TEST_F(config_test, write_read)
{
	config::db_type conf_info;
	conf_info.insert(std::make_pair("user1", "password1"));
	conf_info.insert(std::make_pair("user2", "password2"));
	conf_info.insert(std::make_pair("user3", "password2"));
	config cfg(constant::path);
	cfg.write(conf_info);
	EXPECT_EQ(conf_info, cfg.read().get());
	file_content_equal(constant::path, constant::expected_config);
}

TEST_F(config_test, read_no_file)
{
	config cfg(constant::path);
	EXPECT_FALSE(cfg.read());
}

