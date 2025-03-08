// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"
#include <time.h>
#include <Windows.h>
#include <iostream>

typedef char(__thiscall* gms_ctrl_add_skill)(int a1, int a2);
typedef char(__thiscall* gms_ctrl_rem_skill)(int a1, int a2);
typedef char(__thiscall* get_name)(int a1, int a2);
gms_ctrl_add_skill gms_ctrl_add_skill1;
gms_ctrl_rem_skill gms_ctrl_rem_skill1;
get_name get_name1;
bool hook(void* tohook, void* ourfunc, int len)
{
    if (len < 5)
    {
        return false;
    }
    DWORD curProtection;
    VirtualProtect(tohook, len, PAGE_EXECUTE_READWRITE, &curProtection);
    memset(tohook, 0x90, len);
    DWORD relativeAddress = (DWORD)ourfunc - (DWORD)tohook - 5;
    *(BYTE*)tohook = 0xE9;
    *(DWORD*)((DWORD)tohook + 1) = relativeAddress;
    DWORD temp;
    VirtualProtect(tohook, len, curProtection, &temp);
    return true;
}
DWORD jmpBackAdd;
DWORD jmpBackAdd3;
DWORD jmpBackAdd4;
int ListItemCheck1[5] = { 837,838,839 ,840 ,841 };
int ListItemCheck2[3] = { 837,838,839 };
int ListPhycys[540] = { 1,0,19,50,130,50,24,100,/**/1,19,40,130,100,131,100,/**/2,19,10,23,100,50,1,/**/3,19,25,61,1,2,50,/**/4,19,15,1,50,9,100,
                    2,0,19,60,130,100,24,150,/**/1,19,50,130,150,131,150,/**/2,19,20,23,150,50,3,/**/3,19,35,61,2,2,75,/**/4,19,25,1,75,9,150,
                    3,0,19,70,130,150,24,200,/**/1,19,60,130,200,131,200,/**/2,19,30,23,200,50,5,/**/3,19,45,61,3,2,100,/**/4,19,35,1,100,9,200,
                    4,0,19,80,130,200,24,250,/**/1,19,70,130,250,131,250,/**/2,19,40,23,250,50,7,/**/3,19,55,61,4,2,125,/**/4,19,45,1,125,9,250,
                    5,0,19,90,130,250,24,300,/**/1,19,80,130,300,131,300,/**/2,19,50,23,300,50,9,/**/3,19,65,61,5,2,150,/**/4,19,55,1,150,9,300,
                    6,0,19,100,130,300,24,350,/**/1,19,90,130,350,131,350,/**/2,19,60,23,350,50,11,/**/3,19,75,61,6,2,175,/**/4,19,65,1,175,9,350,
                    7,0,19,110,130,350,24,400,/**/1,19,100,130,400,131,400,/**/2,19,70,23,400,50,13,/**/3,19,85,61,7,2,200,/**/4,19,75,1,200,9,400,
                    8,0,19,120,130,400,24,450,/**/1,19,110,130,450,131,450,/**/2,19,80,23,450,50,15,/**/3,19,95,61,8,2,225,/**/4,19,85,1,225,9,450,
                    9,0,19,130,130,450,24,500,/**/1,19,120,130,500,131,500,/**/2,19,90,23,500,50,17,/**/3,19,105,61,9,2,250,/**/4,19,95,1,250,9,500,
                    10,0,19,150,130,550,24,700,/**/1,19,140,130,700,131,700,/**/2,19,110,23,700,50,21,/**/3,19,125,61,10,2,350,/**/4,19,115,1,350,9,600,
                    11,0,19,250,130,1500,24,900,/**/1,19,250,130,1500,131,900,/**/2,19,200,23,900,50,25,/**/3,19,200,61,20,2,450,/**/4,19,150,1,450,9,1000,
                    12,0,19,300,130,1800,24,1100,/**/1,19,300,130,1800,131,1100,/**/2,19,250,23,1100,50,29,/**/3,19,250,61,25,2,550,/**/4,19,200,1,550,9,1100,
                    13,0,19,350,130,2200,24,1300,/**/1,19,350,130,2200,131,1300,/**/2,19,300,23,1300,50,33,/**/3,19,300,61,30,2,650,/**/4,19,250,1,650,9,1300,
                    14,0,19,400,130,2500,24,1500,/**/1,19,400,130,2500,131,1500,/**/2,19,350,23,1500,50,37,/**/3,19,350,61,35,2,750,/**/4,19,300,1,750,9,1500,
                    15,0,19,450,130,3000,24,1700,/**/1,19,450,130,3000,131,1700,/**/2,19,400,23,1700,50,41,/**/3,19,400,61,40,2,850,/**/4,19,350,1,850,9,2000,
};
int ListChicong[540] = { 1,0,128,50,131,50,24,100,/**/1,128,40,130,100,131,100,/**/2,128,10,23,100,52,1,/**/3,128,25,61,1,137,50,/**/4,128,15,136,50,10,100,
                    2,0,128,60,131,100,24,150,/**/1,128,50,130,150,131,150,/**/2,128,20,23,150,52,3,/**/3,128,35,61,2,137,75,/**/4,128,25,136,75,10,150,
                    3,0,128,70,131,150,24,200,/**/1,128,60,130,200,131,200,/**/2,128,30,23,200,52,5,/**/3,128,45,61,3,137,100,/**/4,128,35,136,100,10,200,
                    4,0,128,80,131,200,24,250,/**/1,128,70,130,250,131,250,/**/2,128,40,23,250,52,7,/**/3,128,55,61,4,137,125,/**/4,128,45,136,125,10,250,
                    5,0,128,90,131,250,24,300,/**/1,128,80,130,300,131,300,/**/2,128,50,23,300,52,9,/**/3,128,65,61,5,137,150,/**/4,128,55,136,150,10,300,
                    6,0,128,100,131,300,24,350,/**/1,128,90,130,350,131,350,/**/2,128,60,23,350,52,11,/**/3,128,75,61,6,137,175,/**/4,128,65,136,175,10,350,
                    7,0,128,110,131,350,24,400,/**/1,128,100,130,400,131,400,/**/2,128,70,23,400,52,13,/**/3,128,85,61,7,137,200,/**/4,128,75,136,200,10,400,
                    8,0,128,120,131,400,24,450,/**/1,128,110,130,450,131,450,/**/2,128,80,23,450,52,15,/**/3,128,95,61,8,137,225,/**/4,128,85,136,225,10,450,
                    9,0,128,130,131,450,24,500,/**/1,128,120,130,500,131,500,/**/2,128,90,23,500,52,17,/**/3,128,105,61,9,137,250,/**/4,128,95,136,250,10,500,
                    10,0,128,150,131,550,24,700,/**/1,128,140,130,700,131,700,/**/2,128,110,23,700,52,21,/**/3,128,125,61,10,137,350,/**/4,128,115,136,350,10,600,
                    11,0,128,250,131,1500,24,900,/**/1,128,250,130,2000,131,900,/**/2,128,200,23,900,52,25,/**/3,128,200,61,20,137,450,/**/4,128,135,136,450,10,1000,
                    12,0,128,300,131,1800,24,1100,/**/1,128,300,130,2500,131,1100,/**/2,128,250,23,1100,52,29,/**/3,128,250,61,25,137,550,/**/4,128,155,136,550,10,1100,
                    13,0,128,350,131,2200,24,1310,/**/1,128,350,130,3000,131,1310,/**/2,128,300,23,1310,52,33,/**/3,128,300,61,30,137,650,/**/4,128,175,136,650,10,1300,
                    14,0,128,400,131,2500,24,1500,/**/1,128,400,130,3500,131,1500,/**/2,128,350,23,1500,52,37,/**/3,128,350,61,35,137,750,/**/4,128,195,136,750,10,1500,
                    15,0,128,450,131,3000,24,1700,/**/1,128,450,130,4000,131,1700,/**/2,128,400,23,1700,52,41,/**/3,128,400,61,40,137,850,/**/4,128,215,136,850,10,2000,
};
int ListDa31[11] = { 3,758,759,760 ,761 ,762 ,763,764,765 ,766 ,767 };
int ListDa32[11] = { 11,768,769,770 ,771 ,772 ,773,774,775 ,776 ,777 };
int ListDa33[11] = { 12,778,779,780 ,781 ,782 ,783,784,785 ,786 ,787 };
int ListDa34[11] = { 13,788,789,790 ,791 ,792 ,793,794,795 ,796 ,797 };
int ListDa35[11] = { 14,798,799,801 ,802 ,803 ,804,838,839 ,806 ,807 };
int ListDa1[11] = { 15,808,809,810,811,812,813,814,815,816,817 };
int ListDa2[11] = { 16,818,819,820,821,822,823,824,825,826,827 };
int ListDa3[11] = { 47,828,829,830,831,832,833,834,835,836,837 };
int ListDa4[11] = { 48,838,839,840,841,842,843,844,845,846,847 };
int ListDa5[11] = { 49,848,849,850,851,852,853,854,855,856,857 };
int ListDa6[11] = { 50,858,859,860,861,862,863,864,865,866,867 };
int ListDa7[11] = { 51,868,869,870,871,872,873,874,875,876,877 };
int ListDa8[11] = { 52,878,879,880,881,882,883,884,885,886,887 };
int ListDa9[11] = { 53,888,889,890,891,892,893,894,895,896,897 };
int ListDa10[11] = { 54,898,899,900,901,902,903,904,905,906,907 };
int ListDa11[11] = { 55,908,909,910,911,912,913,914,915,916,917 };
int ListDa12[11] = { 56,918,919,920,921,922,923,924,925,926,927 };
int ListDa13[11] = { 61,928,929,930,931,932,933,934,935,936,937 };
int ListDa14[11] = { 63,938,939,940,941,942,943,944,945,946,947 };
int ListDa15[11] = { 93,948,949,950,951,952,953,954,955,956,957 };
int ListDa16[11] = { 95,958,959,960,961,962,963,964,965,966,967 };
int ListDa17[11] = { 96,968,969,970,971,972,973,974,975,976,977 };
int ListDa18[11] = { 134,978,979,980,981,982,983,984,985,986,987 };
int ListDa19[11] = { 138,988,989,990,991,992,993,994,995,996,997 };
int ListDa20[11] = { 23,998,999,1000,1001,1002,1003,1004,1005,1006,1007 };
int ListDa21[11] = { 23,1008,1009,1010,1011,1012,1013,1014,1015,1016,1017 };
int ListDa22[11] = { 144,1018,1019,1020,1021,1022,1023,1024,1025,1026,1027 };
int ListDa23[11] = { 145,1028,1029,1030,1031,1032,1033,1034,1035,1036,1037 };
int ListDa24[11] = { 145,1038,1039,1040,1041,1042,1043,1044,1045,1046,1047 };
int ListDa25[11] = { 145,1048,1049,1050,1051,1052,1053,1054,1055,1056,1057 };
int ListDa26[11] = { 145,1058,1059,1060,1061,1062,1063,1064,1065,1066,1067 };
int ListDa27[11] = { 145,1068,1069,1070,1071,1072,1073,1074,1075,1076,1077 };
int ListDa28[11] = { 145,1078,1079,1080,1081,1082,1083,1084,1085,1086,1087 };
int ListDa29[11] = { 145,1088,1089,1090,1091,1092,1093,1094,1095,1096,1097 };
int ListDa30[11] = { 145,1098,1099,1100,1101,1102,1103,1104,1105,1106,1107 };

