#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

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

    int sample_rate;
    std::string filename;
    int dct_size;

    for(int i = 0; i < argc; i++) {
        std::string arg = std::string(argv[i]);
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
        std::cout << "sth went wront" << std::endl;
    }

    std::vector<double> dct_window, temp;
    std::vector<std::vector<double>> transformed;
    std::string str;

    int linecount = 0;

    while (std::getline(_file, str)) {
        dct_window.push_back(atof(str.c_str()));
        linecount ++;

        if (!((linecount+1) % dct_size)) {
            temp = dct(dct_window);
            transformed.push_back(temp);
            for(int i = 0; i < temp.size(); i++) {
                std::cout << temp.at(i) << std::endl;
            }
            dct_window.clear();
        }
    }
}
