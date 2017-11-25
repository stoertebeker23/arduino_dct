#include "dct.h"

#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <cmath>

vector<double> dct(vector<double> &values, bool invert, bool squareroot) {
    // Vector containing either spectral value or signal values
    vector<double> result;

    // Calculate a result vector the same size as the input vector
    for(size_t i = 0; i < values.size(); i++) {

        // Sum the size of the input window resulting in one result for the DCT
        double temp = 0;
        for(size_t j = 0; j < values.size(); j++) {
            // Inversion of DCT is pretty much the same.
            if(!invert) {
                temp += values.at(j) * cos((M_PI*i*(2*j+1)) / (values.size()*2));
            } else {
                // Alpha value is applied to inverse DCT inside the sum
                const double numerator = (i == 0) ? 1.0 : 2.0;
                const double modifier = sqrt(numerator / values.size());
                const double v = cos(M_PI * j * (2 * i + 1) / (values.size() * 2));
                temp += modifier * values.at(j) * v;
            }
        }
        
        // Alpha value is applied outside the sum for DCT
        const double numerator = (i == 0 && !invert) ? 1.0 : 2.0;
        temp *= sqrt(numerator / values.size());
        
        // "squareroot"
        if(squareroot) {
            temp = fabs(temp);
        }
        
        result.push_back(temp);
    }
    return result;
}

vector<double> calc_avg(const vector<vector<double>>& history,
                             const vector<double>& new_values,
                             size_t avg_amount) {
    vector<double> result(new_values);

    // If we don't have enough values yet, use what's there (+ 1 because new values)
    avg_amount = std::min(avg_amount, history.size() + 1);

    for (size_t i = 0; i < avg_amount; i++) {
        const int index = history.size() - 1 - i;

        if (index < 0 || index >= (int)history.size()) {
            break;
        }

        if (history.at(index).size() != result.size()) {
            // TODO make this an assert
            cout << "ERROR: history and result size mismatch!" << endl;
        }

        for (size_t j = 0; j < result.size(); j++) {
            result.at(j) += history.at(index).at(j);
        }
    }

    for(double& d : result) {
        d /= avg_amount;
    }

    return result;
}

double sinc(double x) {
    return (sin(M_PI * x) * 2.0 * sin(M_PI * x / 2.0) / (M_PI * M_PI * x * x));
}

std::vector<double> lanczos(std::vector<double> values, int rfac, int size) {
    std::vector<double> result;
    
    // TODO: why pass values as argument if we clear it anyway?
    values.clear();
    for(int i = 0; i < 32; i++) {
        values.push_back(sin(i*M_PI/4));
    }
    int x = 0;

    for(size_t i = 0; i < rfac * values.size(); i++) {
        if (rfac <= 1) {
            result = values;
            break;
        }
        
        if (i % rfac == 0) {
            const int index = i / rfac - 1;
            if(index < 0) {
                continue;
            }
            result.push_back(values.at(index));
            x = 0;
        } else {
            cout << 1.0 / rfac << endl;
            
            x++;
            double temp = 0;
            
            for(int j = -size; j <= size; j++) {
                if(j == 0) {
                    continue;
                }
                
                const int index = i / rfac + j;
                
                if(j < 0) {
                    if(index < 0) {
                        continue;
                    }
                    temp += values.at(index) * sinc(x * 1.0 / rfac + abs(j) - 1);
                } else if(j > 0) {
                    if(i / rfac + j - 1 > values.size() - 1) {
                        continue;
                    }
                    temp += values.at(index - 1) * sinc(abs(j) - x * 1.0 / rfac);
                }
            }
            result.push_back(temp);
        }
    }
    
    cout << "[";
    for(size_t i = 0; i < values.size(); i++) {
        cout << values.at(i) << ",";
    }
    cout << "];" << endl << "[";
    for(size_t i = 0; i < result.size(); i++) {
        cout << result.at(i) << ",";
    }
    cout << "];" << endl;
    return result;
}
