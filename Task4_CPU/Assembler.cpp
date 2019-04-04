#include "CPU.hpp"

Assembler::Assembler(std::istream &in) {
    std::string comand;
    while (in >> comand) {
        if (comand == "IN") {
            cmd.push_back(IN);
            continue;
        }
        if (comand == "OUT") {
            cmd.push_back(OUT);
            continue;
        }
        if (comand == "PUSH") {
            double num;
            in >> num;
            cmd.push_back(PUSH);
            cmd.push_back(num);
            continue;
        }
        if (comand == "POP") {
            cmd.push_back(POP);
            continue;
        }
        if (comand == "PUT") {
            double num;
            in >> num;
            cmd.push_back(PUT);
            cmd.push_back(num);
            continue;
        }
        if (comand == "GET") {
            cmd.push_back(GET);
            double num;
            in >> num;
            cmd.push_back(num);
            continue;
        }
        if (comand == "WRITE") {
            cmd.push_back(WRITE);
            double num;
            in >> num;
            cmd.push_back(num);
            continue;
        }
        if (comand == "ADD") {
            cmd.push_back(ADD);
            continue;
        }
        if (comand == "SUB") {
            cmd.push_back(SUB);
            continue;
        }
        if (comand == "MUL") {
            cmd.push_back(MUL);
            continue;
        }
        if (comand == "DIV") {
            cmd.push_back(DIV);
            continue;
        }
        if (comand == "SQRT") {
            cmd.push_back(SQRT);
            continue;
        }
        if (comand == "ISLESS") {
            cmd.push_back(ISLESS);
            double num1, num2;
            in >> num1;
            in >> num2;
            cmd.push_back(num1);
            cmd.push_back(num2);
            continue;
        }
        if (comand == "ISGREAT") {
            cmd.push_back(ISGREAT);
            double num1, num2;
            in >> num1;
            in >> num2;
            cmd.push_back(num1);
            cmd.push_back(num2);
            continue;
        }
        if (comand == "ISEQ") {
            cmd.push_back(ISEQ);
            double num1, num2;
            in >> num1;
            in >> num2;
            cmd.push_back(num1);
            cmd.push_back(num2);
            continue;
        }
        if (comand == "NOTEQ") {
            cmd.push_back(NOTEQ);
            double num1, num2;
            in >> num1;
            in >> num2;
            cmd.push_back(num1);
            cmd.push_back(num2);
            continue;
        }
        if (comand == "JUMP") {
            cmd.push_back(JUMP);
            int num;
            in >> num;
            cmd.push_back(num);
            continue;
        }
        if (comand == "END") {
            cmd.push_back(END);
            continue;
        }
        if (comand == "COMMENT") {
            cmd.push_back(COMMENT);
            int num;
            in >> num;
            cmd.push_back(num);
        }
        if (comand == "ARGS") {
            cmd.push_back(ARGS);
            int mode;
            in >> mode;
            cmd.push_back(mode);
        }
        if (comand == "POINT") {
            int num;
            in >> num;
            points.insert(std::make_pair(num, cmd.size()));
        }
    }
}

std::vector<double> Assembler::get_instructions() {
    return cmd;
}

Disassembler::Disassembler(std::vector<double> comands) {
    for (int i = 0; i < comands.size(); i++) {
        switch(int(comands[i])) {
            case IN:
                inv_cmd.push_back("IN\n");
                break;
            case OUT:
                inv_cmd.push_back("OUT\n");
                break;
            case PUSH:
                inv_cmd.push_back("PUSH " + std::to_string(comands[++i]) + "\n");
                break;
            case POP:
                inv_cmd.push_back("POP\n");
                break;
            case PUT:
                inv_cmd.push_back("PUT" + std::to_string(comands[++i]) + "\n");
                break;
            case GET:
                inv_cmd.push_back("GET" + std::to_string(comands[++i]) + "\n");
                break;
            case WRITE:
                inv_cmd.push_back("WRITE" + std::to_string(comands[++i]) + "\n");
                break;
            case ADD:
                inv_cmd.push_back("ADD\n");
                break;
            case SUB:
                inv_cmd.push_back("SUB\n");
                break;
            case MUL:
                inv_cmd.push_back("MUL\n");
                break;
            case DIV:
                inv_cmd.push_back("DIV\n");
                break;
            case SQRT:
                inv_cmd.push_back("SQRT\n");
                break;
            case ISLESS:
                inv_cmd.push_back("ISLESS" + std::to_string(comands[++i]) + std::to_string(comands[++i]) + "\n");
                break;
            case ISGREAT:
                inv_cmd.push_back("ISGREAT" + std::to_string(comands[++i]) + std::to_string(comands[++i]) + "\n");
                break;
            case ISEQ:
                inv_cmd.push_back("ISEQ" + std::to_string(comands[++i]) + std::to_string(comands[++i]) + "\n");
                break;
            case NOTEQ:
                inv_cmd.push_back("NOTEQ" + std::to_string(comands[++i]) + std::to_string(comands[++i]) + "\n");
                break;
            case JUMP:
                inv_cmd.push_back("JUMP" + std::to_string(comands[++i]) + "\n");
                break;
            case END:
                inv_cmd.push_back("END\n");
                break;
            case COMMENT:
                inv_cmd.push_back("COMMENT" + std::to_string(comands[++i]) + "\n");
                break;
            case ARGS:
                inv_cmd.push_back("ARGS" + std::to_string(comands[++i]) + "\n");
                break;
        }
    }
}

void Disassembler::make_file(std::ostream &out) {
    for(int i = 0; i < inv_cmd.size(); ++i) {
        out << inv_cmd[i];
    }
}