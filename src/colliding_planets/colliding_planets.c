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

static double Z(int s, double x, double y) {
    return
        0.1 * pow(25, s) * pow(26, -s) * 3
      * cos(
          pow(11, s) * pow(10, -s)
          * (1 + cos(10 * s))
          * (cos(2 * s * s) * x + sin(2 * s * s) * y + 2 * cos(17 * s))
          + 3 * cos(
                    pow(11, s) * pow(10, -s)
                    * (cos(7 * s * s) * x + sin(7 * s * s) * y)
                )
          + 2 * cos(5 * s)
        )
      * cos(
          pow(11, s) * pow(10, -s)
          * (1 + cos(10 * s))
          * (cos(2 * s * s) * y - sin(2 * s * s) * x + 2 * cos(15 * s))
          + 3 * cos(
                    pow(11, s) * pow(10, -s)
                    * (cos(8 * s * s) * x + sin(8 * s * s) * y)
                )
          + 2 * cos(7 * s)
      )
    ;
}

static double N(double x, double y) {
    return
        (x + y / 4 + 0.2) * (x + y / 4 + 0.2)
      + (y - x / 4 - 27 / 50) * (y - x / 4 - 27 / 50)
    ;
}

static double M(double x, double y) {
    return
        (x + y / 4 - 7 / 20) * (x + y / 4 - 7 / 20)
      + (y - x / 4 + 7 / 20) * (y - x / 4 + 7 / 20)
    ;
}

static double L(int t, double x, double y) {
  return
    sqrt(fabs(
          7600 - 4000 * t
        - ((100 * y - 100 * x + 65 - 1442 * t)
        * (100 * y - 100 * x + 65 - 1442 * t))
        )
    )
    / 100
  ;
}

static double T(double x, double y) {
  return
    exp(
      2 - (5 * (100 * x + 25 * y - 35))
        / (1 + sqrt(
                  fabs(
                    4000
                  - (100 * y - 25 * x + 35) * (100 * y - 25 * x + 35)
                  )
               )
          )
    )
  ;
}

static double E(double x, double y) {
  double sum = 0;

  for (int s = 1; s <= 50; s++)
    sum += Z(s, x, y);

  return sum;
}

static double B(double x, double y) {
  return
    exp(
      -exp(
        70 * N(x, y) - 14 + (7 * E(x, y)) / 20
      )
    )
  ;  
}

static double A(double x, double y) {
  return
    exp(
      -exp(
        70 * M(x, y) - 28 + (7 * E(x, y)) / 20
      )
    )
  ;
}

static double Q(double x, double y) {
  return
    (
      A(x, y)
    * asin(
        pow(2, -0.5) * A(x, y) * sqrt(fabs(2 - 5 * M(x, y)))
      )
    )
  + (
      B(x, y)
    * asin(
        pow(2, -0.5) * B(x, y) * sqrt(fabs(2 - 5 * N(x, y)))
      )
    )
  ;
}

static double C(double x, double y) {
  return
    exp(
      -exp(
        40 * pow(
                (y - x - 0.19 + 0.002 * pow((10 * x + 10 * y - 1), 2))
            , 2)
      - 0.16 + 0.8 * E(x, y) + 40 * pow(((x + y) / 2 - 0.07), 4)
      )
    )
  ;
}

static double P(double x, double y) {
  return
  1.5 * (
          (
            A(x, y) * sqrt(M(x, y)) * atan(
                                        (1000 * y - 250 * x + 350)
                                      / fabs(1000 * x + 250 * y - 350)
                                      )
          )
        + (
            B(x, y) * sqrt(N(x, y)) * atan(
                                        (1000 * y - 250 * x - 540)
                                      / (1 + fabs(1000 * x + 250 * y + 200))
                                      )
          )
        )
  ;
}

