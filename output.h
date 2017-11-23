#ifndef OUTPUT_H
#define OUTPUT_H
void gnuplot_export(const vector<double>& input,
                    const vector<vector<double>>& transformed,
                    const vector<vector<double>>& inverse,
                    int samplerate, std::string format) {
    int window_num = 0;
    int input_index = 0;
    //TODO: add file output for invese too
    for(const vector<double>& window : transformed) {
        std::ofstream dct_file(std::to_string(window_num) + ".dct");
        if(format == "own") {
            dct_file << "# DCT spectrum file generated by Arduino_DCT\n";
            dct_file << "# X Y\n";
        } else if (format == "matlab") {
            dct_file << "[";
        } else {
            dct_file << "# Unknown format" << endl;
            cout << "ERROR: Unknown output file format selected" << endl;
        }

        int x = 0;

        for(const double d : window) {
            const double x_scaled = x * samplerate / (2.0 * window.size());
            if(format == "own") {
                dct_file << x_scaled << " " << d << "\n";
            } else if(format == "matlab") {
                dct_file << x_scaled << "," << d;
                if (x == window.size()-1) {
                    dct_file << "]";
                } else {
                    dct_file << ";";
                }
            }
            x++;
        }

        std::ofstream signal_file(std::to_string(window_num) + ".signal");

        if(format == "own") {
            signal_file << "# Signal file generated by Arduino_DCT\n";
            signal_file << "# X Y\n";
        } else if (format == "matlab") {
            signal_file << "[";
        } else {
            signal_file << "# Unknown format" << endl;
            cout << "ERROR: Unknown output file format selected" << endl;
        }
        x = 0;
        for(int i = 0; i < window.size(); ++i, ++input_index) {
            const double x_scaled = x * 1.0 / samplerate;
            if(format == "own") {
                signal_file << x_scaled << " " << input.at(input_index) << "\n";
            } else if(format == "matlab") {
                signal_file << x_scaled << "," << input.at(input_index);
                if (i == window.size()-1) {
                    signal_file << "]";
                } else {
                    signal_file << ";";
                }
            }

            x++;
        }

        window_num++;
    }
}
#endif // OUTPUT_H
