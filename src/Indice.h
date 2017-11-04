#ifndef TP2_INDICE_H
#define TP2_INDICE_H

#include "BaseDeDatos.h"
#include "Tabla.h"
#include "string_map.h"
#include <set>

using namespace std;

class BaseDeDatos::Indice {

    /* @corregir(ivan): Falta escribir la documentación de este módulo (aunque sea @brief). */

public:

  // O(L) si dato es string
  // O(log(m)) si dato es nat
  // Complejidad: O(max{L,log(m)})
  /* @comentario(ivan): En particular O(max{L, log(m)}) está en O(L + log(m)) */
  set<Tabla::const_iterador_registros> &registros(const Dato &dato) {
    return dato.esString() ? indices_dato_string[dato.valorStr()] : indices_dato_nat[dato.valorNat()];
  }

  bool existe(const Dato &dato) {
    bool existe;
    if (dato.esString()) {
      existe = indices_dato_string.find(dato.valorStr()) != indices_dato_string.end();
    } else {
      existe = indices_dato_nat.find(dato.valorNat()) != indices_dato_nat.end();
    }
    return existe;
  }

private:
  string_map<set<Tabla::const_iterador_registros>> indices_dato_string;
  map<int, set<Tabla::const_iterador_registros>> indices_dato_nat;
};


#endif //TP2_INDICE_H
