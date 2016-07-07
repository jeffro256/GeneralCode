#include <iostream>
#include "miscutils.hpp"
using namespace std;

int main() {
    vector<int> vec;
    vec.push_back(2);
    vec.push_back(420);
    vec.push_back(360);
    vec.push_back(21);
    vec.push_back(1738);
    vec.push_back(69);
    vec.push_back(42);

    for (int i = 0; i < vec.size(); i++) {
         cout << vec[i] << ' ';
    }
    cout << endl;

    jeff::ezremove(vec, 360);
    jeff::ezremove(vec, 69);

    for (int i = 0; i < vec.size(); i++) {
         cout << vec[i] << ' ';
    }
    cout << endl;

    return 0;
}
