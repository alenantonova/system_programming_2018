#include "CPU.hpp"

std::vector<double> buff(7);
std::map<int, int> points;
std::vector<std::string> comments = {"Equation has no roots\n", "Equation has infinitely many roots\n",
                                     "Answer\n", "Wrong input\n"};


CPU::CPU(std::string filepath) {
    std::ifstream in;
    in.open(filepath);
    Assembler asem(in);
    instructions = asem.get_instructions();
}

void CPU::execute() {
    for (int i = 0; i < instructions.size(); ++i) {
        //std::cout << " i = " << i << std::endl;
        switch(int(instructions[i])) {
            case IN: {
                double num;
                std::cin >> num;
                s.push(num);
                break;
            }
            case OUT: {
                if (s.size() >=1) {
                    std::cout << s.top() << std::endl;
                }
                break;
            }
            case PUSH: {
                s.push(instructions[++i]);
                break;
            }
            case POP: {
                s.pop();
                break;
            }
            case PUT: {
                buff.push_back(instructions[++i]);
                break;
            }
            case GET: {
                s.push(buff[instructions[++i]]);
                break;
            }
            case WRITE: {
                buff[instructions[++i]] = s.top();
                break;
            }
            case ADD: {
                if (s.size() >= 2) {
                    double num1 = s.top();
                    s.pop();
                    double num2 = s.top();
                    s.pop();
                    s.push(num1 + num2);
                }
                break;
            }
            case SUB: {
                if (s.size() >= 2) {
                    double num1 = s.top();
                    s.pop();
                    double num2 = s.top();
                    s.pop();
                    s.push(num2 - num1);
                }
                break;
            }
            case MUL: {
                if (s.size() >= 2) {
                    double num1 = s.top();
                    s.pop();
                    double num2 = s.top();
                    s.pop();
                    s.push(num1 * num2);
                }
                break;
            }
            case DIV: {
                if (s.size() >= 2) {
                    double num1 = s.top();
                    s.pop();
                    double num2 = s.top();
                    s.pop();
                    s.push(num1 / num2);
                }
                break;
            }
            case SQRT: {
                double num = s.top();
                s.pop();
                s.push(sqrt(num));
                break;
            }
            case ISLESS: {
                if (buff[instructions[i+1]] < instructions[i+2]) {
                    s.push(true);
                } else {
                    s.push(false);
                }
                i += 2;
                break;
            }
            case ISGREAT: {
                if (buff[instructions[i+1]] > instructions[i+2]) {
                    s.push(true);
                } else {
                    s.push(false);
                }
                i += 2;
                break;
            }
            case ISEQ: {
                if(buff[instructions[i+1]] == instructions[i + 2]) {
                    s.push(true);
                } else {
                    s.push(false);
                }
                i += 2;
                break;
            }
            case NOTEQ: {
                if(buff[instructions[i+1]] != instructions[i+2]) {
                    s.push(true);
                } else {
                    s.push(false);
                }
                i += 2;
                break;
            }
            case JUMP: {
                if (s.top()) {
                    i = points[instructions[i+1]] - 1;
                } else {
                    i++;
                }
                s.pop();
                break;
            }
            case END: {
                for (int i = 0; i < 7; ++i) {
                    buff[i] = 0;
                }
                points.clear();
                i = instructions.size();
                break;
            }
            case COMMENT: {
                std::cout << comments[instructions[++i]];
                break;
            }
            case ARGS: {
                std::vector<double> args = pars_args(instructions[++i]);
                for(int i = 0; i < args.size(); ++i) {
                    buff[i] = args[i];
                }
            }
        }
    }
}

/*int main() {
    std::cout << "Enter path to input file or 'console'\n";
    std::string in_path;
    std::cin >> in_path;
    std::cout << "Enter path to output file or 'console'\n";
    std::string out_path;
    std::cin >> out_path;
    std::vector<double> instructions;
    //std::ifstream in;
    //std::ofstream out;//("/home/alyona/CLionProjects/ded/get_d.txt");"/home/alyona/CLionProjects/ded/linear_solve.txt"
    if(in_path != "console") {
        std::ifstream in;
        in.open(in_path);
        if (!in) {
            std::cout << "Error: open file" + in_path + " failed.\n";
        }
        Assembler a(in);
        instructions = a.get_instructions();
        std::cout << instructions.size() << " 111\n";
    } else {
        Assembler a(std::cin);
        instructions = a.get_instructions();
    }
    Disassembler d(instructions);
    for (int i = 0; i < instructions.size(); ++i) {
        std::cout << instructions[i] << std::endl;

    }
    std::cout << out_path << std::endl;
    if(out_path != "console") {
        std::ofstream out;
        out.open(out_path);
        if (!out) {
            std::cout << "Error: open file" + out_path + " failed.\n";
        }
        d.make_file(out);
    } else {
        //std::cout << "222\n";
        d.make_file(std::cout);
    }
    CPU cpu(instructions);
}*/