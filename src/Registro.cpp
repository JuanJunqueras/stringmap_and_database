#include <iostream>
#include "Registro.h"
#include "utils.h"
using namespace std;

Registro::Registro(const vector<string>& campos, const vector<Dato>& datos) {
    for (int i = 0; i < campos.size(); i++) {
        _campos.insert(campos[i]);
    }
    for (int i = 0; i < campos.size(); i++) {
           _datos.insert(make_pair(campos[i], datos[i]));
    }
};

const Dato& Registro::dato(const string& campo) const {
    return _datos.at(campo);
}

const string_set & Registro::campos() const {
    return _campos;
}

bool Registro::pertenece(const string &campo) const {
    return _datos.count(campo) == 1;
}


bool operator==(const Registro& r1, const Registro& r2) {
    if (not (r1.campos() == r2.campos())) {
        return false;
    }
    for (auto c : r1.campos()) {
        if (r1.dato(c) != r2.dato(c)) {
            return false;
        }
    }
    return true;
}

/* @corregir(ivan): Lo comentaron por alguna razón ? */
//ostream &operator<<(ostream &os, const Registro &r) {
//  os << r._datos;
//  return os;
//}
