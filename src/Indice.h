#ifndef TP2_INDICE_H
#define TP2_INDICE_H

#include "BaseDeDatos.h"
#include "Tabla.h"
#include "string_map.h"
#include <set>

using namespace std;

class BaseDeDatos::Indice {

public:

  // O(L) si dato es string
  // O(log(m)) si dato es nat
  // Complejidad: O(max{L,log(m)})
  set<Tabla::const_iterador_registros> &registros(const Dato &dato) {
    return dato.esString() ? indices_dato_string[dato.valorStr()] : indices_dato_nat[dato.valorNat()];
  }

private:
  string_map<set<Tabla::const_iterador_registros>> indices_dato_string;
  map<int, set<Tabla::const_iterador_registros>> indices_dato_nat;
};


#endif //TP2_INDICE_H
