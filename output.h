#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>

enum class Format {
    OWN,
    MATLAB,
};

void gnuplot_export(const std::vector<double>& input,
                    const std::vector<std::vector<double>>& transformed,
                    const std::vector<std::vector<double>>& inverse,
                    int samplerate, Format format);

#endif // OUTPUT_H
