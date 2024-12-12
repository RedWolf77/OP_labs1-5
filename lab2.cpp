// Вариант 5

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

void underscore();
double f(double x);
std::vector<double> func_lab2(double E);
std::vector<double> func_lab1(double E);

int main() {
    setlocale(LC_ALL, "Russian");
    double E[3] = {0.1, 0.01, 0.0001};
    std::vector<double> f1;
    std::vector<double> f2;
    std::string s = "-";

    std::string strings1[3];
    std::string strings2[3];
    std::string strings3[3];

    for (int i = 0; i < 3; i++) {
        f1 = func_lab1(E[i]);
        s = "M=" + std::to_string(f1[0]) + " "
            + "k=" + std::to_string(int(f1[1])) + " " 
            + "Ep=" + std::to_string(f1[2]);
        strings1[i] = s;

        f2 = func_lab2(E[i]);
        s = "M=" + std::to_string(f2[0]) + " "
            + "k=" + std::to_string(int(f2[1])) + " " 
            + "Ep=" + std::to_string(f2[2]);
        strings2[i] = s;

        s = "dM=" + std::to_string(std::abs(f1[0] - f2[0])) + " "
            + "k1/k2=" + std::to_string(int(f1[1]) / int(f2[0])) + " " 
            + "dEp=" + std::to_string(std::abs(f1[2] - f2[2]));
        strings3[i] = s;
    }
    underscore();
    std::cout << "|" <<  std::setw(18) << " | " 
                     << std::setw(33) << "Ep=0.1              " << "|"
                     << std::setw(33) << "Ep=0.01             " << "|"
                     << std::setw(33) << "Ep=0.0001           " << "|" << std::endl;
    underscore();
    std::cout << "|" <<  std::setw(18) << " Metod pol.d. | " 
                     << std::setw(33) << strings1[0] << "|"
                     << std::setw(33) << strings1[1] << "|"
                     << std::setw(33) << strings1[2] << "|" << std::endl;
    underscore();
    std::cout << "|" <<  std::setw(18) << " Metod sek. | " 
                     << std::setw(33) << strings2[0] << "|"
                     << std::setw(33) << strings2[1] << "|"
                     << std::setw(33) << strings2[2] << "|" << std::endl;
    underscore();
    std::cout << "|" <<  std::setw(18) << " | " 
                     << std::setw(33) << strings3[0] << "|"
                     << std::setw(33) << strings3[1] << "|"
                     << std::setw(33) << strings3[2] << "|" << std::endl;
    underscore();            
}

void underscore() {
    for (int i = 0; i < 121; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

// f(x) = |sin(x+1)| - x + 1 - упрощенная 
double f(double x) {
    return std::abs(std::sin(x + 1)) - x + 1;
}

std::vector<double> func_lab2(double E) {
    double L = 0;            // левая граница
    double R = L;            // правая граница

    std::vector<double> result;

    do {
        R += 0.5;
        L -= 0.5;
    } while (f(L) * f(R) > 0 && R <= 1000);

    if (f(L) * f(R) > 0) {
        std::cout << "Интервал не найден." << std::endl;
        return result;
    }

    double M = 0;       // пересечения секущей с Ox интервала
    int iterations = 0; // количество итераций
    double fM = 0;      // значение f(M)

    while (true) {
        M = L - f(L) * (R - L) / (f(R) - f(L));    // формула прямой, проходящей через две точки (y=0)
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
        result.push_back(M);
        result.push_back(double(iterations));
        result.push_back(fM);
    } 
    else {
        std::cout << "Заданная точность не достигнута - превышен лимит итераций." << std::endl;
    }

    return result;
}

// функция, выполняющая задание ЛР1
std::vector<double> func_lab1(double E) {
    double L = -10;            // левая граница
    double R = L;              // правая граница

    std::vector<double> result;

    do {
        R += 0.5;
    } while (f(L) * f(R) > 0 && R <= 1000);

    if (f(L) * f(R) > 0) {
        std::cout << "Интервал не найден." << std::endl;
        return result;
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
        result.push_back(M);
        result.push_back(double(iterations));
        result.push_back(fM);
    } 
    else {
        std::cout << "Заданная точность не достигнута - превышен лимит итераций." << std::endl;
    }

    return result;
}
