//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include "questao.h"
#include "gtest/gtest.h"

using namespace std;

const char SEP[] = ",.;:/|-&%$+=*?";
const char VOGAIS[] = "aeiouy";
const char CONS[] = "bcdfghjklmnpqrstvwxz";

class TesteQuestao: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }
    string gen_word(int N, int mins=0) {
        string s;
        int n;
        bool vogal = rand() % 2;

        n = mins + (rand() % N);
        while (n-- > 0) {
            if (vogal) s += VOGAIS[rand()%(sizeof(VOGAIS)-1)];
            else s+= CONS[rand()%(sizeof(CONS)-1)];
            vogal = not vogal;
        }
        return s;
    }

    string gen_sep(int n) {
        string s;
        //int n;

        //n = rand() % N;
        while (n-- > 0) {
            if ((rand() % 10) < 5) s += (char)('a'+(rand() % 26));
            else s += SEP[rand()%(sizeof(SEP)-1)];
        }
        return s;
    }

    string gen_string(string & s, list<string> & q, int nsep) {
        string sep = gen_sep(nsep);
        string w;

        int j = 2+(rand()%20); // qtde de substrings
        while (j-- > 1) {
            w = gen_word(10,1);
            q.push_back(w);
            s += w;
            s += sep;
        }
        w = gen_word(10,1);
        q.push_back(w);
        s += w;

        return sep;
    }

    string mostra(list<string> & l, char sep=' ') {
        ostringstream out;

        for (auto & x: l) out << x << sep;
        string res = out.str();
        res.pop_back();
        return res;
    }
};

TEST_F(TesteQuestao, Vazia)
{
    try {
        list<string> q;
        string r = junta(q, gen_sep(1+(rand()%4)));

        if (r.size() > 0) {
            FAIL() << "string tem tamanho maior que 0 após juntar strings de uma lista vazia";
            return;
        }

    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}

TEST_F(TesteQuestao, Simples)
{
    for (int j=0; j < 10; j++) {
        try {
            list<string> q;
            string w = gen_word(10,1+(rand()%3));
            q.push_back(w);
            string sep;
            while (true) {
                sep = gen_sep(2);
                if (w.find(sep) == string::npos) break;
            }
            string r = junta(q, sep);

            if (r != w) {
                auto res = mostra(q);
                FAIL() << "string obtida deveria ser igual à única string existente na lista"
                       << "lista: "+res
                       << "string obtida: "+r;
                return;
            }

        } catch (...) {
            FAIL() << "ocorreu uma exceção";
        }
    }
}

TEST_F(TesteQuestao, Normal) {
    string sep;
    list<string> q;

    try {
        for (int n=0; n < 10; n++) {
            string s;
            s = "";
            q.clear();
            sep = gen_string(s, q, 1+(rand()%4));
            string r = junta(q, sep);

            if (s != r) {
                auto res = mostra(q);
                FAIL() << "Após juntar: LISTA="+res+"; SEPARADOR="+sep
                       << "; Obteve resultado: "+r
                       << "; Esperado: "+s;
                return;
            }
        }
    } catch (...) {
        auto res = mostra(q);
        FAIL() << "ocorreu uma exceção: lista="+res
               << ">>> sep="+sep;
    }
}

TEST_F(TesteQuestao, SemSeparador)
{
    string sep;
    list<string> q;

    try {
        for (int n=0; n < 10; n++) {
            string s;
            s = "";
            q.clear();
            sep = gen_string(s, q, 1);
            string r = junta(q, sep);

            if (s != r) {
                auto res = mostra(q);
                FAIL() << "Após juntar: LISTA="+res+"; SEPARADOR="+sep
                       << "; Obteve resultado: "+r
                       << "; Esperado: "+s;
                return;
            }
        }
    } catch (...) {
        auto res = mostra(q);
        FAIL() << "ocorreu uma exceção: lista="+res
               << ">>> sep="+sep;
    }
}

TEST_F(TesteQuestao, SeparadorSimples)
{
    string sep;
    list<string> q;

    try {
        for (int n=0; n < 10; n++) {
            string s;
            s = "";
            q.clear();
            sep = gen_string(s, q, 2);
            string r = junta(q, sep);

            if (s != r) {
                auto res = mostra(q);
                FAIL() << "Após juntar: LISTA="+res+"; SEPARADOR="+sep
                       << "; Obteve resultado: "+r
                       << "; Esperado: "+s;
                return;
            }
        }
    } catch (...) {
        auto res = mostra(q);
        FAIL() << "ocorreu uma exceção: lista="+res
               << ">>> sep="+sep;
    }
}
