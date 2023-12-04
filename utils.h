#include<string>
#include<vector>
#include<fstream>

int readFile(std::string& fileName, std::vector<std::string>& lines);

void splitOnSpace(std::string& line, std::vector<std::string>& words);