#include <iostream>
#include <vector>

#define len(a) (sizeof(a) / sizeof(a[0]))

int main() {
    int original_array[] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
    int length = len(original_array);
    std::vector<int> myvector = std::vector<int>(original_array, original_array + length);

    for (int i = 0; i < length; i++) {
        std::cout << original_array[i] << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < length; i++) {
        std::cout << myvector[i] << ' ';
    }
    std::cout << std::endl;

    int change_index = 1;
    myvector[change_index]++;

    for (int i = 0; i < length; i++) {
        std::cout << original_array[i] << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < length; i++) {
        std::cout << myvector[i] << ' ';
    }
    std::cout << std::endl;

    if (myvector[change_index] != original_array[change_index]) {
        std::cout << "The vector made a copy of original array" << std::endl;
    }
    else {
        std::cout << "The vector points to the original array" << std::endl;
    }

    return 0;
}