#include "miscutils.hpp"

#include <iostream>

namespace jeff {
    template <typename T>
    void ezremove(std::vector<T>& v, T val) {
        int pos = std::find(v.begin(), v.end(), val) - v.begin();
        if (pos >= v.size()) return;
    	v[pos] = v[v.size() - 1];
        v.pop_back();
    }
}

template void jeff::ezremove<int>(std::vector<int>& v, int val);
