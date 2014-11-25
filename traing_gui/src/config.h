#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <boost/optional.hpp>

namespace constant {
	const std::string default_config_path(".face_recognizerrc");
	const std::string root("root");
	const std::string root_pass("root_pass");
}

class config
{
public:
	typedef std::map<std::string, std::string> db_type;

	config(const std::string& file_path = constant::default_config_path);

	//TODO: shared ptr better?
	boost::optional<db_type> read();

	bool write(db_type& db) const;

private:
	boost::optional<db_type> read_impl();

	const std::string path;
	std::vector<std::string> config_file_content;
};

#endif // CONFIG_H
