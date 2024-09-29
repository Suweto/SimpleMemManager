#pragma once
#include <Windows.h>
class Mem
{
private:
	bool patchUsed = false;
	bool nopUsed = false;
	unsigned int patchSize;
	unsigned int nopSize;
	BYTE* patchDst;
	BYTE* nopDst;
	BYTE* originalPatchBytes;
	BYTE* originalNopBytes;
public:
	bool Patch(BYTE* dst, BYTE* src, unsigned int size);
	bool UnPatch();
	bool Nop(BYTE* dst, unsigned int size);
	bool UnNop();
	bool Copy(BYTE* dst, BYTE* &buffer, unsigned int size);
};

