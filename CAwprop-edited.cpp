#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
using std::fixed;
using std::endl;
using std::cerr;
using std::cout;
using std::ifstream;
// Cellular Automaton Simulation on a Triangular Grid
// © 2021 N. Sukumar, Aditi Iyer
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <sstream> 
double xx(int lat, int longitude){
	double pi=3.14159165359;
	double x=sin(pi*((double)lat/60.))*cos(pi*(double)longitude/60.);
	return x;
}
double yy(int lat, int longitude){
	double pi=3.14159165359;
	double y=sin(pi*((double)lat/60.))*sin(pi*(double)longitude/60.);
	return y;
}

double zz(int lat){
	double pi=3.14159165359;
	double z=cos(pi*((double)lat/60.));
	return z;
}
const int MAX_CHAR = 20

int main()
{
char file_name[MAX_CHAR];
ofstream ofile;

cout << "File name - "
cin >> setw (sizeof (file_name)) >> file_name;
ofile.open(file_name);

	int nlong=120;
	int nlat=60;
        int site[2][120][60], prev[2][120][60];
	int tmax=10;
	double x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6;
	int long1;

//
//	Open Initial configuration file
//
   ifstream myfile;
   myfile.open ("file.tsv");

//
//	Initialize state of CA
//
	for (int lat=0; lat<nlat; lat++){
		for (int longitude=0; longitude<nlong; longitude++){
		    for(int i=0; i<2; i++){
		  if (myfile.is_open())
			site[i][longitude][lat] = 0;
		    }
		}
	}
   int lat;
   int longitude;
   int junk;
   //double junk;
    while (!myfile.eof())
    {
      myfile >> lat >> longitude >> junk;
	//myfile >> lat >> longitude >> junk;
     // prev[1][longitude][lat] = junk;
     // prev[2][longitude][lat] = junk;
     prev[1][longitude][lat] = junk;
     prev[2][longitude][lat] = junk;
     // cout << prev[1[longitude]][lat] << prev[2][longitude][lat] << endl;
     cout << prev[1][lat][longitude] << prev[2][lat][longitude] << endl;
    }
//
////	Start time loop
//
   for (int t=0; t<tmax; t++){
   cout << t << endl;

//	Each band consists of nlong squares with vertices at (long,lat), (long+1,lat), (long,lat+1), (long+1,latlat+1)

	for (int lat=1; lat<=nlat; lat++){
		for (int longitude=0; longitude<nlong; longitude++){
		    if(longitude < nlong-1){

				long1 = longitude+1;
			} else {
				long1 = 0;		 // Periodic Boundary Conditions
			}
//	Each parallelogram consists of two triangles - an upper and a lower (inverted) one
//	Generate lower triangle with vertices (lat-1, longitude), (lat-1, longitude+1) and (lat, longitude+1)
//	but skip this for the first band which consist of nlong trangles with one vertex at the North Pole (lat = 0)
		    if (lat > 1){
                	x1 = xx(lat-1, longitude);
                	y1 = yy(lat-1, longitude);
                	z1 = zz(lat-1);
			x2 = xx(lat-1, long1);
			y2 = yy(lat-1, long1);
			z2 = zz(lat-1);
			x3 = xx(lat, long1);
			y3 = yy(lat, long1);
			z3 = zz(lat);
                    }
//	Generate upper triangle with vertices (lat, longitude), (lat-1, longitude) and (lat, longitude+1)
//	but skip this for the last band which consist of nlong trangles with one vertex at the South Pole (lat = nlat)
		    if (lat < nlat-1){
//	Write out state of CA
			x4 = xx(lat-1, longitude);
			y4 = yy(lat-1, longitude);
			z4 = zz(lat-1);
                	x5 = xx(lat, longitude);
                	y5 = yy(lat, longitude);
                	z5 = zz(lat);
			x6 = xx(lat, long1);
			y6 = yy(lat, long1);
			z6 = zz(lat);
		    }
//      Iterate & Apply CA rule
site[0][longitude][lat] = ((prev[0][longitude][lat] + prev[0][longitude][lat - 1] + prev[0][long1][lat - 1] + prev[0][long1][lat])) / 4 % 10;
site[1][longitude][lat] = ((prev[1][longitude][lat] + prev[1][longitude][lat - 1] + prev[1][longitude][lat] + prev[1][long1][lat])) / 4 % 10;

		for (int i=0; i<2; i++){
    			prev[i][longitude][lat]=(site[i+1]-site[i-1])/2
						}

//site[0][longitude][lat] = (prev[0][longitude][lat] + prev[0][longitude][lat-1] + prev[0][long1][lat-1] + prev[0][long1][lat]) % 10;
//site[1][longitude][lat] = (prev[1][longitude][lat] + prev[1][longitude][lat-1] + prev[1][longitude][lat] + prev[1][long1][lat]) % 10;
	      	    //for (int i=0; i<2; i++){
			//prev[i][longitude][lat] = site[i][longitude][lat];
//
//      Write out state of CA
//      Write out lower triangle
		    if (lat > 1){
			cout << x1 << ',' << y1 << ',' << z1 << ',' << site[0][longitude][lat] << endl;
			cout << x2 << ',' << y2 << ',' << z2 << ',' << site[0][longitude][lat] << endl;
                        cout << x3 << ',' << y3 << ',' << z3 << ',' << site[0][longitude][lat] << endl;
		    }
//      Write out upper triangle
		    if (lat < nlat-1){
			cout << x4 << ',' << y4 << ',' << z4 << ',' << site[0][longitude][lat] << endl;
                        cout << x5 << ',' << y5 << ',' << z5 << ',' << site[0][longitude][lat] << endl;
			cout << x6 << ',' << y6 << ',' << z6 << ',' << site[0][longitude][lat] << endl;
		    }
		}
	}

   }
myfile.close();
ofile.close();
return 0;

}