DWORD StorePacket = 0x0;
DWORD _checkID;
DWORD _storeeax;
DWORD _storeecx;
void __declspec(naked)DeccoEffect()
{
    __asm mov _storeeax, eax
    __asm mov ecx, 0x00000000
    __asm mov cx, [eax + 0x55]
        __asm  mov _checkID, ecx
    __asm xor ecx, ecx
        __asm mov cx, [eax + 0x55]
        __asm cmp ecx,0x00
        __asm jz NotDecco1
        __asm push ecx
    __asm mov cl, 0x1
    __asm push ecx
    __asm mov ecx, 0x00776388
    __asm mov ecx, [ecx]
        __asm mov eax, 0x4D7FB0
    __asm call eax
    __asm and eax, 0xFFFF
    __asm push eax
    __asm mov ecx, 0x00776388
    __asm mov ecx, [ecx]
        __asm mov eax, 0x641930
    __asm call eax
    __asm test eax,eax
    __asm jz NotDecco1
    __asm xor ecx,ecx
    __asm mov cx,[eax+0x4]
    __asm mov eax, _storeeax
    __asm mov[eax + 0x59],cx
    __asm mov eax, _storeeax
    __asm jmp Default22
    __asm NotDecco1:
    __asm mov eax, _storeeax
    __asm mov[eax + 0x59], 0x0000
    __asm mov eax, _storeeax

    __asm Default22:
    __asm
    {
        mov StorePacket, eax
        xor ecx, ecx

        LoopLoad :
        mov eax, [esp + 0x18]
            mov _storeecx, ecx
            imul ecx, ecx, 0x60
            lea edx, [eax + ecx + 0x0000128C]
            mov bl, [edx + 0x18]
            cmp bl, 0x7
            jl Default
            sub bl, 0x5
            mov eax, StorePacket
            mov ecx, _storeecx
            mov[eax + 0x1E + ecx], bl
            Default :
        mov ecx, _storeecx
            add ecx, 0x1
            cmp ecx, 0x5
            jz JmpOut
            jmp LoopLoad
            JmpOut :
    }
    __asm mov eax, _storeeax
    __asm push eax
    __asm mov ecx, DWORD PTR SS : [0x007763AC]
        __asm   jmp[jmpBackAdd]
}
DWORD jmpBackAdd2;
DWORD ChecSlotTo;
DWORD ChecSlotFrom;
DWORD CheckWeapon;
void __declspec(naked)WeaponSkill()
{
    //Get toSlot
    /*__asm pushad
    __asm mov eax, [ebp - 0xE754]
        __asm movsx eax, byte ptr[eax + 0x8]
        __asm mov ChecSlotTo, eax
    if (ChecSlotTo == 10)
    {
        __asm pushad
        __asm mov ecx, [ebp - 0x00000DBC]
            __asm call get_name1
        __asm mov edi, eax
        __asm or ecx, 0xFFFFFFFF
        __asm xor eax, eax
        __asm repne scasb
        __asm not ecx
        __asm sub edi, ecx
        __asm mov eax, ecx
        __asm mov     esi, edi
        __asm lea edx, [esp + 0x17]
            __asm shr     ecx, 0x2
        __asm mov     edi, edx
        __asm rep movsd
        __asm mov     ecx, eax
        __asm and ecx, 0x3
            __asm rep movsb
        __asm mov WORD PTR SS : [esp + 0x14] , 0x12
        __asm mov[esp + 0x16], 0xA9
        __asm mov WORD PTR SS : [esp + 0x24] , 0x1A
        __asm lea eax, [esp + 0x14]
            __asm push eax
        __asm mov ecx, DWORD PTR SS : [0x007763AC]
            __asm call gms_ctrl_rem_skill1
        //
        __asm mov WORD PTR SS : [esp + 0x14] , 0x12
        __asm mov[esp + 0x16], 0xA9
        __asm mov WORD PTR SS : [esp + 0x24] , 0x1B
        __asm lea eax, [esp + 0x14]
            __asm push eax
        __asm mov ecx, DWORD PTR SS : [0x007763AC]
            __asm call gms_ctrl_rem_skill1
        //
        __asm mov WORD PTR SS : [esp + 0x14] , 0x12
        __asm mov[esp + 0x16], 0xA9
        __asm mov WORD PTR SS : [esp + 0x24] , 0x1F
        __asm lea eax, [esp + 0x14]
            __asm push eax
        __asm mov ecx, DWORD PTR SS : [0x007763AC]
            __asm call gms_ctrl_rem_skill1
        //
        __asm popad
        __asm movsx eax, word ptr[ebp - 0x0000E759]
            __asm mov CheckWeapon, eax
        if (CheckWeapon == 12086 || CheckWeapon == 12087 || CheckWeapon == 12088 || CheckWeapon == 12089 || CheckWeapon == 12090 || CheckWeapon == 12091 || CheckWeapon == 12092 || CheckWeapon == 12093 || CheckWeapon == 12094 || CheckWeapon == 12095)
        {
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1A
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
        }
        else if (CheckWeapon == 12096 || CheckWeapon == 12097 || CheckWeapon == 12098 || CheckWeapon == 12099 || CheckWeapon == 12100 || CheckWeapon == 12101 || CheckWeapon == 12102 || CheckWeapon == 12103 || CheckWeapon == 12104)
        {
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1B
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
        }
        else if (CheckWeapon == 12105)
        {
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1F
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
        }
    }
    else
    {
        __asm movsx eax, word ptr[ebp - 0x0000E759]
            __asm mov CheckWeapon, eax
        if (CheckWeapon == 12086 || CheckWeapon == 12087 || CheckWeapon == 12088 || CheckWeapon == 12089 || CheckWeapon == 12090 || CheckWeapon == 12091 || CheckWeapon == 12092 || CheckWeapon == 12093 || CheckWeapon == 12094 || CheckWeapon == 12095)
        {
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x12
            __asm mov[esp + 0x16], 0xA9
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1A
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_rem_skill1
            //
            __asm mov WORD PTR SS : [esp + 0x14] , 0x12
            __asm mov[esp + 0x16], 0xA9
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1B
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_rem_skill1
            //
            __asm mov WORD PTR SS : [esp + 0x14] , 0x12
            __asm mov[esp + 0x16], 0xA9
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1F
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_rem_skill1
        }
        //
    }

    //Get ID and Type Weapon

    __asm popad
    __asm   jmp[jmpBackAdd2]*/
__asm pushad
__asm mov eax, [ebp - 0xE754]
__asm movsx eax, byte ptr[eax + 0x8]
__asm cmp eax, 0xA
__asm jnz RemoveFromSlotB
/// <summary>
/// Remove old Skill
/// </summary>
__asm xor edi, edi
__asm mov ecx, [ebp - 0x00000DBC]
__asm mov di, [ecx + 0x128C + 0x3C0 + 0xA]
__asm cmp edi, 0x2F36
__asm jl AddSkillWeapon
__asm cmp edi, 0x2F3F
__asm jg RemoveSKillFromOldSlot1DS
__asm call RemoveSkill1001
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot1DS:
__asm cmp edi, 0x2F40
__asm jl AddSkillWeapon
__asm cmp edi, 0x2F48
__asm jg RemoveSKillFromOldSlot2sd
__asm call RemoveSkill1002
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot2sd:
__asm cmp edi, 0x2F49
__asm jnz RemoveSKillFromOldSlot3sd
__asm call RemoveSkill1013
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot3sd :
    __asm cmp edi, 0x3072
__asm jl AddSkillWeapon
__asm cmp edi, 0x307B
__asm jg RemoveSKillFromOldSlot4sd
__asm call RemoveSkill1003
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot4sd:
__asm cmp edi, 0x3106
__asm jl AddSkillWeapon
__asm cmp edi, 0x310E
__asm jg RemoveSKillFromOldSlot5sd
__asm call RemoveSkill1011
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot5sd:
__asm cmp edi, 0x310F
__asm jnz AddSkillWeapon
__asm call RemoveSKill1012
__asm AddSkillWeapon :
    __asm mov eax, [ebp - 0xE754]
    __asm xor ecx, ecx
    __asm mov cl, byte ptr[eax + 0x7]
    __asm mov eax, ecx
__asm mov ecx, [ebp - 0x00000DBC]
__asm imul eax, 0x60
__asm xor edi, edi
__asm mov di, [ecx + 0x128C + eax + 0xA]
__asm AddSkillForWeapon1:
__asm mov eax, edi
__asm cmp eax, 0x2F36
__asm jl OutCheck
__asm cmp eax, 0x2F3F
__asm jg CheckSkill2
__asm mov ecx, [ebp - 0x00000DBC]
__asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x18
__asm mov[esp + 0x16], 0xA8
__asm mov WORD PTR SS : [esp + 0x24] , 0x1A
__asm mov WORD PTR SS : [esp + 0x26] , 0x9
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_add_skill1
__asm jmp OutCheck

__asm CheckSkill2 :
    __asm cmp eax, 0x2F40
__asm jl CheckSkill3
__asm cmp eax, 0x2F48
__asm jg CheckSkill3
__asm mov ecx, [ebp - 0x00000DBC]
__asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x18
__asm mov[esp + 0x16], 0xA8
__asm mov WORD PTR SS : [esp + 0x24] , 0x1B
__asm mov WORD PTR SS : [esp + 0x26] , 0x9
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_add_skill1
__asm jmp OutCheck

__asm CheckSkill3 :
    __asm cmp eax, 0x2F49
__asm jz AddSkill1
__asm jmp CheckSkillNew1
__asm AddSkill1 :
    __asm mov ecx, [ebp - 0x00000DBC]
    __asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x18
__asm mov[esp + 0x16], 0xA8
__asm mov WORD PTR SS : [esp + 0x24] , 0x1F
__asm mov WORD PTR SS : [esp + 0x26] , 0x9
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_add_skill1
__asm jmp OutCheck

__asm CheckSkillNew1 :
    __asm cmp eax, 0x3072
__asm jl OutCheck
__asm cmp eax, 0x307B
__asm jg CheckSkillNew2
__asm mov ecx, [ebp - 0x00000DBC]
__asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x18
__asm mov[esp + 0x16], 0xA8
__asm mov WORD PTR SS : [esp + 0x24] , 0x22
__asm mov WORD PTR SS : [esp + 0x26] , 0x9
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_add_skill1
__asm jmp OutCheck
//
__asm CheckSkillNew2 :
    __asm cmp eax, 0x3106
__asm jl OutCheck
__asm cmp eax, 0x310E
__asm jg CheckSkillNew3
__asm mov ecx, [ebp - 0x00000DBC]
__asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x18
__asm mov[esp + 0x16], 0xA8
__asm mov WORD PTR SS : [esp + 0x24] , 0x23
__asm mov WORD PTR SS : [esp + 0x26] , 0x9
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_add_skill1
__asm jmp OutCheck
//
__asm CheckSkillNew3 :
    __asm cmp eax, 0x310F
__asm jnz OutCheck
__asm mov ecx, [ebp - 0x00000DBC]
__asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x18
__asm mov[esp + 0x16], 0xA8
__asm mov WORD PTR SS : [esp + 0x24] , 0x24
__asm mov WORD PTR SS : [esp + 0x26] , 0x9
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_add_skill1
__asm jmp OutCheck
//
__asm RemoveFromSlotB :
    __asm mov eax, [ebp - 0xE754]
    __asm movsx eax, byte ptr[eax + 0x7]
    __asm cmp eax, 0xA
__asm jnz OutCheck
__asm xor edi, edi
__asm mov ecx, [ebp - 0x00000DBC]
__asm mov di, [ecx + 0x128C + 0x3C0 + 0xA]
__asm cmp edi, 0x2F36
__asm jl AddSkillOldSlotB
__asm cmp edi, 0x2F3F
__asm jg RemoveSKillFromOldSlot1
__asm call RemoveSkill1001
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot1:
__asm cmp edi, 0x2F40
__asm jl AddSkillOldSlotB
__asm cmp edi, 0x2F48
__asm jg RemoveSKillFromOldSlot2
__asm call RemoveSkill1002
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot2:
__asm cmp edi, 0x2F49
__asm jnz RemoveSKillFromOldSlot3
__asm call RemoveSkill1013
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot3 :
    __asm cmp edi, 0x3072
__asm jl AddSkillOldSlotB
__asm cmp edi, 0x307B
__asm jg RemoveSKillFromOldSlot4
__asm call RemoveSkill1003
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot4:
__asm cmp edi, 0x3106
__asm jl AddSkillOldSlotB
__asm cmp edi, 0x310E
__asm jg RemoveSKillFromOldSlot5
__asm call RemoveSkill1011
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot5:
__asm cmp edi, 0x310F
__asm jnz AddSkillOldSlotB
__asm call RemoveSKill1012
__asm AddSkillOldSlotB :
    __asm mov eax, [ebp - 0xE754]
    __asm xor ecx, ecx
    __asm mov cl, byte ptr[eax + 0x8]
    __asm mov eax, ecx
__asm mov ecx, [ebp - 0x00000DBC]
__asm imul eax, 0x60
__asm xor edi, edi
__asm mov di, [ecx + 0x128C + eax + 0xA]
__asm jmp AddSkillForWeapon1



//Get ID and Type Weapon
__asm OutCheck:
__asm popad
__asm xor edx, edx
__asm mov edx, 0x1
__asm push 0x005E19C8
__asm ret

__asm RemoveSkill1001:
__asm mov ecx, [ebp - 0x00000DBC]
__asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x12
__asm mov[esp + 0x16], 0xA9
__asm mov WORD PTR SS : [esp + 0x24] , 0x1A
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_rem_skill1
__asm ret
///************
__asm RemoveSKill1002 :
    __asm mov ecx, [ebp - 0x00000DBC]
    __asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x12
__asm mov[esp + 0x16], 0xA9
__asm mov WORD PTR SS : [esp + 0x24] , 0x1B
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_rem_skill1
__asm ret
///************

__asm RemoveSkill1003 :
    __asm mov ecx, [ebp - 0x00000DBC]
    __asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x12
__asm mov[esp + 0x16], 0xA9
__asm mov WORD PTR SS : [esp + 0x24] , 0x22
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_rem_skill1
__asm ret
///************

__asm RemoveSkill1011 :
    __asm mov ecx, [ebp - 0x00000DBC]
    __asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x12
__asm mov[esp + 0x16], 0xA9
__asm mov WORD PTR SS : [esp + 0x24] , 0x23
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_rem_skill1
__asm ret
///************

__asm RemoveSKill1012 :
    __asm mov ecx, [ebp - 0x00000DBC]
    __asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x12
__asm mov[esp + 0x16], 0xA9
__asm mov WORD PTR SS : [esp + 0x24] , 0x24
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_rem_skill1
__asm ret
///************

__asm RemoveSkill1013 :
    __asm mov ecx, [ebp - 0x00000DBC]
    __asm call get_name1
__asm mov edi, eax
__asm or ecx, 0xFFFFFFFF
__asm xor eax, eax
__asm repne scasb
__asm not ecx
__asm sub edi, ecx
__asm mov eax, ecx
__asm mov     esi, edi
__asm lea edx, [esp + 0x17]
__asm shr     ecx, 0x2
__asm mov     edi, edx
__asm rep movsd
__asm mov     ecx, eax
__asm and ecx, 0x3
__asm rep movsb
__asm mov WORD PTR SS : [esp + 0x14] , 0x12
__asm mov[esp + 0x16], 0xA9
__asm mov WORD PTR SS : [esp + 0x24] , 0x1F
__asm lea eax, [esp + 0x14]
__asm push eax
__asm mov ecx, DWORD PTR SS : [0x007763AC]
__asm call gms_ctrl_rem_skill1
__asm ret
///************

}
DWORD checkInch;
DWORD ChecSlotToMove;
void __declspec(naked)WeaponSkill2()
{
    //Get toSlot
      __asm pushad
      __asm mov edi, [ebp - 0xE754]
          __asm xor eax,eax
        __asm mov al, [edi + 0x8]
        __asm cmp eax,0x94
        __asm jz AddPetToUser
        __asm cmp eax,0xB
        __asm jnz RemoveFromSlotBOrA
        __asm jmp ADdSkillNow
        __asm RemoveFromSlotBOrA:
        __asm cmp eax, 0xA
        __asm jnz RemoveFromSlotB
        /// <summary>
        /// Remove old Skill
        /// </summary>
        /// 
        __asm ADdSkillNow:
        __asm xor edi,edi
        __asm mov ecx, [ebp - 0x00000DBC]
        __asm mov eax, [ebp - 0xE754]
        __asm movsx eax, byte ptr[eax + 0x8]
        __asm imul eax,0x60
        __asm mov di,[ecx+0x128C+ eax +0xA]
        __asm cmp edi, 0x2F36
        __asm jl AddSkillWeapon
        __asm cmp edi, 0x2F3F
        __asm jg RemoveSKillFromOldSlot1DS
        __asm call RemoveSkill1001
        __asm jmp AddSkillWeapon
        __asm RemoveSKillFromOldSlot1DS:
        __asm cmp edi, 0x2F40
        __asm jl AddSkillWeapon
        __asm cmp edi, 0x2F48
        __asm jg RemoveSKillFromOldSlot2sd
        __asm call RemoveSkill1002
        __asm jmp AddSkillWeapon
        __asm RemoveSKillFromOldSlot2sd:
        __asm cmp edi, 0x2F49
        __asm jnz RemoveSKillFromOldSlot3sd
        __asm call RemoveSkill1013
        __asm jmp AddSkillWeapon
        __asm RemoveSKillFromOldSlot3sd :
        __asm cmp edi, 0x3072
        __asm jl AddSkillWeapon
        __asm cmp edi, 0x307B
        __asm jg RemoveSKillFromOldSlot4sd
        __asm call RemoveSkill1003
        __asm jmp AddSkillWeapon
        __asm RemoveSKillFromOldSlot4sd:
        __asm cmp edi, 0x3106
        __asm jl AddSkillWeapon
        __asm cmp edi, 0x310E
        __asm jg RemoveSKillFromOldSlot5sd
        __asm call RemoveSkill1011
        __asm jmp AddSkillWeapon
        __asm RemoveSKillFromOldSlot5sd:
        __asm cmp edi, 0x310F
        __asm jnz AddSkillWeapon
        __asm call RemoveSKill1012
        __asm AddSkillWeapon :
            __asm mov eax, [ebp - 0xE754]
            __asm xor ecx, ecx
            __asm mov cl, byte ptr [eax + 0x7]
            __asm mov eax, ecx
            __asm mov ecx, [ebp - 0x00000DBC]
            __asm imul eax, 0x60
            __asm xor edi, edi
            __asm mov di, [ecx + 0x128C + eax + 0xA]
            __asm AddSkillForWeapon1:
            __asm mov eax,edi
            __asm cmp eax,0x2F36
            __asm jl OutCheck
            __asm cmp eax, 0x2F3F
            __asm jg CheckSkill2
            __asm mov ecx, [ebp - 0x00000DBC]
            __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1A
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
            __asm jmp OutCheck

            __asm CheckSkill2:
            __asm cmp eax, 0x2F40
            __asm jl CheckSkill3
            __asm cmp eax, 0x2F48
            __asm jg CheckSkill3
            __asm mov ecx, [ebp - 0x00000DBC]
            __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1B
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
            __asm jmp OutCheck

            __asm CheckSkill3:
            __asm cmp eax,0x2F49
            __asm jz AddSkill1
            __asm jmp CheckSkillNew1
            __asm AddSkill1:
            __asm mov ecx, [ebp - 0x00000DBC]
            __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1F
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
            __asm jmp OutCheck

            __asm CheckSkillNew1 :
                __asm cmp eax, 0x3072
            __asm jl OutCheck
            __asm cmp eax, 0x307B
            __asm jg CheckSkillNew2
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x22
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
            __asm jmp OutCheck
            //
            __asm CheckSkillNew2 :
                __asm cmp eax, 0x3106
            __asm jl OutCheck
            __asm cmp eax, 0x310E
            __asm jg CheckSkillNew3
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x23
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
            __asm jmp OutCheck
            //
            __asm CheckSkillNew3 :
                __asm cmp eax, 0x310F
            __asm jnz OutCheck
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm call get_name1
            __asm mov edi, eax
            __asm or ecx, 0xFFFFFFFF
            __asm xor eax, eax
            __asm repne scasb
            __asm not ecx
            __asm sub edi, ecx
            __asm mov eax, ecx
            __asm mov     esi, edi
            __asm lea edx, [esp + 0x17]
                __asm shr     ecx, 0x2
            __asm mov     edi, edx
            __asm rep movsd
            __asm mov     ecx, eax
            __asm and ecx, 0x3
                __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x18
            __asm mov[esp + 0x16], 0xA8
            __asm mov WORD PTR SS : [esp + 0x24] , 0x24
            __asm mov WORD PTR SS : [esp + 0x26] , 0x9
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_add_skill1
            __asm jmp OutCheck
            //
            __asm RemoveFromSlotB:
                __asm mov eax, [ebp - 0xE754]
                __asm movsx eax, byte ptr[eax + 0x7]
                __asm cmp eax, 0xB
                __asm jnz CheckSlotAFromOld
                __asm jmp ADdSkillFromNowOld
                __asm CheckSlotAFromOld:
                __asm cmp eax, 0xA
                __asm jnz OutCheck
            __asm ADdSkillFromNowOld:
            __asm xor edi, edi
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm mov eax, [ebp - 0xE754]
                __asm movsx eax, byte ptr[eax + 0x7]
                __asm imul eax,0x60
            __asm mov di, [ecx + 0x128C + eax + 0xA]
            __asm cmp edi, 0x2F36
            __asm jl AddSkillOldSlotB
            __asm cmp edi, 0x2F3F
            __asm jg RemoveSKillFromOldSlot1
            __asm call RemoveSkill1001
            __asm jmp AddSkillOldSlotB
            __asm RemoveSKillFromOldSlot1:
            __asm cmp edi, 0x2F40
            __asm jl AddSkillOldSlotB
            __asm cmp edi, 0x2F48
            __asm jg RemoveSKillFromOldSlot2
            __asm call RemoveSkill1002
            __asm jmp AddSkillOldSlotB
            __asm RemoveSKillFromOldSlot2:
            __asm cmp edi, 0x2F49
            __asm jnz RemoveSKillFromOldSlot3
            __asm call RemoveSkill1013
            __asm jmp AddSkillOldSlotB
            __asm RemoveSKillFromOldSlot3 :
                __asm cmp edi, 0x3072
            __asm jl AddSkillOldSlotB
            __asm cmp edi, 0x307B
            __asm jg RemoveSKillFromOldSlot4
            __asm call RemoveSkill1003
            __asm jmp AddSkillOldSlotB
            __asm RemoveSKillFromOldSlot4:
            __asm cmp edi, 0x3106
            __asm jl AddSkillOldSlotB
            __asm cmp edi, 0x310E
            __asm jg RemoveSKillFromOldSlot5
            __asm call RemoveSkill1011
            __asm jmp AddSkillOldSlotB
            __asm RemoveSKillFromOldSlot5:
            __asm cmp edi, 0x310F
            __asm jnz AddSkillOldSlotB
            __asm call RemoveSKill1012
            __asm AddSkillOldSlotB:
                __asm mov eax, [ebp - 0xE754]
                __asm xor ecx, ecx
                __asm mov cl, byte ptr[eax + 0x8]
                __asm mov eax, ecx
            __asm mov ecx, [ebp - 0x00000DBC]
                __asm imul eax, 0x60
            __asm xor edi, edi
            __asm mov di, [ecx + 0x128C + eax + 0xA]
            __asm jmp AddSkillForWeapon1

        

    //Get ID and Type Weapon
    __asm OutCheck:
    __asm
    /* {
     mov eax, [ebp - 0xE754]
        movsx eax, byte ptr[eax + 0x8]
        cmp eax, 0x8C
        jl DefaultNOtNewSlot
        cmp eax,0x94
        jg DefaultNOtNewSlot
        imul eax,0x60
        mov ecx, [ebp - 0x00000DBC]
        xor edx,edx
        mov dl,[ecx+eax+0x128C+0x8]
        cmp edx,0x9
        jnz OutAddItemToNewSlot
        xor edx, edx
        xor ebx,ebx
        xor edi,edi
        mov dx, [ecx + eax + 0x128C + 0xA]
        lea ecx, [ecx + 0x128C + 0x3420 + 0xA]
        BackLoopAdd:
        add ebx,0x1
        xor eax, eax
        add ecx,0x60
        cmp ebx,0x8
        jz ContinueCheck
        mov ax,[ecx]
        cmp edx,eax
        jnz BackLoopAdd
        add edi,0x1
        jmp BackLoopAdd

        ContinueCheck:
        cmp edi,0x2
        jge OutAddItemToNewSlot
        jmp DefaultNOtNewSlot

        OutAddItemToNewSlot:
        popad
        push 0x005E1A8B
        ret

        DefaultNOtNewSlot:

    }*/
    __asm DefaultAfterAddPet:
    __asm popad
    __asm mov ecx, [ebp - 0x0000E754]
    __asm push 0x005E1869
    __asm ret
    /// <summary>
    /// Other Func
    /// </summary>
    __asm RemoveSkill1001:
    __asm mov ecx, [ebp - 0x00000DBC]
        __asm call get_name1
    __asm mov edi, eax
    __asm or ecx, 0xFFFFFFFF
    __asm xor eax, eax
    __asm repne scasb
    __asm not ecx
    __asm sub edi, ecx
    __asm mov eax, ecx
    __asm mov     esi, edi
    __asm lea edx, [esp + 0x17]
        __asm shr     ecx, 0x2
    __asm mov     edi, edx
    __asm rep movsd
    __asm mov     ecx, eax
    __asm and ecx, 0x3
        __asm rep movsb
        __asm mov WORD PTR SS : [esp + 0x14] , 0x12
        __asm mov[esp + 0x16], 0xA9
        __asm mov WORD PTR SS : [esp + 0x24] , 0x1A
        __asm lea eax, [esp + 0x14]
            __asm push eax
        __asm mov ecx, DWORD PTR SS : [0x007763AC]
            __asm call gms_ctrl_rem_skill1
        __asm ret
        ///************
    __asm RemoveSKill1002 :
    __asm mov ecx, [ebp - 0x00000DBC]
        __asm call get_name1
    __asm mov edi, eax
    __asm or ecx, 0xFFFFFFFF
    __asm xor eax, eax
    __asm repne scasb
    __asm not ecx
    __asm sub edi, ecx
    __asm mov eax, ecx
    __asm mov     esi, edi
    __asm lea edx, [esp + 0x17]
        __asm shr     ecx, 0x2
    __asm mov     edi, edx
    __asm rep movsd
    __asm mov     ecx, eax
    __asm and ecx, 0x3
        __asm rep movsb
        __asm mov WORD PTR SS : [esp + 0x14] , 0x12
        __asm mov[esp + 0x16], 0xA9
        __asm mov WORD PTR SS : [esp + 0x24] , 0x1B
        __asm lea eax, [esp + 0x14]
            __asm push eax
        __asm mov ecx, DWORD PTR SS : [0x007763AC]
            __asm call gms_ctrl_rem_skill1
        __asm ret
        ///************

     __asm RemoveSkill1003 :
     __asm mov ecx, [ebp - 0x00000DBC]
         __asm call get_name1
     __asm mov edi, eax
     __asm or ecx, 0xFFFFFFFF
     __asm xor eax, eax
     __asm repne scasb
     __asm not ecx
     __asm sub edi, ecx
     __asm mov eax, ecx
     __asm mov     esi, edi
     __asm lea edx, [esp + 0x17]
         __asm shr     ecx, 0x2
     __asm mov     edi, edx
     __asm rep movsd
     __asm mov     ecx, eax
     __asm and ecx, 0x3
         __asm rep movsb
         __asm mov WORD PTR SS : [esp + 0x14] , 0x12
         __asm mov[esp + 0x16], 0xA9
         __asm mov WORD PTR SS : [esp + 0x24] , 0x22
         __asm lea eax, [esp + 0x14]
             __asm push eax
         __asm mov ecx, DWORD PTR SS : [0x007763AC]
             __asm call gms_ctrl_rem_skill1
         __asm ret
         ///************

        __asm RemoveSkill1011 :
        __asm mov ecx, [ebp - 0x00000DBC]
            __asm call get_name1
        __asm mov edi, eax
        __asm or ecx, 0xFFFFFFFF
        __asm xor eax, eax
        __asm repne scasb
        __asm not ecx
        __asm sub edi, ecx
        __asm mov eax, ecx
        __asm mov     esi, edi
        __asm lea edx, [esp + 0x17]
            __asm shr     ecx, 0x2
        __asm mov     edi, edx
        __asm rep movsd
        __asm mov     ecx, eax
        __asm and ecx, 0x3
            __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x12
            __asm mov[esp + 0x16], 0xA9
            __asm mov WORD PTR SS : [esp + 0x24] , 0x23
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_rem_skill1
            __asm ret
            ///************

        __asm RemoveSKill1012 :
        __asm mov ecx, [ebp - 0x00000DBC]
            __asm call get_name1
        __asm mov edi, eax
        __asm or ecx, 0xFFFFFFFF
        __asm xor eax, eax
        __asm repne scasb
        __asm not ecx
        __asm sub edi, ecx
        __asm mov eax, ecx
        __asm mov     esi, edi
        __asm lea edx, [esp + 0x17]
            __asm shr     ecx, 0x2
        __asm mov     edi, edx
        __asm rep movsd
        __asm mov     ecx, eax
        __asm and ecx, 0x3
            __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x12
            __asm mov[esp + 0x16], 0xA9
            __asm mov WORD PTR SS : [esp + 0x24] , 0x24
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_rem_skill1
            __asm ret
            ///************

        __asm RemoveSkill1013 :
        __asm mov ecx, [ebp - 0x00000DBC]
            __asm call get_name1
        __asm mov edi, eax
        __asm or ecx, 0xFFFFFFFF
        __asm xor eax, eax
        __asm repne scasb
        __asm not ecx
        __asm sub edi, ecx
        __asm mov eax, ecx
        __asm mov     esi, edi
        __asm lea edx, [esp + 0x17]
            __asm shr     ecx, 0x2
        __asm mov     edi, edx
        __asm rep movsd
        __asm mov     ecx, eax
        __asm and ecx, 0x3
            __asm rep movsb
            __asm mov WORD PTR SS : [esp + 0x14] , 0x12
            __asm mov[esp + 0x16], 0xA9
            __asm mov WORD PTR SS : [esp + 0x24] , 0x1F
            __asm lea eax, [esp + 0x14]
                __asm push eax
            __asm mov ecx, DWORD PTR SS : [0x007763AC]
                __asm call gms_ctrl_rem_skill1
            __asm ret
            ///************


    //AddPet
    __asm
        {
    AddPetToUser:
            xor edx, edx
            mov  ecx, [ebp - 0x00000DBC]
            mov edx,[ecx+0x10A4]
            test edx,edx
            jz NotHaveModBefore
            mov ecx,edx
            mov eax, 0x00586F11
            call eax
            mov  ecx, [ebp - 0x00000DBC]
            mov dword ptr[ecx+0x10A4],0x00000000
                //RemoveSKillPet
                mov edx, [ebp - 0xE754]
                mov al, byte ptr[edx + 0x7]
                mov edx, eax
                mov ecx, [ebp - 0x00000DBC]
                imul edx, 0x60
                xor eax, eax
                mov ax, [ecx + 0x3780 + 0x128C + 0xA]
                cmp eax, 0x48E
                jl NotHaveModBefore
                cmp eax, 0x496
                jg NotHaveModBefore
                push 0x1
                mov ecx, [ebp - 0x00000DBC]
                mov eax, 0x004F563B
                call eax
                
            NotHaveModBefore:
            xor edx, edx
            mov edx, [ebp - 0xE754]
            xor eax,eax
            mov al, byte ptr[edx + 0x7]
            mov ecx, [ebp - 0x00000DBC]
            imul eax,0x60
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x9
            jnz DefaultLoadPet
            xor edx, edx
            xor eax, eax
            mov edx, [ebp - 0xE754]
            mov al, byte ptr[edx + 0x7]
            mov ecx, [ebp - 0x00000DBC]
            imul eax, 0x60
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            cmp edx, 0x48E
            jl DefaultLoadPet
            cmp edx, 0x496
            jg DefaultLoadPet
            //CreatePet
            mov  ecx, [ebp - 0x00000DBC]
            mov eax, 0x00431F70
            call eax
            push ecx
            fstp dword ptr[esp]
            pop ecx
            mov[ebp - 0xF164], ecx
            mov  ecx, [ebp - 0x00000DBC]
            mov eax, 0x00431F90
            call eax
            push ecx
            fstp dword ptr[esp]
            pop ecx
            mov[ebp - 0xF160], ecx
            //Check Mod
            mov  ecx,[ebp - 0x00000DBC]
            xor eax, eax
            xor edx, edx
            mov edx, [ebp - 0xE754]
            mov al, byte ptr[edx + 0x7]
            mov edx,eax
            mov ecx, [ebp - 0x00000DBC]
            imul edx, 0x60
            xor eax, eax
            mov ax, [ecx + edx + 0x128C + 0xA]
            cmp eax,0x48E
            jnz GetIdMod1
                mov ecx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CEB
            jmp callboss
            GetIdMod1:
            cmp eax, 0x48F
            jnz GetIdMod12
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CEC
                jmp callboss
                GetIdMod12 :
            cmp eax, 0x490
                jnz GetIdMod13
               
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CED
                jmp callboss
                GetIdMod13 :
            cmp eax, 0x491
                jnz GetIdMod14
                
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CEE
                jmp callboss

                GetIdMod14 :
            cmp eax, 0x492
                jnz GetIdMod15
                
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CEF
                jmp callboss

                GetIdMod15 :
            cmp eax, 0x493
                jnz GetIdMod16
                
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CF0
                jmp callboss

                GetIdMod16 :
            cmp eax, 0x494
                jnz GetIdMod17
                
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CF1
                jmp callboss

                GetIdMod17 :
            cmp eax, 0x495
                jnz GetIdMod18
                
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CF2
                jmp callboss

                GetIdMod18 :
            cmp eax, 0x496
                jnz callboss
                
                mov edx, 0x3E7// (ID Skill)
                call AddSkillForPet
                mov eax, 0x1CF3
                jmp callboss



            //
                callboss:
            push 0x0
            push 0x0
            push 0x0
            lea edx, [ebp - 0x0000F164]
            push edx
            push 0x0
            push eax
            mov eax, 0x00406B10
            call eax
            mov ecx, eax
            mov eax, 0x005BB34D
            call eax
            test eax, eax
            jz NotFoundID
            mov  ecx, [ebp - 0x00000DBC]
            mov[ecx + 0x10A4], eax
            mov cx, ax
            push ecx
            mov eax, 0x00406B10
            call eax
            mov ecx, eax
            mov eax, 0x0005BBB29
            call eax
            //
            NotFoundID :
            mov  ecx, [ebp - 0x00000DBC]
            xor eax, eax
            mov ax, [ecx + 0x10A4]
            push eax
            mov eax, 0x00406B10
            call eax
            xor edx, edx
            mov  edx, [ebp - 0x00000DBC]
            mov ecx, eax
            mov eax, 0x0040AD70
            call eax
            mov  ecx, [ebp - 0x00000DBC]
            mov[ecx + 0x10A4], eax

            mov  ecx, [ebp - 0x00000DBC]
            mov ecx, [ecx + 0x10A4]

            mov byte ptr[ecx + 0x30], 0xFF
            mov byte ptr[ecx + 0x17], 0x1
            mov edx, [ecx + 0x8]
            mov ebx, 0x41700000
            mov dword ptr[edx + 0x3C], ebx
            //
                DefaultLoadPet:
            jmp DefaultAfterAddPet

                AddSkillForPet:
                 push 0x3349
                 mov  ecx, [ebp - 0x00000DBC]
                 mov eax,0x0041F160
                 call eax
                 push 0x0
                 push 0x0
                 push 0x0
                 push edx
                 mov  ecx, [ebp - 0x00000DBC]
                 mov eax,0x004DB99D
                 call eax
                 push 0x334B
                 mov  ecx, [ebp - 0x00000DBC]
                 mov eax, 0x0041F180
                 call eax
                 ret



        }

}
void __declspec(naked)FixDmage1()
{
    __asm mov checkInch, ecx
    if (checkInch == 1 || checkInch == 2)
    {
        __asm mov ecx, 0x3
    }
    __asm fld dword ptr[edx + ecx * 4 + 0x53BC]
        __asm push 0x0052BDC7
    __asm ret

}
DWORD checkInch1;
DWORD checkInch1312;
void __declspec(naked)FixDmage2()
{
    __asm cmp ecx,0x1
    __asm jnz Check32
    __asm mov ecx, 0x3
    __asm jmp Default
    __asm Check32:
    __asm cmp ecx, 0x2
    __asm jnz Default
    __asm mov ecx, 0x3
    __asm Default:
    __asm fld dword ptr[edx + ecx * 4 + 0x53BC]
    __asm push 0x0052BD47
    __asm ret
}
DWORD checkInch2;
void __declspec(naked)FixDmage3()
{
    __asm cmp ecx, 0x1
    __asm jnz Check32
    __asm mov ecx, 0x3
    __asm jmp Default
    __asm Check32:
    __asm cmp ecx, 0x2
    __asm jnz Default
    __asm mov ecx, 0x3
    __asm Default :
    __asm mov eax, [edx + ecx * 4 + 0x5404]
        __asm push 0x0052BD87
    __asm ret
}
DWORD checkInch3;
void __declspec(naked)FixDmage4()
{
    __asm cmp ecx, 0x1
    __asm jnz Check32
    __asm mov ecx, 0x3
    __asm jmp Default
    __asm Check32:
    __asm cmp ecx, 0x2
    __asm jnz Default
    __asm mov ecx, 0x3
    __asm Default :
    __asm mov eax, [edx + ecx * 4 + 0x5404]
        __asm push 0x0052BD07
    __asm ret
}
DWORD checkInch4;
void __declspec(naked)FixDmage5()
{
    __asm cmp ecx, 0x1
    __asm jnz Check32
    __asm mov ecx, 0x3
    __asm jmp Default
    __asm Check32:
    __asm cmp ecx, 0x2
    __asm jnz Default
    __asm mov ecx, 0x3
    __asm Default :
    __asm mov al, [edx + ecx * 4 + 0x5404]
        __asm push 0x0052BE07
    __asm ret
}

