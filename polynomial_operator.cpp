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

deque <int> find_global_minima() {
    deque <int> answer;
    int curMin = INT_MAX;
    for (int i = 0; i <= global.degree; ++i) {
        if (polynomial_coordinates[i] < curMin) {
            curMin = polynomial_coordinates[i];
            answer.clear();
            answer.push_back(i);
        }
        else if (polynomial_coordinates[i] == curMin) {
            answer.push_back(i);
        }
    }
    return answer;
}
double findSlope(pair <int, int> a, pair <int, int> b) {
    return (((double) a.second) - ((double) b.second))/(((double) a.first) - ((double) b.first));
}
void convexHullDescent() {
    deque <int> global_minima = find_global_minima();
    output_coordinate_deque(build_coordinate_deque(global_minima), "Global Minimums");
    int left = global_minima.front(), right = global_minima.back();
    pair <int, int> previous_coor = {0, polynomial_coordinates[0]};
    pair <int, int> minleft = {left, polynomial_coordinates[left]};
    pair <int, int> minright = {right, polynomial_coordinates[right]};
    if (find(global_minima.begin(), global_minima.end(), 0) == global_minima.end()) { global_minima.push_back(0); }
    for (int i = 1; i < left; ++i) {
        if (findSlope({i, polynomial_coordinates[i]}, minleft) < findSlope(previous_coor, minleft)) {
            global_minima.push_back(i);
            previous_coor = {i, polynomial_coordinates[i]};
        }
    }
    if (find(global_minima.begin(), global_minima.end(), global.degree) == global_minima.end()) { global_minima.push_back(global.degree); }
    previous_coor = {global.degree, polynomial_coordinates[global.degree]};
    for (int i = global.degree - 1; i > right; --i) {
        if (findSlope({i, polynomial_coordinates[i]}, minright) < findSlope(previous_coor, minright)) {
            global_minima.push_back(i);
            previous_coor = {i, polynomial_coordinates[i]};
        }
    }
    polygon_lower = global_minima;
    sort(polygon_lower.begin(), polygon_lower.end());
}
deque <pair <int, int>> get_lattice_points(pair <int, int> left, pair <int, int> right) {
    deque <pair <int, int>> lattice_points;
    if (abs(left.first - right.first) == 1 || abs(left.second - right.second) == 1) { return lattice_points; }
    int dx = right.first - left.first, dy = right.second - left.second;
    int steps = gcd_function(abs(dx), abs(dy));
    if (steps <= 1) { return lattice_points; }
    int stepX = dx / steps, stepY = dy / steps;
    for (int i = 1; i < steps; ++i) { lattice_points.emplace_back(left.first + i * stepX, left.second + i * stepY); }
    return lattice_points;
}
void fillLattice() //Add all lattice points between list of coordinates in the graph
{
    deque <int> add_lattice;
    for (int i = 0; i < polygon_lower.size() - 1; ++i) {
        pair <int, int> l = {polygon_lower[i], polynomial_coordinates[polygon_lower[i]]};
        pair <int, int> r = {polygon_lower[i + 1], polynomial_coordinates[polygon_lower[i + 1]]};
        deque <pair <int, int>> toadd = get_lattice_points(l, r);
        for (pair <int, int> x : toadd) {
            add_lattice.push_back(x.first);
            polynomial_coordinates[x.first] = x.second;
        }
    }
    for (int x : add_lattice) { polygon_lower.push_back(x); }
    sort(polygon_lower.begin(), polygon_lower.end());
}
deque <int> performAll(int prime) {
    deque <int> answer;
    polynomial_coordinates.clear();
    for (int i = global.degree; i >= 0; --i) { polynomial_coordinates[global.degree - i] = nu_function(prime, global.coefficients[i]); }
    deque <pair <int, int>> all_points = build_deque_from_map(polynomial_coordinates);
    output_coordinate_deque(all_points, "All Points");
    convexHullDescent();
    deque <pair <int, int>> convex_hull = build_coordinate_deque(polygon_lower);
    output_coordinate_deque(convex_hull, "Convex Hull");
    fillLattice();
    deque <pair <int, int>> latticed_hull = build_coordinate_deque(polygon_lower);
    output_coordinate_deque(latticed_hull, "Latticed Hull");
    cout << "\nNewton Polygon result numbers for prime " << prime << ":\n";
    for (int i = 0; i < latticed_hull.size() - 1; i++) {
        answer.push_back(latticed_hull[i + 1].first - latticed_hull[i].first);
        cout << latticed_hull[i + 1].first - latticed_hull[i].first << ' ';
    }
    cout << "\n\n";
    return answer;
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
int main() {
    srand(time(0));
    cout << "\nWelcome to Polynomial Operator!\n\nTo begin, please input an initial polynomial:\n";
    input_new_polynomial();
    while (true) {
        cout << "\nSelect function menu from below:\n";
        cout << "  Enter d to display the current polynomial\n  Enter i to input or manipulate the polynomial\n";
        cout << "  Enter c to attempt polynomial constant factoring\n  Enter p to generate polynomial-relevant primes\n";
        cout << "  Enter r to generate possible roots with Rational Root Theorem\n  Enter n to construct and calculate Newton Polygons\n";
        cout << "  Enter s to execute polynomial long division on current polynomial\n  Enter f to attempt polynomial linear factoring\n";
        cout << "  Enter e to exit this program\n";
        char key_pressed = cin.get();
        cin.ignore(2147483647, '\n');
        if (key_pressed == 'd' || key_pressed == 'i' || key_pressed == 'c' || key_pressed == 'p' || key_pressed == 'r' || key_pressed == 'n' || 
            key_pressed == 's' || key_pressed == 'f' || key_pressed == 'e') { cout << "\nKey enter \"" << key_pressed << "\" detected.\n"; }
        string target, root;
        if (key_pressed == 'd') { display_polynomial(global); }
        else if (key_pressed == 'i') {
            bool exitStatus = false;
            while (true) {
                cout << "\nSelect input type from list below:\n";
                cout << "   Enter p to input a new polynomial\n";
                cout << "   Enter c to overwrite a coefficient\n";
                cout << "   Enter a to add terms to front of polynomial\n";
                cout << "   Enter r to remove terms from the front of polynomial\n";
                cout << "   Enter e to exit back to the main menu\n";
                char input_pressed = cin.get();
                cin.ignore(2147483647, '\n');
                if (input_pressed == 'p' || input_pressed == 'c' || input_pressed == 'a' || input_pressed == 'r' || input_pressed == 'e') { cout << "\nKey enter \"" << input_pressed << "\" detected.\n"; }
                if (input_pressed == 'p') { input_new_polynomial(); }
                else if (input_pressed == 'c') { input_overwrite_coefficient(); }
                else if (input_pressed == 'a') { input_add_degree(); }
                else if (input_pressed == 'r') { input_remove_degree(); }
                else if (input_pressed == 'e') { exitStatus = true; }
                else { cout << "\n\"" << input_pressed << "\" is an invalid key enter! Attempt aborted.\n"; }
                if (exitStatus) { break; }
            }
        }
        else if (key_pressed == 'c') {
            int save = constant_factor_polynomial(global);
            put_back_constant_factor(global, save);
        }
        else if (key_pressed == 'n') {
            while (true) {
                cout << "\nEnter m to enter target primes manually, or \"gen\" to generate relevant primes:\n";
                string primes_entered, temp;
                getline(cin, primes_entered);
                if (primes_entered == "gen" || primes_entered == "GEN") {
                    p = generate_primes(global);
                    cout << "Generated relevant primes:\n";
                    for (int prime : p) { cout << prime << ' '; }
                    cout << '\n';
                    cout << "Complete Global Polynomial Expression:\n";
                    output_given_polynomial(global);
                    for (int x : p) { performAll(x); }
                    break;
                }
                else if (primes_entered == "M" || primes_entered == "m") {
                    cout << "Enter polygon target primes:\n";
                    getline(cin, temp);
                    temp = temp + ' ';
                    std::istringstream iss(temp);
                    string token;
                    while (std::getline(iss, token, ' ')) {
                        if (!token.empty()) {
                            if (is_integer(token) && is_prime(stoi(token))) { p.push_back(stoi(token)); }
                            else {
                                cout << "Invalid input! Attempt aborted.\n\n";
                                break;
                            }
                        }
                        else { break; }
                    }
                    cout << "Complete Global Polynomial Expression:\n";
                    output_given_polynomial(global);
                    for (int x : p) { performAll(x); }
                    break;
                }
                else { cout << "\n\"" << primes_entered << "\" is an invalid entry! Attempt aborted.\n"; }
            }
        }
        else if (key_pressed == 'p') {
            p = generate_primes(global);
            cout << "Generated relevant primes:\n";
            for (int prime : p) { cout << prime << ' '; }
            cout << '\n';
        }
        else if (key_pressed == 's') {
            polynomial_long_division(input_divisor_polynomial());
        }
        else if (key_pressed == 'r') {
            generate_linear_factors(global);
        }
        else if (key_pressed == 'f') {
            p = generate_primes(global);
            cout << "Generated relevant primes for Newton Polygon:\n";
            for (int prime : p) { cout << prime << ' '; }
            cout << '\n';
            cout << "Complete Global Polynomial Expression:\n";
            output_given_polynomial(global);
            for (int x : p) { global_polygon_results.push_back(performAll(x)); }
            deque <polynomial> possible = generate_linear_factors(global), factorables;
            for (polynomial linear_solution : possible) { if (polynomial_long_division(linear_solution)) { factorables.push_back(linear_solution); } }
            cout << "\n\nAll Possible Linear Factors:\n";
            for (polynomial solution : factorables) { output_given_polynomial(solution); }
        }
        else if (key_pressed == 'e') { return 0; }
        else { cout << "\n\"" << key_pressed << "\" is an invalid key enter! Attempt aborted.\n"; }
    }
    return 0;
}