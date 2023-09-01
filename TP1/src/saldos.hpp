//
// Created by Ariel on 01/09/2023.
//
#include "vector"
#include "string"

using namespace std;

namespace Libro {
    vector<int> libro;
    int N;
    int saldo;
    vector<char> sol;

    void limpiaCuentas(vector<char> &b, int i, int saldoActual) {
        if (i == N && saldoActual == saldo) {
            sol = b;
        } else {
            b[i] = '+';
            limpiaCuentas(b, i + 1, saldoActual + libro[i]);
            b[i] = '-';
            limpiaCuentas(b, i + 1, saldoActual - libro[i]);
        }
    }

}










