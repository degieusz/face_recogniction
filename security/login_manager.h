#ifndef LOGIN_MANAGER_H
#define LOGIN_MANAGER_H

#include <string>
#include <map>
#include <utility>


class login_manager
{

public:
	typedef std::map<std::string, std::string> db_type;
	login_manager();

	bool add(std::string user, std::string password);

	bool remove(std::string user, std::string password);

	bool validate(std::string user, std::string password);

	bool change_password(std::string user, std::string old_password, std::string new_password);

private:
	std::string crypt(const std::string& input);

	db_type db;

};

#endif // LOGIN_MANAGER_H
