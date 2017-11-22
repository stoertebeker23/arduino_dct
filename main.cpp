#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>

std::string help = "Possible arguments:\n"
    "-i: input file\n"
    "-f: sample rate\n"
    "-l: dct size\n"
    "-a: averaging\n";

vector<double> dct(vector<double> &values) {
    vector<double> result;
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

vector<double> calc_avg(const vector<vector<double>>& history,
                             const vector<double>& new_values,
                             size_t avg_amount) {
    vector<double> result(new_values);
    
    // If we don't have enough values yet, use what's there (+ 1 because new values)
    avg_amount = std::min(avg_amount, history.size() + 1);
    
    for (int i = 0; i < avg_amount; i++) {
        const int index = history.size() - 1 - i;
        
        if (index < 0 || index >= history.size()) {
            break;
        }
        
        if (history.at(index).size() != result.size()) {
            // TODO make this an assert
            cout << "ERROR: history and result size mismatch!" << endl;
        }

        for (int j = 0; j < result.size(); j++) {
            result.at(j) += history.at(index).at(j);
        }
    }
    
    for(double& d : result) {
        d /= avg_amount;
    }
    
    return result;
}

void gnuplot_export(const vector<vector<double>>& transformed) {
    std::ofstream out("plotting_data.dat");
    out << "# File generated by Arduino_DCT\n";
    out << "# X Y\n";
    
    int x = 0;
    for(const vector<double>& window : transformed) {
        for(const double d : window) {
            out << x++ << " " << d << "\n";
        }
    }
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
    
    if(averaging) {
        cout << "averaging over " << averaging << " values" << endl;
    }

    std::ifstream _file(filename);

    if(!_file.good()) {
        throw std::runtime_error("Could not read input file");
    }

    vector<double> dct_window;
    vector<vector<double>> transformed;
    std::string str;

    int linecount = 0;

    while (std::getline(_file, str)) {
        dct_window.push_back(atof(str.c_str()));
        linecount++;

        if (linecount % dct_size == 0) {
            vector<double> temp = dct(dct_window);
            
            if(averaging && transformed.size() > 1) {
                vector<double> average = calc_avg(transformed, temp, averaging);
                transformed.push_back(average);
                
                // std::cout << "averaged" << std::endl;
                for(int i = 0; i < average.size(); i++) {
                    std::cout << average.at(i) << std::endl;
                }
            } else {
                transformed.push_back(temp);
                
                // std::cout << "not averaged" << std::endl;
                for(int i = 0; i < temp.size(); i++) {
                    std::cout << temp.at(i) << std::endl;
                }
            }
            
            dct_window.clear();
        }
    }
    
    gnuplot_export(transformed);
    
    return 0;
}
