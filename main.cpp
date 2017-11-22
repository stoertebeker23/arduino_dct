#include <iostream>
using std::cout;
using std::endl;
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

std::string help = "Possible arguments:\n"
"-i: input file\n"
"-f: sample rate\n"
"-l: dct size"
"-a: averaging";

std::vector<double> dct(std::vector<double> &values) {
    std::vector<double> result;
    for(int i = 0; i < values.size(); i++) {
        double temp = 0;
        for(int j = 0; j < values.size(); j++) {
            temp += values.at(j) * cos((M_PI*i*(2*j+1)) / (values.size()*2));
        }

        if (i == 0) {
            temp = temp * sqrt(1.0/values.size());
        } else {
            temp = temp * sqrt(2.0/values.size());
        }
        result.push_back(fabs(temp));
    }

    return result;
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

    for(int i = 0; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if(arg == "-i") {
            filename = argv[i+1];
        } else if (arg == "-f") {
            sample_rate = atoi(argv[i+1]);
        } else if (arg == "-l") {
            dct_size = atoi(argv[i+1]);
        } else if (arg == "-h") {
            cout << help << endl;
            return 0;
        } else if (arg == "-a") {
            averaging = atoi(argv[i+1]);
        }
    }

    std::ifstream _file(filename);

    if(!_file.good()) {
        throw std::runtime_error("Could not read input file");
    }

    std::vector<double> dct_window;
    std::vector<std::vector<double>> transformed;
    std::string str;

    int linecount = 0;

    while (std::getline(_file, str)) {
        dct_window.push_back(atof(str.c_str()));
        linecount++;

        if (!((linecount+1) % dct_size)) {
            std::vector<double> temp = dct(dct_window);
            std::vector<double> average;
            average = temp;
            if(averaging) {
                for(int i = 0; i < averaging; i++) {
                    const int index = transformed.size()-1-i;
                    if (i >= index) {
                        break;
                    }

                    for(int j = 0; j < average.size(); j++) {
                        average.at(j) += transformed.at(index).at(j);
                    }

                }
                for(double& d : average) {
                    d /= averaging;
                }

            }
            transformed.push_back(average);
            std::cout << "not averaged" << std::endl;
            for(int i = 0; i < temp.size(); i++) {
                std::cout << temp.at(i) << std::endl;

            }
            std::cout << "averaged" << std::endl;
            for(int i = 0; i < average.size(); i++) {
                std::cout << average.at(i) << std::endl;

            }
            
            dct_window.clear();
        }

    }
    
    return 0;
}
