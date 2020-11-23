#ifndef GPU_KARP_RABIN_RABINKARPSEARCHGPU_CUH
#define GPU_KARP_RABIN_RABINKARPSEARCHGPU_CUH

__host__ void searchWrapper();
__host__ void initUnifiedMemory();
__host__ void freeUnifiedMemory();
__host__ void printMatches();

#endif //GPU_KARP_RABIN_RABINKARPSEARCHGPU_CUH
