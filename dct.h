#ifndef MATH_H
#define MATH_H

#include <vector>
#include <cstddef>  // size_t

std::vector<double> dct(std::vector<double> &values, bool invert, bool squareroot);

std::vector<double> calc_avg(const std::vector<std::vector<double>>& history,
                             const std::vector<double>& new_values,
                             size_t avg_amount);

double sinc(double x);

std::vector<double> lanczos(std::vector<double> values, int rfac, int size = 2);

#endif // MATH_H
