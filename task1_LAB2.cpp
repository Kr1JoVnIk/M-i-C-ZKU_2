#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// 1. алгоритм перебора возможных делителей
vector<long long> trialDivision(long long n) {
    vector<long long> factors;
    for (long long d = 2; d * d <= n; ++d) {
        while (n % d == 0) {
            factors.push_back(d);
            n /= d;
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
    return factors;
}

// проверка, является ли число точным квадратом
bool isSquare(long long x, long long& root) {
    if (x < 0) return false;
    root = static_cast<long long>(sqrt(x));
    return root * root == x;
}

// 2. метод факторизации Ферма (n = (a - b)(a + b))
void fermatFactorization(long long n, vector<long long>& factors) {
    if (n <= 1) return;

    // Выделяем чётность
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }
    if (n == 1) return;

    long long a = static_cast<long long>(ceil(sqrt(n)));
    long long b2 = a * a - n;
    long long b = 0;

    while (!isSquare(b2, b)) {
        a++;
        b2 = a * a - n;
    }

    long long p = a - b;
    long long q = a + b;

    if (p == 1) {
        factors.push_back(q);
    }
    else {
        fermatFactorization(p, factors);
        fermatFactorization(q, factors);
    }
}

void printFactors(const vector<long long>& factors) {
    for (size_t i = 0; i < factors.size(); ++i) {
        cout << factors[i] << (i + 1 < factors.size() ? " * " : "");
    }
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    long long n;
    cout << "ЗАДАНИЕ 1: РЕАЛИЗОВАТЬ АЛГОРИТМ ФАКТОРИЗАЦИИ ЧИСЛА\n";
    cout << "Введите нечетное/составное число для факторизации (например, 10017959 или 5959): ";
    if (!(cin >> n) || n <= 1) {
        cout << "Некорректный ввод!\n";
        return 1;
    }

    // время перебора делителей
    auto start1 = high_resolution_clock::now();
    vector<long long> factorsTrial = trialDivision(n);
    auto end1 = high_resolution_clock::now();
    duration<double, milli> timeTrial = end1 - start1;

    // время метода Ферма
    auto start2 = high_resolution_clock::now();
    vector<long long> factorsFermat;
    fermatFactorization(n, factorsFermat);
    auto end2 = high_resolution_clock::now();
    duration<double, milli> timeFermat = end2 - start2;

   
    cout << "\nРезультаты\n";
    cout << "1. Перебор делителей: ";
    printFactors(factorsTrial);
    cout << "   Время выполнения: " << fixed << setprecision(4) << timeTrial.count() << " ms\n\n";

    cout << "2. Метод Ферма: ";
    printFactors(factorsFermat);
    cout << "   Время выполнения: " << fixed << setprecision(4) << timeFermat.count() << " ms\n\n";

    cout << "Сравнительный анализ\n";
    if (timeTrial.count() < timeFermat.count()) {
        cout << "Перебор делителей оказался быстрее на "
            << (timeFermat.count() - timeTrial.count()) << " ms.\n";
    }
    else {
        cout << "Метод Ферма оказался быстрее на "
            << (timeTrial.count() - timeFermat.count()) << " ms.\n";
    }
    cout << "(Примечание: Метод Ферма наиболее эффективен, когда множители близки к sqrt(n)).\n";

    return 0;
}