static double R(int s, double x, double y) {
  return
    acos(
      cos(
        (30 + 10 * cos(17 * s)) * x - 15 * y + 4 * cos(12 * s)
      )
    )
  * 0.4 * acos(
            cos(70 * x + 85 * y + 4 * cos(34 * s))
          )
  + acos(cos(140 * x + 100 * y + 4 * cos(36 * s))) / 10
  + acos(cos(270 * x - 200 * y + 4 * cos(32 * s))) / 20
  ;
}

static double U(int v, double u, double w, double t, double x, double y) {
  double prod = 1;

  for (int s = 1; s <= 5; s++)
    prod *=
      exp(
        -exp(
          v
        * (
            cos(
              (16 + 2 * cos(2 * s)) 
              * (100 * (x + y + u))
              / (1 + 100 * L(t, x, y))
            + (1 + t)
              * (fabs(x + y + u) - L(t, x, y))
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
          + E(x, y) / 25 + 0.3 * pow(y - x + w, 3) * pow(-1, t)
          - 4 / M_PI
            * atan(
                -400 * pow(-1, t)
                * (
                    y - x + w + (v - 5) / 475 * pow(-1, t)
                  + cos(8 * s) / 5
                  + cos(7 * (x + y + u) + 3 * cos(14 * s)) / 5
                  )
              )
          )
        )
      )
    ;
  
  return prod;
}

static double K(int v, double x, double y) {
  double sum = 0;

  for (int s = 1; s <= 50; s++)
    sum +=
      3
    * (
        (A(x, y) / 20) * ((5 - v) / 5 + 0.15 * cos((5 + v) * s))
      + (B(x, y) / 20) * (
                           (
                              14 + 3 * v - v * v
                            + 3 * cos((4 + 2 * v) * s)
                           )
                          / 20
                         )
      )
    * exp(
        -exp(
          -20 * (
                  pow(
                    cos(
                      ((5 + 4 * s) / 5)
                    * (cos(4 * s) * Q(x, y) + sin(4 * s) * P(x, y))
                    + 10 * sin(10 * s)
                    )
                    , 2
                  )
                * pow(
                    cos(
                      ((5 + 4 * s) / 5)
                    * (sin(4 * s) * Q(x, y) - cos(4 * s) * P(x, y))
                    + 10 * sin(9 * s)
                    )
                    , 2
                  )
                + (E(x, y) - 7) / 10
                )
        )
      )
    ;
  
  return sum;
}

static double D(double x, double y) {
  return
    exp(
      2.5 - (5 * (100 * x + 25 * y + 20))
            / (1 + sqrt(fabs(2000 - pow((100 * y - 25 * x - 54), 2))))
    )
  ;
}

double H(int v, double x, double y) {
  return
    ((3 * v * v - 11 * v + 16) / 4)
    * (
        (
          1.2
        - U(100, -0.15, -0.7, 1, x, y)
        - 0.2 * U(5, -0.15, -0.7, 1, x, y)
        )
        * B(x, y)
      + (
          1.2
        - U(100, -0.17, 0.4, 0, x, y)
        - 0.2 * U(5, -0.17, 0.4, 0, x, y)
        )
        * A(x,y)
      )
  + ((3 * v * v - 11 * v + 16) / 2) * C(x, y)
  + A(x, y) * exp(-exp(500 * (y - x - 0.18)))
    * (
        ((10 - 3 * v) / 100)
        * (1.25 + K(v, x, y) / 3)
      + K(v, x, y) * exp(-T(x, y))
      )
  + B(x, y)
    * exp(-exp(-500 * (y - x - 0.18)))
    * (
        ((10 - 3 * v) / 100)
        * (1.25 + K(v, x, y) / 3)
      + K(v, x, y) * exp(-D(x, y) - exp(-20 * (y - x / 4 - 0.3)))
      )
  ;
}


hex_value F(double x) {
    return
        floor(
            255 * exp(-exp(-1000 * x))
          * pow(fabs(x),
                exp(-exp(1000 * (x - 1)))
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
 * ......................................................
*/
