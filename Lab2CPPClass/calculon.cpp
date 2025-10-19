#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "stack.h"
#include "vector.h"

class CalculonInterpreter {
private:
    Stack stack_;
    Vector input_data_;
    size_t input_index_;
    
public:
    CalculonInterpreter() : input_index_(0) {}
    
    void loadInputData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening input file: " << filename << std::endl;
            return;
        }
        
        Data value;
        while (file >> value) {   
            input_data_.resize(input_data_.size() + 1);    
            input_data_.set(input_data_.size() - 1, value);
        }
        
        file.close();
    }
    
    void executeScript(const std::string& script) {
        std::istringstream iss(script);
        std::string command;
        
        while (iss >> command) {
            if (command == "peek") {
                if (!stack_.empty()) {
                    std::cout << stack_.get() << " ";
                }
            } else if (command == "setr") {
                if (input_index_ < input_data_.size()) {
                    size_t reverse_index = input_data_.size() - 1 - input_index_;
                    stack_.push(input_data_.get(reverse_index));
                    input_index_++;
                }
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <script_file> <input_file>" << std::endl;
        return 1;
    }
    
    std::string script_file = argv[1];
    std::string input_file = argv[2];
    
    std::ifstream script_stream(script_file);
    if (!script_stream.is_open()) {
        std::cerr << "Error opening script file: " << script_file << std::endl;
        return 1;
    }
    
    std::string script_content;
    std::string line;
    while (std::getline(script_stream, line)) {
        script_content += line + " ";
    }
    script_stream.close();
    
    CalculonInterpreter interpreter;
    interpreter.loadInputData(input_file);
    interpreter.executeScript(script_content);
    std::cout << std::endl;
    
    return 0;
}
