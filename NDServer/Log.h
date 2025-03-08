#pragma once
//#include <Windows.h>

#define _LOG_ITEM_USED_BOX 125
#define _LOG_ITEM_USED_BOOK_COMBINE 126
#define _LOG_ITEM_COMBINE 127
#define _LOG_ITEM_USED_POTION_EXP 128
#define _LOG_INCHANT_CLOTH 129
#define _LOG_TOTALDMGBOSS 130
#define _LOG_GET_EVENTITEM 131
typedef unsigned __int64 u_int64;
/*typedef int(__thiscall* InsertItemLog)(int a1, int a2);
InsertItemLog AddInsertItemLog;
uintptr_t moBase = (uintptr_t)GetModuleHandle(NULL);
AddInsertItemLog = (InsertItemLog)(moBase + 0x140BA4);
*/
struct _ItemLog
{
	uint64_t uniquiID; //0x0000
	char pad_0008[8]; //0x0008
	char Name[13]; //0x0010
	char pad_001D[21]; //0x001D
	uint8_t TypeID; //0x0032
	char pad_0033[1]; //0x0033
	uint16_t IDItem; //0x0034
	char pad_0036[48]; //0x0036
};

int addLog(int typeUsed, int typeItem, int IdItemUsed, int count, int IdEvent, int iDMaps);