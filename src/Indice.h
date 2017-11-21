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
 *  Un indice permite acceder a registros que tienen el mismo dato en un campo.
 * Permite saber si un dato pertenece al campo en el cual se creó el índice.
 *
 * Por ejemplo si para una tabla "alumnos", se hace un índice en el campo "nombres", el
 * índice permite devolver todos los alumnos cuyo nombre es igual a un cierto valor.
 *
 */
class BaseDeDatos::Indice {

public:

    /**
     * @brief Devuelve una referencia a los registros que tienen
     * el mismo dato en el campo en el que está creado el índice. FIXME: chequear
     *
     * @param dato Dato de tipo string o nat.
     *
     * \pre true
     *
     *      índice = \P{this} \LAND
     *      \LNOT (nombre \IN tablas(\P{this})) \LAND
     *      \LAND \LNOT \EMPTYSET?(claves) \LAND
     *      \FORALL (c: campo) c \IN claves \IMPLIES c \IN campos \LAND
     *      long(campos) = long(tipos) \LAND sinRepetidos(campos)
     * \post (\forall dato : datos) ( //FIXME LATER THEN
     *  dato.esString() =>L res = obtener(this.indices_data_string, dato) \LAND
     *  dato.esNat() =>L res = obtener(this.indices_data_nat, dato)
     * )
     *
     * \complexity{\O(L + log(m)}
     * O(L) si dato es string
  * O(log(m)) si dato es nat
  * Complejidad: O(max{L,log(m)})
  = O(L+ log(m)) * */
  const set<Tabla::const_iterador_registros> &registros(const Dato &dato) const {
      if (dato.esString()) {
          return indices_dato_string.at(dato.valorStr());
      } else {
          return indices_dato_nat.at(dato.valorNat());
      }
  }
    /**
   * @brief Permite agregar un registro a un índice
   *
   * @param &campo String
   * @param &it_reg Tabla::const_iterador_registros
   *
     * \pre campo \ISIN  campos(tabla(it_reg)) \LAND \LNOT vacio?(indices(tabla(it_reg))
     * \post it_reg \ISIN  obtener(indices,(obtener(desreferenciar(it_reg),campo)))
     * (se agrego el iterador que apunta al resgistro, al indice que depende del valor del campo ingresado en el registro)
     *
   *
   **/
  void agregarRegistro(const string &campo, const Tabla::const_iterador_registros &it_reg) { //FIXME: documentar
      Dato dato = (*it_reg).dato(campo);
      if (dato.esString()) {
          indices_dato_string[dato.valorStr()].insert(it_reg);
      } else {
          indices_dato_nat[dato.valorNat()].insert(it_reg);
      }
  }

    /**
   * @brief Devuelve un valor booleano que indica si el índice contiene
   * al menos un registro con el valor pasado cómo parámetro en el campo
   * sobre el que fue creado el índice.
   *
   * @param dato Dato de tipo string o nat.
   *
   * \pre true
   * \post { // FIXME LATER AND
   *( dato.esString() \LAND L res = obtener( this.indices_dato_string,dato)) \LOR
   *( dato.esNat() \LAND L res = obtener( this.indices_dato_nat,dato))
   *
   * O(L) si dato es string
   * O(log(m)) si dato es nat
   * Complejidad: O(max{L,log(m)}) = O(L + log(m))
   * \complexity{\O(L + log(m)}
   **/

  bool existe(const Dato &dato) const {
    bool existe;
    if (dato.esString()) {
      existe = indices_dato_string.find(dato.valorStr()) != indices_dato_string.end();
    } else {
      existe = indices_dato_nat.find(dato.valorNat()) != indices_dato_nat.end();
    }
    return existe;
  }
    /** @brief Operadores de comparacion
  *
  * \pre true //FIXME: chequear
  * \post res  = (indices_dato_string(this) = indices_dato_string(otro) \LAND
  * (indices_dato_nat(this) = indices_dato_nat(otro) \LAND
  * \complexity{}//FIXME:completar
  */

  bool operator==(const Indice &indice) const {
      return this->indices_dato_string == indice.indices_dato_string && this->indices_dato_nat == indice.indices_dato_nat;
  }
    /** @brief Operadores de comparacion
     *
     * \pre true //fixme: chequear
     * \post true sii el operator== es falso.
     *
     * \complexity // idem operator== //fixme: completar
 */
   bool operator!=(const Indice &indice) const {
       return !(*this == indice);
   }

private:
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: indice \TO bool\n
     * rep(in) \EQUIV
     *  * (\FORALL (a, b: claves(indices_dato_string)) ((obtener(indices_dato_string, a)
     *  INTERSECCION obtener(indices_dato_string, b) = \EMPTYSET \LAND //FIXME: chequear cómo se hace el INTERSECCIón
     *  * (\FORALL (a, b: claves(indices_dato_nat)) (obtener(indices_dato_nat, a)
     *  INTERSECCION obtener(indices_dato_nat, b) = \EMPTYSET) \LAND //FIXME: chequear cómo se hace el INTERSECCIón
     *  * (\vacio?(claves(indices_dato_string))\LOR \vacio?(claves(indices_dato_nat)))
     *
     * abs: no hay abs, pues no hay TAD de la clase índice para compararlo. FIXME: chequear
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /** @{ */
    string_map<set<Tabla::const_iterador_registros>> indices_dato_string;
    map<int, set<Tabla::const_iterador_registros>> indices_dato_nat;
    /** @} */
};


#endif //TP2_INDICE_H
