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

    /*
       * permite iterar el String_set, clave por clave,
       * en orden alfabetico de las claves.
       * El operador * devuelve una instancia de <value_type>,
       * y el end es <"","">.
       * se inicializa apuntando a la primera clave del string_set en orden alfabetico.
       * Hacer ++ es O(clave más larga).
     * */
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
    /* idem iterator, pero los valores devueltos son constantes evitando aliasing. */
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


    /**
   * @brief Construye mapa con su raiz.
   *
   * \pre true
   * \post vacio?(claves(res))
   *
   * \complexity{\O(1)}
   */


    string_set();

    /** @brief Destruye mapa
     *
     * \complexity{\O(sn * S)}
     */
    ~string_set();

    /** @brief Constructor por copia
    *
    * \pre true
    * \post res = @param
    *
    * \complexity{\O(sn * (S + copy(value_type)))}
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
     * \complexity{\O(sn * (S + copy(value_type)) }
     */

    string_set& operator=(const string_set &);

     /** @brief Operadores de comparacion
     *
     * \pre true
     * \post res  = (claves(this) = claves(otro) \LAND (\FORALL k :claves(this))( obtener(k,this) = obtener(k,otro))    )
     *
     * \complexity{\O(sn * (S+cmp(T)))}
     */
    bool operator==(const string_set& otro) const;

     /** @brief Operadores de comparacion
      *
      * \pre true
      * \post res  = (claves(this) != claves(otro) \LOR \LNOT (\FORALL k :claves(this))( obtener(k,this) = obtener(k,otro))    )
      *
      * \complexity{\O(sn * (S+cmp(T)))}
      */
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

    /** @brief Vacia el mapa
     *
     * \pre true
     * \post vacio?(claves(this))
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

    /** @brief insercion
     *
     * @param value par <clave,significado> a insertar
     * @returns un par con un iterador al par clave-significado agregado o
     * modificado y un bool que indica si la clave se insertó como una clave
     * nueva.
     *
     * \pre this=this_0
     * \post El primer elemento del par resultante es un iterador que apunta a tupla <key, this.at(key)>
 *   * y el segundo elemento es true si la clave no estaba definida en this_0 y false en caso contrario.
 *   * ademas, obtener(this,value.first) = value.second
     * \complexity{\O(S + copy(value_type))}
     */

    pair<iterator,bool> insert(const value_type& elem);

    /** @brief eliminar una clave
     *  @param key clave a eliminar
     *  @returns cantidad de elementos eliminados
     *
     *  \pre key \IN claves(this)
     *  \post key \NOTIN claves(this) \AND res = if clave \ISIN claves(dicc0) then 1 else 0 fi
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
      *  si la raiz esta apuntando a " " como valor, y no tiene hijos
      *  entonces el string_set no tiene ninguna clave con un significado definido.
      *  Si un nodo distinto a la raiz apunta a " " como valor, entonces
      *  tiene que tener al menos un hijo, a menos que sea la raiz.
      *  Todas las otras hojas del arbol tienen un valor distinto de " ".
      *  "" no es una clave valida, y " " no un valor valido.
      *  (pues los usamos para marcar justamente el end en el iterador, y la ausencia de valores).
      *  La cantidad de claves es igual a la cantidad de strings
      *  tal que el significado existe (i.e., no es " ").
      *
      * abs: string_set \TO Diccionario(string, T)\n
      * abs(m) \EQUIV m' tal que es un dicc e \|
      *  * #claves(m') = m._cantidadDeClaves \AND
      *  * \FORALL (c : string) def?(c,m') \IMPLIES string_set[c]=obtener(m',c)
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