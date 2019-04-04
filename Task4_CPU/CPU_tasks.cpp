#include "CPU.hpp"

void get_fact() {
    CPU proc("../factorial.txt");
    proc.execute();
}


void solve_equation() {
    CPU proc("../equation.txt");
    proc.execute();
}
/*int main() {
    try {
        get_fact();
        solve_equation();
    }
    catch(WrongInputException e) {
        std::cout << e.what();
        return 1;
    }
    return 0;
}*/
