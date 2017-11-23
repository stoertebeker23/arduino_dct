#ifndef MATH_H
#define MATH_H
vector<double> dct(vector<double> &values, bool invert, bool squareroot) {
    // Vector containing either spectral value or signal values
    vector<double> result;

    // Calculate a result vector the same size as the input vector
    for(int i = 0; i < values.size(); i++) {

        // Sum the size of the input window resulting in one result for the DCT
        double temp = 0;
        for(int j = 0; j < values.size(); j++) {
            // Inversion of DCT is pretty much the same.
            if(!invert) {
                temp += values.at(j) * cos((M_PI*i*(2*j+1)) / (values.size()*2));
            } else {
                // Alpha value is applied to inverse DCT inside the sum
                double modifier;
                if (j == 0) {
                    modifier = sqrt(1.0/values.size());
                } else {
                    modifier = sqrt(2.0/values.size());
                }
                temp += modifier *
                        values.at(j) * cos((M_PI*j*(2*i+1)) / (values.size()*2));
            }
        }
        // Alpha value is applied outside the sum for DCT
        if (i == 0 && !invert) {
            temp = temp * sqrt(1.0/values.size());
        } else {
            temp = temp * sqrt(2.0/values.size());
        }
        if(squareroot) {
            result.push_back(fabs(temp));
         } else {
            result.push_back(temp);
        }
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

#endif // MATH_H
