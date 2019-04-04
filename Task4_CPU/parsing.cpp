#include "CPU.hpp"

std::vector<double> pars_args(int mode) {
    std::vector<double> args;
    std::string s;
    int size = 0;
    int res = 0;
    int right_number = 0;
    if (mode == 0) {
        std::cout << "Enter equation coefficients\n";
        size = 4;
        right_number = 3;
    } else if (mode == 1) {
        std::cout << "Enter number\n";
        size = 2;
        right_number = 1;
    }
    getline(std::cin, s);
    std::vector<double> nums(size);
    std::vector<int> pos(size);
    if (mode == 0) {
        res = sscanf(s.c_str(), " %n%lf %n%lf %n%lf %n%lf", &pos[0], &nums[0], &pos[1], &nums[1],
                     &pos[2], &nums[2], &pos[3], &nums[3]);
    } else {
        res = sscanf(s.c_str(), " %n%lf %n%lf", &pos[0], &nums[0], &pos[1], &nums[1]);
    }
    if (res > right_number) {
        WrongInputException e("too much numbers");
        throw e;
    }
    if (res == right_number) {
        if (mode == 1 && nums[0] < 0) {
            WrongInputException e("negative number for factorial");
            throw e;
        }
        for (int i = 0; i < right_number; ++i) {
            args.push_back(nums[i]);
        }
        return args;
    }
    if (isalpha(s[pos[res]]) || !isalnum(s[pos[res]])) {
        WrongInputException e("not enough numbers or wrong type of symbols");
        throw e;
    }
}