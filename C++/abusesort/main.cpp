#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int intslength = 8;
    int myints[] = {32,71,12,45,26,80,53,33};
    
    // The right way:
    std::vector<int> myvector(myints, myints + intslength);
    std::sort(myvector.begin(), myvector.end());
    
    cout << "Sorted the right way: " << endl;
    for (int i = 0; i < myvector.size(); i++) {
        cout << myvector[i] << ' ';
    }
    cout << endl;
    
    ////////////////////////////////////////////////////////////
    // The wrong way:
    std::sort(myints, myints + intslength);
    
    cout << endl << "Sorted the \"wrong\" way: " << endl;
    for (int i = 0; i < intslength; i++) {
        cout << myints[i] << ' ';
    }
    cout << endl;
    ////////////////////////////////////////////////////////////
    
    return 0;
}
    
    