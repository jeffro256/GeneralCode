#include <iostream>
using namespace std;

int& ref2lyfe() {
    static int lyfe = 42;

    cout << "Address: " << &lyfe << endl;

    return lyfe;
}

int main() {
    cout << "Lyfe: " << ref2lyfe() << endl;

    return 0;
}
