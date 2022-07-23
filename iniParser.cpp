#include <map>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

std::map<std::string, std::string> parseIni(std::string path) {
	std::ifstream ifs = std::ifstream(path);
	std::string line = std::string();
	std::map<std::string, std::string> retval = std::map<std::string, std::string>();
	// the pattern below should be the most idiot-proof pattern ever
	std::regex match_pattern = std::regex("^([a-zA-Z0-9_\\-]*)(?:\\s*(?:\\\\t)*\\s*=\\s*(?:\\\\t)*\\s*)([a-zA-Z0-9_\\-]*)", std::regex_constants::optimize);
	std::smatch match = std::smatch();

	if (ifs.is_open()) {
		while (ifs.good()) {
			std::getline(ifs, line);
			std::regex_search(line, match, match_pattern);
			if (match.size() == 3) // match[0] is the whole line
				retval.insert_or_assign(match[1], match[2]);
		}
	} else {
		std::cout << "\x1B[31mCould not load the file!\033[0m ifs.is_open() == false\n";
	}

	return retval;
}
