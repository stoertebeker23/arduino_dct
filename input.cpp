#include "input.h"

using std::vector;
using std::string;
#include <fstream>
#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;

vector<double> parseFile(string filename, string* errors) {
    std::ifstream _file(filename);

    if(!_file.good()) {
        const string msg = "Could not read input file\n";
        cerr << msg;
        if(errors) {
            *errors += msg;
        }
        vector<double> nothing;
        return nothing;
    }
    
    std::stringstream buffer;
    buffer << _file.rdbuf();
    string inputRaw = buffer.str();
    
    return parseString(inputRaw.c_str(), errors);
}

std::vector<double> parseString(const char* rawInput, std::string* errors) {
    vector<double> inputParsed;
    
    char c;
    std::string s;
    const char* inputPtr = rawInput;
    int line = 1;
    
    while(true) {
        c = *inputPtr++;
        
        if(c == ' ' || c == '\t') {
            continue;
        }
        
        if(c == '\n' || c == '\0') {
            // Line or file end, try to parse a number
            if(s.empty()) {
                // This line did not contain anything
                if(c == '\0') {
                    break;
                }
                continue;
            }
            
            char* e;
            errno = 0;
            const double value = strtod(s.c_str(), &e);
            
            if (*e != '\0' ||  // error, we didn't consume the entire string
                errno != 0 )   // error, overflow or underflow
            {
                // fail
                if(errors) {
                    *errors += "Error in line " + std::to_string(line);
                    *errors += " (\"" + s + "\" is not a valid number)\n";
                }
            } else {
                // success
                inputParsed.push_back(value);
            }
            
            s.clear();
            
            if(c == '\0') {
                break;
            }
            
            line++;
        } else {
            s += c;
        }
    }
    
    return inputParsed;
}
