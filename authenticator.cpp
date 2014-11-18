#include "authenticator.h"
#include <iostream>

namespace constant {
	const char key[3] = {'P', 'W', 'R'};
}
using namespace std;
authenticator::authenticator()
{
}

bool authenticator::add_user(std::string user, std::string password)
{
	if (db.find(user) != db.end()) {
		cout << "user already in db";
		return false;
	}

	db.insert(std::pair<std::string, std::string>(user, encrypt_decrypt(password)));
	return true;
}


std::string authenticator::encrypt_decrypt(std::string &input)
{
	std::string output;
	for (unsigned int i = 0; i< input.size(); ++i) {
		output[i] = input[i] ^ constant::key[i % (sizeof(constant::key) / sizeof(char))];
	}
	return output;

}
