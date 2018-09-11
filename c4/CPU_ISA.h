#ifndef		_CPU_ISA
#define		_CPU_ISA

#ifdef 		_WIN32					//  Windows
#define 	cpuid    __cpuid
#else								//  Linux
void cpuid(int CPUInfo[4], int InfoType){
	__asm__ __volatile__(
		"cpuid":
	    "=a" (CPUInfo[0]),
		"=b" (CPUInfo[1]),
		"=c" (CPUInfo[2]),
		"=d" (CPUInfo[3]) :
		"a" (InfoType)
		);
}
#endif

class CPU_ISA {
public:
	// Constructor
	CPU_ISA () {
		int info[4];

		cpuid(info, 0x80000000);
		if (info[0] >= 0x00000001) {
			cpuid(info, 0x00000001);

			MMX   = (info[3] & ((int)1 << 23)) != 0;

			SSE   = (info[3] & ((int)1 << 25)) != 0;
			SSE2  = (info[3] & ((int)1 << 26)) != 0;
			SSE3  = (info[2] & ((int)1 << 0)) != 0;
			AES   = (info[2] & ((int)1 << 25)) != 0;
			SSE41 = (info[2] & ((int)1 << 19)) != 0;
			SSE42 = (info[2] & ((int)1 << 20)) != 0;

			AVX   = (info[2] & ((int)1 << 28)) != 0;
		}
		cpuid(info, 0x80000000);
		if (info[0] >= 0x00000007){
			cpuid(info, 0x00000007);
			AVX2   = (info[1] & ((int)1 <<  5)) != 0;
			SHA    = (info[1] & ((int)1 << 29)) != 0;
		}
	};

	// Access member functions
	bool const hasMMX   () {return MMX;   }
	bool const hasSSE   () {return SSE;   }
	bool const hasSSE2  () {return SSE2;  }
	bool const hasSSE3  () {return SSE3;  }
	bool const hasSSE41 () {return SSE41; }
	bool const hasSSE42 () {return SSE42; }
	bool const hasAES   () {return AES;   }
	bool const hasSHA   () {return SHA;   }
	bool const hasAVX   () {return AVX;   }
	bool const hasAVX2  () {return AVX2;  }

private:
	//--  64-bit SIMD
	bool MMX   ;

	//-- 128-bit SIMD
	bool SSE   ;
	bool SSE2  ;
	bool SSE3  ;
	bool SSE41 ;
	bool SSE42 ;
	bool AES   ;
	bool SHA   ;

	//-- 256-bit SIMD
	bool AVX   ;
	bool AVX2  ;
};

#endif
