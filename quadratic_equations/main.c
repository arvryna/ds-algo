#include <assert.h>
#include <math.h>
#include <stdio.h>

enum RootType {
    REAL_ROOTS_WITH_DIFFERENT_VALUES = 1,
    REAL_ROOTS_WITH_SAME_VALUES = 2,
    IMAGINARY_ROOTS = 3
};

// Quadratic equation has three coefficients
// ax2 + bx + c = 0
struct Coefficients {
    double first;
    double second;
    double third;
};

struct Solution {
    enum RootType type;
    double first_root;
    double second_root;
    double real_part;
    double imaginary_part;
};

enum RootType find_root_type(double discriminant) {
    if (discriminant > 0) {
        return REAL_ROOTS_WITH_DIFFERENT_VALUES;

    } else if (discriminant == 0) {
        return REAL_ROOTS_WITH_SAME_VALUES;

    } else {
        return IMAGINARY_ROOTS;
    }
}

double calculate_discriminant(struct Coefficients coef) {
    return (coef.second * coef.second) - (4 * coef.first * coef.third);
}

struct Solution solve_quadatic_equation(struct Coefficients coef) {
    double discriminant = calculate_discriminant(coef);

    struct Solution solution;
    solution.type = find_root_type(discriminant);

    switch (solution.type) {
        case REAL_ROOTS_WITH_DIFFERENT_VALUES:
            solution.first_root = (-coef.second + sqrt(fabs(discriminant))) / (2 * coef.first);
            solution.second_root = (-coef.second - sqrt(fabs(discriminant))) / (2 * coef.first);
            break;

        case REAL_ROOTS_WITH_SAME_VALUES:
            solution.first_root = solution.second_root = -coef.second / (2 * coef.first);
            break;

        case IMAGINARY_ROOTS:
            solution.real_part = -coef.second / (2 * coef.first);
            solution.imaginary_part = sqrt(fabs(discriminant)) / (2 * coef.first);
            break;

        default:
            break;
    }
    return solution;
}

void print_solution(struct Solution solution) {
    switch (solution.type) {

        case REAL_ROOTS_WITH_DIFFERENT_VALUES:
            printf("Roots are real and different: \n");
            printf("First root: %lf\n", solution.first_root);
            printf("Second root: %lf\n", solution.second_root);
            break;

        case REAL_ROOTS_WITH_SAME_VALUES:
            printf("Roots are real and same: \n");
            printf("Root: %lf\n", solution.first_root);
            break;

        case IMAGINARY_ROOTS:
            printf("Roots are complex and different \n");
            printf("First root: %lf + %lfi\n", solution.real_part, solution.imaginary_part);
            printf("Second root: %lf - %lfi\n", solution.real_part, solution.imaginary_part);
            break;

        default:
            break;
    }
}

struct Coefficients equation_input() {
    printf("Enter co-efficient of quadratic equation: a b c (with spaces): ");

    struct Coefficients coef;
    scanf("%lf %lf %lf", &coef.first, &coef.second, &coef.third);

    assert(coef.first != 0 || coef.second != 0 || coef.third != 0);

    return coef;
}

struct Solution solve_equation(struct Coefficients coef) {
    return solve_quadatic_equation(coef);
}

void equation_output(struct Solution solution) {
    print_solution(solution);
}

int main() {
    struct Coefficients coef = equation_input();
    struct Solution solution = solve_equation(coef);
    equation_output(solution);
    return 0;
}
