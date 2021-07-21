#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include <stdbool.h>

typedef struct Block {
    int x;
    int y;
} Block;

typedef struct Shape {
    Block blocks[4];
    int rotation;
    int current_rotation;
} Shape;

