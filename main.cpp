#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;


std::vector<double> dct(std::vector<double> &values) {
    std::vector<double> result;
    for(int i = 0; i < values.size(); i++) {
        double temp = 0;
        for(int j = 0; j < values.size(); j++) {
            temp += values.at(j) * cos(M_PI / values.size() * (j + 0.5) * i);
        }
        result.push_back(temp);
    }

    return result;
}

int main(int argc, char *argv[]) {

    int sample_rate;
    std::string filename;
    int dct_size;

    for(int i = 0; i < argc; i++) {
        string arg = string(argv[i]);
        if(arg == "-i") {
            filename = argv[i+1];
        } else if (arg == "-f") {
            sample_rate = atoi(argv[i+1]);
        } else if (arg == "-l") {
            dct_size = atoi(argv[i+1]);
        }
    }

    std::ifstream _file(filename);

    if(!_file.good()) {
        // Harten Error werfen, wird nicht passieren
    }

    std::vector<double> dct_window;
    std::vector<std::vector<double>> transformed;
    std::string str;
    int linecount = 0;
    while (std::getline(_file, str)) {
        dct_window.push_back(atof(str.c_str()));
        linecount ++;
        if (!((linecount+1) % dct_size)) {
            transformed.push_back(dct(dct_window));
            dct_window.clear();
        }
    }
}
