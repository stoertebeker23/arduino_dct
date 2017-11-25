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
    
    drawGraphs();
    
    ImGui::ShowTestWindow();
        
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
    
    // int sample_rate = 10000;
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
            } else {
                transformed.push_back(temp);
                if(inverse) {
                    inverse_dct.push_back(inv);
                }
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

// Function that reads data from a subvector of the transformed vector
float values_getter(void* data, int index) {
    double* d = (double*)data;
    return d[index];
}

void MainWindow::drawGraphs() {
    if(transformed.empty()) {
        return;
    }
    
    for(vector<double>& vec : transformed) {
        const char* label = "DCT";
        void* data = (void*)&vec[0];
        int values_count = vec.size();
        int values_offset = 0;
        const char* overlay_text = NULL;
        float scale_min = -1.f;
        float scale_max = 1.f;
        ImVec2 graph_size(0, 80);
        
        ImGui::PlotHistogram(label, values_getter, data, values_count, values_offset,
                             overlay_text, scale_min, scale_max, graph_size);
    }
}
