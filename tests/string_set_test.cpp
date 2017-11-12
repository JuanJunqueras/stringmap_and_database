#include <gtest/gtest.h>
#include <list>
#include "../src/string_set.h"

TEST(string_set_test, test_constructor) {
    string_set s1,s2;
    string_set s3(s1);
}

TEST(string_set_test, test_insercion) {
    string_set s1;
    EXPECT_EQ(s1.size(),0);
    s1.insert("strikingLoo");
    EXPECT_EQ(s1.size(),1);
    s1.insert("pablo");
    EXPECT_EQ(s1.count("strikingLoo"),1);
    EXPECT_EQ(s1.count("pablo"),1);
    EXPECT_EQ(s1.count("hola"), 0);
    EXPECT_EQ(s1.count("pab"), 0);
}

TEST(string_set_test, test_comparar) {
    string_set s1,s2;
    s1.insert("hola");
    s1.insert("mundo");
    EXPECT_FALSE(s1==s2);
    s2.insert("hola");
    s2.insert("mundo");
    EXPECT_TRUE(s1==s2);
}

TEST(string_set_test, test_copiar) {
    string_set s1;
    s1.insert("hola");
    s1.insert("mundo");
    string_set s2(s1);
    EXPECT_TRUE(s1==s2);
    string_set s3;
    EXPECT_FALSE(s1==s3);
}

TEST(string_set_test, test_asignar) {
    string_set s1,s2;
    s1.insert("hola");
    s1.insert("mundo");
    EXPECT_FALSE(s1==s2);
    s2 = s1;
    EXPECT_TRUE(s1==s2);
    s2 = string_set();
    EXPECT_FALSE(s1==s2);
}

TEST(string_set_test, test_eliminar) {
    string_set s1;
    EXPECT_TRUE(s1.empty());
    s1.insert("hola");
    EXPECT_TRUE(s1.count("hola"));
    s1.erase("hola");
    EXPECT_FALSE(s1.count("hola"));
    EXPECT_FALSE(s1.count("ho"));
    s1.insert("hola");
    s1.insert("ho");
    EXPECT_TRUE(s1.count("hola"));
    EXPECT_TRUE(s1.count("ho"));
    s1.erase("ho");
    EXPECT_TRUE(s1.count("hola"));
    EXPECT_FALSE(s1.empty());
    s1.erase("hola");
    EXPECT_FALSE(s1.count("hola"));
    EXPECT_TRUE(s1.empty());
}

TEST(string_set_test, test_vaciar) {
    string_set s1;
    s1.insert("hola");
    s1.insert("ho");
    EXPECT_TRUE(s1.count("hola"));
    EXPECT_TRUE(s1.count("ho"));
    EXPECT_FALSE(s1.empty());
    s1.clear();
    EXPECT_FALSE(s1.count("hola"));
    EXPECT_FALSE(s1.count("ho"));
    EXPECT_TRUE(s1.empty());
}

TEST(string_set_test, test_iterator) {
    string_set s1;
    // 3 ramas disjuntas: las debe iterar en orden lexicográfico
    s1.insert("mundo");
    s1.insert("aaaa");
    s1.insert("hola");
    /**
     * s1:  .-a-a-a-a
     *      |-h-o-l-a
     *      \-m-u-n-d-o
     */
    EXPECT_EQ(s1.begin().operator*(), "aaaa");

    // Agrego subramas de "aa": debe iterar en orden correcto lexicográfico
    s1.insert("aaaab");
    s1.insert("aaaba");
    s1.insert("aabba");
/**
 * s1:  .-a-a-a-a
 *               -b
 *             -b-a
 *           -b-b-a
 *      -h-o-l-a
 *      -m-u-n-d-o
 */

    EXPECT_EQ(s1.begin().operator*(), "aaaa");
    s1.erase("aaaa");
    EXPECT_EQ(s1.begin().operator*(), "aaaab");
    EXPECT_EQ(s1.siguienteElemento("aaaab"), "aaaba");
    EXPECT_EQ(s1.siguienteElemento("aabba"), "hola");

    auto it = s1.find("aabba");
    it = s1.erase(it);
    EXPECT_EQ(it.operator*(), "hola");
    it = s1.find("mundo");
    it = s1.erase(it);
    EXPECT_EQ(it, s1.end());

}