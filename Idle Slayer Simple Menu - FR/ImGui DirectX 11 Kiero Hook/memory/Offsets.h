#pragma once
#include <cstdint>
#include <vector>
#include <libloaderapi.h>
// this menu have been make by jxst_kifoxxxxe

uintptr_t FindAddress(uintptr_t ptr, std::vector<unsigned int> offsets)
{

	uintptr_t address = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
	
		address = *(uintptr_t*)address;
		address += offsets[i];
	
	}
	return address;

}

uintptr_t moduleBase = (uintptr_t)GetModuleHandle("GameAssembly.dll");

uintptr_t CoinOffsets = *(double*)FindAddress(moduleBase + 0x01EA6E28, {0x78, 0xB8, 0x20, 0x20});
