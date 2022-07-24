#include <map>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

std::map<std::string, std::string> mapFromIni(std::string path, int maxSettings = 255) {
	std::ifstream ifs = std::ifstream(path);
	// ini is potentially user input, so I want to avoid mods that would try to crash the game by loading too many strings
	// 255 seems like a decent number
	int counter = 0; 

	std::string line = std::string();
	std::map<std::string, std::string> retval = std::map<std::string, std::string>();
	
	std::regex match_pattern = std::regex("^([a-zA-Z0-9_\\-]*)(?:\\s*(?:\\\\t)*\\s*=\\s*(?:\\\\t)*\\s*)([a-zA-Z0-9_\\-]*)", std::regex_constants::optimize);
	std::smatch match = std::smatch();

	if (ifs.is_open()) {
		while (ifs.good() && counter < maxSettings) {
			std::getline(ifs, line);
			std::regex_search(line, match, match_pattern);
			if (match.size() == 3) // match[0] is the whole line
				counter++;
				retval.insert_or_assign(match[1], match[2]);
		}
		ifs.close();
	} else {
		printf_s("\x1B[31mCould not load the file!\033[0m ifs.is_open() == false\n");
	}

	return retval;
}
