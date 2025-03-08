#include "pch.h"
#include <iostream>
#include <Windows.h>
#include "Log.h"


int addLog(int typeUsed, int typeItem,int IdItemUsed,int count,int IdEvent, int iDMaps)
{
	int typeIngame = typeUsed;
	DWORD StoreEcx;
	__asm mov StoreEcx, ecx
	_ItemLog *logInsert;
	//memset(&logInsert,0,sizeof(logInsert) );
	switch (typeIngame)
	{
	case 1: //Su Dung Item Box
		__asm
		{
			mov ecx, 0x007763E0
			mov ecx,[ecx]
			mov eax,0x00540B60
			call eax
			lea ecx, logInsert
			mov [ecx], eax
			lea eax, logInsert
			mov eax,[eax]
			mov DWORD PTR [eax],0x0
			mov DWORD PTR[eax + 0x4], 0x0
			mov word ptr [eax + 0x8], _LOG_ITEM_USED_BOX
			xor ecx,ecx
			mov ecx, iDMaps
			mov word ptr [eax + 0xA],cx
			xor ecx,ecx
			mov edx, StoreEcx
			mov ecx,[edx+0x1054]
			mov[eax + 0xC], ecx
			mov ecx, StoreEcx
			mov eax,0x0041F690
			call eax
			push 0xD
			push eax
			lea eax, logInsert
			mov eax, [eax]
			lea eax,[eax+0x10]
			push eax
			mov eax, 0x006E3CC0
			call eax
			add esp, 0xC
			lea eax, logInsert
			mov eax, [eax]
			mov byte ptr [eax+0x1D],0x1
			mov ecx, count
			sub ecx,0x1
			mov byte ptr[eax + 0x2E], cl
			xor ecx, ecx
			mov ecx, typeItem
			mov[eax + 0x32], cl
			xor ecx, ecx
			mov ecx, IdItemUsed
			mov[eax + 0x34], cx
			lea edx, logInsert
			mov edx,[edx]
			push edx
			mov ecx, 0x007763E0
			mov ecx,[ecx]
			mov eax,0x00540BA4
			call eax
		}
		break;
	case 2: //Su Dung Vp EXP
		
		break;
	case 3://Tinh Luyen Quan Ao
		__asm
		{
			mov ecx, 0x007763E0
			mov ecx, [ecx]
			mov eax, 0x00540B60
			call eax
			lea ecx, logInsert
			mov[ecx], eax
			lea eax, logInsert
			mov eax, [eax]
			mov DWORD PTR[eax], 0x0
			mov DWORD PTR[eax + 0x4], 0x0
			mov word ptr[eax + 0x8], _LOG_INCHANT_CLOTH
			xor ecx, ecx
			mov ecx, iDMaps
			mov word ptr[eax + 0xA], cx
			xor ecx, ecx
			mov edx, StoreEcx
			mov ecx, [edx + 0x1054]
			mov[eax + 0xC], ecx
			mov ecx, StoreEcx
			mov eax, 0x0041F690
			call eax
			push 0xD
			push eax
			lea eax, logInsert
			mov eax, [eax]
			lea eax, [eax + 0x10]
			push eax
			mov eax, 0x006E3CC0
			call eax
			add esp, 0xC
			lea eax, logInsert
			mov eax, [eax]
			mov byte ptr[eax + 0x1D], 0x1
			mov ecx, count
			sub ecx, 0x1
			mov byte ptr[eax + 0x2E], cl
			xor ecx, ecx
			mov ecx, typeItem
			mov[eax + 0x32], cl
			xor ecx, ecx
			mov ecx, IdItemUsed
			mov[eax + 0x34], cx
			lea edx, logInsert
			mov edx, [edx]
			push edx
			mov ecx, 0x007763E0
			mov ecx, [ecx]
			mov eax, 0x00540BA4
			call eax
		}
		break;
	case 4://Dmg Boss
		__asm
		{
			mov ecx, 0x007763E0
			mov ecx, [ecx]
			mov eax, 0x00540B60
			call eax
			lea ecx, logInsert
			mov[ecx], eax
			lea eax, logInsert
			mov eax, [eax]
			mov DWORD PTR[eax], 0x0
			mov DWORD PTR[eax + 0x4], 0x0
			mov word ptr[eax + 0x8], _LOG_TOTALDMGBOSS
			xor ecx, ecx
			mov ecx, iDMaps
			mov word ptr[eax + 0xA], cx
			xor ecx, ecx
			mov edx, StoreEcx
			mov ecx, [edx + 0x1054]
			mov[eax + 0xC], ecx
			mov ecx, StoreEcx
			mov eax, 0x0041F690
			call eax
			push 0xD
			push eax
			lea eax, logInsert
			mov eax, [eax]
			lea eax, [eax + 0x10]
			push eax
			mov eax, 0x006E3CC0
			call eax
			add esp, 0xC
			lea eax, logInsert
			mov eax, [eax]
			mov byte ptr[eax + 0x1D], 0x1
			mov ecx, count
			sub ecx, 0x1
			mov byte ptr[eax + 0x2E], cl
			xor ecx, ecx
			mov ecx, typeItem
			mov[eax + 0x32], cl
			xor ecx, ecx
			mov ecx, IdItemUsed
			mov[eax + 0x34], cx
			lea edx, logInsert
			mov edx, [edx]
			push edx
			mov ecx, 0x007763E0
			mov ecx, [ecx]
			mov eax, 0x00540BA4
			call eax
		}
		break;
	case 5://Item From Event Boss
		break;
	case 6://Su Dung Sach
		break;
	case 7:// Dieu Che
		__asm
		{
			mov ecx, 0x007763E0
			mov ecx, [ecx]
			mov eax, 0x00540B60
			call eax
			lea ecx, logInsert
			mov[ecx], eax
			lea eax, logInsert
			mov eax, [eax]
			mov DWORD PTR[eax], 0x0
			mov DWORD PTR[eax + 0x4], 0x0
			mov word ptr[eax + 0x8], _LOG_ITEM_COMBINE
			xor ecx, ecx
			mov ecx, iDMaps
			mov word ptr[eax + 0xA], cx
			xor ecx, ecx
			mov edx, StoreEcx
			mov ecx, [edx + 0x1054]
			mov[eax + 0xC], ecx
			mov ecx, StoreEcx
			mov eax, 0x0041F690
			call eax
			push 0xD
			push eax
			lea eax, logInsert
			mov eax, [eax]
			lea eax, [eax + 0x10]
			push eax
			mov eax, 0x006E3CC0
			call eax
			add esp, 0xC
			lea eax, logInsert
			mov eax, [eax]
			mov byte ptr[eax + 0x1D], 0x1
			mov ecx, count
			sub ecx, 0x1
			mov byte ptr[eax + 0x2E], cl
			xor ecx, ecx
			mov ecx, typeItem
			mov[eax + 0x32], cl
			xor ecx, ecx
			mov ecx, IdItemUsed
			mov[eax + 0x34], cx
			lea edx, logInsert
			mov edx, [edx]
			push edx
			mov ecx, 0x007763E0
			mov ecx, [ecx]
			mov eax, 0x00540BA4
			call eax
		}
		break;
	case 8: // Doi Opt
		break;
		default:
		break;
	}
}