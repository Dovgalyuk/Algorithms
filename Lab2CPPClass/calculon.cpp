#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <vector>
#include "stack.h"

class ExecutionContext {
public:
    Stack stack;
    std::istream& input;
    std::ostream& output;
    size_t currentIndex = 0;

    // for cond & end commands
    bool skipMode = false;
    int skipLevel = 0;

    //for setr & repeat command
    int repeatCounter = 0;
    size_t repeatStartIndex = 0;
    bool inLoop = false;

    ExecutionContext(std::istream& in, std::ostream& out) : input(in), output(out) {}

    Data pop() {
        if (stack.empty())
        {
            throw std::runtime_error("Stack underflow");
        }
        Data value = stack.get();
        stack.pop();
        return value;
    }

    void push(Data value) {
        stack.push(value);
    }

    Data peek() {
        if (stack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return stack.get();
    }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(ExecutionContext& context) = 0;
};

class AddCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data firstValue = context.pop();
        Data secondValue = context.pop();
        context.push(firstValue + secondValue);
    }
};

class SubCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data firstValue = context.pop();
        Data secondValue = context.pop();
        context.push(firstValue - secondValue);
    }
};

class MulCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data firstValue = context.pop();
        Data secondValue = context.pop();
        context.push(firstValue * secondValue);
    }
};

class DivCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data firstValue = context.pop();
        Data secondValue = context.pop();

        if (secondValue == 0)
        {
            context.push(0);
            return;
        }
        

        context.push(firstValue / secondValue);
    }
};

class SqrtCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data lastValue = context.pop();
        
        if (lastValue < 0)
        {
            context.push(0);
        }
        
        double sqrtValue = std::sqrt(static_cast<double>(lastValue));
        Data result = static_cast<Data>(std::round(sqrtValue));
        context.push(result);
    }
};

class SqCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data lastValue = context.pop();
        
        context.push(lastValue * lastValue);
    }
};

class GetCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data userValue;

        if (context.input >> userValue)
        {
           context.push(userValue);
           return;
        } 
        else {
            context.push(0);
        }
        context.input.clear();
    }
};

class PeekCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        context.output << context.peek() << " ";
    }
};

class CondCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        if (context.skipMode)
        {
            context.skipLevel++;
            return;
        }
        
        Data a = context.pop();
        Data b = context.pop();

        if (a != b)
        {
            context.skipMode = true;
            context.skipLevel = 1;
            context.push(b);
        }
        
    }
};

class EndCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        if (context.skipMode) {
            context.skipLevel--;
            if (context.skipLevel == 0) {
                context.skipMode = false;
            }
        }
    }
};

class SetrCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        Data value = context.pop();
        context.repeatCounter = static_cast<int>(value);
        context.repeatStartIndex = context.currentIndex;
        context.inLoop = true;
    }
};

class RepeatCommand : public Command {
public:
    void execute(ExecutionContext& context) override {
        if (!context.inLoop)
        {
            throw std::runtime_error("repeat without setr");
        }
        
        if (context.repeatCounter > 0)
        {
            context.repeatCounter--;
            context.currentIndex = context.repeatStartIndex;
        } else {
            context.inLoop = false;
        }
    }
};

class CommandFactory {
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Command>()>> commands_;

public:
    CommandFactory() {
        registerCommand("add", []() { return std::make_unique<AddCommand>(); });
        registerCommand("sub", []() { return std::make_unique<SubCommand>(); });
        registerCommand("mul", []() { return std::make_unique<MulCommand>(); });
        registerCommand("div", []() { return std::make_unique<DivCommand>(); });
        registerCommand("sqrt", []() { return std::make_unique<SqrtCommand>(); });
        registerCommand("sq", []() { return std::make_unique<SqCommand>(); });
        registerCommand("get", []() { return std::make_unique<GetCommand>(); });
        registerCommand("peek", []() { return std::make_unique<PeekCommand>(); });
        registerCommand("cond", []() { return std::make_unique<CondCommand>(); });
        registerCommand("end", []() { return std::make_unique<EndCommand>(); });
        registerCommand("setr", []() { return std::make_unique<SetrCommand>(); });
        registerCommand("repeat", []() { return std::make_unique<RepeatCommand>(); });
    }

    void registerCommand(const std::string& name, std::function<std::unique_ptr<Command>()> creator) {
        commands_[name] = std::move(creator);
    }

    std:: unique_ptr<Command> createCommand(const std::string& name) const {
        auto it = commands_.find(name);
        if (it != commands_.end())
        {
            return it -> second();
        }
        return nullptr;
    }
};

std::vector<std::string> tokenize(const std::string& program) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(program);

    while (stream >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

class ProgramExecutor {
private:
    CommandFactory factory_;
    std::vector<std::string> tokens_;
public:
    ProgramExecutor(const std::string &program) {
        tokens_ = tokenize(program);
    }
    void execute() {
        ExecutionContext context(std::cin, std::cout);

        while (context.currentIndex < tokens_.size())
        {
            const std::string& token = tokens_[context.currentIndex];

            try
            {
                if (auto command = factory_.createCommand(token))
                {
                    command -> execute(context);
                } else {
                    double number = std::stod(token);
                    Data value = static_cast<Data>(number);
                    context.push(value);
                }
                
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
                return;
            }
            context.currentIndex++;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <data_and_script_file>" << std::endl;
        return 1;
    }
    
    std::ifstream file(argv[1]);
    
    if (!file)
    {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string program = buffer.str();

    ProgramExecutor executor(program);
    executor.execute();

    return 0;
}