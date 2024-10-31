#pragma once

#include <vector>

class maxwell_solver {
 public:
  maxwell_solver(int nx, int ny) : Nx(nx), Ny(ny) {
    // Resize the field arrays to the correct size
    Ex.resize(Nx * Ny, 0.0);
    Ey.resize(Nx * Ny, 0.0);
    Ez.resize(Nx * Ny, 0.0);
    Bx.resize(Nx * Ny, 0.0);
    By.resize(Nx * Ny, 0.0);
    Bz.resize(Nx * Ny, 0.0);

    // Set up the domain. We always assume that the domain is a square,
    // with length Lx and Ly both equal to 1.0.
    Lx = 1.0;
    Ly = 1.0;
    dx = Lx / Nx;
    dy = Ly / Ny;
  }

  template <typename F>
  void update_e(const F& J, double t, double dt) {
    // TODO: Finish this function. You can assume that J has the following
    // signature:
    //
    // double J(int n, int i, int j, double t);
    //
    // The component n can be 0, 1, 2 which denotes Jx, Jy, and Jz,
    // respectively. The integers i and j denote which cell it is, and t is the
    // current physical time in the simulation.
  }

  void update_b(double dt) {
    // TODO: Finish this function
  }

  template <typename F>
  void update(const F& J, double dt, int step) {
    double t = step * dt;
    if (step == 0) {
      // at step 0, jump start the integration by integrating forward the E
      // field by half a time step.
      update_e(J, t, dt / 2);
    } else {
      // at other time steps, just update the E field by a full time step
      update_e(J, t, dt);
    }
    // update the B field by a full time step
    update_b(dt);
  }

  int Nx, Ny;
  double Lx, Ly;
  double dx, dy;
  std::vector<double> Ex, Ey, Ez, Bx, By, Bz;
};
