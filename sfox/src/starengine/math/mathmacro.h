#ifndef MATHMACRO_H
#define MATHMACRO_H

#include <math.h>

#define EPSILON 0.00001
#define NOTZERO(x) ((x)>EPSILON||(x)<-EPSILON)
#define RAD2DEG(x) (x*180)/M_PI
#define DEG2RAD(x) (x*M_PI)/180

#endif
