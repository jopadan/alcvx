# alcvx
Aligned C Vector Extension single-header math library

## Usage

```c
#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

/* unaligned 3 component vector */
typedef      float vec3_t[3];
/*   aligned 3 component vector using GCC/LLVM vector extensions if available */
typedef VEC(float,3) avec3_t;

int main(int argc, char** argv)
{
     vec3_t a = { 1,2,3 };
    avec3_t b = ALCVX(src,3);

    exit(EXIT_SUCCESS);
}
```
