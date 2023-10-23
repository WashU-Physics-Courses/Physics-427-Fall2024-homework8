# Physics 427 Homework 7

__Due 11:59pm Monday 10/30/2023__

## 1. 1D Advection Equation

Let's implement a numerical method to solve the simple 1D advection equation:
$$
\frac{\partial u}{\partial t} + v\frac{\partial u}{\partial x} = 0
$$

In a C++ header file `problem1.h`, implement the Lax-Wendroff method to solve the advection equation. Your function should have the following signature:
    
```cpp
std::vector<double> lax_wendroff(const std::vector<double> &u,
                                 double v, double dx, double dt);
```

where `u` is the array of values of $u$ at the current time step, `v` is the advection velocity, `dx` is the grid spacing, and `dt` is the time step. The function should return a `std::vector<double>` that contains the values of $u$ at the next time step. Use one ghost cell on each side of the domain to implement periodic boundary conditions. The output array should have periodic boundary conditions already applied.

In a separate C++ source file `problem1.cpp`, write a program that uses your `lax_wendroff` function to solve the advection equation for the following initial condition on a domain $x\in [0, 1]$:
$$
u(x, 0) = e^{-(x - 0.5)^2/\sigma^2}, \quad \sigma = 0.05.
$$
Use a grid with $N_x = 1000$ (remember there is a ghost cell at each end, so only $998$ are physical cells) and a time step $\Delta t = 0.9\Delta x / v$. Use an advection velocity of $v = 1.0$. Run your simulation for a total time of $t = 1.0$. Create an output every time $t$ elapses by $0.01$, and write the values of $u$ in a csv file. Plot the outputs and create a movie of the evolution of $u$ in time. You can use the included `plot_problem1.py` script to make the plots. To create the movie, install the package `ffmpeg` using your package manager (`apt-get` in WSL, or `brew` on Mac), and then run the following command in a terminal:
```bash
ffmpeg -framerate 10 -i u_%03d.png -c:v libx264 -vf "pad=ceil(iw/2)*2:ceil(ih/2)*2" -pix_fmt yuv420p problem1.mp4
```
This command will take in all the `png` files under the current directory named in the form of `u_001.png`, use `libx264` as the video encoder, pad the image to have even number of pixels on both width and height, and make a movie `problem1.mp4` using the `yuv420p` pixel format. Commit the resulting `problem1.mp4` to the repository. DO NOT COMMIT CSV FILES OR BINARY FILES TO THE REPOSITORY!

## 2. LU Decomposition of a Tri-diagonal Matrix

In this problem, we implement the LU decomposition of a tri-diagonal matrix, in order to prepare for the next problem. I have included a skeleton file `tri_diagonal.h` with a class structure. You will need to implement 3 functions, `compute_lu`, `solve`, and `multiply`. 

The `compute_lu` function should compute the LU decomposition of the given tri-diagonal matrix $A$ (given as three vectors `a`, `b`, and `c`), and populate the values of the two diagonal vectors `l` and `u`.

The `solve` function should take in a vector `r` as right hand side of the matrix equation $Ax = r$, and return the solution vector `x`. You should use the LU decomposition computed in the `compute_lu` function to solve the matrix equation.

The `multiply` function is the most straightforward. It takes in a vector `x` and returns the vector $\mathbf{A}\mathbf{x}$.

I have included a C++ test `test_tri_diagonal.cpp` for you to debug your implementation. Note that the class `tri_diagonal` is a template class, and you will need to instantiate it with a type. For example, to instantiate a `tri_diagonal` object with `double` type, you will need to write:
```cpp
tri_diagonal<double> A(a, b, c);
```
This is done so that we can instantiate it with `std::complex<double>` type in the next problem to solve complex-valued linear systems. Your implementation should not be affected by the fact that this class is a template. Commit your implementation of `tri_diagonal.h` to the Github repository.

## 3. Time-dependent Schrödinger equation in 1D

