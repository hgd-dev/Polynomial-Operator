#include <deque>
#include <map>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
bool is_integer(string str) {
    if (str.empty()) return false;
    while (str.front() == ' ') {
        str = str.substr(1);
    }
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
struct polynomial {
    int degree = 0;
    map <int, int> coefficients;
};
polynomial dividend, divisor, quotient, temp;
void take_inputs() {
    string temp;
    while (true) {
        cout << "Enter the dividend polynomial degree:\n";
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) >= 0) {
            dividend.degree = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
    for (int i = dividend.degree; i >= 0; --i) {
        while (true) {
            cout << "Enter the coefficient for term x^" << i << " or 0 if term is not present in the dividend polynomial:\n";
            getline(cin, temp);
            if (is_integer(temp)) {
                dividend.coefficients[i] = stoi(temp);
                break;
            }
            else { cout << "Invalid input! Attempt aborted.\n\n"; }
        }
    }
    while (true) {
        cout << "Enter the divisor polynomial degree:\n";
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) >= 0) {
            divisor.degree = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
    for (int i = divisor.degree; i >= 0; --i) {
        while (true) {
            cout << "Enter the coefficient for term x^" << i << " or 0 if term is not present in the divisor polynomial:\n";
            getline(cin, temp);
            if (is_integer(temp)) {
                divisor.coefficients[i] = stoi(temp);
                break;
            }
            else { cout << "Invalid input! Attempt aborted.\n\n"; }
        }
    }
}
void output_given_polynomial(polynomial a) {
    cout << "f(x) = ";
    if (a.coefficients.empty()) { cout << 0; return; }
    for (int i = a.degree; i >= 0; --i) {
        cout << a.coefficients[i];
        if (i != 0) {
            cout << "x^" << i << " + ";
        }
    }
    cout << '\n';
}
int main() {
    //Input:
    take_inputs();
    cout << "\nGiven Dividend Polynomial:\n";
    output_given_polynomial(dividend);
    cout << "\nGiven Divisor Polynomial:\n";
    output_given_polynomial(divisor);
    quotient.degree = dividend.degree - divisor.degree;
    while (dividend.degree >= divisor.degree) {
        int scale = dividend.coefficients[dividend.degree]/divisor.coefficients[divisor.degree];
        if (scale*divisor.coefficients[divisor.degree] != dividend.coefficients[dividend.degree]) {
            cout << "\nNot divisible over integers.\n";
            return 0;
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
    while (true) {}
    return 0;
}