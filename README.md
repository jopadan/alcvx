# alcvx
Aligned C Vector Extension single-header math library

## Usage

```c
#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

int main(int argc, char** argv)
{
     vec3_t src = { 1,2,3 };
    avec3_t dst = ALCVX(src,3);

    dst *= ALCVX(src,3);
    src = dst;
    exit(EXIT_SUCCESS);
}
```

```sh
[1.000000 2.000000 3.000000 0.000000]  4/12
[1.000000 4.000000 9.000000 0.000000] 16/16
[1 2 3 0]  8/ 8
```
