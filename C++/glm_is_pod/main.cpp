#include <iostream>
#include <type_traits>
using namespace std;

#include "glm/vec3.hpp"
#include "glm/gtx/string_cast.hpp"

struct Glm_test_struct {
    float hi;
    glm::vec3 a;
    glm::vec3 b;
};

int main() {
    cout << "glm::vec3 is POD = " << is_pod<glm::vec3>::value << endl;
    glm::vec3 ex = { 2.0f, 1.5f, -2.0f };
    cout << "glm::vec3 can use aggregate constructors. Example [ex]: " << glm::to_string(ex) << endl;
    cout << "Glm_test_struct [gts] (struct with glm::vec3s in 'em) is POD = " << is_pod<Glm_test_struct>::value << endl;
    Glm_test_struct gts = { 0.2, { 1, 2, 3}, {6, 5, 4} };
    cout << "Glm_test_struct can use aggregate constructors as well!" << endl;
    cout << "Raw values: " << endl;
    cout << "sizeof(glm::vec3) = " << sizeof(glm::vec3) << endl;
    cout << "sizeof(Glm_test_struct) = " << sizeof(Glm_test_struct) << endl; 

    cout << "Contents of ex: ";
    float* raw_ex_ptr = (float*) &ex;
    for (int i = 0; i < sizeof(glm::vec3) / sizeof(float); i++) {
        cout << raw_ex_ptr[i] << " ";
    }
    cout << endl;

    cout << "Contents of gts: ";
    float* raw_gts_ptr = (float*) &gts;
    for (int i = 0; i < sizeof(Glm_test_struct) / sizeof(float); i++) {
        cout << raw_gts_ptr[i] << " ";
    }
    cout << endl;

    Glm_test_struct uninit;

    cout << "Contents of uninitialized struct with glm: ";
    float* raw_uninit_ptr = (float*) &uninit;
    for (int i = 0; i < sizeof(Glm_test_struct) / sizeof(float); i++) {
        cout << raw_uninit_ptr[i] << " ";
    }
    cout << endl;

    return 0;
}
