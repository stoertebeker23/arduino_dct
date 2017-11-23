#ifndef OUTPUT_H
#define OUTPUT_H
void gnuplot_export(const vector<double>& input,
                    const vector<vector<double>>& transformed,
                    const vector<vector<double>>& inverse,
                    int samplerate) {
    int window_num = 0;
    int input_index = 0;
    //TODO: add file output for invese too
    for(const vector<double>& window : transformed) {
        std::ofstream dct_file(std::to_string(window_num) + ".dct");
        dct_file << "# DCT spectrum file generated by Arduino_DCT\n";
        dct_file << "# X Y\n";

        int x = 0;
        for(const double d : window) {
            const double x_scaled = x * samplerate / (2.0 * window.size());
            dct_file << x_scaled << " " << d << "\n";
            x++;
        }

        std::ofstream signal_file(std::to_string(window_num) + ".signal");
        signal_file << "# Signal file generated by Arduino_DCT\n";
        signal_file << "# X Y\n";

        x = 0;
        for(int i = 0; i < window.size(); ++i, ++input_index) {
            const double x_scaled = x * 1.0 / samplerate;
            signal_file << x_scaled << " " << input.at(input_index) << "\n";
            x++;
        }

        window_num++;
    }
}
#endif // OUTPUT_H