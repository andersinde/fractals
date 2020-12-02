#include <iostream>   // std::cout
#include <fstream> // for files manipulation
#include <complex> // for complex numbers
#include <cmath>
using namespace std;

int height = 720;
int width = 1280;
//int height = 6;
//int width = 12;
/*
 * horizon = 2**40
 * log_horizon = log(log(horizon))/log(2)
 */
double log_horizon = log(40)/log(2);


double juliaValueLog(int x, int y, double cr, double ci)  {

	double dx = 2.1;
	double dy = 2.1;//9*dx/16;

	double zr = 2*dx*(float)x/width-dx;
	double zi = 2*dy*(float)y/height-dy; 
	double zr2, zi2;

    unsigned int max_iter = 128;

	for (int i = 0; i<max_iter; i++) {
		zr2 = zr*zr;
		zi2 = zi*zi;
		if (log(zr2+zi2) > 80)
			//return 255*(double(i + 1) - log(log(zr2+zi2)/2));
			return 255*(double(i + 1) - log(log(zr2+zi2))/0.602 + 5.322);
			//return 255*(double(i + 1) - log(0.5*log(zr2+zi2))/40);
		zi = -2*zr*zi + ci; //NOTE: +2 also cool
		zr = zr2 - zi2 + cr;
    }
    return 0;
}

double juliaValueLogKeys(int x, int y, double cr, double ci)  {

	double dx = 2;
	double dy = 2;
	complex<double> z(2*dx*(float)x/width-dx, 2*dy*(float)y/height-dy); 
	complex<double> c(cr, ci);

    unsigned int max_iter = 128;

	for (int i = 0; i<max_iter; i++) {
		z = z * z + c;
		if (log(real(z*z)) > 80) {
			double mu = 255*(double(i + 1) - log(log(real(z*z)))/0.602 + log_horizon);
			if (mu < -2000000000) return 0;
			return mu;
		}
    }
    return 0;
}

double juliaValue(int x, int y, double cr, double ci)  {
	
	double zr = 4*(float)x/width-2;
    double zi = 4*(float)y/height-2;
	double zr2, zi2;

    unsigned int max_iter = 128;

	for (int i = 0; i<max_iter; i++) {
		//z = z * z + c;
		zr2 = zr*zr;
		zi2 = zi*zi;
		if (zr2 + zi2 > 4)
			return 255*i/max_iter;
		zi = 2*zr*zi + ci;
		zr = zr2 - zi2 + cr;
    }
    return 255;
}

int main() {
	int seconds = 5;
	double fps = 60;
	int frames = fps * seconds;

	for (int a = 0; a < frames; a++) { // should be in parallell
		double angle = 2*3.14159*a/frames;
		double r = 0.9;
		double cr = r*cos(angle);
		double ci = r*sin(angle);

	    ofstream my_Image ("frames/" + to_string(a) + ".ppm");

	    if (my_Image.is_open ()) {
	        my_Image << "P3\n" << width << " " << height << " 255\n";
	        for (int y = 0; y < height; y++) {
	            for (int x = 0; x < width; x++)  {
					//int val = juliaValue(x, y, cr, ci);
					//int val = juliaValueLogKeys(x, y, cr, ci);
					int val = juliaValueLog(x, y, cr, ci);
					my_Image << val<< ' ' << val << ' ' << val<< "\n";

					//NOTE: values are larger than 255 so they are showed as val mod 255 in preview causing funny effects
	            }
	        }
	    }
	    my_Image.close();
		std::cout << "done with a = " << a << "\n";
	}
    return 0;
}


//mandelbrot stuff
//int value(int x, int y) {
	//complex<float> point(3.5*(float)x/width-2.5, 2*(float)y/height-1); 
	//complex<float> z(0, 0);
//
    //unsigned int nb_iter = 0;
//
    //while (abs (z) < 2 && nb_iter <= 100) {
           //z = z * z + point;
           //nb_iter++;
    //}
    //if (nb_iter < 101) return 255-(255*nb_iter)/100;
    //else return 255;
//}
