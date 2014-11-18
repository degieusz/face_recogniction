#include "login_manager.h"
#include <iostream>

namespace constant {
	const char key[3] = {'P', 'W', 'R'};
}
using namespace std;
login_manager::login_manager()
{
}

bool login_manager::add(std::string user, std::string password)
{
	if (db.find(user) != db.end()) {
		cout << "user already in db\n";
		return false;
	}

	db.insert(std::pair<std::string, std::string>(user, crypt(password)));
	return true;
}

bool login_manager::remove(std::string user, std::string password)
{
	login_manager::db_type::iterator found = db.find(user);
	if (found == db.end()) {
		cout << "user not in db\n";
		return false;
	}

	db.erase(found);
	return true;
}

bool login_manager::validate(std::string user, std::string password)
{
	login_manager::db_type::iterator found = db.find(user);
	if (found == db.end()) {
		cout << "user not in db\n";
		return false;
	}
	if (found->second == password && !found->second.empty()) {
		cout << "user validated\n";
		return true;
	}
	else {
		cout << "validation failed\n";
		return false;
	}
}

bool login_manager::change_password(std::string user, std::string old_password,
 std::string new_password)
{
	if (validate(user, old_password)) {
		db[user] = crypt(new_password);
		return true;
	}
	return false;
}

std::string login_manager::crypt(const std::string& input)
{
	std::string output = input;
	for (unsigned int i = 0; i< input.size(); ++i) {
		output[i] = input[i] ^ constant::key[i % (sizeof(constant::key) / sizeof(char))];
	}

	return output;
}
