#include <iostream>
#include "vector/vector.h"


int main() {
    srand((unsigned int)time(NULL));
    Vector<int> v(10, 5, 0);
    printf("------print v:\n");
    for(Rank i = 0; i<v.size(); i++) {
        v[i] = rand() % 100;
        std::cout<<"v["<<i<<"]="<<v[i]<<"\n";
    }

    printf("------sort v:\n");
    v.sort(0, v.size());
    for(Rank i = 0; i<v.size(); i++) {
        std::cout<<"v["<<i<<"]="<<v[i]<<"\n";
    }

    int e = rand()%100;
    printf("------search %d: %d\n", e, v.search(e));

    e = rand()%100;
    printf("------insert %d: \n", e);
    v.insert(0, e);
    e = rand()%100;
    printf("------insert %d: \n", e);
    v.insert(0, e);
    e = rand()%100;
    printf("------insert %d: \n", e);
    v.insert(0, e);
    e = rand()%100;
    printf("------insert %d: \n", e);
    v.insert(0, e);
    e = rand()%100;
    printf("------insert %d: \n", e);
    v.insert(0, e);
    e = rand()%100;
    printf("------insert %d: \n", e);
    v.insert(0, e);
    for(Rank i = 0; i<v.size(); i++) {
        std::cout<<"v["<<i<<"]="<<v[i]<<"\n";
    }

}
