/* Colliding Planets, by Hamid Naderi Yeganeh */
/* original at https://x.com/naderi_yeganeh/status/1845760888512414061 */

#include <math.h>
#include <stdlib.h>

#ifndef _WIN32
#include "../bitmap.h"
#else
#include "..\\bitmap.h"
#endif

#ifndef M_PI
#define M_PI ((double)3.14159265358979323846)
#endif

#define E_POW_NEG_E_POW(exponent) exp(-exp((exponent)))

/* OK */
static double Z(int s, double x, double y) {
  double pow_pow = pow(11, s) * pow(10, -s);
  double pow_cos = pow_pow * (1 + cos(10 * s));
  double cos2ss  = cos(2 * s * s);
  double sin2ss  = sin(2 * s * s);

  return
      0.1 * pow(25, s) * pow(26, -s) * 3 /* OK */
    * cos(
        pow_cos
        * (cos2ss * x + sin2ss * y + 2 * cos(17 * s))
        + 3 * cos(
                  pow_pow
                  * (cos(7 * s * s) * x + sin(7 * s * s) * y)
              )
        + 2 * cos(5 * s)
      )
    * cos(
        pow_cos
        * (cos2ss * y - sin2ss * x + 2 * cos(15 * s))
        + 3 * cos(
                  pow_pow
                  * (cos(8 * s * s) * x + sin(8 * s * s) * y)
              )
        + 2 * cos(7 * s)
      )
  ;
}

/* OK */
static double N(double x, double y) {
  double xy2  = x + y / 4 + 0.2;
  double yx54 = y - x / 4 - 0.54;

  return (xy2 * xy2) + (yx54 * yx54);
}

/* OK */
static double M(double x, double y) {
  double xy35 = x + y / 4 - 0.35;
  double yx35 = y - x / 4 + 0.35;
  
  return (xy35 * xy35) + (yx35 * yx35);
}

/* OK */
static double L(int t, double x, double y) {
  double xyt = 100 * y - 100 * x + 65 - 142 * t;

  return sqrt(fabs(7600 - 4000 * t - (xyt * xyt))) / 100;
}

/* OK */
static double T(double x, double y) {
  double yx35 = 100 * y - 25 * x + 35;
  return
    exp(
      2 - (5 * (100 * x + 25 * y - 35))
        / (1 + sqrt(fabs(4000 - (yx35 * yx35))))
    )
  ;
}

/* OK */
static double E(double x, double y) {
  double sum = 0.0;

  for (int s = 1; s <= 50; s++)
    sum += Z(s, x, y);

  return sum;
}

/* OK */
static double B(double x, double y) {
  return
    E_POW_NEG_E_POW(
        70 * N(x, y) - 14 + (7 * E(x, y)) / 20
    )
  ;  
}

/* OK */
static double A(double x, double y) {
  return
    E_POW_NEG_E_POW(
        70 * M(x, y) - 28 + (7 * E(x, y)) / 20
    )
  ;
}

/* OK */
static double Q(double x, double y) {
  double inverse_root_2 = pow(2, -0.5);
  double axy = A(x, y), bxy = B(x, y);

  return
    (
      axy
    * asin(
        inverse_root_2 * axy * sqrt(fabs(2 - 5 * M(x, y)))
      )
    )
  + (
      bxy
    * asin(
        inverse_root_2 * bxy * sqrt(fabs(2 - 5 * N(x, y)))
      )
    )
  ;
}

/* OK */ /* ind */
static double C(double x, double y) {
  return
    E_POW_NEG_E_POW(
        40 * pow(
                (y - x - 0.19 + 0.002 * pow((10 * x + 10 * y - 1), 2))
            , 2)
      - 0.16 + 0.8 * E(x, y) + 40 * pow(((x + y) / 2 - 0.07), 4)
    )
  ;
}

/* OK */ /* a, b*/
static double P(double x, double y) {
  double xy = 1000 * x + 250 * y;
  double yx = 1000 * y - 250 * x;

  return
  1.5 * (
          (
            A(x, y) * sqrt(M(x, y)) * atan((yx + 350) / (1 + fabs(xy - 350)))
          )
        + (
            B(x, y) * sqrt(N(x, y)) * atan((yx - 540) / (1 + fabs(xy + 200)))
          )
        )
  ;
}

/* OK */ /* ind */
static double R(int s, double x, double y) {
  return
    acos(
      cos(
        (30 + 10 * cos(17 * s)) * x - 15 * y + 4 * cos(12 * s)
      )
    )
  + 0.4 * acos(
            cos(70 * x + 85 * y + 4 * cos(34 * s))
          )
  + acos(cos(140 * x + 100 * y + 4 * cos(36 * s))) / 10
  + acos(cos(270 * x - 200 * y + 4 * cos(32 * s))) / 20
  ;
}

