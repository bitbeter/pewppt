#include "stdio.h"
#include "ipp.h"
#include "x86intrin.h"

#define VECTOR_SIZE 16000000

int main(void)
{
	Ipp64u start, end;
	Ipp64u time1, time2;

	float fSRes;
	float fVRes;

	float *v1, *v2;
	v1 = new float[VECTOR_SIZE];
	v2 = new float[VECTOR_SIZE];

	if (!v1 || !v2)
	{
		printf("Memory allocation error!!\n");
		return 1;
	}
	// Initialize vectors with random numbers
	for (long i = 0; i < VECTOR_SIZE; i++)
	{
		v1[i] = (float)rand();
		v2[i] = (float)rand();
	}

	printf("=== Inner product ==========================================================\n");
	start = ippGetCpuClocks();
	for (long i = 0; i < VECTOR_SIZE; i++)
		fSRes += (v1[i] * v2[i]);
	end = ippGetCpuClocks();
	time1 = end - start;
	printf("Serial Run time = %d \n", (Ipp32s)time1);

	// Inner product, Vector edition
	start = ippGetCpuClocks();
	__m128 sum = _mm_set1_ps(0.0f);
	for (long i = 0; i < VECTOR_SIZE; i += 4)
		sum = _mm_add_ps(sum, _mm_mul_ps(_mm_loadu_ps(&v1[i]), _mm_loadu_ps(&v2[i])));
	sum = _mm_hadd_ps(sum, sum);
	sum = _mm_hadd_ps(sum, sum);
	fVRes = _mm_cvtss_f32(sum);
	end = ippGetCpuClocks();
	time2 = end - start;
	printf("Parallel Run time = %d \n", (Ipp32s)time2);
	printf("Speedup = %f", (float)(time1) / (float)time2);

	return 0;
}
