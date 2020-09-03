#include "jasspch.h"
#include "JassUtilities.h"

namespace Jass {

	namespace Strings {

		std::vector<std::string> Split(const std::string& str, char separator)
		{
			std::vector<std::string> strings;
			
			size_t begin = 0;
			size_t end = str.find_first_of(separator, begin);
			end = (end == std::string::npos) ? str.size() : end;
			while (end != str.size())
			{
				strings.push_back(str.substr(begin, end - begin));
				begin = end;
				end = str.find_first_of(separator, begin);
				end = (end == std::string::npos) ? str.size() : end;
			}

			return strings;
		}

		std::vector<std::string> Split(const std::string& str, const std::string& separator)
		{
			std::vector<std::string> strings;

			size_t begin = 0;
			size_t end = str.find_first_of(separator, begin);
			end = (end == std::string::npos) ? str.size() : end;
			while (end != str.size())
			{
				strings.push_back(str.substr(begin, end - begin));
				begin = end;
				end = str.find_first_of(separator, begin);
				end = (end == std::string::npos) ? str.size() : end;
			}

			return strings;
		}

	}

}
