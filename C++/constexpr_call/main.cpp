#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(NULL));

    constexpr int x = rand();

    for (int i = 0; i < 10; i++) {
       cout << x << endl;
    }

    return 0;
}
