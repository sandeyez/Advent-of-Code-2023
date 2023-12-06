#include<string>
#include<vector>
#include<fstream>

int readFile(std::string& fileName, std::vector<std::string>& lines);

void splitOnSpace(std::string& line, std::vector<std::string>& words);

int solveWithABCFormula(long a, long b, long c, long& x1, long& x2);
int solveWithABCFormula(int a, int b, int c, int& x1, int& x2);