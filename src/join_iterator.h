//
// Created by Agustín Argüello on 11/4/17.
//

#ifndef TP2_GRUPO2_JOIN_ITERATOR_H
#define TP2_GRUPO2_JOIN_ITERATOR_H

#include <set>
#include "Tabla.h"
#include "BaseDeDatos.h"
#include "Indice.h"

/**
 * @brief Un join_iterator es un iterador que nos permite movernos entre dos tablas
 * a las cualse se les aplicó la función join.
 *
 * Una join_iterator permite generar un iterarador entre dos tablas.
 * Permite avanzar el iterador.
 * Permite desreferenciar devolviendo un registro compuesto por el contenido de ambos punteros.
 *
 * **se explica con** TAD BaseDeDatos  //FIXME: chequear
 */
class BaseDeDatos::join_iterator {

private:

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: join_iterator \TO bool\n
	rep(ji) \EQUIV
	siendo:   //FIXME: escribir formalmente. Revisar rep
	Lo que se me ocurre del rep por ahora es:
	Si it_registros_tabla_principal = it_registros_tabla_principal_end IMPLIES it_registros_tabla_con_indice = it_registros_tabla_con_indice_end
	Si it_registros_tabla_con_indice != it_registros_tabla_con_indice_end IMPLIES it_registros_tabla_principal != it_registros_tabla_principal_end
	Tabla(it_registros_tabla_principal) == Tabla(it_registros_tabla_principal_end)
	set(it_registros_tabla_con_indice) == set(it_registros_tabla_con_indice_end)
	end(set(it_registros_tabla_con_indice)) == it_registros_tabla_con_indice_end
	end( Tabla(1)) == it_registros_tabla_principal_end
	abs: agarrarse del tad de base de datos que tiene un join. FIXME: hacer
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    const BaseDeDatos &db;
    Tabla::const_iterador_registros it_registros_tabla_principal;
    Tabla::const_iterador_registros it_registros_tabla_principal_end;
    set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice;
    set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end;
    string nombre_tabla = "";
    string nombre_campo = "";

public:

    join_iterator(
            const BaseDeDatos &db,
            string nombre_tabla,
            string nombre_campo,
            Tabla::const_iterador_registros it_registros_tabla_principal,
            Tabla::const_iterador_registros it_registros_tabla_principal_end,
            set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice,
            set<Tabla::const_iterador_registros>::iterator it_registros_tabla_con_indice_end
    ) :
            db(db),
            nombre_tabla(nombre_tabla),
            nombre_campo(nombre_campo),
            it_registros_tabla_principal(it_registros_tabla_principal),
            it_registros_tabla_principal_end(it_registros_tabla_principal_end),
            it_registros_tabla_con_indice(it_registros_tabla_con_indice),
            it_registros_tabla_con_indice_end(it_registros_tabla_con_indice_end)
    { }


    join_iterator operator++() {

        if (it_registros_tabla_con_indice != it_registros_tabla_con_indice_end) {
            ++it_registros_tabla_con_indice;
        } else {

            const BaseDeDatos::Indice &indice = db.indices.at(nombre_tabla).at(nombre_campo);

            // Iteramos sobre tabla principal, buscando el primer siguiente match con registro del indice
            bool match = false;
            while (!match && it_registros_tabla_principal != it_registros_tabla_principal_end) {
                auto dato = (*it_registros_tabla_principal).dato(nombre_campo);
                if (indice.existe(dato)) {
                    it_registros_tabla_con_indice = indice.registros(dato).begin();
                    it_registros_tabla_con_indice_end = indice.registros(dato).end();
                    match = true;
                }
                ++it_registros_tabla_principal;
            }
        }

    }

    /**
   * @brief Desreferencia los registros a los que apuntan los punteros
   * y devuelve un registro por referencia.
   *
   *
   * \pre true
   * \post todo dato en el resultado de desreferenciar, está en alguno
   * de los registros a los que apuntan los iteradores it_ o en ambos.
   * \complexity{\O(copy(Registro))}
   **/
    Registro& operator*() {

        // O(1)
        const Registro &r1 = *it_registros_tabla_principal;
        const Registro &r2 = *(*it_registros_tabla_con_indice);
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
            if (!r1.pertenece(campo_r2)) { // O(1)
                campos_registro_join.push_back(campo_r2); // O(1)
                datos_registro_join.push_back(r2.dato(campo_r2)); // O(1)
            }
        }

        Registro registro_join = Registro(campos_registro_join, datos_registro_join); // O(C * copy(Dato)) = O(C) = O(copy(Registro))
        return registro_join;
    }
};

#endif //TP2_GRUPO2_JOIN_ITERATOR_H
