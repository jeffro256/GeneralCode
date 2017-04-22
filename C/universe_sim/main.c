#include "myglutils.h"

#define G 6.67408E-11 /* In Newtons */

typedef struct PointMass {
    double mass;
    double x;
    double y;
    double z;
    double Vx;
    double Vy;
    double Vz;
    double Ax;
    double Ay;
    double Az;
};

int main() {
