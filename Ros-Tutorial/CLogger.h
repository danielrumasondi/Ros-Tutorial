#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <winbase.h>
#include <winternl.h>
#include <time.h>
#pragma warning(disable: 4996 4102)

#define Pattern_Speed "\xB5\x3F\x00\x00\xF0\x41\x00\x00\x70\x42\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xAB\xAA\x2A\xBE\x86\x88\x08\x3C"
#define Mask_Speed "xx??xx??x?????????????xxxx????"
#define Pattern_Fall "\x57\x8B\x01\xFF\x90\xD8\x00\x00\x00\x8B\x96\x90\x00\x00\x00\xF6\xC2\x02\x74\x14\xC7\x86\x88\x00\x00\x00\x00\x00\x00\x00\xC7\x86\x8C\x00\x00\x00\x00\x00\x00\x00\x8B\xCA\x8B\xC2\xC1\xE9\x03\x83\xE0\x01"
#define Mask_Fall "xxxxx????xx????xx?xxxx????????xx????????xxxxxx?xx?"
#define Pattern_FOG "\xF3\x0F\x11\x45\xE8\xF3\x0F\x10\x83\x60\x03\x00\x00\xF3\x0F\x11\x45\xEC\x8B\x41\x4C\x83\xF8\x10\x0F\x47\xC6\x50\x8D\x45\xE0\x50\xFF\x71\x40\xE8\xCA\xC3\x8C\x00\x83\xC4\x0C\xF3\x0F\x10\x83\x74\x03\x00\x00\xF3\x0F\x10\x8B\x78\x03\x00\x00\x8B\xB7\x80\x06\x00\x00\xF3\x0F\x11\x45\xEC\xF3\x0F\x11\x4D\xF0\x85\xF6"
#define Mask_FOG "xxxx?xxxx????xxxx?xx?xx?xxxxxx?xxx?x????xx?xxxx????xxxx????xx????xxxx?xxxx?xx"
#define Pattern_IsInGame "\x09\x6C\x6F\x61\x64\x5F\x6C\x61\x79\x65\x72\x5F\x63\x6F\x6E\x66\x69\x67\x28\x63\x6F\x6E\x66\x69\x67\x5F\x70\x61\x74\x68\x29\x0A"
#define Mask_IsInGame "xxx?xxxxx?x?xx?xxx?xxxxxx?xxx?xx"

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

		 //DwIsInGame   = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_IsInGame,Mask_IsInGame);
		 DwSpeed	  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Speed,Mask_Speed);
		 DwFall	      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Fall,Mask_Fall);
		 DwFOG	      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_FOG,Mask_FOG);

		 //ResultIsInGame = DwIsInGame - 0x1E;
		 ResultSpeed = DwSpeed + 0x6;
		 ResultFall  = DwFall + 0xF;
		 ResultFOG  = DwFOG;
}