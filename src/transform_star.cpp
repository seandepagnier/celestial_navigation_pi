#include "cmath"
#include "astrolabe/astrolabe.hpp"

using namespace astrolabe;
using namespace astrolabe::calendar;
using namespace astrolabe::nutation;

/* Equations come from 
United States Naval Observatory Circular No. 179:
The IAU Resolutions on Astronomical Reference Systems, Time Scales, and Earth Rotation Models:
Explanation and Implementation
by
George H. Kaplan

Downloaded from http://aa.usno.navy.mil/publications/docs/Circular_179.pdf */


const double mas_to_rad = 4.8481368110953599359e-9; // radians per milli-arc-second */
const double as_to_rad = 4.8481368110953599359e-6; // radians per arc second */
const double J2000 = cal_to_jd(2000,1,1.5,true); // 2000 January 1.5


void frame_bias (double &ra, double &dec) {

double r[3], x[3], B[3][3];
int i,j;

// eq. 5.1 or 3.2 from Circular 179:

r[0] = cos(ra) * cos(dec);
r[1] = sin(ra) * cos(dec);
r[2] = sin(dec);

const double deltaAlpha_0 = -14.6 * mas_to_rad;
const double xi_0 = -16.6170 * mas_to_rad;
const double eta_0 = -6.8192 * mas_to_rad;

// eq. 3.3 from Circular 179:

B[0][0] = 1.;
B[0][1] = deltaAlpha_0;
B[0][2] = -xi_0;
B[1][0] = -deltaAlpha_0;
B[1][1] = 1.;
B[1][2] = -eta_0;
B[2][0] = xi_0;
B[2][1] = eta_0;
B[2][2] = 1.;

for(i=0;i<3;++i) {
  x[i] = 0.;
  for (j=0;j<3;++j)
    x[i] += B[i][j] * r[j];
}

// eq. 5.2 from Circular 179:

ra = atan2(x[1], x[0]);
dec = atan2(x[2],sqrt(x[0]*x[0] + x[1]*x[1]));

}

void nutate (double jdd, double &ra, double &dec) {

double r[3], x[3], N[3][3];
int i,j;

// eq. 5.1 from Circular 179:

r[0] = cos(ra) * cos(dec);
r[1] = sin(ra) * cos(dec);
r[2] = sin(dec);

// nutation in longitude
const double deltaPsi = nut_in_lon(jdd);
    
// nutation in obliquity
const double deltaEps = nut_in_obl(jdd);

// mean obliquity
const double eps = obliquity(jdd);

// true obliquity
const double epsPrime = eps + deltaEps;

// eq. 5.20 from Circular 179:

double S1 = sin(eps), S2 = sin(-deltaPsi), S3 = sin(-epsPrime);
double C1 = cos(eps), C2 = cos(-deltaPsi), C3 = cos(-epsPrime);

// eq. 5.21 from Circular 179:

N[0][0] = C2;
N[0][1] = S2*C1;
N[0][2] = S2*S1;
N[1][0] = -S2*C3;
N[1][1] = C3*C2*C1 - S1*S3;
N[1][2] = C3*C2*S1 + C1*S3;
N[2][0] = S2*S3;
N[2][1] = -S3*C2*C1 - S1*C3;
N[2][2] = -S3*C2*S1 + C3*C1;

for(i=0;i<3;++i) {
  x[i] = 0.;
  for (j=0;j<3;++j)
    x[i] += N[i][j] * r[j];
}

// eq. 5.2 from Circular 179:

ra = atan2(x[1], x[0]);
dec = atan2(x[2],sqrt(x[0]*x[0] + x[1]*x[1]));

}

