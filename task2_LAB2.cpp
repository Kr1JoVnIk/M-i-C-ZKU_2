#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// 1. алгоритм – Решето Эратосфена (поиск всех простых чисел до N)
vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;

    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// 2. алгоритм проверки числа на принадлежность к «совершенным числам»
bool isPerfectNumber(long long n, long long& sumOfDivisors) {
    if (n <= 1) return false;

    sumOfDivisors = 1; 
    for (long long d = 2; d * d <= n; ++d) {
        if (n % d == 0) {
            sumOfDivisors += d;
            if (d * d != n) {
                sumOfDivisors += n / d;
            }
        }
    }
    return sumOfDivisors == n;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "ЗАДАНИЕ 2: РЕАЛИЗОВАТЬ ТЕСТ ПРОСТОТЫ\n";

    int limit;
    cout << "Введите верхний предел N для Решета Эратосфена (например, 1000000): ";
    cin >> limit;

    // время работы Решета Эратосфена
    auto startSieve = high_resolution_clock::now();
    vector<int> primes = sieveOfEratosthenes(limit);
    auto endSieve = high_resolution_clock::now();
    duration<double, milli> timeSieve = endSieve - startSieve;

    cout << "\n1. Решето Эратосфена:\n";
    cout << "   Найдено простых чисел до " << limit << ": " << primes.size() << "\n";
    cout << "   Время выполнения: " << fixed << setprecision(4) << timeSieve.count() << " ms\n\n";

    long long num;
    cout << "Введите число для проверки на совершенность (например, 6, 28, 496, 8128): ";
    cin >> num;

    // время проверки на совершенность
    long long divisorSum = 0;
    auto startPerfect = high_resolution_clock::now();
    bool perfect = isPerfectNumber(num, divisorSum);
    auto endPerfect = high_resolution_clock::now();
    duration<double, milli> timePerfect = endPerfect - startPerfect;

    cout << "\n2. Проверка на совершенность:\n";
    cout << "   Число " << num << (perfect ? " ЯВЛЯЕТСЯ " : " НЕ ЯВЛЯЕТСЯ ") << "совершенным.\n";
    cout << "   Сумма делителей: " << divisorSum << "\n";
    cout << "   Время выполнения: " << fixed << setprecision(4) << timePerfect.count() << " ms\n\n";

    // анализ 
    cout << "Сравнительный анализ\n";
    cout << "Векторный поиск (Решето Эратосфена) обрабатывает диапазон [" << limit
        << "] за " << timeSieve.count() << " ms.\n";
    cout << "Точечная проверка числа " << num << " выполнена за "
        << timePerfect.count() << " ms.\n";

    return 0;
}