#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

int main(int argc, char** argv)
{
     vec3_t id[3] = {{1,2,3},{4,5,6},{0,0,1}};
    avec3_t a = ALCVX(id[0],3);
    avec3_t b = ALCVX(id[1],3);
    avec3_t c = cross3(a,b);

    printf("[%f %f %f %f] %2zu/%2zu\n", id[0][0], id[0][1], id[0][2], id[0][3], alignof(id[0]), sizeof(id[0]));
    printf("[%f %f %f %f] %2zu/%2zu\n", id[1][0], id[1][1], id[1][2], id[1][3], alignof(id[1]), sizeof(id[1]));
    printf("[%f %f %f %f] %2zu/%2zu\n", a[0], a[1], a[2], a[3], alignof(a), sizeof(a));
    printf("[%f %f %f %f] %2zu/%2zu\n", b[0], b[1], b[2], b[3], alignof(b), sizeof(b));
    printf("[%f %f %f %f] %2zu/%2zu\n", c[0], c[1], c[2], c[3], alignof(c), sizeof(c));
    printf("%f\n", dot3(a,b));

    vec(u16,3) tmp = { 1,2,3 }; 
    printf("[%hu %hu %hu %hu] %2zu/%2zu\n", tmp[0], tmp[1], tmp[2], tmp[3], alignof(tmp), sizeof(tmp));
    vec(u16,2) dst = (vec(u16,2))perm(tmp,1,0);
    printf("[%hu %hu]\n", dst[0], dst[1]);
    exit(EXIT_SUCCESS);
}