In this problem, we will try to solve the time-dependent Schrödinger equation in 1D in an infinite potential well. The 1D Schrödinger equation is:
$$
i\hbar \frac{\partial \psi}{\partial t} = -\frac{\hbar^2}{2m}\frac{\partial^2 \psi}{\partial x^2} + V(x)\psi
$$
where $\psi(x, t)$ is the wavefunction, $V(x)$ is the potential, and $m$ is the mass of the particle. Using a procedure similar to HW6 description, we can make this equation dimensionless:
$$
i\frac{\partial \psi}{\partial t} = -\frac{1}{2}\frac{\partial^2 \psi}{\partial x^2} + V(x)\psi
$$
For the purpose of this homework, we will simply take $V = 0$. Consider a domain of $x\in [-10, 10]$. There is an infinite potential barrier at the boundaries of the domain, therefore the boundary conditions are $\psi(-10, t) = \psi(10, t) = 0$.

We start with a Gaussian wave packet that is centered at $x = 0$ and traveling to the right at speed $v$:
$$
\psi(x, 0) = \exp\left(-\frac{x^2}{2\sigma^2} + ivx\right)
$$
where $\sigma$ is the width of the wave packet. Set $\sigma = 0.5$ and $v = 10.0$.

We will use the Crank-Nicolson method to solve this equation. The Crank-Nicolson method utilizes the following discretization of the Schrödinger equation:
$$
\left(1 + \frac{1}{2}i\hat{H}\Delta t\right)\psi^{n+1}_j = \left(1 - \frac{1}{2}i\hat{H}\Delta t\right)\psi^n_j,
$$
where $\hat{H}$ is the Hamiltonian operator, and $\psi^n_j$ is the value of $\psi$ at the $j$-th grid point at time step $n$. The Hamiltonian operator in our case is simply a 2nd order spatial derivative, and it's approximated by a central difference:
$$
\hat{H}\psi^n_j = -\frac{1}{2}\frac{\psi^n_{j+1} - 2\psi^n_j + \psi^n_{j-1}}{\Delta x^2}.
$$
The Crank-Nicolsom method is an implicit method, and it requires solving a linear system at each time step. Fortunately, the linear system is tri-diagonal, and we can use the LU solver you wrote in Problem 2 to solve it.

Write a C++ file `problem3.cpp` to solve the time-dependent Schrödinger equation using the method above. Use $\Delta t = 10^{-3}$ and simulate the wave function for a total of $t = 1.0$. Create an output every time $t$ elapses by $0.01$, and write the values of $\psi$ in a csv file. Since the wave function is complex, you will need to include the header file `<complex>` and use `std::vector<std::complex<double>>` instead of `std::vector<double>` as the type of your arrays. You also need to use the `tri_diagonal<std::complex<double>>` version of the class you implemented in Problem 2. To help facilitate implementing the initial condition, you can include a line before the `main` function:
```cpp
using namespace std::complex_literals;
```
to use the `i` literal for complex numbers. When assigning the initial condition, you can write something like the following:
```cpp
psi[j] = std::exp(-0.5 * (x * x) / (sigma * sigma) + 1.0i * v * x);
```
Here `1.0i` means the imaginary unit $i$.

When writing output, remember to write both the real and imaginary parts of $\psi$ to the csv file. You can do it with the following code snipped:
```cpp
for (int i = 0; i < Nx; i++) {
  double x = x0 + i * dx;
  output_file << x << "," << std::real(psi[i]) << "," << std::imag(psi[i]) << std::endl;
}
```
Plot the outputs and create a movie of the evolution of $\psi$ in time. You can modify the included `plot_problem1.py` script used in Problem 1 to make the plots. Remember to plot $|\psi|^2 = (\mathrm{Re}\ \psi)^2 + (\mathrm{Im}\ \psi)^2$ instead of $\psi$, since $|\psi|^2$ is the probability of finding the particle at position $x$. Use the same `ffmpeg` command as in Problem 1 to create the movie. Commit the resulting `problem3.mp4` to the repository. Commit your plotting script as `plot_problem3.py`. DO NOT COMMIT CSV FILES OR BINARY FILES TO THE REPOSITORY!