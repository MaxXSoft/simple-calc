#ifndef CALC_GLOBAL_H_
#define CALC_GLOBAL_H_

#include <cstdio>

inline int PrintLn(const char *Str) {
    return fprintf(stderr, "%s\n", Str);
}

inline int Print(const char *Str) {
    return fprintf(stderr, "%s", Str);
}

template<class T>
inline int GetArrayLength(T &Array) {
    return sizeof(Array) / sizeof(Array[0]);
}

#endif