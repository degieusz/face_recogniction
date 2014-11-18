#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>
#include <map>
#include <utility>


class authenticator
{

public:
	authenticator();

	bool add_user(std::string user, std::string password);

	bool remove_user(std::string user, std::string password);

	void validate_user(std::string user, std::string password);

private:
	std::string encrypt_decrypt(std::string& input);

	std::map<std::string, std::string> db;

};

#endif // AUTHENTICATOR_H
