#include "DiffTree.hpp"

int main() {
    std::vector<std::string> exp = {"1/(x*y)", "x^4+2*x*y+8", "sin(x)+ln(x^(2*x+y)+7*x+y)"};
    freopen("/home/alyona/CLionProjects/ded/Differentiator/answer.txt", "w", stdout);
    for(int i = 0;  i < exp.size(); ++i) {
        write_ans(exp[i]);
    }
    //fclose(f);
    return 0;
}