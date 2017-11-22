#ifndef STRING_SET_H
#define STRING_SET_H

#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include "linear_set.h"

using namespace std;

/**
 * @brief Representa un diccionario cuyas claves son strings.
 *
 * **se explica con** TAD Diccionario(string, T)
 */


class string_set {
public:
    typedef string value_type;
    typedef size_t size_type;

    /* @corregir(ivan): Falta la documentación de este iterador */
    class iterator{
        const string_set* set;
        friend class string_set;
        value_type elementoActual;
    public:
        value_type getElemento();
        iterator(const string_set* mapa);
        iterator();
        //using value_type = const string_set::value_type;
        using iterator_category = std::forward_iterator_tag;
        using reference =value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        value_type operator*();
        value_type* operator->();
        iterator& operator++();
        bool operator!=(const iterator& o_it) const;
        bool operator==(const iterator& o_it) const;
        bool isEnd();

    };
    /* @corregir(ivan): Falta la documentación de este iterador */
    class const_iterator{

        const string_set* set;
        friend class string_set;
        value_type elementoActual;
    public:
        value_type getElemento();
        const_iterator(const string_set* set);
        const_iterator();
        //using value_type = const string_set::value_type;
        using iterator_category = std::forward_iterator_tag;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        value_type operator*();
        value_type* operator->();
        const_iterator& operator++();
        bool operator!=(const const_iterator &o_it) const;
        bool operator==(const const_iterator &o_it) const;
        bool isEnd();


    };
    friend class iterator;
    friend class const_iterator;


    /* @corregir(ivan): De dónde sale "raiz" en la post del constructor vacío ?
     * En la pre y la post sólo pueden hablar en terminos de las operaciones del TAD con el cual se explica el módulo.
     * */
    /**
   * @brief Construye mapa con su raiz.
   *
   * \pre true
   * \post vacio?(res) \AND vacio?(raiz.hijos().empty())
   *
   * \complexity{\O(1)}
   */

    string_set();

    /** @brief Destruye mapa
     *
     * \complexity{\O(sn * S)}
     */
    ~string_set();

    /* @corregir(ivan): En el constructor por copia y en el operador de asignación faltan el costo de copy(T) */
    /** @brief Constructor por copia
     *
     * \pre true
     * \post res = @param
     *
     * \complexity{\O(sn * S)}
     */
    string_set(const string_set &);

    /** @brief Constructor desde linear_set
     *
     * \pre true
     * \post res = @param
     *
     * \complexity{\O(sn * S)}
     */
    string_set(const linear_set<string> &);

    /** @brief Operador de asignacion
     *
     * \pre true
     * \post res = @param
     *
     * \complexity{\O(sn * S)}
     */
    /* @corregir(ivan): Esta complejidad debería ser O(sn * (S + copy(value_type)) */
    string_set& operator=(const string_set &);

    /* @corregir(ivan): En el operador == falta el costo de comparar T (cmp(T)) */
    /* @corregir(ivan): La post está sin terminar */
    /** @brief Operadores de comparacion
     *
     * \pre true
     * \post true
     *
     * \complexity{\O(sn * S)}
     */
    bool operator==(const string_set& otro) const;

    /* @corregir(ivan): Falta la documentación de esta función. */
    bool operator!=(const string_set& otro) const;

    /** @brief Cantidad de apariciones de la clave (0 o 1)
     *  @param key clave a buscar
     *
     *  \pre true
     *  \post res = if def?(this, key) then 1 else 0 fi
     *
     *  \complexity{\O(S)}
     */
    size_type count(const value_type& elem) const;

    /** @brief Devuelve cantidad de claves definidas
     *
     * \pre true
     * \post res = #claves(this)
     *
     * \complexity{\O(1)}
     * */
    size_t size() const;

    /** @brief devuelve true si size() == 0
     *
     * \pre true
     * \post res = if #claves(this) = 0 then true else false fi
     *
     * \complexity{\O(1)}
     * */
    bool empty() const;

    /* @corregir(ivan): En el clear, de dónde sale "raiz" ?
     * En la pre y la post sólo pueden hablar en terminos de las operaciones del TAD con el cual se explica el módulo.
     * */
    /** @brief Vacia el mapa
     *
     * \pre true
     * \post vacio?(res) \AND vacio?(res.raiz().hijos())
     *
     * \complexity{\O(n)}
     *
     */
    void clear();

    // Accesos con iteradores

