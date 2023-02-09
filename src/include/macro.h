#ifndef MACRO_H
#define MACRO_H

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define ARRAY_SIZE(arr) (int)(sizeof(arr) / sizeof(arr[0]))

#endif