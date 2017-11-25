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
    char inputText[1024 * 1024] = {};
    std::vector<double> inputParsed;
    std::vector<std::vector<double>> transformed;
    
    void parseInput();
    void calcDCT();
};

#endif /* MAINWINDOW_H */
