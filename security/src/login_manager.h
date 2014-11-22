#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <string>
#include <map>
#include <utility>
#include <config.h>


class login_manager
{

public:
	typedef std::map<std::string, std::string> db_type;
	login_manager();

	bool add(std::string user, std::string password, std::string root_password);

	bool remove(std::string user, std::string password, std::string root_password);

	bool validate(std::string user, std::string password);

	bool change_password(std::string user, std::string old_password, std::string new_password,
	  std::string root_password);

	bool read_config_file(const std::string file_path);

private:
	bool validate_credential(std::string credential);
	bool create_config_file();
	std::string crypt(const std::string& input);

	db_type db;

	std::string config_file_path;
	std::string config_file_content;

	config configuration;

};

#endif // LOGIN_MANAGER_H