void precess (double jdd, double &ra, double &dec) {

const double eps_0 = obliquity(J2000)/as_to_rad; //obliquity of the ecliptic at J2000.0

double psi_a, om_a, chi_a;
double r[3], x[3], P[3][3];
int i,j;

#define sinas(x) sin(as_to_rad * x)
#define cosas(x) cos(as_to_rad * x)

if( jdd == J2000 )
	return;

// eq. 5.1 from Circular 179:

r[0] = cos(ra) * cos(dec);
r[1] = sin(ra) * cos(dec);
r[2] = sin(dec);

double T = (jdd - J2000)/36525.0;

// eq. 5.8 from Circular 179:

psi_a = (((( - 0.0000000951   * T
             + 0.000132851  ) * T
	     - 0.00114045   ) * T
	     - 1.0790069    ) * T
	     + 5038.481507  ) * T;

om_a =  (((( + 0.0000003337   * T
             - 0.000000467  ) * T
	     - 0.00772503   ) * T
	     + 0.0512623    ) * T
	     - 0.025754     ) * T + eps_0;

chi_a = (((( - 0.0000000560   * T
             + 0.000170663  ) * T
	     - 0.00121197   ) * T
	     - 2.3814292    ) * T
	     + 10.556403    ) * T;

// eq. 5.9 from Circular 179:

double S1 = sinas(eps_0), S2 = sinas(-psi_a), S3 = sinas(-om_a), S4 = sinas(chi_a);
double C1 = cosas(eps_0), C2 = cosas(-psi_a), C3 = cosas(-om_a), C4 = cosas(chi_a);

// eq. 5.10 from Circular 179:

P[0][0] = C4*C2 - S2*S4*C3;
P[0][1] = C4*S2*C1 + S4*C3*C2*C1 - S1*S4*S3;
P[0][2] = C4*S2*S1 + S4*C3*C2*S1 + C1*S4*S3;
P[1][0] = -S4*C2 - S2*C4*C3;
P[1][1] = -S4*S2*C1 + C4*C3*C2*C1 - S1*C4*S3;
P[1][2] = -S4*S2*S1 + C4*C3*C2*S1 + C1*C4*S3;
P[2][0] = S2*S3;
P[2][1] = -S3*C2*C1 - S1*C3;
P[2][2] = -S3*C2*S1 + C3*C1;

for(i=0;i<3;++i) {
  x[i] = 0.;
  for (j=0;j<3;++j)
    x[i] += P[i][j] * r[j];
}

// eq. 5.2 from Circular 179:

ra = atan2(x[1], x[0]);
dec = atan2(x[2],sqrt(x[0]*x[0] + x[1]*x[1]));

}

int iauEpv00_wrapper(double date, double* pob);

void proper_motion_parallax (double jdd, double &ra, double &dec, double dra, double ddec, double radvel, double parallax) {

/* based on function pmpx from the sofa library - http://www.iausofa.org */

double pob[3];

double r[3], pm[3];
int i;

// eq. 5.1 from Circular 179:

r[0] = cos(ra) * cos(dec);
r[1] = sin(ra) * cos(dec);
r[2] = sin(dec);

dra = atan2 ( dra * mas_to_rad , cos(dec) ); // convert from milli-arcsec * cos(doc) to radians per year
ddec = ddec * mas_to_rad; // convert from milli-arcsec to radians per year
parallax = parallax * mas_to_rad; // convert from milli-arcsec to radians

iauEpv00_wrapper(jdd, &pob[0]); //get barycentric Earth position

//std::cout << "POB vector: " << pob[0] << ", " << pob[1] << ", " << pob[2] << endl;

double T = (jdd - J2000)/365.25; /* in Julian years - not centuries! */

double w = parallax * radvel * 86400.0 * 365250.0 / 1.49597870e11; // parallax in radians * radvel in AU/year
double pdz = ddec * r[2];

pm[0] = -dra * r[1] - pdz * cos(ra) + w * r[0];
pm[1] = dra * r[0] - pdz * sin(ra) + w * r[1];
pm[2] = ddec * cos(dec) + w * r[2];

for(i=0;i<3;++i) {
  r[i] += T * pm[i] - parallax  * pob[i];
}
// note: at this stage r is no longer a unit vector - but this doesn't matter

// eq. 5.2 from Circular 179:

ra = atan2(r[1], r[0]);
dec = atan2(r[2],sqrt(r[0]*r[0] + r[1]*r[1]));

}