/* OK */
static double U(int v, double u, double w, double t, double x, double y) {
  double prod = 1.0, ltxy = L(t, x, y), exy = E(x, y), signal = pow(-1, t);

  for (int s = 1; s <= 5; s++)
    prod *=
      E_POW_NEG_E_POW(
          v
        * (
            cos(
              (16 + 2 * cos(2 * s)) 
              * (100 * (x + y + u))
              / (1 + 100 * ltxy)
            + (1 + t)
              * (fabs(x + y + u) - ltxy)
              * (
                  acos(
                    cos(
                      (10 + 4 * cos(15 * s)) * x
                     + 5 * y + 4 * cos(19 * s)
                    )
                  )
                + R(s, x, y)
                )
            + 4 * cos(27 * s)
            )
          - 3.01 
          + exy / 25 + 0.3 * pow(y - x + w, 3) * signal
          - 4 / M_PI
            * atan(
                -400 * signal
                * (
                    y - x + w + (v - 5) / 475 * signal
                  + cos(8 * s) / 5
                  + cos(7 * (x + y + u) + 3 * cos(14 * s)) / 5
                  )
              )
          )
      )
    ;
  
  return prod;
}

/* OK */
static double K(int v, double x, double y) {
  double sum = 0.0;
  double axy = A(x, y) / 20;
  double bxy = B(x, y) / 20;
  double pxy = P(x, y);
  double qxy = Q(x, y);
  double exy = (E(x, y) - 7) / 10;

  for (int s = 1; s <= 50; s++)
    sum +=
      3
    * (
        (axy) * ((5 - v) / 5 + 0.15 * cos((5 + v) * s))
      + (bxy) * ((14 + 3 * v - v * v
                + 3 * cos((4 + 2 * v) * s)
                 )
                 / 20
                )
      )
    * E_POW_NEG_E_POW(
          -20 * (
                  pow(
                    cos(
                      ((5 + 4 * s) / 5)
                    * (cos(4 * s) * qxy + sin(4 * s) * pxy)
                    + 10 * sin(10 * s)
                    )
                    , 2
                  )
                * pow(
                    cos(
                      ((5 + 4 * s) / 5)
                    * (sin(4 * s) * qxy - cos(4 * s) * pxy)
                    + 10 * sin(9 * s)
                    )
                    , 2
                  )
                + exy
                )
      )
    ;
  
  return sum;
}

/* OK */
static double D(double x, double y) {
  return
    exp(
      2.5 - (5 * (100 * x + 25 * y + 20))
            / (1 + sqrt(fabs(2000 - pow((100 * y - 25 * x - 54), 2))))
    )
  ;
}

/* OK */
double H(int v, double x, double y) {
  double axy   = A(x, y);
  double bxy   = B(x, y);
  double kvxy  = K(v, x, y);
  double kvxy3 = ((10 - 3 * v) / 100) * (1.25 + kvxy / 3);
  double v2v16 = (3 * v * v - 11 * v + 16);
  double yx18  = 500 * (y - x - 0.18);

  return
    (v2v16 / 4)
    * (
        (
          1.2
        - U(100, -0.15, -0.7, 1, x, y)
        - 0.2 * U(5, -0.15, -0.7, 1, x, y)
        )
        * bxy
      + (
          1.2
        - U(100, -0.17, 0.4, 0, x, y)
        - 0.2 * U(5, -0.17, 0.4, 0, x, y)
        )
        * axy
      )
  + (v2v16 / 2) * C(x, y)
  + axy * E_POW_NEG_E_POW(yx18)
    * ((kvxy3) + kvxy * exp(-T(x, y)))
  + bxy
    * E_POW_NEG_E_POW(-yx18)
    * (
        (kvxy3)
      + kvxy * exp(-D(x, y) - exp(-20 * (y - x / 4 - 0.3)))
      )
  ;
}


hex_value F(double x) {
    return
        floor(
            255 * E_POW_NEG_E_POW(-1000 * x)
          * pow(fabs(x),
                E_POW_NEG_E_POW(1000 * (x - 1))
          )
        )
    ;
}

/* 
 * .....................::comments::.....................
 * > i don't think this is the most
 * > computationally efficient way to generate the image
 * > what sort of black magic is this, anyway?
 * > the dude who made this is insane
 * > (genius, but insane)
 * > this thing is incredibly hard to make readable
 * > the way i've rewritten the formulas is horrible
 * > but i think the original is much worse
 * >
 * > i tried to put some repeats in variables
 * > to see if it helps when generating the image
 * > the thing is even uglier than before
 * > i really don't like it
 * ......................................................
*/
/*#include <stdio.h>
int main() {
  for (int n = 0; n < 1200; n++) {
		for (int m = 0; m < 2100; m++) {
			double x = ((double)m + 1 - 970) / 652;
			double y = (601 - (1200 - (double)n)) / 652;
      printf("m=%d, n=%d: x=%f, y=%f\n",m, n, x, y);
    }
  }
}*/
