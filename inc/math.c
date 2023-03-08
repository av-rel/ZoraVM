#ifndef ZORA_MATH_C
#define ZORA_MATH_C

#define ZORA_M_PI 3.14159265359

#define ZORA_M_abs(n) (n < 0 ? -(n) : n)
#define ZORA_M_sqr(n) (n*n)
#define ZORA_M_mid(a, b) ((a + b) / 2)
#define ZORA_M_max(a, b) (a > b ? a : b)
#define ZORA_M_min(a, b) (a < b ? a : b)

long int ZORA_M_factorial(int num) {
    if (num < 0) return -1;
    if (num == 0 || num == 1) return 1;
    return (num * ZORA_M_factorial(num - 1));
}

double ZORA_M_pow(double x, int exp) {
    double res = 1;

    if (exp < 0) return (1 / ZORA_M_pow(x, ZORA_M_abs(exp)));

    int i;
    for (i = 0; i < exp; i++) res *= x;

    return res;
}

/* All the functions below are not accurate completely 
 * sqrt
 * sin
 * cos
 * tan (dangerous)
 * */

double ZORA_M_sqrt(double x) {
    double guess = x / 2.0,
           prev_guess,
           error = 0.000001;

    do {
        prev_guess = guess;
        guess = (guess + x / guess) / 2.0;
    } while (prev_guess - guess > error || guess - prev_guess > error);

    return guess;
}

double ZORA_M_sin(double theta) {
    /* theta => 0 < theta < 360 */
    if (theta < 0) do { theta += 360; } while (theta < 0);
    if (theta > 360) do { theta -= 360; } while(theta > 360);

    /*constants*/
    if (theta == 0 || theta == 360) return 0.f;
    else if (theta == 30) return (1.f/2.f);
    else if (theta == 45) return (ZORA_M_sqrt(1.f/2.f));
    else if (theta == 60) return (ZORA_M_sqrt(3)/2.f);
    else if (theta == 90) return 1.f;

    /*approx*/
    if (theta <= 30 ) return (theta * ZORA_M_PI / 180); /* ~ x => sin(x) = x*/
    else if (theta > 30 && theta <= 90) return (2 * ZORA_M_sin(theta/2) * ZORA_M_sqrt(1 - (ZORA_M_sin(theta/2)*ZORA_M_sin(theta/2)))); /*sin2x = 2.sin(x/2).cos(x/2)*/
    else if (theta > 90 && theta < 180) return (ZORA_M_sin(180 - theta)); /*sinx = sin(180-x)*/
    else if (theta >= 180 && theta <= 270) return -(ZORA_M_sin(theta - 180)); /*sinx = sin(180 - x) = -sin(x - 180)*/
    else if (theta > 270 && theta < 360) return -(ZORA_M_sin(360-theta)); /*sinx = -sin(-x) = sin(x - 360)*/

    /*UNREACHABLE*/
    return (theta * ZORA_M_PI / 180);
}

double ZORA_M_cos(double theta) {
    /*	cosx = (1 - (sinx)^2)^(1/2) => X */
    if (theta < 0) do { theta += 360; } while (theta < 0);
    if (theta > 360) do { theta -= 360; } while(theta > 360);
    
    /*constants*/
    if (theta == 0 || theta == 360) return 1.f;
    else if (theta == 30) return (ZORA_M_sqrt(3)/2.f);
    else if (theta == 45) return (ZORA_M_sqrt(1.f/2.f));
    else if (theta == 60) return (1.f/2.f);
    else if (theta == 90) return -0.f;
    else if (theta == 270) return 0.f;
    
    /*approx*/
    if (theta >= 0 && theta <= 90) return ZORA_M_sqrt(1 - ( ZORA_M_sin(theta) * ZORA_M_sin(theta)));
    else if (theta > 90 && theta <= 180) return ZORA_M_sin(90 + theta);
    else if (theta > 180 && theta < 270) return -ZORA_M_sin(270 - theta);
    else if (theta > 270 && theta < 360) return -ZORA_M_sin(270 + (360 - theta));

    /*UNREACHABLE*/
    return ( ZORA_M_sqrt(1 - ( ZORA_M_sin(theta) * ZORA_M_sin(theta)) ) );
}

/* tan = sinx/cosx */
double ZORA_M_tan(double theta) { return (ZORA_M_sin(theta)/ZORA_M_cos(theta)); }

#endif
