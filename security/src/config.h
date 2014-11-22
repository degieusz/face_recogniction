#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <boost/optional.hpp>

namespace constant {
	const std::string default_config_path(".face_recogniser");
}

class config
{
public:
	typedef std::map<std::string, std::string> db_type;
	config(std::string file_path = constant::default_config_path);

	boost::optional<db_type> read();

	bool write(db_type db);

	/*bool change_password(std::string user, std::string old_password, std::string new_password,*/
	/*std::string root_password);*/

	/*bool read_config_file(const std::string file_path);*/

private:
	boost::optional<db_type> parse();

	const std::string path;
	std::vector<std::string> config_file_content;

};

#endif // CONFIG_H
