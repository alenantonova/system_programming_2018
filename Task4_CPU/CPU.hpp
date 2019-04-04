#include <iostream>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <map>
#include <vector>

class WrongInputException : public std::exception {
public:
    std::string type_of_ex;
    WrongInputException(std::string str) {
        type_of_ex = str;
    }
    std::string what() {
        return "Wrong input: " + type_of_ex;
    }
};

std::vector<double> pars_args(int mode);

enum comands {IN = 1, OUT, PUSH, POP, PUT, GET, WRITE, ADD, SUB, MUL, DIV, SQRT,
    ISLESS, ISGREAT, ISEQ, NOTEQ, JUMP, END, COMMENT, ARGS};
extern std::vector<double> buff;
extern std::map<int, int> points;
extern std::vector<std::string> comments;

class Assembler {
    std::vector<double> cmd;
public:
    Assembler(std::istream &in);
    std::vector<double> get_instructions();
};

class Disassembler {
    std::vector<std::string> inv_cmd;
public:
    Disassembler(std::vector<double > comands);
    void make_file(std::ostream &out);
};

class CPU {
    std::stack<double> s;
    std::vector<double> instructions;
public:
    CPU(std::string filepath);
    void execute();
};