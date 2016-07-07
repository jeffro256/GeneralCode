#include "mathex.hpp"

template<typename T>
T clamp(T num, T l1, T l2) {
    if (l2 < l1) swap(l1, l2);
    return std::max(l1, std::min(num, l2));
}
