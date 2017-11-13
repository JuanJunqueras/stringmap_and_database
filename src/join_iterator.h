//
// Created by Agustín Argüello on 11/4/17.
//

#ifndef TP2_GRUPO2_JOIN_ITERATOR_H
#define TP2_GRUPO2_JOIN_ITERATOR_H

#include <set>
#include "Tabla.h"

/**
 * @brief Un join_iterator es un iterador que nos permite movernos entre dos tablas
 * a las cualse se les aplicó la función join.
 *
 * Una join_iterator permite generar un iterarador entre dos tablas.
 * Permite avanzar el iterador.
 * Permite desreferenciar devolviendo un regitro compuesto por el contenido de ambos punteros.
 *
 * **se explica con** TAD BaseDeDatos  //FIXME: chequear
 */
class join_iterator {

private:

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: join_iterator \TO bool\n
     * rep(ji) \EQUIV
     *
     * siendo: it_registros_tabla_principal = 1
     *         it_registros_tabla_principal_end = 2
     *         it_registros_tabla_con_indice = 3
     *         it_registros_tabla_con_indice_end = 4
     *         Lo que se me ocurre del rep por ahora es:
     *         1 != 2
     *         2 != 4
     *         Si 1 = 2 entonces 3 = 4
     *         Si 3 != 4 entonces 1 != 2
     *
     *
     * abs: no hay abs, pues no hay TAD de la clase índice para compararlo. FIXME: chequear
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////
        Tabla::const_iterador_registros it_registros_tabla_principal;
        Tabla::const_iterador_registros it_registros_tabla_principal_end;
        set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice;
        set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end;

public:

    join_iterator(
            Tabla::const_iterador_registros it_registros_tabla_principal,
            Tabla::const_iterador_registros it_registros_tabla_principal_end,
            set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice,
            set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end
    ) :
            it_registros_tabla_principal(it_registros_tabla_principal),
            it_registros_tabla_principal_end(it_registros_tabla_principal_end),
            it_registros_tabla_con_indice(it_registros_tabla_con_indice),
            it_registros_tabla_con_indice_end(it_registros_tabla_con_indice_end)
    { }
    /**
   * @brief Desreferencia los registros a los que apuntan los punteros
   * y devuelve un registro por referencia.
   *
   *
   * \pre true //FIXME: chequear
   * \post { // FIXME terminar
   *
   * \complexity{\O(copy(Registro))}
   **/
    Registro& operator*() {

        // O(1)
        Registro r1 = *it_registros_tabla_principal;
        Registro r2 = **it_registros_tabla_con_indice;
        vector<string> campos_registro_join;
        vector<Dato> datos_registro_join;

        // Agregamos campos y datos del primer registro
        const string_set &campos_r1 = r1.campos(); // O(1)
        for (const string &campo_r1 : campos_r1) { // O(C)
            campos_registro_join.push_back(campo_r1); // O(1)
            datos_registro_join.push_back(r1.dato(campo_r1)); // O(1)
        }

        // Agregamos campos y datos del segundo registro, si estos no están ya en el primero
        const string_set &campos_r2 = r2.campos();
        for (const string &campo_r2 : campos_r2) { // O(C)
            if (r1.pertenece(campo_r2)) { // O(1)
                campos_registro_join.push_back(campo_r2); // O(1)
                datos_registro_join.push_back(r2.dato(campo_r2)); // O(1)
            }
        }

        Registro registro_join = Registro(campos_registro_join, datos_registro_join); // O(C * copy(Dato)) = O(C) = O(copy(Registro))
        return registro_join;
    }
};

#endif //TP2_GRUPO2_JOIN_ITERATOR_H
