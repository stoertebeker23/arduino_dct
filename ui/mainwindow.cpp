#include "mainwindow.h"
#include "imgui_impl_glfw_gl3.h"
#include "../dct.h"

using std::vector;
#include <iostream>
using std::cout;
using std::endl;


MainWindow::MainWindow() {}

void MainWindow::draw() {
    ImGui::Begin("MainWindow");
    
    ImGui::Text("Paste your input here:");
    
    ImGui::InputTextMultiline("##source", inputText, IM_ARRAYSIZE(inputText),
        ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
        ImGuiInputTextFlags_AllowTabInput);
        
    if(ImGui::Button("Calculate DCT")) {
        parseInput();
        calcDCT();
    }
        
    ImGui::End();
}

void MainWindow::parseInput() {
    inputParsed.clear();
    
    char c;
    std::string s;
    char* inputPtr = inputText;
    while(true) {
        c = *inputPtr++;
        
        if(c == '\n' || c == '\0') {
            // Line or file end, try to parse a number
            if(s.empty()) {
                // This line did not contain anything
                if(c == '\0') {
                    break;
                }
                continue;
            }
            
            const double value = std::atof(s.c_str());
            inputParsed.push_back(value);
            s.clear();
            
            if(c == '\0') {
                break;
            }
        } else {
            s += c;
        }
    }
}

void MainWindow::calcDCT() {
    transformed.clear();
    
    int sample_rate = 10000;
    int dct_size = 16;
    int averaging = 0;
    bool inverse = false;
    bool squareroot = false;
    
    vector<double> dct_window;
    // vector<vector<double>> transformed;
    vector<vector<double>> inverse_dct;

    for(size_t i = 0; i < inputParsed.size(); ++i) {
        // Read signal values to dct window...
        dct_window.push_back(inputParsed.at(i));
        // ...until window size is reached then...
        if (i > 0 && i % dct_size == 0) {
            vector<double> temp = dct(dct_window, false, squareroot);
            vector<double> inv;
            
            if(inverse) {
                inv = dct(temp, true, squareroot);
            }
            
            if(averaging && transformed.size() > 1) {
                vector<double> average = calc_avg(transformed, temp, averaging);
                transformed.push_back(average);

                // for(size_t i = 0; i < average.size(); i++) {
                //     std::cout << average.at(i) << std::endl;
                // }
            } else {
                transformed.push_back(temp);
                if(inverse) {
                    inverse_dct.push_back(inv);
                }

                // for(size_t i = 0; i < temp.size(); i++) {
                //     std::cout << temp.at(i) << std::endl;
                // }
                // if(inverse) {
                //     std::cout << std::endl;
                //     for(size_t i = 0; i < temp.size(); i++) {
                //         std::cout << inv.at(i) << std::endl;
                //     }
                //     std::cout << std::endl;
                // }
            }
            // clear window to fill it with new signal values
            dct_window.clear();
        }
    }

    if(transformed.size() == 0) {
        std::cout << "No results written, is your dct window "
                     "longer than your file?" << std::endl;
    }
}
