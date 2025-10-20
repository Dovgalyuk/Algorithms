#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include "stack.h"
#include "vector.h"

class CalculonInterpreter {
private:
    Stack stack_;
    Vector input_data_;
    size_t input_index_;
    Data loop_variable_;
    std::vector<std::string> commands_;
    size_t command_index_;
    bool in_conditional_block_;
    bool conditional_executed_;
    size_t repeat_start_index_;
    
public:
    CalculonInterpreter() : input_index_(0), loop_variable_(0), command_index_(0), 
                           in_conditional_block_(false), conditional_executed_(false), 
                           repeat_start_index_(0) {}
    
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
                    
                    commands_.push_back(token);
                }
            } else {
                commands_.push_back(token);
            }
        }
        
        file.close();
        
        while (command_index_ < commands_.size()) {
            executeCommand(commands_[command_index_]);
            command_index_++;
        }
    }
    
private:
    void executeCommand(const std::string& command) {
        if (in_conditional_block_ && !conditional_executed_) {
            if (command == "end") {
                in_conditional_block_ = false;
                conditional_executed_ = false;
            }
            return;
        }
        
        if (command == "repeat") {
            if (loop_variable_ > 0) {
                loop_variable_--;
                command_index_ = repeat_start_index_ - 1;
                return;
            }
        }
        
        if (command == "add") {
            if (!stack_.empty()) {
                Data b = stack_.get();
                stack_.pop();
                if (!stack_.empty()) {
                    Data a = stack_.get();
                    stack_.pop();
                    stack_.push(a + b);
                } else {
                    stack_.push(b);
                }
            }
        } else if (command == "sub") {
            if (!stack_.empty()) {
                Data b = stack_.get();
                stack_.pop();
                if (!stack_.empty()) {
                    Data a = stack_.get();
                    stack_.pop();
                    stack_.push(a - b);
                } else {
                    stack_.push(b);
                }
            }
        } else if (command == "mul") {
            if (!stack_.empty()) {
                Data b = stack_.get();
                stack_.pop();
                if (!stack_.empty()) {
                    Data a = stack_.get();
                    stack_.pop();
                    stack_.push(a * b);
                } else {
                    stack_.push(b);
                }
            }
        } else if (command == "div") {
            if (!stack_.empty()) {
                Data b = stack_.get();
                stack_.pop();
                if (!stack_.empty()) {
                    Data a = stack_.get();
                    stack_.pop();
                    if (b != 0) {
                        stack_.push(a / b);
                    }
                } else {
                    stack_.push(b);
                }
            }
        } else if (command == "sqrt") {
            if (!stack_.empty()) {
                Data value = stack_.get();
                stack_.pop();
                stack_.push(static_cast<Data>(std::sqrt(value)));
            }
        } else if (command == "sq") {
            if (!stack_.empty()) {
                Data value = stack_.get();
                stack_.pop();
                stack_.push(value * value);
            }
        } else if (command == "get") {
            if (input_index_ < input_data_.size()) {
                stack_.push(input_data_.get(input_index_));
                input_index_++;
            }
        } else if (command == "peek") {
            if (!stack_.empty()) {
                std::cout << stack_.get() << " ";
            }
        } else if (command == "cond") {
            if (!stack_.empty()) {
                Data b = stack_.get();
                stack_.pop();
                if (!stack_.empty()) {
                    Data a = stack_.get();
                    stack_.pop();
                    
                    if (a == b) {
                        in_conditional_block_ = true;
                        conditional_executed_ = true;
                    } else {
                        in_conditional_block_ = true;
                        conditional_executed_ = false;
                    }
                } else {
                    stack_.push(b);
                }
            }
        } else if (command == "end") {
            in_conditional_block_ = false;
            conditional_executed_ = false;
        } else if (command == "setr") {
            if (!stack_.empty()) {
                loop_variable_ = stack_.get();
                stack_.pop();
                repeat_start_index_ = command_index_ + 1;
            }
        }
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