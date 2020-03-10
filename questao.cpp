// implemente aqui sua função
#include "questao.h"


string junta(list<string> & l, const string & delim){

    string r;
    int n = l.size();

    for (auto & sub: l) {
        r += sub;
        n--;
        if (n>0) r += delim;
    }

    return r;
}