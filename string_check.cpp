#include <string>
#include <string_check.h>

bool str_only_letters(const std::string& to_check)
{
	char c;
	for (unsigned int i = 0; i < to_check.length(); ++i) {
		c = to_check.at(i);

		if (! ( ( c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) ) {
			return false;
		}
	}
	return true;
}

