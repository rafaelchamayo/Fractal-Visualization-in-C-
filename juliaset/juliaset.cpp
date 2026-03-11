#include <fstream>
#include <complex>
#include <iostream>
using namespace std;

// Our objective is to create a simple image of a julia set of a polynomial complex function of the form.
// f(z) = z^2+c


// First let's define a function to determine if a specific point in the complex plane belongs to the julia set.
// It will take a complex number 'c' and a maximum number of iterations. Then we apply the julia set formula iteratively

int isInJuliaSet(complex<double> z,complex<double>c, int max_iter) {
    int num_iter = 0;
    complex<double> z_n = z;
    for (int i = 0; i < max_iter; i++) {
        z_n = z_n*z_n + c;
        if (norm(z_n) > 4.0) {
            return i; // The point escaped the threshhold in i iterations
        } 
    }
    num_iter = max_iter;
    return num_iter; // The point never escaped
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

    // Defining the initial c constant
    complex<double> c(-0.8 , 0.156);

    // Setting up the output file
    ofstream img("imagejuliaset.ppm");

    img << "P3\n";
    img << width << " " << height << "\n";
    img << "255\n";

    // Setting up the maximum amount of iterations for the julia set calculation
    const int max_iter = 100;

    // Looping through each pixel in the image we will generate. This will allow us to change the parameter 'z'.
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {

            // Mapping each pixel's coordinates to a number in the complex plane
            complex<double> z(x_min + (x_max-x_min)* (double)x / width , y_min + (y_max-y_min)*(double)y/height);

            // We will also keep track of the number of iterations it takes for a number to escape
            int iter_escaped = 0;

            // We determine if the point 'c' belongs to the Mandelbrot set by calculating it's escaped iterations
            iter_escaped = isInJuliaSet(z,c, max_iter);

            // Output the result as a grayscale in the image.
            double t = 255.0 * iter_escaped / max_iter;
            int r = t;
            int g = t;
            int b = t;
            img << r << " " << g << " " << b << "\n";
            // If a point is in the mandelbrot set it the pixel it was mapped from will be shown as white
            // The less iterations an object takes to escape the set the darker shade of black it gets colored

        }
    }

    cout << "Julia set image generated as 'imagejuliaset.ppm'" << endl;
    return 0;

}