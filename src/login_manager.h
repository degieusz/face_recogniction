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

	bool setup();

	bool add(const std::string& user, const std::string& password, const std::string& root_password);

	bool remove(const std::string& user, const std::string& root_password);

	bool validate(const std::string& user, const std::string& password) const;

	bool change_password(const std::string& user, const std::string& old_password,
	 const std::string& new_password);

private:
	//TODO: check if no bad characters in string
	bool validate_credential(const std::string& credential);
	bool create_config_file();
	std::string crypt(const std::string& input) const;

	boost::optional<db_type> db;

	std::string config_file_path;
	std::string config_file_content;

	config configuration;
};

#endif // LOGIN_MANAGER_H
