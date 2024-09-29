#include "mem.h"

bool Mem::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	if (patchUsed || !dst || !src || size == 0)
		return false;

	DWORD oldProtection;

	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtection);
	originalPatchBytes = new BYTE[size];
	Copy(dst, originalPatchBytes, size);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProtection, &oldProtection);

	patchDst = dst;
	patchSize = size;
	patchUsed = true;
	return true;
}

bool Mem::UnPatch()
{
	if (!patchUsed)
		return false;

	DWORD oldProtection;

	VirtualProtect(patchDst, patchSize, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy(patchDst, originalPatchBytes, patchSize);
	VirtualProtect(patchDst, patchSize, oldProtection, &oldProtection);

	delete[] originalPatchBytes;
	patchUsed = false;
	return true;
}

bool Mem::Nop(BYTE* dst, unsigned int size)
{
	if (nopUsed || size == 0)
		return false;

	DWORD oldProtection;

	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtection);
	originalNopBytes = new BYTE[size];
	Copy(dst, originalNopBytes, size);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldProtection, &oldProtection);
	
	nopDst = dst;
	nopSize = size;
	nopUsed = true;
	return true;
}

bool Mem::UnNop()
{
	if (!nopUsed)
		return false;

	DWORD oldProtection;

	VirtualProtect(nopDst, nopSize, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy(nopDst, originalNopBytes, nopSize);
	VirtualProtect(nopDst, nopSize, oldProtection, &oldProtection);

	delete[] originalNopBytes;
	nopUsed = false;
	return true;
}

bool Mem::Copy(BYTE* dst, BYTE*& buffer, unsigned int size)
{
	DWORD oldProtection;

	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy(buffer, dst, size);
	VirtualProtect(dst, size, oldProtection, &oldProtection);

	return true;
}