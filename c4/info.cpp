#include <CPU_ISA.h>
#include "stdio.h"

int main(void)
{
	CPU_ISA isa;

	printf("%s\n", isa.hasMMX()   ? "MMX   Supported" : "MMX   NOT Supported");
	printf("%s\n", isa.hasSSE()   ? "SSE   Supported" : "SSE   NOT Supported");
	printf("%s\n", isa.hasSSE2()  ? "SSE2  Supported" : "SSE2  NOT Supported");
	printf("%s\n", isa.hasSSE3()  ? "SSE3  Supported" : "SSE3  NOT Supported");
	printf("%s\n", isa.hasSSE41() ? "SSE41 Supported" : "SSE41 NOT Supported");
	printf("%s\n", isa.hasSSE42() ? "SSE42 Supported" : "SSE42 NOT Supported");
	printf("%s\n", isa.hasAES()   ? "AES   Supported" : "AES   NOT Supported");
	printf("%s\n", isa.hasSHA()   ? "SHA   Supported" : "SHA   NOT Supported");
	printf("%s\n", isa.hasAVX()   ? "AVX   Supported" : "AVX   NOT Supported");
	printf("%s\n", isa.hasAVX2()  ? "AVX2  Supported" : "AVX2  NOT Supported");

	printf("\nPress enter to continue ...");
	getchar();

	return 0;
}
