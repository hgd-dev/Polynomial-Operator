#include <iostream>
#include <map>
#include <deque>
#include <set>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
using namespace std;
struct polynomial {
    int degree = 0;
    map <int, int> coefficients;
};
deque <int> polygon_lower, p;
map <int, int> polynomial_coordinates;
polynomial global;
deque <deque <int>> global_polygon_results;

void output_given_polynomial(polynomial a) {
    cout << "f(x) = ";
    if (a.coefficients.empty()) { cout << 0; return; }
    for (int i = a.degree; i >= 0; --i) {
        cout << a.coefficients[i];
        if (i != 0) { cout << "x^" << i << " + "; }
    }
    cout << '\n';
}
int gcd_function(int a, int b) {
    return (b == 0) ? (abs(a)) : (gcd(b, a % b));
}

bool polynomial_long_division(polynomial div, polynomial target = global) {
    string temp;
    polynomial dividend = target, divisor = div, quotient;
    cout << "\nDividend Polynomial:\n";
    output_given_polynomial(dividend);
    cout << "\nGiven Divisor Polynomial:\n";
    output_given_polynomial(divisor);
    quotient.degree = dividend.degree - divisor.degree;
    while (dividend.degree >= divisor.degree) {
        int scale = dividend.coefficients[dividend.degree]/divisor.coefficients[divisor.degree];
        if (scale*divisor.coefficients[divisor.degree] != dividend.coefficients[dividend.degree]) {
            cout << "\nNot divisible over integers.\n";
            return false;
        }
        quotient.coefficients[dividend.degree - divisor.degree] = scale;
        for (int i = 0; i <= divisor.degree; ++i) {
            dividend.coefficients[dividend.degree - i] -= (divisor.coefficients[divisor.degree - i]*scale);
            cout << dividend.coefficients[dividend.degree - i] << '\n';
        }
        while (!dividend.coefficients.empty() && dividend.coefficients[dividend.degree] == 0) {
            dividend.coefficients.erase(dividend.degree);
            dividend.degree--;
        }
    }
    cout << "Long Division Answer:\nQuotient:\n";
    output_given_polynomial(quotient);
    cout << "\nRemainder:\n";
    output_given_polynomial(dividend);
    cout << '\n';
    return dividend.coefficients.empty();
}
set <int> positive_factorize(long long n) {
    set <int> answer;
    long long z = 1;
    while (z <= n) {
        if (z != 0 && n % z == 0) { answer.insert(z); }
        z++;
    }
    return answer;
}
set <int> full_factorize(long long n) {
    set <int> answer;
    long long z = -1*n;
    while (z <= n) {
        if (z != 0 && n % z == 0) { answer.insert(z); }
        z++;
    }
    return answer;
}
deque <int> generate_primes(polynomial x) {
    int na = x.coefficients[x.degree], nb = x.coefficients[0];
    set <int> primes;
    long long z = 2;
    while (z * z <= na) {
        if (na % z == 0) { primes.insert(z), na /= z; }
        else { z++; }
    }
    if (na > 1) { primes.insert(z); }
    z = 2;
    while (z * z <= nb) {
        if (nb % z == 0) { primes.insert(z), nb /= z; }
        else { z++; }
    }
    if (nb > 1) { primes.insert(z); }
    deque <int> ans;
    for (int k : primes) { ans.push_back(k); }
    return ans;
}
int constant_factor_polynomial(polynomial &target) {
    int constant_factor = target.coefficients[target.degree];
    for (int i = target.degree; i >= 0; --i) { constant_factor = gcd_function(constant_factor, target.coefficients[i]); }
    cout << "\nConstant Factor: " << constant_factor << '\n';
    for (int i = target.degree; i >= 0; --i) { target.coefficients[i] /= constant_factor; }
    cout << "Factored Out Polynomial:\n";
    output_given_polynomial(target);
    return constant_factor;
}
void put_back_constant_factor(polynomial &target, int constant_factor) {
    for (int i = target.degree; i >= 0; --i) { target.coefficients[i] *= constant_factor; }
}
deque <polynomial> generate_linear_factors(polynomial &target) {
    deque <polynomial> possible;
    polynomial temp;
    temp.degree = 1, temp.coefficients[1] = 0, temp.coefficients[0] = 0;
    int save = constant_factor_polynomial(target);
    set <int> a = positive_factorize(target.coefficients[target.degree]);
    set <int> b = full_factorize(target.coefficients[0]);
    cout << "First Term Coefficient Factors:\n";
    for (int x : a) { cout << x << ' '; }
    cout << "\nConstant Term Factors:\n";
    for (int x : b) { cout << x << ' '; }
    cout << "\n\n";
    for (int slope : a) {
        for (int intercept : b) {
            temp.coefficients[1] = slope, temp.coefficients[0] = intercept;
            cout << "Possible Linear Factor: (" << slope << "x";
            if (intercept > 0) { cout << " + " << intercept; }
            else { cout << " - " << -1*intercept; }
            cout << ") with solution: " << ((double) -1*intercept)/((double) slope) << '\n';
            possible.push_back(temp);
        }
    }
    put_back_constant_factor(target, save);
    return possible;
}