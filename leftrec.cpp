#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string nonTerminal;
    int n;

    cout << "Enter Non-Terminal: ";
    cin >> nonTerminal;

    cout << "Enter number of productions: ";
    cin >> n;

    vector<string> alpha, beta;
    cout << "Enter productions (without spaces):\n";

    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;

        // Check for left recursion
        if (prod.substr(0, nonTerminal.length()) == nonTerminal) {
            alpha.push_back(prod.substr(nonTerminal.length()));
        } else {
            beta.push_back(prod);
        }
    }

    if (alpha.empty()) {
        cout << "\nNo left recursion found.\n";
        return 0;
    }

    string newNT = nonTerminal + "'";

    cout << "\nAfter eliminating left recursion:\n";

    // A → βA'
    cout << nonTerminal << " → ";
    for (int i = 0; i < beta.size(); i++) {
        cout << beta[i] << newNT;
        if (i != beta.size() - 1) cout << " | ";
    }

    // A' → αA' | ε
    cout << "\n" << newNT << " → ";
    for (int i = 0; i < alpha.size(); i++) {
        cout << alpha[i] << newNT << " | ";
    }
    cout << "ε";

    return 0;
}
