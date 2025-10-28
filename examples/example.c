#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

int main(int argc, char** argv)
{
	float u[3] = {1,2,3};
	VEC(float,3) a = TO_VEC(u,3);
	a *= a;
	printf("[%f %f %f %f] %zu/%zu\n", u[0], u[1], u[2], a[3], alignof(u), sizeof(u));
	printf("[%f %f %f %f] %zu/%zu\n", a[0], a[1], a[2], a[3], alignof(a), sizeof(a));
	exit(EXIT_SUCCESS);
}
