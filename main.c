#include <math.h>
#include <assert.h>
#include <stdio.h>

enum RootType {
    REAL_ROOTS_WITH_DIFFERENT_VALUES = 1,
    REAL_ROOTS_WITH_SAME_VALUES,
    IMAGINARY_ROOTS
};

struct Solution {
    enum RootType type;
    double first_root;
    double second_root;
    double real_part;
    double imaginary_part;
};

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

double calculate_discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

enum RootType find_root_type(double discriminant) {
    if (discriminant > 0) {
        return REAL_ROOTS_WITH_DIFFERENT_VALUES;
    } else if (discriminant == 0) {
        return REAL_ROOTS_WITH_SAME_VALUES;
    } else {
        return IMAGINARY_ROOTS;
    }
}

struct Solution solve_quadatic_equation(double a, double b, double c) {
    double discriminant = calculate_discriminant(a, b, c);
    struct Solution solution;
    solution.type = find_root_type(discriminant);
    switch (solution.type) {
        case REAL_ROOTS_WITH_DIFFERENT_VALUES:
            solution.first_root = (-b + sqrt(fabs(discriminant))) / (2 * a);
            solution.second_root = (-b - sqrt(fabs(discriminant))) / (2 * a);
            break;
        case REAL_ROOTS_WITH_SAME_VALUES:
            solution.first_root = solution.second_root = -b / (2 * a);
            break;
        case IMAGINARY_ROOTS:
            solution.real_part = -b / (2 * a);
            solution.imaginary_part = sqrt(fabs(discriminant)) / (2 * a);
            break;
        default:
            break;
    }
    return solution;
}

void solver() {
    double a, b, c;
    printf("Enter co-efficient of quadratic equation: a b c (with spaces): ");
    scanf("%lf %lf %lf", &a, &b, &c);
    assert(a!=0);
    assert(b!=0);
    assert(c!=0);
    struct Solution solution = solve_quadatic_equation(a, b, c);
    print_solution(solution);
}

int main() {
    solver();
    return 0;
}