void __declspec(naked)InChantCloth()
{
    __asm
    {
        mov cl, [ebp + 0x8]
        cmp cl, 0x1
        jz AcceptClth
        mov eax, 0x52B460
        push ecx
        call eax
        push 0x0063B07E
        ret
        AcceptClth :
        mov eax, 0x1
            push 0x0063B081
            ret

    }
}
void __declspec(naked)FixInchantBlood()
{
    __asm
    {
        pushad
        mov al, [ebp - 0x27]
        cmp al, 0x1
        jnz Check1
        mov byte ptr[ebp - 0x25], 0x0
        jmp Jumout
        Check1 :
        cmp al, 0x2
            jnz Check2
            mov byte ptr[ebp - 0x25], 0x0
            jmp Jumout
            Check2 :
        cmp al, 0x3
            jnz Check3
            mov byte ptr[ebp - 0x25], 0x0
            jmp Jumout
            Check3 :
        cmp al, 0x4
            jnz Check4
            mov byte ptr[ebp - 0x25], 0x0
            jmp Jumout
            Check4 :
        cmp al, 0x5
            jnz Check5
            mov byte ptr[ebp - 0x25], 0x0
            jmp Jumout
            Check5 :
        cmp al, 0x6
            jnz Check6
            mov byte ptr[ebp - 0x25], 0x0
            jmp Jumout
            Check6 :
        cmp al, 0x7
            jnz Check7
            mov byte ptr[ebp - 0x25], 0x0
            jmp Jumout
            Check7 :
        cmp al, 0x8
            jnz Check8
            mov byte ptr[ebp - 0x25], 0x0
            jmp Jumout
            Check8 :
        cmp al, 0x9
            jnz Check9
            mov byte ptr[ebp - 0x25], 0x6
            jmp Jumout
            Check9 :
        cmp al, 0xA
            jnz Check10
            mov byte ptr[ebp - 0x25], 0x8
            jmp Jumout
            Check10 :
        cmp al, 0xB
            jnz Check11
            mov byte ptr[ebp - 0x25], 0xA
            jmp Jumout
            Check11 :
        cmp al, 0xC
            jnz Check12
            mov byte ptr[ebp - 0x25], 0xF
            jmp Jumout
            Check12 :
        cmp al, 0xD
            jnz Check13
            mov byte ptr[ebp - 0x25], 0x14
            jmp Jumout
            Check13 :
        cmp al, 0xE
            jnz Check14
            mov byte ptr[ebp - 0x25], 0x1E
            jmp Jumout
            Check14 :
        cmp al, 0xF
            jnz Check15
            mov byte ptr[ebp - 0x25], 0x2D
            jmp Jumout
            Check15 :
        cmp al, 0x10
            jnz Check16
            mov byte ptr[ebp - 0x25], 0x3C
            jmp Jumout
            Check16 :
        cmp al, 0x11
            jnz Check17
            mov byte ptr[ebp - 0x25], 0x50
            jmp Jumout
            Check17 :
        cmp al, 0x12
            jnz uNKNOW
            mov byte ptr[ebp - 0x25], 0x78
            jmp Jumout
            Jumout :
        popad
            push 0x00522B00
            ret
            uNKNOW :
        mov byte ptr[ebp - 0x25], 0x00
            popad
            push 0x00522B00
            ret
    }
}

void __declspec(naked)ClockEffect()
{
    __asm
    {
        push 0x1
        mov ecx, [ebp - 0xDBC]
        mov eax, 0x004F563B
        call eax
        mov ecx, [ebp - 0xDBC]
        push 0x005E407F
        ret
    }

}
DWORD backupvalue = 0x0;
DWORD backupvalue1 = 0x0;
DWORD backupvalue2 = 0x0;
DWORD backupvalue3 = 0x0;
DWORD backupvalue4 = 0x0;
DWORD backupvalue5 = 0x0;
DWORD backupvalue6 = 0x0;
DWORD backupvalue7 = 0x0;
DWORD backupvalue8 = 0x0;
DWORD backupvalue9 = 0x0;
DWORD backupvalue10 = 0x0;
DWORD backupvalue11 = 0x0;
DWORD backupvalue12 = 0x0;
DWORD backupvalue13 = 0x0;
DWORD backupvalue14 = 0x0;
DWORD backupvalue15 = 0x0;
DWORD backupvalue16 = 0x0;
DWORD backupvalue17 = 0x0;
void __declspec(naked)SendPacketIncClo()
{
    __asm
    {
        pushad
        xor edx, edx
        mov     eax, [ebp - 0x50]
        mov   dl, byte ptr[eax + 0x531A]
        imul edx, edx, 0x60
        lea edx, [edx + eax + 0x0000128C]
        xor ecx,ecx
        mov cl, [edx + 0x8]
        cmp ecx, 0x1
        jnz Check2Relcs
        jmp SendPacketClothes
        Check2Relcs:
        cmp ecx, 0x13
            jnz WeaponItem
            jmp SendPacketClothes
            WeaponItem :
        cmp ecx, 0x9
        jnz Default
        SendPacketClothes:
        mov edx, [ebp - 0x4C]
        mov backupvalue, edx

        mov edx, [ebp - 0x48]
        mov backupvalue1, edx

        mov edx, [ebp - 0x44]
        mov backupvalue2, edx

        mov edx, [ebp - 0x40]
        mov backupvalue3, edx

        mov edx, [ebp - 0x3C]
        mov backupvalue4, edx

        mov edx, [ebp - 0x38]
        mov backupvalue5, edx

        mov edx, [ebp - 0x34]
        mov backupvalue6, edx

        mov edx, [ebp - 0x30]
        mov backupvalue7, edx

        mov edx, [ebp - 0x2C]
        mov backupvalue8, edx

        mov edx, [ebp - 0x28]
        mov backupvalue9, edx

        mov edx, [ebp - 0x24]
        mov backupvalue10, edx

        mov edx, [ebp - 0x20]
        mov backupvalue11, edx

        mov edx, [ebp - 0x1C]
        mov backupvalue12, edx

        mov edx, [ebp - 0x18]
        mov backupvalue13, edx

        mov edx, [ebp - 0x14]
        mov backupvalue14, edx

        mov edx, [ebp - 0x10]
        mov backupvalue15, edx

        mov edx, [ebp - 0xC]
        mov backupvalue16, edx

        mov edx, [ebp - 0x8]
        mov backupvalue17, edx


        //
        mov byte ptr[ebp - 0x4C], 0x5E
        mov byte ptr[ebp - 0x4B], 0x00
        mov byte ptr[ebp - 0x4A], 0x9F
        mov byte ptr[ebp - 0x49], 0x1F
        xor edx, edx
        mov eax, [ebp - 0x50]
        mov  dl, byte ptr[eax + 0x531A]
        mov[ebp - 0x48], dl
        mov     ecx, [ebp - 0x50]
        imul edx, edx, 0x60
        lea edx, [edx + ecx + 0x0000128C]
        mov ecx, [edx + 0x8]
        mov[ebp - 0x47], ecx
        mov ecx, [edx + 0xC]
        mov[ebp - 0x43], ecx
        mov byte ptr[ebp - 0x3F], 0x1
        mov dword ptr[ebp - 0x3E], 0x00000000
        mov dword ptr[ebp - 0x3A], 0x00000000
        xor ecx, ecx
        mov cl, [edx + 0x18]
        mov[ebp - 0x36], ecx
        mov cl,[edx+0x8]
        cmp ecx,0x13
        jnz RelicItem
        xor ecx, ecx
        mov cl, [edx + 0x18]
        mov [ebp - 0x33], cl
        mov byte ptr[ebp - 0x32], 0xFF
        jmp DefaultOldType1
        RelicItem:
          cmp ecx, 0x9
            jnz DefaultOldType
            xor ecx, ecx
            xor eax, eax
            push ebx
            xor ebx,ebx
            BackLoopCheckValue:
            mov cl, [edx + 0x24+ +0x4+ebx]
            test ecx,ecx
            jz NotValue
            add eax,0x1
            add ebx,0x5
            cmp ebx,0x23
            jnz BackLoopCheckValue
            NotValue:
            pop ebx
            mov[ebp - 0x33], al
            jmp DefaultOldType1
        DefaultOldType:
        mov byte ptr[ebp - 0x32], 0xE
        DefaultOldType1:
        //Option 1
        xor ecx, ecx
        mov ecx, [edx + 0x24]
        mov [ebp - 0x31], ecx
         xor ecx, ecx
         mov cl, [edx + 0x28]
         mov [ebp - 0x2D], cl
            //Option 2
            xor ecx, ecx
            mov ecx, [edx + 0x29]
            mov[ebp - 0x2C], ecx

            xor ecx, ecx
            mov cl, [edx + 0x2D]
            mov[ebp - 0x28], cl
            //Option 3
            xor ecx, ecx
            mov ecx, [edx + 0x2E]
            mov[ebp - 0x27], ecx

            xor ecx, ecx
            mov cl, [edx + 0x32]
            mov[ebp - 0x23], cl
            //Option 4
            xor ecx, ecx
            mov ecx, [edx + 0x33]
            mov[ebp - 0x22], ecx

            xor ecx, ecx
            mov cl, [edx + 0x37]
            mov[ebp - 0x1E], cl
            //Option 5
            xor ecx, ecx
            mov ecx, [edx + 0x38]
            mov[ebp - 0x1D], ecx

            xor ecx, ecx
            mov cl, [edx + 0x3C]
            mov[ebp - 0x19], cl
            //Option 6
            xor ecx, ecx
            mov ecx, [edx + 0x3D]
            mov[ebp - 0x18], ecx

            xor ecx, ecx
            mov cl, [edx + 0x41]
            mov[ebp - 0x14], cl
        mov     dx, [ebp - 0x4C]
        and dx, 0x7FFF
        and edx, 0xFFFF
        push    edx
        lea     ecx, [ebp - 0x4C]
        push    ecx
        mov     ecx, [ebp - 0x50]
        mov eax, 0x69479A
        call eax
        //
        xor edx, edx
        mov edx, backupvalue
        mov[ebp - 0x4C], edx

        mov edx, backupvalue1
        mov[ebp - 0x48], edx

        mov edx, backupvalue2
        mov[ebp - 0x44], edx

        mov edx, backupvalue3
        mov[ebp - 0x40], edx

        mov edx, backupvalue4
        mov[ebp - 0x3C], edx

        mov edx, backupvalue5
        mov[ebp - 0x38], edx

        mov edx, backupvalue6
        mov[ebp - 0x34], edx

        mov edx, backupvalue7
        mov[ebp - 0x30], edx

        mov edx, backupvalue8
        mov[ebp - 0x2C], edx

        mov edx, backupvalue9
        mov[ebp - 0x28], edx

        mov edx, backupvalue10
        mov[ebp - 0x24], edx

        mov edx, backupvalue11
        mov[ebp - 0x20], edx

        mov edx, backupvalue12
        mov[ebp - 0x1C], edx

        mov edx, backupvalue13
        mov[ebp - 0x18], edx

            mov edx, backupvalue14
            mov[ebp - 0x14], edx

            mov edx, backupvalue15
            mov[ebp - 0x10], edx

            mov edx, backupvalue16
            mov[ebp - 0xC], edx

            mov edx, backupvalue17
            mov[ebp - 0x8], edx

        Default :
        popad
            mov ecx, [ebp - 0x10]
            mov fs : [00000000] , ecx
            push 0x00522CC7
            ret
    }

}
DWORD ADDRESSUSER = 0x0;
void __declspec(naked)DisableEffect()
{
    __asm
    {
        push 0x1
        mov ecx, [ebp - 0x8B0]
        mov eax, 0x004F563B
        call eax

        xor edx, edx
        mov  ecx, [ebp - 0x8B0]
        mov dl, [ecx + 0x3780 + 0x128C + 0x8]
        cmp edx,0x9
        jnz DefaultLoadPet112
        xor edx, edx
        mov dx, [ecx + 0x3780 + 0x128C + 0xA]
        cmp edx,0x48E
        jl DefaultLoadPet112
        cmp edx, 0x496
        jg DefaultLoadPet112
        pushad
        //CreatePet
        /*mov ecx, [ebp - 0x88E]
        push ecx
        mov ecx, [ebp - 0x88A]
        push ecx
        mov  ecx, [ebp - 0x8B0]
        mov eax, 0x00431F70
        call eax
        push ecx
        fstp dword ptr[esp]
        pop ecx
        mov[ebp - 0x88E], ecx
        mov  ecx, [ebp - 0x8B0]
        mov eax, 0x00431F90
        call eax
        push ecx
        fstp dword ptr[esp]
        pop ecx
        mov[ebp - 0x88A], ecx*/
        //Check Mod
        mov  ecx, [ebp - 0x8B0]
        xor eax,eax
        mov ax,[ecx+ 0x3780 +0x128C+0xA]
        cmp eax, 0x48E
        jnz GetIdMod1
        mov edx, 0x3E7
        call AddSkillForPet
        mov eax, 0xD4B
        jmp callboss
        GetIdMod1 :
        cmp eax, 0x48F
            jnz GetIdMod12
            mov edx,0x3E7
            call AddSkillForPet
            mov eax, 0x1CEC
            jmp callboss
            GetIdMod12 :
        cmp eax, 0x490
            jnz GetIdMod13
            mov edx, 0x3E7
            call AddSkillForPet
            mov eax, 0x1CED
            jmp callboss
            GetIdMod13 :
        cmp eax, 0x491
            jnz GetIdMod14
            mov edx, 0x3E7
            call AddSkillForPet
            mov eax, 0x1CEE
            jmp callboss

            GetIdMod14 :
        cmp eax, 0x492
            jnz GetIdMod15
            mov edx, 0x3E7
            call AddSkillForPet
            mov eax, 0x1CEF
            jmp callboss

            GetIdMod15 :
        cmp eax, 0x493
            jnz GetIdMod16
            mov edx, 0x3E7
            call AddSkillForPet
            mov eax, 0x1CF0
            jmp callboss

            GetIdMod16 :
        cmp eax, 0x494
            jnz GetIdMod17
            mov edx, 0x3E7
            call AddSkillForPet
            mov eax, 0x1CF1
            jmp callboss

            GetIdMod17 :
        cmp eax, 0x495
            jnz GetIdMod18
            mov edx, 0x3E7
            call AddSkillForPet
            mov eax, 0x1CF2
            jmp callboss

            GetIdMod18 :
        cmp eax, 0x496
            jnz callboss
            mov edx, 0x3E7
            call AddSkillForPet
            mov eax, 0x1CF3
            jmp callboss
        //
            callboss:
        push 0x0
        push 0x0
        push 0x0
        lea edx, [ebp - 0x88E]
        push edx
        push 0x0
        push eax
        mov eax, 0x00406B10
        call eax
        mov ecx, eax
        mov eax, 0x005BB34D
        call eax
        mov  ecx, [ebp - 0x8B0]
        mov[ecx + 0x10A4], eax
        mov cx, ax
        push ecx
        mov eax, 0x00406B10
        call eax
        mov ecx, eax
        mov eax, 0x0005BBB29
        call eax
        mov  ecx, [ebp - 0x8B0]
            xor eax, eax
            mov ax, [ecx + 0x10A4]
            push eax
            mov eax, 0x00406B10
            call eax
            xor edx, edx
            mov  edx, [ebp - 0x8B0]
            mov ecx, eax
            mov ax, [edx + 0x10A4]
            push eax
            mov eax, 0x40AD70
            call eax
            mov  ecx, [ebp - 0x8B0]
            mov[ecx + 0x10A4], eax
            pop ecx
            mov[ebp - 0x88A], ecx
            pop ecx
            mov[ebp - 0x88E], ecx

            mov  ecx, [ebp - 0x8B0]
            mov ecx, [ecx + 0x10A4]

            mov byte ptr [ecx + 0x30],0x6D
            mov byte ptr [ecx+0x17],0x1
            mov edx, [ecx + 0x8]
            mov ebx, 0x41700000
            mov dword ptr[edx + 0x3C], ebx
        //
        popad
            mov ecx, [ebp - 0x8B0]
            push 0x00495666
            ret
            DefaultLoadPet112:

mov ecx, [ebp - 0x8B0]
mov dword ptr[ecx + 0x10A4],0x0000
push 0x00495666
ret
            /*DefaultLoadPet :
        mov  ecx, [ebp - 0x000008B0]
            mov dword ptr [ecx+0x10A4],0x00000000
            jmp DefaultLoadPet112*/

            AddSkillForPet:
            push 0x3349
            mov  ecx, [ebp - 0x8B0]
            mov eax, 0x0041F160
            call eax
            push 0x0
            push 0x0
            push 0x0
            push edx
            mov  ecx, [ebp - 0x8B0]
            mov eax, 0x004DB99D
            call eax
            push 0x334B
            mov  ecx, [ebp - 0x8B0]
            mov eax, 0x0041F180
            call eax
            ret
    }

}
DWORD reportDamage = 0x0;
void __declspec(naked)MoreDamageSkill()
{
    __asm
    {
        pushad
        xor ebx, ebx
        mov edx, [ebp - 0xE6B0]
        cmp edx, 0xFFFF
        jle Default
        SubAgain :
        sub edx, 0xFFFF
            add ebx, 0x01
            cmp edx, 0xFFFF
            jg SubAgain
            mov cl, [ebp - 0x831]
            cmp cl, 0x1
            jz Die
            mov ecx, ebx
            add ecx, 0x01
            mov[ebp - 0x831], cl
            mov[ebp - 0x833], dx
            popad
            push 0x005DCFB7
            ret

            Die :
        xor ecx, ecx
            add ebx, 0x32
            mov ecx, ebx
            mov[ebp - 0x831], cl
            mov[ebp - 0x833], dx
            popad
            push 0x005DCFB7
            ret

            Default :
        popad
            xor edx,edx
            mov dx, [ebp - 0xE6B0]
            mov[ebp - 0x833], dx
            push 0x005DCFB7
            ret
    }
}
void __declspec(naked)MoreDamageSkillNuker()
{
    __asm
    {
        pushad
        xor ebx, ebx
        mov edx, [ebp - 0xE6F4]
        cmp edx, 0xFFFF
        jle Default
        SubAgain :
        sub edx, 0xFFFF
            add ebx, 0x01
            cmp edx, 0xFFFF
            jg SubAgain
            mov cl, [ebp - 0x809]
            cmp cl, 0x1
            jz Die
            mov ecx, ebx
            add ecx, 0x01
            mov[ebp - 0x809], cl
            mov[ebp - 0x80B], dx
            popad
            push 0x005DE4FA
            ret

            Die :
        xor ecx, ecx
            add ebx, 0x32
            mov ecx, ebx
            mov[ebp - 0x809], cl
            mov[ebp - 0x80B], dx
            popad
            push 0x005DE4FA
            ret

            Default :
        popad
            mov dx, [ebp - 0xE6F4]
            mov[ebp - 0x80B], dx
            push 0x005DE4FA
            ret
    }
}
void __declspec(naked)MoreDamageSkillNuker1()
{
    __asm
    {
        pushad
        xor ebx, ebx
        mov edx, [ebp - 0xE5F0]
        cmp edx, 0xFFFF
        jle Default
        SubAgain :
        sub edx, 0xFFFF
            add ebx, 0x01
            cmp edx, 0xFFFF
            jg SubAgain
            mov cl, [ebp - 0x9099]
            cmp cl, 0x1
            jz Die
            mov ecx, ebx
            add ecx, 0x01
            mov[ebp - 0x9099], cl
            mov[ebp - 0x909B], dx
            popad
            push 0x005D7930
            ret

            Die :
        xor ecx, ecx
            add ebx, 0x32
            mov ecx, ebx
            mov[ebp - 0x9099], cl
            mov[ebp - 0x909B], dx
            popad
            push 0x005D7930
            ret

            Default :
        popad
            mov dx, [ebp - 0xE5F0]
            mov[ebp - 0x909B], dx
            push 0x005D7930
            ret
    }
}
void __declspec(naked)FixOptDecco()
{
    __asm
    {
        pushad
        xor edx,edx
        mov ecx, [ebp - 0x18]
        mov dl,[ecx + 0x2A0 + 0x128C + 0x8]
        cmp edx,0x1
        jnz Default
        xor edx, edx
        mov dx,[ecx+0x2A0+0x128C+0xA]
        push edx
        mov dl,[ecx + 0x2A0 + 0x128C + 0x8]
        push edx
        mov ecx, 0x00776388
        mov ecx,[ecx]
        mov eax,0x4D7FB0
        call eax
        and eax,0xFFFF
        push eax
        mov ecx, 0x00776388
        mov ecx, [ecx]
        mov eax,0x641930
        call eax
        xor edx,edx
        mov ebx, [eax + 0x18]
        test ebx,ebx
        jz Default
        xor edi, edi
        LoopAdd:
        push eax
        mov dx,[ebx]
        mov eax, [ebp - 0x18]
        cmp dx, 0x13
        jnz CheckType2
        xor edx,edx
        mov dx, [ebx+0x4]
        mov ecx, [eax + 0x6FD4]
        lea ecx, [ecx + edx]
        mov[eax + 0x6FD4], ecx
        jmp EndCheck

        CheckType2 :
        cmp dx, 0x18
            jnz CheckType3
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + edx]
            mov[eax + 0x702C], ecx
            jmp EndCheck


            CheckType3 :
        cmp dx, 0x82
            jnz CheckType4
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7250]
            lea ecx, [ecx + edx]
            mov[eax + 0x7250], ecx
            jmp EndCheck


            CheckType4 :
        cmp dx, 0x83
            jnz CheckType5
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7258]
            lea ecx, [ecx + edx]
            mov[eax + 0x7258], ecx
            jmp EndCheck


            CheckType5 :
        cmp dx, 0x17
            jnz CheckType6
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + edx]
            mov[eax + 0x7024], ecx
            jmp EndCheck


            CheckType6 :
        cmp dx, 0x32
            jnz CheckType7
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheck


            CheckType7 :
        cmp dx, 0x3D
            jnz CheckType8
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheck


            CheckType8 :
        cmp dx, 0x2
            jnz CheckType9
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC4], ecx
            jmp EndCheck


            CheckType9 :
        cmp dx, 0x1
            jnz CheckType10
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck


            CheckType10 :
        cmp dx, 0xF
            jnz CheckType11
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheck


            CheckType11 :
        cmp dx, 0x34
            jnz CheckType12
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7240 + 0x4]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheck


            CheckType12 :
        cmp dx, 0x89
            jnz CheckType13
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck


            CheckType13 :
        cmp dx, 0x88
            jnz CheckType14
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FBC], ecx
            jmp EndCheck


            CheckType14 :
        cmp dx, 0x10
            jnz EndCheck
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx
            jmp EndCheck

            EndCheck:
            pop eax
            mov ebx, [ebx + 0x10]
            test ebx,ebx
            jne LoopAdd
            add edi,0x1
            cmp edi,0x2
            jz Default
            mov ebx, [eax + 0x1C]
            test ebx,ebx
            jne LoopAdd

                Default:
            xor edx, edx
                mov ecx, [ebp - 0x18]
                mov dl, [ecx + 0x2A0 + 0x128C + 0x8]
                cmp edx, 0x1
                jnz Default22
                xor edx, edx
                mov dx, [ecx + 0x2A0 + 0x128C + 0xA]
                push edx
                mov dl, [ecx + 0x2A0 + 0x128C + 0x8]
                push edx
                mov ecx, 0x00776388
                mov ecx, [ecx]
                mov eax, 0x4D7FB0
                call eax
                and eax, 0xFFFF
                push eax
                mov ecx, 0x00776388
                mov ecx, [ecx]
                mov eax, 0x641930
                call eax
                xor edx, edx
                mov ebx, [eax + 0x18]
                test ebx, ebx
                jz Default22
                xor edi, edi
                LoopAdd2 :
            push eax
                mov dx, [ebx]
                mov eax, [ebp - 0x18]
                cmp dx, 0x13
                jnz CheckType2
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FD4]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FD4], ecx
                jmp EndCheck2D

                CheckType22 :
            cmp dx, 0x18
                jnz CheckType23
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x702C]
                lea ecx, [ecx + edx]
                mov[eax + 0x702C], ecx
                jmp EndCheck2D


                CheckType23 :
            cmp dx, 0x82
                jnz CheckType24
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x7250]
                lea ecx, [ecx + edx]
                mov[eax + 0x7250], ecx
                jmp EndCheck2D


                CheckType24 :
            cmp dx, 0x83
                jnz CheckType25
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x7258]
                lea ecx, [ecx + edx]
                mov[eax + 0x7258], ecx
                jmp EndCheck2D


                CheckType25 :
            cmp dx, 0x17
                jnz CheckType26
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x7024]
                lea ecx, [ecx + edx]
                mov[eax + 0x7024], ecx
                jmp EndCheck2D


                CheckType26 :
            cmp dx, 0x32
                jnz CheckType27
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov cx, [eax + 0x7240]
                lea ecx, [ecx + edx]
                mov[eax + 0x7240], cx
                jmp EndCheck2D


                CheckType27 :
            cmp dx, 0x3D
                jnz CheckType28
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FD4]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FD4], ecx
                jmp EndCheck2D


                CheckType28 :
            cmp dx, 0x2
                jnz CheckType29
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FC4]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FC4], ecx
                jmp EndCheck2D


                CheckType29 :
            cmp dx, 0x1
                jnz CheckType210
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FFC]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FFC], ecx
                jmp EndCheck2D


                CheckType210 :
            cmp dx, 0xF
                jnz CheckType211
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FC8]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FC8], ecx
                jmp EndCheck2D


                CheckType211 :
            cmp dx, 0x34
                jnz CheckType212
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov cx, [eax + 0x7240 + 0x4]
                lea ecx, [ecx + edx]
                mov[eax + 0x7240], cx
                jmp EndCheck2D


                CheckType212 :
            cmp dx, 0x89
                jnz CheckType213
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FFC]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FFC], ecx
                jmp EndCheck2D


                CheckType213 :
            cmp dx, 0x88
                jnz CheckType214
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FBC]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FBC], ecx
                jmp EndCheck2D


                CheckType214 :
            cmp dx, 0x10
                jnz EndCheck2D
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x7000]
                lea ecx, [ecx + edx]
                mov[eax + 0x7000], ecx
                jmp EndCheck2D

                EndCheck2D :
            pop eax
                mov ebx, [ebx + 0x10]
                test ebx, ebx
                jne LoopAdd2
                add edi, 0x1
                cmp edi, 0x2
                jz Default22
                mov ebx, [eax + 0x1C]
                test ebx, ebx
                jne LoopAdd2

            Default22:
        popad
        mov edx, [ebp - 10]
        and edx, 0x000000FF
        push 0x004D147D
        ret
    }
}

