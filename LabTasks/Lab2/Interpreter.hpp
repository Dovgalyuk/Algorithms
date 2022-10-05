#ifndef H_INTERPRETER
#define H_INTERPRETER

class Interpreter {
    private:
        Stack *stack;
        std::string str;
    public:
        Interpreter();
        void setString(const std::string str);
        void run();
        ~Interpreter ();
};

#endif