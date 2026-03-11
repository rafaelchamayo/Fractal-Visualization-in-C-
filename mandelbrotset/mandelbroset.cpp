#include <fstream>
#include <complex>
#include <iostream>
using namespace std;

// Our objective is to create a simple image of the Mandelbrot set.


// First let's define a function to determine if a specific point in the complex plane belongs to the Mandelbrot set.
// It will take a complex number 'c' and a maximum number of iterations. Then we apply the Mandelbrot formula iteratively

int isInMandelbrotSet(complex<double> c, int max_iter) {
    int num_iter = 0;
    complex<double> z = 0;
    for (int i = 0; i < max_iter; i++) {
        z = z*z + c;
        if (norm(z) > 4.0) {
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


    // Setting up the output file
    ofstream img("imagemandelbrotset.ppm");

    img << "P3\n";
    img << width << " " << height << "\n";
    img << "255\n";

    // Setting up the maximum amount of iterations for the Mandelbrot set calculation
    const int max_iter = 400;

    // Looping through each pixel in the image we will generate. This will allow us to change the parameter 'c'.
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {

            // Mapping each pixel's coordinates to a number in the complex plane
            complex<double> c(x_min + (x_max-x_min)* (double)x / width , y_min + (y_max-y_min)*(double)y/height);

            // We will also keep track of the number of iterations it takes for a number to escape
            int iter_escaped = 0;

            // We determine if the point 'c' belongs to the Mandelbrot set by calculating it's escaped iterations
            iter_escaped = isInMandelbrotSet(c, max_iter);

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

    cout << "Mandelbrot set image generated as 'image.ppm'" << endl;
    return 0;

}