void __declspec(naked)MoreDamageThuc1()
{
    __asm
    {
        pushad
        xor ebx, ebx
        mov ecx, [ebp - 0x24]
        cmp ecx, 0xFFFF
        jle Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            jg SubAgain2
            add ebx, 0x01
            mov[eax + 0x10], cx
            mov[eax + 0x19], bl
            push 0x0058816B
            ret

            Default :
        popad
            mov  cx, [ebp - 0x24]
            mov[eax + 0x10], cx
            mov[eax + 0x19], 0x00
            push 0x00588159
            ret
    }
}
void __declspec(naked)FixAmDamagePvp()
{
    __asm
    {
        sub     edx, [ebp - 0x84]
        and edx, 0xFFFF
        push 0x004B99CD
        ret
    }
}
void __declspec(naked)FixAmDamagePvp1()
{
    __asm
    {
        sub     eax, edx
        and eax, 0xFFFF
        mov[ebp - 0x54], eax
        push 0x004B9A01
        ret
    }
}

void __declspec(naked)MoreDamageThuc2()
{
    __asm
    {
        pushad
        xor ebx, ebx
        mov ecx, [ebp - 0x24]
        cmp ecx, 0xFFFF
        jle Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            jg SubAgain2
            add ebx, 0x27
            mov[eax + 0x10], cx
            mov[eax + 0x13], cx
            mov[eax + 0x19], bl
            push 0x00588035
            ret

            Default :
        popad
            mov  cx, [ebp - 0x24]
            mov[eax + 0x10], cx
            mov[eax + 0x19], 0x00
            push 0x0058802A
            ret
    }
}
DWORD checkDie1 = 0x01;
void __declspec(naked)MoreDamageThucDie()
{
    __asm
    {
        push eax
        xor eax, eax
        mov checkDie1, 0x00000000
        mov ecx, [ebp + 0xC]
        mov  al, byte ptr[ecx + 0x19]
        cmp eax, 0x2
        jl Check2
        cmp eax, 0x11
        jg Check2
        add eax, 0x12
        jmp Default
        //
        Check2 :
        cmp eax, 0x28
            jl Check3
            cmp eax, 0x37
            jg Check3
            add eax, 0x14
            jmp Default

            //
            Check3 :
        cmp eax, 0x50
            jl Check4
            cmp eax, 0x5F
            jg Check4
            add eax, 0x14
            jmp Default

            //
            Check4 :

        mov eax, 0x01
            Default :
            mov ecx, [ebp + 0xC]
            mov byte ptr[ecx + 0x19], al
            pop eax
            push 0x005887D8
            ret
    }
}
DWORD checkDie2 = 0x00;
void __declspec(naked)MoreDamageThucDie2()
{
    __asm
    {
        mov     edx, [ebp + 0xC]
        //mov     checkDie2,byte ptr[edx+0x19]
    }
    if (checkDie2 == 0)
    {

    }
    __asm
    {
        push 0x00588724
        ret
    }
}
void __declspec(naked)GetAmDmgTanker1()
{
    __asm mov[ebp - 0x88], eax
    __asm push 0x004B8F89
    __asm ret
}
void __declspec(naked)GetAmDmgTanker11()
{
    __asm mov eax, dword ptr[ebp - 0x88]
        __asm push 0x004B8F5E
    __asm ret
}
void __declspec(naked)GetAmDmgTanker2()
{
    __asm mov[ebp - 0x88], eax
    __asm push 0x004B8F38
    __asm ret
}
void __declspec(naked)GetAmDmgTanker22()
{
    __asm mov eax, dword ptr[ebp - 0x88]
        __asm push 0x004B8FAF
    __asm ret
}
void __declspec(naked)GetAmDmgNuker()
{
    __asm mov eax, dword ptr[ebp - 0x1C]
        __asm push  eax
    __asm push 0x004C8B47
    __asm ret
}
void __declspec(naked)GetAmDmgNuker2()
{
    __asm mov   edx, eax
    __asm mov[ebp - 0x84], edx
    __asm push 0x004B98E9
    __asm ret
}
void __declspec(naked)FixAmDamTanker()
{
    __asm
    {
        mov eax, dword ptr[ebp - 0x1C]
        push eax
        push 0x004C82D2
        ret
    }
}
void __declspec(naked)MoreDamageThuc3()
{
    __asm
    {
        pushad
        xor ebx, ebx
        mov ecx, [ebp - 0x24]
        cmp ecx, 0xFFFF
        jle Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            jg SubAgain2
            add ebx, 0x4F
            mov[eax + 0x10], cx
            mov[eax + 0x19], bl
            mov[eax + 0x16], cx
            mov[eax + 0x13], cx
            push 0x00587EA3
            ret

            Default :
        popad
            mov  cx, [ebp - 0x24]
            mov[eax + 0x10], cx
            mov[eax + 0x19], 0x00
            push 0x00587E89
            ret
    }
}
void __declspec(naked)MoreDamageThuc3Die()
{
    __asm
    {
        push 0x00588159
        ret
    }
}
void __declspec(naked)MoreDamageThuc3NoDie()
{
    __asm
    {
        push 0x00588159
        ret
    }
}

/*void __declspec(naked)MoreDamageMax()
{
    __asm
    {
        pushad
        mov ebx, ebx
        mov  eax, [ebp + 0xC]
        mov  ecx, [ebp - 0x24]
        cmp ecx, 0xFFFF
        jle Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            jg SubAgain2
            mov[eax + 0x10], cx
            mov     edx, [ebp + 0xC]
            mov     word ptr[edx + 0x13], 0x1
            mov     eax, [ebp + 0xC]
            mov     word ptr[eax + 0x16], 0
            push 0x0058816B
            ret

            Default :
        popad
            mov  cx, [ebp - 0x24]
            push 0x00588155
            ret
    }
}*/
DWORD AdresStoreIem = 0x0;
void __declspec(naked)ExchangeItem()
{
    __asm
    {
        pushad
        mov     ecx, [ebp + 0x8]
        xor edx, edx
        mov     dl, [ecx + 0x5]
        imul    edx, 0x60
        mov     eax, [ebp - 0x6C]
        lea ecx, [eax + edx + 0x128C]
        mov[ebp - 0x50], ecx
        mov al, [ecx + 0x8]
        cmp al, 0xA
        jnz InChantRelicItem
        mov al, [ecx + 0xA]
        cmp al, 0x4E
        jnz RsOther
        popad
        push 1
        mov ecx, [ebp - 0x6C]
        mov eax, 0x50F9E2
        call eax
        cmp eax, 0x4C4B40
        jb NotRequest
        mov edx, [ebp - 0x50]
        mov cl, [edx + 0xF]
        sbb cl, 0x1
        mov[edx + 0xF], cl
        cmp cl, 0x0
        jnz KoBangKhong
        mov ecx, [ebp + 0x8]
        mov cl, [ecx + 0x5]
        push ecx
        mov ecx, [ebp - 0x6C]
        mov eax, 0x004B2960
        call eax
        KoBangKhong :
        mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            imul eax, eax, 0x60
            mov ecx, [ebp - 0x6C]
            lea edx, [ecx + eax + 0x0000128C]
            mov  AdresStoreIem, edx
            push 0x00
            mov cx, [edx + 0xA]
            push ecx
            mov cl, [edx + 0x8]
            push ecx
            mov edx, [ebp + 0x8]
            mov al, [edx + 0x4]
            push eax
            push 0x0
            mov ecx, [ebp - 0x6C]
            mov eax, 0x004A257B
            call eax
            mov[ebp - 0x60], 0xEC
            mov[ebp - 0x5F], 0x00
            mov[ebp - 0x5E], 0x7C
            mov[ebp - 0x5D], 0x04
            mov[ebp - 0x5C], 0x08
            mov edx, AdresStoreIem
            mov al, [edx + 0x18]
            mov[ebp - 0x5B], al
            mov edx, [ebp - 0x50]
            mov cl, [edx + 0xF]
            mov[ebp - 0x5A], cl
            push 1
            mov ecx, [ebp - 0x6C]
            mov eax, 0x50F9E2
            call eax
            sbb eax, 0x4C4B40
            push eax
            mov ecx, [ebp - 0x6C]
            mov edx, eax
            mov eax, 0x050FA03
            call eax
            mov[ebp - 0x58], edx
            mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            mov[ebp - 0x59], al
            mov dx, [ebp - 0x60]
            and dx, 0x7FFF
            and edx, 0xFFFF
            push edx
            lea eax, [ebp - 0x60]
            push eax
            mov ecx, [ebp - 0x6C]
            mov eax, 0x69479A
            call eax
            push 0x00415D5D
            ret

            RsOther :
        cmp al, 0x4D
            jnz RsOther1
            popad
            push 1
            mov ecx, [ebp - 0x6C]
            mov eax, 0x50F9E2
            call eax
            cmp eax, 0x4C4B40
            jb NotRequest
            mov edx, [ebp - 0x50]
            mov cl, [edx + 0xF]
            sub cl, 0x1
            mov[edx + 0xF], cl
            cmp cl, 0x0
            jnz KoBangKhong1
            mov ecx, [ebp + 0x8]
            mov cl, [ecx + 0x5]
            push ecx
            mov ecx, [ebp - 0x6C]
            mov eax, 0x004B2960
            call eax
            KoBangKhong1 :
            mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            imul eax, eax, 0x60
            mov ecx, [ebp - 0x6C]
            lea edx, [ecx + eax + 0x0000128C]
            mov  AdresStoreIem, edx
            mov dword ptr[edx + 0x1C], 0x2300
            mov[ebp - 0x60], 0xEC
            mov[ebp - 0x5F], 0x00
            mov[ebp - 0x5E], 0x7C
            mov[ebp - 0x5D], 0x04
            mov[ebp - 0x5C], 0x09
            mov edx, AdresStoreIem
            mov al, [edx + 0x18]
            mov[ebp - 0x5B], al
            mov edx, [ebp - 0x50]
            mov cl, [edx + 0xF]
            mov[ebp - 0x5A], cl
            push 1
            mov ecx, [ebp - 0x6C]
            mov eax, 0x50F9E2
            call eax
            sub eax, 0x4C4B40
            push eax
            mov edx, eax
            mov ecx, [ebp - 0x6C]
            mov eax, 0x050FA03
            call eax
            mov[ebp - 0x58], edx
            mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            mov[ebp - 0x59], al
            mov dx, [ebp - 0x60]
            and dx, 0x7FFF
            and edx, 0xFFFF
            push edx
            lea eax, [ebp - 0x60]
            push eax
            mov ecx, [ebp - 0x6C]
            mov eax, 0x69479A
            call eax
            push 0x00415D5D
            ret


            RsOther1 :
            cmp al, 0x4B
            jnz JumOut
            popad
            mov edx, [ebp - 0x50]
            mov cl, [edx + 0xF]
            sub cl, 0x1
            mov[edx + 0xF], cl
            cmp cl, 0x0
            jnz KoBangKhong11
            mov ecx, [ebp + 0x8]
            mov cl, [ecx + 0x5]
            push ecx
            mov ecx, [ebp - 0x6C]
            mov eax, 0x004B2960
            call eax
            KoBangKhong11 :
        mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            imul eax, eax, 0x60
            mov ecx, [ebp - 0x6C]
            lea edx, [ecx + eax + 0x0000128C]
            mov  AdresStoreIem, edx
            xor eax, eax
            mov al, [edx + 0x8]
            cmp al, 0x13
            jnz NotRequest
            xor eax, eax
            mov eax, AdresStoreIem
            mov ax, [eax + 0xA]
            cmp ax, 0x2EF0
            jz Acceptitem
            cmp ax, 0x2EF1
            jz Acceptitem
            cmp ax, 0x2EF2
            jz Acceptitem
            cmp ax, 0x2EF3
            jz Acceptitem
            cmp ax, 0x2EF4
            jz Acceptitem
            cmp ax, 0x2EF5
            jz Acceptitem
            cmp ax, 0x2EF6
            jz Acceptitem
            cmp ax, 0x2EF7
            jz Acceptitem
            cmp ax, 0x2EF8
            jz Acceptitem
            cmp ax, 0x2EF9
            jz Acceptitem
            jmp NotRequest
            Acceptitem :
        mov byte ptr[edx + 0x18], 0x12
            mov[ebp - 0x60], 0xEC
            mov[ebp - 0x5F], 0x00
            mov[ebp - 0x5E], 0x7C
            mov[ebp - 0x5D], 0x04
            mov[ebp - 0x5C], 0x00
            mov edx, AdresStoreIem
            mov al, [edx + 0x18]
            mov[ebp - 0x5B], al
            mov edx, [ebp - 0x50]
            mov cl, [edx + 0xF]
            mov[ebp - 0x5A], cl
            push 1
            mov ecx, [ebp - 0x6C]
            mov eax, 0x50F9E2
            call eax
            mov[ebp - 0x58], eax
            mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            mov[ebp - 0x59], al
            mov dx, [ebp - 0x60]
            and dx, 0x7FFF
            and edx, 0xFFFF
            push edx
            lea eax, [ebp - 0x60]
            push eax
            mov ecx, [ebp - 0x6C]
            mov eax, 0x69479A
            call eax
            push 0x00415D5D
            ret
            InChantRelicItem:
            mov al, [ecx + 0x8]
            cmp al, 0x7
            jnz JumOut
                xor eax,eax
                mov ax, [ecx + 0xA]
                jmp AddSlotForRelic
                BackAddSlotForRelicCurrent:
                mov edx, [ebp + 0x8]
                xor eax, eax
                mov al, [edx + 0x4]
                imul eax, eax, 0x60
                mov ecx, [ebp - 0x6C]
                lea edx, [ecx + eax + 0x0000128C]
                xor ecx, ecx
                mov cl,[edx+0x8]
                cmp ecx,0x13
                jz WeaponUpgrade
                mov     ecx, [ebp + 0x8]
                xor edx, edx
                mov     dl, [ecx + 0x5]
                imul    edx, 0x60
                mov     eax, [ebp - 0x6C]
                lea ecx, [eax + edx + 0x128C]
            xor eax,eax
            mov ax, [ecx + 0xA]
            cmp ax, 0x2F6
            jl JumOut
            cmp ax, 0x2FF
            jg ItemRs2
            xor eax, eax
            lea eax, ListDa31
            jmp MainFun

            ItemRs2 :
        cmp ax, 0x309
            jg ItemRs3
            xor eax, eax
            lea eax, ListDa32
            jmp MainFun

            ItemRs3 :
        cmp ax, 0x313
            jg ItemRs4
            xor eax, eax
            lea eax, ListDa33
            jmp MainFun

            ItemRs4 :
        cmp ax, 0x31D
            jg ItemRs5
            xor eax, eax
            lea eax, ListDa34
            jmp MainFun

            ItemRs5 :
        cmp ax, 0x327
            jg ItemRs6
            xor eax, eax
            lea eax, ListDa35
            jmp MainFun

            ItemRs6 :
        cmp ax, 0x331
            jg ItemRs7
            xor eax, eax
            lea eax, ListDa1
            jmp MainFun

            ItemRs7 :
        cmp ax, 0x33B
            jg ItemRs8
            xor eax, eax
            lea eax, ListDa2
            jmp MainFun

            ItemRs8 :
        cmp ax, 0x345
            jg ItemRs9
            xor eax, eax
            lea eax, ListDa3
            jmp MainFun

            ItemRs9 :
        cmp ax, 0x34F
            jg ItemRs10
            xor eax, eax
            lea eax, ListDa4
            jmp MainFun

            ItemRs10 :
        cmp ax, 0x359
            jg ItemRs11
            jmp JumOut

            ItemRs11 :
        cmp ax, 0x363
            jg ItemRs12
            xor eax, eax
            lea eax, ListDa6
            jmp MainFun

            ItemRs12 :
        cmp ax, 0x36D
            jg ItemRs13
            jmp JumOut

            ItemRs13 :
        cmp ax, 0x377
            jg ItemRs14
            jmp JumOut

            ItemRs14 :
        cmp ax, 0x381
            jg ItemRs15
            jmp JumOut

            ItemRs15 :
        cmp ax, 0x38B
            jg ItemRs16
            jmp JumOut

            ItemRs16 :
        cmp ax, 0x395
            jg ItemRs17
            jmp JumOut

            ItemRs17 :
        cmp ax, 0x39F
            jg ItemRs18
            jmp JumOut

            ItemRs18 :
        cmp ax, 0x3A9
            jg ItemRs19
            xor eax, eax
            lea eax, ListDa13
            jmp MainFun

            ItemRs19 :
        cmp ax, 0x3B3
            jg ItemRs20
            jmp JumOut

            ItemRs20 :
        cmp ax, 0x3BD
            jg ItemRs21
            xor eax, eax
            lea eax, ListDa15
            jmp MainFun

            ItemRs21 :
        cmp ax, 0x3C7
            jg ItemRs22
            jmp JumOut

            ItemRs22 :
        cmp ax, 0x3D1
            jg ItemRs23
            jmp JumOut

            ItemRs23 :
        cmp ax, 0x3DB
            jg ItemRs24
            xor eax, eax
            lea eax, ListDa18
            jmp MainFun

            ItemRs24 :
        cmp ax, 0x3E5
            jg ItemRs25
            xor eax, eax
            lea eax, ListDa19
            jmp MainFun

            ItemRs25 :
        cmp ax, 0x3EF
            jg ItemRs26
            xor eax, eax
            lea eax, ListDa20
            jmp MainFun

            ItemRs26 :
        cmp ax, 0x3F9
            jg ItemRs27
            jmp JumOut

            ItemRs27 :
        cmp ax, 0x403
            jg ItemRs28
            jmp JumOut

            ItemRs28 :
        cmp ax, 0x40D
            jg ItemRs29
            jmp JumOut

            ItemRs29 :
        cmp ax, 0x417
            jg ItemRs30
            jmp JumOut

            ItemRs30 :
        cmp ax, 0x421
            jg ItemRs31
            jmp JumOut

            ItemRs31 :
        cmp ax, 0x42B
            jg ItemRs32
            jmp JumOut


            ItemRs32 :
        cmp ax, 0x435
            jg ItemRs33
            jmp JumOut


            ItemRs33 :
        cmp ax, 0x43F
            jg ItemRs34
            jmp JumOut

            ItemRs34 :
        cmp ax, 0x449
            jg ItemRs35
            jmp JumOut

            ItemRs35 :
        cmp ax, 0x453
            jg JumOut
            jmp JumOut



        MainFun:
            push eax
            mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            imul eax, eax, 0x60
            mov ecx, [ebp - 0x6C]
            lea edx, [ecx + eax + 0x0000128C]
            xor ecx, ecx
            BackloopCheckValue :
            pop eax
            push eax
            xor ebx, ebx
            mov bx, [edx + 0x24 + ecx+0x4]
            test ebx,ebx
            jz JumOut321
            xor ebx, ebx
            mov bx, [edx + 0x24 + ecx]
            test ebx, ebx
            jz AddNewValue
            mov eax, [eax]
            cmp eax, ebx
            jz InctValue
            add ecx, 0x5
            cmp ecx, 0x1E
            jz JumOut321
            jmp BackloopCheckValue
            
            JumOut321:
            pop eax
            jmp JumOut
            AddNewValue :
            xor ebx, ebx
            pop eax
            push eax
            push edx
            push ecx
            mov ebx, [eax + 0x4]
            mov ecx, [ebp + 0x8]
            xor edx, edx
            mov  dl, [ecx + 0x5]
            imul edx, 0x60
            mov  eax, [ebp - 0x6C]
            lea ecx, [eax + edx + 0x128C]
            xor eax, eax
            mov ax, [ecx + 0xA]
            pop ecx
            pop edx
            cmp eax, ebx
            pop eax
            jnz JumOut
            xor ebx, ebx
            mov ebx, [eax]
            mov[edx + 0x24 + ecx], bx
            cmp ebx,0x17
            jnz DefaultOptionAdd
            mov ebx,0x64
            jmp BpassDefaultOptionAdd
            DefaultOptionAdd:
            mov ebx,0x1
            BpassDefaultOptionAdd:
            mov[edx + 0x24 + ecx + 0x2], bx
            mov[edx + 0x24 + ecx + 0x4], 0x10
            jmp DefaultIncRelics

            //
            InctValue :
        xor ebx, ebx
            mov bl, [edx + 0x24 + ecx + 0x4]
            call GetTwoValue
            pop eax
            push edx
            push ecx
            mov bx, [eax + ebx*4+0x4]
            mov ecx, [ebp + 0x8]
            xor edx, edx
            mov  dl, [ecx + 0x5]
            imul edx, 0x60
            mov  eax, [ebp - 0x6C]
            lea ecx, [eax + edx + 0x128C]
            xor eax, eax
            mov ax, [ecx + 0xA]
            pop ecx
            pop edx
            cmp eax, ebx
            jnz JumOut
            xor eax, eax
            mov al, [edx + 0x24 + ecx + 0x4]
            add eax, 0x10
            mov[edx + 0x24 + ecx + 0x4], al
            xor eax, eax
            mov ax, [edx + 0x24 + ecx + 0x2]
            xor ebx,ebx
            mov bx, [edx + 0x24 + ecx]
            cmp ebx,0x17
            jnz NotCrit
            add eax, 0x64
            jmp EndCheckCrit
            NotCrit:
            add eax, 0x1
            EndCheckCrit:
            mov[edx + 0x24 + ecx + 0x2], ax
            jmp DefaultIncRelics

            DefaultIncRelics :
        mov edx, [ebp - 0x50]
            mov cl, [edx + 0xF]
            sbb cl, 0x1
            mov[edx + 0xF], cl
            cmp cl, 0x0
            jnz KoBangKhong321
            mov ecx, [ebp + 0x8]
            mov cl, [ecx + 0x5]
            push ecx
            mov ecx, [ebp - 0x6C]
            mov eax, 0x004B2960
            call eax
            KoBangKhong321 :
            xor edx, edx
            mov byte ptr[ebp - 0x30], 0x01
                mov edx, [ebp - 0x6C]
                mov eax, [ebp + 0x08]
                mov cl, [eax + 0x04]
                mov[edx + 0x0000531A], cl
                mov edx, [ebp - 0x6C]
                mov eax, [ebp + 0x08]
                mov cl, [eax + 0x05]
                mov[edx + 0x0000531B], cl
                xor edx, edx
            popad
            push 0x0052263F
            ret
            JumOut :


        popad
            mov     edx, [ecx + 0x5320]
            push 0x00522009
            ret

            NotRequest :
        push 0x00415D5D
            ret

            WeaponUpgrade:
            mov     ecx, [ebp + 0x8]
            xor edx, edx
            mov     dl, [ecx + 0x5]
            imul    edx, 0x60
            mov     eax, [ebp - 0x6C]
            lea ecx, [eax + edx + 0x128C]
            mov[ebp - 0x50], ecx
            mov ax, [ecx + 0xA]
            cmp ax, 0x2F6
            jl JumOut
            cmp ax, 0x2FF
            jg ItemRs2122
            xor eax, eax
            lea eax, ListDa31
            jmp MainFun1

            ItemRs2122 :
        cmp ax, 0x309
            jg ItemRs3111
            xor eax, eax
            lea eax, ListDa32
            jmp MainFun1

            ItemRs3111 :
        cmp ax, 0x313
            jg ItemRs41
            xor eax, eax
            lea eax, ListDa33
            jmp MainFun1

            ItemRs41 :
        cmp ax, 0x31D
            jg ItemRs51
            xor eax, eax
            lea eax, ListDa34
            jmp MainFun1

            ItemRs51 :
        cmp ax, 0x327
            jg ItemRs61
            xor eax, eax
            lea eax, ListDa35
            jmp MainFun1

            ItemRs61 :
        cmp ax, 0x331
            jg ItemRs71
            xor eax, eax
            lea eax, ListDa1
            jmp MainFun1

            ItemRs71 :
        cmp ax, 0x33B
            jg ItemRs81
            xor eax, eax
            lea eax, ListDa2
            jmp MainFun1

            ItemRs81 :
        cmp ax, 0x345
            jg ItemRs91
            xor eax, eax
            lea eax, ListDa3
            jmp MainFun1

            ItemRs91 :
        cmp ax, 0x34F
            jg ItemRs101
            xor eax, eax
            lea eax, ListDa4
            jmp MainFun1

            ItemRs101 :
        cmp ax, 0x359
            jg ItemRs111
            xor eax, eax
            lea eax, ListDa5
            jmp MainFun1

            ItemRs111 :
        cmp ax, 0x363
            jg ItemRs121
            xor eax, eax
            lea eax, ListDa6
            jmp MainFun1

            ItemRs121 :
        cmp ax, 0x36D
            jg ItemRs131
            xor eax, eax
            lea eax, ListDa7
            jmp MainFun1

            ItemRs131 :
        cmp ax, 0x377
            jg ItemRs141
            xor eax, eax
            lea eax, ListDa8
            jmp MainFun1

            ItemRs141 :
        cmp ax, 0x381
            jg ItemRs151
            xor eax, eax
            lea eax, ListDa9
            jmp MainFun1

            ItemRs151 :
        cmp ax, 0x38B
            jg ItemRs161
            xor eax, eax
            lea eax, ListDa10
            jmp MainFun1

            ItemRs161 :
        cmp ax, 0x395
            jg ItemRs171
            xor eax, eax
            lea eax, ListDa11
            jmp MainFun1

            ItemRs171 :
        cmp ax, 0x39F
            jg ItemRs181
            xor eax, eax
            lea eax, ListDa12
            jmp MainFun1

            ItemRs181 :
        cmp ax, 0x3A9
            jg ItemRs191
            xor eax, eax
            lea eax, ListDa13
            jmp MainFun1

            ItemRs191 :
        cmp ax, 0x3B3
            jg ItemRs201
            xor eax, eax
            lea eax, ListDa14
            jmp MainFun1

            ItemRs201 :
        cmp ax, 0x3BD
            jg ItemRs211
            xor eax, eax
            lea eax, ListDa15
            jmp MainFun1

            ItemRs211 :
        cmp ax, 0x3C7
            jg ItemRs221
            xor eax, eax
            lea eax, ListDa16
            jmp MainFun1

            ItemRs221 :
        cmp ax, 0x3D1
            jg ItemRs231
            xor eax, eax
            lea eax, ListDa17
            jmp MainFun1

            ItemRs231 :
        cmp ax, 0x3DB
            jg ItemRs241
            xor eax, eax
            lea eax, ListDa18
            jmp MainFun1

            ItemRs241 :
        cmp ax, 0x3E5
            jg ItemRs251
            xor eax, eax
            lea eax, ListDa19
            jmp MainFun1

            ItemRs251 :
        cmp ax, 0x3EF
            jg ItemRs261
            xor eax, eax
            lea eax, ListDa20
            jmp MainFun1

            ItemRs261 :
        cmp ax, 0x3F9
            jg ItemRs271
            xor eax, eax
            lea eax, ListDa21
            jmp MainFun1

            ItemRs271 :
        cmp ax, 0x403
            jg ItemRs281
            xor eax, eax
            lea eax, ListDa22
            jmp MainFun1

            ItemRs281 :
        cmp ax, 0x40D
            jg ItemRs291
            xor eax, eax
            lea eax, ListDa23
            jmp MainFun1

            ItemRs291 :
        cmp ax, 0x417
            jg ItemRs301
            xor eax, eax
            lea eax, ListDa24
            jmp MainFun1

            ItemRs301 :
        cmp ax, 0x421
            jg ItemRs311
            xor eax, eax
            lea eax, ListDa25
            jmp MainFun1

            ItemRs311 :
        cmp ax, 0x42B
            jg ItemRs321
            xor eax, eax
            lea eax, ListDa26
            jmp MainFun1


            ItemRs321 :
        cmp ax, 0x435
            jg ItemRs331
            xor eax, eax
            lea eax, ListDa27
            jmp MainFun1


            ItemRs331 :
        cmp ax, 0x43F
            jg ItemRs341
            xor eax, eax
            lea eax, ListDa28
            jmp MainFun1

            ItemRs341 :
        cmp ax, 0x449
            jg ItemRs351
            xor eax, eax
            lea eax, ListDa29
            jmp MainFun1

            ItemRs351 :
        cmp ax, 0x453
            jg JumOut
            xor eax, eax
            lea eax, ListDa30
            jmp MainFun1



        MainFun1:
        push eax
            mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            imul eax, eax, 0x60
            mov ecx, [ebp - 0x6C]
            lea edx, [ecx + eax + 0x0000128C]
            xor ecx, ecx
            BackloopCheckValue1 :
        pop eax
            push eax
            xor ebx, ebx
            mov bx, [edx + 0x24 + ecx]
            mov eax, [eax]
            cmp eax, ebx
            jz InctValue1
            add ecx, 0x5
            cmp ecx, 0x1E
            jz JumOut3211
            jmp BackloopCheckValue1

            JumOut3211 :
        pop eax
            jmp JumOut

            InctValue1 :
        xor ebx, ebx
            mov bl, [edx + 0x24 + ecx + 0x4]
            pop eax
            push edx
            push ecx
            cmp ebx,0x10
            jge Uprade2
            mov ebx,0x00
            jmp CompleteCheck
            Uprade2:
            cmp ebx, 0x20
            jge Uprade3
                mov ebx, 0x01
                jmp CompleteCheck
                Uprade3 :
            cmp ebx, 0x30
                jge Uprade4
                mov ebx, 0x02
                jmp CompleteCheck

                Uprade4 :
            cmp ebx, 0x40
                jge Uprade5
                mov ebx, 0x03
                jmp CompleteCheck

                Uprade5 :
            cmp ebx, 0x50
                jge Uprade6
                mov ebx, 0x04
                jmp CompleteCheck

                Uprade6 :
            cmp ebx, 0x60
                jge Uprade7
                mov ebx, 0x05
                jmp CompleteCheck

                Uprade7 :
            cmp ebx, 0x70
                jge Uprade8
                mov ebx, 0x06
                jmp CompleteCheck

                Uprade8 :
            cmp ebx, 0x80
                jge Uprade9
                mov ebx, 0x07
                jmp CompleteCheck

                Uprade9 :
            cmp ebx, 0x90
                jge Uprade10
                mov ebx, 0x08
                jmp CompleteCheck

                Uprade10 :
            cmp ebx, 0xA0
                jge JumOut
                mov ebx, 0x09
                jmp CompleteCheck


                CompleteCheck:
            xor ecx,ecx
            mov ecx, [eax + ebx * 4 + 0x4]
            mov ebx,ecx
            mov ecx, [ebp + 0x8]
            xor edx, edx
            mov  dl, [ecx + 0x5]
            imul edx, 0x60
            mov  eax, [ebp - 0x6C]
            lea ecx, [eax + edx + 0x128C]
            xor eax, eax
            mov ax, [ecx + 0xA]
            pop ecx
            pop edx
            cmp eax, ebx
            jnz JumOut
            xor eax, eax
            mov al, [edx + 0x24 + ecx + 0x4]
            add eax, 0x10
            mov[edx + 0x24 + ecx + 0x4], al
            xor eax, eax
            mov ax, [edx + 0x24 + ecx + 0x2]
            xor ebx,ebx
            mov bx, [edx + 0x24 + ecx]
            cmp ebx,0x17
            jnz NotCritWp
            add eax,0x64
            jmp EndNotCritWp
            NotCritWp:
            add eax, 0x1
            EndNotCritWp:
            mov[edx + 0x24 + ecx + 0x2], ax
            jmp DefaultIncRelics1

            DefaultIncRelics1 :
        mov edx, [ebp - 0x50]
            mov cl, [edx + 0xF]
            sbb cl, 0x1
            mov[edx + 0xF], cl
            cmp cl, 0x0
            jnz KoBangKhong3211
            mov ecx, [ebp + 0x8]
            mov cl, [ecx + 0x5]
            push ecx
            mov ecx, [ebp - 0x6C]
            mov eax, 0x004B2960
            call eax
            KoBangKhong3211 :
        xor edx, edx
            mov byte ptr[ebp - 0x30], 0x01
            mov edx, [ebp - 0x6C]
            mov eax, [ebp + 0x08]
            mov cl, [eax + 0x04]
            mov[edx + 0x0000531A], cl
            mov edx, [ebp - 0x6C]
            mov eax, [ebp + 0x08]
            mov cl, [eax + 0x05]
            mov[edx + 0x0000531B], cl
            xor edx, edx
            popad
            push 0x0052263F
            ret

            AddSlotForRelic:
            mov ax, [ecx + 0xA]
            cmp eax,0x76D
            jnz CheckItemType2
            push eax
            call FuncAddSlotForRelic
                jmp DefaultIncRelics1
            CheckItemType2:
            cmp eax, 0x769
            jnz CheckItemType3
            push eax
            call FuncAddSlotForRelic
                jmp DefaultIncRelics1
            CheckItemType3 :
            cmp eax, 0x76A
            jnz BackAddSlotForRelicCurrent
            push eax
            call FuncAddSlotForRelic
            jmp DefaultIncRelics1

            FuncAddSlotForRelic:
            mov ecx, [ebp + 0x8]
            xor edx, edx
            mov  dl, [ecx + 0x4]
            imul edx, 0x60
            mov  eax, [ebp - 0x6C]
            lea ecx, [eax + edx + 0x128C]
            xor eax, eax
            mov al, [ecx + 0x8]
            cmp eax, 0x9
            jnz JumOut
            xor eax, eax
                mov ecx, [ebp + 0x8]
                xor edx, edx
                mov  dl, [ecx + 0x4]
                imul edx, 0x60
                mov  ecx, [ebp - 0x6C]
                lea edx,[edx+ecx+0x128C]
                xor ecx,ecx
            BackCheckForAddNewValueo:
            mov al, [edx + 0x24 + 0x4+ ecx]
            test eax,eax
            jz AddNewValue22ss
            add ecx,0x5
            cmp ecx,0x1E
            jnz BackCheckForAddNewValueo
            AddNewValue22ss:
            cmp ecx,0x14
            jge AddSlot5Relic
            mov eax,[esp+0x4]
            cmp eax,0x76D
            jnz EndCheckAdd
            mov[edx + 0x24 + 0x4 + ecx], 0x1
            jmp EndCheckAdd
            AddSlot5Relic:
            cmp ecx, 0x19
            jge AddSlot6Relic
                mov eax, [esp + 0x4]
                cmp eax, 0x769
                jnz EndCheckAdd
                mov[edx + 0x24 + 0x4 + ecx], 0x1
                jmp EndCheckAdd
            AddSlot6Relic:
            cmp ecx, 0x19
                jnz EndCheckAdd
                mov eax, [esp + 0x4]
                cmp eax, 0x76A
                jnz EndCheckAdd
                mov[edx + 0x24 + 0x4 + ecx], 0x1
                jmp EndCheckAdd
            EndCheckAdd:
            ret 0x4

                GetTwoValue :
            cmp ebx, 0x10
                jge Uprade232
                mov ebx, 0x00
                ret
                Uprade232 :
            cmp ebx, 0x20
                jge Uprade3fd
                mov ebx, 0x01
                ret
                Uprade3fd :
            cmp ebx, 0x30
                jge Uprade4fd
                mov ebx, 0x02
                ret

                Uprade4fd :
            cmp ebx, 0x40
                jge Uprade5fd
                mov ebx, 0x03
                ret

                Uprade5fd :
            cmp ebx, 0x50
                jge Uprade6fd
                mov ebx, 0x04
                ret

                Uprade6fd :
            cmp ebx, 0x60
                jge Uprade7fd
                mov ebx, 0x05
                ret

                Uprade7fd :
            cmp ebx, 0x70
                jge Uprade8fd
                mov ebx, 0x06
                ret

                Uprade8fd :
            cmp ebx, 0x80
                jge Uprade9fd
                mov ebx, 0x07
                ret
                Uprade9fd :
            cmp ebx, 0x90
                jge Uprade10fd
                mov ebx, 0x08
                ret

                Uprade10fd :
            cmp ebx, 0xA0
                jge Uprade11fd
                mov ebx, 0x9
                ret

                Uprade11fd :
                mov ebx, 0xA
                ret
        
    }

}

