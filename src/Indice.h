#ifndef TP2_INDICE_H
#define TP2_INDICE_H

#include "BaseDeDatos.h"
#include "Tabla.h"
#include "string_map.h"
#include <set>

using namespace std;

/**
 * @brief Un indice para una tabla y un campo es un diccionario cuyas claves
 * son los distintos datos que la tabla contiene en dicho campo y los significados
 * son los registros que comparten dicho dato en ese campo.
 *
 * Un indice permite acceder a registros que tienen el mismo dato en un campo.
 * Permite saber si un dato pertenece al campo en el cual se creó el índice.
 *
 * **se explica con** TAD BaseDeDatos //FIXME: el TAD indice no existe, con que TAD se explica entonces?
 */
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
