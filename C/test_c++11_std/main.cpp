#ifdef __cplusplus
#include <iostream>
using namespace std;
#else
#include <stdio.h>
#endif

int main() {
    #ifndef __cplusplus
        printf("This was not compiled with a c++ compiler.\n");
    #elif __cplusplus >= 201103L
        cout << "This was compiled with a compiler that has full c++11 support: " << __cplusplus << endl;
    #elif __cplusplus > 199711L
        cout << "This was compiled with a compiler thas has partial c++11 support: " << __cplusplus << endl;
    #else
        cout << "This was compiled with a compiler that has no c++11 support: " << __cplusplus << endl;
    #endif

    return 0;
}
