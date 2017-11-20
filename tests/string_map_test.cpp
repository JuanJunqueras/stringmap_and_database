#include <gtest/gtest.h>
#include <list>
#include "../src/string_map.h"
#include "../src/Dato.h"

TEST(string_map_test, test_constructor) {
   string_map<int> m1,m2;
     string_map<int> m3(m1);
    string_map<string_map<string> > m4;

}

TEST(string_map_test, test_insercion) {
    string_map<int> m1;
    EXPECT_EQ(m1.size(),0);
    m1.insert(pair<string, int>("strikingLoo", 1));
    EXPECT_EQ(m1.size(),1);
    m1.insert(pair<string, int>("pablo", 5));
    auto falsy = m1.insert(pair<string, int>("pablo", 7));
    EXPECT_EQ(m1.at("strikingLoo"),1);
    EXPECT_EQ(m1.at("pablo"),5);
    EXPECT_EQ(falsy.second,false);
    m1.at("pablo") = 3;
    EXPECT_EQ(m1.at("pablo"),3);
    m1["pablo"] = 4;
    EXPECT_EQ(m1.at("pablo"),4);
    m1["alberto"] = 7;
    EXPECT_EQ(m1.at("alberto"),7);
}

TEST(string_map_test, test_corchetes){
    string_map<int> m1;
    m1["pablo"] = 4;
    EXPECT_EQ(m1.at("pablo"),4);
    m1["alberto"] = 7;
    EXPECT_EQ(m1.at("alberto"),7);
}

TEST(string_map_test, test_clave_iterador){
    string_map<int> m1;
    m1["pablo"] = 4;
    string_map<int>::iterator it = m1.begin();
}

TEST(string_map_test, test_siguiente_clave_con_subtring){

    string_map<int> m1;
    m1["juan"] = 4;
    m1["juancito"] = 5;
    m1["juatir"] = 6;
    m1["jvan"] = 7;

    string juancito = m1.siguienteClave("juan");
    EXPECT_EQ(juancito,"juancito");
    string wtv = m1.siguienteClave("juancito");
    EXPECT_EQ(wtv,"juatir");
    wtv = m1.siguienteClave("juatir");
    EXPECT_EQ(wtv,"jvan");
}
TEST(string_map_test, test_siguiente_clave_sin_substring){
    string_map<int> m1;
    m1["ju"] = 4;
    m1["le"] = 5;
    m1["pe"] = 6;
    string le = m1.siguienteClave("ju");
    EXPECT_EQ(le,"le");
    string pe = m1.siguienteClave("le");
    EXPECT_EQ(pe,"pe");

}
TEST(string_map_test, test_asterisco){
    string_map<int> m1;
    m1["pablorrr"] = 4;
    auto begin = m1.begin();
    string_map<int>::iterator::value_type pair = (*begin);
    ASSERT_EQ(pair.first,"pablorrr");
    ASSERT_EQ(pair.second,4);

}

#ifdef POST_SOLUCION
/*

*/
TEST(string_map_test, test_definir) {
    string_map<int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
    //EXPECT_FALSE(m.count(""));
    m["hola"] = 3;
    //EXPECT_FALSE(m.count(""));
    EXPECT_EQ(m.size(), 1);
    EXPECT_FALSE(m.empty());
    EXPECT_TRUE(m.count("hola"));
    EXPECT_FALSE(m.count("hol"));
    EXPECT_FALSE(m.count("holas"));
    m["ho"] = 1;
    //EXPECT_FALSE(m.count(""));
    EXPECT_EQ(m.size(), 2);
    EXPECT_TRUE(m.count("hola"));
    EXPECT_TRUE(m.count("ho"));
    EXPECT_FALSE(m.count("hol"));
    EXPECT_FALSE(m.count("h"));
    //m[""] = 0;
    EXPECT_EQ(m.size(), 2);
    EXPECT_TRUE(m.count("hola"));
    EXPECT_TRUE(m.count("ho"));
    //EXPECT_TRUE(m.count(""));

    string_map<string> m2;
    m2["mundo"] = "feliz";
    string_map<string_map<string> > m3;
    EXPECT_NE(m2,m3["hola"]);
    m3["hola"]["mundo"] = "feliz";
    EXPECT_EQ(m2,m3["hola"]);
}

TEST(string_map_test, test_obtener) {
    string_map<int> m;
    m["hola"] = 3;
    EXPECT_EQ(m["hola"], 3);
    EXPECT_EQ(m.at("hola"), 3);
    m["ho"] = 1;
    EXPECT_EQ(m["ho"], 1);
    EXPECT_EQ(m.at("ho"), 1);

    // test version const de "at"
    const string_map<int> m2(m);
    EXPECT_EQ(m2.at("ho"), 1);
}

TEST(string_map_test, test_comparar) {
    string_map<int> m1,m2;
    m1["hola"] = 123;
    m1["mundo"] = 456;
    EXPECT_FALSE(m1==m2);
    m2["hola"] = 123;
    m2["mundo"] = 456;
    EXPECT_TRUE(m1==m2);
    m2["mundo"] = 45;
    EXPECT_FALSE(m1==m2);
}

TEST(string_map_test, test_copiar) {
    string_map<int> m1;
    m1["hola"] = 123;
    m1["mundo"] = 456;
    string_map<int> m2(m1);
    EXPECT_TRUE(m1==m2);
    string_map<int> m3;
    EXPECT_FALSE(m1==m3);
}

