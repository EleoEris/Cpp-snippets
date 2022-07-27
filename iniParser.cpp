#include <unordered_map>
#include <string>
#include <fstream>
#include <regex>

std::unordered_map<std::string, std::string> mapFromIni(std::string path, int maxSettings, std::string errorKey) {
	std::ifstream ifs = std::ifstream(path);
	int counter = 0; 

	std::string line = std::string();
	std::unordered_map<std::string, std::string> retval = std::unordered_map<std::string, std::string>();
	
	std::regex match_pattern = std::regex("^([a-zA-Z0-9_\\-]*)(?:\\s*(?:\\\\t)*\\s*=\\s*(?:\\\\t)*\\s*)([a-zA-Z0-9_\\-]*)", std::regex_constants::optimize);
	std::smatch match = std::smatch();

	retval.insert_or_assign(errorKey, "");

	if (ifs.is_open()) {
		while (ifs.good()) {
			std::getline(ifs, line);
			std::regex_search(line, match, match_pattern);
			if (match.size() == 3) { // match[0] is the whole line
				counter++;
				retval.insert_or_assign(match[1], match[2]);
			}
			if (counter > maxSettings) {
				retval.insert_or_assign(errorKey, "Too many lines in settings!");
				break;
			}
		}
	} else {
		retval.insert_or_assign(errorKey, "Could not load the file! ifs.is_open() == false");
	}
	ifs.close();

	return retval;
}
