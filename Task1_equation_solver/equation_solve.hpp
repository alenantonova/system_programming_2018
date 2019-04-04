/**
 * @file equation_solve.hpp
 * @brief Содержит реализацию функции для решения квадратных уравнений, а так же тестов для нее.
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include<limits>
#define INF std::numeric_limits<int>::max()

const double EPSILON = 0.00000001;

bool is_zero(double x)
{
    return std::abs(x) < EPSILON;
}

/**
 * @function solve_equation(double a, double b, double c, std::vector<double> *roots)
 * @brief Функция для решения квадратных уравнений вида ax^2 + bx + c = 0
 * @param [in] a - коэффициент при x^2
 * @param [in] b - коэффициент при x
 * @param [in] c - свободный член
 * @param [in] roots - указатель на массив, в который фуекция запишет корни уравнения (если они есть)
 * @note Если размер массива после завершения работы функции равен 3, то уравнение имеет бесконечно много корней.
 */
int solve_equation(double a, double b, double c, std::vector<double> *roots) {
    if (is_zero(a)) {
        if (!is_zero(b)) {
            double x = (-c)/b;
            if (is_zero(x)) {
                x = 0;
            }
            roots->push_back(x);
        } else {
            if (!is_zero(c)) {
                return 0;
            }
            return INF;
        }
        return 1;
    }

    if (is_zero(c)) {
        roots->push_back(0);
        if (!is_zero(b)) {
            roots->push_back((-b) / a);
            return 2;
        }
        return 1;
    }

    double d = b*b - 4*a*c;

    if (is_zero(d)) {
        double x = (-b)/(2*a);
        if (x == 0) {
            x = 0;
        }
        roots->push_back(x);
        return 1;
    } else if (d > 0) {
        double x1 = (-b + sqrt(d))/(2*a);
        if (x1 == 0) {
            x1 = 0;
        }
        double x2 = (-b - sqrt(d))/(2*a);
        if (x2 == 0) {
            x2 = 0;
        }
        roots->push_back(x1);
        roots->push_back(x2);
        return 2;
    }
    return 0;
}

/// Функция, тестирующая случай наличия двух несовпадающих корней у уравнения.
void test_a2_b3_c1() {
    std::vector<double> roots;
    int ans = solve_equation(2, 3, 1, &roots);
    assert(ans == 2);
    assert(roots[0] == -0.5);
    assert(roots[1] == -1);
}

///Функция, тестирующая случай налисчия бесконечного множества кореней у уравнения.
void test_a0_b0_c0() {
    std::vector<double> roots;
    int ans = solve_equation(0, 0, 0, &roots);
    assert(ans == INF);
}

///Функция, тестирующая случай линейного уравнения.
void test_a0_b3_c12() {
    std::vector<double> roots;
    int ans = solve_equation(0, 3, 12, &roots);
    assert(ans == 1);
    assert(roots[0] == -4);
}


