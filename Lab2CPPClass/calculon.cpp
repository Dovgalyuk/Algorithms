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
    
    void execute(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }
        
        std::string token;
        bool reading_data = true;
        
        while (file >> token) {
            if (reading_data) {
                std::istringstream iss(token);
                Data value;
                if (iss >> value && iss.eof()) {
                    size_t current_size = input_data_.size();
                    input_data_.resize(current_size + 1);
                    input_data_.set(current_size, value);
                } else {
                    reading_data = false;
                    executeCommand(token);
                }
            } else {
                executeCommand(token);
            }
        }
        
        file.close();
    }
    
private:
    void executeCommand(const std::string& command) {
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
        // ...
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <data_and_script_file>" << std::endl;
        return 1;
    }
    
    std::string filename = argv[1];
    
    CalculonInterpreter interpreter;
    interpreter.execute(filename);
    std::cout << std::endl;
    
    return 0;
}