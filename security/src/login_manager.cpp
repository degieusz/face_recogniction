#include "login_manager.h"
#include <iostream>
#include <fstream>

namespace constant {
	const char key[3] = {'P', 'W', 'R'};
	const std::string root("root");
	const std::string root_pass("root_pass");

}
using namespace std;
login_manager::login_manager()
{
	db.insert(std::pair<std::string, std::string>(constant::root, crypt(constant::root_pass)));
	//TODO: load config, if not present create default config
	//read_config_file(constant::default_config_path);
}

bool login_manager::add(const std::string& user, const std::string& password,
 const std::string& root_password)
{
	if (!validate(constant::root, root_password)) {
		return false;
	}

	if (db.find(user) != db.end()) {
		cout << "user "<< user << " already in db\n";
		return false;
	}

	db.insert(std::pair<std::string, std::string>(user, crypt(password)));
	configuration.write(db);
	return true;
}

bool login_manager::remove(const std::string& user, const std::string& password,
 const std::string& root_password)
{
	if (!validate(constant::root, root_password)) {
		return false;
	}

	login_manager::db_type::iterator found = db.find(user);
	if (found == db.end()) {
		cout << "user "<< user << " not in db\n";
		return false;
	}

	db.erase(found);
	configuration.write(db);
	return true;
}

bool login_manager::validate(const std::string& user, const std::string& password) const
{
	login_manager::db_type::const_iterator found = db.find(user);
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

bool login_manager::change_password(const std::string& user, const std::string& old_password,
 const std::string& new_password)
{
	if (validate(user, old_password)) {
		db[user] = crypt(new_password);
		configuration.write(db);
		return true;
	}
	return false;
}

std::string login_manager::crypt(const std::string& input) const
{
	std::string output = input;
	for (unsigned int i = 0; i< input.size(); ++i) {
		output[i] = input[i] ^ constant::key[i % (sizeof(constant::key) / sizeof(char))];
	}

	return output;
}
