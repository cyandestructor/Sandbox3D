#ifndef JASS_UTILITIES_H
#define JASS_UTILITIES_H

namespace Jass {

	namespace Strings {

		std::vector<std::string> Split(const std::string& str, char separator);
		std::vector<std::string> Split(const std::string& str, const std::string& separator);
	}

}

#endif // !JASS_UTILITIES_H
