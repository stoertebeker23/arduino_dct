
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

#include "dct.h"
#include "output.h"
#include "input.h"

std::string help = "Possible arguments:\n"
    "-f: input file\n"
    "-s: sample rate\n"
    "-l: dct size\n"
    "-a: averaging\n"
    "-q: squareroot\n"
    "-i: include inverse\n"
    "-d: format\n";
    
char* getArgValue(char** argv, int i) {
    if(argv[i + 1][0] == '-') {
        cout << "Error: No value specified for argument " << argv[i] << endl;
        throw std::runtime_error("Error parsing command line arguments");
    }
    return argv[i + 1];
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << help << endl;
        return 0;
    }

    int sample_rate = 10000;
    std::string filename;
    int dct_size = 16;
    int averaging = 0;
    Format format = Format::OWN;
    bool inverse = false;
    bool squareroot = false;

    // First arg is our program name, skip it
    // Last arg has to be a value for the previous arg, skip it
    for(int i = 1; i < argc - 1; i++) {
        std::string arg = std::string(argv[i]);
        if(arg == "-f") {
            filename = getArgValue(argv, i);
        } else if (arg == "-s") {
            sample_rate = atoi(getArgValue(argv, i));
        } else if (arg == "-l") {
            dct_size = atoi(getArgValue(argv, i));
        } else if (arg == "-h") {
            cout << help << endl;
            return 0;
        } else if (arg == "-a") {
            averaging = atoi(getArgValue(argv, i));
        } else if (arg == "-q") {
            squareroot = atoi(getArgValue(argv, i));
        } else if (arg == "-i") {
            inverse = atoi(getArgValue(argv, i));
        } else if (arg == "-d") {
            std::string format_raw = getArgValue(argv, i);
            
            if(format_raw == "own") {
                format = Format::OWN;
            } else if(format_raw == "matlab") {
                format = Format::MATLAB;
            } else {
                cout << "Unsupported format: " << format_raw << endl
                     << "Supported are: \"own\", \"matlab\"" << endl;
                throw std::runtime_error("Unsupported format");
            }
        }
    }

    if(averaging) {
        cout << "averaging over " << averaging << " values" << endl;
    }
    
    if(filename.empty()) {
        cout << "Warning: no filename specified (argument: -f <filename>)." << endl;
    }

    vector<double> input = parseFile(filename);
    if(input.empty()) {
        throw std::runtime_error("Could not read input file");
    }

    vector<double> dct_window;
    vector<vector<double>> transformed;
    vector<vector<double>> inverse_dct;

    for(size_t i = 0; i < input.size(); ++i) {
        // Read signal values to dct window...
        dct_window.push_back(input.at(i));
        // ...until window size is reached then...
        if (i > 0 && i % dct_size == 0) {
            vector<double> temp = dct(dct_window, false, squareroot);
            vector<double> inv;
            
            if(inverse) {
                inv = dct(temp, true, squareroot);
            }
            
            if(averaging && transformed.size() > 1) {
                vector<double> average = calc_avg(transformed, temp, averaging);
                transformed.push_back(average);

                for(size_t i = 0; i < average.size(); i++) {
                    std::cout << average.at(i) << std::endl;
                }
            } else {
                transformed.push_back(temp);
                if(inverse) {
                    inverse_dct.push_back(inv);
                }

                for(size_t i = 0; i < temp.size(); i++) {
                    std::cout << temp.at(i) << std::endl;
                }
                if(inverse) {
                    std::cout << std::endl;
                    for(size_t i = 0; i < temp.size(); i++) {
                        std::cout << inv.at(i) << std::endl;
                    }
                    std::cout << std::endl;
                }
            }
            // clear window to fill it with new signal values
            dct_window.clear();
        }
    }

    if(transformed.size() == 0) {
        std::cout << "No results written, is your dct window "
                     "longer than your file?" << std::endl;
    } else {
        gnuplot_export(input, transformed, inverse_dct, sample_rate, format);
        std::vector<double> lol;
        lanczos(lol, 4, 2);
    }
    
    return 0;
}
