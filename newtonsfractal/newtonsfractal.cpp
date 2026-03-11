#include <fstream>
#include <complex>
#include <iostream>
#include <vector>
using namespace std;

// For the optional fractal i will do a c++ implementation of newton's fractal. I chose this fractal as i found fascinating
// from a while back how from a relatively simple method for approximating roots of polynomials chaos can emerge when you
// consider the effect the algorithm has in the complex plane. I think it can really capture how chaotic the output of an 
// algorithm, even from relatively simple one, can be. Because of this I think it might be helpful to later on understand
// how to represent algorithms with fractals.

// Let's create a newton fractal for the polynomial P(z)=z^5+z^2-z+1.

//First let's define a function to calculate the polynomial and its derivative
complex<double> P(complex<double> z) {
    return z*z*z*z*z+z*z-z+complex<double>(1.0,0);
}

complex<double> dPdz(complex<double> z) {
    return complex<double>(5.0,0.0)*z*z*z*z+complex<double>(2.0,0.0)*z-complex<double>(1.0,0.0);
} 

// Calculating the distance between two complex numbers in the complex plane
double distance(complex<double> z1, complex<double> z2) {
    complex<double> diff = z1-z2;
    return abs(diff);
}

// Then we want to create a function that decides to which root an initial guess gets closest to after
// n iterations of the newton-raphson method.
int closestRoot(vector<complex<double>> roots, complex<double> z,  int max_iter) {
    for (int i = 0; i<max_iter; i++) {
        z = z-P(z)/dPdz(z);
    }
    vector<double> closestroot({0.0,0.0});
    
    for (int i = 0; i < 5; i++) {
        if (i == 0) {closestroot[0]=distance(z,roots[0]); closestroot[1]=1.0;}
        if (distance(z,roots[i])<closestroot[0]){closestroot = {distance(z,roots[i]),(double)i+1.0};}
    }

    return (int)closestroot[1];
}

int main() {

    // Defining the dimensions of the image
    int width = 800;    
    int height = 600;

    // Defining the x-y limit coordinates
    double x_max = 2.0;
    double x_min = -2.0;
    double y_max = 1.5;
    double y_min = -1.5;

    // Defining the initial roots
    vector<complex<double>> roots({complex<double>(-1.3247,0),complex<double>(0,-1.0),complex<double>(0.0,1.0),complex<double>(0.66236,0.56228),complex<double>(0.66236,-0.56228)});

    // Setting up the output file
    ofstream img("imagenewtonfractal.ppm");

    img << "P3\n";
    img << width << " " << height << "\n";
    img << "255\n";

    // Setting up the maximum amount of iterations of the newton raphson method
    const int max_iter = 20;

    // Looping through each pixel in the image we will generate. This will allow us to change the parameter 'z'.
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {

            // Mapping each pixel's coordinates to a number in the complex plane
            complex<double> z(x_min + (x_max-x_min)* (double)x / width , y_min + (y_max-y_min)*(double)y/height);

            // Defining a parameter to store the closest root
            int root = 0;

            // We determine if the point 'c' belongs to the Mandelbrot set by calculating it's escaped iterations
            root = closestRoot(roots, z, max_iter);

            // Color coding the point depending on which root is closest
            if (root == 1) {
                img << 92 << " " << 0 << " " << 110 << "\n";
            } else if (root == 2) {
                img << 40 << " " << 150 << " " << 150 << "\n";
            } else if (root == 3) {
                img << 110 << " " << 220 << " " << 120 << "\n";
            } else if (root == 4) {
                img << 240 << " " << 220 << " " << 90 << "\n";
            } else if (root == 5) {
                img << 10 << " " << 20 << " " << 90 << "\n";
            }

        }
    }

    cout << "Newton's fractal image generated as 'imagenewtonsfractal.ppm'" << endl;
    return 0;

}