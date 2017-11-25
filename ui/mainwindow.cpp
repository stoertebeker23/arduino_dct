#include "mainwindow.h"
#include "imgui_impl_glfw_gl3.h"

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
        cout << c << endl;
        
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
