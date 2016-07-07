#pragma once

template <typename T = float>
struct PhysicsBody {
    T mass;
    T x;
    T y;
    T z;
    T Vx;
    T Vy;
    T Vz;
    T Ax;
    T Ay;
    T Az;

    void applyForce(T Nx, T Ny, T Nz);
    void applyForceX(T Nx);
    void applyForceY(T Ny);
    void applyForceZ(T Nz);
    void update(T step);
};

typedef PhysicsBody<> PBody;
