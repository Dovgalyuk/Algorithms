#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>
#include "stack.h"  

static int parseRegister(const char* tok) {
    if (strlen(tok) != 1) {
        return -1;  
    }

    char reg = tok[0];  

    switch (reg) {
    case 'A': return 0;  
    case 'B': return 1; 
    case 'C': return 2; 
    case 'D': return 3;  
    default: return -1;  
    }
}

static bool isRegisterToken(const char* tok) {
    if (!tok) return false;  
    if (strlen(tok) != 1) return false;  
    char reg = tok[0];  
    return (reg == 'A' || reg == 'B' || reg == 'C' || reg == 'D');
}

static bool parseInt64(const char* tok, int64_t* out) {
    if (!tok || !out) return false;  

    while (*tok == ' ' || *tok == '\t' || *tok == '\n' || *tok == '\r') ++tok;
    if (*tok == '\0') return false;  

    char* endptr = NULL;  
    long long v = strtoll(tok, &endptr, 10); 

    if (endptr == tok) return false; 

    while (*endptr == ' ' || *endptr == '\t') ++endptr;
    if (*endptr != '\0') return false; 

    *out = (int64_t)v; 
    return true; 
}

static void executePush(Stack* st, const char* arg, int64_t regs[4]) {
    if (!st || !arg || !regs) return;  

    int64_t value = 0;  

    if (isRegisterToken(arg)) {
        int idx = parseRegister(arg);  
        if (idx < 0) return; 
        value = regs[idx]; 
    }
    else {
        if (!parseInt64(arg, &value)) return; 
    }

    stack_push(st, (Data)(intptr_t)value); 
}

static void executePop(Stack* st, const char* arg, int64_t regs[4]) {
    if (!st || !arg || !regs) return;  

    int idx = parseRegister(arg); 
    if (idx < 0) return;  

    if (stack_empty(st)) return; 

    Data top = stack_get(st);  
    regs[idx] = (int64_t)(intptr_t)top;  
    stack_pop(st);  
}

static void executeBinaryOp(Stack* st, const char* op, const char* dstReg, int64_t regs[4]) {
    if (!st || !op || !dstReg || !regs) return;  
    int idx = parseRegister(dstReg);  
    if (idx < 0) return; 

    if (stack_empty(st)) return;  
    int64_t x = (int64_t)(intptr_t)stack_get(st);  
    stack_pop(st);  

    if (stack_empty(st)) return;  
    int64_t y = (int64_t)(intptr_t)stack_get(st); 
    stack_pop(st);  

    int64_t res = 0; 

    if (strcmp(op, "add") == 0) {
        res = y + x;  
    }
    else if (strcmp(op, "mul") == 0) {
        res = y * x;  
    }
    else if (strcmp(op, "sub") == 0) {
        res = y - x;  
    }
    else {
        return;  
    }

    regs[idx] = res;  
}

static void processLine(Stack* st, const char* line, int64_t regs[4]) {
    if (!st || !line || !regs) return;  

    char buf[256];  
    size_t len = strlen(line);  

    if (len >= sizeof(buf)) len = sizeof(buf) - 1;
    memcpy(buf, line, len);  
    buf[len] = '\0';  

    if (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        buf[len - 1] = '\0';  
    }

    char* s = buf;
    while (*s == ' ' || *s == '\t') ++s;
    if (*s == '\0') return; 

    char cmd[16] = { 0 };  
    char arg1[64] = { 0 };  

    int n = sscanf(s, "%15s %63s", cmd, arg1);
    if (n <= 0) return;  

    if (strcmp(cmd, "push") == 0) {
        if (n >= 2) executePush(st, arg1, regs); 
        return;
    }

    if (strcmp(cmd, "pop") == 0) {
        if (n >= 2) executePop(st, arg1, regs);  
        return;
    }

    if (strcmp(cmd, "add") == 0 || strcmp(cmd, "mul") == 0 || strcmp(cmd, "sub") == 0) {
        if (n >= 2) executeBinaryOp(st, cmd, arg1, regs);  
        return;
    }
}

static void printRegisters(const int64_t regs[4]) {
    std::cout << "A = " << regs[0] << std::endl;  
    std::cout << "B = " << regs[1] << std::endl;  
    std::cout << "C = " << regs[2] << std::endl;  
    std::cout << "D = " << regs[3] << std::endl;  
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return 1;  
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::perror("fopen");  
        return 1;  
    }

    int64_t regs[4] = { 0, 0, 0, 0 };  

    Stack* st = stack_create();
    if (!st) {
        std::cerr << "Failed to create stack" << std::endl;
        return 1;  
    }

    std::string line;  

    while (std::getline(input, line)) {
        processLine(st, line.c_str(), regs); 
    }

    printRegisters(regs);  

    stack_delete(st);  

    return 0;  
}