void __declspec(naked)TestMovePet()
{
    __asm
    {
        pushad
        //
        xor eax, eax
        mov ecx, [ebp - 0x28]
        mov eax, [ecx + 0x10A4]
        test eax,eax
        jz DefaultRun
        /*mov byte ptr[eax + 0x204], 0xEE
        mov byte ptr[eax + 0x208], 0xEE
        mov ecx, [ebp - 0x28]
        xor eax, eax
        mov ax, [ecx + 0xE72]
        push eax
        mov ecx, [ecx + 0x10A4]
        mov eax,0x0059BD10
        call eax*/
       
        mov byte ptr [eax + 0x30], 0xFF
        //1
        /*mov ecx, [ebp - 0x28]
        mov edx,[ecx+0x5BC8]
        mov [eax+0x1C8+0xC],edx
        mov[eax + 0x1F], edx
        //2
        mov edx, [ecx + 0x5BC8+0x4]
        mov[eax + 0x1C8+0x10], edx
        mov[eax + 0x23], edx
        //3
        mov edx, [ecx + 0x5BC8+0x8]
        mov[eax + 0x1C8+0x4], edx
        mov[eax + 0x27], edx
        //4
        mov edx, [ecx + 0x5BC8+0xC]
        mov[eax + 0x1C8+0x8], edx
        mov[eax + 0x2B], edx
        //mov[eax + 0x30], 0xFF
        mov[eax + 0x2F], 0x64 */

        //mov eax,[ebp-0x32]
        //push eax
        /*mov dword ptr [ebp-0x32],0x40000000

        //Get X
        mov ecx, [ebp - 0x28]
        mov eax, 0x00431F70
        call eax
        push ecx
        fsub [ebp-0x32]
        fstp dword ptr[esp]
        pop edx
        mov ecx, [ebp - 0x28]
        mov eax, [ecx + 0x10A4]
        mov [eax+0x1C8+0xC], edx
        //Get Y
        mov ecx, [ebp - 0x28]
        mov eax, 0x00431F90
        call eax
        push ecx
        fsub[ebp - 0x32]
        fstp dword ptr[esp]
        pop edx
        mov ecx, [ebp - 0x28]
        mov eax, [ecx + 0x10A4]
        mov[eax + 0x1C8 + 0x10], edx*/
        mov ecx, [ebp - 0x28]
        xor eax, eax
        mov ax, [ecx + 0xE72]
        push eax
        mov ecx, [ecx + 0x10A4]
        mov eax, 0x0059BD10
        call eax
       /* //Get Next X
        mov ecx, [ebp - 0x28]
        mov eax, 0x005F31D0
        call eax
        push ecx
        fsub[ebp - 0x32]
        fstp dword ptr[esp]
        pop edx
        mov ecx, [ebp - 0x28]
        mov eax, [ecx + 0x10A4]
        mov[eax + 0x1C8 + 0x4], edx
        mov[eax + 0x27], edx
        //Get Next Y
        mov ecx, [ebp - 0x28]
        mov eax, 0x005F31F0
        call eax
        push ecx
        fsub[ebp - 0x32]
        fstp dword ptr[esp]
        pop edx
        mov ecx, [ebp - 0x28]
        mov eax, [ecx + 0x10A4]
        mov[eax + 0x1C8 + 0x8], edx
        mov[eax + 0x2B], edx
        mov[eax + 0x30],0xFF
        mov[eax + 0x2F], 0x64


        //Run Mod

        mov ecx, [ebp - 0x28]
        mov eax, [ecx + 0x10A4]
        mov eax,[eax+0xB4]
        push eax
        mov ecx, [ebp - 0x28]
        mov eax, [ecx + 0x10A4]
        mov eax,[eax+0x208]
        push eax
        mov ecx, [ebp - 0x28]
        mov ecx,[ecx+0x10A4]
        add ecx,0x1C8
        mov eax,0x005A0FA0
        call eax
        push eax
            mov ecx, [ebp - 0x28]
        mov edx,[ecx+0x10A4]
        mov ax,[edx+0x18]
        and ax,0x7FFF
        and eax,0xFFFF
        push eax
        mov ecx, [ebp - 0x28]
        mov ecx, [ecx + 0x10A4]
        add ecx,0x18
        push ecx
        mov ecx, 0x007763AC
        mov ecx,[ecx]
        mov eax,0x0060342E
        call eax
        push 0x0
            mov ecx, [ebp - 0x28]
        mov edx, [ecx + 0x10A4]
        push edx
        push 0x0
        push 0x20
        push 0x7
        mov eax,0x00406B20
        call eax
        mov ecx,eax
        mov eax,0x0040AE50
        call eax*/


        //

        DefaultRun:
        


        //
        popad
            mov ecx, [ebp - 0x28]
            mov     edx, [ebp + 0x8]
        push 0x0048E718
        ret
    }
}
void __declspec(naked)DisableMovePet()//005A0D14
{
    __asm
    {
        mov[ebp - 0x4], ecx
        xor eax,eax
        mov ax,[ecx-0xC8]
        cmp eax,0x00
        jz NotFoundUserID
        push eax
        mov ecx, 0x007763AC
        mov ecx,[ecx]
        mov eax,0x00607FB4
        call eax
        test eax,eax
        jz NotFoundUserID
        mov eax,[eax+0x10A4]
        cmp eax,ecx
        jz NotMove
        NotFoundUserID:
        mov eax, [ebp - 0x4]
        push 0x005A0D1A
        ret

        NotMove:
        push 0x005A0D2E
        ret

    }
}
void __declspec(naked)ProcessDeletePet()//005D0F3A
{
    __asm
    {
        mov ecx, [ebp - 0x00000DBC]
        mov ecx,[ecx+0x10A4]
        test ecx,ecx
        jz DefaultNotHavePet
        mov eax,0x00586F11
        call eax
        DefaultNotHavePet:
        lea edx, [ebp - 0x0000D84C]
        push 0x005D0F40
        ret

    }
}
void __declspec(naked)ProcessDeletePet2()//00602093
{
    __asm
    {
        mov eax, [ebp + 0x8]
        mov ecx, [eax + 0x10A4]
        test ecx, ecx
        jz DefaultNotHavePet
        mov eax, 0x00586F11
        call eax
        DefaultNotHavePet :
        mov eax, [ebp + 0x8]
            xor ecx, ecx
            push 0x00602098
            ret

    }
}
void __declspec(naked)ProcessDeletePet3()//00602613
{
    __asm
    {
        mov eax, [ebp + 0x8]
        mov ecx, [eax + 0x10A4]
        test ecx, ecx
        jz DefaultNotHavePet
        mov eax, 0x00586F11
        call eax
        DefaultNotHavePet :
        mov eax, [ebp + 0x8]
            xor ecx, ecx
            push 0x00602618
            ret

    }
}
void __declspec(naked)DisableMovePet1()//00406A34
{
    __asm
    {
        mov[ebp - 0x4], ecx
        xor eax, eax
        mov ax, [ecx - 0xC8]
        cmp eax, 0x00
        jz NotFoundUserID
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x00607FB4
        call eax
        test eax, eax
        jz NotFoundUserID
        mov eax, [eax + 0x10A4]
        cmp eax, ecx
        jz NotMove
        NotFoundUserID :
        mov eax, [ebp - 0x4]
            push 0x00406A3A
            ret

            NotMove :
        push 0x00406A4D
            ret
    }
}
void __declspec(naked)DisableMoveRandomPet()//0059020F
{
    __asm
    {
        pushad
        mov ecx,[ebp-0x94]
        mov eax, [ecx + 0x100]
        test eax,eax
        jz DefaultRun
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x00607FB4
        call eax
        test eax,eax
        jz DefaultRun
        mov eax, [eax + 0x10A4]
        mov ecx, [ebp - 0x94]
        cmp eax, ecx
        jz NotMove
        DefaultRun:
        popad
        and eax, 0xFF
        test eax, eax
        push 0x00590216
        ret

        NotMove :
        popad
        push 0x00591073
        ret

    }
}
void __declspec(naked)ByPassCheckRun()//0059C084
{
    __asm
    {
        pushad
        mov ecx, [ebp - 0x1C]
        mov ecx,[ecx+0x10A4]
        mov eax, [ebp - 0x000000A8]
        cmp eax,ecx
        jz JmpBypass
        popad
        mov ecx, [ebp - 0x000000A8]
        push 0x0059C08A
        ret

        JmpBypass:
        popad
        push 0x0059D2E8
        ret

    }
}
void __declspec(naked)ByPassCheckRun42()//0059D79E
{
    __asm
    {
        pushad
        mov ecx, [ebp - 0x1C]
        mov ecx, [ecx + 0x10A4]
        mov eax, [ebp - 0x000000A8]
        cmp eax, ecx
        jz JmpBypass
        popad
        cmp dword ptr[ebp - 0xA0], 0x5
        push 0x0059D7A5
        ret

        JmpBypass :
        popad
            mov dword ptr [ebp-0xA0],0x300
            push 0x0059D924
            ret

    }
}
void __declspec(naked)ByPassCheckRunNext1()//0059D718
{
    __asm
    {
        pushad
        mov ecx, [ebp - 0x1C]
        mov ecx, [ecx + 0x10A4]
        mov eax, [ebp - 0x000000A8]
        cmp eax, ecx
        jz JmpBypass
        popad
        lea     ecx, [ebp - 0x9C]
        push 0x0059D71E
        ret

        JmpBypass :
            mov ecx, [ebp - 0x1C]
            mov edx, [ecx + 0x5BC8 + 0x8]
            mov ecx, [ebp - 0x000000A8]
            add ecx, 0x1C8
            mov[ecx+0x4], edx
            lea ecx, [ebp - 0x9C]
            mov[ecx], edx
            //2
            mov ecx, [ebp - 0x1C]
            mov edx, [ecx + 0x5BC8 + 0xC]
            mov ecx, [ebp - 0x000000A8]
            add ecx,0x1C8
            mov[ecx + 0x8], edx
            lea ecx, [ebp - 0x9C]
            mov [ecx+0x4],edx
            popad
            push 0x0059D730
            ret

       /* pushad
        mov eax, [ebp - 0x4]
        xor ecx,ecx
        sub eax,0xC8
        mov cx, [eax + 0x100]
        test ecx, ecx
        jmp NotFoundUser
        push ecx
        mov ecx, 0x007763AC
        mov ecx,[ecx]
        mov eax,0x00607FB4
        call eax
        test eax,eax
        jz NotFoundUser
        mov edx,[eax+0x10A4]
        mov edx, [edx + 0x1C8]
        mov ecx, [ebp - 0x4]
        cmp edx, ecx
        jnz NotFoundUser
        popad
        mov edx, [eax + 0x5BC8+0x8]
        mov ecx, [ebp - 0x4]
        mov [ecx], edx
        //2
        mov edx, [eax + 0x5BC8 + 0xC]
        mov ecx, [ebp - 0x4]
        mov[ecx+0x4], edx

        push 0x00406A4D
        ret

        NotFoundUser :
        popad
            mov eax, [ebp - 0x4]
            mov ecx, [ebp + 0x8]
            push 0x00406A3D
            ret*/

    }
}
void __declspec(naked)ByPassCheckRunNext2()//005A0D17
{
    __asm
    {
        pushad
        mov eax, [ebp - 0x4]
        xor ecx, ecx
        sub eax, 0xC8
        mov cx, [eax + 0x100]
        test ecx,ecx
        jmp NotFoundUser
        push ecx
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x00607FB4
        call eax
        test eax, eax
        jz NotFoundUser
        mov edx, [eax + 0x10A4]
        mov edx,[edx+0x1C8]
        mov ecx, [ebp - 0x4]
        cmp edx, ecx
        jnz NotFoundUser
        popad
        mov edx, [eax + 0x5BC8 + 0x8]
        mov ecx, [ebp - 0x4]
        mov[ecx], edx
        //2
        mov edx, [eax + 0x5BC8 + 0xC]
        mov ecx, [ebp - 0x4]
        mov[ecx + 0x4], edx

        push 0x005A0D2E
        ret

        NotFoundUser :
        popad
            mov eax, [ebp - 0x4]
            mov ecx, [ebp + 0x8]
            push 0x005A0D1D
            ret

    }
}
void __declspec(naked)MoveMobNearUser()//0059D5D7
{
    __asm
    {

        mov edx, 0x41a00000
        fld dword ptr[ebp - 0x000000A4]
        mov ecx,[ebp - 0x20]
        mov [ebp-0x20], edx
        fcomp dword ptr[ebp - 0x20]
        fnstsw ax
        test ah, 0x41
        mov [ebp-0x20],ecx
        je MoveMobNearUser22
        DefaultRunSpeed:
        mov ecx, [ebp - 0x000000A8]
        push 0x0059D5DD
        ret

        MoveMobNearUser22 :
        mov ecx, [ebp - 0x1C]
        mov ecx, [ecx + 0x10A4]
        mov eax, [ebp - 0x000000A8]
        cmp eax, ecx
        jz PetOfUser
        jmp DefaultRunSpeed

        PetOfUser:
        mov ecx, [ebp - 0x1C]
        mov edx,[ecx+0x5BC8]
        mov [eax+0x1C8+0xC],edx
        mov edx, [ecx + 0x5BC8+0x4]
        mov[eax + 0x1C8 + 0x10], edx
        jmp DefaultRunSpeed

    }
}
void __declspec(naked)ByPassCheckRun2()//0059D4C0
{
    __asm
    {
        pushad
        mov ecx, [ebp - 0x1C]
        mov ecx, [ecx + 0x10A4]
        mov eax, [ebp - 0x000000A8]
        cmp eax, ecx
        jz JmpBypass
        popad
        mov eax, [ebp - 0x000000A8]
        push 0x0059D4C6
        ret

        JmpBypass :
        popad
            push 0x0059D57F
            ret

    }
}
void __declspec(naked)DisableMoveRandomPet23()//0058146C
{
    __asm
    {
        pushad
        mov ecx, [ebp - 0x0C]
        mov eax, [ecx + 0x100]
        test eax, eax
        jz DefaultRun
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x00607FB4
        call eax
        test eax, eax
        jz DefaultRun
        mov eax, [eax + 0x10A4]
        cmp eax, ecx
        jz NotMove
        DefaultRun :
        popad
            and eax, 0xFF
            test eax, eax
            push 0x00581473
            ret

            NotMove :
        popad
            push 0x00581475
            ret

    }
}
DWORD StoreVaule = 0x0;
DWORD StoreVaule1 = 0x0;
DWORD StoreVaule2 = 0x0;
DWORD StoreVaule3 = 0x0;
DWORD StoreAdrItem = 0x0;
DWORD StoreSlotItem = 0x0;
int ramdnumber = 0;
int spawmBoss = 0;
int boss = 0;
void __declspec(naked)UseItemSpawn()
{
    __asm
    {

        mov[ebp - 0x0000F160], eax
        pushad
        mov eax, [eax + 0x3]
        mov StoreSlotItem, eax
        imul eax, eax, 0x60
        mov ecx, [ebp - 0xDBC]
        lea edx, [ecx + eax + 0x0000128C]
        mov StoreAdrItem, edx
        mov dx, [edx + 0xA]
        cmp dx, 0xD6D
        jnz Check2
        mov edx, StoreAdrItem
        mov cl, [edx + 0xF]
        sub cl, 0x1
        mov[edx + 0xF], cl
        cmp cl, 0x0
        jnz KoBangKhong1
        mov ecx, StoreSlotItem
        push ecx
        mov ecx, [ebp - 0xDBC]
        mov eax, 0x004B2960
        call eax
        KoBangKhong1 :
    }
    srand((int)time(0));
    ramdnumber = rand() % 100 + 1;
    if (ramdnumber >= 0 && ramdnumber <= 90)
    {
        srand((int)time(0));
        spawmBoss = 0;
        spawmBoss = rand() % 6 + 1;
        if (spawmBoss == 1)
        {
            __asm mov boss, 0x1CE0;
        }
        else if (spawmBoss == 2)
        {
            __asm mov boss, 0x1CE1;
        }
        else if (spawmBoss == 3)
        {
            __asm mov boss, 0x1CE2;
        }
        else if (spawmBoss == 4)
        {
            __asm mov boss, 0x1CE3;
        }
        else if (spawmBoss == 5)
        {
            __asm mov boss, 0x1CE4;
        }
        else if (spawmBoss == 6)
        {
            __asm mov boss, 0x1CE5;
        }

    }
    else
    {
        __asm mov boss, 0x1CE6
    }
    ramdnumber = 0;
    __asm
    {
        // mov boss, 0x1C83; //Zplay
        mov  ecx, [ebp - 0xDBC]
        mov eax, 0x00431F70
        call eax
        push ecx
        fstp dword ptr[esp]
        pop ecx
        mov[ebp - 0x0F164], ecx
        mov  ecx, [ebp - 0xDBC]
        mov eax, 0x00431F90
        call eax
        push ecx
        fstp dword ptr[esp]
        pop ecx
        mov[ebp - 0x0F160], ecx
        push 0x0
        push 0x0
        push 0x0
        lea edx, [ebp - 0xF164]
        push edx
        push 0x0
        push boss
        mov boss, 0x00000000
        mov eax, 0x00406B10
        call eax
        mov ecx, eax
        mov eax, 0x005BB34D
        call eax
        mov cx, ax
        push ecx
        mov eax, 0x00406B10
        call eax
        mov ecx, eax
        mov eax, 0x0005BBB29
        call eax
        mov byte ptr[ebp - 0xF170], 0x06
        mov byte ptr[ebp - 0xF16F], 0x00
        mov byte ptr[ebp - 0xF16E], 0x7A
        mov ecx, StoreSlotItem
        mov word ptr[ebp - 0xF16D], 0x01
        mov word ptr[ebp - 0xF16C], cx
        mov eax, StoreAdrItem
        mov al, [eax + 0xF]
        mov byte ptr[ebp - 0xF16B], al
        mov eax, 0x00000000
        mov ax, [ebp - 0xF170]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push    6
        lea     edx, [ebp - 0xF170]
        push    edx
        mov  ecx, [ebp - 0xDBC]
        mov eax, 0x69479A
        call eax
		popad
        push 0x005E79D6
        ret

        Check2 :
        cmp dx, 0xD6B
            jnz Check3
            mov  ecx, [ebp - 0xDBC]
            mov cx, [ecx + 0x5C54]
            cmp cx, 0x96
            jge Default1
            mov  ecx, [ebp - 0xDBC]
            mov word ptr[ecx + 0x5C54], 0x96
            mov ecx, dword ptr[ebp - 0xF170]
            mov StoreVaule1, ecx
            mov ecx, dword ptr[ebp - 0xF16C]
            mov StoreVaule2, ecx
            mov ecx, dword ptr[ebp - 0xF168]
            mov StoreVaule3, ecx
            mov byte ptr[ebp - 0xF170], 0x0A
            mov byte ptr[ebp - 0xF16F], 0x00
            mov byte ptr[ebp - 0xF16E], 0x6A
            mov word ptr[ebp - 0xF16D], 0x96
            mov  ecx, [ebp - 0xDBC]
            mov eax, 0x00616150
            call eax
            mov word ptr[ebp - 0xF16B], ax
            mov  ecx, [ebp - 0xDBC]
            mov eax, 0x00616170
            call eax
            mov word ptr[ebp - 0xF169], ax
            mov byte ptr[ebp - 0xF167], 0x01
            mov ax, [ebp - 0xF170]
            and ax, 0x7FFF
            and eax, 0xFFFF
            push    eax
            lea     edx, [ebp - 0xF170]
            push    edx
            mov  ecx, [ebp - 0xDBC]
            mov eax, 0x69479A
            call eax
            mov ecx, StoreVaule1
            mov  dword ptr[ebp - 0xF170], ecx
            mov ecx, StoreVaule2
            mov dword ptr[ebp - 0xF16C], ecx
            mov ecx, StoreVaule3
            mov dword ptr[ebp - 0xF168], ecx
            jmp Default1
            /* mov ecx, dword ptr[ebp - 0xF170]
             mov StoreVaule1, ecx
             mov ecx, dword ptr[ebp - 0xF16C]
             mov StoreVaule2, ecx
             mov ecx, dword ptr[ebp - 0xF168]
             mov StoreVaule3, ecx
             mov byte ptr[ebp - 0xF170], 0x0A
             mov byte ptr[ebp - 0xF16F], 0x00
             mov byte ptr[ebp - 0xF16E], 0x6A
             mov word ptr[ebp - 0xF16D], 0x64
             mov  ecx, [ebp - 0xDBC]
             mov eax, 0x00616150
             call eax
             mov word ptr[ebp - 0xF16B], ax
             mov  ecx, [ebp - 0xDBC]
             mov eax, 0x00616170
             call eax
             mov word ptr[ebp - 0xF169], ax
             mov byte ptr[ebp - 0xF168], 0x01
             mov al, [ebp - 0xF164]
             and cx, 0x7FFF
             and ecx, 0xFFFF
             push    ecx
             lea     edx, [ebp - 0xF170]
             push    edx
             mov  ecx, [ebp - 0xDBC]
             mov eax, 0x69479A
             call eax
             mov ecx, StoreVaule1
             mov  dword ptr[ebp - 0xF170], ecx
             mov ecx, StoreVaule2
             mov dword ptr[ebp - 0xF16C], ecx
             mov ecx, StoreVaule3
             mov dword ptr[ebp - 0xF168], ecx*/
        Check3:
        cmp dx, 0xD6C
            jnz Default1
            mov  ecx, [ebp - 0xDBC]
            mov cx, [ecx + 0x5C54]
            cmp cx, 0xBE
            jge Default1
            mov  ecx, [ebp - 0xDBC]
            mov word ptr[ecx + 0x5C54], 0xBE
            mov ecx, dword ptr[ebp - 0xF170]
            mov StoreVaule1, ecx
            mov ecx, dword ptr[ebp - 0xF16C]
            mov StoreVaule2, ecx
            mov ecx, dword ptr[ebp - 0xF168]
            mov StoreVaule3, ecx
            mov byte ptr[ebp - 0xF170], 0x0A
            mov byte ptr[ebp - 0xF16F], 0x00
            mov byte ptr[ebp - 0xF16E], 0x6A
            mov word ptr[ebp - 0xF16D], 0xBE
            mov  ecx, [ebp - 0xDBC]
            mov eax, 0x00616150
            call eax
            mov word ptr[ebp - 0xF16B], ax
            mov  ecx, [ebp - 0xDBC]
            mov eax, 0x00616170
            call eax
            mov word ptr[ebp - 0xF169], ax
            mov byte ptr[ebp - 0xF167], 0x01
            mov ax, [ebp - 0xF170]
            and ax, 0x7FFF
            and eax, 0x0000FFFF
            push    eax
            lea     edx, [ebp - 0xF170]
            push    edx
            mov  ecx, [ebp - 0xDBC]
            mov eax, 0x69479A
            call eax
            mov ecx, StoreVaule1
            mov  dword ptr[ebp - 0xF170], ecx
            mov ecx, StoreVaule2
            mov dword ptr[ebp - 0xF16C], ecx
            mov ecx, StoreVaule3
            mov dword ptr[ebp - 0xF168], ecx
            jmp Default1
            //Inchant Cloth
            //
            Default1 :
        popad
            mov dword ptr[ebp - 0xF160], eax
            mov dword ptr[ebp - 0xF164], 0
            push 0x005E75C6
            ret
    }
}
void __declspec(naked)FixResetWeapon()
{
    __asm
    {
        mov al, [edx + eax + 0x12AF]
        cmp al, 0x01
        jnz Defalt
        mov eax, [ebp + 0xC]
        and eax, 0x000000FF
        imul eax, eax, 0x60
        mov[edx + eax + 0x12AF], 0x00
        push 0x004A2688
        ret
        Defalt :
        push 0x004A266E
            ret
    }
}

