// Вариант 5

#include <iostream>
#include <cmath>

// f(x) = |sin(x+1)| - x + 1 - упрощенная 
double f(double x) {
    return std::abs(std::sin(x + 1)) - x + 1;
}

int main() {
    double L = -10;            // левая граница
    double R = L;              // правая граница
    double E = 0.001;          // точность

    do {
        R += 0.5;
    } while (f(L) * f(R) > 0 && R <= 1000);

    if (f(L) * f(R) > 0) {
        std::cout << "Интервал не найден." << std::endl;
        return 1;
    }

    double M = 0;       // середина интервала
    int iterations = 0; // количество итераций
    double fM = 0;      // значение f(M)

    while (true) {
        M = (L + R) / 2;    
        fM = f(M);          
        iterations++;

        if (std::abs(fM) < E || iterations >= 1000) {
            break;
        }

        if (fM > 0) {
            L = M;
        } 
        else {
            R = M;
        }
    }

    if (std::abs(fM) < E) {
        std::cout << "Корень найден.\nM = " << M << ", k = " << iterations << ", Ep = " << fM << std::endl;
    } 
    else {
        std::cout << "Заданная точность не достигнута - превышен лимит итераций." << std::endl;
    }

    return 0;
}
