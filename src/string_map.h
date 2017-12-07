#ifndef STRING_MAP_STRING_MAP_H
#define STRING_MAP_STRING_MAP_H

#include <cassert>
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

/**
 * @brief Representa un diccionario cuyas claves son strings.
 *
 * **se explica con** TAD Diccionario(string, T)
 */

/**
 * Implementacion de map<string,T> sobre Trie
 * Asume de T:
 * - tiene constructor por copia 
 * - tiene operador ==
 * - solo permite utilizar el operator[] si T tiene constructor por defecto
 */

template < typename T >
class string_map {
public:
    typedef string key_type;
    typedef T mapped_type;
    typedef std::pair<const key_type, mapped_type> value_type;
    typedef size_t size_type;

    /*
     * permite iterar el String_map, clave por clave,
     * en orden alfabetico de las claves.
     * El operador * devuelve una instancia de <value_type>,
     * y el end es <"",nullptr>.
     * se inicializa apuntando a la primera clave del string_map en orden alfabetico.
     * Hacer ++ es O(1) asumiendo que las claves esten acotadas.
     * */
    class iterator{

    public:

        /**
       * @brief Devuelve la clave actual del iterador
       *
       * \pre El iterador no debe estar en la posición pasando-el-último.
       * \post Devuelve el primer elemento de la tupla<clave, significado>
       * a la que apunta el iterador.
       *
       * \complexity{\O(1)}
       */
        key_type getClave() const;

        /**
       * @brief Constructor del iterador.
       *
       * \pre true
       * \post El iterador apunta a la primera tupla <clave, significado> del mapa que itera.
       * Si es vacío, apunta a la posición pasando-el-último
       *
       * \complexity{\O(1)}
       */
        iterator(const string_map* mapa);

      /**
      * @brief Constructor del iterador.
      *
      * \pre true
      * \post El iterador apunta a la primera tupla <clave, significado> del mapa que itera.
      * Si es vacío, apunta a la posición pasando-el-último
      *
      * \complexity{\O(1)}
      */
        iterator();

        /**
      * @brief Constructor por copia del iterador.
      *
      * \pre true
      * \post El iterador creado itera el mismo mapa que el argumento y
        apunta a la misma tupla <clave, significado>.
      *
      * \complexity{\O(1)}
      */
        iterator(const iterator&);
        using value_type = const string_map::value_type;
        using iterator_category = std::forward_iterator_tag;
        using reference =value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;

        /**
        * @brief Operador de desreferencia.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post Devuelve la tupla <clave, significado> a la que apunta
        *
        * \complexity{\O(L)}
        */
        value_type operator*();

        /**
        * @brief Operador de referencia.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post Devuelve una referencia a la tupla <clave, significado> a la que apunta
        *
        * \complexity{\O(L)}
        */
        value_type* operator->();

        /**
        * @brief Avanza el iterador.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post La clave es la clave siguiente a la original en orden lexicográfico, o
        * el string vacio si llegó a la posición pasando-el-último
        *
        * \complexity{\O(L)}
        */
        iterator& operator++();

        /**
        * @brief Operador de igualdad.
        *
        * \pre true
        * \post true sii iteran el mismo mapa y se encuentan apuntando a la misma clave
        *
        * \complexity{\O(1)}
        */
        bool operator==(const iterator& o_it) const;

        /**
        * @brief Operador de diferencia.
        *
        * \pre true
        * \post true sii no iteran el mismo mapa o
        * itera el mismo mapa pero no se encuentan apuntando a la misma clave
        *
        * \complexity{\O(1)}
        */
        bool operator!=(const iterator& o_it) const;

        /**
        * @brief Consulta si llego al final.
        *
        * \pre true
        * \post true sii el iterador apunta a la posición pasando-el-último
        *
        * \complexity{\O(1)}
        */
                bool isEnd();

    private:

        const string_map* mapa;
        friend class string_map;
        key_type claveActual;
        const mapped_type* valorActual;
        pointer tuplaActual;

    };

    class const_iterator{

        public:

        /**
        * @brief Devuelve la clave actual del iterador
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post \P{res} es el primer elemento de la tupla<clave, significado>
        * a la que apunta el iterador.
        *
        * \complexity{\O(1)}
        */
            key_type getClave() const;

        /**
        * @brief Constructor del iterador.
        *
        * \pre true
        * \post El iterador apunta a la primera tupla <clave, significado> del mapa que itera.
        * Si es vacío, apunta a la posición pasando-el-último
        *
        * \complexity{\O(1)}
        */
            const_iterator(const string_map* mapa);

        /**
        * @brief Constructor del iterador.
        *
        * \pre true
        * \post El iterador apunta a la primera tupla <clave, significado> del mapa que itera.
        * Si es vacío, apunta a la posición pasando-el-último
        *
        * \complexity{\O(1)}
        */
            const_iterator();
            using value_type = const string_map::value_type;
            using iterator_category = std::forward_iterator_tag;
            using reference = value_type&;
            using pointer = value_type*;
            using difference_type = std::ptrdiff_t;

        /**
        * @brief Operador de desreferencia.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post Devuelve la tupla <clave, significado> a la que apunta
        *
        * \complexity{\O(L)}
        */
            value_type operator*();

        /**
        * @brief Operador de referencia.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post Devuelve una referencia a la tupla <clave, significado> a la que apunta
        *
        * \complexity{\O(L)}
        */
            value_type* operator->();

        /**
        * @brief Avanza el iterador.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post La clave es la clave siguiente a la original en orden lexicográfico, o
        * el string vacio si llego a la posición pasando-el-último
        *
        * \complexity{\O(L)}
        */
            const_iterator& operator++();

        /**
        * @brief Operador de igualdad.
        *
        * \pre true
        * \post true sii itera el mismo mapa y se encuentan apuntando a la misma clave
        *
        * \complexity{\O(1)}
        */
            bool operator==(const const_iterator &o_it) const;

/**
        * @brief Operador de diferencia.
        *
        * \pre true
        * \post true sii no itera el mismo mapa o
        * itera el mismo mapa pero no se encuentan apuntando a la misma clave
        *
        * \complexity{\O(1)}
        */
            bool operator!=(const const_iterator &o_it) const;
        /**
        * @brief Consulta si llego al final.
        *
        * \pre true
        * \post true sii el iterador apunta a la posición pasando-el-último
        *
        * \complexity{\O(1)}
        */
            bool isEnd();

    private:
        const string_map* mapa;
        friend class string_map;
        key_type claveActual;
        const mapped_type* valorActual;
        pointer tuplaActual;

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

    string_map();

    /** @brief Destruye mapa
     *
     * \complexity{\O(sn * S)}
     */
    ~string_map();

    /** @brief Constructor por copia
     *
     * \pre true
     * \post res = @param
     *
     * \complexity{\O(sn * (S + copy(value_type)))}
     */
    string_map(const string_map &);

    /** @brief Operador de asignacion
     *
     * \pre true
     * \post res = @param
     *
     * \complexity{\O(sn * (S + copy(value_type)) }
     */
    string_map& operator=(const string_map &);

    /** @brief Operadores de comparacion
     *
     * \pre true
     * \post res  = (claves(this) = claves(otro) \LAND (\FORALL k :claves(this))( obtener(k,this) = obtener(k,otro))    )
     *
     * \complexity{\O(sn * (S+cmp(T)))}
     */
    bool operator==(const string_map& otro) const;

    /** @brief Operadores de comparacion
      *
      * \pre true
      * \post res  = (claves(this) != claves(otro) \LOR \LNOT (\FORALL k :claves(this))( obtener(k,this) = obtener(k,otro))    )
      *
      * \complexity{\O(sn * (S+cmp(T)))}
      */
    bool operator!=(const string_map& otro) const;

    /** @brief Cantidad de apariciones de la clave (0 o 1)
     *  @param key clave a buscar
     *
     *  \pre true
     *  \post res = if def?(this, key) then 1 else 0 fi
     *
     *  \complexity{\O(S)}
     */
    size_type count(const key_type &key) const;

    /** @brief Devuelve cantidad de claves definidas
     *
     * \pre true
     * \post res = #claves(this)
     *
     * \complexity{\O(1)}
     */
    size_t size() const;