void __declspec(naked)UpdateEffectInc()
{
    __asm
    {
        pushad
        mov StorePacket, eax
        xor ecx, ecx
        mov eax, [ebp - 0x8074]
        LoopLoad:
        push ecx
            imul ecx, ecx, 0x60
            lea edx, [eax + ecx + 0x0000128C]
            mov bl, [edx + 0x18]
            cmp bl, 0x7
            jl Default
            sub bl, 0x5
            mov eax, StorePacket
            pop ecx
            mov[eax + 0x1C + ecx], bl
            add ecx, 0x1
            cmp ecx, 0x5
            jz Default
            jmp LoopLoad

            Default :
        popad
            push 0x004A266E
            ret
    }
}
void __declspec(naked)FixMaxCritMob()
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        cmp eax, 0x1
        push 0x00594364
        ret
    }
}
void __declspec(naked)FixMaxCritMob2()
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        xor ecx, ecx
        push 0x00594384
        ret
    }
}
void __declspec(naked)FixMaxCritNuker()
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        cmp eax, 0x1
        push 0x005943A2
        ret
    }
}
void __declspec(naked)FixMaxCritNuker3() //005943ED
{
    __asm
    {
        xor edx, edx
        mov dx, [ebp + 0x8]
        cmp edx, 0x1
        push 0x005943AB
        ret
    }
}
void __declspec(naked)FixMaxCritNuker4() //00594437
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        cmp eax, 0x1
        push 0x0059443E
        ret
    }
}
void __declspec(naked)FixMaxCritNuker5() //00594475
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        cmp eax, 0x1
        push 0x0059443E
        ret
    }
}
void __declspec(naked)FixMaxCritNuker31() //0059440E
{
    __asm
    {
        xor edx, edx
        mov dx, [ebp + 0x8]
        xor eax,eax
        push 0x00594414
        ret
    }
}
void __declspec(naked)FixMaxCritNuker41() //00594458
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        xor ecx, ecx
        push 0x0059445E
        ret
    }
}
void __declspec(naked)FixMaxCritNuker51() //00594496
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        xor ecx, ecx
        push 0x0059449C
        ret
    }
}
void __declspec(naked)FixMaxCritNuker2()
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp + 0x8]
        xor ecx, ecx
        push 0x005943C2
        ret
    }
}
DWORD checkSlotItem = 0x0;
void __declspec(naked)LockEquipAssesstory()
{
    __asm
    {
        pushad
        mov eax, [ebp - 0x848]
        xor ecx, ecx
        mov cl, [eax + 0xD]
        mov checkSlotItem, ecx
        cmp ecx,0xC
        jl Default1
        cmp ecx,0x13
        jg Default1
            mov eax, [ebp - 0x848]
            xor ecx, ecx
            mov cl, [eax + 0xC]
            imul ecx, ecx, 0x60
            mov eax, [ebp - 0xDBC]
            xor edx, edx
            mov dl, [eax + ecx + 0x128C + 0x9]
            cmp dl, 0x33
            jz GetOut
            jmp Default
            GetOut :
            popad
            push 0x005E1AF0
            ret
            Default :
        Default1:
        popad
        mov eax, [ebp - 0x848]
        push 0x005E185A
        ret
    }
}
DWORD CheckInc = 0x0;
DWORD CheckOption2 = 0x0;
DWORD Type1 = 0x0;
DWORD Type2 = 0x0;
DWORD Type3 = 0x0;
DWORD Option1 = 0x0;
DWORD Option2 = 0x0;
DWORD Option3 = 0x0;
BYTE TypeOtionInc = 0x0;
DWORD CheckTypeItemInc = 0x00;
int i = 0;
int y = 0;
int a = 0;
void __declspec(naked)CheckIncClot()
{
    __asm
    {
        pushad
        mov  edx, [ebp - 0x48]
        xor ecx, ecx
        mov  cl, [edx + 0x18]
        mov CheckInc, ecx
        mov  cl, [edx + 0x8]
        cmp ecx, 0x01
        jnz Default
        mov  cl, [edx + 0x9]
        mov CheckOption2, ecx
        mov eax, [ebp - 0x50]
        mov ax, [eax + 0xA]
        and ax, 0x7FFF
        and eax, 0xFFFF
        mov CheckTypeItemInc, eax

        xor eax, eax
        xor ecx, ecx
        xor edx, edx
    }
    i = 0;
    a = 0;
    y = 0;
    if (CheckTypeItemInc >= 112 && CheckTypeItemInc <= 126)
    {
        for (i; i < 540; i = i + 36)
        {
            if (ListChicong[i] == (CheckInc + 1))
            {
                i = i + 1;
                y = i + y;
                for (a; a <= 4; a++)
                {
                    if (ListChicong[y] == CheckOption2)
                    {
                        Type1 = ListChicong[y + 1];
                        Option1 = ListChicong[y + 2];
                        Type2 = ListChicong[y + 3];
                        Option2 = ListChicong[y + 4];
                        Type3 = ListChicong[y + 5];
                        Option3 = ListChicong[y + 6];
                        TypeOtionInc = 2;

                    }
                    y = y + 7;
                }
            }
        }

    }
    else
    {
        for (i; i < 540; i = i + 36)
        {
            if (ListPhycys[i] == (CheckInc + 1))
            {
                i = i + 1;
                y = i + y;
                for (a; a <= 4; a++)
                {
                    if (ListPhycys[y] == CheckOption2)
                    {
                        Type1 = ListPhycys[y + 1];
                        Option1 = ListPhycys[y + 2];
                        Type2 = ListPhycys[y + 3];
                        Option2 = ListPhycys[y + 4];
                        Type3 = ListPhycys[y + 5];
                        Option3 = ListPhycys[y + 6];
                        TypeOtionInc = 1;
                    }
                    y = y + 7;
                }
            }
        }
    }




    __asm {
        mov  edx, [ebp - 0x48]
        xor ecx, ecx
        mov cl, TypeOtionInc
        mov[edx + 0x23], cl
        xor ecx, ecx
        mov ecx, Type1
        mov[edx + 0x24], cx
        mov ecx, Option1
        mov[edx + 0x26], cx
        mov[edx + 0x28], 0x1
        mov ecx, Type2
        mov[edx + 0x29], cx
        mov ecx, Option2
        mov[edx + 0x2B], cx
        mov[edx + 0x2D], 0x1
        mov ecx, Type3
        mov[edx + 0x2E], cx
        mov ecx, Option3
        mov[edx + 0x30], cx
        //Send Packet

        //

    Default:
        popad
            mov  eax, [ebp - 0x48]
            xor ecx, ecx
            push 0x005222DD
            ret
    }
}
DWORD checkItem = 0x0;
DWORD returnItem = 0x0;
void __declspec(naked)AcceptIntNewItem()
{
    __asm
    {
        movsx ecx, word ptr[ebp + 0xC]
        mov checkItem, ecx
    }
    if (checkItem == 112)
    {
        returnItem = 7;
    }
    else if (checkItem == 113)
    {
        returnItem = 8;
    }
    else if (checkItem == 114)
    {
        returnItem = 9;
    }
    else if (checkItem == 115)
    {
        returnItem = 10;
    }
    else if (checkItem == 116)
    {
        returnItem = 11;
    }
    else if (checkItem == 117)
    {
        returnItem = 12;
    }
    else if (checkItem == 118)
    {
        returnItem = 13;
    }
    else if (checkItem == 119)
    {
        returnItem = 14;
    }
    else if (checkItem == 120)
    {
        returnItem = 15;
    }
    else if (checkItem == 121)
    {
        returnItem = 16;
    }
    else if (checkItem == 122)
    {
        returnItem = 17;
    }
    else if (checkItem == 123)
    {
        returnItem = 18;
    }
    else if (checkItem == 124)
    {
        returnItem = 86;
    }
    else if (checkItem == 125)
    {
        returnItem = 87;
    }
    else if (checkItem == 126)
    {
        returnItem = 88;
    }
    else
    {
        __asm  movsx ecx, word ptr[ebp + 0xC]
            __asm    mov edx, [ebp - 0x4]
            __asm     push 0x0063AFF7
        __asm     ret
    }
    __asm
    {
        mov ecx, returnItem
        mov edx, [ebp - 0x4]
        push 0x0063AFF7
        ret
    }
}

