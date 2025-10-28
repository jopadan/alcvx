#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

int main(int argc, char** argv)
{
     vec3_t src = { 1,2,3 };
    avec3_t dst = ALCVX(src,3);

    dst *= dst;
    printf("[%f %f %f %f] %2zu/%2zu\n", src[0], src[1], src[2], src[3], alignof(src), sizeof(src));
    printf("[%f %f %f %f] %2zu/%2zu\n", dst[0], dst[1], dst[2], dst[3], alignof(dst), sizeof(dst));

    exit(EXIT_SUCCESS);
}
