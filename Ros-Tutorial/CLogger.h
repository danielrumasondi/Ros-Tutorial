#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <winbase.h>
#include <winternl.h>
#include <time.h>
#pragma warning(disable: 4996 4102)

#define Pattern_Speed "\xB5\x3F\x00\x00\xF0\x41\x00\x00\x70\x42\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
#define Mask_Speed "xx??xx??x?????????????"
#define Pattern_Fall "\x57\x8B\x01\xFF\x90\xD8\x00\x00\x00\x8B\x96\x90\x00\x00\x00\xF6\xC2\x02\x74\x14\xC7\x86\x88\x00\x00\x00\x00\x00\x00\x00\xC7\x86\x8C\x00\x00\x00\x00\x00\x00\x00\x8B\xCA\x8B\xC2\xC1\xE9\x03\x83\xE0\x01"
#define Mask_Fall "xxxxx????xx????xx?xxxx????????xx????????xxxxxx?xx?"
#define Pattern_FOG "\xF3\x0F\x11\x45\xE0\xF3\x0F\x10\x86\x44\x03\x00\x00\xF3\x0F\x11\x45\xE4\xF3\x0F\x10\x86\x5C\x03\x00\x00\xF3\x0F\x11\x45\xE8\xF3\x0F\x10\x86\x60\x03\x00\x00\xF3\x0F\x11\x45\xEC\x8B\x40\x50\x8B\x44\xC8\xF8\x8B\x48\x5C\x83\xF9\xFF"
#define Mask_FOG "xxxx?xxxx????xxxx?xxxx????xxxx?xxxx????xxxx?xx?xx??xx?xx?"

DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] ) 
{ 
	unsigned int i = NULL; 
	int iLen = strlen( pszMask ) - 1; 
	for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ ) 
	{ 
		if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' ) 
		{ 
			if( pszMask[i+1] == '\0' ) return( dwRet - iLen ); i++; 
		} 
		else i = NULL; 
	} return NULL; 
}

DWORD DwStartAddress, DwSize, DwSpeed, DwFall, DwFOG, ResultSpeed, ResultFall, ResultFOG, DwIsInGame, ResultIsInGame;

void SearchPatterns()
{
Sleep(50);
DwStartAddress = (DWORD)GetModuleHandle("ros.exe");
do {
DwStartAddress = (DWORD)GetModuleHandle("ros.exe");
Sleep(50);
	}while(!DwStartAddress);
DwSize = 0xF0000000;
		 DwSpeed	  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Speed,Mask_Speed);
		 DwFall	      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Fall,Mask_Fall);
		 DwFOG	      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_FOG,Mask_FOG);

		 ResultSpeed = DwSpeed + 0x6;
		 ResultFall  = DwFall + 0xF;
		 ResultFOG  = DwFOG;
}
