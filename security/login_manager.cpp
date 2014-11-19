#include "login_manager.h"
#include <iostream>
#include <fstream>

namespace constant {
	const char key[3] = {'P', 'W', 'R'};
	const std::string root("root");
	const std::string root_pass("root_pass");
	const std::string default_config_path(".face_recogniser");

}
using namespace std;
login_manager::login_manager()
{
	add(constant::root, constant::root_pass);
	//read_config_file(constant::default_config_path);
}

bool login_manager::add(std::string user, std::string password)
{
	if (db.find(user) != db.end()) {
		cout << "user "<< user << " already in db\n";
		return false;
	}

	db.insert(std::pair<std::string, std::string>(user, crypt(password)));
	return true;
}

bool login_manager::remove(std::string user, std::string password)
{
	login_manager::db_type::iterator found = db.find(user);
	if (found == db.end()) {
		cout << "user "<< user << " not in db\n";
		return false;
	}

	db.erase(found);
	return true;
}

bool login_manager::validate(std::string user, std::string password)
{
	login_manager::db_type::iterator found = db.find(user);
	if (found == db.end()) {
		cout << "user "<< user << " not in db\n";
		return false;
	}
	if (found->second == crypt(password) && !found->second.empty()) {
		cout << "user "<< user << " validated\n";
		return true;
	}
	else {
		cout << "\nvalidation for user "<< user << " failed\n";
		return false;
	}
}

bool login_manager::change_password(std::string user, std::string old_password,
  std::string new_password, std::string root_password)
{
	if (!validate(constant::root, root_password)) {
		return false;
	}
	if (validate(user, old_password)) {
		db[user] = crypt(new_password);
		return true;
	}
	return false;
}

bool login_manager::read_config_file(std::string file_path)
{
	ifstream config_file(file_path);
	if (!config_file) {
		cout << file_path << "could not be open";
		// TODO: add config file handling
		create_config_file();
		//return false;
	}
	while (config_file) {
		config_file >> config_file_content;
	}
	return true;
}

std::string login_manager::crypt(const std::string& input)
{
	std::string output = input;
	for (unsigned int i = 0; i< input.size(); ++i) {
		output[i] = input[i] ^ constant::key[i % (sizeof(constant::key) / sizeof(char))];
	}

	return output;
}
