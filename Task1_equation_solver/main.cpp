#include "equation_solve.hpp"
#include <string>
#include <cctype>
#include <exception>
#include <algorithm>

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

void pars_args(std::vector<double> &coef) {
    std::string s;
    std::getline(std::cin, s);
    std::vector<double> nums(4);
    std::vector<int> pos(4);
    int res = sscanf(s.c_str(), " %n%lf %n%lf %n%lf %n%lf", &pos[0], &nums[0], &pos[1], &nums[1],
                     &pos[2], &nums[2], &pos[3], &nums[3]);

    if (res > 3) {
        WrongInputException e("too much coefficients");
        throw e;
    }

    if (res == 3) {
        coef.push_back(nums[0]);
        coef.push_back(nums[1]);
        coef.push_back(nums[2]);
        return;
    }

    if (isalpha(s[pos[res]]) || !isalnum(s[pos[res]])) {
        WrongInputException e("has letter or punctuation mark");
        throw e;
    }
}

int main() {
    test_a0_b0_c0();
    test_a0_b3_c12();
    test_a2_b3_c1();
    std::vector<double> coef;
    std::cout << "Enter the coefficients of equation" << std::endl;
    try {
        pars_args(coef);
        std::vector<double> answer;
        int num_of_roots = solve_equation(coef[0], coef[1], coef[2], &answer);
        std::cout << "Answer:" << std::endl;
        if (num_of_roots > 2) {
            std::cout << "Equation has infinitely many roots" << std::endl;
        } else if (num_of_roots == 0) {
            std::cout << "Equation has no roots" << std::endl;
        } else {
            size_t start = answer.size() - num_of_roots;
            int i = 1;
            while (num_of_roots > 0) {
                std::cout << "x" << i << " = " << answer[start + (i-1)] << std::endl;
                i++;
                num_of_roots--;
            }
        }
    }
    catch(WrongInputException e) {
        std::cout << e.what();
        return 1;
    }
    return 0;
}