    /** @brief iterador al primer par <clave,significado> en orden lexicografico
     *  @returns iterador al elemento o end() si el mapa era vacio
     *
     * \pre true
     * \post El iterador resultante apunta al primer elemento o end() si el mapa era vacio
     *
     *  \complexity{\O(S)}
     */
    iterator begin();
    iterator end();
    const_iterator begin() const;
    /** @brief iterador al fin de la coleccion
     *
     * \pre true
     * \post El iterador resultante apunta al final de la coleccion
     *
     *
     *  \complexity{\O(S)}
     */
    const_iterator end() const;

    /// Versiones const de begin/end

    const_iterator cbegin() const;
    const_iterator cend() const;

    /** @brief busca una clave
     *  @param key clave a buscar
     *  @returns un iterador al par <clave, significado>
     *
     *  \pre true
     *  \post El iterador resultante apunta a la tupla <key, this.at(key)>
     *  o al final de la coleccion si key no esta definida en this.
     *
     *  \complexity{\O(S)}
     */
    iterator find(const value_type& elem);

    /** @brief busca una clave
     *  @param key clave a buscar
     *  @returns un iterador const al par <clave, significado>
     *
     *  \pre true
     *  \post El iterador resultante apunta a la tupla <key, this.at(key)>
     *  o al final de la coleccion si key no esta definida en this.
     *
     *  \complexity{\O(S)}
     */
    const_iterator find(const value_type& elem) const;

    /* @corregir(ivan): Acá falta hablar en la post de que pasa con el diccionario */
    /** @brief insercion
     *
     * @param value par <clave,significado> a insertar
     * @returns un par con un iterador al par clave-significado agregado o
     * modificado y un bool que indica si la clave se insertó como una clave
     * nueva.
     *
     * \pre this=this_0
     * \post El primer elemento del par resultante es un iterador que apunta a tupla <key, this.at(key)>
     * y el segundo elemento es true si la clave no estaba definida en this_0 y false en caso contrario.
     *
     * \complexity{\O(S + copy(value_type))}
     */
    pair<iterator,bool> insert(const value_type& elem);

    /* @corregir(ivan): terminar de escribir la post (si tienen dudas, pregunten). */
    /** @brief eliminar una clave
     *  @param key clave a eliminar
     *  @returns cantidad de elementos eliminados
     *
     *  \pre key \IN claves(this)
     *  \post key \NOTIN claves(this) \AND res = FIXME ver como escribir esto en logica
     *
     *  \complexity{\O(S)}
     */
    size_type erase(const value_type& elem);

    /** @brief eliminar una clave mediante irerador
     *  @param pos iterador apuntando a clave a eliminar
     *  @returns iterador apuntando el proximo de la clave eliminada (o end() si era la ultima)
     *
     *  \pre la claveActual de pos esta definida en el mapa
     *  \post key \NOTIN claves(this) \AND la claveActual del iterador resultante es la siguiente clave
     *  y valorActual del iterador resultante es un puntero a this.at(claveActual)
     *  o un puntero nulo en caso de ser el fin de la coleccion.
     *
     *  \complexity{\O(S)}
     */
    iterator erase(iterator pos);


    string siguienteElemento(string elemActual) const;

private:

    /* @corregir(ivan): Dado que el string_map tiene dentro una estructura recursiva, les conviene armar un predicado auxiliar que les ayude a escribir el Rep. */
    /* @corregir(ivan): Están mezclando el abs del string_map con el de sus iteradores. */
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: string_map \TO bool\n
     * rep(m) \EQUIV
     *  * m.raiz.valor = null
     *  * m._cantidadDeClaves = FIXME no se a qué igualarlo
     *
     * abs: string_map \TO Diccionario(string, T)\n
     * abs(m) \EQUIV m' \|
     *  * #claves(m') = m._cantidadDeClaves \AND
     *  * \FORALL (c : string) def?(c,m') \IMPLIES \EXISTS (i: string_map_iterator(m))(i.claveActual = c) \LAND
     *  (i.valorActual = obtener(c,m')
     *  * \FORALL (i: string_map_iterator(m)) (i \NEQ m.end) \LIMPLIES def?(i.claveActual, m') \AND
     *  obtener(i.claveActual, m') = i.valorActual
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    struct Nodo {
        map<char, Nodo*> hijos;
        bool esClave;
        Nodo() {esClave = false;};
    };

    Nodo* raiz;
    size_t _cantidadDeElementos;
    string primerElemento() const;
    Nodo* findNodo(string key)const;
    vector<Nodo*> getBranch(string key)const;
};


#endif //STRING_SET_STRING_SET_H