    /** @brief devuelve true si size() == 0
     *
     * \pre true
     * \post res = if #claves(this) = 0 then true else false fi
     *
     * \complexity{\O(1)}
     */
    bool empty() const;

    /** @brief Acceso / definición de pares clave/valor
     *  @param key clave a acceder, si no existe, se crea
     *  @returns una referencia a la definicion.
     *
     * \pre true
     * \post res = significado(key, this)
     *
     *  \complexity{\O(S + copy(T))}
     */
    mapped_type& operator[](const key_type &key);

    /** @brief Acceso a una clave sin modificar mapa
     *  @param key clave a acceder que debe existir previamente
     *  @returns una referencia a la definicion.
     *
     * \pre def?(this, key)
     * \post res = significado(key, this)
     *
     *  \complexity{\O(S + copy(T))}
     */
    mapped_type& at(const key_type& key);

    /** @brief Acceso a una clave sin modificar mapa
     *  @param key clave a acceder que debe existir previamente
     *  @returns una referencia const a la definicion.
     *
     * \pre def?(this, key)
     * \post res = significado(key, this)
     *
     *  \complexity{\O(S + copy(T))}
     */
    const mapped_type& at(const key_type& key) const;

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
   iterator find(const key_type &key);

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
   const_iterator find(const key_type &key) const;

    /* */
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
     * ademas, obtener(this,value.first) = value.second
     * \complexity{\O(S + copy(value_type))}
     */
    pair<iterator,bool> insert(const value_type &value);

    /*  */
    /** @brief eliminar una clave
     *  @param key clave a eliminar
     *  @returns cantidad de elementos eliminados
     *
     *  \pre this = dicc0
     *  \post key \NOTIN claves(this) \AND res = if clave \ISIN claves(dicc0) then 1 else 0 fi
     *
     *  \complexity{\O(S)}
     */
    size_type erase(const key_type& key);

    /** @brief eliminar una clave mediante irerador
     *  @param pos iterador apuntando a clave a eliminar
     *  @returns iterador apuntando el proximo de la clave eliminada (o end() si era la ultima)
     *
     *  \pre this = dicc0
     *  \post key \NOTIN claves(this) \AND la claveActual del iterador resultante es la siguiente clave
     *  y valorActual del iterador resultante es un puntero a this.at(claveActual)
     *  o un puntero nulo en caso de ser el fin de la coleccion.
     *  \LAND res = if clave \ISIN claves(dicc0) then 1 else 0 fi
     *  \complexity{\O(S)}
     */
    iterator erase(iterator pos);


    string siguienteClave(string claveActual) const;

private:

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: string_map \TO bool\n
     * rep(m) \EQUIV
     *  si la raiz esta apuntando a nullptr como valor, y no tiene hijos
     *  entonces el string_map no tiene ninguna clave con un significado definido.
     *  Si un nodo distinto a la raiz apunta a nullptr como valor, entonces
     *  tiene que tener al menos un hijo, a menos que sea la raiz.
     *  Todas las otras hojas del arbol tienen un valor distinto de nullptr.
     *  "" no es una clave valida, y nullptr no un valor valido.
     *  (pues los usamos para marcar justamente el end en el iterador, y la ausencia de valores).
     *  La cantidad de claves es igual a la cantidad de strings
     *  tal que el significado existe (i.e., no es nullptr).
     *
     * abs: string_map \TO Diccionario(string, T)\n
     * abs(m) \EQUIV m' tal que es un dicc e \|
     *  * #claves(m') = m._cantidadDeClaves \AND
     *  * \FORALL (c : string) def?(c,m') \IMPLIES string_map[c]=obtener(m',c)
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    struct Nodo {
        map<char, Nodo*> hijos;
        value_type* valor;
        Nodo(value_type* v) : valor(v) {};
    };

    Nodo* raiz;
    size_t _cantidadDeClaves;
    string primeraClave() const;
    Nodo* findNodo(string key)const;
    vector<Nodo*> getBranch(string key)const;
};
#include "string_map.hpp"

#endif //STRING_MAP_STRING_MAP_H
