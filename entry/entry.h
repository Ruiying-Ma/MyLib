//
// Created by 马睿赢 on 2023/2/22.
//

#ifndef MY_LIB_ENTRY_H
#define MY_LIB_ENTRY_H

template <typename K, typename V> struct Entry {
    K key;
    V value;
    /* Constructor */
    Entry(K k = K(), V v = V()) : key(k), value(v) {};
    Entry(Entry<K,V> const &e ) : key(e.key), value(e.value) {};
    /* api */
    bool operator< (Entry<K,V> const &e) {return key < e.key;}
    bool operator> (Entry<K,V> const &e) {return key > e.key;}
    bool operator== (Entry<K,V> const &e) {return key == e.key;}
    bool operator!= (Entry<K,V> const &e) {return key != e.key;}
};

#endif //MY_LIB_ENTRY_H
