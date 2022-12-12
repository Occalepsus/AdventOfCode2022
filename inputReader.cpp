#include "inputReader.h"
#include <iostream>
#include <fstream>

std::vector<std::string> readInputFile(std::string path) {
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file " << path << std::endl;
        throw std::invalid_argument("Could not open the file " + path);
    }
    std::string line;
    std::vector<std::string> res;
    while (std::getline(inputFile, line)) {
        res.push_back(line.substr(0, line.find('\r')));
    }
    return res;
}

//std::vector<std::string> readInputFile(std::string src) {
//	std::ifstream inputFile(src);
//
//	std::vector<std::string> res{};
//
//	std::string buff{};
//	int i{ 0 };
//	while (getline(inputFile, buff)) {
//		std::cout << "Line " << i << ", reading \"" << buff << "\"\n";
//		res.push_back(buff);
//		i++;
//	}
//	std::cout << "End of file, read done !\n";
//
//	inputFile.close();
//
//	res.shrink_to_fit();
//	return res;
//}