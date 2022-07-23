#include <map>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

std::map<std::string, std::string> parseIni(std::string path) {
	std::ifstream ifs = std::ifstream(path);
	std::string line = std::string();
	std::map<std::string, std::string>	retval = std::map<std::string, std::string>();
	std::regex match_pattern = std::regex("^([a-zA-Z0-9_\\-]*)(?:\\s*(?:\\\\t)*\\s*=\\s*(?:\\\\t)*\\s*)([a-zA-Z0-9_\\-]*)", std::regex_constants::optimize);
	std::smatch match = std::smatch();

	if (ifs.is_open()) {
		while (ifs.good()) {
			std::getline(ifs, line);
			std::regex_search(line, match, match_pattern);
			if (match.size() < 3)
				continue;

			std::cout << "inside: " << match[1].str() << " - " << match[2].str() << "\n";
			retval.insert_or_assign(match[1], match[2]);
		}

	} else {
		printf("Could not load the file!" "ifs.is_open() == false");
	}

	for (std::pair<std::string, std::string> x : retval) {
		std::cout << x.first << ": " << x.second << "\n";
	}

	return retval;
}
