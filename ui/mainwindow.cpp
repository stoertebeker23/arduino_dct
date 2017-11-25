#include "mainwindow.h"
#include "imgui_impl_glfw_gl3.h"
#include "../dct.h"

using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>
using std::strtod;
#include <cerrno>


MainWindow::MainWindow() {}

void MainWindow::draw() {
    ImGui::Begin("MainWindow");
    
    ImGui::Text("Paste your input here:");
    
    ImGui::InputTextMultiline("##source", inputText, IM_ARRAYSIZE(inputText),
        ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
        ImGuiInputTextFlags_AllowTabInput);
        
    if(!errors.empty()) {
        ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "%s", errors.c_str());
    }
    
    // last two args are step and step_fast
    // ImGui::InputInt("Sample Rate", &dct_settings.sample_rate, 100, 1000);
    if(ImGui::InputInt("Window Size", &dct_settings.window_size, 10, 100)) {
        dct_settings.window_size = std::max(dct_settings.window_size, 1);
    }
    if(ImGui::InputInt("Averaging (0 = disabled)", &dct_settings.averaging, 10, 100)) {
        dct_settings.averaging = std::max(dct_settings.averaging, 0);
    }
    ImGui::Checkbox("Calculate Inverse", &dct_settings.inverse);
    ImGui::Checkbox("Squareroot (take absolute value)", &dct_settings.squareroot);
        
    if(ImGui::Button("Calculate DCT")) {
        errors.clear();
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
    int line = 1;
    
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
            
            char* e;
            errno = 0;
            const double value = strtod(s.c_str(), &e);
            
            if (*e != '\0' ||  // error, we didn't consume the entire string
                errno != 0 )   // error, overflow or underflow
            {
                // fail
                errors += "Error in line " + std::to_string(line);
                errors += " (\"" + s + "\" is not a valid number)\n";
            } else {
                // success
                inputParsed.push_back(value);
            }
            
            s.clear();
            
            if(c == '\0') {
                break;
            }
            
            line++;
        } else {
            s += c;
        }
    }
}

void MainWindow::calcDCT() {
    if(inputParsed.size() == 0) {
        if(!errors.empty())
            errors += "\n";
        errors += "No input, nothing to do.\n";
        return;
    }
    
    transformed.clear();
    
    vector<double> dct_window;
    vector<vector<double>> inverse_dct;  // TODO make a private member

    for(size_t i = 0; i < inputParsed.size(); ++i) {
        // Read signal values to dct window...
        dct_window.push_back(inputParsed.at(i));
        // ...until window size is reached then...
        if (i > 0 && i % dct_settings.window_size == 0) {
            vector<double> temp = dct(dct_window, false, dct_settings.squareroot);
            vector<double> inv;
            
            if(dct_settings.inverse) {
                inv = dct(temp, true, dct_settings.squareroot);
            }
            
            if(dct_settings.averaging && transformed.size() > 1) {
                const int avg = dct_settings.averaging;
                vector<double> average = calc_avg(transformed, temp, avg);
                transformed.push_back(average);
            } else {
                transformed.push_back(temp);
                if(dct_settings.inverse) {
                    inverse_dct.push_back(inv);
                }
            }
            // clear window to fill it with new signal values
            dct_window.clear();
        }
    }

    if(transformed.size() == 0) {
        if(!errors.empty())
            errors += "\n";
        errors += "No results written, is your dct window longer than your file?\n";
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
