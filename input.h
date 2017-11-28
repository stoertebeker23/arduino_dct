#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>

std::vector<double> parseFile(std::string filename, std::string* errors = nullptr);
std::vector<double> parseString(const char* rawInput, std::string* errors = nullptr);

#endif /* INPUT_H */
