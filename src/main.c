#include <stdio.h>
#include "defs.h"

int main(void) {
    vec_t vctr = vadd(&v3(2, 3, 4), &v3(9, 2, 3));
    vprint(&vctr);
    return 0;
}