void __declspec(naked)CheckTypeUsed()
{
    __asm
    {
        cmp edx, 0x02
        jz ChangeTime
        mov     ecx, [ebp - 0x4]
        mov     edx, [ebp + 0xC]
        push 0x0052CD63
        ret
        ChangeTime :
        mov ecx, [ebp - 0x4]
            mov     edx, [ebp + 0xC]
            mov[ecx + 0x5B48], edx
            mov     eax, [ebp - 0x4]
            mov     dword ptr[eax + 0x5B4C], 0x7148
            push 0x0052CD76
            ret
    }
}
void __declspec(naked)AcceptType8()
{
    __asm
    {
        mov al, [ecx + 0x0063B2E9]
        cmp al, 0x02
        jnz Default
        mov al, 0x00
        Default:
        push 0x0063B0F2
            ret
    }
}
DWORD AddressItemrequest = 0x00;
BYTE TypeItemReques2t = 0x00;
void __declspec(naked)CheckTypeKcorPh()
{
    __asm
    {
        pushad
        //Get Slot Item Request
        mov     ecx, [ebp + 0x8]
        xor edx, edx
        mov     dl, [ecx + 0x5]
        imul    edx, 0x60
        mov     eax, [ebp - 0x6C]
        lea     ecx, [eax + edx + 0x128C]
        mov AddressItemrequest, ecx
        //Get Slot Item Inc
        mov     ecx, [ebp + 0x8]
        xor edx, edx
        mov     dl, [ecx + 0x4]
        imul    edx, 0x60
        mov     eax, [ebp - 0x6C]
        lea     ecx, [eax + edx + 0x128C]
        mov     dl, [ecx + 0x8]
        cmp     dl, 0x01
        jnz IncWeapon
        mov     dl, [ecx + 0x9]
        cmp     dl, 0x04
        jle NotDecco
        popad
        push 0x00522054
        ret
        NotDecco :
        mov     bl, [ecx + 0x23]
            cmp     bl, 0x00
            jz IncWeapon
            mov     ecx, AddressItemrequest
            xor eax, eax
            mov     al, [ecx + 0xA]
            mov TypeItemReques2t, al
    }
    if (TypeItemReques2t >= 112 && TypeItemReques2t <= 126)
    {
        //Khi Cong
        __asm mov al, 0x2
    }
    else if (TypeItemReques2t >= 7 && TypeItemReques2t <= 88)
    {
        //Physical
        __asm mov al, 0x1
    }
    __asm {
        cmp al, bl
        jz IncWeapon
        popad
        push 0x00522054
        ret

        IncWeapon :
        popad
            add  edx, 0x5DC
            push 0x0052200F
            ret
    }
}
DWORD checkresuld = 0x0;
DWORD CheckIncFailed = 0x0;
DWORD CheckOption2Failed = 0x0;
DWORD Type1Failed = 0x0;
DWORD TypeOtherFailed = 0x0;
DWORD Type2Failed = 0x0;
DWORD Type3Failed = 0x0;
DWORD Option1Failed = 0x0;
DWORD Option2Failed = 0x0;
DWORD Option3Failed = 0x0;
void __declspec(naked)Checkfaild()
{
    __asm
    {
        pushad
        mov[ebp - 0x20], al
        mov checkresuld, eax
        mov  edx, [ebp - 0x48]
        xor ecx, ecx
        mov  cl, [edx + 0x18]
        mov CheckIncFailed, ecx
        mov  cl, [edx + 0x8]
        cmp ecx, 0x01
        jnz Default
        mov  cl, [edx + 0x9]
        mov CheckOption2Failed, ecx
        xor eax, eax
        xor ecx, ecx
        xor edx, edx
    }
    if (CheckIncFailed == 0 || CheckIncFailed == 1)
    {
        __asm
        {

            mov  edx, [ebp - 0x48]
            mov ecx, CheckIncFailed
            mov[edx + 0x18], cl
            xor ecx, ecx
            mov[edx + 0x23], 0x0
            mov word ptr[edx + 0x24], 0x0000
            mov word ptr[edx + 0x26], 0x0000
            mov[edx + 0x28], 0x0
            mov word ptr[edx + 0x29], 0x0000
            mov word ptr[edx + 0x2B], 0x0000
            mov[edx + 0x2D], 0x0
            mov word ptr[edx + 0x2E], 0x0000
            mov word ptr[edx + 0x30], 0x0000
            //
            push    1
            mov     ecx, [ebp - 0x6C]
            mov eax, 0x50F9E2
            call eax
            mov     ecx, [ebp + 0x8]
            sub     eax, [ecx + 0x7]
            push    eax
            mov     ecx, [ebp - 0x6C]
            mov eax, 0x50FA03
            call eax
            //
            mov     edx, [ebp - 0x50]
            xor eax, eax
            mov     al, [edx + 0xF]
            sub     al, [edx + 6]
            mov     ecx, [ebp - 50]
            mov[ecx + 0xF], al
            mov     edx, [ebp - 0x50]
            xor eax, eax
            mov     al, [edx + 0xF]
            test    eax, eax
            jnz ConVatPham1
            mov     ecx, [ebp + 8]
            mov     dl, [ecx + 5]
            push    edx
            mov     ecx, [ebp - 0x6C]
            mov eax, 0x004B2960
            call eax
            ConVatPham1 :
            popad
                push 0x00522639
                ret
        }
    }
    else
    {
        CheckIncFailed--;
        if (CheckOption2Failed == 0)
        {
            Type1Failed = 19;
            Type2Failed = 130;
            Type3Failed = 24;
            Option1Failed = 50 * CheckIncFailed;
            Option2Failed = 200 * CheckIncFailed;
            Option3Failed = 100 * CheckIncFailed;
        }
        else if (CheckOption2Failed == 1)
        {
            Type1Failed = 19;
            Type2Failed = 130;
            Type3Failed = 131;
            Option1Failed = 40 * CheckIncFailed;
            Option2Failed = 100 * CheckIncFailed;
            Option3Failed = 100 * CheckIncFailed;
        }
        else if (CheckOption2Failed == 2)
        {
            Type1Failed = 19;
            Type2Failed = 23;
            Type3Failed = 50;
            Option1Failed = 10 * CheckIncFailed;
            Option2Failed = 100 * CheckIncFailed;
            Option3Failed = 1 * CheckIncFailed;
        }
        else if (CheckOption2Failed == 3)
        {
            Type1Failed = 19;
            Type2Failed = 61;
            Type3Failed = 2;
            Option1Failed = 25 * CheckIncFailed;
            Option2Failed = 1 * CheckIncFailed;
            Option3Failed = 100 * CheckIncFailed;
        }
        else if (CheckOption2Failed == 4)
        {
            Type1Failed = 19;
            Type2Failed = 1;
            Type3Failed = 9;
            Option1Failed = 15 * CheckIncFailed;
            Option2Failed = 50 * CheckIncFailed;
            Option3Failed = 100 * CheckIncFailed;
        }
    }
    __asm {

        mov  edx, [ebp - 0x48]
        mov ecx, CheckIncFailed
        mov[edx + 0x18], cl
        xor ecx, ecx
        mov[edx + 0x23], 0x1
        mov ecx, Type1Failed
        mov[edx + 0x24], cx
        mov ecx, Option1Failed
        mov[edx + 0x26], cx
        mov[edx + 0x28], 0x1
        mov ecx, Type2Failed
        mov[edx + 0x29], cx
        mov ecx, Option2Failed
        mov[edx + 0x2B], cx
        mov[edx + 0x2D], 0x1
        mov ecx, Type3Failed
        mov[edx + 0x2E], cx
        mov ecx, Option3Failed
        mov[edx + 0x30], cx
        //
        push    1
        mov     ecx, [ebp - 0x6C]
        mov eax, 0x50F9E2
        call eax
        mov     ecx, [ebp + 0x8]
        sub     eax, [ecx + 0x7]
        push    eax
        mov     ecx, [ebp - 0x6C]
        mov eax, 0x50FA03
        call eax
        //
        mov     edx, [ebp - 0x50]
        xor eax, eax
        mov     al, [edx + 0xF]
        sub     al, [edx + 6]
        mov     ecx, [ebp - 50]
        mov[ecx + 0xF], al
        mov     edx, [ebp - 0x50]
        xor eax, eax
        mov     al, [edx + 0xF]
        test    eax, eax
        jnz ConVatPham
        mov     ecx, [ebp + 8]
        mov     dl, [ecx + 5]
        push    edx
        mov     ecx, [ebp - 0x6C]
        mov eax, 0x004B2960
        call eax
        ConVatPham :
        popad
            push 0x00522639
            ret

            Default :
        popad
            mov     dl, [ebp - 0x20]
            push 0x005222B2
            ret
    }
}
void __declspec(naked)BlockUsePk()
{
    __asm
    {
        mov eax, [ebp - 0xF160]
        movsx ecx, byte ptr[eax + 0x4]
        pushad
        cmp ecx, 0x03
        jnz Check2
        movsx eax, byte ptr[eax + 0x3]
        imul eax, eax, 0x60
        mov ecx, [ebp - 0xDBC]
        lea edx, [ecx + eax + 0x0000128C]
        mov cl, [edx + 0x8]
        cmp cl, 0x03
        jnz Default1
        mov ecx, 0x00000000
        mov cx, [edx + 0xA]
        cmp cx, 0xBB9
        jnz CheckType2
        popad
        push 0x05E79CE
        ret
        CheckType2 :
        cmp cx, 0xBBA
            jnz Default1
            popad
            push 0x05E79CE
            ret
            Default1 :
        popad
            mov  byte ptr[eax + 0x4], 0x00
            mov ecx, 0x01
            push 0x005E7625
            ret
            Check2 :
        cmp ecx, 0x02
            jnz Default
            movsx eax, byte ptr[eax + 0x3]
            imul eax, eax, 0x60
            mov ecx, [ebp - 0xDBC]
            lea edx, [ecx + eax + 0x0000128C]
            mov cl, [edx + 0x8]
            cmp cl, 0x03
            jnz Default2
            mov ecx, 0x00000000
            mov cx, [edx + 0xA]
            cmp cx, 0xBB9
            jnz CheckType22
            popad
            push 0x05E79CE
            ret
            CheckType22 :
        cmp cx, 0xBBA
            jnz Default2
            popad
            push 0x05E79CE
            ret

            Default2 :
        popad
            mov  byte ptr[eax + 0x4], 0x00
            mov ecx, 0x00
            push 0x005E7625
            ret
            Default :
        popad
            push 0x005E7625
            ret
    }
}
void __declspec(naked)AddOptionCloth()
{
    __asm
    {

        pushad
        mov eax, [ebp - 0x18]
        xor esi, esi
        LoopCheckType :
        xor edx, edx
            xor ecx, ecx
            push esi
            imul esi, esi, 0x60
            mov dl, [eax + esi + 0x128C + 0x18]
            cmp dl, 0x1
            jl NotInct
            //
            xor edi, edi
            LoopCheckOption :

        // bo add ebp,esi
        push edi
            lea edi, [edi + esi]
            xor ebx, ebx
            mov dl, [eax + 0x128C + 0x24 + edi]
            cmp dl, 0x13
            jnz CheckType2
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheck

            CheckType2 :
        cmp dl, 0x18
            jnz CheckType3
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + ebx]
            mov[eax + 0x702C], ecx
            jmp EndCheck


            CheckType3 :
        cmp dl, 0x82
            jnz CheckType4
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7250]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7250], ecx
            jmp EndCheck


            CheckType4 :
        cmp dl, 0x83
            jnz CheckType5
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7258]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7258], ecx
            jmp EndCheck


            CheckType5 :
        cmp dl, 0x17
            jnz CheckType6
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7024], ecx
            jmp EndCheck


            CheckType6 :
        cmp dl, 0x32
            jnz CheckType7
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7240], cx
            jmp EndCheck


            CheckType7 :
        cmp dl, 0x3D
            jnz CheckType8
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheck


            CheckType8 :
        cmp dl, 0x2
            jnz CheckType9
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FC4], ecx
            jmp EndCheck


            CheckType9 :
        cmp dl, 0x1
            jnz CheckType10
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck


            CheckType10 :
        cmp dl, 0xF
            jnz CheckType11
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheck


            CheckType11 :
        cmp dl, 0x34
            jnz CheckType12
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x7240 + 0x4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7240], cx
            jmp EndCheck


            CheckType12 :
        cmp dl, 0x89
            jnz CheckType13
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck


            CheckType13 :
        cmp dl, 0x88
            jnz CheckType14
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FBC], ecx
            jmp EndCheck


            CheckType14 :
        cmp dl, 0x10
            jnz EndCheck
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7000], ecx
            jmp EndCheck


            EndCheck :
        pop edi
            add edi, 0x5
            cmp edi, 0xF
            jz NotInct
            jmp LoopCheckOption
            //
            NotInct :
        pop esi
            add esi, 0x1
            cmp esi, 0x5
            jz CompleteCheck
            jmp LoopCheckType

            CompleteCheck :
        xor edx, edx
            mov ecx, [ebp - 0x18]
            mov dl, [ecx + 0x2A0 + 0x128C + 0x8]
            cmp edx, 0x1
            jnz Default22
            xor edx, edx
            mov dx, [ecx + 0x2A0 + 0x128C + 0xA]
            push edx
            mov dl, [ecx + 0x2A0 + 0x128C + 0x8]
            push edx
            mov ecx, 0x00776388
            mov ecx, [ecx]
            mov eax, 0x4D7FB0
            call eax
            and eax, 0xFFFF
            push eax
            mov ecx, 0x00776388
            mov ecx, [ecx]
            mov eax, 0x641930
            call eax
            cmp eax,0x00
            jz Default22
            xor edx, edx
            mov ebx, [eax + 0x14]
            test ebx, ebx
            jz Default22
            xor edi, edi
            LoopAdd2 :
        push eax
            mov dx, [ebx]
            mov eax, [ebp - 0x18]
            cmp dx, 0x13
            jnz CheckType22
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheck2D

            CheckType22 :
        cmp dx, 0x18
            jnz CheckType23
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + edx]
            mov[eax + 0x702C], ecx
            jmp EndCheck2D


            CheckType23 :
        cmp dx, 0x82
            jnz CheckType24
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7250]
            lea ecx, [ecx + edx]
            mov[eax + 0x7250], ecx
            jmp EndCheck2D


            CheckType24 :
        cmp dx, 0x83
            jnz CheckType25
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7258]
            lea ecx, [ecx + edx]
            mov[eax + 0x7258], ecx
            jmp EndCheck2D


            CheckType25 :
        cmp dx, 0x17
            jnz CheckType26
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + edx]
            mov[eax + 0x7024], ecx
            jmp EndCheck2D


            CheckType26 :
        cmp dx, 0x32
            jnz CheckType27
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheck2D


            CheckType27 :
        cmp dx, 0x3D
            jnz CheckType28
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheck2D


            CheckType28 :
        cmp dx, 0x2
            jnz CheckType29
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC4], ecx
            jmp EndCheck2D


            CheckType29 :
        cmp dx, 0x1
            jnz CheckType210
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck2D


            CheckType210 :
        cmp dx, 0xF
            jnz CheckType211
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheck2D


            CheckType211 :
        cmp dx, 0x34
            jnz CheckType212
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7240 + 0x4]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheck2D


            CheckType212 :
        cmp dx, 0x89
            jnz CheckType213
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck2D


            CheckType213 :
        cmp dx, 0x88
            jnz CheckType214
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FBC], ecx
            jmp EndCheck2D


            CheckType214 :
        cmp dx, 0x10
            jnz CheckType21415
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx
            jmp EndCheck2D

            CheckType21415 :
        cmp dx, 0x18
            jnz CheckType21416
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6B68]
            lea ecx, [ecx + edx]
            mov[eax + 0x6B68], ecx
            jmp EndCheck2D

            CheckType21416 :
        cmp dx, 0x9
            jnz CheckType21417
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov [eax + 0x6FD4], ecx
            jmp EndCheck2D

            CheckType21417 :
        cmp dx, 0xA
            jnz CheckType21418
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7004]
            lea ecx, [ecx + edx]
            mov[eax + 0x7004], ecx
            jmp EndCheck2D

            CheckType21418 :
        cmp dx, 0xB
            jnz CheckType21419
            xor edx, edx
            xor ecx,ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x86B8]
            lea ecx, [ecx + edx]
            mov[eax + 0x86B8], cl
            jmp EndCheck2D

            CheckType21419 :
        cmp dx, 0xC
            jnz CheckType21420
            xor edx, edx
            xor ecx, ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x86D0]
            lea ecx, [ecx + edx]
            mov[eax + 0x86D0], cl
            jmp EndCheck2D

            CheckType21420 :
        cmp dx, 0xD
            jnz CheckType21421
            xor edx, edx
            xor ecx, ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x86C0]
            lea ecx, [ecx + edx]
            mov[eax + 0x86C0], cl
            jmp EndCheck2D

            CheckType21421 :
        cmp dx, 0xE
            jnz CheckType21422
            xor edx, edx
            xor ecx, ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x86D8]
            lea ecx, [ecx + edx]
            mov[eax + 0x86D8], cl
            jmp EndCheck2D

            CheckType21422 :
        cmp dx, 0xF
            jnz CheckType21423
            xor edx, edx
            xor ecx, ecx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheck2D

            CheckType21423 :
        cmp dx, 0x10
            jnz CheckType2155
            xor edx, edx
            xor ecx, ecx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx
            jmp EndCheck2D
        
            CheckType2155 :
        cmp dx, 0x3F
            jnz EndCheck2D
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            mov[eax + 0x7240+2], cx
            mov[eax + 0x7240+4], cx
            mov[eax + 0x7240+6], cx
            mov[eax + 0x7240+8], cx
            jmp EndCheck2D

            EndCheck2D :
        pop eax
            mov ebx, [ebx + 0x10]
            test ebx, ebx
            jne LoopAdd2
            add edi, 0x1
            cmp edi, 0x2
            jz Default22
            mov ebx, [eax + 0x1C]
            test ebx, ebx
            jne LoopAdd2
            Default22:
            			xor edx,edx
			xor edi,edi
			xor esi,esi
			mov esi,0xC
			BackLoopCheckRelic:
			push esi
			imul esi,0x60
			lea edi,[edi+esi]
            add esi,0x3D
			BackLoopCheckRelic2:
			mov dx,[eax+0x128C+0x24+edi]
			test edx,edx
			jz NotHaveValueForRelic
			
			cmp dx, 0x13
            jnz CheckTypeRelic22
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheckRelic

            CheckTypeRelic22 :
        cmp dx, 0x18
            jnz CheckTypeRelic23
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + edx]
            mov[eax + 0x702C], ecx
            jmp EndCheckRelic


            CheckTypeRelic23 :
        cmp dx, 0x82
            jnz CheckTypeRelic24
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x7250]
            lea ecx, [ecx + edx]
            mov[eax + 0x7250], ecx
            jmp EndCheckRelic


            CheckTypeRelic24 :
        cmp dx, 0x83
            jnz CheckTypeRelic25
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x7258]
            lea ecx, [ecx + edx]
            mov[eax + 0x7258], ecx
            jmp EndCheckRelic


            CheckTypeRelic25 :
        cmp dx, 0x17
            jnz CheckTypeRelic26
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + edx]
            mov[eax + 0x7024], ecx
            jmp EndCheckRelic


            CheckTypeRelic26 :
        cmp dx, 0x32
            jnz CheckTypeRelic27
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheckRelic


            CheckTypeRelic27 :
        cmp dx, 0x3D
            jnz CheckTypeRelic28
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheckRelic


            CheckTypeRelic28 :
        cmp dx, 0x2
            jnz CheckTypeRelic29
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC4], ecx
            jmp EndCheckRelic


            CheckTypeRelic29 :
        cmp dx, 0x1
            jnz CheckTypeRelic210
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheckRelic


            CheckTypeRelic210 :
        cmp dx, 0xF
            jnz CheckTypeRelic211
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheckRelic


            CheckTypeRelic211 :
        cmp dx, 0x34
            jnz CheckTypeRelic212
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cx, [eax + 0x7240 + 0x4]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheckRelic


            CheckTypeRelic212 :
        cmp dx, 0x89
            jnz CheckTypeRelic213
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheckRelic


            CheckTypeRelic213 :
        cmp dx, 0x88
            jnz CheckTypeRelic214
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FBC], ecx
            jmp EndCheckRelic


            CheckTypeRelic214 :
        cmp dx, 0x10
            jnz CheckTypeRelic21415
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx
            jmp EndCheckRelic

            CheckTypeRelic21415 :
        cmp dx, 0x18
            jnz CheckTypeRelic21416
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6B68]
            lea ecx, [ecx + edx]
            mov[eax + 0x6B68], ecx
            jmp EndCheckRelic

            CheckTypeRelic21416 :
        cmp dx, 0x9
            jnz CheckTypeRelic21417
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov [eax + 0x6FD4], ecx
            jmp EndCheckRelic

            CheckTypeRelic21417 :
        cmp dx, 0xA
            jnz CheckTypeRelic21418
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov ecx, [eax + 0x7004]
            lea ecx, [ecx + edx]
            mov[eax + 0x7004], ecx
            jmp EndCheckRelic

            CheckTypeRelic21418 :
        cmp dx, 0xB
            jnz CheckTypeRelic21419
            xor edx, edx
            xor ecx,ecx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cl, [eax + 0x86B8]
            lea ecx, [ecx + edx]
            mov[eax + 0x86B8], cl
            jmp EndCheckRelic

            CheckTypeRelic21419 :
        cmp dx, 0xC
            jnz CheckTypeRelic21420
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cl, [eax + 0x86D0]
            lea ecx, [ecx + edx]
            mov[eax + 0x86D0], cl
            jmp EndCheckRelic

            CheckTypeRelic21420 :
        cmp dx, 0xD
            jnz CheckTypeRelic21421
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cl, [eax + 0x86C0]
            lea ecx, [ecx + edx]
            mov[eax + 0x86C0], cl
            jmp EndCheckRelic

            CheckTypeRelic21421 :
        cmp dx, 0xE
            jnz CheckTypeRelic21422
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cl, [eax + 0x86D8]
            lea ecx, [ecx + edx]
            mov[eax + 0x86D8], cl
            jmp EndCheckRelic

            CheckTypeRelic21422 :
        cmp dx, 0xF
            jnz CheckTypeRelic21423
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheckRelic

            CheckTypeRelic21423 :
        cmp dx, 0x10
            jnz CXVL
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx
            jmp EndCheckRelic

            CXVL :
        cmp dx, 0x3
            jnz CXKC
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax + 0x128C + 0x24 + edi + 0x2]
            mov cx, [eax + 0x6FB8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FB8], ecx
            jmp EndCheckRelic

            CXKC :
        cmp dx, 0x8A
            jnz Satthuongchimag
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax + 0x128C + 0x24 + edi + 0x2]
            mov cx, [eax + 0x6FF0]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FF0], ecx
            jmp EndCheckRelic

            Satthuongchimag :
        cmp dx, 0x86
            jnz Satthuongtoithieuvk
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax + 0x128C + 0x24 + edi + 0x2]
            mov cx, [eax + 0x7030]
            lea ecx, [ecx + edx]
            mov[eax + 0x7030], ecx
            jmp EndCheckRelic


            Satthuongtoithieuvk :
        cmp dx, 0x5D
            jnz SmtoidaPhantram
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax + 0x128C + 0x24 + edi + 0x2]
            mov cx, [eax + 0x7068]
            lea ecx, [ecx + edx]
            mov[eax + 0x7068], ecx
            jmp EndCheckRelic

            SmtoidaPhantram :
        cmp dx, 0x2F
            jnz noicongdaPhantram
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax + 0x128C + 0x24 + edi + 0x2]
            mov cx, [eax + 0x724C]
            lea ecx, [ecx + edx]
            mov[eax + 0x724C], ecx
            jmp EndCheckRelic

            noicongdaPhantram :
        cmp dx, 0x30
            jnz CheckTypeRelic2155
            xor edx, edx
            xor ecx, ecx
            mov dx, [eax + 0x128C + 0x24 + edi + 0x2]
            mov cx, [eax + 0x7254]
            lea ecx, [ecx + edx]
            mov[eax + 0x7254], ecx
            jmp EndCheckRelic
        
            CheckTypeRelic2155 :
        cmp dx, 0x3F
            jnz EndCheckRelic
            xor edx, edx
            mov dx, [eax+0x128C+0x24+edi+0x2]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            mov[eax + 0x7240+2], cx
            mov[eax + 0x7240+4], cx
            mov[eax + 0x7240+6], cx
            mov[eax + 0x7240+8], cx

			EndCheckRelic:
			add edi,0x5
			cmp edi,esi
			jl BackLoopCheckRelic2
			NotHaveValueForRelic:
			pop esi
            add esi,0x1
			xor edi,edi
			cmp esi,0x14
			jg CompleteCheckRelic
			jmp BackLoopCheckRelic
			CompleteCheckRelic:
			
        popad

            mov eax, [ebp - 0x8]
            and eax, 0xFF
            push 0x004D1410
            ret
    }
}
void Patch(BYTE* dst, BYTE* src, unsigned int size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}
void __declspec(naked)DontDeleteClothInc()
{
    __asm
    {
        xor eax, eax
        mov     al, [edx + 0x4]
        imul eax, 0x60
        mov     ecx, [ebp - 0x6C]
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x8]
        cmp dl, 0x1
        jnz Default
        mov dl, [ecx + eax + 0x128C + 0x18]
        sub edx, 0x1
        mov[ecx + eax + 0x128C + 0x18], dl
        push 0x00522819
        ret
        Default :
        xor eax, eax
            mov     al, [edx + 0x4]
            push eax
            mov ecx, [ebp - 0x6C]
            push 0x00522814
            ret
    }
}
void __declspec(naked)DontDeleteClothInc1()
{
    __asm
    {
        xor ecx,ecx
        mov     cl, [eax + 0x4]
        imul ecx, 0x60
        mov     eax, [ebp - 0x6C]
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x8]
        cmp dl, 0x1
        jnz Default
        mov dl, [ecx + eax + 0x128C + 0x18]
        sub edx, 0x1
        mov[ecx + eax + 0x128C + 0x18], dl
        push 0x005225EC
        ret
        Default :
        xor ecx, ecx
            mov eax, [ebp + 0x8]
            mov     cl, [eax + 0x4]
            push ecx
            mov ecx, [ebp - 0x6C]
            push 0x005225A8
            ret
    }
}
void __declspec(naked)SendFailIncClot()
{
    __asm
    {
        lea eax, [ebp - 0x2C]
        xor ecx, ecx
        mov cl, [eax + 0x4]
        cmp cl, 0x1
        jl Default
        mov cl, [eax + 0x6]
        imul ecx, 0x60
        xor eax, eax
        mov eax, [ebp - 0x50]
        mov cl, [eax + ecx + 0x128C + 0x8]
        cmp cl, 0x1
        jnz Default
        lea eax, [ebp - 0x2C]
        mov byte ptr[eax + 0x4], 0x00
        xor ecx, ecx
        mov cl, [eax + 0x5]
        sub ecx, 0x1
        mov[eax + 0x5], cl
        Default :
        lea eax, [ebp - 0x2C]
            push    eax
            mov     ecx, [ebp - 0x50]
            push 0x00522CB8
            ret
    }
}
void __declspec(naked)FixErrorDmg()
{
    __asm
    {
        mov ecx, 0x64
        idiv ecx
        mov edx,0x00000000
        push 0x0058BBAE
        ret
    }
}
void __declspec(naked)ChangeDie()//00588517 
{
    __asm
    {
        cmp byte ptr[edx + 0x19], 0x1
        jnz Default
        mov byte ptr[edx+0x19],0x00
        Default:
        xor ax,ax
        push 0x0058851E
        ret
    }
}
void __declspec(naked)ChangeDie1()//0058789C
{
    __asm
    {
        cmp byte ptr[edx + 0x19], 0x1
        jnz Default
        mov byte ptr[edx + 0x19], 0x00
        Default:
        xor ax, ax
        push 0x005878A3
        ret
    }
}
void __declspec(naked)ChangeDie2()//00588720
{
    __asm
    {
        cmp byte ptr[edx + 0x19], 0x1
        jnz Default
        mov byte ptr[edx + 0x19], 0x00
        Default:
        mov eax, [ebp - 0x40]
        push 0x00588727
        ret
    }
}
void __declspec(naked)ChangeTypeRelic()//0050FE80
{
    __asm
    {
        mov edx, [ebp - 0x1C]
        cmp edx,0x09
        jnz Default
        push 0x0050FEBD
        ret
        Default :
        xor ecx, ecx
        mov cl, [edx + 0x005101E6]
        push 0x0050FE8B
        ret


    }
}
void __declspec(naked)CheckItem()//0050FE80
{
    __asm
    {
       pushad
       mov ebx, 0x0000000C
       xor esi,esi
       BackLoop:
       lea eax,ListItemCheck1
       mov edi, [eax + esi * 4]
       BackLoop1:
       push ebx
       mov ecx, [ebp - 0x18]
       imul ebx,0x60
       xor edx,edx
       mov dx,[ecx+0x128C+ebx+0xA]
       pop ebx
       cmp edx, edi
       jz OutGame
       add ebx,0x01
       cmp ebx,0x13
       jle BackLoop1
       mov ebx, 0x0000000C
       add esi,0x1
       cmp esi,0x4
       jle BackLoop
       popad
       mov word ptr[ebp - 0x4], 0000
       push 0x004CEC29
       ret

       OutGame:
       popad
       mov eax, [ebp - 0x18]
       push eax
       mov ecx, 0x007763AC
       mov ecx,[ecx]
       mov eax, 0x00602604
       call eax
       push 0x004CEC29
       ret
    }
}
void __declspec(naked)CheckItem1()//0050FE80
{
    __asm
    {
        pushad
        mov ebx, 0x0000000C
        xor esi, esi
        BackLoop :
        lea eax, ListItemCheck2
            mov edi, [eax + esi * 4]
            BackLoop1 :
            push ebx
            mov ecx, [ebp - 0x18]
            imul ebx, 0x60
            xor edx, edx
            mov dx, [ecx + 0x128C + ebx + 0xA]
            pop ebx
            cmp edx, edi
            jz OutGame
            add ebx, 0x01
            cmp ebx, 0x13
            jle BackLoop
            mov ebx, 0x0000000C
            add esi, 0x1
            cmp esi, 0x4
            jle BackLoop
            popad
            mov edx, [ebp - 0x18]
            xor eax, eax
            push 0x004CEC45
            ret

            OutGame :
            push ebx
            xor eax,eax
            mov ebx, 0x0000000C
            BackLoop2:
            push ebx
            mov ecx, [ebp - 0x18]
            imul ebx, 0x60
            xor edx, edx
            mov dx, [ecx + 0x128C + ebx + 0xA]
            pop ebx
            cmp edx, edi
            jz ChecutGame
            add ebx, 0x01
            cmp ebx, 0x13
            jle BackLoop2
            pop ebx
            add ebx,0x01
            jmp BackLoop1

            ChecutGame:
            add eax,0x1
            cmp eax,0x2
            jge OutGame1
            add ebx, 0x01
            cmp ebx, 0x13
            jle BackLoop2
            pop ebx
            add ebx, 0x01
            jmp BackLoop1

            OutGame1 :
            popad
            mov eax, [ebp - 0x18]
            push eax
                mov ecx, 0x007763AC
                mov ecx, [ecx]
            mov eax, 0x00602604
            call eax
            mov edx, [ebp - 0x18]
            xor eax, eax
            push 0x004CEC45
            ret

    }
}
void __declspec(naked)ChangePacketRelics()//0050FEE4
{
    __asm
    {
        pushad
        xor ecx,ecx
        mov cl,[eax+0x8]
        cmp ecx,0x9
        jnz Default
        mov  cl, [eax + 0x24]
        test ecx,ecx
        jz Default
        xor ecx,ecx
        mov cl,[eax+0x9]
        add ecx,0x90
        mov [edx+0x2],cl
        popad
        push 0x0050FEEA
        ret
        Default:
        popad
            mov cl, [eax + 0x9]
            mov [edx + 0x2], cl
        push 0x0050FEEA
        ret

    }
}
void __declspec(naked)AddOptionNewSlot()//004CBF66
{
    __asm
    {
        cmp dword ptr[ebp - 0x50], 0x18
        jg loc_4CC020
        push 0x004CBF70
        ret

        loc_4CC020:
        cmp dword ptr[ebp - 0x50], 0x19
        jnz NotaddMoreSlot
        mov dword ptr[ebp-0x50],0x8C
            NotaddMoreSlot:
            cmp dword ptr[ebp - 0x50], 0x94
            jg loc_4CC020Out
            mov edx,[ebp - 0x50]
            mov[ebp - 0x64], edx
            xor eax,eax
            sub edx,0x8C
            cmp edx,0x4
            jg Lost4Duoi
            mov eax,0x3
            jmp DoneWithCheckJmp
            Lost4Duoi:
            mov eax, 0x4
            DoneWithCheckJmp:
            push 0x004CBF8B
            ret
            loc_4CC020Out:
            push 0x004CC020
            ret

    }
}
void __declspec(naked)AddOptionNewSlot2()//0050D0DB
{
    __asm
    {
        mov edx, [ebp - 0x4]
        and edx,0x000000FF
        cmp edx,0x18
        jg log_0050E2AE
        push 0x0050D0ED
        ret

        log_0050E2AE:
        cmp edx, 0x8C
        jl LogOutCheck
        cmp edx, 0x94
        jg LogOutCheck
        push 0x0050D0ED
        ret


            LogOutCheck:
        push 0x0050E2AE
        ret


    }
}
void __declspec(naked)AddOptionNewSlot3()//0050EB3D
{
    __asm
    {
        add eax, 0x10
        cmp esi,eax
        jge loc_50EB48
        push 0x0050EB44
        ret
        loc_50EB48:
        cmp esi,0x8C
        jl OutCheck
        cmp esi,0x94
        jg OutCheck
        push 0x0050EB44
        ret

        OutCheck:
        push 0x0050EB48
        ret
    }
}
void __declspec(naked)AddOptionNewSlot4()//0050D7B5
{
    __asm
    {
        add ecx, 0xF
        cmp esi, ecx
        jle loc_50D7EE
        cmp esi,0x8C
        jl NotADd
        cmp esi, 0x94
        jg NotADd
        push 0x0050D7EE
        ret

        NotADd:
        push 0x0050EB44
        ret

        loc_50D7EE :
        push 0x0050D7EE
        ret
    }
}
void __declspec(naked)AddOptionNewSlot5()//00512A14
{
    __asm
    {
        mov[ebp - 0x20], ecx
        cmp ecx,0x8C
        jl Default
        cmp ecx,0x94
        jg Default
        push 0x00512AD9
        ret
        Default:
        cmp[ebp - 0x20],0x13
        jg loc_512A43
        push 0x00512A1D
        ret
        loc_512A43:
        push 0x00512A43
        ret
    }
}
void __declspec(naked)AddOptionNewSlot6()//004CBA91
{
    __asm
    {
        xor ecx,ecx
        mov cl,[ebp + 0x8]
        cmp ecx,0x18
        jle loc_4CBA9F
        cmp ecx,0x8C
        jl OutCheckSlot
        cmp ecx,0x94
        jg OutCheckSlot
        jmp loc_4CBA9F

        OutCheckSlot:
        push 0x004CBA9A
        ret


        loc_4CBA9F:
        xor edx,edx
        mov dl, [ebp + 0x8]
        push 0x004CBAA3
        ret
    }
}
void __declspec(naked)AddOptionNewSlot16()//004CBA86
{
    __asm
    {
        mov[ebp - 0x30], ecx
        xor eax,eax
        mov al, [ebp + 0x8]
        push 0x004CBA8D
        ret
    }
}
void __declspec(naked)ChangeOldCode()//004D8EE8
{
    __asm
    {
        xor eax, eax
        mov   al, [ebp + 0x8]
        cmp     eax, 0x5
        jz       loc_4D8F38
        xor ecx, ecx
        mov   cl, [ebp + 0x8]
        cmp     ecx, 0x6
        jz       loc_4D8F38
        xor edx, edx
        mov   dl, [ebp + 0x8]
        cmp     edx, 0xC
        jl       loc_4D8F19
        xor ecx, ecx
        mov   cl, [ebp + 0x8]
        mov esi, ecx
        mov     ecx, [ebp - 0x4]
        mov eax,0x004D9030
        call    eax
        movsx   eax, al
        add     eax, 0xC
        cmp     esi, eax
        jl       loc_4D8F38

        loc_4D8F19 :
        xor ecx, ecx
            mov   cl, [ebp + 0x8]
            cmp     ecx, 0x10
            jl       loc_4D8F3C
            xor ecx, ecx
            mov   cl, [ebp + 0x8]
            mov esi, ecx
            mov     ecx, [ebp - 0x4]
            mov eax,0x004D9050
            call    eax
            movsx   edx, al
            add     edx, 0x10
            cmp     esi, edx
            jge      loc_4D8F3C


            loc_4D8F38 :
        push 0x004D8F38
            ret

            loc_4D8F3C :
        cmp esi,0x8C
        jl DefaltnotNewSlot
        cmp esi,0x94
        jg DefaltnotNewSlot
        jmp loc_4D8F38
        DefaltnotNewSlot:
        push 0x004D8F3C
            ret
    }
}
void __declspec(naked)AddOptionNewSlot7()//004CBAF8
{
    __asm
    {
        xor eax,eax
        mov al,[ebp+0x8]
        imul eax,0x60
        push 0x004CBAFF
        ret
    }
}
void __declspec(naked)AddOptionNewSlot8()//004D1591
{
    __asm
    {
        cmp dword ptr[ebp - 0xC], 0x18
        jg  loc_4D1691
        push 0x004D159B
        ret
        loc_4D1691:
        cmp dword ptr[ebp - 0xC], 0x19
        jnz NotADdMore
        mov dword ptr[ebp - 0xC], 0x8C
        NotADdMore:
        cmp dword ptr[ebp - 0xC], 0x8C
        jl BackOut
        cmp dword ptr[ebp - 0xC], 0x94
        jg BackOut
        push 0x004D15FE
        ret

        BackOut:
        push 0x4D1691
        ret
    }
}
void __declspec(naked)AddEffectAfterAttack()//005D4A36
{
    __asm
    {
        pushad
        //Kiem tra co pet ko ( Kiem tra Type Vat pham)
        mov ecx, [ebp - 0xDBC]
        lea eax,[ecx+0x128C+0x8+0x3780]
        xor edx,edx
        mov dl,[eax]
        cmp edx,0x9
        jnz Default
        //
        //Kiem tra co pet ko ( Kiem tra ID Vat pham)
        xor edx,edx
        mov dx,[eax+0x2]
        cmp edx, 0x48E
        jl Default  //tét
        cmp edx, 0x496
        jg Default
        // 
            mov  ecx, [ebp - 0xDBC]
            xor eax, eax
            mov ax, [ecx + 0x3780 + 0x128C + 0xA]
            cmp eax, 0x48E
            jnz GetIdMod1
            push 0x136
            jmp addeffectattack
            GetIdMod1 :
        cmp eax, 0x48F
            jnz GetIdMod12
            push 0x136
            jmp addeffectattack
            GetIdMod12 :
        cmp eax, 0x490
            jnz GetIdMod13
            push 0x136
            jmp addeffectattack

            GetIdMod13 :
        cmp eax, 0x491
            jnz GetIdMod14
            push 0x136
            jmp addeffectattack

            GetIdMod14 :
        cmp eax, 0x492
            jnz GetIdMod15
            push 0x136
            jmp addeffectattack

            GetIdMod15 :
        cmp eax, 0x493
            jnz GetIdMod16
            push 0x136
            jmp addeffectattack

            GetIdMod16 :
        cmp eax, 0x494
            jnz GetIdMod17
            push 0x136
            jmp addeffectattack

            GetIdMod17 :
        cmp eax, 0x495
            jnz GetIdMod18
            push 0x136
            jmp addeffectattack

            GetIdMod18 :
        cmp eax, 0x496
            jnz Default
            push 0x136
            jmp addeffectattack
        addeffectattack:
        mov ecx, 0x00776388
        mov ecx,[ecx]
        mov eax,0x004B0F90
        call eax
        test eax,eax
        jz Default// Not Found ID
        //
        mov ebx,eax //Luu gia tri lay dc 
        mov eax,0x00406AD0
        call eax
        push eax
        mov ebx,[ebx+0x4A]
        push ebx
        mov ecx, [ebp - 0xDBC]
        mov eax,0x004DD89F
        call eax


        Default:
        popad
        push 0x005D4A5A
            ret
    }
}
DWORD WINAPI MainThread(LPVOID param)
{
    int hooklenght = 7;
    int hooklenghtAddSkill = 8;
    //DWORD ChangeTimeUse = 0x52CD72;
    //Patch((BYTE*)ChangeTimeUse, (BYTE*)"\x90\xE2\x00\x00", 4);
    //Sleep(5000);
    DWORD hookAddSKill = 0x005E19C0;
    DWORD CheckItemAdr = 0x004CEC23;
    DWORD hookAddress = 0x0049CDB5;
    DWORD CheckItem1Adr = 0x004CEC40;
    DWORD SendPacketIncCloAdr = 0x00522CBD;
    DWORD AdreFixDame1 = 0x0052BDC0;
    DWORD AcceptIntNewItemAdr = 0x0063AFF0;
    DWORD FixIncahnt = 0x00522AF6;
    DWORD AcceptType8Adr = 0x0063B0EC;
    DWORD CheckTypeUsedAdr = 0x0052CD5D;
    DWORD AdreFixDame2 = 0x0052BD40;
    DWORD ChangePacketRelicsAdr = 0x0050FEE4;
    DWORD AdreFixDame3 = 0x0052BD80;
    DWORD DontDeleteClothIncAdr = 0x0052280D;
    DWORD MoreDamageThucDieAdr = 0x005887D1;
    DWORD MoreDamageDr = 0x005DCFA9;
    DWORD MoreDamageMaxAdr = 0x0058814E;
    DWORD AdInchant = 0x0063B075;
    DWORD BlockUsePkAdr = 0x005E761B;
    DWORD LockEffect = 0x00495660;
    DWORD ExchangeItemAdr = 0x00522003;
    DWORD FixResetWeaponAdr = 0x004A2667;
    DWORD AdreFixDame4 = 0x0052BD00;
    DWORD AdreFixDame5 = 0x0052BE00;
    DWORD CheckIncClotAdr = 0x005222D8;
    DWORD UseItemSpawAdr = 0x0005E75C0;
    DWORD LockSkill = 0x00495660;
    DWORD AddOptionClothAdr = 0x004D1408; 
    DWORD FixOptDeccoAdr = 0x004D1474;
    DWORD CheckTypeKcorPhAdr = 0x00522009;
    DWORD MoreDamageThucDie2Adr = 0x0058871D;
    DWORD MoreDamageThuc1Adr = 0x00588151;
    DWORD MoreDamageThuc2Adr = 0x00588022;
    DWORD MoreDamageThuc3Adr = 0x00587E85;
    DWORD MoreDamageSkillNukerAdr = 0x005DE4EC;
    DWORD MoreDamageSkillNuker1Adr = 0x005D7929;
    DWORD LockEquipAssesstoryAdr = 0x005E1854;
    DWORD FixMaxCritMobAdr = 0x0059435D;
    DWORD FixMaxCritMob2Adr = 0x0059437E;
    DWORD FixAmDamagePvpAdr = 0x004B99C7;
    DWORD FixAmDamagePvp1Adr = 0x004B99FC;
    DWORD GetAmDmgTanker1Adr = 0x004B8F31;
    DWORD GetAmDmgTanker2Adr = 0x004B8F82;
    DWORD FixAmDamTankerAdr = 0x004C82CD;
    DWORD GetAmDmgTanker11Adr = 0x004B8F57;
    DWORD GetAmDmgTanker22Adr = 0x004B8FA8;
    DWORD GetAmDmgNukerAdr = 0x004C8B42;
    DWORD GetAmDmgNuker2Adr = 0x004B98E0;
    DWORD FixMaxCritNukerAdr = 0x0059439B;
    DWORD FixMaxCritNuker2Adr = 0x005943BC;
    DWORD SendFailIncClotAdr = 0x00522CB1;
    DWORD WeaponSkill2Adr = 0x005E1863;
    DWORD DontDeleteClothInc1Adr = 0x005225A1;
    DWORD FixMaxCritNuker3Adr = 0x005943ED;
    DWORD FixMaxCritNuker4Adr = 0x00594437;
    DWORD FixMaxCritNuker5Adr = 0x00594475;
    DWORD FixMaxCritNuker31Adr = 0x0059440E;
    DWORD FixMaxCritNuker41Adr = 0x00594458;
    DWORD FixMaxCritNuker51Adr = 0x00594496;
    DWORD FixErrorDmgAdr = 0x0058BBA4;
    DWORD ChangeDieAdr = 0x00588517;
    DWORD ChangeDie1Adr = 0x0058789C;
    DWORD ChangeDie2Adr = 0x00588720;
    DWORD ChangeTypeRelicAdr = 0x0050FE80;
    DWORD TestMovePetAdr = 0x0048E712;
    DWORD DisableMovePetAdr = 0x005A0D14;
    DWORD DisableMoveRandomPetAdr = 0x0059020F;
    DWORD DisableMovePet1Adr = 0x00406A34;
    DWORD DisableMoveRandomPet23Adr = 0x0058146C;
    DWORD ByPassCheckRunAdr = 0x0059C084;
    DWORD ByPassCheckRun2Adr = 0x0059D4C0;
    DWORD MoveMobNearUserAdr = 0x0059D5D7;
    DWORD ProcessDeletePetAdr = 0x005D0F3A;
    DWORD ProcessDeletePet2Adr = 0x00602093;
    DWORD ProcessDeletePet3Adr = 0x00602613;
    DWORD AddOptionNewSlotAdr = 0x004CBF66;
    DWORD AddOptionNewSlot2Adr = 0x0050D0DB;
    DWORD AddOptionNewSlot3Adr = 0x0050EB3D;
    DWORD AddOptionNewSlot4Adr = 0x0050D7B5;
    DWORD AddOptionNewSlot5Adr = 0x00512A14;
    DWORD AddOptionNewSlot6Adr = 0x004CBA91;
    DWORD ChangeOldCodeAdr = 0x004D8EE8;
    DWORD AddOptionNewSlot7Adr = 0x004CBAF8;
    DWORD AddOptionNewSlot8Adr = 0x004D1591;
    DWORD AddOptionNewSlot16Adr = 0x004CBA86;
    DWORD ByPassCheckRun42Adr = 0x0059D79E;
    DWORD ByPassCheckRunNext1Adr = 0x0059D718;
    DWORD ByPassCheckRunNext2Adr = 0x005A0D17;
    DWORD AddEffectAfterAttackAdr = 0x005D4A36;


    //16 Slot
    /*hook((void*)AddOptionNewSlot16Adr, AddOptionNewSlot16, 7);
    hook((void*)AddOptionNewSlot8Adr, AddOptionNewSlot8, 10);
    hook((void*)AddOptionNewSlot7Adr, AddOptionNewSlot7, 7);

    hook((void*)ChangeOldCodeAdr, ChangeOldCode, 7);
    hook((void*)AddOptionNewSlot6Adr, AddOptionNewSlot6, 7);
    hook((void*)AddOptionNewSlot5Adr, AddOptionNewSlot5, 7);
    hook((void*)AddOptionNewSlot4Adr, AddOptionNewSlot4, 5);
    hook((void*)AddOptionNewSlot3Adr, AddOptionNewSlot3, 5);
    hook((void*)AddOptionNewSlot2Adr, AddOptionNewSlot2, 9);
    hook((void*)AddOptionNewSlotAdr, AddOptionNewSlot, 10);*/

    //Pet
    //Effect Pet
    hook((void*)AddEffectAfterAttackAdr, AddEffectAfterAttack, 6);
    //
   /* hook((void*)ByPassCheckRunNext1Adr, ByPassCheckRunNext1, 6);
    //hook((void*)ByPassCheckRunNext2Adr, ByPassCheckRunNext2, 6);
    hook((void*)ByPassCheckRun42Adr, ByPassCheckRun42, 7);
    hook((void*)DisableMoveRandomPet23Adr, DisableMoveRandomPet23, 7);
    hook((void*)ByPassCheckRunAdr, ByPassCheckRun, 6);
    hook((void*)ProcessDeletePetAdr, ProcessDeletePet, 6);
    hook((void*)ProcessDeletePet2Adr, ProcessDeletePet2, 5);
    hook((void*)ProcessDeletePet3Adr, ProcessDeletePet3, 5);
    hook((void*)MoveMobNearUserAdr, MoveMobNearUser, 6);
    hook((void*)ByPassCheckRun2Adr, ByPassCheckRun2, 6);
    hook((void*)DisableMoveRandomPetAdr, DisableMoveRandomPet, 7);
    //hook((void*)DisableMovePetAdr, DisableMovePet, 6);
    //hook((void*)DisableMovePet1Adr, DisableMovePet1, 6);
    hook((void*)TestMovePetAdr, TestMovePet, 6);*/

    hook((void*)ChangeTypeRelicAdr, ChangeTypeRelic, 11);
   /* hook((void*)CheckItemAdr, CheckItem, 6);
    hook((void*)CheckItem1Adr, CheckItem1, 5);*/
    hook((void*)FixErrorDmgAdr, FixErrorDmg, 10);


    hook((void*)FixMaxCritNuker3Adr, FixMaxCritNuker3, 7);
    hook((void*)FixMaxCritNuker4Adr, FixMaxCritNuker4, 7);
    hook((void*)FixMaxCritNuker5Adr, FixMaxCritNuker5, 7);
    hook((void*)FixMaxCritNuker31Adr, FixMaxCritNuker31, 6);
    hook((void*)FixMaxCritNuker41Adr, FixMaxCritNuker41, 6);
    hook((void*)FixMaxCritNuker51Adr, FixMaxCritNuker51, 6); 
    //hook((void*)FixOptDeccoAdr, FixOptDecco, 9);

    hook((void*)DontDeleteClothInc1Adr, DontDeleteClothInc1, 7);
    hook((void*)WeaponSkill2Adr, WeaponSkill2, 6);
    hook((void*)SendFailIncClotAdr, SendFailIncClot, 7);
    hook((void*)DontDeleteClothIncAdr, DontDeleteClothInc, 7);
    hook((void*)FixMaxCritNukerAdr, FixMaxCritNuker, 7);
    hook((void*)FixMaxCritNuker2Adr, FixMaxCritNuker2, 6);
    hook((void*)GetAmDmgNukerAdr, GetAmDmgNuker, 5);
    hook((void*)GetAmDmgNuker2Adr, GetAmDmgNuker2, 9);
    hook((void*)GetAmDmgTanker11Adr, GetAmDmgTanker11, 7);
    hook((void*)GetAmDmgTanker22Adr, GetAmDmgTanker22, 7);
    hook((void*)FixAmDamTankerAdr, FixAmDamTanker, 5);
    hook((void*)GetAmDmgTanker1Adr, GetAmDmgTanker1, 7);
    hook((void*)GetAmDmgTanker2Adr, GetAmDmgTanker2, 7);
    hook((void*)FixAmDamagePvp1Adr, FixAmDamagePvp1, 5);
    hook((void*)FixAmDamagePvpAdr, FixAmDamagePvp, 6);
    hook((void*)FixMaxCritMob2Adr, FixMaxCritMob2, 6);
    hook((void*)FixMaxCritMobAdr, FixMaxCritMob, 7);
    hook((void*)LockEquipAssesstoryAdr, LockEquipAssesstory, 6);
    hook((void*)MoreDamageSkillNuker1Adr, MoreDamageSkillNuker1, 7);
    hook((void*)MoreDamageSkillNukerAdr, MoreDamageSkillNuker, 7);
    //Bo hook((void*)MoreDamageThucDie2Adr, MoreDamageThucDie2, 7);
    hook((void*)MoreDamageThucDieAdr, MoreDamageThucDie, 7);
    hook((void*)ChangeDieAdr, ChangeDie, 7);
    hook((void*)ChangeDie1Adr, ChangeDie1, 7);
    hook((void*)ChangeDie2Adr, ChangeDie2, 7);
    hook((void*)MoreDamageThuc1Adr, MoreDamageThuc1, 8);
    hook((void*)MoreDamageThuc2Adr, MoreDamageThuc2, 8);
    hook((void*)MoreDamageThuc3Adr, MoreDamageThuc3, 8);

    hook((void*)CheckTypeKcorPhAdr, CheckTypeKcorPh, 6);
    hook((void*)AcceptType8Adr, AcceptType8, 6);
    hook((void*)SendPacketIncCloAdr, SendPacketIncClo, 10);
    hook((void*)CheckIncClotAdr, CheckIncClot, 5);
    hook((void*)AddOptionClothAdr, AddOptionCloth, 8);
    hook((void*)LockSkill, DisableEffect, 6);
    hook((void*)CheckTypeUsedAdr, CheckTypeUsed, 6);
    hook((void*)BlockUsePkAdr, BlockUsePk, 10);
    hook((void*)AcceptIntNewItemAdr, AcceptIntNewItem, 7);
    hook((void*)FixResetWeaponAdr, FixResetWeapon, 7);
    jmpBackAdd = hookAddress + hooklenght;
    jmpBackAdd2 = hookAddSKill + hooklenghtAddSkill;
    hook((void*)hookAddress, DeccoEffect, hooklenght);
    hook((void*)UseItemSpawAdr, UseItemSpawn, 6);
    hook((void*)ExchangeItemAdr, ExchangeItem, 6);
    //Bo hook((void*)MoreDamageMaxAdr, MoreDamageMax, 7);
    hook((void*)MoreDamageDr, MoreDamageSkill, 7);
    hook((void*)FixIncahnt, FixInchantBlood, 10);
    hook((void*)AdreFixDame1, FixDmage1, hooklenght);
    hook((void*)AdInchant, InChantCloth, 9);
    hook((void*)AdreFixDame2, FixDmage2, hooklenght);
    hook((void*)AdreFixDame3, FixDmage3, hooklenght);
    hook((void*)AdreFixDame4, FixDmage4, hooklenght);
    //Bo hook((void*)AdreFixDame5, FixDmage5, hooklenght);
    //hook((void*)hookAddSKill, WeaponSkill, 8);
    uintptr_t moBase = (uintptr_t)GetModuleHandle(NULL);
    gms_ctrl_add_skill1 = (gms_ctrl_add_skill)(moBase + 0x0020E2E2);
    gms_ctrl_rem_skill1 = (gms_ctrl_rem_skill)(moBase + 0x0020E374);
    get_name1 = (get_name)(moBase + 0x1F690);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwreason, LPVOID lpRevered)
{
    switch (dwreason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
        break;
    default:
        break;
    }
    return true;
}

