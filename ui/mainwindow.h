#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <imgui.h>

#include <string>
#include <vector>


class MainWindow {
public:
    MainWindow();
    void draw();
    
private:
    struct DCT_Settings {
        int sample_rate = 10000;
        int window_size = 16;
        int averaging = 0;
        bool inverse = false;
        bool squareroot = false;
    } dct_settings;
    
    char inputText[1024 * 1024] = {};
    std::vector<double> inputParsed;
    std::vector<std::vector<double>> transformed;
    std::string errors;
    
    void parseInput();
    void calcDCT();
    void drawGraphs();
};

#endif /* MAINWINDOW_H */
