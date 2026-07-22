#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>
typedef int32_t i32;
typedef uint8_t u8;

typedef struct {
    i32 r,g,b,a;
} Color_t;

static const i32 LENGTH = 800;
static const i32 SQUARE_LEN = 100;
#endif //CONSTANTS_H
