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
deque <pair <int, int>> build_coordinate_deque(deque <int> given) {
    deque <pair <int, int>> answer;
    for (int i : given) { answer.push_back({i, polynomial_coordinates[i]}); }
    return answer;
}
deque <pair <int, int>> build_deque_from_map(map <int, int> given) {
    deque <pair <int, int>> answer;
    for (pair <int, int> pair : given) { answer.push_back(pair); }
    return answer;
}
void output_given_polynomial(polynomial a) {
    cout << "f(x) = ";
    if (a.coefficients.empty()) { cout << 0; return; }
    for (int i = a.degree; i >= 0; --i) {
        cout << a.coefficients[i];
        if (i != 0) { cout << "x^" << i << " + "; }
    }
    cout << '\n';
}
void output_coordinate_deque(deque <pair <int, int>> given, string title) {
    cout << '\n' << title << ":\n";
    for (pair <int, int> i : given) { cout << '(' << i.first << ", " << i.second << ")\n"; }
}
int nu_function(int prime, int coefficient) {
    if (coefficient == 0) { return INT_MAX; }
    else { coefficient = abs(coefficient); }
    int answer = 0;
    while (coefficient % prime == 0) { coefficient /= prime, answer++; }
    return answer;
}
int gcd_function(int a, int b) {
    return (b == 0) ? (abs(a)) : (gcd(b, a % b));
}
bool is_integer(string str) {
    if (str.empty()) return false;
    while (str.front() == ' ') { str = str.substr(1); }
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.size() == 1) { return false; }
        start = 1;
    }
    for (size_t i = start; i < str.size(); ++i) { if (!isdigit(str[i])) { return false; } }
    return true;
}
bool is_prime(int number) {
    if (number < 2) { return false; }
    if (number == 2) { return true; }
    if (number % 2 == 0) { return false; }
    for (int i = 3; (i*i) <= number; i += 2) { if (number % i == 0 ) { return false; } }
    return true;
}
void display_polynomial(polynomial a) {
    cout << "Polynomial(x) = ";
    if (a.coefficients.empty()) { cout << 0; return; }
    for (int i = a.degree; i >= 0; --i) {
        cout << a.coefficients[i];
        if (i != 0) { cout << "x^" << i << " + "; }
    }
    cout << '\n';
}

void input_new_polynomial() {
    string temp;
    global.degree = -1, global.coefficients.clear();
    while (true) {
        cout << "Enter new polynomial degree:\n";
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) >= 0) {
            global.degree = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
    for (int i = global.degree; i >= 0; --i) {
        while (true) {
            cout << "Enter the coefficient for term x^" << i << " or 0 if term is not present:\n";
            getline(cin, temp);
            if (is_integer(temp)) {
                global.coefficients[i] = stoi(temp);
                break;
            }
            else { cout << "Invalid input! Attempt aborted.\n\n"; }
        }
    }
}
void input_overwrite_coefficient() {
    int cur_change_degree = 0;
    string temp;
    while (true) {
        cout << "Enter desired coefficient's degree to be overwritten:\n";
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) >= 0 && stoi(temp) <= global.degree) {
            cur_change_degree = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
    while (true) {
        cout << "Enter your new desired coefficient for term x^" << cur_change_degree << " or 0 if term is not present anymore:\n";
        getline(cin, temp);
        if (is_integer(temp)) {
            global.coefficients[cur_change_degree] = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
}
void input_add_degree() {
    int new_degree = 0;
    string temp;
    while (true) {
        cout << "Enter new desired enlarged polynomial degree:\n";
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) > global.degree) {
            new_degree = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
    for (int i = new_degree; i > global.degree; --i) {
        while (true) {
            cout << "Enter the coefficient for term x^" << i << " or 0 if term is not present:\n";
            getline(cin, temp);
            if (is_integer(temp)) {
                global.coefficients[i] = stoi(temp);
                break;
            }
            else { cout << "Invalid input! Attempt aborted.\n\n"; }
        }
    }
    cout << "\nAdded new polynomial terms until new degree " << new_degree << ".";
    global.degree = new_degree;
}
void input_remove_degree() {
    int new_degree = 0;
    string temp;
    while (true) {
        cout << "Enter new desired reduced polynomial degree:\n";
        getline(cin, temp);
        if (is_integer(temp) && stoi(temp) < global.degree) {
            new_degree = stoi(temp);
            break;
        }
        else { cout << "Invalid input! Attempt aborted.\n\n"; }
    }
    for (int i = new_degree; i > global.degree; --i) { global.coefficients.erase(i); }
    global.degree = new_degree;
    cout << "\nReduced polynomial terms until new degree " << new_degree << ".";
}
polynomial input_divisor_polynomial() {
    string temp;
    polynomial divisor;
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
    return divisor;
}