TEST(string_map_test, test_asignar) {
    string_map<int> m1,m2;
    m1["hola"] = 123;
    m1["mundo"] = 456;
    EXPECT_FALSE(m1==m2);
    m2 = m1;
    EXPECT_TRUE(m1==m2);
    m2 = string_map<int>();
    EXPECT_FALSE(m1==m2);
}

TEST(string_map_test, test_eliminar) {
    string_map<int> m1;
    EXPECT_TRUE(m1.empty());
    m1["hola"] = 123;
    EXPECT_TRUE(m1.count("hola"));
    m1.erase("hola");
    EXPECT_FALSE(m1.count("hola"));
    EXPECT_FALSE(m1.count("ho"));
    //EXPECT_FALSE(m1.count(""));
    m1["hola"] = 1;
    m1["ho"] = 3;
    //m1[""] = 4;
    //m1.erase("");
    EXPECT_TRUE(m1.count("hola"));
    EXPECT_TRUE(m1.count("ho"));
    m1.erase("ho");
    EXPECT_TRUE(m1.count("hola"));
    EXPECT_FALSE(m1.empty());
    m1.erase("hola");
    EXPECT_FALSE(m1.count("hola"));
    EXPECT_TRUE(m1.empty());
}

TEST(string_map_test, test_vaciar) {
    string_map<int> m1;
    m1["hola"] = 1;
    m1["ho"] = 3;
    //m1[""] = 4;
    EXPECT_TRUE(m1.count("hola"));
    EXPECT_TRUE(m1.count("ho"));
    //EXPECT_TRUE(m1.count(""));
    EXPECT_FALSE(m1.empty());
    m1.clear();
    EXPECT_FALSE(m1.count("hola"));
    EXPECT_FALSE(m1.count("ho"));
    //EXPECT_FALSE(m1.count(""));
    EXPECT_TRUE(m1.empty());
}

TEST(string_map_test, test_tipo_complejo) {
    struct punto2d {
        int x,y;
        punto2d() : x(0), y(0) {}
        punto2d(int a, int b) : x(a), y(b) {}
        bool operator==(const punto2d& otro) const { return x == otro.x && y == otro.y; }
        bool operator!=(const punto2d& otro) const { return ! (*this == otro); }
    };
    string_map<punto2d> m;
    m["origen"] = {0,0};
    EXPECT_EQ(m["origen"],m.at("origen"));
    m["origen"].x = 1;
    EXPECT_EQ(m["origen"],punto2d(1,0));
    m["origen"].y = 2;
    EXPECT_NE(m["origen"],punto2d(1,0));
    EXPECT_EQ(m["origen"],punto2d(1,2));
}

TEST(string_map_test, test_iterator) {
    string_map<int> m1;
    // 3 ramas disjuntas: las debe iterar en orden lexicográfico
    m1["mundo"] = 2;
    m1["aaaa"] = 0;
    m1["hola"] = 1;
    /**
     * m1:  .-a-a-a-a[0]
     *      |-h-o-l-a[1]
     *      \-m-u-n-d-o[2]
     */
std::list<int> l1, l2 = {0,1,2};
for (auto p : m1)
l1.push_back(p.second);
EXPECT_EQ(l1,l2);

// Agrego subramas de "aa": debe iterar en orden correcto lexicográfico
m1["aaaab"] = 12;
m1["aaaba"] = 24;
m1["aabba"] = 48;
/**
 * m1:  .-a-a-a-a[0]-b[12]
 *      |    | \b-a[24]
 *      |    \b-b-a[48]
 *      |-h-o-l-a[1]
 *      \-m-u-n-d-o[2]
 */

std::list<int> l3, l4 = {0,12,24,48,1,2};
for (auto p : m1)
l3.push_back(p.second);
EXPECT_EQ(l3,l4);

// Borro 1ra clave: debe apuntar a la siguiente (en este caso una subrama)
EXPECT_EQ(m1.erase("aaaa"), 1);

auto it = m1.find("aaaab");
it = m1.erase(it);
/**
 * m1:  .-a-a-a-b-a[24]
 *      |    \b-b-a[48]
 *      |-h-o-l-a[1]
 *      \-m-u-n-d-o[2]
 */
EXPECT_EQ(it->first, "aaaba");
EXPECT_EQ(it->second, 24);

// borro ultima clave de una subrama: debe devolver la de rama siguiente pasando por la raiz
it = m1.find("aabba");
it = m1.erase(it);
/**
 * m1:  .-a-a-a-b-a[24]
 *      |-h-o-l-a[1]
 *      \-m-u-n-d-o[2]
 */
EXPECT_EQ(it, m1.find("hola"));

// borro ultima clave: debe devolver end()
EXPECT_EQ(m1.erase(m1.find("mundo")), m1.end());
/**
 * m1:  .-a-a-a-b-a[24]
 *      \-h-o-l-a[1]
 */
std::list<int> l5, l6 = {24,1};
for (auto p : m1)
l5.push_back(p.second);
EXPECT_EQ(l5,l6);

}

TEST(string_map_test, no_default) {
    string_map<Dato> dato_map;
    dato_map.insert(make_pair("March", datoStr("March")));
    dato_map.insert(make_pair("EvilMarch", datoNat(-1000)));

    EXPECT_NE(dato_map.find("March"), dato_map.end());
    EXPECT_NE(dato_map.find("EvilMarch"), dato_map.end());
}
#endif // POST_SOLUCION
