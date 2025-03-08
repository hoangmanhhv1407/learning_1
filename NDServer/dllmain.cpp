// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "dllmain.h"
#include <timeapi.h>
#pragma comment(lib, "winmm.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma pack(1)
typedef unsigned short u_short;
typedef unsigned int	 u_int;
typedef unsigned char u_char;
typedef unsigned __int64 u_int64;
#define MAX_CHAT_LENGTH 81
#define CuuPhung
//#define Zplay
#include "StdAfx.h"
#include <fstream>
#include <iostream>
using namespace std;


typedef struct CMSG_GM_EDIT_ZONE
{
    u_short usLength;
    u_char cMessage;
    char cCharacName[13];
    int iZone;
    float fX;
    float fZ;
}CMSG_GM_EDIT_ZONE;
struct CMSG_GM_ADD_INVITEM {
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];			//UniqueUserID

    u_int64             ui64UniqueId; // 8byte

    char				cFirstType;
    char				cSecondType;
    short				sItemID;
    unsigned char		ucItemCount;
    unsigned short		usDurability;
    unsigned char		ucSlotCount;			
    unsigned char		ucInchant;					
};

struct CMSG_GM_ADD_INVGOLD {
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];			//UniqueUserID
    int					iGold;
};
struct _sHeader {
    u_short		sLength : 12;		// -2048 ~ 2047
    u_short		sCrypto : 2;		// 0 : false , ³ª¸ÓÁö´Â true
    u_short		sCompressed : 2;	//0 : false , ³ª¸ÓÁö´Â true

    _sHeader() {}
    _sHeader(u_short len) : sLength(len), sCrypto(0), sCompressed(0) {}
};
struct MSG_ZONE_CHAT_NORMAL
{
    _sHeader			header;
    u_char				ucMessage;

    char				cMode;		// 0-14ÀÏ¹Ý(Ä®¶ó°ª), 15 : ¸ÊÃ¤ÆÃ. 16 µ¿Çà ,17 ºÐÆÄÃª, 18 µ¿¸ÍÃÂ. 32 ±Í¼Ó¸» 33 º¹¸éÀÏ¹Ý  34 º¹¸é±Ó¸» 64 ºê·Îµå, 127 ¿î¿µÀÚÀÇ ¸Þ¼¼Áö. »öÁöÁ¤ µÊ. -1 Àº Ã¤ÆÃ ±ÝÁö»óÅÂ.
                                    // 96~99: Èæµµ/¹éµµ/¹®ÆÄ/¸ðµÎ(ÀÚ¼¼ÇÑ°Ç Àß ¸ð¸£°ÚÀ½. ¾Æ´Â »ç¶÷ÀÌ Ã¤¿öÁÖ»ï)
                                    // 50: [Vina Shutdown] ÇÇ·Îµµ °øÁö(1½Ã°£¸¶´Ù Ãâ·Â)

    char				cName[13];
    char				cSay[MAX_CHAT_LENGTH];				//	Ã¤ÆÃ ¸Þ½ÃÁö( strlen + 1 : NULL Æ÷ÇÔ ) // 51Àº ÃÖ´ë±æÀÌ´Ù..º¸³¾ ¶§ Â©¶ó¼­ º¸³¿.

    void set_length()
    {
        cSay[MAX_CHAT_LENGTH - 1] = 0;
        header.sLength = sizeof(MSG_ZONE_CHAT_NORMAL) - MAX_CHAT_LENGTH + strlen(cSay) + 1;
    }
};
MSG_ZONE_CHAT_NORMAL NoteGameEventKill;
struct CMSG_SHOWTEXT_REQ {
    u_short				usLength;
    u_char				cMessage;

    char				cString[MAX_CHAT_LENGTH];
};
struct MSG_STR_BUY_SLOT_CANCEL
{
    _sHeader            header;
    u_char              ucMessage;
    u_int               uiMoney;			 
};
struct MSG_STR_BUY_SLOT_RESULT
{
    _sHeader            header;
    u_char              ucMessage;
    u_char              ucTotalUsableSlot;     // ¾µ ¼ö ÀÖ´Â ½½·Ô ÃÑ °¹¼ö.
    short				sCheckYear;
    u_char				ucCheckMonth;
    u_char				ucCheckDay;
    u_char				ucCheckHour;
    u_int               uiMoney;		   // ³²Àºµ· .
};
struct CMSG_GM_EDIT_NICK_ID
{
    u_short				usLength;
    u_char				ucMessage;
    char				cCharacName[13];
    short				sSlotNum;
    u_short				usNickID;
};
struct CMSG_GM_EDIT_PARTY {
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];			//UniqueUserID
    char				cParty;
};
struct	CMSG_GM_EDIT_CHARAC_ROLE
{
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];
    char				cClass;
};
struct	PosXYBoss
{
    float   PosX;
    float	PosY;
};
struct MARTIAL_RESULT
{
    _sHeader			header;
    u_char				ucMessage;

    u_char				ucMartialType : 4;		// ¹«°ø Å¸ÀÔ 
    u_char				ucTargetType : 3;		// ´ë»óÀÇ Å¸ÀÔ
    u_char				ucPadding1 : 1;		// ÆÐµù

    short				sLeftForce;			// »ç¿ëÈÄ ³²Àº ³»°ø
};
struct MSG_ACTIVE_RESULT_MOB : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;

    short				sAnimation;

    u_short				ucSequence : 2;		//
    u_short				usAtkInfo_1 : 3;		// atkinfo : 0 for Hit, 1 Critical, 2 Evasion, 3 Block, 4 Shock, 5, 6, 7
    u_short				usAtkInfo_2 : 3;		//
    u_short				usAtkInfo_3 : 3;		//
    u_short				usPadding : 5;			// 

    u_short				sDamage_1;
    char				cMobVitalRate_1;		//

    u_short				sDamage_2;
    char				cMobVitalRate_2;		//

    u_short				sDamage_3;
    char				cMobVitalRate_3;		//

    char				cBattleResult;			// ÀüÅõ °á°ú.
    char                xRateDmg;
    char                xAtspeed;
};
MSG_ACTIVE_RESULT_MOB actresuldmod;
struct MSG_ACTIVE_RESULT_PVP : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;


    u_char				ucPadding : 6;
    short				sAnimation;

    u_char				ucSequence : 2;
    u_short				usAtkInfo_1 : 3;		// 
    u_short				usAtkInfo_2 : 3;		//
    u_short				usAtkInfo_3 : 3;		//
    u_short				usPadding : 5;			// 

    u_short				sDamage_1;
    u_short				sDamage_2;
    u_short				sDamage_3;

    char				cBattleResult;			// EN_CHARAC_BATTLE_RESULT
    char                xRateDmg;
    char                xAtspeed;
};
MSG_ACTIVE_RESULT_PVP actresuldpvp;
struct MSG_SMASHING_RESULT_MOB : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;

    short				sSmashingSkillID;
    char				cSkillStep;

    char				cMobVitalRate;

    u_char				usAtkInfo : 3;			// atkinfo : 0 for Hit, 1 Critical, 2 Evasion, 3 Block, 4 Shock, 5, 6, 7
    u_char				ucPadding : 5;

    u_short				sDamage;

    char				cBattleResult;
    char                xRateDmg;
    char                xAtspeed;
};
MSG_SMASHING_RESULT_MOB smashingresultmob;
struct MSG_SMASHING_RESULT_PVP : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;
    short				sSmashingSkillID;
    char				cSkillStep;

    u_char				usAtkInfo : 3;			// atkinfo : 0 for Hit, 1 Critical, 2 Evasion, 3 Block, 4 Shock, 5, 6, 7
    u_char				ucPadding : 5;

    u_short				sDamage;

    char				cBattleResult;
    char                xRateDmg;
    char                xAtspeed;
};
MSG_SMASHING_RESULT_PVP smashingresultpvp;
struct MSG_ROUNDING_RESULT_TO_MOB : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;
    short				sRoundingSpellID;
    char				cSpellStep;
    char				cMobVitalRate;

    u_char				usAtkInfo : 3;
    u_char				ucPadding : 5;

    u_short				sDamage;

    char				cBattleResult;
    char                xRateDmg;
    char                xAtspeed;
};
MSG_ROUNDING_RESULT_TO_MOB roundresultmod;
struct MSG_ROUNDING_RESULT_TO_PC : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;
    short				sRoundingSpellID;
    char				cSpellStep;

    u_char				usAtkInfo : 3;
    u_char				ucPadding : 5;

    u_short				sDamage;

    char				cBattleResult;
    char                xRateDmg;
    char                xAtspeed;
};
MSG_ROUNDING_RESULT_TO_PC roundresultpvp;
MSG_ROUNDING_RESULT_TO_PC roundresultpvp2;
struct MSG_CASTING_RESULT_TO_MOB : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;
    short				sCastingSpellID;
    char				cSpellStep;
    char				cMobVitalRate;

    u_char				usAtkInfo : 3;
    u_char				ucPadding : 5;

    u_short				sDamage;			// 

    char				cBattleResult;
    char                xRateDmg;
    char                xAtspeed;
};
MSG_CASTING_RESULT_TO_MOB castingresultmod;
struct MSG_CASTING_RESULT_TO_PVP : public MARTIAL_RESULT
{
    u_short				usAttackerID;
    u_short				usTargetID;
    short				sCastingSpellID;
    char				cSpellStep;

    u_char				usAtkInfo : 3;
    u_char				ucPadding : 5;

    u_short				sDamage;			// 

    char				cBattleResult;
    char                xRateDmg;
    char                xAtspeed;
};
MSG_CASTING_RESULT_TO_PVP castingresultpvp;
struct CMSG_GM_REM_SKILL {
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];			//UniqueUserID
    short				sSkillID;
};
struct CMSG_GM_ADD_SKILL {
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];			//UniqueUserID
    short				sSkillID;
    short				sSkillStep;
    int					iSkillExp;
};
PosXYBoss toadoBoss;
struct MGS_InforCloth
{
    u_short usLength; //0x0000
    u_char ucMessage; //0x0002
    char UnknoValue; //0x0003
    char numbSlot; //0x0004
    char TypeItem; //0x0005
    char Type2; //0x0006
    short IDitem; //0x0007
    DWORD UnknoValue2; //0x0009
    char ValueEqual1; //0x000D
    DWORD UnknoValue3; //0x000E
    DWORD UnknoValue4; //0x0012
    DWORD UnknoValue5; //0x0016
    char ValueEqualFF; //0x001A
    u_short IDOpt1; //0x001B
    u_short ValueOpt1; //0x001D
    char rank1; //0x001F
    u_short IDOpt2; //0x0020
    u_short ValueOpt2; //0x0022
    char rank2; //0x0024
    u_short IDOpt3; //0x0025
    u_short ValueOpt3; //0x0027
    char rank3; //0x0029
    u_short IDOpt4; //0x002A
    u_short ValueOpt4; //0x002C
    char rank4; //0x002E
    u_short IDOpt5; //0x002F
    u_short ValueOpt5; //0x0031
    char rank5;
    u_short IDOpt6; //0x002F
    u_short ValueOpt6; //0x0031
    char rank6;

};
class SendpacketBox
{
    char pad_0000[80]; //0x0000
}; 
struct MSG_USE_ITEM_RESULT
{
    _sHeader			header;
    u_char				ucMessage;
    char				cResult;		 
    char				cInvenIndex;		
    u_char				ucCount;		

};
struct CMSG_GM_EDIT_JIN
{
    u_short				usLength;
    u_char				cMessage;

    char				cCharacName[13];
    u_int				uiJin;				// Áø
};
struct MSG_MONEY_GRAB_SUCCESS
{
    _sHeader			header;
    u_char				ucMessage;

    int					iItemWorldID;
    u_int				uiMoney;
};
struct MSG_SET_POWER
{
    _sHeader			header;
    u_char				ucMessage;				// ÇÊ¿äÇÑ°¡..
    char				cMax;					// true : ÃÖ´ë°ª ¼ÂÆÃ, false : ÇöÀç°ª ¼ÂÆÃ.
    u_int				sLifePower;			// 
    u_int				sForcePower;			//
    u_int				sConcentrationPower;			//
};
typedef char(__thiscall* gms_ctrl_add_skill)(int a1, int a2);
typedef char(__thiscall* gms_ctrl_rem_skill)(int a1, int a2);
typedef __int64(__thiscall* SM_Item_Make_UniqueID)();
typedef char(__thiscall* gms_edit_zone)(CMSG_GM_EDIT_ZONE*a1);

typedef char(__thiscall* get_name)( int a1, int a2);
gms_ctrl_add_skill gms_ctrl_add_skill1;
gms_ctrl_rem_skill gms_ctrl_rem_skill1; 
get_name get_name1;
gms_edit_zone edit_zone_gamer;
SM_Item_Make_UniqueID makeUniqueIDItem;
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
BoxLucky* g_BoxLucky = NULL;
void SendMoneyGrap(unsigned int money)
{
    DWORD STOREECX;
    MSG_MONEY_GRAB_SUCCESS pkMoneySend;
    __asm
    {
        mov STOREECX,ecx
        lea eax, pkMoneySend
        mov word ptr [eax],0xB
        mov byte ptr [eax+0x2],0x74
        mov dword ptr [eax+0x3],0x0
        mov ecx,money
        mov [eax+0x7],ecx
        lea eax, pkMoneySend
        mov cx,[eax]
        and cx,0x7FFF
        and ecx,0xFFFF
        push ecx
        lea eax, pkMoneySend
        push eax
        mov ecx, STOREECX
        mov eax,0x0069479A
        call eax
    }
    
}
void SendInforPowerUser()
{
    MSG_SET_POWER pkPowerUser;
    DWORD StoreEcx;
    __asm
    {
        
        mov StoreEcx,ecx
        push 0x3C44
        mov eax,0x0041F1A0
        call eax
        lea eax, pkPowerUser
        mov byte ptr [eax], 0x10
        mov byte ptr [eax+0x1], 0x00
        mov byte ptr [eax+0x2], 0x69
        mov byte ptr [eax+0x3], 0x00
        mov ecx, StoreEcx
        xor edx,edx
        mov edx,[ecx+0x5C00]
        mov [eax+0x4],edx
        xor edx, edx
        mov edx, [ecx + 0x5C04]
        mov[eax + 0x8], edx
        xor edx, edx
        mov edx, [ecx + 0x5C08]
        mov[eax + 0xC], edx
        push 0x3C7C
        mov ecx, StoreEcx
        mov eax,0x0041F1C0
        call eax
        lea eax, pkPowerUser
        xor edx,edx
        mov dx,[eax]
        and dx,0x7FFF
        and edx,0xFFFF
        push edx
        lea eax, pkPowerUser
        push eax
        mov ecx, StoreEcx
        mov eax,0x0069479A
        call eax

    }
}
bool callfun(void* tohook, void* ourfunc, int len)
{
    if (len < 5)
    {
        return false;
    }
    DWORD curProtection;
    VirtualProtect(tohook, len, PAGE_EXECUTE_READWRITE, &curProtection);
    memset(tohook, 0x90, len);
    DWORD relativeAddress = (DWORD)ourfunc - (DWORD)tohook - 5;
    *(BYTE*)tohook = 0xE8;
    *(DWORD*)((DWORD)tohook + 1) = relativeAddress;
    DWORD temp;
    VirtualProtect(tohook, len, curProtection, &temp);
    return true;
}
void conectTCpClient()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        cerr << "Can't Initialize winsock! Quitting" << endl;
        return;
    }

    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return;
    }

    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening 
    listen(listening, SOMAXCONN);

    // Wait for a connection
    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    char host[NI_MAXHOST];		// Client's remote name
    char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

    ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " <<
            ntohs(client.sin_port) << endl;
    }

    // Close listening socket
    closesocket(listening);

    // While loop: accept and echo message back to client
    char buf[4096];

    while (true)
    {
        ZeroMemory(buf, 4096);

        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }

        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }

        cout << string(buf, 0, bytesReceived) << endl;

        // Echo message back to client
        send(clientSocket, buf, bytesReceived + 1, 0);

    }

    // Close the socket
    closesocket(clientSocket);

    // Cleanup winsock
    WSACleanup();
}
void SendPacketBoxtoClient(int type1,int iditem, int count, int inchant)
{
    SendpacketBox SendpacketBox2;
    int item, id, countd, inc;
    item = type1;
    id = iditem;
    countd = count;
    inc = inchant;
    DWORD storeECX;
    __asm
    {
        mov storeECX,ecx
        lea eax, SendpacketBox2
        mov byte ptr[eax],0x4C
        mov byte ptr[eax+0x2], 0xF2
        mov byte ptr[eax+0x3], 0x7
        mov dword ptr[eax+0x4], 0x0
        mov dword ptr[eax+0x8], 0x0
        mov dword ptr [eax+0xC], 0x0
        mov word ptr[eax + 0x10], 0x0
        mov byte ptr[eax+0x12], 0x1
        mov byte ptr[eax + 0x13], 0x1
        mov dword ptr [eax+0x14], 0x0
        mov dword ptr [eax+0x18], 0xF00
        mov dword ptr [eax+0x1C], 0x00FF0000
        mov byte ptr [eax+0x20], 0x0
        mov ecx,type1
        mov[eax+0x21], cl
        mov word ptr[eax+0x22],0x0
        mov byte ptr [eax+0x24], 0x0
        mov ecx,iditem
        mov [eax+0x25],cx
        mov word ptr[eax+0x27], 0x0
        mov ecx,countd
        mov [eax+0x29],cl
        xor ecx,ecx
        mov ecx, inc
        mov byte ptr[eax + 0x2A],cl 
        mov byte ptr [eax + 0x2B], 0x0
        mov dword ptr[eax+0x2C], 0xA0000
        mov dword ptr[eax + 0x30], 0x30003
        mov dword ptr [eax + 0x34], 0xDB8
        mov dword ptr [eax + 0x38], 0x355
        mov dword ptr [eax + 0x3C], 0x355
        mov dword ptr [eax + 0x40], 0x3
        mov dword ptr [eax + 0x44], 0x9
        mov dword ptr [eax + 0x48], 0x9
        mov dword ptr [eax+0x4C], 0x0
        lea edx, SendpacketBox2
        mov ax,[edx]
        and ax,0x7FFF
        and eax,0xFFFF
        push eax
        lea edx, SendpacketBox2
        push edx
        mov ecx, storeECX
        mov eax,0x0069479A
        call eax

    }

}
void editZoneGame()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 17;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = -52.365f;
    newInforPacket.fZ = -210.499f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax,0x006E3CC0
        call eax
        add esp,0xC
        lea eax, newInforPacket
        push eax
        mov ecx,0x007763AC
        mov ecx,[ecx]
        call edit_zone_gamer
    }
    
}
void editZoneGame2()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 17;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = 68.802f;//-34.837f;
    newInforPacket.fZ = 38.305f;//-58.121f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, newInforPacket
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        call edit_zone_gamer
    }
}
void editZoneGame3()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 14;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = 346.277f;//-34.837f;
    newInforPacket.fZ = -410.721f;//-58.121f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, newInforPacket
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        call edit_zone_gamer
    }
}
void ChienTruongBenKim()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 11;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = -406.390f;//-34.837f;
    newInforPacket.fZ = -411.365f;//-58.121f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, newInforPacket
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        call edit_zone_gamer
    }
}
void ChienTruongBenTong()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 11;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = -292.800f;//-34.837f;
    newInforPacket.fZ = -385.757f;//-58.121f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, newInforPacket
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        call edit_zone_gamer
    }
}
void TongChienTruong()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 11;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = 141.500f;//-34.837f;
    newInforPacket.fZ = -410.524f;//-58.121f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, newInforPacket
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        call edit_zone_gamer
    }
}
void KimChienTruong()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 11;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = -36.473f;//-34.837f;
    newInforPacket.fZ = 388.494f;//-58.121f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, newInforPacket
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        call edit_zone_gamer
    }
}

/*void editZoneGame2()
{
    CMSG_GM_EDIT_ZONE newInforPacket;
    newInforPacket.cMessage = 157;
    newInforPacket.iZone = 17;
    newInforPacket.usLength = sizeof(CMSG_GM_EDIT_ZONE);
    newInforPacket.fX = 68.802f;
    newInforPacket.fZ = 38.305f;
    __asm
    {
        push 0xD
        call get_name1
        push eax
        lea eax, newInforPacket.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, newInforPacket
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        call edit_zone_gamer
    }
}*/
void AddJinUser( unsigned int Jinadd)
{
    CMSG_GM_EDIT_JIN userAdd;
    userAdd.uiJin = Jinadd;
    DWORD StoreECX;
    __asm
    {
        mov StoreECX,ecx
        push 0xD
        call get_name1
        push eax
        lea eax, userAdd.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp,0xC
        lea eax, userAdd
        push eax
        mov ecx, 0x007763AC
        mov ecx,[ecx]
        mov eax,0x0060E80B
        call eax
    }

}
void EditNickName(u_short usNickID)
{
    u_short NikcID = usNickID;
    __asm
    {
        push 0x1
        xor eax,eax
        mov ax, NikcID
        push eax
        mov eax,0x00498D59
        call eax
    }

}
void deleteItem(int numberslot)
{
    MSG_USE_ITEM_RESULT itemusedieuche;
    DWORD storeEcx;
    int result;
    __asm
    {
        mov storeEcx,ecx
        mov eax, numberslot
        imul eax, eax, 0x60
        lea edx, [ecx + eax + 0x0000128C] //Get Address Item
        xor ecx,ecx
        mov cl,[edx+0x8]
        cmp ecx,0x7
        jnz KhongVp
        xor ecx,ecx
        mov cx,[edx+0xA]
        cmp ecx,0xB43
        jz Bua100
        cmp ecx, 0xB42
        jnz KhongVp
        mov eax, 0x2
        mov result, eax
        jmp Bua50
        Bua100:
        mov eax,0x1
        mov result,eax
        Bua50:
        xor ecx,ecx
        mov cl, [edx + 0xF]
        sub cl, 0x1
        mov[edx + 0xF], cl
        cmp cl, 0x0
        jnz KoBangKhong1
        push 0x94
        mov ecx, storeEcx
        mov eax, 0x004B2960
        call eax
        KoBangKhong1 :
        lea eax, itemusedieuche
        mov byte ptr [eax], 0x06
            mov byte ptr[eax+0x1], 0x00
            mov byte ptr[eax+0x2], 0x7A
            mov byte ptr[eax + 0x3], 0x01
            mov ecx, numberslot
            mov byte ptr[eax + 0x4], cl
            imul ecx, ecx, 0x60
            mov eax, storeEcx
            lea edx, [ecx + eax + 0x0000128C]//Get Address Item

            xor ecx, ecx
            mov cl, [edx + 0xF]
            lea eax, itemusedieuche
            mov byte ptr[eax + 0x5], cl
            push 0x6
            lea eax, itemusedieuche
            push eax
            mov ecx, storeEcx
            mov eax, 0x69479A
            call eax
            mov eax, result
            jmp EndFun
            KhongVp:
            xor eax,eax
            EndFun:
    }
}
void SendMoneyData()
{
    CMSG_GM_ADD_INVGOLD UserItemAddSlot;
    UserItemAddSlot.usLength = 20;
    UserItemAddSlot.cMessage = 166;

    DWORD StoreECX = 0;
    int storemoney = 0;
    __asm
    {
        mov StoreECX, ecx
        push 0x1
        mov eax, 0x50F9E2
        call eax
        mov storemoney, eax
        push 0x00
        mov ecx, StoreECX
        mov eax, 0x050FA03
        call eax

        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, UserItemAddSlot
        lea eax,[eax+0x3]
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp,0xC
        mov eax, storemoney
        cmp eax, 0x77359400
        jnbe AddTwoTimes
        lea ecx, UserItemAddSlot
        mov [ecx+ 0x10], eax
        lea eax, UserItemAddSlot
        mov byte ptr [ecx+0x2], 0xA6
        mov byte ptr [ecx], 0x14
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x0060E1A9
        call eax
        jmp EndAdd
        AddTwoTimes :
        sbb eax, 0x77359400
            lea ecx, UserItemAddSlot
            mov[ecx + 0x10], eax
            lea eax, UserItemAddSlot
            mov byte ptr[ecx + 0x2], 0xA6
            mov byte ptr[ecx], 0x14
            push eax
            mov ecx, 0x007763AC
            mov ecx, [ecx]
            mov eax, 0x0060E1A9
            call eax
            //
            mov eax, 0x77359400
            lea ecx, UserItemAddSlot
            mov[ecx + 0x10], eax
            lea eax, UserItemAddSlot
            mov byte ptr[ecx + 0x2], 0xA6
            mov byte ptr[ecx], 0x14
            push eax
            mov ecx, 0x007763AC
            mov ecx, [ecx]
            mov eax, 0x0060E1A9
            call eax


            EndAdd :
    }
}
void SendInforCloth(int Slotnum)
{
    MGS_InforCloth SendInforClothes;
    SendInforClothes.usLength = 94;
    SendInforClothes.ucMessage = 159;
    SendInforClothes.UnknoValue = 31;
    int numberslot = 0;
    numberslot = Slotnum;
    DWORD StoreECX = 0;
    int storemoney = 0;
    __asm
    {
        lea edx, SendInforClothes
        mov eax, numberslot
        mov StoreECX, ecx
        mov eax, numberslot
        mov SendInforClothes.numbSlot, al
        imul eax, 0x60
        xor ebx,ebx
        mov bl, [ecx + 0x128C + eax + 0x8]
        mov [edx+0x5], bl
        xor ebx, ebx
        mov bl, [ecx + 0x128C + eax + 0x9]
        mov[edx + 0x6], bl
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0xA]
        mov[edx + 0x7], bx
        xor ebx, ebx
        mov ebx, [ecx + 0x128C + eax + 0xC]
        mov[edx + 0x9], ebx
        mov byte ptr[edx + 0x1A], 0xFF
        mov byte ptr [edx + 0xD], 0x01
        mov dword ptr [edx + 0xE], 0x00
        mov dword ptr[edx + 0x12], 0x00
        mov dword ptr[edx + 0x16], 0x00
        //Opt 1
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x24]
        mov[edx + 0x1B], bx
        //Value 1
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x26]
        mov[edx + 0x1D], bx
        //Rank 1
        xor ebx, ebx
        mov bl, [ecx + 0x128C + eax + 0x28]
        mov[edx + 0x1F], bl
        ///2
        //Opt 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x29]
        mov[edx + 0x20], bx
        //Value 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x2B]
        mov[edx + 0x22], bx
        //Rank 2
        xor ebx, ebx
        mov bl, [ecx + 0x128C + eax + 0x2D]
        mov[edx + 0x24], bl
        ///3 
        //Opt 3
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x2E]
        mov[edx + 0x25], bx
        //Value 3
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x30]
        mov[edx + 0x27], bx
        //Rank 3
        xor ebx, ebx
        mov bl, [ecx + 0x128C + eax + 0x32]
        mov[edx + 0x29], bl
        ///4
        //Opt 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x33]
        mov[edx + 0x2A], bx
        //Value 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x35]
        mov[edx + 0x2C], bx
        //Rank 2
        xor ebx, ebx
        mov bl, [ecx + 0x128C + eax + 0x37]
        mov[edx + 0x2E], bl

        ///5
        //Opt 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x38]
        mov[edx + 0x2F], bx
        //Value 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x3A]
        mov[edx + 0x31], bx
        //Rank 2
        xor ebx, ebx
        mov bl, [ecx + 0x128C + eax + 0x3C]
        mov[edx + 0x33], bl
        ///5
        //Opt 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x3D]
        mov[edx + 0x34], bx
        //Value 2
        xor ebx, ebx
        mov bx, [ecx + 0x128C + eax + 0x3F]
        mov[edx + 0x36], bx
        //Rank 2
        xor ebx, ebx
        mov bl, [ecx + 0x128C + eax + 0x41]
        mov[edx + 0x38], bl

        xor eax,eax
        mov ax, SendInforClothes.usLength
        push eax
        lea eax, SendInforClothes
        push eax
        mov eax, 0x0069479A
        call eax
    }
}
struct CMSG_GM_EDIT_LEVEL {
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];
    int					iLevel;
};
void EditLevelGM(int ilevel)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    CMSG_GM_EDIT_LEVEL ChangeLevelUser;
    memset(&ChangeLevelUser, 0, sizeof(CMSG_GM_EDIT_LEVEL));
    ChangeLevelUser.usLength = sizeof(CMSG_GM_EDIT_LEVEL);
    ChangeLevelUser.cMessage = 166;
    __asm
    {
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, ChangeLevelUser.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov eax, ilevel
        mov ChangeLevelUser.iLevel, eax
        lea eax, ChangeLevelUser
        push eax
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov eax, 0x0060CD8C
        call eax
    }
}
void AddMoneyForEvent(int addMoney)
{
    DWORD storeECX;
    __asm
    {
        mov storeECX,ecx
        mov eax, 0x50F9E2
        call eax
        cmp eax,0xD09DC300
        ja MaxMoney
        mov ecx, addMoney
        cmp ecx, 0x20C85580
        ja MaxMoney
        add eax,ecx
        push 0x1
        push eax
        mov ecx, storeECX
        mov eax, 0x050FA03
        call eax
        MaxMoney:
        mov ecx, storeECX
        mov eax, 0x50F9E2
        call eax    
        push eax
        mov ecx, storeECX
        call SendMoneyGrap
        add esp, 0x4
    }
}
void ChangeParty(int partyID)
{
    CMSG_GM_EDIT_PARTY ChangePartyUser;
    ChangePartyUser.usLength = 20;
    ChangePartyUser.cMessage = 166;

    DWORD StoreECX = 0;
    char storemoney = partyID;
    __asm
    {
        mov StoreECX, ecx
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, ChangePartyUser.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp,0xC
        mov al, storemoney
        mov ChangePartyUser.cParty, al
        lea eax, ChangePartyUser
        mov byte ptr ChangePartyUser.cMessage, 0xA6
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x0060D903
        call eax
    }
}
void ChangeClass(int classId)
{
    CMSG_GM_EDIT_CHARAC_ROLE ChangeClassUser;
    ChangeClassUser.usLength = 20;
    ChangeClassUser.cMessage = 166;

    DWORD StoreECX = 0;
    char storemoney = classId;
    __asm
    {
        mov StoreECX, ecx
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, ChangeClassUser.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp,0xC
        mov al, storemoney
        mov ChangeClassUser.cClass, al
        lea eax, ChangeClassUser
        mov byte ptr ChangeClassUser.cMessage, 0xA6
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x0060E67E
        call eax
    }
}
struct CMSG_GM_REM_INVITEM {
    u_short				usLength;
    u_char				cMessage;
    char				cCharacName[13];			//UniqueUserID
    char				cFirstType;
    char				cSecondType;
    short				sItemID;
    u_char				ucSlotNo;
};
struct DataUseItem {
    int idTypeTuiBot;
    int IdTuiBot;
    int CountTuiBot;
    //
    int idTypeTuiDuong;
    int IdTuiDuong;
    int CountTuiDuong;
    //
    int idTypeTuiTrung;
    int IdTuiTrung;
    int CountTuiTrung;
    //
    int idTypeTuiDauXanh;
    int IdTuiDauXanh;
    int CountTuiDauXanh;
    //
    int idTypeTuiHatSen;
    int IdTuiHatSen;
    int CountTuiHatSen;
    //
    int idTypeBanhSen;
    int IdBanhSen;
    int CountBanhSen;
    //
    int idTypeBanhGa;
    int IdBanhGa;
    int CountBanhGa;
    //
    int idTypeBanhHeo;
    int IdBanhHeo;
    int CountBanhHeo;
    //
    int idTypeBanh100;
    int IdBanh100;
    int CountBanh100;
    //
    int idTypeBanh500;
    int IdBanh500;
    int CountBanh500;
    //
    int idTypeBanh1Tr;
    int IdBanh1Tr;
    int CountBanh1Tr;
    //
    int idTypeBanh2Tr;
    int IdBanh2Tr;
    int CountBanh2Tr;
    //
    int idTypeBanh3Tr;
    int IdBanh3Tr;
    int CountBanh3Tr;
    //
    int idTypeBanh4Tr;
    int IdBanh4Tr;
    int CountBanh4Tr;
    //
    int idTypeBanh5Tr;
    int IdBanh5Tr;
    int CountBanh5Tr;
};
#define Test_Open_File "UserInfo/88854.txt"
bool ReadData(DataUseItem& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/%d.txt", UniqueID);
    DataUseItem* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    int idTypeTuiBotvalue;
    int IdTuiBotvalue;
    int CountTuiBotvalue;
    //
    int idTypeTuiDuongvalue;
    int IdTuiDuongvalue;
    int CountTuiDuongvalue;
    //
    int idTypeTuiTrungvalue;
    int IdTuiTrungvalue;
    int CountTuiTrungvalue;
    //
    int idTypeTuiDauXanhvalue;
    int IdTuiDauXanhvalue;
    int CountTuiDauXanhvalue;
    //
    int idTypeTuiHatSenvalue;
    int IdTuiHatSenvalue;
    int CountTuiHatSenvalue;
    //
    int idTypeBanhSenvalue;
    int IdBanhSenvalue;
    int CountBanhSenvalue;
    //
    int idTypeBanhGavalue;
    int IdBanhGavalue;
    int CountBanhGavalue;
    //
    int idTypeBanhHeovalue;
    int IdBanhHeovalue;
    int CountBanhHeovalue;
    //
    int idTypeBanh100value;
    int IdBanh100value;
    int CountBanh100value;
    //
    int idTypeBanh500value;
    int IdBanh500value;
    int CountBanh500value;
    //
    int idTypeBanh1Trvalue;
    int IdBanh1Trvalue;
    int CountBanh1Trvalue;
    //
    int idTypeBanh2Trvalue;
    int IdBanh2Trvalue;
    int CountBanh2Trvalue;
    //
    int idTypeBanh3Trvalue;
    int IdBanh3Trvalue;
    int CountBanh3Trvalue;
    //
    int idTypeBanh4Trvalue;
    int IdBanh4Trvalue;
    int CountBanh4Trvalue;
    //
    int idTypeBanh5Trvalue;
    int IdBanh5Trvalue;
    int CountBanh5Trvalue;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        FILE* fp = fopen(fname, "w");
        fclose(fp);
        goto OutFun;
    }
    while (1)
    {
        ++iLine;
        if (fgets(line,256,fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        //rewind(fp);
        sscanf(line, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
            &idTypeTuiBotvalue, &IdTuiBotvalue, &CountTuiBotvalue,
            &idTypeTuiDuongvalue, &IdTuiDuongvalue, &CountTuiDuongvalue,
            &idTypeTuiTrungvalue, &IdTuiTrungvalue, &CountTuiTrungvalue,
            &idTypeTuiDauXanhvalue, &IdTuiDauXanhvalue, &CountTuiDauXanhvalue,
            &idTypeTuiHatSenvalue, &IdTuiHatSenvalue, &CountTuiHatSenvalue,
            &idTypeBanhSenvalue, &IdBanhSenvalue, &CountBanhSenvalue,
            &idTypeBanhGavalue, &IdBanhGavalue, &CountBanhGavalue,
            &idTypeBanhHeovalue, &IdBanhHeovalue, &CountBanhHeovalue,
            &idTypeBanh100value, &IdBanh100value, &CountBanh100value,
            &idTypeBanh500value, &IdBanh500value, &CountBanh500value,
            &idTypeBanh1Trvalue, &IdBanh1Trvalue, &CountBanh1Trvalue,
            &idTypeBanh2Trvalue, &IdBanh2Trvalue, &CountBanh2Trvalue,
            &idTypeBanh3Trvalue, &IdBanh3Trvalue, &CountBanh3Trvalue,
            &idTypeBanh4Trvalue, &IdBanh4Trvalue, &CountBanh4Trvalue,
            &idTypeBanh5Trvalue, &IdBanh5Trvalue, &CountBanh5Trvalue
            );
        InnforUserLoad->idTypeTuiBot = idTypeTuiBotvalue;
        InnforUserLoad->IdTuiBot = IdTuiBotvalue;
        InnforUserLoad->CountTuiBot = CountTuiBotvalue;
        //
        InnforUserLoad->idTypeTuiDuong = idTypeTuiDuongvalue;
        InnforUserLoad->IdTuiDuong = IdTuiDuongvalue;
        InnforUserLoad->CountTuiDuong = CountTuiDuongvalue;
        //
        InnforUserLoad->idTypeTuiTrung = idTypeTuiTrungvalue;
        InnforUserLoad->IdTuiTrung = IdTuiTrungvalue;
        InnforUserLoad->CountTuiTrung = CountTuiTrungvalue;
        //
        InnforUserLoad->idTypeTuiDauXanh = idTypeTuiDauXanhvalue;
        InnforUserLoad->IdTuiDauXanh = IdTuiDauXanhvalue;
        InnforUserLoad->CountTuiDauXanh = CountTuiDauXanhvalue;
        //
        InnforUserLoad->idTypeTuiHatSen = idTypeTuiHatSenvalue;
        InnforUserLoad->IdTuiHatSen = IdTuiHatSenvalue;
        InnforUserLoad->CountTuiHatSen = CountTuiHatSenvalue;
        //
        InnforUserLoad->idTypeBanhSen = idTypeBanhSenvalue;
        InnforUserLoad->IdBanhSen = IdBanhSenvalue;
        InnforUserLoad->CountBanhSen = CountBanhSenvalue;
        //
        InnforUserLoad->idTypeBanhGa = idTypeBanhGavalue;
        InnforUserLoad->IdBanhGa = IdBanhGavalue;
        InnforUserLoad->CountBanhGa = CountBanhGavalue;
        //
        InnforUserLoad->idTypeBanhHeo = idTypeBanhHeovalue;
        InnforUserLoad->IdBanhHeo = IdBanhHeovalue;
        InnforUserLoad->CountBanhHeo = CountBanhHeovalue;
        //
        InnforUserLoad->idTypeBanh100 = idTypeBanh100value;
        InnforUserLoad->IdBanh100 = IdBanh100value;
        InnforUserLoad->CountBanh100 = CountBanh100value;
        //
        InnforUserLoad->idTypeBanh500 = idTypeBanh500value;
        InnforUserLoad->IdBanh500 = IdBanh500value;
        InnforUserLoad->CountBanh500 = CountBanh500value;
        //
        InnforUserLoad->idTypeBanh1Tr = idTypeBanh1Trvalue;
        InnforUserLoad->IdBanh1Tr = IdBanh1Trvalue;
        InnforUserLoad->CountBanh1Tr = CountBanh1Trvalue;
        //
        InnforUserLoad->idTypeBanh2Tr = idTypeBanh2Trvalue;
        InnforUserLoad->IdBanh2Tr = IdBanh2Trvalue;
        InnforUserLoad->CountBanh2Tr = CountBanh2Trvalue;
        //
        InnforUserLoad->idTypeBanh3Tr = idTypeBanh3Trvalue;
        InnforUserLoad->IdBanh3Tr = IdBanh3Trvalue;
        InnforUserLoad->CountBanh3Tr = CountBanh3Trvalue;
        //
        InnforUserLoad->idTypeBanh4Tr = idTypeBanh4Trvalue;
        InnforUserLoad->IdBanh4Tr = IdBanh4Trvalue;
        InnforUserLoad->CountBanh4Tr = CountBanh4Trvalue;
        //
        InnforUserLoad->idTypeBanh5Tr = idTypeBanh5Trvalue;
        InnforUserLoad->IdBanh5Tr = IdBanh5Trvalue;
        InnforUserLoad->CountBanh5Tr = CountBanh5Trvalue;
        returninfo = true;
    }
    fclose(fp);
OutFun:
    return returninfo;
}
bool WriteData(DataUseItem& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/%d.txt", UniqueID);
    DataUseItem* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    FILE* fp = fopen(fname, "w");
    if (fp)
    {
        fprintf(fp, "%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u",
            InnforUserLoad->idTypeTuiBot, InnforUserLoad->IdTuiBot, InnforUserLoad->CountTuiBot,
            InnforUserLoad->idTypeTuiDuong, InnforUserLoad->IdTuiDuong, InnforUserLoad->CountTuiDuong,
            InnforUserLoad->idTypeTuiTrung, InnforUserLoad->IdTuiTrung, InnforUserLoad->CountTuiTrung,
            InnforUserLoad->idTypeTuiDauXanh, InnforUserLoad->IdTuiDauXanh, InnforUserLoad->CountTuiDauXanh,
            InnforUserLoad->idTypeTuiHatSen, InnforUserLoad->IdTuiHatSen, InnforUserLoad->CountTuiHatSen,
            InnforUserLoad->idTypeBanhSen, InnforUserLoad->IdBanhSen, InnforUserLoad->CountBanhSen,
            InnforUserLoad->idTypeBanhGa, InnforUserLoad->IdBanhGa, InnforUserLoad->CountBanhGa,
            InnforUserLoad->idTypeBanhHeo, InnforUserLoad->IdBanhHeo, InnforUserLoad->CountBanhHeo,
            InnforUserLoad->idTypeBanh100, InnforUserLoad->IdBanh100, InnforUserLoad->CountBanh100,
            InnforUserLoad->idTypeBanh500, InnforUserLoad->IdBanh500, InnforUserLoad->CountBanh500,
            InnforUserLoad->idTypeBanh1Tr, InnforUserLoad->IdBanh1Tr, InnforUserLoad->CountBanh1Tr,
            InnforUserLoad->idTypeBanh2Tr, InnforUserLoad->IdBanh2Tr, InnforUserLoad->CountBanh2Tr,
            InnforUserLoad->idTypeBanh3Tr, InnforUserLoad->IdBanh3Tr, InnforUserLoad->CountBanh3Tr,
            InnforUserLoad->idTypeBanh4Tr, InnforUserLoad->IdBanh4Tr, InnforUserLoad->CountBanh4Tr,
            InnforUserLoad->idTypeBanh5Tr, InnforUserLoad->IdBanh5Tr, InnforUserLoad->CountBanh5Tr
        );
        //fwrite(InnforUserLoad, sizeof(int), sizeof(DataUseItem), fp);
        returninfo = true;
        fclose(fp);
    }
    else
    {
        std::cout << "Error Create File and Write" << std::endl;
    }
       
    return returninfo;
}
struct InforUserTK
{
    int nPhe;
    int nDiem;
    int nNguoi;
    int nLienTram;
};
bool ReadTongKim(InforUserTK& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/EventTK/%d.txt", UniqueID);
    InforUserTK* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    int idPhe;
    int IdDiem;
    int vNguoi;
    int vLienTram;

    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        FILE* fp = fopen(fname, "w");
        fclose(fp);
        goto OutFun;
    }
    while (1)
    {
        ++iLine;
        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        //rewind(fp);
        sscanf(line, "%d %d %d %d",
             &idPhe, &IdDiem, &vNguoi,&vLienTram
        );
        InnforUserLoad->nPhe = idPhe;
        InnforUserLoad->nDiem = IdDiem;
        InnforUserLoad->nNguoi = vNguoi;
        InnforUserLoad->nLienTram = vLienTram;
        returninfo = true;
    }
    fclose(fp);
OutFun:
    return returninfo;
}
struct UserData {
    int iRankLevel;
    int countQLLSolo;
    int countQLLParty;
    int nDiemTichLuy;
    int nDiemHoatDodng;
    int flagDay;
};
bool ReadInforUserChar(UserData& nUserData, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InfoUserDB/%d.txt", UniqueID);
    UserData* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &nUserData;
    int iLine = 0;
    char line[256];
    string filname;
    int RankLevel;
    int icountQLLSolo;
    int icountQLLParty;
    int iDiemTichLuy;
    int iDiemHoatDodng;
    int iflagday;

    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        FILE* fp = fopen(fname, "w");
        fclose(fp);
        goto OutFun;
    }
    while (1)
    {
        ++iLine;
        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        //rewind(fp);
        sscanf(line, "%d %d %d %d %d %d",
            &RankLevel, &icountQLLSolo, &icountQLLParty, &iDiemTichLuy,&iDiemHoatDodng,&iflagday
        );
        InnforUserLoad->iRankLevel = RankLevel;
        InnforUserLoad->countQLLSolo = icountQLLSolo;
        InnforUserLoad->countQLLParty = icountQLLParty;
        InnforUserLoad->nDiemTichLuy = iDiemTichLuy;
        InnforUserLoad->nDiemHoatDodng = iDiemHoatDodng;
        InnforUserLoad->flagDay = iflagday;
        returninfo = true;
    }
    fclose(fp);
OutFun:
    return returninfo;
}
bool WriteDataInforUser(UserData& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InfoUserDB/%d.txt", UniqueID);
    UserData* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    FILE* fp = fopen(fname, "w");
    if (fp)
    {
        fprintf(fp, "%u %u %u %u %u %u",
            InnforUserLoad->iRankLevel, InnforUserLoad->countQLLSolo, InnforUserLoad->countQLLParty, InnforUserLoad->nDiemTichLuy, InnforUserLoad->nDiemHoatDodng, InnforUserLoad->flagDay
        );
        //fwrite(InnforUserLoad, sizeof(int), sizeof(DataUseItem), fp);
        returninfo = true;
        fclose(fp);
    }
    else
    {
        std::cout << "Error Create File and Write" << std::endl;
    }

    return returninfo;
}
bool WriteDataTongKim(InforUserTK& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/EventTK/%d.txt", UniqueID);
    InforUserTK* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    FILE* fp = fopen(fname, "w");
    if (fp)
    {
        fprintf(fp, "%u %u %u %u",
            InnforUserLoad->nPhe, InnforUserLoad->nDiem, InnforUserLoad->nNguoi, InnforUserLoad->nLienTram
        );
        //fwrite(InnforUserLoad, sizeof(int), sizeof(DataUseItem), fp);
        returninfo = true;
        fclose(fp);
    }
    else
    {
        std::cout << "Error Create File and Write" << std::endl;
    }

    return returninfo;
}
bool ReadDataTongKim()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    InforUserTK InnforUserLoad;
    __asm
    {
        xor eax, eax
        mov ecx, StoreEcx
        mov eax, [ecx + 0x1054]
        push eax
        lea eax, InnforUserLoad
        push eax
        call ReadTongKim
        add esp, 0x8
        test eax, eax
        jz CreateNewFile
        mov ecx, StoreEcx
        lea edx, InnforUserLoad
        xor eax, eax
        mov eax, [edx]
        mov[ecx + 0xD625], al
        xor eax, eax
        mov eax, [edx + 0x4]
        mov[ecx + 0xD626], eax
        xor eax, eax
        mov eax, [edx + 0x8]
        mov[ecx + 0xD632], eax
        xor eax, eax
        mov eax, [edx + 0xC]
        mov[ecx + 0xD62A], eax
 
        CreateNewFile :

    }
    return returnresult;
}
bool ReadDataUserAnother()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    UserData InnforUserLoad;
    __asm
    {
        xor eax, eax
        mov ecx, StoreEcx
        mov eax, [ecx + 0x1054]
        push eax
        lea eax, InnforUserLoad
        push eax
        call ReadInforUserChar
        add esp, 0x8
        test eax, eax
        jz CreateNewFile
        mov ecx, StoreEcx
        lea edx, InnforUserLoad
        xor eax, eax
        mov eax, [edx]
        mov[ecx + 0xD63E], al
        xor eax, eax
        mov eax, [edx + 0x4]
        mov[ecx + 0xD63F], al
        xor eax, eax
        mov eax, [edx + 0x8]
        mov[ecx + 0xD640], al
        xor eax, eax
        mov eax, [edx + 0xC]
        mov[ecx + 0xD641], eax
        xor eax, eax
        mov eax, [edx + 0x10]
        mov[ecx + 0xD645], eax
        xor eax, eax
        mov eax, [edx + 0x14]
        mov[ecx + 0xD64A], al

        CreateNewFile :

    }
    return returnresult;
}
bool ReadDataBaseUser()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    DataUseItem InnforUserLoad;
    __asm
    {
        xor eax,eax
        mov ecx, StoreEcx
        mov eax,[ecx+0x1054]
        push eax
        lea eax, InnforUserLoad
        push eax
        call ReadData
        add esp,0x8
        test eax,eax
        jz CreateNewFile
        mov ecx, StoreEcx
        lea edx, InnforUserLoad
        xor eax,eax
        mov eax,[edx]
        mov [ecx+0xD5D1],al
        xor eax, eax
        mov eax, [edx+0x4]
        mov[ecx + 0xD5D2], ax
        xor eax, eax
        mov eax, [edx+0x8]
        mov[ecx + 0xD5D4], ax
        //
        xor eax, eax
        mov eax, [edx+0xC]
        mov[ecx + 0xD5D6], al
        xor eax, eax
        mov eax, [edx + 0x10]
        mov[ecx + 0xD5D7], ax
        xor eax, eax
        mov eax, [edx + 0x14]
        mov[ecx + 0xD5D9], ax
        //
        xor eax, eax
        mov eax, [edx+0x18]
        mov[ecx + 0xD5DB], al
        xor eax, eax
        mov eax, [edx + 0x1C]
        mov[ecx + 0xD5DC], ax
        xor eax, eax
        mov eax, [edx + 0x20]
        mov[ecx + 0xD5DE], ax
        ///////
        xor eax, eax
        mov eax, [edx+0x24]
        mov[ecx + 0xD5E1], al
        xor eax, eax
        mov eax, [edx + 0x28]
        mov[ecx + 0xD5E2], ax
        xor eax, eax
        mov eax, [edx + 0x2C]
        mov[ecx + 0xD5E4], ax
        //
        xor eax, eax
        mov eax, [edx + 0x30]
        mov[ecx + 0xD5E6], al
        xor eax, eax
        mov eax, [edx + 0x34]
        mov[ecx + 0xD5E7], ax
        xor eax, eax
        mov eax, [edx + 0x38]
        mov[ecx + 0xD5E9], ax
        //
        xor eax, eax
        mov eax, [edx + 0x3C]
        mov[ecx + 0xD5EB], al
        xor eax, eax
        mov eax, [edx + 0x40]
        mov[ecx + 0xD5EC], ax
        xor eax, eax
        mov eax, [edx + 0x44]
        mov[ecx + 0xD5EE], ax
        ///////////
        xor eax, eax
        mov eax, [edx+0x48]
        mov[ecx + 0xD5F1], al
        xor eax, eax
        mov eax, [edx + 0x4C]
        mov[ecx + 0xD5F2], ax
        xor eax, eax
        mov eax, [edx + 0x50]
        mov[ecx + 0xD5F4], ax
        //
        xor eax, eax
        mov eax, [edx + 0x54]
        mov[ecx + 0xD5F6], al
        xor eax, eax
        mov eax, [edx + 0x58]
        mov[ecx + 0xD5F7], ax
        xor eax, eax
        mov eax, [edx + 0x5C]
        mov[ecx + 0xD5F9], ax
        //
        xor eax, eax
        mov eax, [edx + 0x60]
        mov[ecx + 0xD5FB], al
        xor eax, eax
        mov eax, [edx + 0x64]
        mov[ecx + 0xD5FC], ax
        xor eax, eax
        mov eax, [edx + 0x68]
        mov[ecx + 0xD5FE], ax
        /////////
            xor eax, eax
            mov eax, [edx+0x6C]
            mov[ecx + 0xD601], al
            xor eax, eax
            mov eax, [edx + 0x70]
            mov[ecx + 0xD602], ax
            xor eax, eax
            mov eax, [edx + 0x74]
            mov[ecx + 0xD604], ax
            //
            xor eax, eax
            mov eax, [edx + 0x78]
            mov[ecx + 0xD606], al
            xor eax, eax
            mov eax, [edx + 0x7C]
            mov[ecx + 0xD607], ax
            xor eax, eax
            mov eax, [edx + 0x80]
            mov[ecx + 0xD609], ax
            //
            xor eax, eax
            mov eax, [edx + 0x84]
            mov[ecx + 0xD60B], al
            xor eax, eax
            mov eax, [edx + 0x88]
            mov[ecx + 0xD60C], ax
            xor eax, eax
            mov eax, [edx + 0x8C]
            mov[ecx + 0xD60E], ax
        //////////
            xor eax, eax
            mov eax, [edx+0x90]
            mov[ecx + 0xD611], al
            xor eax, eax
            mov eax, [edx + 0x94]
            mov[ecx + 0xD612], ax
            xor eax, eax
            mov eax, [edx + 0x98]
            mov[ecx + 0xD614], ax
            //
            xor eax, eax
            mov eax, [edx + 0x9C]
            mov[ecx + 0xD616], al
            xor eax, eax
            mov eax, [edx + 0xA0]
            mov[ecx + 0xD617], ax
            xor eax, eax
            mov eax, [edx + 0xA4]
            mov[ecx + 0xD619], ax
            //
            xor eax, eax
            mov eax, [edx + 0xA8]
            mov[ecx + 0xD61B], al
            xor eax, eax
            mov eax, [edx + 0xAC]
            mov[ecx + 0xD61C], ax
            xor eax, eax
            mov eax, [edx + 0xB0]
            mov[ecx + 0xD61E], ax


        CreateNewFile:
        
    }
    return returnresult;
}
struct OptionofItem
{
    u_short   IdOption1;
    u_short   ValueOption1;
    u_char    RankOption1;
};
union __item_or_money
{
    struct
    {
        u_short	 usCurDur;			  // ÇöÀç ³»±¸·Â
        char	 cIdentify : 4;	  // °¨Á¤ »óÅÂ
        u_char   ucSocketCount : 4;   // ¼ÒÄÏÀÌ ¸î°³±îÁö ¶Õ¸± ¼ö ÀÖ´Â°¡?
        u_char   ucCount;			  // ÃÖ´ë ¸ÓÁö 255°³
    };

    u_int	 uiMoney;	 		  // ¸Ó´Ï..

};
struct InvenItemSlot
{
    u_int64					ui64UniqueId;	// 8 
    char					cType;			// ¾ÆÀÌÅÛ ´ëºÐ·ù 9
    char					cSecond;		// Second´Â ÃÊ±âÈ­ µÉ ¶§¸¶´Ù, »õ·ÎÀÌ ¼³Á¤ÇÑ´Ù.
    short					sID;			// ¾ÆÀÌÅÛ ¼ÒºÐ·ù. (¾ÆÀÌÅÛ ¾ÆÀÌµð) 12
    char					sunKnow1;			// ¾ÆÀÌÅÛ ¼ÒºÐ·ù. (¾ÆÀÌÅÛ ¾ÆÀÌµð) 12	
    char					sunKnow2;			// ¾ÆÀÌÅÛ ¼ÒºÐ·ù. (¾ÆÀÌÅÛ ¾ÆÀÌµð) 12	
    char					sunKnow3;			// ¾ÆÀÌÅÛ ¼ÒºÐ·ù. (¾ÆÀÌÅÛ ¾ÆÀÌµð) 12	
    char                    sCount;
    short                   sSocket[7];		// 24
    u_char				    ucYear;		// Year - 1900 : 5 ~ ½ÃÀÛ.
    u_char				    ucMonth;		// Month
    u_char				    ucDay;			// Day
    u_char				    ucHour;		// Hour
    u_char				    ucMinute;		// Minute 
    u_char				    sunKnow4;		// Year - 1900 : 5 ~ ½ÃÀÛ.
    OptionofItem            InforMoreOption[7];

    inline InvenItemSlot()
    {
        ::ZeroMemory(this, sizeof(InvenItemSlot));
    }
};
bool StoreDataUse()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    DataUseItem InnforUserLoad;
    __asm
    {
        xor eax, eax
        mov ecx, StoreEcx
        lea edx, InnforUserLoad
        xor eax,eax
        mov al,[ecx + 0xD5D1]
        mov [edx],eax
        xor eax, eax
        mov ax,[ecx + 0xD5D2]
        mov [edx+0x4], eax
        xor eax, eax
        mov ax,[ecx + 0xD5D4]
        mov [edx+0x8], eax
        //
        xor eax, eax
        mov al,[ecx + 0xD5D6]
        mov [edx+0xC], eax
        xor eax, eax
        mov ax,[ecx + 0xD5D7]
        mov[edx+0x10], eax
        xor eax, eax
        mov ax,[ecx + 0xD5D9]
        mov[edx+0x14], eax
        //
        xor eax, eax
        mov al,[ecx + 0xD5DB]
        mov [edx+0x18], eax
        xor eax, eax
        mov ax,[ecx + 0xD5DC]
        mov [edx+0x1C], eax
        xor eax, eax
        mov ax,[ecx + 0xD5DE]
        mov [edx+0x20], eax
        ///////
        xor eax, eax
        mov al, [ecx + 0xD5E1]
        mov[edx+0x24], eax
        xor eax, eax
        mov ax, [ecx + 0xD5E2]
        mov[edx + 0x28], eax
        xor eax, eax
        mov ax, [ecx + 0xD5E4]
        mov[edx + 0x2C], eax
        //
        xor eax, eax
        mov al, [ecx + 0xD5E6]
        mov[edx + 0x30], eax
        xor eax, eax
        mov ax, [ecx + 0xD5E7]
        mov[edx + 0x34], eax
        xor eax, eax
        mov ax, [ecx + 0xD5E9]
        mov[edx + 0x38], eax
        //
        xor eax, eax
        mov al, [ecx + 0xD5EB]
        mov[edx + 0x3C], eax
        xor eax, eax
        mov ax, [ecx + 0xD5EC]
        mov[edx + 0x40], eax
        xor eax, eax
        mov ax, [ecx + 0xD5EE]
        mov[edx + 0x44], eax
        ////////
        xor eax, eax
        mov al, [ecx + 0xD5F1]
        mov[edx+0x48], eax
        xor eax, eax
        mov ax, [ecx + 0xD5F2]
        mov[edx + 0x4C], eax
        xor eax, eax
        mov ax, [ecx + 0xD5F4]
        mov[edx + 0x50], eax
        //
        xor eax, eax
        mov al, [ecx + 0xD5F6]
        mov[edx + 0x54], eax
        xor eax, eax
        mov ax, [ecx + 0xD5F7]
        mov[edx + 0x58], eax
        xor eax, eax
        mov ax, [ecx + 0xD5F9]
        mov[edx + 0x5C], eax
        //
        xor eax, eax
        mov al, [ecx + 0xD5FB]
        mov[edx + 0x60], eax
        xor eax, eax
        mov ax, [ecx + 0xD5FC]
        mov[edx + 0x64], eax
        xor eax, eax
        mov ax, [ecx + 0xD5FE]
        mov[edx + 0x68], eax
        ///////
        xor eax, eax
        mov al, [ecx + 0xD601]
        mov[edx+0x6C], eax
        xor eax, eax
        mov ax, [ecx + 0xD602]
        mov[edx + 0x70], eax
        xor eax, eax
        mov ax, [ecx + 0xD604]
        mov[edx + 0x74], eax
        //
        xor eax, eax
        mov al, [ecx + 0xD606]
        mov[edx + 0x78], eax
        xor eax, eax
        mov ax, [ecx + 0xD607]
        mov[edx + 0x7C], eax
        xor eax, eax
        mov ax, [ecx + 0xD609]
        mov[edx + 0x80], eax
        //
        xor eax, eax
        mov al, [ecx + 0xD60B]
        mov[edx + 0x84], eax
        xor eax, eax
        mov ax, [ecx + 0xD60C]
        mov[edx + 0x88], eax
        xor eax, eax
        mov ax, [ecx + 0xD60E]
        mov[edx + 0x8C], eax
        //////////
        xor eax, eax
        mov al, [ecx + 0xD611]
        mov[edx+0x90], eax
        xor eax, eax
        mov ax, [ecx + 0xD612]
        mov[edx + 0x94], eax
        xor eax, eax
        mov ax, [ecx + 0xD614]
        mov[edx + 0x98], eax
            //
        xor eax, eax
        mov al, [ecx + 0xD616]
        mov[edx + 0x9C], eax
        xor eax, eax
        mov ax, [ecx + 0xD617]
        mov[edx + 0xA0], eax
        xor eax, eax
        mov ax, [ecx + 0xD619]
        mov[edx + 0xA4], eax
            //
        xor eax, eax
        mov al, [ecx + 0xD61B]
        mov[edx + 0xA8], eax
        xor eax, eax
        mov ax, [ecx + 0xD61C]
        mov[edx + 0xAC], eax
        xor eax, eax
        mov ax, [ecx + 0xD61E]
        mov[edx + 0xB0], eax
        mov ecx, StoreEcx
        mov eax, [ecx + 0x1054]
        push eax
        lea eax, InnforUserLoad
        push eax
        call WriteData
        add esp,0x8
    }
    return returnresult;
}
bool StoreUserDB()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    UserData InnforUserLoad;
    __asm
    {
        xor eax, eax
        mov ecx, StoreEcx
        lea edx, InnforUserLoad
        xor eax, eax
        mov al, [ecx + 0xD63E]
        mov[edx], eax
        xor eax, eax
        mov al, [ecx + 0xD63F]
        mov [edx + 0x4], eax
        xor eax, eax
        mov al, [ecx + 0xD640]
        mov[edx + 0x8], eax
        xor eax, eax
        mov eax, [ecx + 0xD641]
        mov[edx + 0xC], eax
        xor eax, eax
        mov eax, [ecx + 0xD645]
        mov[edx + 0x10], eax
        xor eax, eax
        mov al, [ecx + 0xD64A]
        mov[edx + 0x14], eax
        mov eax, [ecx + 0x1054]
        push eax
        lea eax, InnforUserLoad
        push eax
        call WriteDataInforUser
        add esp, 0x8
    }
    return returnresult;
}
bool StoreChienTruongTongKim()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    InforUserTK InnforUserLoad;
    __asm
    {
        xor eax, eax
        mov ecx, StoreEcx
        lea edx, InnforUserLoad
        xor eax,eax
        mov al,[ecx+0xD625]
        mov [edx],eax
        xor eax,eax
        mov eax,[ecx+0xD626]
        mov [edx+0x4],eax
        xor eax, eax
        mov eax, [ecx + 0xD632]
        mov[edx + 0x8], eax
        xor eax, eax
        mov eax, [ecx + 0xD62A]
        mov[edx + 0xC], eax
        mov eax, [ecx + 0x1054]
        push eax
        lea eax, InnforUserLoad
        push eax
        call WriteDataTongKim
        add esp, 0x8
    }
    return returnresult;
}

void RemoveItem(int slotItem)
{
    CMSG_GM_REM_INVITEM RemoveItem;
    char storemoney = slotItem;
    DWORD StoreECX = 0;
    __asm
    {
        mov StoreECX, ecx
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, RemoveItem
        lea eax, [eax+0x3]
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        //
        mov eax, slotItem
        imul eax,0x60
        mov ecx, StoreECX
        xor edx,edx
        lea ecx,[ecx+0x128C+eax+0x8]
        lea eax, RemoveItem
        mov edx,[eax+0x8]
        mov [eax+0x10],edx
        xor edx,edx
        mov edx, slotItem
        mov [eax+0x14],dl
        mov byte ptr [eax],0x15
        mov byte ptr[eax+0x1], 0x00
        mov byte ptr[eax+0x2], 0xA3
        //
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x0060DD2F
        call eax
    }
}
void __declspec(naked)StoreInfoUserTxt()//005D0F01 9
{
    __asm
    {
        mov ecx, [ebp - 0xDBC]
        call StoreDataUse
        mov ecx, [ebp - 0xDBC]
        call StoreUserDB
#ifdef TestTK
        mov ecx, [ebp - 0xDBC]
        call StoreChienTruongTongKim
#endif // TestTK
        mov ecx, [ebp - 0xDBC]
        push 0x005D0F07
        ret 
    }
}
void __declspec(naked)StoreInfoUserTxt2()//00602391 9
{
    __asm
    {
        mov ecx, [ebp + 0x8]
        call StoreDataUse
        mov ecx, [ebp + 0x8]
        call StoreUserDB
#ifdef TestTK
        mov ecx, [ebp + 0x8]
        call StoreChienTruongTongKim
#endif // TestTK
        push 0x006023B3
        ret
    }
}
void __declspec(naked)StoreInfoUserTxt3()//00602645 9
{
    __asm
    {
        mov ecx, [ebp + 0x8]
        call StoreDataUse
        mov ecx, [ebp + 0x8]
        call StoreUserDB
#ifdef TestTK
        mov ecx, [ebp + 0x8]
        call StoreChienTruongTongKim
#endif // TestTK
        push 0x00602664
        ret
    }
}
void NoticeZOne()
{
    char StringSay[41] = "Da DDa Den Thoi Gian Su Kien Loan Chien ";
    MSG_ZONE_CHAT_NORMAL chat;
    chat.ucMessage = 28;
    chat.header.sCompressed = 0;
    chat.header.sCrypto = 0;
    strcpy(chat.cName, "GMS");
    int nstring = 0;
    chat.cMode = 127;
    StringSay[41 - 1] = 0;
    nstring = 41;
    if (nstring < MAX_CHAT_LENGTH)
    {
        strcpy(chat.cSay, StringSay);
        chat.cSay[nstring] = 0;
        chat.header.sLength = 18 + nstring;
        __asm
        {
            xor eax,eax
            mov ax,chat.header.sLength
            and ax,0x7FFF
            and eax,0xFFFF
            push eax
            lea eax,chat
            push eax
            mov ecx, 0x007763AC
            mov ecx, [ecx]
            mov eax,0x00603B9E
            call eax
        }
    }
}
int CheckTimeMove(int checkType)
{
    int  acceptmove = 0;
    SYSTEMTIME checktime;
    GetLocalTime(&checktime);
#ifdef TestEvent
    acceptmove = 0;
    return acceptmove;
#endif // TestEvent

    if (checkType == 1)
    {
        if (checktime.wHour == 20)
        {
            if (checktime.wMinute >= 00 && checktime.wMinute <= 40)
            {
                acceptmove = 1;
            }
        }
    }
    else
    {
       
    }


    return acceptmove;
}

void AddItemLoadChien(char cFirstType,char cSecondType,short sItemID ,unsigned char ucItemCount)//0049F91F
{
    DWORD StoreECX = 0;
    __asm mov StoreECX, ecx
    CMSG_GM_ADD_INVITEM pkaddItemEvent;
    pkaddItemEvent.usLength = 33;
    pkaddItemEvent.ucInchant = 0;
    pkaddItemEvent.ucSlotCount = 0;
    pkaddItemEvent.usDurability = 0;
        char getcFirstType = cFirstType;
        char getcSecondType = cSecondType;
        short getsItemID = sItemID;
        pkaddItemEvent.ucItemCount = ucItemCount;
        pkaddItemEvent.ui64UniqueId = makeUniqueIDItem();
    __asm
    {
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, pkaddItemEvent.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp,0xC

        //
        mov al, getcFirstType
        mov pkaddItemEvent.cFirstType,al
        //
        mov al, getcSecondType
        mov pkaddItemEvent.cSecondType, al
        //
        mov ax, getsItemID
        mov pkaddItemEvent.sItemID, ax
        mov pkaddItemEvent.cMessage,0xA2
        //
        lea eax, pkaddItemEvent
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x0060DBA0
        call eax
    }
}
void AddItemWeapon(char cFirstType, char cSecondType, short sItemID, unsigned char ucItemCount, char inchant)//0049F91F
{
    DWORD StoreECX = 0;
    int countitem = static_cast<int>(ucItemCount);
    __asm mov StoreECX, ecx
#ifdef TestCode308
    if (cFirstType == 13)
    {
        __asm
        {
            mov eax, countitem
            push eax
            mov ecx, StoreECX
            call AddMoneyForEvent
            add esp, 0x4
        }
    }
#endif // TestCode308


    CMSG_GM_ADD_INVITEM pkaddItemEvent;
    pkaddItemEvent.usLength = 33;
    pkaddItemEvent.ucInchant = 0x0;
    pkaddItemEvent.ucSlotCount = 0;
    pkaddItemEvent.usDurability = 0;
    char getcFirstType = cFirstType;
    char getcSecondType = cSecondType;
    short getsItemID = sItemID;
    pkaddItemEvent.ucItemCount = ucItemCount;
    pkaddItemEvent.ui64UniqueId = makeUniqueIDItem();
    __asm
    {
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, pkaddItemEvent.cCharacName
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC

        //
        mov al, getcFirstType
        mov pkaddItemEvent.cFirstType, al
        //
        //ADdIncon
        lea eax, pkaddItemEvent
        xor ecx,ecx
        mov cl, inchant
        mov [eax+0x20], cl
        xor eax,eax
        xor ecx,ecx
        //
        mov al, getcSecondType
        mov pkaddItemEvent.cSecondType, al
        //
        mov ax, getsItemID
        mov pkaddItemEvent.sItemID, ax
        mov pkaddItemEvent.cMessage, 0xA2
        //
        lea eax, pkaddItemEvent
        push eax
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x0060DBA0
        call eax
    }
}
int nDiemTong = 0;
int nDiemKim = 0;
DWORD ListTopTongKim[9];
struct ThongTinAccTop {
    char tkUserName[15];
    int topUser;
    int DiemUser;
    int PheEvent;
    int countUser;
    int LienTram;
};
struct TongKimPackage {
    u_short usLength;
    u_char cMessage;
    u_char unknow;
    int DiemTong;
    int DiemKim;
    ThongTinAccTop ListTop[9];
};
struct ThongTinTkUser {
    u_short usLength;
    u_char cMessage;
    u_char unknow;
    char tkUserName[15];
    int DiemUser;
    int PheEvent;
    int countUser;
    int LienTram;
};
DWORD TopTongKim[10]
{
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
};
struct Users {
    char pad_0000[54821]; //0x0000
    uint8_t Phe; //0xD625
    uint32_t DiemTongKim; //0xD626
    uint32_t Top; //0xD62A
    uint32_t LienTram; //0xD62E
    uint32_t CountPk; //0xD632
};
TongKimPackage pkTongKim;
void NhapThongTin(ThongTinAccTop * ptThongTinAccTop)
{
    int count;
    ThongTinAccTop* pttThongTinAccTop;
    pttThongTinAccTop = ptThongTinAccTop;
    DWORD StoreECX;
    int TopInfo;
    TopInfo = 0;
    __asm
    {
        xor ecx, ecx
        lea eax, count
        mov[eax], ecx
        BackLoop :
            lea eax, TopInfo
            mov ecx, [eax]
            lea eax, TopTongKim
            mov eax, [eax + ecx * 0x4]
            test eax, eax
            jz KhongTinThay
            lea ecx, StoreECX
            mov [ecx],eax
            mov ecx, eax
            call get_name1
            push 0xD
            push eax
            lea eax, count
            mov ecx, [eax]
            mov eax, pttThongTinAccTop
            lea eax, [eax + ecx]
            push eax
            mov eax, 0x006E3CC0
            call eax
            add esp, 0xC
            mov eax, pttThongTinAccTop
            lea edx, TopInfo
            mov ecx, [edx]
            lea edx, count
            mov edx, [edx]
            mov[eax + 0x10 + edx], ecx
            lea eax, TopTongKim
            mov eax, [eax + ecx * 0x4]
            //Get Diem Tong KIm
            xor edx, edx
            lea ecx, StoreECX
            mov eax,[ecx]
            mov edx, [eax + 0xD626]
            mov eax, pttThongTinAccTop
            lea ecx, count
            mov ecx, [ecx]
            mov[eax + 0x14 + ecx], edx
            //Get Phe
            xor edx, edx
            lea ecx, StoreECX
            mov eax, [ecx]
            mov dl, [eax + 0xD625]
            mov eax, pttThongTinAccTop
            lea ecx, count
            mov ecx, [ecx]
            mov[eax + 0x18 + ecx], edx
            //Get CountPk
            xor edx, edx
            lea ecx, StoreECX
            mov eax, [ecx]
            mov edx, [eax + 0xD632]
            mov eax, pttThongTinAccTop
            lea ecx, count
            mov ecx, [ecx]
            mov[eax + 0x1C + ecx], edx
            // Get LienTram
            xor edx, edx
            lea ecx, StoreECX
            mov eax, [ecx]
            mov edx, [eax + 0xD62E]
            mov eax, pttThongTinAccTop
            lea ecx, count
            mov ecx, [ecx]
            mov[eax + 0x20 + ecx], edx
            //
            KhongTinThay :
            lea edx, TopInfo
            mov ecx, [edx]
            add ecx,0x1
            mov [edx],ecx
            lea edx, count
            mov ecx, [edx]
            add ecx, 0x24
            lea edx, count
            mov[edx], ecx
            cmp ecx, 0x144
            jb BackLoop
    }
}
void SendDiemTongKimUser()
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    int sizeofpackage = sizeof(TongKimPackage);
    ThongTinTkUser pg_TKuser;
    memset(&pg_TKuser, 0, sizeof(ThongTinTkUser));
    int count;
    int TopInfo;
    __asm
    {
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        //NhapThongTin
        lea eax, pg_TKuser
        add eax, 0x4
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        lea eax, pg_TKuser
        mov word ptr[eax], 0x28
        mov byte ptr[eax + 0x2], 0x3B
        mov byte ptr[eax + 0x3], 0xF9
        mov ecx, StoreECX
        xor edx,edx
        mov edx,[ecx+0xD626]
        mov [eax+0x18],edx
        //
        mov ecx, StoreECX
        xor edx, edx
        mov dl, [ecx + 0xD625]
        mov[eax + 0x1C], edx
        //
        mov ecx, StoreECX
        xor edx, edx
        mov edx, [ecx + 0xD632]
        mov[eax + 0x20], edx
        //
        mov ecx, StoreECX
        xor edx, edx
        mov edx, [ecx + 0xD62E]
        mov[eax + 0x24], edx
        //
        lea eax, pg_TKuser
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, pg_TKuser
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
};
void SendDiemTongKim()
{
    int sizeofpackage = sizeof(TongKimPackage);
    TongKimPackage pg_TongKim;
    memset(&pg_TongKim, 0, sizeof(TongKimPackage));
    ThongTinAccTop* ThongTinTop;
    ThongTinTop = (ThongTinAccTop*)(&pg_TongKim.ListTop);
    DWORD* ListTop;
    int count;
    int TopInfo;
    __asm
    {
        //NhapThongTin
        lea eax, pg_TongKim
        add eax,0xC
        push eax
        call NhapThongTin
        add esp,0x4
        lea eax, pg_TongKim
        lea ecx, sizeofpackage
        mov ecx,[ecx]
        mov word ptr[eax], 0x150
        mov byte ptr[eax + 0x2], 0x3B
        mov byte ptr[eax + 0x3], 0xF3
        lea ecx, nDiemTong
        mov ecx,[ecx]
        mov[eax + 0x4], ecx
        lea ecx, nDiemKim
        mov ecx, [ecx]
        mov[eax + 0x8], ecx
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, pg_TongKim
        push eax
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov eax, 0x00603B9E
        call eax
    }
};
struct PkInfor {
    u_short usLength;
    u_char cMessage;
    u_char unknow;
    char NguoiThang[13];
    char NguoiThua[13];
    DWORD StoreAddress;
};
void SendPkInfo(DWORD * ptUserThang, DWORD* ptUserThua)
{
    PkInfor pg_PkInfor;
    memset(&pg_PkInfor, 0, sizeof(PkInfor));
    DWORD* Thang;
    DWORD* Thua;
    Thang = ptUserThang;
    Thua = ptUserThua;
    int TopInfo;
    __asm
    {
        //NhapThongTin
        push 0xD
        mov eax, Thang
        push eax
        lea eax, pg_PkInfor.NguoiThang
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        //
        push 0xD
        mov eax, Thua
        push eax
        lea eax, pg_PkInfor.NguoiThua
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        //
        lea eax, pg_PkInfor
        mov byte ptr[eax], 0x22
        mov byte ptr[eax + 0x2], 0x3B
        mov byte ptr[eax + 0x3], 0xE2
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, pg_PkInfor
        push eax
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov eax, 0x00603B9E
        call eax
    }
};
void SapXepTopTongKim(char *NameUser, int vitri)
{
    /*char* NameNhap;
    NameNhap = NameUser;
    char Nametemp[13];
    int Diemtemp;
    TongKimPackage* pn_TongKim;
    char* PointName;
    int *PointerDiem;
    bool resultCheck;
    pn_TongKim = &pkTongKim;
    for (int i = vitri; i < 10; ++i)
    {
        PointName = *(&pn_TongKim->ListTop[i].tkUserName);
        PointerDiem = &pn_TongKim->ListTop[i].DiemUser;
        memcpy(Nametemp, *(&pn_TongKim->ListTop[i].tkUserName), 13);
        memcpy(*(&pn_TongKim->ListTop[i].tkUserName), &NameNhap, 13);
        memcpy(NameNhap, Nametemp, 13);
        __asm
        {
            mov eax, PointName
            push eax
            mov ecx, DWORD PTR SS : [0x007763AC]
            mov eax, 0x006080B7
            call eax
            test eax,eax
            jz KhongTimThay
            mov ecx,[eax+0xD626]
            mov eax, PointerDiem
            mov [eax], ecx
            jmp Backloop
            KhongTimThay:
            push 0xD
            mov eax, NameNhap
            push eax
            mov eax, PointName
            push eax
            mov eax, 0x006E3CC0
            call eax
            add esp, 0xC
            lea eax, resultCheck
            mov dword ptr [eax],0x0
                Backloop:
        }
        if (resultCheck)
        {
            break;
        }
    }*/
}
void SapXepTopTongKimTest()
{
    DWORD StoreECX1;
    DWORD StoreECX2;
    for (int i = 0; i < 9; i++)
    {
        __asm
        {
            lea ecx,i
            mov ecx,[ecx]
            lea eax, TopTongKim
            mov edx,[eax + ecx*0x4]
            test edx,edx
            jz OutFunc
            lea eax, StoreECX1
            mov [eax],edx
        }
        for (int y = 1; y < 9; y++)
        {
            __asm
            {
                lea ecx, y
                mov ecx, [ecx]
                lea eax, TopTongKim
                mov edx, [eax + ecx * 0x4]
                test edx,edx
                jz NextCheck
                lea eax, StoreECX2
                mov [eax], edx
                mov eax, StoreECX1
                mov ecx,[eax+0xD626]
                cmp ecx,[edx+0xD626]
                jae NextCheck
                mov ecx,[edx+0xD62A]
                mov edx,[eax+0xD62A]
                mov [eax+0xD62A],ecx
                mov eax, StoreECX2
                mov [eax+0xD62A],edx
                //
                mov eax, StoreECX2
                mov ecx,[eax + 0xD62A]
                lea edx, TopTongKim
                mov [edx+ecx*0x4], eax
                //
                mov eax, StoreECX1
                mov ecx, [eax + 0xD62A]
                lea edx, TopTongKim
                mov[edx + ecx * 0x4], eax
                //
                mov eax, StoreECX2
                lea ecx, StoreECX1
                mov [ecx],eax
                //

                NextCheck:
            }
        }
        __asm OutFunc:
    }
    /*__asm
    {
        BackLoop:
        lea eax, count
        mov ecx,[eax]
        lea eax, TopTongKim
        mov edx, [eax + ecx * 0x4]
        test edx,edx
        jz EndCheck
        lea ecx, countn
        mov ecx,[ecx]
        mov eax, [eax + ecx * 0x4]
        test eax,eax
        jz EndCheck
        mov ecx,[edx+0xD626]
        cmp ecx,[eax+0xD626]
        jae NextCheckRank


        NextCheckRank:

        EndCheck:

    }*/
}
void KiemTraVaAddTopTongKim()
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    DWORD StoreCheck;
    int Count;
    __asm
    {
        xor ecx,ecx
        lea eax, Count
        mov [eax],ecx
        LoopBack:
        lea eax, Count
        mov ecx,[eax]
        lea eax, TopTongKim
        mov eax,[eax+ecx*0x4]
        test eax,eax
        jz KhongCoTop
        mov ecx, StoreECX
        xor edx,edx
        mov edx,[ecx+0x1208]
        xor ecx,ecx
        mov ecx,[eax+ 0x1208]
        cmp ecx,edx
        jz DaCoTop
        lea edx, StoreCheck
        mov [edx],eax
        xor edx,edx
        mov edx,[eax+0xD626]
        mov ecx, StoreECX
        mov eax,[ecx+0xD626]
        cmp eax,edx
        jbe BackLoopCheck
        lea eax, Count
        mov ecx, [eax]
        lea eax, TopTongKim
        mov edx, StoreECX
        mov [eax + ecx * 0x4],edx
        add ecx,0x1
        mov eax,[edx+0xD62A]
        mov [edx+0xD62A],ecx
        mov edx, StoreCheck
        mov [edx+0xD62A],eax
        test eax,eax
        jz EndFunCheck
        cmp eax,0xA
        ja EndFunCheck
        mov ecx,eax
        lea eax, TopTongKim
        mov edx, StoreCheck
        sub ecx,0x1
        mov[eax + ecx * 0x4], edx
        jmp EndFunCheck
        BackLoopCheck:
        lea eax, Count
        mov ecx,[eax]
        add ecx,0x1
        mov [eax],ecx
        cmp ecx,0x9
        jl LoopBack
        jmp EndFunCheck
        KhongCoTop:
        lea eax, Count
        mov ecx,[eax]
        lea eax, TopTongKim
        mov edx,StoreECX
        mov [eax+ecx*0x4],edx
        add ecx,0x1
        mov [edx+0xD62A],ecx
        jmp EndFunCheck
        DaCoTop:
        mov ecx, StoreECX
        cmp ecx, eax
        jz EndFunCheck
        lea eax, Count
        mov ecx, [eax]
        lea eax, TopTongKim
        mov edx, StoreECX
        mov[eax + ecx * 0x4], edx
            EndFunCheck:
        call SapXepTopTongKimTest
    }
};
bool TangDiemKhiTongKim(int PheLocalUser,int PheDoiDich, DWORD * pUser)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    DWORD *StoreECXDoiDich;
    StoreECXDoiDich = pUser;
    int* ptDiemTOngKim;
    bool resultAdd;
    resultAdd = false;
    if (PheLocalUser != 0 && PheDoiDich != 0)
    {
        if (PheDoiDich != PheLocalUser)
        {
            if (PheLocalUser == 1)
            {
                ptDiemTOngKim = &nDiemTong;
            }
            else if (PheLocalUser == 2)
            {
                ptDiemTOngKim = &nDiemKim;
            }
            __asm
            {
                xor eax, eax
                mov eax, StoreECXDoiDich
                mov ecx, [eax + 0xD626]
                cmp ecx, 0x1F4
                jae HieuUy
                mov eax, StoreECX
                mov edx, [eax + 0xD626]
                add edx, 0x32
                mov[eax + 0xD626], edx
                //
                xor edx,edx
                mov eax, ptDiemTOngKim
                mov edx, [eax]
                add edx, 0x32
                mov[eax], edx
                jmp EndAddDiemTK

                //Rank2
                HieuUy :
                cmp ecx, 0x7D0
                jae ThongLinh
                mov eax, StoreECX
                mov edx, [eax + 0xD626]
                add edx, 0x64
                mov[eax + 0xD626], edx
                //
                xor edx, edx
                mov eax, ptDiemTOngKim
                mov edx, [eax]
                add edx, 0x64
                mov[eax], edx
                jmp EndAddDiemTK

                ThongLinh:
                cmp ecx, 0xFA0
                jae PhoTuong
                mov eax, StoreECX
                mov edx, [eax + 0xD626]
                add edx, 0x96
                mov[eax + 0xD626], edx
                //
                xor edx, edx
                mov eax, ptDiemTOngKim
                mov edx, [eax]
                add edx, 0x96
                mov[eax], edx
                jmp EndAddDiemTK

                PhoTuong:
                cmp ecx, 0x1770
                jae DaiTuong
                mov eax, StoreECX
                mov edx, [eax + 0xD626]
                add edx, 0xC8
                mov[eax + 0xD626], edx
                //
                xor edx, edx
                mov eax, ptDiemTOngKim
                mov edx, [eax]
                add edx, 0xC8
                mov[eax], edx
                jmp EndAddDiemTK

                DaiTuong:
                mov eax, StoreECX
                mov edx, [eax + 0xD626]
                add edx, 0x12C
                mov[eax + 0xD626], edx
                //
                xor edx, edx
                mov eax, ptDiemTOngKim
                mov edx, [eax]
                add edx, 0x12C
                mov[eax], edx

                //Add Lien Tram Va Count User
                EndAddDiemTK:
                mov ecx, StoreECX
                xor eax, eax
                mov eax, [ecx + 0xD62E]
                add eax, 0x1
                mov[ecx + 0xD62E], eax
                xor eax, eax
                mov eax, [ecx + 0xD632]
                add eax, 0x1
                mov[ecx + 0xD632], eax
                lea eax, resultAdd
                mov [eax],0x1
            }
        }
    }
    return  resultAdd;
}
void ReadLuckBox()
{
    g_BoxLucky = new BoxLucky();
    if (g_BoxLucky)
    {
        g_BoxLucky->ReadFileText();
    }

}
void __declspec(naked)AddBloodPk()//004D29D4 9
{
    __asm
    {

        xor ecx, ecx
        mov ecx, [ebp - 0x14]
        and ecx, 0xFFFF
        cmp ecx, 0x3C
        jnz Default
        mov edx, 0x007711F2
        movsx edx, [edx]
        cmp edx, 0xE
        jnz EventTongKim
        // Complete Code Hien Thi PK
        mov edx,[ebp+0x8]
        push edx
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov eax, 0x00608193
        call eax
        test eax, eax
        jz Default
        mov ecx,eax
        call get_name1
        push eax
        mov ecx, [ebp - 0x30]
        call get_name1
        push eax
        call SendPkInfo
        add esp,0x8
        jmp Default
        EventTongKim:
        cmp edx, 0xB
        jnz Default
        push 0x1
        call CheckTimeMove
        add esp, 0x4
        cmp eax, 0x1
        jnz Default
        mov edx, [ebp + 0x8]
        push edx
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov eax, 0x00608193
        call eax
        test eax,eax
        jz Default
        mov dword ptr [eax+0xD62E],0x0
        push eax
        xor ecx,ecx
        mov cl, [eax + 0xD625]
        push ecx
        mov eax, [ebp - 0x30]
        xor ecx, ecx
        mov cl, [eax + 0xD625]
        push ecx
        mov ecx, [ebp - 0x30]
        call TangDiemKhiTongKim
        add esp,0xC
        xor ecx,ecx
        mov cl,al
        test ecx, ecx
        jz Default
        mov ecx, [ebp - 0x30]
        call SendDiemTongKimUser
        mov ecx, [ebp - 0x30]
        call KiemTraVaAddTopTongKim
        call SendDiemTongKim
        Default:
        mov ecx, [ebp - 0xC]
        and ecx, 0xFF
        push 0x004D29DD
        ret
    }
}
void sapxepTopDmg(int * ListTop,int * pUser)
{
    int *diachiUser = pUser;
    int* diachiList = ListTop;
    DWORD temp;

    __asm {
        mov ecx,0x0
        loopCheckTOp:
        push ecx
        mov eax, ListTop
        mov eax,[eax+ecx*0x4]
        test eax,eax
        jz KhongCoTop
        //Tinh toan dmg top
        mov ecx,[eax+ 0xD55C]
        mov eax, pUser
        xor edx,edx
        mov edx, [eax + 0xCAA8]
        cmp edx,ecx
        ja KhongCoTop
        LoopCheckAnotherTop:
        pop ecx
        add ecx,0x1
        cmp ecx,0x9
        jae EndCheck
        push ecx
        mov eax, ListTop
        mov eax, [eax + ecx * 0x4]
        test eax,eax
        jz KhongCoTop
        mov ecx, [eax + 0xD55C]
        mov eax, pUser
        xor edx, edx
        mov edx, [eax + 0xCAA8]
        cmp edx, ecx
        ja KhongCoTop
        jmp LoopCheckAnotherTop

        KhongCoTop:
        pop ecx
        mov eax, ListTop
        mov edx, pUser
        LoopSapXep:
        push ecx
        mov ebx,[eax + ecx * 0x4]
        mov [eax + ecx * 0x4], edx
        pop ecx
        mov edx,ebx
        add ecx,0x1
        cmp ecx,0x9
        jb LoopSapXep
        EndCheck:

    }
}
void __declspec(naked)ImprisonmentPlayer()//0049F91F
{
    __asm
    {
        //Add Effect
        push 0x3
        mov ecx, [ebp - 0x8]
        mov eax,0x0049F6BC
        call eax
        //MOve User
        mov ecx, [ebp - 0x8]
        call editZoneGame
        push 0x0049F929
        ret
    }
}

char NoticeMod[81] = "Boss Da Xuat Hien O Maps Hai Nam";
char GmNote[13] = "GM Note";
void GameEvent()
{
    MSG_ZONE_CHAT_NORMAL chat;
    strcpy(chat.cName, GmNote);
    strcpy(chat.cSay, NoticeMod);
    chat.header.sLength = 54;
    __asm
    {
        xor eax,eax
        mov ax, chat.header.sLength
        and ax,0x7FFF
        and eax,0xFFFF
        push eax
        lea eax,chat
        push eax
        mov ecx, 0x007763AC
        mov ecx,[ecx]
        mov eax,0x00603B9E
        call eax
    }
}
int DanhSachBoss[16]
{
    {6623},
    {6624},
    {6625},
    {6626},
    {6627},
    {6628},
    {6629},
    {6630},
    {6631},
    {6632},
    {6633},
    {6634},
    {6635},
    {6636},
    {6637},
    {0},
};
float ListBoxHp[57][2] =
{
    {232.97,314.189},
    {232.62,300.877},
    {232.62,286.877},
    {232.62,272.877},
    {232.62,258.877},
    {232.62,244.877},
    {232.62,230.877},
    {232.62,215.877},
    {232.62,207.877},
    {221.97,314.189},
    {221.62,300.877},
    {221.62,286.877},
    {221.62,272.877},
    {221.62,258.877},
    {221.62,244.877},
    {221.62,230.877},
    {221.62,215.877},
    {221.62,207.877},
    {207.97,314.189},
    {207.62,300.877},
    {207.62,286.877},
    {207.62,272.877},
    {207.62,258.877},
    {207.62,244.877},
    {207.62,230.877},
    {207.62,215.877},
    {207.62,207.877},
    {195.97,314.189},
    {195.62,300.877},
    {195.62,286.877},
    {195.62,272.877},
    {195.62,258.877},
    {195.62,244.877},
    {195.62,230.877},
    {195.62,215.877},
    {195.62,207.877},
    {179.97,314.189},
    {179.62,300.877},
    {179.62,286.877},
    {179.62,272.877},
    {179.62,258.877},
    {179.62,244.877},
    {179.62,230.877},
    {179.62,215.877},
    {179.62,207.877},
    {211.209,266.549},
    {215.687,257.937},
    {211.417,252.484},
    {203.454,249.964},
    {197.364,258.670},
    {195.703,265.521},
    {203.903,265.977},
    {211.815,264.288},
    {214.778,257.608},
    {207.998,251.589},
    {201.302,261.545},
    {201.599,269.550},
};
float DiachiBossLonHP[1][2] =
{
    {205.689 ,261.289},
};
float ToaDoBossSKHopPhi[1][2] =
{
   {-121.095, -114.058}
};
void SpawnModBossSuKien(int IdBoss)
{
    int KiemTraBoxTha;
    int IdboxSpawn = 0;
    KiemTraBoxTha = IdBoss;
    if (KiemTraBoxTha == 6623 || KiemTraBoxTha == 6624)
    {
        IdboxSpawn = 6638;
    }
    else if (KiemTraBoxTha == 6625 || KiemTraBoxTha == 6626)
    {
        IdboxSpawn = 6639;
    }
    else if (KiemTraBoxTha == 6627 || KiemTraBoxTha == 6628)
    {
        IdboxSpawn = 6640;
    }
    else if (KiemTraBoxTha == 6629 || KiemTraBoxTha == 6630)
    {
        IdboxSpawn = 6641;
    }
    else if (KiemTraBoxTha == 6631 || KiemTraBoxTha == 6632)
    {
        IdboxSpawn = 6642;
    }
    else if (KiemTraBoxTha == 6633)
    {
        IdboxSpawn = 6643;
    }
    else if (KiemTraBoxTha == 6634)
    {
        IdboxSpawn = 6644;
    }
    else if (KiemTraBoxTha == 6635)
    {
        IdboxSpawn = 6645;
    }
    else if (KiemTraBoxTha == 6636)
    {
        IdboxSpawn = 6646;
    }
    else if (KiemTraBoxTha == 6637)
    {
        IdboxSpawn = 6647;
    }
    __asm
    {
        lea eax, DanhSachBoss
        mov dword ptr [eax+0x3C],0x0
        mov edx, IdBoss
        xor ecx,ecx
        LoopCheckBoss:
        cmp edx,[eax+ecx*0x4]
        jnz KhongBangBossCu
        add ecx,0x1
        mov ecx,[eax+ecx*0x4]
        lea eax, DiachiBossLonHP
        push eax
        push ecx
        call CallBoss
            push 0x0
            lea eax, ListBoxHp
            push eax
            call ThaQuaiSk
            jmp EndBoss
        KhongBangBossCu:
        add ecx,0x1
        cmp ecx,0xF
        jl LoopCheckBoss
        jmp EndBoss
            SpawnBossOut:
            CallBoss:
            push 0x0
            push 0x0
            push 0x0
            mov edx, [esp + 0x14]
            push edx
            push 0x0
            mov eax, [esp + 0x18]
            push eax
            mov eax, 0x00406B10
            call eax
            mov ecx, eax
            mov eax, 0x005BB34D
            call eax
            lea ecx,DanhSachBoss
            mov [ecx+0x3C],eax
            mov cx, ax
            push ecx
            mov eax, 0x00406B10
            call eax
            mov ecx, eax
            mov eax, 0x005BBB29
            call eax
            lea ecx, DanhSachBoss
            mov eax,[ecx+0x3C]
            push eax
            mov eax, 0x00406B10
            call eax
            mov ecx, eax
            mov eax, 0x0040AD70
            call eax
            lea ecx, DanhSachBoss
            mov [ecx+0x3C],eax
            ret 0x8

                CallBoss2:
                push 0x0
                push 0x0
                push 0x0
                mov edx, [esp + 0x14]
                push edx
                push 0x0
                mov eax, [esp + 0x18]
                push eax
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
                mov eax, 0x005BBB29
                call eax
                ret 0x8

                ThaQuaiSk:
                xor ecx, ecx
                LoopSpawnBox :
                mov ecx, [esp + 0x8]
                mov edx, [esp + 0x4]
                lea eax, [edx + ecx * 0x4]
                mov ecx, [eax]
                lea edx, toadoBoss
                mov[edx], ecx
                mov ecx, [eax + 0x4]
                mov[edx + 0x4], ecx
                mov eax, IdboxSpawn
                lea edx, toadoBoss
                push edx
                push eax
                call CallBoss2
                mov ecx, [esp + 0x8]
                add ecx, 0x2
                mov[esp + 0x8], ecx
                cmp ecx, 0x72
                jae EndLoopBox
                jmp LoopSpawnBox
                EndLoopBox :
                ret 0x8
        EndBoss:
    }
};
void __declspec(naked)runFuneditZonetest()
{
    __asm
    {
        xor eax, eax
        mov ecx, [ebp - 0xDBC]
        mov al, [ecx + 0xB5E0 + 0x48 + 0x2]//kiem tra pham phap
        cmp eax, 0x2
        jnz CheckMove2
        push 0x005E3CD6
        ret


        CheckMove2 :
#ifdef Check_ConditionMove
        mov eax, [ebp - 0xEAB4]
            cmp eax, 0xF
            jnz Default
            push 0x3
            call CheckTimeMove
            add esp, 0x4
            cmp eax, 0x1
            jnz DisableMoveNotEnoughtTime
            jmp Default
            DisableMoveNotEnoughtTime :
        push 0x005E3CD6
            ret
#endif // CuuPhung

        Default:
        mov byte ptr[ebp - 0x0000E9C1], 0x7
            push 0x005E3C6E
            ret


    }

};
int BoxTinVatCls[121][4] =
{
    {0 ,0,0,120},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1072,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1073,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1082,1,0},
    {9, 1083,1,0},
    {9, 1070,1,0},
    {9, 1070,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1050,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1051,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1052,1,0},
    {9, 1053,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1062,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
    {9, 1063,1,0},
    {9, 1070,1,0},
    {9, 1071,1,0},
    {9, 1080,1,0},
    {9, 1081,1,0},
    {9, 1050,1,0},
    {9, 1051,1,0},
    {9, 1060,1,0},
    {9, 1061,1,0},
};
#ifdef ListIDCombineCp
#endif // ListIDCombineCp
#ifdef ListIDCombineZplay
int ListDieuCheKhongTacDungSach[6] =
{
    {5},
    {61},
    {62},
    {63},
    {64},
    {65},
};
int ListDieuCheChoPhepSuDungBua[134] =
{
    {133},
    {167},
    {168},
    {169},
    {170},
    {291},
    {292},
    {293},
    {294},
    {295},
    {296},
    {297},
    {298},
    {299},
    {300},
    {337},
    {338},
    {339},
    {340},
    {341},
    {342},
    {343},
    {344},
    {345},
    {346},
    {356},
    {357},
    {358},
    {359},
    {360},
    {361},
    {362},
    {363},
    {367},
    {368},
    {369},
    {370},
    {371},
    {372},
    {373},
    {374},
    {375},
    {376},
    {392},
    {393},
    {394},
    {395},
    {396},
    {397},
    {398},
    {399},
    {400},
    {401},
    {238},
    {239},
    {240},
    {241},
    {242},
    {243},
    {244},
    {245},
    {246},
    {247},
    {248},
    {249},
    {250},
    {251},
    {252},
    {253},
    {254},
    {255},
    {256},
    {257},
    {258},
    {259},
    {260},
    {261},
    {262},
    {263},
    {264},
    {265},
    {266},
    {267},
    {268},
    {269},
    {270},
    {271},
    {272},
    {273},
    {282},
    {283},
    {284},
    {285},
    {286},
    {287},
    {288},
    {289},
    {290},
    {291},
    {292},
    {293},
    {294},
    {295},
    {296},
    {297},
    {298},
    {327},
    {328},
    {329},
    {330},
    {331},
    {332},
    {333},
    {334},
    {335},
    {336},
    {337},
    {338},
    {339},
    {340},
    {341},
    {342},
    {343},
    {344},
    {345},
    {346},
    {356},
    {357},
    {358},
    {359},
    {360},
    {361},
    {362},
    {363},
};
#endif // ListIDCombineCp
DWORD jmpBackAdd;
DWORD jmpBackAdd3;
DWORD jmpBackAdd4;
int ListItemCheck1[5] = { 837,838,839 ,840 ,841 };
int ListItemCheck2[3] = { 837,838,839 };
int ListPhycys[648] = { 0,0,0,0,0,0,0,0,/**/1,0,0,0,0,0,0,/**/2,0,0,0,0,0,0,/**/3,0,0,0,0,0,0,/**/4,0,0,0,0,0,0,
                    1,0,19,50,47,1,24,100,/**/1,19,40,130,100,131,100,/**/2,19,10,23,100,50,1,/**/3,19,25,61,1,2,50,/**/4,19,15,1,50,9,100,
                    2,0,19,60,47,2,24,150,/**/1,19,50,130,150,131,150,/**/2,19,20,23,150,50,3,/**/3,19,35,61,2,2,75,/**/4,19,25,1,75,9,150,
                    3,0,19,70,47,3,24,200,/**/1,19,60,130,200,131,200,/**/2,19,30,23,200,50,5,/**/3,19,45,61,3,2,100,/**/4,19,35,1,100,9,200,
                    4,0,19,80,47,4,24,250,/**/1,19,70,130,250,131,250,/**/2,19,40,23,250,50,7,/**/3,19,55,61,4,2,125,/**/4,19,45,1,125,9,250,
                    5,0,19,90,47,5,24,300,/**/1,19,80,130,300,131,300,/**/2,19,50,23,300,50,9,/**/3,19,65,61,5,2,150,/**/4,19,55,1,150,9,300,
                    6,0,19,100,47,6,24,350,/**/1,19,90,130,350,131,350,/**/2,19,60,23,350,50,11,/**/3,19,75,61,6,2,175,/**/4,19,65,1,175,9,350,
                    7,0,19,110,47,7,24,400,/**/1,19,100,130,400,131,400,/**/2,19,70,23,400,50,13,/**/3,19,85,61,7,2,200,/**/4,19,75,1,200,9,400,
                    8,0,19,120,47,8,24,450,/**/1,19,110,130,450,131,450,/**/2,19,80,23,450,50,15,/**/3,19,95,61,8,2,225,/**/4,19,85,1,225,9,450,
                    9,0,19,130,47,9,24,500,/**/1,19,120,130,500,131,500,/**/2,19,90,23,500,50,17,/**/3,19,105,61,9,2,250,/**/4,19,95,1,250,9,500,
                    10,0,19,150,47,10,24,700,/**/1,19,140,130,700,131,700,/**/2,19,110,23,700,50,21,/**/3,19,125,61,10,2,350,/**/4,19,115,1,350,9,600,
                    11,0,19,250,47,11,24,900,/**/1,19,250,130,1500,131,900,/**/2,19,200,23,900,50,25,/**/3,19,200,61,20,2,450,/**/4,19,150,1,450,9,1000,
                    12,0,19,300,47,12,24,1100,/**/1,19,300,130,1800,131,1100,/**/2,19,250,23,1100,50,29,/**/3,19,250,61,25,2,550,/**/4,19,200,1,550,9,1100,
                    13,0,19,600,47,18,24,1500,/**/1,19,600,130,3000,131,2000,/**/2,19,600,23,1500,50,35,/**/3,19,600,61,30,2,650,/**/4,19,600,1,650,9,1500,
                    14,0,19,1000,47,26,24,2100,/**/1,19,1000,130,4500,131,3500,/**/2,19,1000,23,2100,50,43,/**/3,19,1000,61,35,2,750,/**/4,19,1000,1,750,9,2100,
                    15,0,19,1600,47,36,24,3000,/**/1,19,1600,130,6000,131,5500,/**/2,19,1600,23,3000,50,53,/**/3,19,1600,61,40,2,850,/**/4,19,1600,1,850,9,3000,
                    16,0,19,650,47,20,24,2000,/**/1,19,550,130,4000,131,2000,/**/2,19,550,23,2000,50,44,/**/3,19,550,61,48,2,950,/**/4,19,450,1,950,9,2500,
                    17,0,19,750,47,25,24,2500,/**/1,19,700,130,5500,131,2500,/**/2,19,700,23,2500,50,47,/**/3,19,700,61,58,2,1050,/**/4,19,600,1,1050,9,3000,
};
int ListChicong[648] = { 0,0,0,0,0,0,0,0,/**/1,0,0,0,0,0,0,/**/2,0,0,0,0,0,0,/**/3,0,0,0,0,0,0,/**/4,0,0,0,0,0,0,
                    1,0,128,50,131,50,24,100,/**/1,128,40,130,100,131,100,/**/2,128,10,23,100,52,1,/**/3,128,25,61,1,137,50,/**/4,128,15,136,50,10,100,
                    2,0,128,60,131,100,24,150,/**/1,128,50,130,150,131,150,/**/2,128,20,23,150,52,3,/**/3,128,35,61,2,137,75,/**/4,128,25,136,75,10,150,
                    3,0,128,70,131,150,24,200,/**/1,128,60,130,200,131,200,/**/2,128,30,23,200,52,5,/**/3,128,45,61,3,137,100,/**/4,128,35,136,100,10,200,
                    4,0,128,80,131,200,24,250,/**/1,128,70,130,250,131,250,/**/2,128,40,23,250,52,7,/**/3,128,55,61,4,137,125,/**/4,128,45,136,125,10,250,
                    5,0,128,90,131,250,24,300,/**/1,128,80,130,300,131,300,/**/2,128,50,23,300,52,9,/**/3,128,65,61,5,137,150,/**/4,128,55,136,150,10,300,
                    6,0,128,100,131,300,24,350,/**/1,128,90,130,350,131,350,/**/2,128,60,23,350,52,11,/**/3,128,75,61,6,137,175,/**/4,128,65,136,175,10,350,
                    7,0,128,110,131,350,24,400,/**/1,128,100,130,400,131,400,/**/2,128,70,23,400,52,13,/**/3,128,85,61,7,137,200,/**/4,128,75,136,200,10,400,
                    8,0,128,120,131,400,24,450,/**/1,128,110,130,450,131,450,/**/2,128,80,23,450,52,15,/**/3,128,95,61,8,137,225,/**/4,128,85,136,225,10,450,
                    9,0,128,130,131,450,24,500,/**/1,128,120,130,500,131,500,/**/2,128,90,23,500,52,17,/**/3,128,105,61,9,137,250,/**/4,128,95,136,250,10,500,
                    10,0,128,150,131,550,24,700,/**/1,128,140,130,700,131,700,/**/2,128,110,23,700,52,21,/**/3,128,125,61,10,137,350,/**/4,128,115,136,350,10,600,
                    11,0,128,250,131,1500,24,900,/**/1,128,250,130,1500,131,900,/**/2,128,200,23,900,52,25,/**/3,128,200,61,20,137,450,/**/4,128,150,136,450,10,1000,
                    12,0,128,300,131,1800,24,1100,/**/1,128,300,130,1800,131,1100,/**/2,128,250,23,1100,52,29,/**/3,128,250,61,25,137,550,/**/4,128,200,136,550,10,1100,
                    13,0,128,600,131,2400,24,1500,/**/1,128,600,130,3000,131,2000,/**/2,128,600,23,1500,52,35,/**/3,128,600,61,30,137,650,/**/4,128,600,136,650,10,1500,
                    14,0,128,1000,131,3200,24,2100,/**/1,128,1000,130,4500,131,3500,/**/2,128,1000,23,2100,52,43,/**/3,128,1000,61,35,137,750,/**/4,128,1000,136,750,10,2100,
                    15,0,128,1600,131,4000,24,3000,/**/1,128,1600,130,6000,131,5500,/**/2,128,1600,23,3000,52,53,/**/3,128,1600,61,40,137,850,/**/4,128,1600,136,850,10,3000,
                    16,0,128,650,131,5000,24,2000,/**/1,128,550,130,2000,131,2000,/**/2,128,550,23,2000,52,44,/**/3,128,550,61,48,137,950,/**/4,128,235,136,950,10,2500,
                    17,0,128,750,131,5500,24,2500,/**/1,128,700,130,2500,131,2500,/**/2,128,700,23,2500,52,47,/**/3,128,700,61,58,137,1050,/**/4,128,255,136,1050,10,3000,
};
float ListToaDoBoss[1][2] =
{
   {-121.095, -114.058}
};
int BangChien1 = 0;
int BangChien2 = 0;
int BangChienThang = 0;
float ListToaDoBossMini[4][2] =
{
    {-94.912 ,-386.762},
    {-425.185, -399.903},
    {-427.624, -277.141},
    {-357.052 ,-163.870},
};

float ListBossThieuLam[1][2] =
{
    {28.676,45.961},
};
float ListBossCaiBang[1][2] =
{
    {-125.746,6.427},
};
float ListBossLucLam[1][2] =
{
    {55.279 ,-6.594},
};
float ListBossBiCung[1][2] =
{
    {-37.623,57.586},
};
float ListBossVoDang[1][2] =
{
    {-109.346,90.694},
};
float ListBossMaGiao[1][2] =
{
    {159.421,82.472},
};
float ListQuaiThieuLam[20][2] =
{
    {48.994,28.554},
    {39.439,23.340},
    {32.133,17.358},
    {28.437,16.342},
    {19.454,18.781},
    {12.888,23.254},
    {10.492,30.729},
    {5.738,37.566},
    {2.008,44.675},
    {-0.319,51.550},
    {2.846,58.757},
    {6.501,64.699},
    {11.662,66.865},
    {17.852,68.632},
    {24.123,72.476},
    {30.076,74.877},
    {35.822,81.016},
    {36.473,64.684},
    {29.148,58.777},
    {19.733,51.399},
};
float ListQuaiCaiBang[20][2] =
{
    {-127.521,26.706},
    {-138.448,28.031},
    {-139.100,16.561},
    {-138.669,6.671},
    {-136.231,-4.438},
    {-134.515,-16.171},
    {-123.377,-17.133},
    {-112.915,-13.747},
    {-102.498,-11.364},
    {-97.060,-1.409},
    {-101.226,7.467},
    {-106.001,14.072},
    {-113.817,10.999},
    {-110.894,-0.374},
    {-104.304,0.543},
    {-119.616,4.941},
    {-141.243,-141.243},
    {-151.511,45.844},
    {-162.588,54.156},
    {-166.316,42.150},
};
float ListQuaiLucLam[20][2] =
{
    {62.965,10.460},
    {52.405,11.375},
    {41.045,8.005},
    {36.077,-1.356},
    {36.594,-9.563},
    {38.567,-17.350},
    {42.321,-25.930},
    {45.415,-31.489},
    {51.471,-37.810},
    {50.954,-47.905},
    {61.841,-48.577},
    {68.688,-33.780},
    {65.697,-21.779},
    {59.896,-10.168},
    {67.893,-2.517},
    {63.549,5.161},
    {54.780,5.302},
    {49.430,-3.615},
    {55.668,-21.392},
    {62.265,-32.906},
};
float ListQuaiBiCung[20][2] =
{
    {-34.768,60.441},
    {-29.205,75.015},
    {-21.778,83.551},
    {-13.763,89.250},
    {-4.972,92.728},
    {6.577,96.152},
    {16.401,99.054},
    {24.051,105.204},
    {33.653,98.332},
    {47.123,89.073},
    {36.555,80.485},
    {30.814,68.896},
    {68.896,60.415},
    {22.470,50.186},
    {13.211,43.605},
    {2.648,41.475},
    {-10.211,45.702},
    {-23.772,53.820},
    {-40.134,53.396},
    {-40.136,63.802},
};
float ListQuaiVoDang[20][2] =
{
    {-83.819,98.745},
    {-81.516,91.688},
    {-81.939,86.094},
    {-89.954,86.419},
    {-96.083,94.496},
    {-97.859,101.161},
    {-106.130,99.731},
    {-108.006,92.799},
    {-112.222,87.096},
    {-120.168,85.521},
    {-123.561,92.701},
    {-124.516,98.511},
    {-130.746,99.997},
    {-134.958,93.019},
    {-135.571,86.369},
    {-119.643,104.945},
    {-108.618,101.212},
    {-100.179,104.715},
    {-101.540,93.182},
    {-117.331,92.757},
};
float ListQuaiMaGiao[20][2] =
{
    {181.131,151.029},
    {188.398,142.491},
    {186.105,131.630},
    {175.323,127.400},
    {168.700,117.265},
    {183.632,102.602},
    {180.546,86.894},
    {193.190,76.025},
    {205.601,83.431},
    {171.730,92.824},
    {159.421,82.472},
    {157.719,65.841},
    {159.228,52.331},
    {145.155,45.602},
    {128.713,47.835},
    {137.968,61.762},
    {160.436,72.626},
    {172.115,81.852},
    {165.858,96.251},
    {155.095,107.279},
};
float ListHeo1[300][2] =
{
    {-88.395866,6.115073},
{-88.554146,14.742147},
{-83.433525,17.886284},
{-87.792496,22.313915},
{-93.778641,17.094193},
{-75.754135,27.149073},
{-71.796799,18.711119},
{-63.139648,13.776003},
{-60.451569,20.048992},
{-59.738144,25.715706},
{-65.988243,32.626194},
{-67.493042,35.394119},
{-80.912468,29.078966},
{-53.626587,1.168166},
{-59.502747,-3.291487},
{-60.986835,-9.302757},
{-55.51342,-10.499376},
{-50.065292,-8.377193},
{-54.968227,8.365083},
{-55.850616,19.060097},
{-32.131802,81.627464},
{-33.387924,87.762108},
{-35.560745,76.350601},
{-39.542854,80.960129},
{-42.375648,84.353783},
{-41.504059,88.642624},
{-25.390556,75.474068},
{-20.445091,81.782326},
{-22.548059,69.500549},
{-36.748611,69.600296},
{-36.563046,72.162231},
{-17.308971,71.008423},
{-21.488949,61.956062},
{-9.574772,91.26619},
{-6.641317,93.714142},
{-12.185154,96.297974},
{-8.429569,99.216347},
{-20.888948,97.075241},
{-1.137013,99.772331},
{6.832796,94.27726},
{72.623268,24.473904},
{69.837959,30.375614},
{73.771797,20.647469},
{83.181076,23.136494},
{76.772369,27.287207},
{82.899063,32.871334},
{83.246841,37.548401},
{79.654266,38.612961},
{79.210381,44.762276},
{75.322281,51.087475},
{70.168137,49.618301},
{72.479935,40.914619},
{69.691933,36.687222},
{63.204296,38.908527},
{58.321339,45.113724},
{59.278999,50.132553},
{65.681435,51.237362},
{61.911373,55.000923},
{66.617607,55.44989},
{64.26693,19.964523},
{-51.590366,-45.777039},
{-54.411846,-51.427822},
{-54.732258,-59.451878},
{-50.760319,-60.950062},
{-48.464115,-59.416096},
{-41.913811,-52.804501},
{-37.950001,-46.280987},
{-28.877155,-47.25042},
{-36.969257,-67.335014},
{-24.172787,-63.177696},
{-17.621233,-59.392338},
{-7.680976,-66.832802},
{-11.910258,-64.057014},
{-0.114716,-71.418434},
{1.706881,-63.111443},
{1.474138,-55.976418},
{-9.85822,-57.160332},
{-10.777865,-46.058525},
{4.207225,-47.776333},
{5.85689,-66.109985},
{16.953436,-103.011047},
{24.603233,-102.855972},
{26.998878,-100.817017},
{22.708878,-91.367912},
{23.029179,-84.023712},
{26.499357,-80.715515},
{37.024311,-82.9217},
{32.160889,-93.716003},
{39.610336,-101.541588},
{38.107491,-98.303307},
{46.277397,-105.310555},
{52.955406,-99.436874},
{46.660851,-93.811829},
{48.041893,-87.458649},
{50.293713,-86.081375},
{55.086452,-91.562241},
{58.13343,-97.732056},
{54.755379,-104.929367},
{50.279442,-97.003647},
{40.992317,-86.150475},
{-6.742689,46.433132},
{-9.572525,51.462105},
{-7.304581,51.519741},
{-11.664645,55.32299},
{-14.310201,53.853226},
{-14.192494,56.741753},
{-17.437021,56.503532},
{-11.961193,58.449211},
{-9.365929,59.088951},
{-9.501137,60.021526},
{-8.339973,57.406876},
{-5.995116,57.147915},
{-15.087845,48.383156},
{-12.988506,49.756058},
{-10.655462,53.372749},
{-12.099661,61.315208},
{-16.289619,45.535728},
{-19.734266,45.574127},
{-23.267523,45.420574},
{-25.548483,45.738037},
{18.359581,-41.126251},
{16.434814,-39.311836},
{14.280096,-44.779163},
{14.488754,-48.481995},
{20.09313,-48.929779},
{27.483353,-46.467358},
{23.167999,-44.277252},
{24.854107,-41.547359},
{22.870388,-39.387299},
{30.130009,-42.922306},
{31.641918,-45.966583},
{32.842579,-40.732292},
{28.013355,-39.594284},
{29.756664,-38.11607},
{33.681042,-38.08358},
{37.383549,-39.259975},
{41.33075,-41.9543},
{38.70739,-46.061234},
{42.396713,-45.318878},
{44.124336,-42.033077},
{37.224442,43.245979},
{36.802124,46.543636},
{36.291351,48.544174},
{32.860497,51.107941},
{30.678802,48.578026},
{27.105215,48.602345},
{26.038944,50.999874},
{22.018887,49.97448},
{17.767181,51.78492},
{16.224932,49.985882},
{15.246294,54.202934},
{16.776121,55.776085},
{20.778137,55.899708},
{27.379766,53.695023},
{31.458805,53.24258},
{25.961117,57.565857},
{20.740072,57.450413},
{16.767952,57.399158},
{10.471621,52.830048},
{9.722755,54.708561},
{-32.391193,-35.195686},
{-37.477303,-37.010918},
{-39.372593,-40.215031},
{-34.753189,-41.180061},
{-30.596773,-40.33873},
{-25.491655,-40.357853},
{-22.137009,-40.758911},
{-19.514736,-43.303654},
{-16.71701,-40.635994},
{-18.477802,-38.361649},
{-22.766102,-36.595764},
{-26.609245,-34.441555},
{-31.111574,-32.302822},
{-36.499058,-30.415743},
{-36.000942,-27.530107},
{-32.36356,-28.157537},
{-28.459936,-29.916582},
{-23.902954,-32.938141},
{-17.878338,-34.585804},
{-13.309591,-37.481068},
{62.589176,10.92341},
{54.594978,11.145366},
{49.268627,12.374033},
{49.130516,17.711456},
{52.298923,18.894003},
{54.230633,24.430073},
{55.017391,6.75492},
{45.972824,13.867896},
{45.449883,22.492397},
{49.573433,27.478554},
{53.364704,27.729511},
{55.750336,28.870041},
{50.058201,30.800419},
{45.074806,27.984043},
{42.096344,24.050587},
{42.841644,16.453627},
{43.257385,19.685368},
{47.571125,24.799728},
{39.175293,26.743805},
{43.533031,30.415073},
{-42.720108,3.94452},
{-41.922371,5.40219},
{-40.376137,6.339795},
{-42.684486,7.459062},
{-45.638466,4.49871},
{-49.40255,3.564384},
{-48.890678,4.140452},
{-48.654888,-1.084283},
{-44.845894,-2.83273},
{-43.015865,-1.036211},
{-43.155647,-4.499352},
{-41.45047,-4.264966},
{-41.281151,-1.186382},
{-39.659637,1.559775},
{-39.924511,7.870388},
{-41.60228,9.554815},
{-39.206375,11.373459},
{-38.3354,12.25615},
{-39.943085,13.796459},
{-42.386009,12.781907},
{-39.201759,38.576466},
{-40.423481,41.225163},
{-39.603069,43.950241},
{-41.65361,43.75666},
{-43.405312,43.20697},
{-44.785492,41.036007},
{-46.246609,35.469154},
{-46.270622,34.511887},
{-45.653519,32.256313},
{-42.865929,34.806755},
{-45.381779,37.916149},
{-41.781864,30.652378},
{-44.329407,29.965115},
{-39.923336,33.042713},
{-41.429752,36.131893},
{-46.80587,27.28162},
{-49.470947,28.197266},
{-51.395645,29.241802},
{-50.054871,31.793325},
{-50.376904,34.737484},
{53.183846,-32.786827},
{53.733101,-29.5555},
{53.651367,-25.982178},
{53.782036,-23.446392},
{54.242096,-21.494038},
{54.280968,-18.527609},
{54.387787,-16.280224},
{57.585194,-15.95941},
{59.707123,-20.425909},
{59.445908,-23.589733},
{59.067245,-26.458155},
{58.940796,-29.432035},
{58.915131,-32.280933},
{61.994209,-32.371536},
{62.05986,-27.879555},
{62.430717,-21.058838},
{62.382256,-18.126226},
{59.580059,-14.598316},
{53.705925,-14.215906},
{54.587982,-11.274091},
{-22.372078,33.315292},
{-26.247585,32.874989},
{-25.650192,35.919544},
{-24.279955,38.353111},
{-18.656237,39.44611},
{-21.018257,36.330795},
{-18.91074,37.550747},
{-14.7987,37.573986},
{-15.932266,35.570114},
{-17.429926,33.3447},
{-19.871311,31.472065},
{-17.740795,30.924622},
{-14.955875,32.300224},
{-12.908228,34.807011},
{-11.164022,36.641335},
{-11.973974,39.655724},
{-8.30546,35.978306},
{-9.822269,33.332302},
{-12.053611,30.772751},
{-16.894993,28.144554},
{18.632519,-10.871004},
{16.87966,-10.413992},
{15.404736,-10.27072},
{17.790737,-8.358362},
{21.395201,-8.659963},
{16.613173,-7.594914},
{16.206345,-14.794718},
{14.545485,-14.611462},
{13.74646,-16.487484},
{17.193586,-16.239956},
{19.42511,-13.096296},
{21.186874,-13.292429},
{22.90169,-11.98624},
{23.221733,-10.768068},
{25.112514,-10.588991},
{25.774059,-8.236353},
{23.74614,-7.24406},
{21.641495,-6.527333},
{20.082273,-6.465353},
{22.475998,-5.586054},
};
float ListHeo2[30][2] =
{
    {155.22,-21.021},
    {149.539,-26.586},
    {131.184,-31.928},
    {126.462,-24.998},
    {119.516,-17.914},
    {125.292,-9.918},
    {132.379,-3.36},
    {137.291,-0.413},
    {142.592,-5.703},
    {147.568,-12.194},
    {152.863,-19.012},
    {138.274,-1.065},
    {133.798,-9.721},
    {133.756,-24.682},
    {139.797,-26.089},
    {145.94,-18.227},
    {141.972,-7.791},
    {131.024,-7.515},
    {131.853,-19.641},
    {142.255,-22.939},
    {26.374,97.475},
    {16.245,104.976},
    {10.936,112.258},
    {21.598,127.411},
    {34.215,119.55},
    {27.602,105.843},
    {17.996,112.32},
    {22.38,118.982},
    {27.132,123.488},
    {28.561,109.649},
};
float ListHeo3[30][2] =
{
    {4.673,114.381},
    {10.546,119.271},
    {15.783,125.207},
    {22.883,130.452},
    {30.021,129.032},
    {34.885,123.895},
    {41.134,116.283},
    {45.704,110.148},
    {38.526,104.727},
    {32.368,99.086},
    {25.386,93.612},
    {19.421,97.579},
    {18.169,107.036},
    {16.798,118.266},
    {24.129,124.8},
    {32.137,118.281},
    {36.838,112.143},
    {27.839,102.184},
    {25.945,113.783},
    {31.043,107.861},
    {132.491,-23.282},
    {132.239,-12.794},
    {136.086,-5.945},
    {148.942,-16.352},
    {141.855,-27.952},
    {138.752,-30.168},
    {130.026,-22.475},
    {129.897,-10.556},
    {138.555,-4.545},
    {138.742,-18.358},
};
int BoxSam[2][4] =
{
    {0 ,0,0,1},
    {3, 245,5,0},
};
int BoxLinhChi[2][4] =
{
    {0 ,0,0,1},
    {3, 246,5,0},
};
int BoxVkQuetTan[11][4] =
{
    {0 ,0,0,10},
    {19, 12550,1,0},
    {19, 12551,1,0},
    {19, 12552,1,0},
    {19, 12553,1,0},
    {19, 12554,1,0},
    {19, 12555,1,0},
    {19, 12556,1,0},
    {19, 12557,1,0},
    {19, 12558,1,0},
    {19, 12559,1,0},
};
float SpawnModEXP[61][2] =
{
    {244.108,129.655},
    {243.535,137.796},
    {240.086,143.967},
    {233.426,150.353},
    {230.894,145.189},
    {247.813,146.826},
    {256.271,145.06},
    {261.87,140.7},
    {259.009,132.742},
    {253.931,135.718},
    {246.742,141.584},
    {253.78,132.668},
    {253.172,141.611},
    {251.199,109.042},
    {252.036,103.659},
    {250.195,96.545},
    {243.461,94.747},
    {241.264,101.459},
    {242.692,109.836},
    {236.103,111.788},
    {228.862,105.767},
    {226.901,96.809},
    {213.916,103.687},
    {214.91,113.742},
    {217.277,123.657},
    {210.088,132.002},
    {201.252,125.439},
    {192.757,114.742},
    {184.132,114.971},
    {189.435,131.042},
    {199.166,137.32},
    {197.242,146.205},
    {177.83,136.296},
    {176.764,144.498},
    {169.725,149.963},
    {175.503,133.639},
    {169.727,126.937},
    {168.143,118.478},
    {166.216,109.655},
    {142.864,120.799},
    {133.925,120.23},
    {127.115,126.005},
    {126.318,135.936},
    {128.53,142.621},
    {130.263,149.857},
    {128.01,157.005},
    {131.339,165.571},
    {131.634,172.096},
    {131.113,150.596},
    {137.483,150.421},
    {136.283,139.831},
    {130.306,142.446},
    {154.52,146.067},
    {154.151,138.966},
    {157.872,130.944},
    {150.542,123.91},
    {145.916,126.468},
    {147.474,137.245},
    {240.343,103.577},
    {198.31,115.058},
    {158.83,100.477},
};
int BoxVkQuetTanTinhLuyen[11][4] =
{
    {0 ,0,0,10},
    {19, 12550,1,15},
    {19, 12551,1,15},
    {19, 12552,1,15},
    {19, 12553,1,15},
    {19, 12554,1,15},
    {19, 12555,1,15},
    {19, 12556,1,15},
    {19, 12557,1,15},
    {19, 12558,1,15},
    {19, 12559,1,15},
};
int BoxVkHaiBaTinhLuyen[11][4] =
{
    {0 ,0,0,10},
    {19, 12402,1,15},
    {19, 12403,1,15},
    {19, 12404,1,15},
    {19, 12405,1,15},
    {19, 12406,1,15},
    {19, 12407,1,15},
    {19, 12408,1,15},
    {19, 12409,1,15},
    {19, 12410,1,15},
    {19, 12411,1,15},
};

float toadoBoxEvent[8][2] =
{
    {-238.778,-446.297},
    {439.643,-173.339},
    {-413.628,-327.427},
    {124.693,-75.052},
    {300.878,367.177},
    {470.599,446.933},
    {-311.28,310.06},
    {-383.478,45.321},
};


int BoxVkHaiBa[11][4] =
{
    {0 ,0,0,10},
    {19, 12402,1,0},
    {19, 12403,1,0},
    {19, 12404,1,0},
    {19, 12405,1,0},
    {19, 12406,1,0},
    {19, 12407,1,0},
    {19, 12408,1,0},
    {19, 12409,1,0},
    {19, 12410,1,0},
    {19, 12411,1,0},
};
float ListBossNho[4][2] =
{
    {62.067,48.830},
    {78.644,26.427},
    {101.070,44.713},
    {81.193,67.722},
};


int ListDa31[11] = { 3,758,759,760 ,761 ,762 ,763,764,765 ,766 ,767 };
int ListDa32[11] = { 11,768,769,770 ,771 ,772 ,773,774,775 ,776 ,777 };
int ListDa33[11] = { 12,778,779,780 ,781 ,782 ,783,784,785 ,786 ,787 };
int ListDa34[11] = { 13,788,789,790 ,791 ,792 ,793,794,795 ,796 ,797 };
int ListDa35[11] = { 14,798,799,800 ,801 ,802 ,803,804,805 ,806 ,807 };
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

int ListPet1[10] = { 7443,7444,7445,7446,7447,7448,7449,7450,7451,7452 };
int ListPet2[10] = { 7453,7454,7455,7456,7457,7458,7459,7460,7461,7462 };
int ListPet3[10] = { 7463,7464,7465,7466,7467,7468,7469,7470,7471,7472 };

int ListItemCLSExist1[10] = { 1049 ,1050,1051,1052,1053,1054,1055,1056,1057,1058};
int ListItemCLSExist2[10] = { 1069,1070 ,1071,1072,1073,1074,1075,1076,1077,1078 };
int ListItemCLSExist3[10] = { 1079 ,1080,1081,1082,1083,1084,1085,1086,1087,1088 };

int ListChauThuong[16] = { 1020 ,1021,1022,1023,1024,1037,1114,1112,0,0,0,0,0,0,0,0 };
int ListChauTuyet[16] = { 1129 ,1130,1131,1132,1133,1134,1135,1136,0,0,0,0,0,0,0,0 };

int Ky1[2] = { 433 ,853 };
int Ky2[2] = { 665 ,876 };
int Ky3[2] = { 666 ,857 };
int Ky4[2] = { 686 ,874 };
int Ky5[2] = { 687 ,875 };
#ifdef DanhSachChongDeoTrungCP
int ListDanhSachVpChongDeoTrung[18][16] =
{
    {1059,1060,1061,1062,1063,1167,1168,1169,1170,1171,0,0,0,0,0,0},
    {1172,1070,1071,1072,1073,1074,1075,1076,1077,1078,0,0,0,0,0,0},
    {1079,1080,1081,1082,1083,1084,1085,1086,1087,1088,0,0,0,0,0,0},
    {1049,1050,1051,1052,1053,1054,1055,1056,1057,1058,0,0,0,0,0,0},
    {433,853,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {665,876,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {666,857,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {687,875,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {686,874,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //{912,913,914,915,916,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //Chau
    {912,1094,1025,0,0,0,0,0,0,0,0,0,0,0,0},
    {913,1095,1026,0,0,0,0,0,0,0,0,0,0,0,0},
    {914,1096,1027,0,0,0,0,0,0,0,0,0,0,0,0},
    {915,1097,1028,0,0,0,0,0,0,0,0,0,0,0,0},
    {916,1098,1029,0,0,0,0,0,0,0,0,0,0,0,0},
    //Tin Vat MOi
    {936,937,938,939,940,0,0,0,0,0,0,0,0,0,0},
    {941,942,943,944,945,0,0,0,0,0,0,0,0,0,0},
    {871,870,872,1011,1015,0,0,0,0,0,0,0,0,0,0},
};
int totalsizeItemCheck = 18;
#endif // DanhSachChongDeoTrung
#ifdef DanhSachChongDeoTrungZplay
int ListDanhSachVpChongDeoTrung[16][16] =
{
    {1059,1060,1061,1062,1063,1167,1168,1169,1170,1171,0,0,0,0,0,0},
    {1172,1070,1071,1072,1073,1074,1075,1076,1077,1078,0,0,0,0,0,0},
    {1079,1080,1081,1082,1083,1084,1085,1086,1087,1088,0,0,0,0,0,0},
    {1049,1050,1051,1052,1053,1054,1055,1056,1057,1058,0,0,0,0,0,0},
    {433,853,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {665,876,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {666,857,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {687,875,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {686,874,0,0,0,0,0,0,0,0,0,0,0,0,0},
    //{912,913,914,915,916,0,0,0,0,0,0,0,0,0,0,0},
    //{877,1010,1014,0,0,0,0,0,0,0,0,0,0,0,0},
    //Chau
    {912,1094,1025,0,0,0,0,0,0,0,0,0,0,0,0},
    {913,1095,1026,0,0,0,0,0,0,0,0,0,0,0,0},
    {914,1096,1027,0,0,0,0,0,0,0,0,0,0,0,0},
    {915,1097,1028,0,0,0,0,0,0,0,0,0,0,0,0},
    {916,1098,1029,0,0,0,0,0,0,0,0,0,0,0,0},
    //Tin Vat MOi
    {936,937,938,939,940,0,0,0,0,0,0,0,0,0,0},
    {941,942,943,944,945,0,0,0,0,0,0,0,0,0,0},
    //{871,870,872,1011,1015,0,0,0,0,0,0,0,0,0,0},
};
int totalsizeItemCheck = 16;
#endif // DEBUG


int ListChau[16] = { 1020 ,1021,1022,1023,1024,1037,1114,1112,1129 ,1130,1131,1132,1133,1134,1135,1136 };

int ListTinVatKy[16] = { 433,853,665,876,666,857,687,875,686,874,0,0,0,0,0,0 };
int ChauThienQuyet[16] = { 1113,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
int HonNguyenKy[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

int ListTinVatLinhChien1[16] = { 936,937,938,939,940,0,0,0,0,0,0,0,0,0,0 };
int ListTinVatLinhChien2[16] = { 941,942,943,944,945,0,0,0,0,0,0,0,0,0,0 };
int ListNgoChauTuyet[16] = { 1025,1026,1027,1028,1029,0,0,0,0,0,0,0,0,0,0,0 };
bool CheckTinVatCoTonTaiKhong(DWORD & ListCheck)
{
    bool resultaftercheck;
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    DWORD* Address;
    resultaftercheck = true;
    int loopcountKy;
    Address = &ListCheck;
    __asm
    {
        mov edx, Address
        xor ecx, ecx
        LoopHNKAgain :
        mov loopcountKy, ecx
            xor ebx, ebx
            mov ebx, [edx + ecx * 0x4]
            test ebx, ebx
            jz EndOfFunCheck
            mov eax, StoreECX
            mov ecx, 0x420
            LoopbackcheckKy:
            add ecx, 0x60
            cmp ecx, 0x720
            ja KiemtraNewSlotKy
            cmp bx, [eax + 0x128C + ecx + 0xA]
            jnz LoopbackcheckKy
            mov resultaftercheck, 0x0
            jmp EndOfFunCheck

            KiemtraNewSlotKy :
            mov eax, StoreECX
            mov ecx, 0x3420
            Loopbackcheck2Ky :
            add ecx, 0x60
            cmp ecx, 0x3720
            ja LoopCheckKyInList
            cmp bx, [eax + 0x128C + ecx + 0xA]
            jnz Loopbackcheck2Ky
            mov resultaftercheck, 0x0
            jmp EndOfFunCheck

            LoopCheckKyInList :
            mov ecx, loopcountKy
            add ecx, 0x1
            cmp ecx, 0xF
            ja EndOfFunCheck
            jmp LoopHNKAgain
    }
    EndOfFunCheck:
    return resultaftercheck;
};
bool CheckTinVat(int IdVp)
{
    bool resultAccept;
    resultAccept = true;
    DWORD storeECX;
    int loopcount;
    int loopcount2;
    int loopcountKy1;
    __asm
    {
        mov storeECX,ecx
    }
    int IdVatPhamCheck, sizetotal, CurrentSlot;
    IdVatPhamCheck = IdVp;
    if (IdVatPhamCheck == 1113)
    {
        __asm
        {
            lea edx, ListChau
            push edx
            mov ecx, storeECX
            call CheckTinVatCoTonTaiKhong
            add esp, 0x4
            test al, al
            jnz EndCheckSpecialItem
            mov resultAccept, 0x0
            jmp EndOfFunCheck
        }
    };
#ifdef ChongDeoTrungKyCp

   /* for (int i = 0; i < 3; i++)
    {
        if (HonNguyenKy[i] == IdVatPhamCheck)
        {
            __asm
            {
                lea edx, ListTinVatKy
                push edx
                mov ecx, storeECX
                call CheckTinVatCoTonTaiKhong
                add esp, 0x4
                test al, al
                jnz EndCheckSpecialItem
                mov resultAccept, 0x0
                jmp EndOfFunCheck
            }
        }
    };*/
#endif // ChoDeoTrungKyZPlay
    for (int i = 0; i < 8; i++)
    {
        if (ListChauThuong[i] == IdVatPhamCheck)
        {
            __asm
            {
                lea edx, ChauThienQuyet
                xor ecx, ecx
                jmp LoopCheckItemListAgain
            }
        }
    };
    for (int i = 0; i < 8; i++)
    {
        if (ListChauTuyet[i] == IdVatPhamCheck)
        {
            __asm
            {
                lea edx, ChauThienQuyet
                xor ecx, ecx
                jmp LoopCheckItemListAgain
            }
        }
    };
    for (int i = 0; i < 5; i++)
    {
        if (ListTinVatLinhChien1[i] == IdVatPhamCheck)
        {
            __asm
            {
                lea edx, ListTinVatLinhChien2
                push edx
                mov ecx, storeECX
                call CheckTinVatCoTonTaiKhong
                add esp,0x4
                test al,al
                jnz EndCheckSpecialItem
                mov resultAccept, 0x0
                jmp EndOfFunCheck
            }
        }
        if (ListTinVatLinhChien2[i] == IdVatPhamCheck)
        {
            __asm
            {
                lea edx, ListTinVatLinhChien1
                push edx
                mov ecx, storeECX
                call CheckTinVatCoTonTaiKhong
                add esp, 0x4
                test al, al
                jnz EndCheckSpecialItem
                mov resultAccept, 0x0
                jmp EndOfFunCheck
            }
        }
    };
#ifdef ChongDeoTrungKyCp
 /*   for (int i = 0; i < 10; i++)
    {
        if (ListTinVatKy[i] == IdVatPhamCheck)
        {
            int loopcountKy = 0;
            __asm
            {
                lea edx, HonNguyenKy
                push edx
                mov ecx, storeECX
                call CheckTinVatCoTonTaiKhong
                add esp, 0x4
                test al, al
                jnz EndCheckSpecialItem
                mov resultAccept, 0x0
                jmp EndOfFunCheck
            }
        }
    }*/
#endif // ChoDeoTrungKyZPlay
 
    EndCheckSpecialItem:
    CurrentSlot = 255;
    for (int i = 0; i < totalsizeItemCheck; i++)
    {
        for (int y = 0; y < 16; y++)
        {
            if (ListDanhSachVpChongDeoTrung[i][y] != 0)
            {
                if (ListDanhSachVpChongDeoTrung[i][y] == IdVatPhamCheck)
                {
                    CurrentSlot = i;
                    goto JumOutCheck;
                }
            }
        }
    }
JumOutCheck:
    if (CurrentSlot < 50)
    {
        __asm
        {
            xor eax,eax
            mov eax, CurrentSlot
            imul eax,0x40
            xor edx,edx
            lea ecx, ListDanhSachVpChongDeoTrung
            lea edx,[ecx+eax]
            xor ecx,ecx
            LoopCheckItemListAgain:
            mov loopcount,ecx
            xor ebx,ebx
            mov ebx,[edx+ecx*0x4]
            test ebx,ebx
            jz EndOfFunCheck
                mov eax, storeECX
                mov ecx, 0x420
                Loopbackcheck:
                add ecx,0x60
                cmp ecx, 0x720
                ja KiemtraNewSlot
                cmp bx,[eax+0x128C+ecx+0xA]
                jnz Loopbackcheck
                mov resultAccept,0x0
                jmp EndOfFunCheck

                KiemtraNewSlot:
                mov eax, storeECX
                mov ecx, 0x3420
                Loopbackcheck2 :
                add ecx, 0x60
                cmp ecx, 0x3720
                ja LoopCheckItemInList
                cmp bx, [eax + 0x128C + ecx + 0xA]
                jnz Loopbackcheck2
                mov resultAccept, 0x0
                jmp EndOfFunCheck

            LoopCheckItemInList:
            mov ecx, loopcount
            add ecx,0x1
            cmp ecx,0xF
            ja EndOfFunCheck
            jmp LoopCheckItemListAgain 
        }
    }
    EndOfFunCheck:
    return resultAccept;
}

int ListVpDieuCheKhongMat[64][2] =
{
{0,126},
{ 9 ,853 },
{ 9 ,857 },
{ 9 ,875 },
{ 9 ,874 },
{ 9 ,876 },
//Pet Train
{ 9 ,1174 },
{ 9 ,1175 },
{ 9 ,1176 },
{ 9 ,1177 },
{ 9 ,1178 },
{ 9 ,1179 },
{ 9 ,1180 },
{ 9 ,1181 },
{ 9 ,1182 },
{ 9 ,1183 },
//PetPk
{ 9 ,1194 },
{ 9 ,1195 },
{ 9 ,1196 },
{ 9 ,1197 },
{ 9 ,1198 },
{ 9 ,1199 },
{ 9 ,1200 },
{ 9 ,1201 },
{ 9 ,1202 },
{ 9 ,1203 },
//An Mon Phai
{ 9 ,778 },
{ 9 ,779 },
{ 9 ,780 },
{ 9 ,781 },
{ 9 ,782 },
{ 9 ,783 },
//
{ 9 ,784 },
{ 9 ,785 },
{ 9 ,786 },
{ 9 ,787 },
{ 9 ,788 },
{ 9 ,789 },
//
{ 9 ,790 },
{ 9 ,791 },
{ 9 ,792 },
{ 9 ,793 },
{ 9 ,794 },
{ 9 ,795 },
//
{ 9 ,796 },
{ 9 ,797 },
{ 9 ,798 },
{ 9 ,799 },
{ 9 ,800 },
{ 9 ,801 },
//
{ 9 ,802 },
{ 9 ,803 },
{ 9 ,804 },
{ 9 ,805 },
{ 9 ,806 },
{ 9 ,807 },
//
{ 9 ,808 },
{ 9 ,809 },
{ 9 ,810 },
{ 9 ,811 },
{ 9 ,812 },
{ 9 ,813 },
{ 9 ,858 },
{ 9 ,887 },
};
#ifdef NewBoxCP
int nBox1931[62][4] =
{
    {0,0,0,61},
    {9,876,1,0},
    {9,857,1,0},
    {9,875,1,0},
    {9,874,1,0},
    {9,857,1,0},
    {9,874,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,853,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,857,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,857,1,0},
    {9,876,1,0},
    {9,853,1,0},
    {9,874,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,857,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,857,1,0},
    {9,853,1,0},
    {9,874,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,857,1,0},
    {9,874,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,853,1,0},
    {9,857,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,857,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,874,1,0},
    {9,857,1,0},
    {9,875,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,853,1,0},
    {9,857,1,0},
    {9,874,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,857,1,0},
    {9,876,1,0},
    {9,875,1,0},
    {9,857,1,0},
};
int nBox2212[214][4] =
{
    {0,0,0,213},
    {19,12096,1,10},
    {19,12097,1,10},
    {19,12098,1,10},
    {19,12099,1,10},
    {19,12100,1,10},
    {19,12101,1,10},
    {19,12102,1,10},
    {19,12096,1,11},
    {19,12097,1,11},
    {19,12096,1,10},
    {19,12097,1,10},
    {19,12098,1,10},
    {19,12099,1,10},
    {19,12100,1,10},
    {19,12101,1,10},
    {19,12102,1,10},
    {19,12103,1,10},
    {19,12104,1,10},
    {19,12105,1,10},
    {19,12098,1,11},
    {19,12099,1,11},
    {19,12096,1,12},
    {19,12097,1,12},
    {19,12096,1,10},
    {19,12097,1,10},
    {19,12098,1,10},
    {19,12099,1,10},
    {19,12100,1,10},
    {19,12101,1,10},
    {19,12102,1,10},
    {19,12103,1,10},
    {19,12104,1,10},
    {19,12105,1,10},
    {19,12098,1,12},
    {19,12099,1,12},
    {19,12096,1,11},
    {19,12097,1,11},
    {19,12098,1,11},
    {19,12099,1,11},
    {19,12100,1,11},
    {19,12101,1,11},
    {19,12102,1,11},
    {19,12103,1,11},
    {19,12104,1,11},
    {19,12105,1,11},
    {19,12100,1,12},
    {19,12101,1,12},
    {19,12102,1,12},
    {19,12103,1,12},
    {19,12104,1,12},
    {19,12105,1,12},
    {19,12100,1,11},
    {19,12101,1,11},
    {19,12102,1,11},
    {19,12103,1,11},
    {19,12104,1,11},
    {19,12105,1,11},
    {19,12103,1,10},
    {19,12104,1,10},
    {19,12105,1,10},
    {19,12096,1,10},
    {19,12097,1,10},
    {19,12098,1,10},
    {19,12099,1,10},
    {19,12100,1,10},
    {19,12101,1,10},
    {19,12102,1,10},
    {19,12103,1,10},
    {19,12104,1,10},
    {19,12105,1,10},
    {19,12096,1,10},
    {19,12097,1,10},
    {19,12096,1,11},
    {19,12097,1,11},
    {19,12098,1,11},
    {19,12099,1,11},
    {19,12100,1,11},
    {19,12101,1,11},
    {19,12102,1,11},
    {19,12103,1,11},
    {19,12104,1,11},
    {19,12105,1,11},
    {19,12098,1,10},
    {19,12099,1,10},
    {19,12100,1,10},
    {19,12101,1,10},
    {19,12096,1,12},
    {19,12097,1,12},
    {19,12098,1,12},
    {19,12099,1,12},
    {19,12100,1,12},
    {19,12101,1,12},
    {19,12102,1,12},
    {19,12103,1,12},
    {19,12104,1,12},
    {19,12105,1,12},
    {19,12102,1,10},
    {19,12103,1,10},
    {19,12104,1,10},
    {19,12105,1,10},
    {19,12096,1,11},
    {19,12097,1,11},
    {19,12098,1,11},
    {19,12099,1,11},
    {19,12096,1,13},
    {19,12097,1,13},
    {19,12098,1,13},
    {19,12099,1,13},
    {19,12100,1,13},
    {19,12101,1,13},
    {19,12102,1,13},
    {19,12103,1,13},
    {19,12104,1,13},
    {19,12105,1,13},
    {19,12100,1,11},
    {19,12101,1,11},
    {19,12102,1,11},
    {19,12103,1,11},
    {19,12104,1,11},
    {19,12105,1,11},
    {19,12096,1,10},
    {19,12096,1,14},
    {19,12097,1,14},
    {19,12096,1,11},
    {19,12097,1,11},
    {19,12098,1,11},
    {19,12099,1,11},
    {19,12100,1,11},
    {19,12101,1,11},
    {19,12102,1,11},
    {19,12103,1,11},
    {19,12104,1,11},
    {19,12105,1,11},
    {19,12098,1,14},
    {19,12099,1,14},
    {19,12100,1,14},
    {19,12101,1,14},
    {19,12102,1,14},
    {19,12103,1,14},
    {19,12104,1,14},
    {19,12105,1,14},
    {19,12097,1,10},
    {19,12098,1,10},
    {19,12096,1,12},
    {19,12097,1,12},
    {19,12098,1,12},
    {19,12099,1,12},
    {19,12100,1,12},
    {19,12101,1,12},
    {19,12102,1,12},
    {19,12103,1,12},
    {19,12096,1,13},
    {19,12097,1,13},
    {19,12096,1,15},
    {19,12097,1,15},
    {19,12098,1,15},
    {19,12096,1,12},
    {19,12097,1,12},
    {19,12098,1,12},
    {19,12099,1,12},
    {19,12100,1,12},
    {19,12101,1,12},
    {19,12102,1,12},
    {19,12103,1,12},
    {19,12104,1,12},
    {19,12105,1,12},
    {19,12099,1,15},
    {19,12100,1,15},
    {19,12101,1,15},
    {19,12096,1,10},
    {19,12097,1,10},
    {19,12098,1,10},
    {19,12099,1,10},
    {19,12100,1,10},
    {19,12101,1,10},
    {19,12102,1,10},
    {19,12103,1,10},
    {19,12104,1,10},
    {19,12105,1,10},
    {19,12102,1,15},
    {19,12103,1,15},
    {19,12104,1,15},
    {19,12105,1,15},
    {19,12098,1,13},
    {19,12099,1,13},
    {19,12096,1,12},
    {19,12097,1,12},
    {19,12098,1,12},
    {19,12099,1,12},
    {19,12100,1,12},
    {19,12101,1,12},
    {19,12102,1,12},
    {19,12103,1,12},
    {19,12104,1,12},
    {19,12105,1,12},
    {19,12100,1,13},
    {19,12101,1,13},
    {19,12102,1,13},
    {19,12103,1,13},
    {19,12104,1,13},
    {19,12105,1,13},
    {19,12104,1,12},
    {19,12105,1,12},
    {19,12096,1,10},
    {19,12097,1,10},
    {19,12098,1,10},
    {19,12099,1,10},
    {19,12100,1,10},
    {19,12101,1,10},
    {19,12102,1,10},
    {19,12103,1,10},
    {19,12104,1,10},
    {19,12105,1,10},
};
int nBox3239[54][4] =
{
    {0,0,0,53},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3246,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3247,1,0},
    {7,3244,1,0},
    {7,3248,1,0},
    {7,3237,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3247,1,0},
    {7,3246,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3246,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3246,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3247,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3246,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3246,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3247,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3245,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
    {7,3244,1,0},
};
int nBox3131[5][4] =
{
    {0,0,0,4},
    {9,1049,1,0},
    {9,1059,1,0},
    {9,1172,1,0},
    {9,1079,1,0},
};
int nBox2336[11][4] =
{
    {0,0,0,10},
    {1,14639,1,0},
    {1,14640,1,0},
    {1,14641,1,0},
    {1,14642,1,0},
    {1,14643,1,0},
    {1,14644,1,0},
    {1,14645,1,0},
    {1,14646,1,0},
    {1,14647,1,0},
    {1,14648,1,0},
};
int nBox2018[42][4] =
{
    {0,0,0,41},
    {3,3237,2,0},
    {3,3238,2,0},
    {3,3513,1,0},
    {3,3730,1,0},
    {3,3305,2,0},
    {3,3034,2,0},
    {3,3035,2,0},
    {3,3273,2,0},
    {3,1051,1,0},
    {7,645,1,0},
    {3,3237,2,0},
    {3,3238,2,0},
    {3,3513,1,0},
    {3,3730,1,0},
    {3,3305,2,0},
    {3,3034,2,0},
    {3,3035,2,0},
    {3,3273,2,0},
    {3,1051,1,0},
    {7,646,1,0},
    {3,3888,1,0},
    {3,3237,2,0},
    {3,3238,2,0},
    {3,3513,1,0},
    {3,3730,1,0},
    {3,3305,2,0},
    {3,3034,2,0},
    {3,3035,2,0},
    {3,3273,2,0},
    {3,1051,1,0},
    {7,646,1,0},
    {3,3888,1,0},
    {3,3237,2,0},
    {3,3238,2,0},
    {3,3513,1,0},
    {3,3730,1,0},
    {3,3305,2,0},
    {3,3034,2,0},
    {3,3035,2,0},
    {3,3273,2,0},
    {3,1051,1,0},
};
int nBox3130[9][4] =
{
    {0,0,0,8},
    {1,14637,1,0},
    {1,14638,1,0},
    {1,14789,1,0},
    {1,14790,1,0},
    {1,14791,1,0},
    {1,14792,1,0},
    {1,14793,1,0},
    {1,14794,1,0},
};
int nBox1550[3][4] =
{
    {0,0,0,2},
    {7,1993,1,0},
    {7,1994,25,0},
};
int nBox1554[351][4] =
{
    {0,0,0,350},
    {19,11677,1,10},
    {19,11678,1,10},
    {19,11677,1,9},
    {19,11678,1,9},
    {19,11679,1,9},
    {19,11680,1,9},
    {19,11681,1,9},
    {19,11682,1,9},
    {19,11683,1,9},
    {19,11684,1,9},
    {19,11685,1,9},
    {19,11686,1,9},
    {19,11679,1,10},
    {19,11680,1,10},
    {19,11677,1,8},
    {19,11678,1,8},
    {19,11679,1,8},
    {19,11680,1,8},
    {19,11681,1,8},
    {19,11682,1,8},
    {19,11683,1,8},
    {19,11684,1,8},
    {19,11685,1,8},
    {19,11686,1,8},
    {19,11681,1,10},
    {19,11682,1,10},
    {19,11683,1,10},
    {19,11677,1,11},
    {19,11678,1,11},
    {19,11677,1,8},
    {19,11678,1,8},
    {19,11679,1,8},
    {19,11680,1,8},
    {19,11681,1,8},
    {19,11682,1,8},
    {19,11683,1,8},
    {19,11684,1,8},
    {19,11685,1,8},
    {19,11686,1,8},
    {19,11679,1,11},
    {19,11680,1,11},
    {19,11677,1,12},
    {19,11678,1,12},
    {19,11677,1,9},
    {19,11678,1,9},
    {19,11679,1,9},
    {19,11680,1,9},
    {19,11681,1,9},
    {19,11682,1,9},
    {19,11683,1,9},
    {19,11684,1,9},
    {19,11685,1,9},
    {19,11686,1,9},
    {19,11679,1,12},
    {19,11680,1,12},
    {19,11681,1,12},
    {19,11677,1,7},
    {19,11678,1,7},
    {19,11679,1,7},
    {19,11680,1,7},
    {19,11681,1,7},
    {19,11682,1,7},
    {19,11683,1,7},
    {19,11684,1,7},
    {19,11685,1,7},
    {19,11686,1,7},
    {19,11682,1,12},
    {19,11683,1,12},
    {19,11684,1,12},
    {19,11685,1,12},
    {19,11686,1,12},
    {19,11681,1,11},
    {19,11682,1,11},
    {19,11683,1,11},
    {19,11684,1,11},
    {19,11685,1,11},
    {19,11686,1,11},
    {19,11677,1,9},
    {19,11678,1,9},
    {19,11679,1,9},
    {19,11680,1,9},
    {19,11681,1,9},
    {19,11682,1,9},
    {19,11683,1,9},
    {19,11684,1,9},
    {19,11685,1,9},
    {19,11686,1,9},
    {19,11684,1,10},
    {19,11685,1,10},
    {19,11686,1,10},
    {19,11677,1,10},
    {19,11678,1,10},
    {19,11679,1,10},
    {19,11680,1,10},
    {19,11681,1,10},
    {19,11682,1,10},
    {19,11683,1,10},
    {19,11684,1,10},
    {19,11685,1,10},
    {19,11686,1,10},
    {19,11677,1,10},
    {19,11678,1,10},
    {19,11677,1,11},
    {19,11678,1,11},
    {19,11679,1,11},
    {19,11680,1,11},
    {19,11681,1,11},
    {19,11682,1,11},
    {19,11683,1,11},
    {19,11684,1,11},
    {19,11685,1,11},
    {19,11686,1,11},
    {19,11677,1,7},
    {19,11678,1,7},
    {19,11679,1,7},
    {19,11680,1,7},
    {19,11681,1,7},
    {19,11682,1,7},
    {19,11683,1,7},
    {19,11684,1,7},
    {19,11685,1,7},
    {19,11686,1,7},
    {19,11679,1,10},
    {19,11680,1,10},
    {19,11681,1,10},
    {19,11682,1,10},
    {19,11677,1,12},
    {19,11678,1,12},
    {19,11679,1,12},
    {19,11680,1,12},
    {19,11681,1,12},
    {19,11682,1,12},
    {19,11677,1,6},
    {19,11678,1,6},
    {19,11679,1,6},
    {19,11680,1,6},
    {19,11681,1,6},
    {19,11682,1,6},
    {19,11683,1,6},
    {19,11684,1,6},
    {19,11685,1,6},
    {19,11686,1,6},
    {19,11683,1,12},
    {19,11684,1,12},
    {19,11685,1,12},
    {19,11686,1,12},
    {19,11683,1,10},
    {19,11684,1,10},
    {19,11685,1,10},
    {19,11686,1,10},
    {19,11677,1,11},
    {19,11678,1,11},
    {19,11679,1,11},
    {19,11680,1,11},
    {19,11677,1,13},
    {19,11678,1,13},
    {19,11679,1,13},
    {19,11680,1,13},
    {19,11681,1,13},
    {19,11682,1,13},
    {19,11683,1,13},
    {19,11684,1,13},
    {19,11685,1,13},
    {19,11686,1,13},
    {19,11681,1,11},
    {19,11682,1,11},
    {19,11683,1,11},
    {19,11684,1,11},
    {19,11685,1,11},
    {19,11686,1,11},
    {19,11677,1,10},
    {19,11677,1,14},
    {19,11677,1,6},
    {19,11678,1,6},
    {19,11679,1,6},
    {19,11680,1,6},
    {19,11681,1,6},
    {19,11682,1,6},
    {19,11683,1,6},
    {19,11684,1,6},
    {19,11685,1,6},
    {19,11686,1,6},
    {19,11678,1,14},
    {19,11679,1,14},
    {19,11680,1,14},
    {19,11681,1,14},
    {19,11682,1,14},
    {19,11683,1,14},
    {19,11684,1,14},
    {19,11677,1,5},
    {19,11678,1,5},
    {19,11679,1,5},
    {19,11680,1,5},
    {19,11681,1,5},
    {19,11682,1,5},
    {19,11683,1,5},
    {19,11684,1,5},
    {19,11685,1,5},
    {19,11686,1,5},
    {19,11685,1,14},
    {19,11686,1,14},
    {19,11678,1,10},
    {19,11679,1,10},
    {19,11677,1,12},
    {19,11678,1,12},
    {19,11679,1,12},
    {19,11680,1,12},
    {19,11681,1,12},
    {19,11682,1,12},
    {19,11683,1,12},
    {19,11684,1,12},
    {19,11677,1,13},
    {19,11678,1,13},
    {19,11677,1,15},
    {19,11678,1,15},
    {19,11679,1,15},
    {19,11677,1,1},
    {19,11678,1,1},
    {19,11679,1,1},
    {19,11680,1,1},
    {19,11681,1,1},
    {19,11682,1,1},
    {19,11683,1,1},
    {19,11684,1,1},
    {19,11685,1,1},
    {19,11686,1,1},
    {19,11680,1,15},
    {19,11677,1,5},
    {19,11678,1,5},
    {19,11679,1,5},
    {19,11680,1,5},
    {19,11681,1,5},
    {19,11682,1,5},
    {19,11683,1,5},
    {19,11684,1,5},
    {19,11685,1,5},
    {19,11686,1,5},
    {19,11681,1,15},
    {19,11677,1,1},
    {19,11678,1,1},
    {19,11679,1,1},
    {19,11680,1,1},
    {19,11681,1,1},
    {19,11682,1,1},
    {19,11683,1,1},
    {19,11684,1,1},
    {19,11685,1,1},
    {19,11686,1,1},
    {19,11682,1,15},
    {19,11677,1,4},
    {19,11678,1,4},
    {19,11679,1,4},
    {19,11680,1,4},
    {19,11681,1,4},
    {19,11682,1,4},
    {19,11683,1,4},
    {19,11684,1,4},
    {19,11685,1,4},
    {19,11686,1,4},
    {19,11683,1,15},
    {19,11677,1,2},
    {19,11678,1,2},
    {19,11679,1,2},
    {19,11680,1,2},
    {19,11681,1,2},
    {19,11682,1,2},
    {19,11683,1,2},
    {19,11684,1,2},
    {19,11685,1,2},
    {19,11686,1,2},
    {19,11684,1,15},
    {19,11677,1,1},
    {19,11678,1,1},
    {19,11679,1,1},
    {19,11680,1,1},
    {19,11681,1,1},
    {19,11682,1,1},
    {19,11683,1,1},
    {19,11684,1,1},
    {19,11685,1,1},
    {19,11686,1,1},
    {19,11685,1,15},
    {19,11686,1,15},
    {19,11677,1,4},
    {19,11678,1,4},
    {19,11679,1,4},
    {19,11680,1,4},
    {19,11681,1,4},
    {19,11682,1,4},
    {19,11683,1,4},
    {19,11684,1,4},
    {19,11685,1,4},
    {19,11686,1,4},
    {19,11679,1,13},
    {19,11680,1,13},
    {19,11681,1,13},
    {19,11682,1,13},
    {19,11677,1,2},
    {19,11678,1,2},
    {19,11679,1,2},
    {19,11680,1,2},
    {19,11681,1,2},
    {19,11682,1,2},
    {19,11683,1,2},
    {19,11684,1,2},
    {19,11685,1,2},
    {19,11686,1,2},
    {19,11683,1,13},
    {19,11684,1,13},
    {19,11685,1,13},
    {19,11677,1,3},
    {19,11678,1,3},
    {19,11679,1,3},
    {19,11680,1,3},
    {19,11681,1,3},
    {19,11682,1,3},
    {19,11683,1,3},
    {19,11684,1,3},
    {19,11685,1,3},
    {19,11686,1,3},
    {19,11686,1,13},
    {19,11685,1,12},
    {19,11686,1,12},
    {19,11680,1,10},
    {19,11677,1,3},
    {19,11678,1,3},
    {19,11679,1,3},
    {19,11680,1,3},
    {19,11681,1,3},
    {19,11682,1,3},
    {19,11683,1,3},
    {19,11684,1,3},
    {19,11685,1,3},
    {19,11686,1,3},
    {19,11681,1,10},
    {19,11682,1,10},
    {19,11683,1,10},
    {19,11684,1,10},
    {19,11685,1,10},
    {19,11686,1,10},
    {19,11677,1,1},
    {19,11678,1,1},
    {19,11679,1,1},
    {19,11680,1,1},
    {19,11681,1,1},
    {19,11682,1,1},
    {19,11683,1,1},
    {19,11684,1,1},
    {19,11685,1,1},
    {19,11686,1,1},
};
int nBox2299[6][4] =
{
    {0,0,0,5},
    {7,3360,1,0},
    {7,3361,1,0},
    {7,3362,1,0},
    {7,3363,1,0},
    {7,3364,1,0},
};
int nBox3314[6][4] =
{
    {0,0,0,5},
    {1,15583,1,0},
    {1,15584,1,0},
    {1,15585,1,0},
    {1,15586,1,0},
    {1,15587,1,0},
};
int nBox3315[6][4] =
{
    {0,0,0,5},
    {1,15588,1,0},
    {1,15589,1,0},
    {1,15590,1,0},
    {1,15591,1,0},
    {1,15592,1,0},
};
int BoxWeaponNewbie1[11][4] =
{
    {0 ,0,0,10},
    {19,12016,1,15},
    {19,12017,1,15},
    {19,12018,1,15},
    {19,12019,1,15},
    {19,12020,1,15},
    {19,12021,1,15},
    {19,12022,1,15},
    {19,12023,1,15},
    {19,12024,1,15},
    {19,12025,1,15},
};
int nBox3132[176][4] =
{
    {0,0,0,175},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,5,0},
    {7,2359,1,0},
    {7,2360,1,0},
    {7,2359,1,0},
    {7,557,5,0},
    {7,2359,1,0},
    {7,554,5,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2361,1,0},
    {7,2359,1,0},
    {3,3743,1,0},
    {3,3744,1,0},
    {3,3745,1,0},
    {3,3746,1,0},
    {7,2359,1,0},
    {3,3747,1,0},
    {7,2364,1,0},
    {7,2365,1,0},
    {7,2359,1,0},
    {7,2366,1,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,5,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,2359,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,2359,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,2359,1,0},
    {7,2359,1,0},
    {7,556,5,0},
    {7,557,5,0},
    {7,2359,10,0},
    {7,556,5,0},
    {7,2359,5,0},
    {7,557,5,0},
    {7,2359,10,0},
};
#endif // NewBoxCP
//Ky
/*int Ky1[2] = { 433 ,853};
int Ky2[2] = { 665 ,876};
int Ky3[2] = { 666 ,857};
int Ky4[2] = { 686 ,874};
int Ky5[2] = { 687 ,875};*/

int TiLeTinhLuyenQuanAo[15] = {1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 ,600000 ,400000,300000,200000,20000,7500,5000 };

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
            jb Default
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
/*void __declspec(naked)WeaponSkill()
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
    __asm   jmp[jmpBackAdd2]
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
__asm jb AddSkillWeapon
__asm cmp edi, 0x2F3F
__asm ja RemoveSKillFromOldSlot1DS
__asm mov eax, 0x1A
__asm call RemoveSkill1001
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot1DS:
__asm cmp edi, 0x2F40
__asm jb AddSkillWeapon
__asm cmp edi, 0x2F48
__asm ja RemoveSKillFromOldSlot2sd
__asm call RemoveSkill1002
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot2sd:
__asm cmp edi, 0x2F49
__asm jnz RemoveSKillFromOldSlot3sd
__asm mov eax, 0x1F
__asm call RemoveSkill1013
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot3sd :
    __asm cmp edi, 0x3072
__asm jb AddSkillWeapon
__asm cmp edi, 0x307B
__asm ja RemoveSKillFromOldSlot4sd
__asm mov eax,0x22
__asm call RemoveSkill1003
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot4sd:
__asm cmp edi, 0x3106
__asm jb AddSkillWeapon
__asm cmp edi, 0x310E
__asm ja RemoveSKillFromOldSlot5sd
__asm mov eax, 0x23
__asm call RemoveSkill1011
__asm jmp AddSkillWeapon
__asm RemoveSKillFromOldSlot5sd:
__asm cmp edi, 0x310F
__asm jnz AddSkillWeapon
__asm mov eax,0x24
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
__asm jb OutCheck
__asm cmp eax, 0x2F3F
__asm ja CheckSkill2
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
__asm jb CheckSkill3
__asm cmp eax, 0x2F48
__asm ja CheckSkill3
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
__asm jb OutCheck
__asm cmp eax, 0x307B
__asm ja CheckSkillNew2
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
__asm jb OutCheck
__asm cmp eax, 0x310E
__asm ja CheckSkillNew3
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
__asm jb AddSkillOldSlotB
__asm cmp edi, 0x2F3F
__asm ja RemoveSKillFromOldSlot1
__asm mov eax, 0x1A
__asm call RemoveSkill1001
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot1:
__asm cmp edi, 0x2F40
__asm jb AddSkillOldSlotB
__asm cmp edi, 0x2F48
__asm ja RemoveSKillFromOldSlot2
__asm call RemoveSkill1002
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot2:
__asm cmp edi, 0x2F49
__asm jnz RemoveSKillFromOldSlot3
__asm mov eax, 0x1F
__asm call RemoveSkill1013
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot3 :
    __asm cmp edi, 0x3072
__asm jb AddSkillOldSlotB
__asm cmp edi, 0x307B
__asm ja RemoveSKillFromOldSlot4
__asm mov eax, 0x22
__asm call RemoveSkill1003
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot4:
__asm cmp edi, 0x3106
__asm jb AddSkillOldSlotB
__asm cmp edi, 0x310E
__asm ja RemoveSKillFromOldSlot5
__asm mov eax, 0x23
__asm call RemoveSkill1011
__asm jmp AddSkillOldSlotB
__asm RemoveSKillFromOldSlot5:
__asm cmp edi, 0x310F
__asm jnz AddSkillOldSlotB
__asm mov eax, 0x24
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
__asm mov[esp + 0x24] , ax
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

}*/
DWORD checkInch;
DWORD ChecSlotToMove;
int ListSkillAdd[60][2];
void LoadInforWeaponSkillFunc()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char fname[200];
    sprintf(fname, "nfofile/listWeaponSkill.txt");
    int iLine = 0;
    char line[256];
    bool returninfo;
    returninfo = false;
    string filname;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        std::cout << "Error Load listWeaponSkill" << std::endl;
    }
    while (1)
    {

        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        sscanf(line, "%d %d", &ListSkillAdd[iLine][0], &ListSkillAdd[iLine][1]);
        ++iLine;
    }
    fclose(fp);
};
bool KiemTraTonTaiVk(int idVuKhi)
{
    bool resultCheck;
    resultCheck = false;
    for (int i = 0; i < 60; i++)
    {
        if (idVuKhi == ListSkillAdd[i][0])
        {
            resultCheck = true;
        }
    }
    return resultCheck;
}
int GetidSkill(int idVuKhi)
{
    int resultCheck;
    resultCheck = 0;
    for (int i = 0; i < 60; i++)
    {
        if (idVuKhi == ListSkillAdd[i][0])
        {
            resultCheck = ListSkillAdd[i][1];
        }
    }
    return resultCheck;
}
void gmAddSkillUser(int idSkill)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    CMSG_GM_ADD_SKILL pkUserAddSkill;
    memset(&pkUserAddSkill, 0, sizeof(CMSG_GM_ADD_SKILL));
    
}
void gmRemoveSkillUser(int idSkill)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    CMSG_GM_REM_SKILL pkUserRemoveSkill;
    memset(&pkUserRemoveSkill, 0, sizeof(CMSG_GM_REM_SKILL));
    
}
void RemoveandAddSkill(int idSkillAdd, int idSkillRemove)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    CMSG_GM_REM_SKILL pkUserRemoveSkill;
    CMSG_GM_ADD_SKILL pkUserAddSkill;
    memset(&pkUserAddSkill, 0, sizeof(CMSG_GM_ADD_SKILL));
    memset(&pkUserRemoveSkill, 0, sizeof(CMSG_GM_REM_SKILL));
    if (idSkillRemove != 0)
    {
        __asm
        {
            push 0xD
            mov ecx, StoreECX
            call get_name1
            push eax
            lea eax, pkUserRemoveSkill.cCharacName
            push eax
            mov eax, 0x006E3CC0
            call eax
            add esp, 0xC
            lea eax, pkUserRemoveSkill
            mov word ptr[eax], 0x12
            mov byte ptr[eax + 0x2], 0xA9
            lea eax, pkUserRemoveSkill.sSkillID
            mov ecx, idSkillRemove
            mov[eax], cx
            lea eax, pkUserRemoveSkill
            push eax
            mov ecx, DWORD PTR SS : [0x007763AC]
            mov eax, 0x0060E374
            call eax
        }
    }
    if (idSkillAdd != 0)
    {
        __asm
        {
            push 0xD
            mov ecx, StoreECX
            call get_name1
            push eax
            lea eax, pkUserAddSkill.cCharacName
            push eax
            mov eax, 0x006E3CC0
            call eax
            add esp, 0xC
            lea eax, pkUserAddSkill
            mov word ptr[eax], 0x18
            mov byte ptr[eax + 0x2], 0xA8
            lea eax, pkUserAddSkill.sSkillID
            mov ecx, idSkillAdd
            mov[eax], cx
            mov word ptr[eax + 0x2], 0x9
            mov byte ptr[eax + 0x3], 0x0
            lea eax, pkUserAddSkill
            push eax
            mov ecx, DWORD PTR SS : [0x007763AC]
            mov eax, 0x0060E2E2
            call eax
        }
    }
}
void __declspec(naked)EquitItemCheck()
{
    __asm
    {
        mov edi,[ebp-0xE754]
        xor eax,eax
        // Kiem Tra Vi Tri Vp
        mov al, [edi + 0x8]
        cmp eax,0xA
        jz ContinueToCheck
        cmp eax, 0xB
        jz AddSkill2
        cmp eax, 0x94
        jz Default
        xor eax,eax
        mov al, [edi + 0x7]
        cmp eax,0xA
        jz RemoveSkill
        cmp eax,0xB
        jz RemoveSkill
        cmp eax, 0x94
        jz Default
        mov ecx, [ebp - 0x00000DBC]
        imul eax, 0x60
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x8]
        jmp Default

        RemoveSkill:
        mov edi, [ebp - 0xE754]
        mov al, [edi + 0x7]
        mov ecx, [ebp - 0x00000DBC]
        imul eax, 0x60
        xor edx, edx
        mov dx, [ecx + eax + 0x128C + 0xA]
        push edx
        call GetidSkill
        add esp, 0x4
        push eax
        push 0x0
        mov ecx, [ebp - 0x00000DBC]
        call RemoveandAddSkill
        add esp, 0x8
        jmp Default

        ContinueToCheck:
        mov al, [edi + 0x7]
        cmp eax, 0xB
        jz Default
        AddSkill2 :
        mov edi, [ebp - 0xE754]
        mov al, [edi + 0x8]
        mov ecx, [ebp - 0x00000DBC]
        imul eax, 0x60
        xor edx, edx
        mov dx, [ecx + eax + 0x128C + 0xA]
        push edx
        call GetidSkill
        add esp, 0x4
        push eax
        mov edi, [ebp - 0xE754]
        mov al, [edi + 0x7]
        mov ecx, [ebp - 0x00000DBC]
        imul eax, 0x60
        xor edx, edx
        mov dx, [ecx + eax + 0x128C + 0xA]
        push edx
        call GetidSkill
        add esp, 0x4
        push eax
        mov ecx, [ebp - 0x00000DBC]
        call RemoveandAddSkill
        add esp, 0x8
        jmp Default
        // Kiem Tra Tin Vat
        //Chua Can Kiem Tra
        Default:
        ret
    }
}
bool CheckDieuKienNewSlot(int countSlotUnl, int SlotMove)
{
    switch (SlotMove)
    {
    case 140:
        if (countSlotUnl >= 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 141:
        if (countSlotUnl >= 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 142:
        if (countSlotUnl >= 3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 143:
        if (countSlotUnl >= 4)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 144:
        if (countSlotUnl >= 5)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 145:
        if (countSlotUnl >= 6)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 146:
        if (countSlotUnl >= 7)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    case 147:
        if (countSlotUnl == 8)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        break;
    default:
        return 1;
        break;
    }
};
bool CheckKhongDeoTvPhaiQuaTrai(InvenItemSlot& AddressItem, int SlotMove) {
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    switch (SlotMove)
    {
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:
    case 147:
        if (AddressItem.cSecond == 51)
        {
            return 0;
        }
        else
        {
            return 1;
        }
        break;
    default:
        return 1;
        break;
    }

};
bool KiemTraDieuKienTrungSlot(int moveTo)
{
    switch (moveTo)
    {
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:
    case 147:
        return 1;
    default:
        return 0;
        break;
    }
};
DWORD GetTimeRunCheckAnti()
{
    time_t timestarDao = time(nullptr);
    DWORD timeDaoStart = (DWORD)timestarDao;
    return timeDaoStart + 600;
}
bool ChongDeoTrung(unsigned int iDDeoVP)
{
    DWORD StoreECX;
    bool resultInfo = false;
    __asm mov StoreECX, ecx
    for (int i = 0; i < 16; i++)
    {
        if (!resultInfo)
        {
            if (i < 8)
            {
                unsigned int realSlot = i + 12;
                __asm
                {
                    mov eax, realSlot
                    imul eax, 0x60
                    mov ecx, StoreECX
                    xor edx, edx
                    mov dx, [ecx + eax + 0x128C + 0xA]
                    xor ecx, ecx
                    mov ecx, iDDeoVP
                    cmp edx, ecx
                    jnz CheckSlotKhacThap
                    mov eax, 1
                    mov resultInfo, al
                    CheckSlotKhacThap :
                }
            }
            else
            {
                unsigned int realSlot2 = i + 132;
                __asm
                {
                    mov eax, realSlot2
                    imul eax, 0x60
                    mov ecx, StoreECX
                    xor edx, edx
                    mov dx, [ecx + eax + 0x128C + 0xA]
                    xor ecx, ecx
                    mov ecx, iDDeoVP
                    cmp edx, ecx
                    jnz CheckSlotKhacCao
                    mov eax, 1
                    mov resultInfo, al
                    CheckSlotKhacCao :
                }
            }
        }
        
    }
    return resultInfo;
};
void __declspec(naked)WeaponSkill2()
{
    __asm{
        pushad
        call EquitItemCheck
        //
        mov edx, [ebp - 0xE754]
        xor eax, eax
        mov al, [edx + 0x8]
        push eax
        mov edx, [ebp - 0xE754]
        xor eax, eax
        mov al, [edx + 0x7]
        imul eax, 0x60
        mov ecx, [ebp - 0x00000DBC]
        lea edx, [ecx + eax + 0x128C]
        push edx
        mov ecx, [ebp - 0x00000DBC]
        call CheckKhongDeoTvPhaiQuaTrai
        add esp, 0x8
        test al, al
        jz OutAddItemToNewSlot
        //Check Level
        mov ecx, [ebp - 0xE754]
        xor eax, eax
        mov al, [ecx + 0x8]
        push eax
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        mov al, [ecx + 0xD63E]
        push eax
        call CheckDieuKienNewSlot
        add esp, 0x8
        test al, al
        jz OutAddItemToNewSlot
        // Kiem Tra Dieu Kien Khoa Tin Vat Trung
        mov edx, [ebp - 0xE754]
        xor eax, eax
        mov al, [edx + 0x8]
        push eax
        call KiemTraDieuKienTrungSlot
        add esp, 0x4
        test al, al
        jz EndCheckTv
        mov edx, [ebp - 0xE754]
        xor eax, eax
        mov al, [edx + 0x7]
        imul eax, 0x60
        mov ecx, [ebp - 0x00000DBC]
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x8]
        cmp edx, 0x9
        jnz EndCheckTv
        xor edx, edx
        mov dx, [ecx + eax + 0x128C + 0xA]
        push edx
        call CheckTinVat
        add esp, 0x4
        test al, al
        jz OutAddItemToNewSlot
        //
        mov edx, [ebp - 0xE754]
        xor eax, eax
        mov al, [edx + 0x7]
        imul eax, 0x60
        mov ecx, [ebp - 0x00000DBC]
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x9]
        cmp edx,1
        jz ChoDeo
        xor edx, edx
        mov dx, [ecx + eax + 0x128C + 0xA]
        push edx
        call ChongDeoTrung
        add esp,0x4
        test al,al
        jz ChoDeo
        jmp OutAddItemToNewSlot
        ChoDeo:
        //
        EndCheckTv :
        popad
            mov ecx, [ebp - 0x0000E754]
            push 0x005E1869
            ret

            OutAddItemToNewSlot :
        mov edx, [ebp - 0xE754]
            xor eax, eax
            mov al, [edx + 0x7]
            mov[edx + 0x8], al
            popad
            push 0x005E1929
            ret
     }
}
void __declspec(naked)FixDmage1()
{
    __asm cmp ecx,0x1
    __asm jnz CheckInt2
    __asm mov ecx,0x3
    __asm jmp DefaultOut
    __asm CheckInt2:
    __asm cmp ecx,0x2
    __asm jnz DefaultOut
    __asm mov ecx,0x3
    __asm DefaultOut:
    /*if (checkInch == 1 || checkInch == 2)
    {
        __asm mov ecx, 0x3
    }*/
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
float CheckToaDo[2][2] =
{
    {160.495,88.022},
    {272.425,120.653},
};
float CheckToaDo2[2][2] =
{
    {-418.616,-452.475},
    {220.588,148.999},
};
struct ToaDoUser
{
    float posx;
    float posy;
};
bool CheckCurrentPox(ToaDoUser * ToaDoCurrent)
{
    ToaDoUser* lsUser;
    lsUser = ToaDoCurrent;
    bool resultCheck;
    resultCheck = false;
    if (lsUser->posx >= CheckToaDo[1][1] && lsUser->posx <= CheckToaDo[1][0])
    {
        if (lsUser->posy <= CheckToaDo[0][0] && lsUser->posy >= CheckToaDo[0][1])
        {
            resultCheck = true;
        }
    }
    return resultCheck;
}
bool CheckCurrentPox2(ToaDoUser* ToaDoCurrent)
{
    ToaDoUser* lsUser;
    lsUser = ToaDoCurrent;
    bool resultCheck;
    resultCheck = false;
    if (lsUser->posx >= CheckToaDo2[1][1] && lsUser->posx <= CheckToaDo2[1][0])
    {
        if (lsUser->posy <= CheckToaDo2[0][0] && lsUser->posy >= CheckToaDo2[0][1])
        {
            resultCheck = true;
        }
    }
    return resultCheck;
}
float CheckToaDoTk1[2][2] =
{
    {431.168,358.470},
    {3.497 ,-84.492},
};
float CheckToaDoTk2[2][2] =
{
    {-375.507 ,-439.395},
    {146.478,62.203},
};
float CheckToaDoTk3[2][2] =
{
    {-347.945 ,-469.212},
    {-261.848 ,-431.675},
};
bool ToaDoBenTong(ToaDoUser* ToaDoCurrent)
{
    ToaDoUser* lsUser;
    lsUser = ToaDoCurrent;
    bool resultCheck;
    resultCheck = false;
    if (lsUser->posx >= CheckToaDoTk1[1][1] && lsUser->posx <= CheckToaDoTk1[1][0])
    {
        if (lsUser->posy <= CheckToaDoTk1[0][0] && lsUser->posy >= CheckToaDoTk1[0][1])
        {
            resultCheck = true;
        }
    }
    if (!resultCheck)
    {
        if (lsUser->posx >= CheckToaDoTk3[1][1] && lsUser->posx <= CheckToaDoTk3[1][0])
        {
            if (lsUser->posy <= CheckToaDoTk3[0][0] && lsUser->posy >= CheckToaDoTk3[0][1])
            {
                resultCheck = true;
            }
        }
    }
    return resultCheck;
}

bool ToaDoBenKim(ToaDoUser* ToaDoCurrent)
{
    ToaDoUser* lsUser;
    lsUser = ToaDoCurrent;
    bool resultCheck;
    resultCheck = false;
    if (lsUser->posx >= CheckToaDoTk2[1][1] && lsUser->posx <= CheckToaDoTk2[1][0])
    {
        if (lsUser->posy <= CheckToaDoTk2[0][0] && lsUser->posy >= CheckToaDoTk2[0][1])
        {
            resultCheck = true;
        }
    }
    if (!resultCheck)
    {
        if (lsUser->posx >= CheckToaDoTk3[1][1] && lsUser->posx <= CheckToaDoTk3[1][0])
        {
            if (lsUser->posy <= CheckToaDoTk3[0][0] && lsUser->posy >= CheckToaDoTk3[0][1])
            {
                resultCheck = true;
            }
        }
    }
    return resultCheck;
}
bool KiemTraToaDoUser(int type)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx;
    bool resultCheck;
    int typeUser;
    typeUser = type;
    if (typeUser == 1)
    {
        __asm
        {
             mov ecx, StoreECX
             lea ecx, [ecx + 0x5BC8]
             push ecx
             mov ecx, StoreECX
             call ToaDoBenTong
             add esp,0x4
             cmp al,0x1
             jnz KhongNamTrongViTri
             lea eax, resultCheck
             mov DWORD PTR [eax],0x1
             KhongNamTrongViTri:
        }
    }
    else if (typeUser == 2)
    {
        __asm
        {
            mov ecx, StoreECX
            lea ecx, [ecx + 0x5BC8]
            push ecx
            mov ecx, StoreECX
            call ToaDoBenKim
            add esp, 0x4
            cmp al, 0x1
            jnz KhongNamTrongViTri1
            lea eax, resultCheck
            mov DWORD PTR[eax], 0x1
            KhongNamTrongViTri1:
        }
    }
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
DWORD reportDamage = 0x0;
void __declspec(naked)MoreDamageSkill()
{
    __asm
    {
        pushad
        xor ebx, ebx
        mov edx, [ebp - 0xE6B0]
        cmp edx, 0xFFFF
        jbe Default
        SubAgain :
        sub edx, 0xFFFF
            add ebx, 0x01
            cmp edx, 0xFFFF
            ja SubAgain
            mov ecx, ebx
            mov[ebp - 0x833], dx
            mov ecx, [ebp - 0xDBC]
            mov[ecx + 0xCAB0], bl
            popad
            push 0x005DCFB7
            ret

            Default :
        popad
            xor edx,edx
            mov dx, [ebp - 0xE6B0]
            mov[ebp - 0x833], dx
            mov ecx, [ebp - 0xDBC]
            mov[ecx + 0xCAB0], 0x0
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
        jbe Default
        SubAgain :
        sub edx, 0xFFFF
            add ebx, 0x01
            cmp edx, 0xFFFF
            ja SubAgain
            mov ecx, ebx
            mov[ebp - 0x80B], dx
            mov ecx, [ebp - 0xDBC]
            mov[ecx + 0xCAB0], bl
            popad
            push 0x005DE4FA
            ret

            Default :
        popad
            mov dx, [ebp - 0xE6F4]
            mov[ebp - 0x80B], dx
            mov ecx, [ebp - 0xDBC]
            mov byte ptr [ecx + 0xCAB0], 0x0
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
        jbe Default
        SubAgain :
        sub edx, 0xFFFF
            add ebx, 0x01
            cmp edx, 0xFFFF
            ja SubAgain
            mov ecx, ebx
            mov[ebp - 0x909B], dx
            mov ecx, [ebp - 0xDBC]
            mov[ecx + 0xCAB0], bl
            popad
            push 0x005D7930
            ret

            Default :
        popad
            mov dx, [ebp - 0xE5F0]
            mov[ebp - 0x909B], dx
            mov ecx, [ebp - 0xDBC]
            mov byte ptr[ecx + 0xCAB0], 0x0
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
            /*xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx*/
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
                /*xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x6FD4]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FD4], ecx*/
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
        jbe Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            ja SubAgain2
            mov[eax + 0x10], cx
            mov ecx,[ebp+0x8]
            mov byte ptr[ecx + 0xCAB0], bl
            popad
            push 0x0058816B
            ret

            Default :
        popad
            mov  cx, [ebp - 0x24]
            mov[eax + 0x10], cx
            mov ecx, [ebp + 0x8]
            mov byte ptr[ecx + 0xCAB0], 0x0
            push 0x00588159
            ret
    }
}
void __declspec(naked)FixAmDamagePvp()
{
    __asm
    {
        sub     edx, [ebp - 0x84]
        push 0x004B99CD
        ret
    }
}
void __declspec(naked)FixAmDamagePvp1()
{
    __asm
    {
        sub eax, edx
        xor edx, edx
        mov ecx, [ebp - 0xBC]
        mov dl, [ecx + 0xD561]
        test edx, edx
        jz Default
        mov[ecx + 0xD56C], eax
        //Min
        mov ecx, [ebp - 0xBC]
        fild[ecx + 0xD561]
        fimul dword ptr[ecx + 0x0000D56C]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov ecx, [ebp - 0xBC]
        mov edx, [ecx + 0x0000D56C]
        sub edx, eax
        mov[ebp - 0x54], edx
        push 0x004B9A01
        ret

        Default :
        mov [ebp - 0x54], eax
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
        jbe Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            ja SubAgain2
            mov[eax + 0x10], cx
            mov[eax + 0x13], cx
            mov ecx, [ebp + 0x8]
            mov[ecx + 0xCAB0], bl
            popad
            push 0x00588035
            ret

            Default :
        popad
            mov  cx, [ebp - 0x24]
            mov[eax + 0x10], cx
            mov ecx, [ebp + 0x8]
            mov byte ptr [ecx + 0xCAB0], 0x00
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
        jb Check2
        cmp eax, 0x11
        ja Check2
        add eax, 0x12
        jmp Default
        //
        Check2 :
        cmp eax, 0x28
            jb Check3
            cmp eax, 0x37
            ja Check3
            add eax, 0x14
            jmp Default

            //
            Check3 :
        cmp eax, 0x50
            jb Check4
            cmp eax, 0x5F
            ja Check4
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
    __asm mov[ebp - 0x84], eax
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
        jbe Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            ja SubAgain2
            mov[eax + 0x10], cx
            mov[eax + 0x16], cx
            mov[eax + 0x13], cx
            mov ecx, [ebp + 0x8]
            mov[ecx + 0xCAB0], bl
            popad
            push 0x00587EA3
            ret

            Default :
        popad
            mov  cx, [ebp - 0x24]
            mov[eax + 0x10], cx
            mov ecx, [ebp + 0x8]
            mov byte ptr [ecx + 0xCAB0], 0x0
            push 0x00587E8D
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
        jbe Default
        SubAgain2 :
        sub ecx, 0xFFFF
            add ebx, 0x01
            cmp ecx, 0xFFFF
            ja SubAgain2
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
void LogUserItemExChange(int typeID, int IDitem, int count, int MapID,int uniqueid)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char NameUser[13];
    char fname[128];
    sprintf(fname, "C:/9Dragons/LogUserItem/MacThaiLan/%d_%dmap.txt", uniqueid, MapID);
    InforUserTK* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    int iLine = 0;
    time_t now = time(0);
    char* dt = ctime(&now);
    char line[256];
    __asm
    {
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, NameUser
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
    }
    string filname;
    FILE* fp = fopen(fname, "a");
    if (fp)
    {
        fprintf(fp, "%s %u %u %u %s ",
            NameUser, typeID, IDitem, count, dt
        );
        returninfo = true;
        fclose(fp);
    }
    else
    {
        std::cout << "Error Create File and Write" << NameUser << typeID << IDitem << std::endl;
    }

};
struct PackagePetDao
{
    u_short	usLength;
    u_char	cMessage;
    u_char  ucMode;
    u_char  InforReport;//0x4
    unsigned short typePet;
    unsigned short idPet;
    unsigned char level;
    unsigned char statusPet;
    u_short idSkill5;
    u_short dHonNang;
    unsigned int TimeLeft;
    u_char UnknowByte;
    //
    unsigned short typePet1;
    unsigned short idPet1;
    unsigned char level1;
    unsigned char statusPet1;
    u_short idSkill51;
    u_short dHonNang1;
    unsigned int TimeLeft1;
    u_char UnknowByte1;
    //
    unsigned short typePet2;
    unsigned short idPet2;
    unsigned char level2;
    unsigned char statusPet2;
    u_short idSkill52;
    u_short dHonNang2;
    unsigned int TimeLeft2;
    u_char UnknowByte2;
    //
    unsigned short typePet3;
    unsigned short idPet3;
    unsigned char level3;
    unsigned char statusPet3;
    u_short idSkill53;
    u_short dHonNang3;
    unsigned int TimeLeft3;
    u_char UnknowByte3;
    //Vi tri Vp
    u_char VitriVp;
    u_char Count;
};
struct DataUseItemPet {
    unsigned short typePet;
    unsigned short idPet;
    unsigned char level;
    unsigned char statusPet;
    u_short idSkill5;
    u_short dHonNang;
    unsigned int timedaobatdau;
    unsigned int timedaoofEnd;
    u_char MapsDao;
    u_char UnknowByte;
    unsigned short typePet1;
    unsigned short idPet1;
    unsigned char level1;
    unsigned char statusPet1;
    u_short idSkill51;
    u_short dHonNang1;
    unsigned int timedaobatdau1;
    unsigned int timedaoofEnd1;
    u_char MapsDao1;
    u_char UnknowByte1;
    unsigned short typePet2;
    unsigned short idPet2;
    unsigned char level2;
    unsigned char statusPet2;
    u_short idSkill52;
    u_short dHonNang2;
    unsigned int timedaobatdau2;
    unsigned int timedaoofEnd2;
    u_char MapsDao2;
    u_char UnknowByte2;
    unsigned short typePet3;
    unsigned short idPet3;
    unsigned char level3;
    unsigned char statusPet3;
    u_short idSkill53;
    u_short dHonNang3;
    unsigned int timedaobatdau3;
    unsigned int timedaoofEnd3;
    u_char MapsDao3;
    u_char UnknowByte3;
};
void SendPackagePetDao(int InforPackage, DataUseItemPet* AddressPet, int vpvitri, int countvp)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    PackagePetDao userPackagePet;
    time_t timenow = time(nullptr);
    DWORD timecurGame = (DWORD)timenow;
    memset((&userPackagePet), 0, sizeof(PackagePetDao));
    userPackagePet.usLength = sizeof(PackagePetDao);
    userPackagePet.cMessage = 193;
    userPackagePet.InforReport = InforPackage;
    userPackagePet.ucMode = 239;
    //
    userPackagePet.typePet = *(&AddressPet->typePet);
    userPackagePet.idPet = *(&AddressPet->idPet);
    userPackagePet.level = *(&AddressPet->level);
    userPackagePet.statusPet = *(&AddressPet->statusPet);
    userPackagePet.idSkill5 = *(&AddressPet->idSkill5);
    userPackagePet.dHonNang = *(&AddressPet->dHonNang);
    DWORD timeleftDaoPet1 = *(&AddressPet->timedaoofEnd);
    DWORD TimeleftPet1;
    if (timeleftDaoPet1 > timecurGame)
    {
        TimeleftPet1 = timeleftDaoPet1 - timecurGame;
        TimeleftPet1 = TimeleftPet1 * 1000;
    }
    else
    {
        TimeleftPet1 = 0;
    }
    userPackagePet.TimeLeft = TimeleftPet1;
    //
    userPackagePet.typePet1 = *(&AddressPet->typePet1);
    userPackagePet.idPet1 = *(&AddressPet->idPet1);
    userPackagePet.level1 = *(&AddressPet->level1);
    userPackagePet.statusPet1 = *(&AddressPet->statusPet1);
    userPackagePet.idSkill51 = *(&AddressPet->idSkill51);
    userPackagePet.dHonNang1 = *(&AddressPet->dHonNang1);
    DWORD timeleftDaoPet2 = *(&AddressPet->timedaoofEnd1);
    DWORD TimeleftPet2;
    if (timeleftDaoPet2 > timecurGame)
    {
        TimeleftPet2 = timeleftDaoPet2 - timecurGame;
        TimeleftPet2 = TimeleftPet2 * 1000;
    }
    else
    {
        TimeleftPet2 = 0;
    }
    userPackagePet.TimeLeft1 = TimeleftPet2;
    //
    userPackagePet.typePet2 = *(&AddressPet->typePet2);
    userPackagePet.idPet2 = *(&AddressPet->idPet2);
    userPackagePet.level2 = *(&AddressPet->level2);
    userPackagePet.statusPet2 = *(&AddressPet->statusPet2);
    userPackagePet.idSkill52 = *(&AddressPet->idSkill52);
    userPackagePet.dHonNang2 = *(&AddressPet->dHonNang2);
    DWORD timeleftDaoPet3 = *(&AddressPet->timedaoofEnd2);
    DWORD TimeleftPet3;
    if (timeleftDaoPet3 > timecurGame)
    {
        TimeleftPet3 = timeleftDaoPet3 - timecurGame;
        TimeleftPet3 = TimeleftPet3 * 1000;
    }
    else
    {
        TimeleftPet3 = 0;
    }
    userPackagePet.TimeLeft2 = TimeleftPet3;
    //
    userPackagePet.typePet3 = *(&AddressPet->typePet3);
    userPackagePet.idPet3 = *(&AddressPet->idPet3);
    userPackagePet.level3 = *(&AddressPet->level3);
    userPackagePet.statusPet3 = *(&AddressPet->statusPet3);
    userPackagePet.idSkill53 = *(&AddressPet->idSkill53);
    userPackagePet.dHonNang3 = *(&AddressPet->dHonNang3);
    DWORD timeleftDaoPet4 = *(&AddressPet->timedaoofEnd3);
    DWORD TimeleftPet4;
    if (timeleftDaoPet4 > timecurGame)
    {
        TimeleftPet4 = timeleftDaoPet4 - timecurGame;
        TimeleftPet4 = TimeleftPet4 * 1000;
    }
    else
    {
        TimeleftPet4 = 0;
    }
    userPackagePet.TimeLeft3 = TimeleftPet4;
    //
    userPackagePet.VitriVp = vpvitri;
    userPackagePet.Count = countvp;
    __asm
    {
        lea eax, userPackagePet
        xor ecx, ecx
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePet
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
};
struct PackageSlot
{
    u_short	usLength;
    u_char	cMessage;
    u_char  ucMode;
    u_char  Result;
    u_char  SlotItem;
    u_char  CountItem;
    u_char  numberSlot;
    u_int   moneyCur;
};
void SendPackageInforSlot(u_int moneycurUser, int slotNumberUsed, int CountItem, int numberSlot, int resultUsed)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    PackageSlot userPackageSlot;
    memset((&userPackageSlot), 0, sizeof(PackageSlot));
    userPackageSlot.usLength = sizeof(PackageSlot);
    userPackageSlot.cMessage = 51;
    userPackageSlot.ucMode = 5;
    userPackageSlot.Result = resultUsed;
    userPackageSlot.numberSlot = numberSlot;
    userPackageSlot.SlotItem = slotNumberUsed;
    userPackageSlot.CountItem = CountItem;
    userPackageSlot.moneyCur = moneycurUser;
    __asm {
        lea eax, userPackageSlot
        xor ecx, ecx
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackageSlot
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
};
int ReadCountNewSlot(int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InfoUser/%d.txt", UniqueID);
    bool returninfo;
    returninfo = false;
    int iLine = 0;
    int countallNewSlot = 0;
    char line[256];
    string filname;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        return 0;
    }
    while (1)
    {
        ++iLine;
        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        //rewind(fp);
        sscanf(line, "%d",
            &countallNewSlot);
    }
    fclose(fp);
OutFun:
    return countallNewSlot;
}
bool ReadDataSlotFromText()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    __asm
    {
        xor eax, eax
        mov ecx, StoreEcx
        mov eax, [ecx + 0x1054]
        push eax
        call ReadCountNewSlot
        add esp, 0x4
        mov ecx, StoreEcx
        xor edx,edx
        mov dl,al
        mov [ecx + 0xD63E], dl
        push 4
        push edx
        push 0
        push 0
        push 0
        mov ecx, StoreEcx
        call SendPackageInforSlot
        add esp, 0x14
        CreateNewFile:
    }
}


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
        cmp al, 0x4444E
        jnz RsOther
        popad
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
            push 0x00522054
            ret

            RsOther :
        cmp al, 0x444D
            jnz RsOther1
            popad
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
                mov eax, 0x1
                push 0x00522054
                ret



            RsOther1 :
            cmp al, 0x4EA
            jnz UpdateCuongDoCloth
            popad
            jmp NotRequest
            CuongHoa10000:
            popad
            mov edx, [ebp + 0x8]
            xor eax, eax
            mov al, [edx + 0x4]
            imul eax, eax, 0x60
            mov ecx, [ebp - 0x6C]
            lea edx, [ecx + eax + 0x0000128C]
            xor eax,eax
            mov al,[edx+0x18]
            cmp eax,0xE
            ja NotRequest
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
            mov al, [edx + 0x18]
            add eax,0x1
            mov byte ptr[edx + 0x18], al
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
            push 0x00522054
            ret

            InChantRelicItem:
            mov al, [ecx + 0x8]
            cmp al, 0x7
            jnz JumOut
                xor eax,eax
                mov ax, [ecx + 0xA]
                cmp eax,0x4EA
                jz CuongHoa10000
                /*xor eax,eax
                mov ax, [ecx + 0xA]
                jmp AddSlotForRelic
                BackAddSlotForRelicCurrent:*/
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
                jmp JumOut
            JumOut :    
            popad
            mov edx, [ecx + 0x5320]
            push 0x00522009
            ret

            NotRequest :
            push 0x00522054
            ret

            WeaponUpgrade:
            mov ecx, [ebp + 0x8]
            xor edx, edx
            mov dl, [ecx + 0x5]
            imul edx, 0x60
            mov eax, [ebp - 0x6C]
            lea ecx, [eax + edx + 0x128C]
            mov[ebp - 0x50], ecx
            mov ax, [ecx + 0xA]
            cmp ax, 0x2F6
            jb JumOut
            cmp ax, 0x2FF
            ja ItemRs2122
            xor eax, eax
            lea eax, ListDa31
            jmp MainFun1

            ItemRs2122 :
        cmp ax, 0x309
            ja ItemRs3111
            xor eax, eax
            lea eax, ListDa32
            jmp MainFun1

            ItemRs3111 :
        cmp ax, 0x313
            ja ItemRs41
            xor eax, eax
            lea eax, ListDa33
            jmp MainFun1

            ItemRs41 :
        cmp ax, 0x31D
            ja ItemRs51
            xor eax, eax
            lea eax, ListDa34
            jmp MainFun1

            ItemRs51 :
        cmp ax, 0x327
            ja ItemRs61
            xor eax, eax
            lea eax, ListDa35
            jmp MainFun1

            ItemRs61 :
        cmp ax, 0x331
            ja ItemRs71
            xor eax, eax
            lea eax, ListDa1
            jmp MainFun1

            ItemRs71 :
        cmp ax, 0x33B
            ja ItemRs81
            xor eax, eax
            lea eax, ListDa2
            jmp MainFun1

            ItemRs81 :
        cmp ax, 0x345
            ja ItemRs91
            xor eax, eax
            lea eax, ListDa3
            jmp MainFun1

            ItemRs91 :
        cmp ax, 0x34F
            ja ItemRs101
            xor eax, eax
            lea eax, ListDa4
            jmp MainFun1

            ItemRs101 :
        cmp ax, 0x359
            ja ItemRs111
            xor eax, eax
            lea eax, ListDa5
            jmp MainFun1

            ItemRs111 :
        cmp ax, 0x363
            ja ItemRs121
            xor eax, eax
            lea eax, ListDa6
            jmp MainFun1

            ItemRs121 :
        cmp ax, 0x36D
            ja ItemRs131
            xor eax, eax
            lea eax, ListDa7
            jmp MainFun1

            ItemRs131 :
        cmp ax, 0x377
            ja ItemRs141
            xor eax, eax
            lea eax, ListDa8
            jmp MainFun1

            ItemRs141 :
        cmp ax, 0x381
            ja ItemRs151
            xor eax, eax
            lea eax, ListDa9
            jmp MainFun1

            ItemRs151 :
        cmp ax, 0x38B
            ja ItemRs161
            xor eax, eax
            lea eax, ListDa10
            jmp MainFun1

            ItemRs161 :
        cmp ax, 0x395
            ja ItemRs171
            xor eax, eax
            lea eax, ListDa11
            jmp MainFun1

            ItemRs171 :
        cmp ax, 0x39F
            ja ItemRs181
            xor eax, eax
            lea eax, ListDa12
            jmp MainFun1

            ItemRs181 :
        cmp ax, 0x3A9
            ja ItemRs191
            xor eax, eax
            lea eax, ListDa13
            jmp MainFun1

            ItemRs191 :
        cmp ax, 0x3B3
            ja ItemRs201
            xor eax, eax
            lea eax, ListDa14
            jmp MainFun1

            ItemRs201 :
        cmp ax, 0x3BD
            ja ItemRs211
            xor eax, eax
            lea eax, ListDa15
            jmp MainFun1

            ItemRs211 :
        cmp ax, 0x3C7
            ja ItemRs221
            xor eax, eax
            lea eax, ListDa16
            jmp MainFun1

            ItemRs221 :
        cmp ax, 0x3D1
            ja ItemRs231
            xor eax, eax
            lea eax, ListDa17
            jmp MainFun1

            ItemRs231 :
        cmp ax, 0x3DB
            ja ItemRs241
            xor eax, eax
            lea eax, ListDa18
            jmp MainFun1

            ItemRs241 :
        cmp ax, 0x3E5
            ja ItemRs251
            xor eax, eax
            lea eax, ListDa19
            jmp MainFun1

            ItemRs251 :
        cmp ax, 0x3EF
            ja ItemRs261
            xor eax, eax
            lea eax, ListDa20
            jmp MainFun1

            ItemRs261 :
        cmp ax, 0x3F9
            ja ItemRs271
            xor eax, eax
            lea eax, ListDa21
            jmp MainFun1

            ItemRs271 :
        cmp ax, 0x403
            ja ItemRs281
            xor eax, eax
            lea eax, ListDa22
            jmp MainFun1

            ItemRs281 :
        cmp ax, 0x40D
            ja ItemRs291
            xor eax, eax
            lea eax, ListDa23
            jmp MainFun1

            ItemRs291 :
        cmp ax, 0x417
            ja ItemRs301
            xor eax, eax
            lea eax, ListDa24
            jmp MainFun1

            ItemRs301 :
        cmp ax, 0x421
            ja ItemRs311
            xor eax, eax
            lea eax, ListDa25
            jmp MainFun1

            ItemRs311 :
        cmp ax, 0x42B
            ja ItemRs321
            xor eax, eax
            lea eax, ListDa26
            jmp MainFun1


            ItemRs321 :
        cmp ax, 0x435
            ja ItemRs331
            xor eax, eax
            lea eax, ListDa27
            jmp MainFun1


            ItemRs331 :
        cmp ax, 0x43F
            ja ItemRs341
            xor eax, eax
            lea eax, ListDa28
            jmp MainFun1

            ItemRs341 :
        cmp ax, 0x449
            ja ItemRs351
            xor eax, eax
            lea eax, ListDa29
            jmp MainFun1

            ItemRs351 :
        cmp ax, 0x453
            ja JumOut
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
            jae Uprade2
            mov ebx,0x00
            jmp CompleteCheck
            Uprade2:
            cmp ebx, 0x20
            jae Uprade3
                mov ebx, 0x01
                jmp CompleteCheck
                Uprade3 :
            cmp ebx, 0x30
                jae Uprade4
                mov ebx, 0x02
                jmp CompleteCheck

                Uprade4 :
            cmp ebx, 0x40
                jae Uprade5
                mov ebx, 0x03
                jmp CompleteCheck

                Uprade5 :
            cmp ebx, 0x50
                jae Uprade6
                mov ebx, 0x04
                jmp CompleteCheck

                Uprade6 :
            cmp ebx, 0x60
                jae Uprade7
                mov ebx, 0x05
                jmp CompleteCheck

                Uprade7 :
            cmp ebx, 0x70
                jae Uprade8
                mov ebx, 0x06
                jmp CompleteCheck

                Uprade8 :
            cmp ebx, 0x80
                jae Uprade9
                mov ebx, 0x07
                jmp CompleteCheck

                Uprade9 :
            cmp ebx, 0x90
                jae Uprade10
                mov ebx, 0x08
                jmp CompleteCheck

                Uprade10 :
            cmp ebx, 0xA0
                jae JumOut
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
            jmp CheckItemType3
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
            jae AddSlot5Relic
            mov eax,[esp+0x4]
            cmp eax,0x76D
            jnz EndCheckAdd
            mov[edx + 0x24 + 0x4 + ecx], 0x1
            jmp EndCheckAdd
            AddSlot5Relic:
            cmp ecx, 0x19
            jae AddSlot6Relic
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
                jae Uprade232
                mov ebx, 0x00
                ret
                Uprade232 :
            cmp ebx, 0x20
                jae Uprade3fd
                mov ebx, 0x01
                ret
                Uprade3fd :
            cmp ebx, 0x30
                jae Uprade4fd
                mov ebx, 0x02
                ret

                Uprade4fd :
            cmp ebx, 0x40
                jae Uprade5fd
                mov ebx, 0x03
                ret

                Uprade5fd :
            cmp ebx, 0x50
                jae Uprade6fd
                mov ebx, 0x04
                ret

                Uprade6fd :
            cmp ebx, 0x60
                jae Uprade7fd
                mov ebx, 0x05
                ret

                Uprade7fd :
            cmp ebx, 0x70
                jae Uprade8fd
                mov ebx, 0x06
                ret

                Uprade8fd :
            cmp ebx, 0x80
                jae Uprade9fd
                mov ebx, 0x07
                ret
                Uprade9fd :
            cmp ebx, 0x90
                jae Uprade10fd
                mov ebx, 0x08
                ret

                Uprade10fd :
            cmp ebx, 0xA0
                jae Uprade11fd
                mov ebx, 0x9
                ret

                Uprade11fd :
                mov ebx, 0xA
                ret


                UpdateCuongDoCloth:
                cmp al, 0x62
                jnz ChangeOptCloth
                    mov ecx, [ebp + 0x8]
                    xor edx, edx
                    mov  dl, [ecx + 0x4]
                    imul edx, 0x60
                    mov  eax, [ebp - 0x6C]
                    xor ecx, ecx
                    mov cl, [eax + edx + 0x128C + 0x28]
                    cmp ecx,0x8
                    ja JumOut
                    xor ecx,ecx
                    mov cl, [eax + edx + 0x128C + 0x18]
                    test ecx,ecx
                    jz JumOut
                    popad
                    mov ecx, [ebp - 0x6C]
                    mov eax, 0x50F9E2
                    call eax
                    cmp eax, 0x186A0
                    jb NotRequest
                    mov edx, [ebp - 0x50]
                    mov cl, [edx + 0xF]
                    sub cl, 0x1
                    mov[edx + 0xF], cl
                    cmp cl, 0x0
                    jnz KoBangKhong132
                    mov ecx, [ebp + 0x8]
                    mov cl, [ecx + 0x5]
                    push ecx
                    mov ecx, [ebp - 0x6C]
                    mov eax, 0x004B2960
                    call eax
                    KoBangKhong132 :
                    mov edx, [ebp + 0x8]
                    xor eax, eax
                    mov al, [edx + 0x4]
                    imul eax, eax, 0x60
                    mov ecx, [ebp - 0x6C]
                    lea edx, [ecx + eax + 0x0000128C]
                    mov  AdresStoreIem, edx
                    mov[ebp - 0x60], 0xEC
                    mov[ebp - 0x5F], 0x00
                    mov[ebp - 0x5E], 0x7C
                    mov[ebp - 0x5D], 0x04
                    mov[ebp - 0x5C], 0x0A
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
                    sub eax, 0x186A0
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
                    mov ecx, [ebp + 0x8]
                    xor edx, edx
                    mov  dl, [ecx + 0x4]
                    imul edx, 0x60
                    mov  eax, [ebp - 0x6C]
                    xor ecx,ecx
                    mov cl, [eax + edx + 0x128C+0x28]
                    add ecx,0x1
                    mov[eax + edx + 0x128C + 0x28],cl
                    mov eax,0x1
                    push 0x00522054
                    ret

                        ChangeOptCloth:
                    cmp al, 0x59
                    jnz PhanGiaiVuKhi
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        mov cl, [eax + edx + 0x128C + 0x8]
                        cmp ecx,0x1
                        jnz JumOut
                        xor ecx,ecx
                        mov cx, [eax + edx + 0x128C + 0x33]
                        test ecx,ecx
                        jz JumOut
                        popad
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
                        jnz KoBangKhong13232
                        mov ecx, [ebp + 0x8]
                        mov cl, [ecx + 0x5]
                        push ecx
                        mov ecx, [ebp - 0x6C]
                        mov eax, 0x004B2960
                        call eax
                        KoBangKhong13232 :
                        mov edx, [ebp + 0x8]
                        xor eax, eax
                        mov al, [edx + 0x4]
                        imul eax, eax, 0x60
                        mov ecx, [ebp - 0x6C]
                        lea edx, [ecx + eax + 0x0000128C]
                        mov[ebp - 0x60], 0xEC
                        mov[ebp - 0x5F], 0x00
                        mov[ebp - 0x5E], 0x7C
                        mov[ebp - 0x5D], 0x04
                        mov[ebp - 0x5C], 0x0A
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
                            mov eax, 0x006FF224
                            call[eax]
                            push eax
                            mov eax, 0x006E4F34
                            call eax
                            add esp, 0x4
                            mov eax, 0x006E4F41
                            call eax
                            cdq
                            mov ecx, 0x64
                            xor edx, edx
                            idiv ecx
                            mov eax,edx
                        cmp eax, 0xA
                        ja AddOptNew2
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        lea ecx, [eax + edx + 0x128C]
                        xor eax,eax
                        mov al,[ecx+0x8]
                        cmp eax,0x1
                        jnz Inclow
                        xor eax,eax
                        mov al,[ecx+0x18]
                        mov word ptr[ecx + 0x33], 0x3
                        mov [ecx + 0x35], ax
                        mov byte ptr[ecx + 0x37], 0x01
                        xor ecx, ecx
                        jmp Inclow
                        AddOptNew2 :
                    cmp eax, 0x1E
                        ja AddOptNew4
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        lea ecx, [eax + edx + 0x128C]
                        xor eax, eax
                        mov al, [ecx + 0x8]
                        cmp eax, 0x1
                        jnz Inclow
                        xor eax, eax
                        mov al, [ecx + 0x18]
                        mov word ptr[ecx + 0x33], 0x8A
                        mov[ecx + 0x35], ax
                        mov byte ptr[ecx + 0x37], 0x01
                        xor ecx, ecx
                        jmp Inclow
                        AddOptNew4 :
                    cmp eax, 0x32
                        ja AddOptNew6
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        lea ecx, [eax + edx + 0x128C]
                        xor eax, eax
                        mov al, [ecx + 0x8]
                        cmp eax, 0x1
                        jnz Inclow
                        xor eax, eax
                        mov al, [ecx + 0x18]
                        mov word ptr[ecx + 0x33], 0xF
                        mov[ecx + 0x35], ax
                        mov byte ptr[ecx + 0x37], 0x01
                        xor ecx, ecx
                        jmp Inclow
                        AddOptNew6 :
                    cmp eax, 0x3C
                        ja AddOptNew7
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        lea ecx, [eax + edx + 0x128C]
                        xor eax, eax
                        mov al, [ecx + 0x8]
                        cmp eax, 0x1
                        jnz Inclow
                        xor eax, eax
                        mov al, [ecx + 0x18]
                        mov word ptr[ecx + 0x33], 0x10
                        mov[ecx + 0x35], ax
                        mov byte ptr[ecx + 0x37], 0x01
                        xor ecx, ecx
                        jmp Inclow
                        AddOptNew7 :
                    cmp eax, 0x4E
                        ja AddOptNew8
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        lea ecx, [eax + edx + 0x128C]
                        xor eax, eax
                        mov al, [ecx + 0x8]
                        cmp eax, 0x1
                        jnz Inclow
                        xor eax, eax
                        mov al, [ecx + 0x18]
                        mov word ptr[ecx + 0x33], 0x2F
                        mov[ecx + 0x35], ax
                        mov byte ptr[ecx + 0x37], 0x01
                        xor ecx, ecx
                        jmp Inclow
                        AddOptNew8 :
                    cmp eax, 0x5B
                        ja AddOptNew91
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        lea ecx, [eax + edx + 0x128C]
                        xor eax, eax
                        mov al, [ecx + 0x8]
                        cmp eax, 0x1
                        jnz Inclow
                        xor eax, eax
                        mov al, [ecx + 0x18]
                        mov word ptr[ecx + 0x33], 0x30
                        mov[ecx + 0x35], ax
                        mov byte ptr[ecx + 0x37], 0x01
                        xor ecx, ecx
                        jmp Inclow

                        AddOptNew91:
                        cmp eax, 0x60
                        ja AddOptNew9
                            mov ecx, [ebp + 0x8]
                            xor edx, edx
                            mov  dl, [ecx + 0x4]
                            imul edx, 0x60
                            mov  eax, [ebp - 0x6C]
                            xor ecx, ecx
                            lea ecx, [eax + edx + 0x128C]
                            xor eax, eax
                            mov al, [ecx + 0x8]
                            cmp eax, 0x1
                            jnz Inclow
                            xor eax, eax
                            mov al, [ecx + 0x18]
                            mov word ptr[ecx + 0x33], 0x86
                            mov[ecx + 0x35], ax
                            mov byte ptr[ecx + 0x37], 0x01
                            xor ecx, ecx
                            jmp Inclow


                        AddOptNew9 :
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        imul edx, 0x60
                        mov  eax, [ebp - 0x6C]
                        xor ecx, ecx
                        lea ecx, [eax + edx + 0x128C]
                        xor eax, eax
                        mov al, [ecx + 0x8]
                        cmp eax, 0x1
                        jnz Inclow
                        xor eax, eax
                        mov al, [ecx + 0x18]
                        imul eax,0x64
                        mov word ptr[ecx + 0x33], 0x17
                        mov[ecx + 0x35], ax
                        mov byte ptr[ecx + 0x37], 0x01
                        xor ecx, ecx
                        Inclow:
                        mov ecx, [ebp + 0x8]
                        xor edx, edx
                        mov  dl, [ecx + 0x4]
                        push edx
                        mov  ecx, [ebp - 0x6C]
                        call SendInforCloth
                        add esp,0x4
                        mov eax, 0x1
                        push 0x00522054
                        ret




#ifdef TestNewFunc
                        PhanGiaiVuKhi:
                        cmp al,0x6D
                        jnz JumOut
                            popad
#ifdef AddLogCp
                            mov  ecx, [ebp - 0x6C]
                            mov eax, [ecx + 0x1054]
                            push eax
                            mov ecx, [ebp + 0x8]
                            xor edx, edx
                            mov  dl, [ecx + 0x4]
                            imul edx, 0x60
                            mov  eax, [ebp - 0x6C]
                            xor ecx, ecx
                            mov cl, [eax + edx + 0x128C + 0xF]
                            push 0x11
                            push ecx
                            xor ecx, ecx
                            mov cx, [eax + edx + 0x128C + 0xA]
                            push ecx
                            xor ecx, ecx
                            mov cl, [eax + edx + 0x128C + 0x8]
                            push ecx
                            mov  ecx, [ebp - 0x6C]
                            call LogUserItemExChange
                            add esp, 0x14
#endif // AddLogCp     
                            mov ecx, [ebp + 0x8]
                            xor edx, edx
                            mov  dl, [ecx + 0x4]
                            imul edx, 0x60
                            mov  eax, [ebp - 0x6C]
                            xor ecx, ecx
                            mov cl, [eax + edx + 0x128C + 0x8]
                            cmp ecx,0x1
                            jnz CheckVuKhiLoai2
                            jmp AcceptPhanGiai
                            CheckVuKhiLoai2:
                            cmp ecx, 0x13
                            jnz NotRequest
                            //Kiem tra ko accept vk tan thu
#ifdef PhanGiaiZplay
                                mov ecx, [ebp + 0x8]
                                xor edx, edx
                                mov  dl, [ecx + 0x4]
                                imul edx, 0x60
                                mov  eax, [ebp - 0x6C]
                                xor ecx, ecx
                                mov cx, [eax + edx + 0x128C + 0xA]
                                cmp ecx, 0x2EF0
                                jb AcceptPhanGiai
                                cmp ecx, 0x2EF9
                                ja AcceptPhanGiai
                                jmp NotRequest
                                AcceptPhanGiai :
                                mov edx, [ebp - 0x50]
                                mov cl, [edx + 0xF]
                                sub cl, 0x1
                                mov[edx + 0xF], cl
                                cmp cl, 0x0
                                jnz KoBangKhong132332
                                mov ecx, [ebp + 0x8]
                                mov cl, [ecx + 0x5]
                                push ecx
                                mov ecx, [ebp - 0x6C]
                                mov eax, 0x004B2960
                                call eax
                                KoBangKhong132332 :
                                mov edx, [ebp + 0x8]
                                xor eax, eax
                                mov al, [edx + 0x4]
                                imul eax, eax, 0x60
                                mov ecx, [ebp - 0x6C]
                                lea edx, [ecx + eax + 0x0000128C]
                                mov[ebp - 0x60], 0xEC
                                mov[ebp - 0x5F], 0x00
                                mov[ebp - 0x5E], 0x7C
                                mov[ebp - 0x5D], 0x04
                                mov[ebp - 0x5C], 0x0A
                                mov al, [edx + 0x18]
                                mov[ebp - 0x5B], al
                                mov edx, [ebp - 0x50]
                                mov cl, [edx + 0xF]
                                mov[ebp - 0x5A], cl
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
                                    mov eax, 0x006FF224
                                    call[eax]
                                push eax
                                mov eax, 0x006E4F34
                                call eax
                                add esp, 0x4

                                //AddItem
                                mov eax, [ebp + 0x8]
                                xor ecx, ecx
                                mov cl, [eax + 0x4]
                                imul ecx, 0x60
                                mov eax, [ebp - 0x6C]
                                xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                cmp edx, 0xB
                                ja TinhHuyetThach
                                mov dx, [eax + 0x128C + ecx + 0xA]
                                cmp edx, 0x2D9D
                                jb LoaiThap
                                xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x3
                                mov eax, 0x4E7
                                jmp addItemPhanGiai
                                LoaiThap :
                            xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x2
                                mov eax, 0x4E7
                                jmp addItemPhanGiai

                                TinhHuyetThach :
                            mov dx, [eax + 0x128C + ecx + 0xA]
                                cmp edx, 0x2D9D
                                jb LoaiThap1
                                xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x3
                                mov eax, 0x4E8
                                jmp addItemPhanGiai
                                LoaiThap1 :
                            xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x2
                                mov eax, 0x4E8
                                addItemPhanGiai :
                                push edx
                                push eax
                                push 0xA
                                push 0x7
                                mov ecx, [ebp - 0x6C]
                                call AddItemLoadChien
                                add esp, 0x10

                                //Remove Item
                                mov eax, [ebp + 0x8]
                                xor ecx, ecx
                                mov cl, [eax + 0x4]
                                push ecx
                                mov ecx, [ebp - 0x6C]
                                call RemoveItem
                                add esp, 0x4

                                mov eax, 0x1
                                push 0x00522054
                                ret
#endif // PhanGiaiZplay
#ifdef PhanGiaiCp
                                mov ecx, [ebp + 0x8]
                                xor edx, edx
                                mov  dl, [ecx + 0x4]
                                imul edx, 0x60
                                mov  eax, [ebp - 0x6C]
                                xor ecx, ecx
                                mov cx, [eax + edx + 0x128C + 0xA]
                                cmp ecx, 0x307C
                                jb AcceptPhanGiai
                                cmp ecx, 0x3085
                                ja AcceptPhanGiai
                                jmp NotRequest
                                AcceptPhanGiai :
                            mov ecx, [ebp - 0x6C]
                                mov eax, 0x50F9E2
                                call eax
                                cmp eax, 0xE4E1C0
                                jb NotRequest
                                mov edx, [ebp - 0x50]
                                mov cl, [edx + 0xF]
                                sub cl, 0x1
                                mov[edx + 0xF], cl
                                cmp cl, 0x0
                                jnz KoBangKhong132332
                                mov ecx, [ebp + 0x8]
                                mov cl, [ecx + 0x5]
                                push ecx
                                mov ecx, [ebp - 0x6C]
                                mov eax, 0x004B2960
                                call eax
                                KoBangKhong132332 :
                            mov edx, [ebp + 0x8]
                                xor eax, eax
                                mov al, [edx + 0x4]
                                imul eax, eax, 0x60
                                mov ecx, [ebp - 0x6C]
                                lea edx, [ecx + eax + 0x0000128C]
                                mov[ebp - 0x60], 0xEC
                                mov[ebp - 0x5F], 0x00
                                mov[ebp - 0x5E], 0x7C
                                mov[ebp - 0x5D], 0x04
                                mov[ebp - 0x5C], 0x0A
                                mov al, [edx + 0x18]
                                mov[ebp - 0x5B], al
                                mov edx, [ebp - 0x50]
                                mov cl, [edx + 0xF]
                                mov[ebp - 0x5A], cl
                                push 0x1
                                mov ecx, [ebp - 0x6C]
                                mov eax, 0x50F9E2
                                call eax
                                sub eax, 0xE4E1C0
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
                                mov eax, 0x006FF224
                                call[eax]
                                push eax
                                mov eax, 0x006E4F34
                                call eax
                                add esp, 0x4

                                //AddItem
                                mov eax, [ebp + 0x8]
                                xor ecx, ecx
                                mov cl, [eax + 0x4]
                                imul ecx, 0x60
                                mov eax, [ebp - 0x6C]
                                xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                cmp edx, 0xB
                                ja TinhHuyetThach
                                mov dx, [eax + 0x128C + ecx + 0xA]
                                cmp edx, 0x2D9D
                                jb LoaiThap
                                xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x3
                                mov eax, 0x4E7
                                jmp addItemPhanGiai
                                LoaiThap :
                            xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x2
                                mov eax, 0x4E7
                                jmp addItemPhanGiai

                                TinhHuyetThach :
                            mov dx, [eax + 0x128C + ecx + 0xA]
                                cmp edx, 0x2D9D
                                jb LoaiThap1
                                xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x3
                                mov eax, 0x4E8
                                jmp addItemPhanGiai
                                LoaiThap1 :
                            xor edx, edx
                                mov dl, [eax + 0x128C + ecx + 0x18]
                                imul edx, 0x2
                                mov eax, 0x4E8
                                addItemPhanGiai :
                                push edx
                                push eax
                                push 0xA
                                push 0x7
                                mov ecx, [ebp - 0x6C]
                                call AddItemLoadChien
                                add esp, 0x10

                                //Remove Item
                                mov eax, [ebp + 0x8]
                                xor ecx, ecx
                                mov cl, [eax + 0x4]
                                push ecx
                                mov ecx, [ebp - 0x6C]
                                call RemoveItem
                                add esp, 0x4

                                mov eax, 0x1
                                push 0x00522054
                                ret
#endif // PhanGiaiCp

#endif // TestNewFunc

    }

}
void __declspec(naked)DeleteOptSetItem()//004CC020
{
    __asm
    {
        mov eax, [ebp - 0x60]
        mov byte ptr[eax + 0xD5B0], 0x0
        mov byte ptr[eax + 0xD5B1], 0x0
        mov word ptr[eax + 0xD5B2], 0x0
        mov word ptr[eax + 0xD5B4], 0x0
        mov word ptr[eax + 0xD5B6], 0x0
        mov dword ptr[eax + 0xD5B8], 0x0
        mov dword ptr[eax + 0xD5BC], 0x0
        mov word ptr[eax + 0xD636], 0x0
        //NewOPt

        mov dword ptr [ebp - 0x4], 0x00000000
        lea  ecx, [ebp - 0x48]
        push ecx
        mov eax, 0x00776388
        mov ecx,[eax]
        push 0x004CC02A
        ret

    }
}
bool AddNewOptionForItem(int type, int AddressSet)
{
    DWORD StoreEcx;
    __asm mov StoreEcx, ecx
    bool returnvalue;
    returnvalue = false;
    DWORD StoreAdressOptItem;
    DWORD AddressOptSet;
    AddressOptSet = AddressSet;
    int typeItem = type;
    
    if (typeItem == 99)
    {
        __asm
        {
            mov ecx, AddressOptSet
            CheckOptSetAgain :
            xor eax, eax
                mov ax, [ecx]
                cmp ax, 0x14
                jnz CheckOptSet2
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD556]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxTDDSet
                mov byte ptr[edx + 0xD556], 0x64
                jmp EndofTDDSet
                ChuaMaxTDDSet :
            mov byte ptr[edx + 0xD556], al
                EndofTDDSet :
            pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 2
                CheckOptSet2 :
            cmp ax, 0x2D2 //Khang Hieu Ung
                jnz CheckOptSet3
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD5A0]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxKhangHUSet
                mov byte ptr[edx + 0xD5A0], 0x64
                jmp EndofKhangSet
                ChuaMaxKhangHUSet :
            mov byte ptr[edx + 0xD5A0], al
                EndofKhangSet :
            pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 3
                CheckOptSet3 :
            cmp ax, 0x2D0 //Phong thu chi  mang
                jnz CheckOptSet4
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD636]
                add eax, ecx
                mov[edx + 0xD636], ax
                pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 4
                CheckOptSet4 :
            cmp ax, 0x41 //giam sat thuong
                jnz CheckOptSet5
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD5A1]
                add eax, ecx
                cmp eax, 0x28
                jb ChuaMaxGiamSatThuongSet
                mov byte ptr[edx + 0xD5A1], 0x28
                jmp EndofGiamgStSet
                ChuaMaxGiamSatThuongSet :
            mov byte ptr[edx + 0xD5A1], al
                EndofGiamgStSet :
            pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 5
                CheckOptSet5 :
            cmp ax, 0x43 //tang st vo cong
                jnz CheckOptSet6
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A2]
                add eax, ecx
                mov[edx + 0xD5A2], ax
                pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 6
                CheckOptSet6 :
            cmp ax, 0xE3 //Deff pvp
                jnz CheckOptSet7
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A4]
                add eax, ecx
                mov[edx + 0xD5A4], ax
                pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 7
                CheckOptSet7 :
            cmp ax, 0x344 //xuyen deff
                jnz CheckOptSet8
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A6]
                add eax, ecx
                mov[edx + 0xD5A6], ax
                pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 8
                CheckOptSet8 :
            cmp ax, 0x29 //phan st
                jnz CheckOptSet9
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A8]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxPhanDonSet
                mov byte ptr[edx + 0xD5A8], 0x64
                jmp OutCheckPhanDonSet
                ChuaMaxPhanDonSet :
            mov byte ptr[edx + 0xD5A8], al
                OutCheckPhanDonSet :
            pop ecx
                jmp EndofOptCheckSet

                // CheckOpt 9
                CheckOptSet9 :
            cmp ax, 0x33E //khang phan dmg
                jnz EndofOptCheckSet
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5AC]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxKhangPhanDonSet
                mov byte ptr[edx + 0xD5AC], 0x64
                jmp OutCheckKhangPhanDonSet
                ChuaMaxKhangPhanDonSet :
            mov byte ptr[edx + 0xD5AC], al
                OutCheckKhangPhanDonSet :
            pop ecx

                EndofOptCheckSet :
            xor eax, eax
                mov eax, [ecx + 0x10]
                test eax, eax
                jz EndCheckOptSetItem
                mov ecx, eax
                jmp CheckOptSetAgain
                EndCheckOptSetItem :
        }
    }
    if (typeItem == 1)
    {
        int tempSlotCloth = 0;
        __asm
        {
            mov eax, StoreEcx
            mov byte ptr[eax + 0xD580], 0x0
            mov byte ptr[eax + 0xD581], 0x0
            mov word ptr[eax + 0xD582], 0x0
            mov word ptr[eax + 0xD584], 0x0
            mov word ptr[eax + 0xD586], 0x0
            mov dword ptr[eax + 0xD588], 0x0
            mov dword ptr[eax + 0xD58C], 0x0
            mov byte ptr [eax + 0xD590], 0x0
            mov word ptr[eax + 0xD638], 0x0
            mov word ptr[eax + 0xD63C], 0x0
            mov tempSlotCloth, 0x0
            LoopBackCheckCloth:
            mov ecx, tempSlotCloth
                imul ecx, 0x60
                mov eax, StoreEcx
                xor edx, edx
                mov dx, [eax + 0x128C + ecx + 0xA]
                test edx, edx
                jz EndOfItemCloth
                push edx
                mov ecx, 0x00776388
                mov ecx, [ecx]
                mov eax, 0x004D8230
                call eax
                mov ecx, [eax + 0x63]
                test ecx, ecx
                jz EndOfItemCloth
                CheckAgainOptCloth :
            xor eax, eax
                mov ax, [ecx]
                cmp ax, 0x2D2 //Khang Hieu Ung
                jnz CheckTypeOptCloth3
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD580]
                add eax, ecx
                cmp eax, 0x64
                jb NextSlotCloth54126Cloth
                mov byte ptr[edx + 0xD580], 0x64
                jmp EndCheck2oot2Cloth
                NextSlotCloth54126Cloth :
            mov byte ptr[edx + 0xD580], al
                EndCheck2oot2Cloth :
            pop ecx
                jmp NextSlotCloth

                // CheckOpt 4
                CheckTypeOptCloth3 :
            cmp ax, 0x41 //giam sat thuong
                jnz CheckTypeOptCloth5
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD581]
                add eax, ecx
                cmp eax, 0x28
                jb ChuaMaxOptGiamSTCloth
                mov byte ptr[edx + 0xD581], 0x28
                jmp NhayRaKhoiAddOptGiamSTCloth
                ChuaMaxOptGiamSTCloth :
            mov byte ptr[edx + 0xD581], al
                NhayRaKhoiAddOptGiamSTCloth :
            pop ecx
                jmp NextSlotCloth

                // CheckOpt 5
                CheckTypeOptCloth5 :
            cmp ax, 0x43 //tang st vo cong
                jnz CheckTypeOptCloth6
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD582]
                add eax, ecx
                mov[edx + 0xD582], ax
                pop ecx
                jmp NextSlotCloth

                // CheckOpt 6
                CheckTypeOptCloth6 :
            cmp ax, 0xE3 //Deff pvp
                jnz CheckTypeOptCloth7
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD584]
                add eax, ecx
                mov[edx + 0xD584], ax
                pop ecx
                jmp NextSlotCloth

                // CheckOpt 7
                CheckTypeOptCloth7 :
            cmp ax, 0x344 //xuyen deff
                jnz CheckTypeOptCloth8
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD586]
                add eax, ecx
                mov[edx + 0xD586], ax
                pop ecx
                jmp NextSlotCloth

                // CheckOpt 8
                CheckTypeOptCloth8 :
            cmp ax, 0x29 //phan st
                jnz CheckTypeOptCloth8PNSTCM
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD588]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxPhanDonCloth
                mov byte ptr[edx + 0xD588], 0x64
                jmp OutCheckPhanDonCloth
                ChuaMaxPhanDonCloth :
            mov byte ptr[edx + 0xD588], al
                OutCheckPhanDonCloth :
            pop ecx
                jmp NextSlotCloth

                // CheckOpt 81
                CheckTypeOptCloth8PNSTCM :
            cmp ax, 0x2D2 //phan st
                jnz CheckTypeOptCloth9
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD638]
                add eax, ecx
                mov[edx + 0xD638], ax
                pop ecx
                jmp NextSlotCloth

                // CheckOpt 9
                CheckTypeOptCloth9 :
            cmp ax, 0x33E //khang phan dmg
                jnz NextSlotCloth
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD58C]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxKhangPhanDonCloth
                mov byte ptr[edx + 0xD58C], 0x64
                jmp OutCheckKhangPhanDonCloth
                ChuaMaxKhangPhanDonCloth :
            mov byte ptr[edx + 0xD58C], al
                OutCheckKhangPhanDonCloth :
            pop ecx

                NextSlotCloth:
            xor eax, eax
                mov eax, [ecx + 0x10]
                test eax, eax
                jz EndOfItemCloth
                mov ecx, eax
                jmp CheckAgainOptCloth

                EndOfItemCloth :
            mov ecx, tempSlotCloth
                add ecx, 0x1
                mov tempSlotCloth, ecx
                cmp ecx, 0x4
                jbe LoopBackCheckCloth

                //Check Decco
                mov ecx, 0x7
                imul ecx, 0x60
                mov eax, StoreEcx
                xor edx, edx
                mov dx, [eax + 0x128C + ecx + 0xA]
                test edx, edx
                jz EndOfItemDecco
                push edx
                mov ecx, 0x00776388
                mov ecx, [ecx]
                mov eax, 0x004D8230
                call eax
                mov ecx, [eax + 0x63]
                test ecx, ecx
                jz EndOfItemDecco
                CheckAgainOptDecco :
            xor eax, eax
                mov ax, [ecx]
                cmp ax, 0x2D2 //Khang Hieu Ung
                jnz CheckTypeOptDecco3
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD580]
                add eax, ecx
                cmp eax, 0x64
                jb NextSlotDecco54126Decco
                mov byte ptr[edx + 0xD580], 0x64
                jmp EndCheck2oot2Decco
                NextSlotDecco54126Decco :
            mov byte ptr[edx + 0xD580], al
                EndCheck2oot2Decco :
            pop ecx
                jmp NextSlotDecco

                // CheckOpt 4
                CheckTypeOptDecco3 :
            cmp ax, 0x41 //giam sat thuong
                jnz CheckTypeOptTDDDecco3
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD581]
                add eax, ecx
                cmp eax, 0x28
                jb ChuaMaxOptGiamSTDecco
                mov byte ptr[edx + 0xD581], 0x28
                jmp NhayRaKhoiAddOptGiamSTDecco
                ChuaMaxOptGiamSTDecco :
            mov byte ptr[edx + 0xD581], al
                NhayRaKhoiAddOptGiamSTDecco :
            pop ecx
                jmp NextSlotDecco

                CheckTypeOptTDDDecco3 :
            cmp ax, 0x14 //giam sat thuong
                jnz CheckTypeOptDecco5
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD590]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxOptTDDDecco
                mov byte ptr[edx + 0xD590], 0x28
                jmp NhayRaKhoiAddOptTDDDecco
                ChuaMaxOptTDDDecco :
            mov byte ptr[edx + 0xD590], al
                NhayRaKhoiAddOptTDDDecco :
            pop ecx
                jmp NextSlotDecco

                // CheckOpt 5
                CheckTypeOptDecco5 :
            cmp ax, 0x43 //tang st vo cong
                jnz CheckTypeOptDecco6
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD582]
                add eax, ecx
                mov[edx + 0xD582], ax
                pop ecx
                jmp NextSlotDecco

                // CheckOpt 6
                CheckTypeOptDecco6 :
            cmp ax, 0xE3 //Deff pvp
                jnz CheckTypeOptDecco7
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD584]
                add eax, ecx
                mov[edx + 0xD584], ax
                pop ecx
                jmp NextSlotDecco

                // CheckOpt 7
                CheckTypeOptDecco7 :
            cmp ax, 0x344 //xuyen deff
                jnz CheckTypeOptCloth8PNSTCMDeco
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD586]
                add eax, ecx
                mov[edx + 0xD586], ax
                pop ecx
                jmp NextSlotDecco


                CheckTypeOptCloth8PNSTCMDeco :
            cmp ax, 0x2D0 //phan st
                jnz CheckTypeOptDecco8
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD63C]
                add eax, ecx
                mov[edx + 0xD63C], ax
                pop ecx
                jmp NextSlotDecco


                // CheckOpt 8
                CheckTypeOptDecco8 :
            cmp ax, 0x29 //phan st
                jnz CheckTypeOptDecco9
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD588]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxPhanDonDecco
                mov byte ptr[edx + 0xD588], 0x64
                jmp OutCheckPhanDonDecco
                ChuaMaxPhanDonDecco :
            mov byte ptr[edx + 0xD588], al
                OutCheckPhanDonDecco :
            pop ecx
                jmp NextSlotDecco

                // CheckOpt 9
                CheckTypeOptDecco9 :
            cmp ax, 0x33E //khang phan dmg
                jnz NextSlotDecco
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD58C]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxKhangPhanDonDecco
                mov byte ptr[edx + 0xD58C], 0x64
                jmp OutCheckKhangPhanDonDecco
                ChuaMaxKhangPhanDonDecco :
            mov byte ptr[edx + 0xD58C], al
                OutCheckKhangPhanDonDecco :
            pop ecx

                NextSlotDecco :
            xor eax, eax
                mov eax, [ecx + 0x10]
                test eax, eax
                jz EndOfItemDecco
                mov ecx, eax
                jmp CheckAgainOptDecco

                EndOfItemDecco :
        }
    }
    else if (typeItem == 9)
    {
        int tempSlot = 0;
        __asm
        {
            mov eax, StoreEcx
            mov byte ptr[eax + 0xD5A0], 0x0
            mov byte ptr[eax + 0xD5A1], 0x0
            mov word ptr[eax + 0xD5A2], 0x0
            mov word ptr[eax + 0xD5A4], 0x0
            mov word ptr[eax + 0xD5A6], 0x0
            mov dword ptr[eax + 0xD5A8], 0x0
            mov dword ptr[eax + 0xD5AC], 0x0
            mov byte ptr[eax + 0xD556], 0x0
            mov word ptr[eax + 0xD63A], 0x0
            mov byte ptr[eax + 0xCAA4], 0x0
            mov tempSlot, 0xC
            LoopBackCheckOldSlot:
            mov ecx, tempSlot
                imul ecx, 0x60
                mov eax, StoreEcx
                xor edx, edx
                mov dx, [eax + 0x128C + ecx + 0xA]
                test edx, edx
                jz EndOfItem
                push edx
                mov ecx, 0x00776388
                mov ecx, [ecx]
                mov eax, 0x004D82A0
                call eax
                mov ecx, [eax + 0x44]
                test ecx, ecx
                jz EndOfItem
                CheckAgainOpt :
                xor eax, eax
                mov ax, [ecx]
                cmp ax, 0x14
                jnz CheckTypeOpt2
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD556]
                add eax, ecx
                cmp eax, 0x64
                jb NextSlot3212
                mov byte ptr[edx + 0xD556], 0x64
                jmp EndCheck2oot2221
                NextSlot3212 :
                mov byte ptr[edx + 0xD556], al
                EndCheck2oot2221 :
                pop ecx
                jmp NextSlot

                // CheckOpt 2
                CheckTypeOpt2 :
                cmp ax, 0x2D2 //Khang Hieu Ung
                jnz CheckTypeOpt3
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD5A0]
                add eax, ecx
                cmp eax, 0x64
                jb NextSlot54126
                mov byte ptr[edx + 0xD5A0], 0x64
                jmp EndCheck2oot2
                NextSlot54126 :
                mov byte ptr[edx + 0xD5A0], al
                EndCheck2oot2 :
                pop ecx
                jmp NextSlot

                // CheckOpt 3
                CheckTypeOpt3 :
                cmp ax, 0x2D0 //Phong thu chi  mang
                jnz NextNewOpt
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD63A]
                add eax, ecx
                mov[edx + 0xD63A], ax
                pop ecx
                jmp NextSlot

                // CheckOpt 4
                NextNewOpt :
                cmp ax, 0x41 //giam sat thuong
                jnz NextNewOpt2
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD5A1]
                add eax, ecx
                cmp eax, 0x28
                jb ChuaMaxOptGiamST
                mov byte ptr[edx + 0xD5A1], 0x28
                jmp NhayRaKhoiAddOptGiamST
                ChuaMaxOptGiamST :
                mov byte ptr[edx + 0xD5A1], al
                NhayRaKhoiAddOptGiamST :
                pop ecx
                jmp NextSlot

                // CheckOpt 5
                NextNewOpt2 :
                cmp ax, 0x43 //tang st vo cong
                jnz DeffPVp
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A2]
                add eax, ecx
                mov[edx + 0xD5A2], ax
                pop ecx
                jmp NextSlot

                // CheckOpt 6
                DeffPVp :
                cmp ax, 0xE3 //Deff pvp
                jnz KhangDeffPvp
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A4]
                add eax, ecx
                mov[edx + 0xD5A4], ax
                pop ecx
                jmp NextSlot

                // CheckOpt 7
                KhangDeffPvp :
                cmp ax, 0x344 //xuyen deff
                jnz PhanDam
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A6]
                add eax, ecx
                mov[edx + 0xD5A6], ax
                pop ecx
                jmp NextSlot

                // CheckOpt 8
                PhanDam :
                cmp ax, 0x29 //phan st
                jnz KhangPhanDam
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A8]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxPhanDon
                mov byte ptr[edx + 0xD5A8], 0x64
                jmp OutCheckPhanDon
                ChuaMaxPhanDon :
                mov byte ptr[edx + 0xD5A8], al
                OutCheckPhanDon :
                pop ecx
                jmp NextSlot

                // CheckOpt 9
                KhangPhanDam :
                cmp ax, 0x33E //khang phan dmg
                jnz NextSlot
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5AC]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxKhangPhanDon
                mov byte ptr[edx + 0xD5AC], 0x64
                jmp OutCheckKhangPhanDon
                ChuaMaxKhangPhanDon :
                mov byte ptr[edx + 0xD5AC], al
                OutCheckKhangPhanDon :
                pop ecx

                NextSlot :
                xor eax, eax
                mov eax, [ecx + 0x10]
                test eax, eax
                jz EndOfItem
                mov ecx, eax
                jmp CheckAgainOpt

                EndOfItem :
            mov ecx, tempSlot
                add ecx, 0x1
                mov tempSlot, ecx
                cmp ecx, 0x13
                jbe LoopBackCheckOldSlot
                //New Slot
                mov tempSlot, 0x8C
                mov ecx, tempSlot
                BackLoopCheckItemNs :
            imul ecx, 0x60
                mov eax, StoreEcx
                xor edx, edx
                mov dx, [eax + 0x128C + ecx + 0xA]
                test edx, edx
                jz EndOfItem2
                push edx
                mov ecx, 0x00776388
                mov ecx, [ecx]
                mov eax, 0x004D82A0
                call eax
                mov ecx, [eax + 0x44]
                test ecx, ecx
                jz EndOfItem2
                CheckAgainOpt2 :
            xor eax, eax
                mov ax, [ecx]
                cmp ax, 0x14
                jnz CheckTypeOpt22
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD556]
                add eax, ecx
                cmp eax, 0x64
                jb NextSlotNs213
                mov byte ptr[edx + 0xD556], 0x64
                jmp EndCheck2oot22234
                NextSlotNs213 :
            mov[edx + 0xD556], al
                EndCheck2oot22234 :
            pop ecx
                jmp NextSlotNs
                CheckTypeOpt22 :
            cmp ax, 0x2D2
                jnz CheckTypeOpt223
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD5A0]
                add eax, ecx
                cmp eax, 0x64
                jb NextSlotNs4422
                mov byte ptr[edx + 0xD5A0], 0x64
                jmp EndChec22k2oot22234
                NextSlotNs4422 :
            mov[edx + 0xD5A0], al
                EndChec22k2oot22234 :
            pop ecx
                jmp NextSlotNs
                CheckTypeOpt223 :
            cmp ax, 0x2D0
                jnz ChecOptTruSt
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD63A]
                add eax, ecx
                mov[edx + 0xD63A], ax
                pop ecx
                jmp NextSlotNs

                ChecOptTruSt :
            cmp ax, 0x41
                jnz CheckOptStvoCong
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cl, [edx + 0xD5A1]
                add eax, ecx
                cmp eax, 0x28
                jb ChuaMaxOptGiamSTNewSlot
                mov byte ptr[edx + 0xD5A1], 0x28
                jmp NhayRaKhoiAddOptGiamSTNewSlot
                ChuaMaxOptGiamSTNewSlot :
            mov byte ptr[edx + 0xD5A1], al
                NhayRaKhoiAddOptGiamSTNewSlot :
            pop ecx
                jmp NextSlotNs

                CheckOptStvoCong :
            cmp ax, 0x43
                jnz DeffPVp2
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A2]
                add eax, ecx
                mov[edx + 0xD5A2], ax
                pop ecx
                jmp NextSlotNs

                DeffPVp2 :
            cmp ax, 0xE3 //Deff pvp
                jnz KhangDeffPvp2
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A4]
                add eax, ecx
                mov[edx + 0xD5A4], ax
                pop ecx
                jmp NextSlotNs

                KhangDeffPvp2 :
            cmp ax, 0x344 //xuyen deff
                jnz PhanDam2
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A6]
                add eax, ecx
                mov[edx + 0xD5A6], ax
                pop ecx
                jmp NextSlotNs

                PhanDam2 :
            cmp ax, 0x29 //phan st
                jnz KhangPhanDam2
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5A8]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxPhanDon2
                mov byte ptr[edx + 0xD5A8], 0x64
                jmp OutCheckPhanDon2
                ChuaMaxPhanDon2 :
            mov byte ptr[edx + 0xD5A8], al
                OutCheckPhanDon2 :
            pop ecx
                jmp NextSlotNs

                KhangPhanDam2 :
            cmp ax, 0x33E //khang phan dmg
                jnz NextSlotNs
                push ecx
                xor eax, eax
                mov ax, [ecx + 0x4]
                mov edx, StoreEcx
                xor ecx, ecx
                mov cx, [edx + 0xD5AC]
                add eax, ecx
                cmp eax, 0x64
                jb ChuaMaxKhangPhanDon2
                mov byte ptr[edx + 0xD5AC], 0x64
                jmp OutCheckKhangPhanDon2
                ChuaMaxKhangPhanDon2 :
            mov byte ptr[edx + 0xD5AC], al
                OutCheckKhangPhanDon2 :

        NextSlotNs:
            xor eax, eax
                mov eax, [ecx + 0x10]
                test eax, eax
                jz EndOfItem2
                mov ecx, eax
                jmp CheckAgainOpt2
                EndOfItem2 :
            mov ecx, tempSlot
                add ecx, 0x1
                mov tempSlot, ecx
                cmp ecx, 0x93
                jbe BackLoopCheckItemNs
                mov returnvalue, 0x1
                jmp EndOptFuncCheck
        }
    }
EndOptFuncCheck:
    //Count All Value
    __asm
    {
        //Opt Khang Hieu Ung
        mov eax, StoreEcx
        xor edx, edx
        mov dl, [eax + 0xD555]
        xor ecx, ecx
        mov cl, [eax + 0xD556]
        add edx, ecx
        xor ecx, ecx
        mov cl, [eax + 0xD590]
        add edx, ecx
        cmp edx, 0x64
        ja MaxOptTDD
        mov byte ptr[eax + 0xCAA4], dl
        jmp EndofTDD
        MaxOptTDD :
        mov byte ptr[eax + 0xCAA4], 0x64
            EndofTDD :
        //Phong ngu sat thuong cm
            mov eax, StoreEcx
            xor edx, edx
            mov dx, [eax + 0xD636]
            xor ecx, ecx
            mov cx, [eax + 0xD638]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD63A]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD63C]
            add edx, ecx
            mov[eax + 0xCAA6], dx
        ///
        //Opt Khang Hieu Ung
        mov eax, StoreEcx
        xor edx, edx
        mov dl, [eax + 0xD580]
        xor ecx, ecx
        //mov cl, [eax + 0xD590]
        //add edx, ecx
        //xor ecx, ecx
        mov cl, [eax + 0xD5A0]
        add edx, ecx
        xor ecx, ecx
        mov cl, [eax + 0xD5B0]
        add edx, ecx
        xor ecx, ecx
        mov cl, [eax + 0xD5C0]
        add edx, ecx
        cmp edx, 0x64
        ja MaxOptKhangHieuUng
        mov byte ptr[eax + 0xCAA5], dl
        jmp EndofKhangHieuUng
        MaxOptKhangHieuUng :
        mov byte ptr[eax + 0xCAA5], 0x64
            EndofKhangHieuUng :
            //Opt Giam Sat Thuong
            mov eax, StoreEcx
            xor edx, edx
            mov dl, [eax + 0xD581]
            xor ecx, ecx
            mov cl, [eax + 0xD591]
            add edx, ecx
            xor ecx, ecx
            mov cl, [eax + 0xD5A1]
            add edx, ecx
            xor ecx, ecx
            mov cl, [eax + 0xD5B1]
            add edx, ecx
            xor ecx, ecx
            mov cl, [eax + 0xD5C1]
            add edx, ecx
            cmp edx, 0x32
            ja MaxOptGiamSatThuong
            mov byte ptr[eax + 0xD561], dl
            jmp EndofGiamSatThuong
            MaxOptGiamSatThuong :
        mov byte ptr[eax + 0xD561], 0x32
            EndofGiamSatThuong :
            //Opt St Vo Cong
            mov eax, StoreEcx
            xor edx, edx
            mov dx, [eax + 0xD582]
            xor ecx, ecx
            mov cx, [eax + 0xD592]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5A2]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5B2]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5C2]
            add edx, ecx
            mov [eax + 0xD562], dx
            //Opt Deff Pvp
            mov eax, StoreEcx
            xor edx, edx
            mov dx, [eax + 0xD584]
            xor ecx, ecx
            mov cx, [eax + 0xD594]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5A4]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5B4]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5C4]
            add edx, ecx
            mov [eax + 0xD570], dx
            //Opt Xuyen Deff Pvp
            mov eax, StoreEcx
            xor edx, edx
            mov dx, [eax + 0xD586]
            xor ecx, ecx
            mov cx, [eax + 0xD596]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5A6]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5B6]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5C6]
            add edx, ecx
            mov [eax + 0xD572], dx
            //Opt Phan Dmg
            mov eax, StoreEcx
            xor edx, edx
            mov edx, [eax + 0xD588]
            xor ecx, ecx
            mov ecx, [eax + 0xD598]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5A8]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5B8]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5C8]
            add edx, ecx
            cmp edx, 0x64
            ja MaxOptPhanDamge
            mov[eax + 0xD574], edx
            jmp EndofPhanDmg
            MaxOptPhanDamge :
        mov[eax + 0xD574], 0x64
            EndofPhanDmg :
            //Opt Khang Phan Dmg
            mov eax, StoreEcx
            xor edx, edx
            mov edx, [eax + 0xD58C]
            xor ecx, ecx
            mov ecx, [eax + 0xD59C]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5AC]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5BC]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5CC]
            add edx, ecx
            cmp edx, 0x64
            ja MaxOptKhangPhanDamge
            mov[eax + 0xD578], edx
            jmp EndofKhangPhanDmg
            MaxOptKhangPhanDamge :
        mov[eax + 0xD578], 0x64
            EndofKhangPhanDmg :
    }
    return returnvalue;
}
void __declspec(naked)AddOptFromSetItem()//004CC02F
{
    __asm
    {
        lea edx, [ebp - 0x48]
        xor ecx,ecx
        BackLoopCheckSet:
        mov eax,[edx + ecx*0x4+0x24]
        test eax,eax
        jz ByPassSetItem
        push ecx
        push eax
        push 0x63
        mov ecx, [ebp - 0x60]
        call AddNewOptionForItem
        add esp,0x8
        pop ecx
        ByPassSetItem:
        add ecx,0x1
        lea edx, [ebp - 0x48]
        cmp ecx,0x8
        ja Default
        jmp BackLoopCheckSet
        Default :
        mov dword ptr[ebp - 0x4C], 0x0
        push 0x004CC036
        ret

    }
}
void __declspec(naked)ByPassCheckRunNext1()//0059D718
{
    __asm
    {
        pushad
        mov ecx, [ebp - 0x1C]
        mov ecx, [ecx + 0xCAA0]
        mov eax, [ebp - 0x000000A8]
        cmp eax, ecx
        jz JmpBypass
        popad
        lea     ecx, [ebp - 0x9C]
        push 0x0059D71E
        ret

        JmpBypass :
            mov edx,[ebp-0x9C]
            push edx
            mov edx,[ebp-0xA8]
            push edx
            mov dword ptr[ebp-0xA8], 0x3f000000
            mov ecx, [ebp - 0x1C]
            mov edx, [ecx + 0x5BC8 + 0x8]
            
            mov [ebp-0x9C],edx
            fld dword ptr[ebp-0x9C]
            fadd dword ptr[ebp-0xA8]
            push ecx
            fstp dword ptr[esp]
            pop edx
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
            pop edx
            mov [ebp-0xA8],edx
            pop edx
            mov [ebp-0x9C],edx
            popad
            push 0x0059D730
            ret

      
    }
}
void __declspec(naked)ByPassCheckRunNext1Test()//0059D924
{
    __asm
    {
        pushad
        mov ecx, [ebp - 0x1C]
        mov ecx, [ecx + 0xCAA0]
        mov eax, [ebp - 0x000000A8]
        cmp eax, ecx
        jz JmpBypass
        DefaultLoadPet:
        popad
        mov     ecx, [ebp - 0xA8]
        mov eax,0x0059BCC0
        call eax
        push 0x0059D92F
        ret

        JmpBypass :
            mov edx, [ebp - 0x9C]
            push edx
            mov edx, [ebp - 0xA8]
            push edx
            mov dword ptr[ebp - 0xA8], 0x3f000000
            mov ecx, [ebp - 0x1C]
            mov edx, [ecx + 0x5BC8]

            mov[ebp - 0x9C], edx
            fld dword ptr[ebp - 0x9C]
            fsub dword ptr[ebp - 0xA8]
            push ecx
            fstp dword ptr[esp]
            pop edx
            pop ecx
            mov [ebp- 0x000000A8],ecx
            mov ecx, [ebp - 0x000000A8]
            add ecx, 0x1C8
            mov[ecx + 0x4], edx
            //2
            mov ecx, [ebp - 0x1C]
            mov edx, [ecx + 0x5BC8 +0x4]
            mov ecx, [ebp - 0x000000A8]
            add ecx, 0x1C8
            mov[ecx + 0x8], edx
            pop edx
            mov[ebp - 0x9C], edx
            jmp DefaultLoadPet

            

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
        mov edx, [eax + 0xCAA0]
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
        mov ecx, [ecx + 0xCAA0]
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
        mov ecx, [ecx + 0xCAA0]
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
        mov eax, [eax + 0xCAA0]
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
int SLPheTong = 0;
int SLPheKim = 0;
bool KiemTraPhe(int Type)
{
    bool resultCheck;
    resultCheck = false;
    if (Type == 1)//Tong
    {
        if (SLPheKim >= SLPheTong)
        {
            resultCheck = true;
        }
    }
    if (Type == 2)//Kim
    {
        if (SLPheTong >= SLPheKim)
        {
            resultCheck = true;
        }
    }
    return resultCheck;
}
struct GhiDanhTongKim {
    u_short usLength;
    u_char cMessage;
    u_char unknow;
    u_char ThongBao;
    DWORD StoreAddress;
};
void SendInforTongKimGhiDanh(int Type)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int loai;
    loai = Type;
    GhiDanhTongKim pkUserTK;
    __asm
    {
        lea eax, pkUserTK
        mov byte ptr[eax], 0x9
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x3B
        mov byte ptr[eax + 0x3], 0x24
        lea ecx, loai
        xor edx,edx
        mov dl,[ecx]
        mov [eax + 0x4], dl
        lea eax, pkUserTK
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, pkUserTK
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
}

void LogUserItem(int typeID, int IDitem,int count, int MapID,int uniqueID)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    char NameUser[13];
    char fname[128];
    sprintf(fname, "C:/9Dragons/LogUserItem/%d_%dmap.txt", uniqueID, MapID);
    InforUserTK* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    int iLine = 0;
    time_t now = time(0);
    char* dt = ctime(&now);
    char line[256];
    __asm
    {
        mov ecx, StoreECX
        call get_name1
        push 0xD
        push eax
        lea eax, NameUser
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
    }
    string filname;
    FILE* fp = fopen(fname, "a");
    if (fp)
    {
        fprintf(fp, " %s %u %u %u %s %u",
            NameUser, typeID, IDitem,count, dt, MapID
        );
        returninfo = true;
        fclose(fp);
    }
    else
    {
        std::cout << "Error Create File and Write" << NameUser  << typeID << IDitem << std::endl;
    }

};
struct ThongTinQuyetCoKey
{
    u_short usLength;
    u_char cMessage;
    u_char unknow;
    u_char SlotItem;
    u_char ncCount;
    u_char bInfor;
};
void SendInfoDiQMoi(int SlotNeed,int nCountItem,int infoBack) {
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    ThongTinQuyetCoKey pkTTQuyet;
    __asm
    {
        lea eax, pkTTQuyet
        mov word ptr[eax], 0x07
        mov byte ptr[eax + 0x2], 0x79
        mov byte ptr[eax + 0x3], 0x17
        xor ecx, ecx
        mov ecx, SlotNeed
        mov byte ptr[eax + 0x4], cl
        xor ecx, ecx
        mov ecx, nCountItem
        mov byte ptr[eax + 0x5], cl
        xor ecx, ecx
        mov ecx, infoBack
        mov byte ptr[eax + 0x6], cl
        lea eax, pkTTQuyet
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, pkTTQuyet
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }  
}
bool SaveLogUsedItem(int typeItem, int idItem, int countItem, unsigned int uniqueID_User)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char fname[200];
    SYSTEMTIME checktime;
    GetLocalTime(&checktime);
    sprintf(fname, "C:/9Dragons/DBUserInfo/LogUser/log_%d_%d_%d_%d.txt", checktime.wYear, checktime.wMonth, checktime.wDay, uniqueID_User);
    int iLine = 0;
    char line[256];
    bool returninfo;
    returninfo = false;
    string filname;
    FILE* fp = fopen(fname, "a");
    if (fp)
    {
        fprintf(fp, "%u-%u-%u %u:%u, ItemType: %u ,ItemID: %u ,CountCur: %u \n",
            checktime.wDay, checktime.wMonth, checktime.wYear, checktime.wHour, checktime.wMinute, typeItem, idItem, countItem);
        fclose(fp);
        return true;
    }
    else
    {
        std::cout << "Error Save Log Use Item " << uniqueID_User << std::endl;
        return false;
    }
    return false;
}
int ListItemProcessFunc[100][4];
void LoadInforItemFunc()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char fname[200];
    sprintf(fname, "nfofile/inforfunc.txt");
    int iLine = 0;
    char line[256];
    bool returninfo;
    returninfo = false;
    string filname;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        std::cout << "Error Load" << std::endl;
    }
    while (1)
    {

        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        sscanf(line, "%d %d %d %d",
            &ListItemProcessFunc[iLine][0], &ListItemProcessFunc[iLine][1], &ListItemProcessFunc[iLine][2], &ListItemProcessFunc[iLine][3]);
        ++iLine;
    }
    fclose(fp);
}
int ListDieuCheKhongTacDungSach[200];
void LoadInforDieuCheKhongCoTDSachFunc()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char fname[200];
    sprintf(fname, "nfofile/khongcotacdungsach.txt");
    int iLine = 0;
    char line[256];
    bool returninfo;
    returninfo = false;
    string filname;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        std::cout << "Error Load khongcotacdungsach" << std::endl;
    }
    while (1)
    {

        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        sscanf(line, "%d", &ListDieuCheKhongTacDungSach[iLine]);
        ++iLine;
    }
    fclose(fp);
};

int ListDieuCheChoPhepSuDungBua[200];
void LoadInforDieuCheCoTDBuaFunc()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char fname[200];
    sprintf(fname, "nfofile/giuvatpham.txt");
    int iLine = 0;
    char line[256];
    bool returninfo;
    returninfo = false;
    string filname;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        std::cout << "Error Load giuvatpham" << std::endl;
    }
    while (1)
    {

        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        sscanf(line, "%d", &ListDieuCheChoPhepSuDungBua[iLine]);
        ++iLine;
    }
    fclose(fp);
};
/*int ListItemProcessFunc[20][4] =
{
    {3,3880,1,0},
    {3,3435,5,200},
    {3,3436,5,240},
    {3,3810,2,1},
    {3,3811,2,2},
    {3,3812,2,3},
    {3,3813,2,4},
    {3,3814,2,5},
    {3,3815,2,6},
    {3,3806,3,1},
    {3,3807,3,2},
    {3,3808,3,3},
    {3,3809,3,4},
    {10,76,6,1000},
    {10,96,6,2000},
    {10,100,6,500},
    {10,101,6,200},
    {7,2299,4,2299},
    {7,3020,7,1},
    {7,3019,7,2},
};*/

int listModAoHinhLon[7] = { 6648,6649,6650,6651,6652,6653,6654 };
int listModAoHinhThanBi[5] = { 6656,6657,6658,6659,6660 };
int listModAoHinhDiaNguc[5] = { 6662,6663,6664,6665,6666 };
int listModAoHinhThanThoai[5] = { 6668,6669,6670,6671,6672 };
struct _point
{
    float m_posX;
    float m_posZ;

    _point() : m_posX(0.0f), m_posZ(0.0f) {}
    _point(float x, float z) : m_posX(x), m_posZ(z) {}
    inline void operator=(const _point& p) { m_posX = p.m_posX; m_posZ = p.m_posZ; }
};
void SpawnMod(int idMod)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int RankMod;
    _point localUser;
    int idModRandom;
    int idModSpaw;
    if (idMod != 0)
    {
        __asm
        {
            mov  ecx, StoreECX
            mov eax, 0x00431F70
            call eax
            fstp localUser.m_posX
            mov  ecx, StoreECX
            mov eax, 0x00431F90
            call eax
            fstp localUser.m_posZ
            // Spawn Mod
            push 0x0
            push 0x0
            push 0x0
            lea edx, localUser
            push edx
            push 0x0
            push idMod
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
        }
    }
    else
    {

        srand(timeGetTime());
        int ramdnumber = rand() % 100;
        if (ramdnumber <= 60)
        {
            RankMod = 1;
        }
        else if (ramdnumber <= 75)
        {
            RankMod = 2;
        }
        else if (ramdnumber <= 90)
        {
            RankMod = 3;
        }
        else if (ramdnumber <= 100)
        {
            RankMod = 4;
        }
        int numbercountmod;
        switch (RankMod)
        {
        case 1:
            idModRandom = rand() % 7;
            idModSpaw = listModAoHinhLon[idModRandom];
            break;
        case 2:
            idModRandom = rand() % 5;
            idModSpaw = listModAoHinhThanBi[idModRandom];
            break;
        case 3:
            idModRandom = rand() % 5;
            idModSpaw = listModAoHinhDiaNguc[idModRandom];
            break;
        case 4:
            idModRandom = rand() % 5;
            idModSpaw = listModAoHinhThanThoai[idModRandom];
            break;
        default:
            break;
        }

        _asm
        {
            mov  ecx, StoreECX
            mov eax, 0x00431F70
            call eax
            fstp localUser.m_posX
            mov  ecx, StoreECX
            mov eax, 0x00431F90
            call eax
            fstp localUser.m_posZ
            // Spawn Mod
            push 0x0
            push 0x0
            push 0x0
            lea edx, localUser
            push edx
            push 0x0
            push idModSpaw
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
        }
        //Spawn Random Mod
    }

}
struct MSG_USE_ITEM_RESULT_ANOTHER_FUNC
{
    _sHeader			header;
    u_char				ucMessage;
    char				cResult;				// ¼º°ø or ½ÇÆÐ & ½ÇÆÐ ÀÌÀ¯. // 2004.06.09->oneway48 insert
    char                cAnotherCase;
    u_char				ucInvenIndex;			// ¼Ò¸ðÇÑ ¾ÆÀÌÅÛÀÇ ÀÎº¥¹øÈ£ 
    u_char				ucCount;				// ÇöÀç ³²¾ÆÀÖ´Â °³¼ö 0°³¸é ÇØ´ç ÀÎº¥Åä¸® ½½·ÔÀ» »èÁ¦ 
    unsigned int        moneyCur;
};
struct MSG_REWARD_FROM_BOX
{
    _sHeader			header;
    u_char				ucMessage;
    char				cResult;
    char                cAnotherCase;
    u_char				cType;
    u_short				cIdItem;
    u_char              cCountItem;
    u_char              inChant;
};
void SendPackageUseItemOtherFunc(int slotItem, char countItem, int InforResult)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    MSG_USE_ITEM_RESULT_ANOTHER_FUNC PackageSendItemUsed;
    memset(&PackageSendItemUsed, 0, sizeof(MSG_USE_ITEM_RESULT_ANOTHER_FUNC));
    PackageSendItemUsed.header = sizeof(MSG_USE_ITEM_RESULT_ANOTHER_FUNC);
    PackageSendItemUsed.ucMessage = 122;
    PackageSendItemUsed.cAnotherCase = 170;
    PackageSendItemUsed.cResult = static_cast<char>(InforResult);
    PackageSendItemUsed.ucCount = countItem;
    PackageSendItemUsed.ucInvenIndex = slotItem;
    __asm
    {

        mov ecx, StoreECX
        mov eax, 0x0050F9E2
        call eax
        push eax
        mov PackageSendItemUsed.moneyCur, eax
        lea eax, PackageSendItemUsed
        xor ecx, ecx
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, PackageSendItemUsed
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
}

void SendPackageRewardBox(u_char typeItem, u_short idItem, u_char count, u_char inchant)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    MSG_REWARD_FROM_BOX PackageSendRewardBox;
    memset(&PackageSendRewardBox, 0, sizeof(MSG_REWARD_FROM_BOX));
    PackageSendRewardBox.header = sizeof(MSG_REWARD_FROM_BOX);
    PackageSendRewardBox.ucMessage = 122;
    PackageSendRewardBox.cAnotherCase = 161;
    PackageSendRewardBox.cResult = 161;
    PackageSendRewardBox.cType = typeItem;
    PackageSendRewardBox.cIdItem = idItem;
    PackageSendRewardBox.cCountItem = count;
    PackageSendRewardBox.inChant = inchant;
    __asm
    {
        lea eax, PackageSendRewardBox
        xor ecx, ecx
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, PackageSendRewardBox
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
}

int AddItemFromBox(int typeItem, int idItem, int count, int InchantItem)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char Listpackage[100];
    int slot = 0;
    memset(&Listpackage, 0, 100);
    Listpackage[0] = 96;
    Listpackage[2] = 80;
    int InchantADd = InchantItem + 10000;
    __asm
    {
        mov eax, InchantADd
        push eax
        mov eax, count
        push eax
        mov eax, idItem
        push eax
        mov eax, typeItem
        push eax
        lea eax, Listpackage
        push eax
        mov ecx, StoreECX
        mov eax, 0x00509EF3
        call eax
        add esp, 0x4
        mov slot, eax
    }
    if (slot != -1)
    {
        __asm
        {
            mov eax, slot
            imul eax, 0x60
            mov ecx, StoreECX
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x18]
            push edx
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            push edx
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            push edx
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            push edx
            mov ecx, StoreECX
            call SendPackageRewardBox
            add esp, 0x10
        }
    }
    return slot;
}
void __declspec(naked)AddInchantForItemBox() //00509FDA
{
    __asm
    {
        push 0x0
        mov eax, [esp + 0x88]
        cmp eax, 0x2710
        jb Default
        sub eax, 0x2710
        test eax, eax
        jb Default
        cmp eax, 0xF
        ja Default
        push 0x0
        push eax
        push 0x00509FE0
        ret
        Default :
        push 0x0
            push 0x0
            push 0x00509FE0
            ret
    }

}
int AddItemForUserBox(int RankBox)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    unsigned int slotitemadd;
    DataBox* InfoBox;
    InfoBox = g_BoxLucky->GetInforBox(RankBox);
    srand(timeGetTime());
    int ramdnumber = rand() % 10000;
    int i = 0;
    while (1)
    {
        if (*(&InfoBox->Item[i].idItem) == 0)
        {
            i = i - 1;
            if (*(&InfoBox->Item[i].idItem) != 0)
            {
                int typeitem = *(&InfoBox->Item[i].idType);
                int iditem = *(&InfoBox->Item[i].idItem);
                int countitem = *(&InfoBox->Item[i].CountId);
                int inchant = *(&InfoBox->Item[i].InchantItem);
                __asm
                {
                    push inchant
                    push countitem
                    push iditem
                    push typeitem
                    mov ecx, StoreECX
                    call AddItemFromBox
                    add esp, 0x10
                    mov slotitemadd, eax
                }
                return slotitemadd;
            }
        }
        else
        {
            if (*(&InfoBox->Item[i].RateIt) >= ramdnumber)
            {
                int typeitem = *(&InfoBox->Item[i].idType);
                int iditem = *(&InfoBox->Item[i].idItem);
                int countitem = *(&InfoBox->Item[i].CountId);
                int inchant = *(&InfoBox->Item[i].InchantItem);
                __asm
                {
                    push inchant
                    push countitem
                    push iditem
                    push typeitem
                    mov ecx, StoreECX
                    call AddItemFromBox
                    add esp, 0x10
                    mov slotitemadd, eax
                }
                return slotitemadd;
            }
        }
        i++;
    }
}
struct AnotherDataUser {
    u_char SlotNew;
};
bool WriteDataInfoUser(AnotherDataUser& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InfoUser/%d.txt", UniqueID);
    AnotherDataUser* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    FILE* fp = fopen(fname, "w");
    if (fp)
    {
        fprintf(fp, "%d", InnforUserLoad->SlotNew);
        returninfo = true;
        fclose(fp);
    }
    else
    {
        std::cout << "Error Create File and Write AnotherData" << std::endl;
    }

    return returninfo;
}
int ProcessOpenSlotRelics(unsigned int money, int infoslot, int param1)
{
    // 0 Thanh Cong
    // 1 Khong Dung VP 1
    // 2 Khong Dung VP 2
    // 3 Khong Du tien
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    switch (param1)
    {
    case 1:
        if (infoslot > 3)
        {
            return 1;
        }
        else
        {
            infoslot = infoslot + 1;
        }
        break;
    case 2:
        if (infoslot < 3)
        {
            return 2;
        }
        else
        {
            infoslot = infoslot + 1;
        }
        break;
    default:
        break;
    }
    if (infoslot > 8)
    {
        infoslot = 8;
    }
    if (infoslot == 1)
    {
        if (money < 1000000000)
        {
            return 3;
        }
        else
        {
            money = money - 1000000000;
        }
    }
    else if (infoslot == 2)
    {
        if (money < 2000000000)
        {
            return 3;
        }
        else
        {
            money = money - 2000000000;
        }
    }
    else if (infoslot == 3)
    {
        if (money < 4000000000)
        {
            return 3;
        }
        else
        {
            money = money - 4000000000;
        }
    }
    __asm
    {
        push 0x1
        push money
        mov ecx, StoreECX
        mov eax, 0x50FA03
        call eax
        mov ecx, StoreECX
        mov eax, infoslot
        mov[ecx + 0xD63E], al
        mov eax, [ecx + 0x1054]
        push eax
        lea ecx, [ecx + 0xD63E]
        push ecx
        call WriteDataInfoUser
        add esp, 0x8
    }
    return 0;
}
int ProcessUsedItemFromUser(int typeItem, int idItem, int countItem, unsigned int uniqueID_User, unsigned int SlotUsed, InvenItemSlot& AddressItem)
{
    // 0 Thanh Cong
    // 1 Ko Tim Thay Type
    // 2 Ko du sl
    // 3 Chua Du time su dung lai
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    DWORD TimePrive;
    __asm
    {
        mov ecx, StoreECX
        xor edx, edx
        mov edx, [ecx + 0xD631]
        mov TimePrive, edx
    }
    int param1 = 0;
    int param2 = 0;
    int resultinfo = 0;
    int resultUsedItem;
    if (countItem <= 0)
    {
        return 2;
    }
    bool resultSaveLog = SaveLogUsedItem(typeItem, idItem, countItem, uniqueID_User);
    if (!resultSaveLog)
    {
        std::cout << "Can't Save Log Used Item" << std::endl;
        return 1;
    }
    for (int i = 0; i < 100; i++)
    {
        if (ListItemProcessFunc[i][0] == typeItem)
        {
            if (ListItemProcessFunc[i][1] == idItem)
            {

                time_t timestarDao = time(nullptr);
                DWORD timeDaoStart = (DWORD)timestarDao;
                if (TimePrive > timeDaoStart)
                {
                    return 3;
                }
                else
                {
                    timeDaoStart = timeDaoStart + 5;
                    __asm
                    {
                        mov ecx, StoreECX
                        mov edx, timeDaoStart
                        mov[ecx + 0xD631], edx
                    }
                    param1 = ListItemProcessFunc[i][2];
                    param2 = ListItemProcessFunc[i][3];
                }

            }
        }
    }
    switch (param1)
    {
    case 1:
        countItem = countItem - 1;
        if (countItem == 0)
        {
            __asm
            {
                push SlotUsed
                mov ecx, StoreECX
                mov eax, 0x004B2960
                call eax
            }
        }
        else
        {
            AddressItem.sCount = countItem;
        }
        __asm
        {
            push param2
            mov ecx, StoreECX
            call SpawnMod
            add esp, 0x4
        }
        break;
    case 2:
        __asm
        {
            mov ecx, StoreECX
            xor eax, eax
            mov eax, [ecx + 0x688F]
            test eax, eax
            jnz VanConBangHoi
            push param2
            mov ecx, StoreECX
            call ChangeParty
            add esp, 0x4
            mov eax, 0x0
            mov resultinfo, eax
        }
        countItem = countItem - 1;
        if (countItem == 0)
        {
            __asm
            {
                push SlotUsed
                mov ecx, StoreECX
                mov eax, 0x004B2960
                call eax
            }
        }
        else
        {
            AddressItem.sCount = countItem;
        }
        __asm
        {
            jmp EndFuncChangePhai
            VanConBangHoi :
            mov eax, 0x3
                mov resultinfo, eax
                EndFuncChangePhai :
        }
        break;
    case 3:
        countItem = countItem - 1;
        if (countItem == 0)
        {
            __asm
            {
                push SlotUsed
                mov ecx, StoreECX
                mov eax, 0x004B2960
                call eax
            }
        }
        else
        {
            AddressItem.sCount = countItem;
        }
        if (param2 == 4)
        {
            __asm
            {
                mov ecx, StoreECX
                xor eax, eax
                mov al, [ecx + 0x1264]
                cmp eax, 0x2
                jnz CheckMnPhai
                mov eax, 0x7
                jmp ProcessChangeClass
                CheckMnPhai :
                cmp eax, 0x4
                    jnz DefaultMonPhai
                    mov eax, 0x8
                    jmp ProcessChangeClass
                    DefaultMonPhai :
                mov eax, 0x4
                    ProcessChangeClass :
                    push eax
                    mov ecx, StoreECX
                    call ChangeClass
                    add esp, 0x4
            }
        }
        else
        {
            __asm
            {
                push param2
                mov ecx, StoreECX
                call ChangeClass
                add esp, 0x4
            }
        }
        break;
    case 4:
        countItem = countItem - 1;
        if (countItem == 0)
        {
            __asm
            {
                push SlotUsed
                mov ecx, StoreECX
                mov eax, 0x004B2960
                call eax
            }
        }
        else
        {
            AddressItem.sCount = countItem;
        }
        __asm
        {
            push param2
            mov ecx, StoreECX
            call AddItemForUserBox
            add esp, 0x4
        }
        break;
    case 5:
        countItem = countItem - 1;
        if (countItem == 0)
        {
            __asm
            {
                push SlotUsed
                mov ecx, StoreECX
                mov eax, 0x004B2960
                call eax
            }
        }
        else
        {
            AddressItem.sCount = countItem;
        }
        __asm
        {
            push param2
            mov ecx, StoreECX
            call EditLevelGM
            add esp, 0x4
        }
        break;
    case 6:
        countItem = countItem - 1;
        if (countItem == 0)
        {
            __asm
            {
                push SlotUsed
                mov ecx, StoreECX
                mov eax, 0x004B2960
                call eax
            }
        }
        else
        {
            AddressItem.sCount = countItem;
        }
        __asm
        {
            mov ecx, StoreECX
            mov eax, param2
            mov DWORD PTR SS : [ecx + 0xD564] , eax
        }
        break;
    case 7: //Mo Slot Moi
        countItem = countItem - 1;
        if (countItem == 0)
        {
            __asm
            {
                push SlotUsed
                mov ecx, StoreECX
                mov eax, 0x004B2960
                call eax
            }
        }
        else
        {
            AddressItem.sCount = countItem;
        }
        __asm
        {
            push param2
            mov ecx, StoreECX
            xor eax, eax
            mov al, [ecx + 0xD63E]
            push eax
            mov ecx, StoreECX
            mov eax, 0x0050F9E2
            call eax
            push eax
            mov ecx, StoreECX
            call ProcessOpenSlotRelics
            add esp, 0xC
            push eax
            mov ecx, StoreECX
            xor edx, edx
            mov dl, [ecx + 0xD63E]
            push edx
            mov edx, SlotUsed
            imul edx, 0x60
            mov ecx, StoreECX
            xor eax, eax
            mov al, [ecx + edx + 0x128C + 0xF]
            push eax
            mov edx, SlotUsed
            push edx
            mov ecx, StoreECX
            mov eax, 0x0050F9E2
            call eax
            push eax
            mov ecx, StoreECX
            call SendPackageInforSlot
            add esp, 0x14
            mov resultinfo, 85
        }
        break;
    default:
        return 1;
        break;
    }
    return resultinfo;
}
void __declspec(naked)UseItemSpawn()
{
    __asm
    {

        mov[ebp - 0x0000F160], eax
        pushad
        mov eax, [ebp - 0x0000F160]
        mov eax, [eax + 0x3]//Get Slot Item Used
        imul eax, eax, 0x60
        mov ecx, [ebp - 0xDBC]
        xor edx, edx
        lea edx, [ecx + eax + 0x0000128C]
        push edx
        mov eax, [ebp - 0x0000F160]
        mov ecx, [eax + 0x3]//Get Slot Item Used
        push ecx
        mov ecx, [ebp - 0xDBC]
        mov eax, [ecx + 0x1054]
        push eax
        mov eax, [ebp - 0x0000F160]
        mov eax, [eax + 0x3]//Get Slot Item Used
        imul eax, eax, 0x60
        mov ecx, [ebp - 0xDBC]
        xor edx, edx
        mov dl, [ecx + eax + 0x0000128C + 0xF]
        push edx
        xor edx, edx
        mov dx, [ecx + eax + 0x0000128C + 0xA]
        push edx
        xor edx, edx
        mov dl, [ecx + eax + 0x0000128C + 0x8]
        push edx
        call ProcessUsedItemFromUser
        add esp, 0x18
        cmp eax, 0x1
        jnz ProcessUseItemContinue
        popad
        mov dword ptr[ebp - 0xF164], 0
        push 0x005E75C6
        ret
        ProcessUseItemContinue :
        cmp eax, 0x55
            jz OpenNewSlotEnd
            push eax
            mov eax, [ebp - 0x0000F160]
            mov eax, [eax + 0x3]//Get Slot Item Used
            imul eax, eax, 0x60
            mov ecx, [ebp - 0xDBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x0000128C + 0xF]
            push edx
            mov eax, [ebp - 0x0000F160]
            mov eax, [eax + 0x3]//Get Slot Item Used
            push eax
            mov ecx, [ebp - 0xDBC]
            call SendPackageUseItemOtherFunc
            add esp, 0xC
            popad
            push 0x005E79CE
            ret

            OpenNewSlotEnd :
        popad
            push 0x005E79CE
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
            jb Default
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
char tempIPCheck[16] = "103.210.20.156";
void __declspec(naked)CheckIPConnect()//006B1E6B
{
    __asm
    {
        mov ecx, DWORD PTR SS:[0x007763AC]
        add ecx, 0x4188
        push ecx
        lea ecx, tempIPCheck
        push ecx
        mov eax, 0x006E43C0
        call eax
        add esp, 0x8
        test eax, eax
        jz Defalt
        mov dword ptr ss:[0x007763AC],0x0
        push 0x007629EC
        push 0x006B1E70
        ret
        Defalt :
        push 0x007629EC
        push 0x006B1E70
        ret
    }
};
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
        jb Default1
        cmp ecx,0x13
        ja Default1
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
void __declspec(naked)IncFailed()//005222B2
{
    __asm
    {
        pushad
        mov[ebp - 0x70], dl
        cmp byte ptr[ebp - 0x70], 0x0
        jz Default
        mov  edx, [ebp - 0x48]
        xor ecx, ecx
        mov  cl, [edx + 0x8]
        cmp ecx, 0x1
        jnz Default
        mov eax, [ebp + 0x8]
        xor edx,edx
        mov dl, [eax + 0xB]
        test edx,edx
        jnz CoCuongDo
        mov eax, [ebp + 0x8]
        mov al, [eax + 0x3]
        cmp al, 0x6E
        jz IncFailedPhysic
        mov  edx, [ebp - 0x48]
        xor ecx, ecx
        mov  cl, [edx + 0x18]
        sub ecx, 0x1
        xor eax, eax
        mov  al, [edx + 0x19]
        test eax, eax
        jz NotGiaHan
        add ecx, eax
        NotGiaHan :
        lea edx, ListChicong
            xor eax, eax
            xor ebx, ebx
            backLoopCheck :
        mov eax, [edx + ebx]
            cmp eax, ecx
            jnz LoopCheck
            xor ecx, ecx
            mov  edx, [ebp - 0x48]
            mov  cl, [edx + 0x9]
            cmp ecx, 0x0
            jnz CheckOptionCloth2
            lea ebx, [ListChicong + ebx]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x8 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x8 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x8 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo71
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit1
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx,0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo71
            NotCrit1 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo71 :
        jmp Default
            //

            CheckOptionCloth2 :
        cmp ecx, 0x1
            jnz CheckOptionCloth4
            lea ebx, [ListChicong + ebx]
            lea ebx, [ebx + 0x20]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /*mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo72
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo72
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit12
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo72
            NotCrit12 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo72 :
        jmp Default
            CheckOptionCloth4 :
        cmp ecx, 0x2
            jnz CheckOptionCloth5
            lea ebx, [ListChicong + ebx]
            lea ebx, [ebx + 0x3C]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /*mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo73
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo73
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit13
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo73
            NotCrit13 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo73 :
        jmp Default

            CheckOptionCloth5 :
        cmp ecx, 0x3
            jnz CheckOptionCloth6
            lea ebx, [ListChicong + ebx]
            lea ebx, [ebx + 0x58]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /*mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo74
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo74
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit14
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo74
            NotCrit14 :
            xor ecx,ecx
            mov cx, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo74 :
        jmp Default

            CheckOptionCloth6 :
        cmp ecx, 0x4
            jnz Default
            lea ebx, [ListChicong + ebx]
            lea ebx, [ebx + 0x74]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /* mov cx, [edx + 0x33]
             test ecx, ecx
             jz NotIncTo75
             mov cl, [edx + 0x18]
             sub ecx, 0x1
             imul ecx, 0x64
             mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo75
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit15
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo75
            NotCrit15 :
            mov cx, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo75 :
        jmp Default

            LoopCheck :
        add ebx, 0x90
            cmp ebx, 0x21C
            jz Default
            jmp backLoopCheck



        IncFailedPhysic:
        mov  edx, [ebp - 0x48]
            xor ecx, ecx
            mov  cl, [edx + 0x18]
            sub ecx, 0x1
            xor eax, eax
            mov  al, [edx + 0x19]
            test eax, eax
            jz NotGiaHan321
            add ecx, eax
            NotGiaHan321 :
            lea edx, ListPhycys
            xor eax, eax
            xor ebx, ebx
            backLoopCheckPhycys :
        mov eax, [edx + ebx]
            cmp eax, ecx
            jnz LoopCheckPhycys
            xor ecx, ecx
            mov  edx, [ebp - 0x48]
            mov  cl, [edx + 0x9]
            cmp ecx, 0x0
            jnz CheckOptionCloth2Phycys
            lea ebx, [ListPhycys + ebx]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x8 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x8 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x8 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /*mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys1
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys1
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit7Phycys1
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo7Phycys1
            NotCrit7Phycys1 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo7Phycys1 :
        jmp Default
            //

            CheckOptionCloth2Phycys :
        cmp ecx, 0x1
            jnz CheckOptionCloth4Phycys
            lea ebx, [ListPhycys + ebx]
            lea ebx, [ebx + 0x20]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /* mov cx, [edx + 0x33]
             test ecx, ecx
             jz NotIncTo7Phycys2
             mov cl, [edx + 0x18]
             sub ecx, 0x1
             imul ecx, 0x64
             mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys2
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit7Phycys2
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo7Phycys2
            NotCrit7Phycys2 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo7Phycys2 :
        jmp Default
            CheckOptionCloth4Phycys :
        cmp ecx, 0x2
            jnz CheckOptionCloth5Phycys
            lea ebx, [ListPhycys + ebx]
            lea ebx, [ebx + 0x3C]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /*mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys3
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys3
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit7Phycys3
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo7Phycys3
            NotCrit7Phycys3 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo7Phycys3 :
        jmp Default

            CheckOptionCloth5Phycys :
        cmp ecx, 0x3
            jnz CheckOptionCloth6Phycys
            lea ebx, [ListPhycys + ebx]
            lea ebx, [ebx + 0x58]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /*mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys4
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys4
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit7Phycys4
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo7Phycys4
            NotCrit7Phycys4 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo7Phycys4 :
        jmp Default

            CheckOptionCloth6Phycys :
        cmp ecx, 0x4
            jnz Default
            lea ebx, [ListPhycys + ebx]
            lea ebx, [ebx + 0x74]
            mov  edx, [ebp - 0x48]
            //ADd Option
            mov ecx, [ebx + 0x4 + 0x4]
            mov[edx + 0x26], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x2B], cx
            xor ecx, ecx
            mov ecx, [ebx + 0x4 + 0x4 + 0x4 + 0x4 + 0x4 + 0x4]
            mov[edx + 0x30], cx
            xor ecx, ecx
            /*mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys5
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx*/
            mov cx, [edx + 0x33]
            test ecx, ecx
            jz NotIncTo7Phycys5
            xor ecx, ecx
            mov cx, [edx + 0x33]
            cmp ecx, 0x17
            jnz NotCrit7Phycys5
            xor ecx, ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            imul ecx, 0x64
            mov word ptr[edx + 0x35], cx
            jmp NotIncTo7Phycys5
            NotCrit7Phycys5 :
            xor ecx,ecx
            mov cl, [edx + 0x18]
            sub ecx, 0x1
            mov word ptr[edx + 0x35], cx
            NotIncTo7Phycys5 :
        jmp Default

            LoopCheckPhycys :
        add ebx, 0x90
            cmp ebx, 0x21C
            jz Default
            jmp backLoopCheckPhycys




        Default:
        popad
            cmp byte ptr[ebp - 0x70], 0
            push 0x005222B9
            ret
            CoCuongDo:
            push 0x0052264A
            ret

    }
}
void __declspec(naked)CheckIncClot()
{
    __asm
    {
        pushad
        mov  ecx, [ebp - 0x48]
        xor eax,eax
        mov al,[ecx+0x8]
        cmp eax,0x1
        jnz Default
        mov eax, [ebp + 0x8]
        mov al, [eax + 0x3]
        cmp al, 0x6E
        jz VatlyOption
        //Get Inchant and Address
        xor ebx, ebx
        xor edx, edx
        mov  ecx, [ebp - 0x48]
        mov dl, [ecx + 0x19]
        mov bl, [ecx + 0x18]
        and ebx, 0xFF
        add ebx,0x1
        add ebx, edx
        imul ebx, 0x90
        lea eax, ListChicong
        lea eax, [eax + ebx]
        lea eax, [eax + 0x4]
        xor ebx, ebx
        mov  ecx, [ebp - 0x48]
        mov bl, [ecx + 0x9]
        and ebx, 0xFF
        imul ebx, 0x1C
        lea eax, [eax + ebx]

        //Get Type Option 1
        mov  ecx, [ebp - 0x48]
        mov ebx, [eax + 0x4]
        mov[ecx + 0x24], bx
        // Get Option 1
        xor ebx, ebx
        mov ebx, [eax + 0x8]
        mov[ecx + 0x26], bx
        //

        //Get Type Option 2
        mov  ecx, [ebp - 0x48]
        mov ebx, [eax + 0xC]
        mov[ecx + 0x29], bx
        // Get Option 2
        xor ebx, ebx
        mov ebx, [eax + 0x10]
        mov[ecx + 0x2B], bx

        //

        //Get Type Option 3
        mov  ecx, [ebp - 0x48]
        mov ebx, [eax + 0x14]
        mov[ecx + 0x2E], bx
        // Get Option 3
        xor ebx, ebx
        mov ebx, [eax + 0x18]
        mov[ecx + 0x30], bx
        mov byte ptr[ecx + 0x23], 0x2
        //
        jmp EndAddOtionClothInc
        //Vat Ly
        VatlyOption :
        //Get Inchant and Address
        xor ebx, ebx
            xor edx, edx
            mov  ecx, [ebp - 0x48]
            mov dl, [ecx + 0x19]
            mov bl, [ecx + 0x18]
            and ebx, 0xFF
            add ebx, 0x1
            add ebx, edx
            imul ebx, 0x90
            lea eax, ListPhycys
            lea eax, [eax + ebx]
            lea eax, [eax + 0x4]
            xor ebx, ebx
            mov  ecx, [ebp - 0x48]
            mov bl, [ecx + 0x9]
            and ebx, 0xFF
            imul ebx, 0x1C
            lea eax, [eax + ebx]

            //Get Type Option 1
            mov  ecx, [ebp - 0x48]
            mov ebx, [eax + 0x4]
            mov [ecx + 0x24], bx
            // Get Option 1
            xor ebx, ebx
            mov ebx, [eax + 0x8]
            mov[ecx + 0x26], bx
            //

            //Get Type Option 2
            mov  ecx, [ebp - 0x48]
            mov ebx, [eax + 0xC]
            mov[ecx + 0x29], bx
            // Get Option 2
            xor ebx, ebx
            mov ebx, [eax + 0x10]
            mov[ecx + 0x2B], bx
            //

            //Get Type Option 3
            mov  ecx, [ebp - 0x48]
            mov ebx, [eax + 0x14]
            mov[ecx + 0x2E], bx
            // Get Option 3
            xor ebx, ebx
            mov ebx, [eax + 0x18]
            mov[ecx + 0x30], bx
            mov byte ptr[ecx + 0x23], 0x1

        EndAddOtionClothInc:
        mov  edx, [ebp - 0x48]
        xor ecx, ecx
        mov cl,[edx+0x18]
        cmp ecx,0x7
        jb Inclow
        xor ecx,ecx
        mov cx,[edx+0x33]
        test ecx,ecx
        jnz Level7
        push 0x64
        mov eax, 0x006A06F0
        call eax
        add esp,0x4
        mov  edx, [ebp - 0x48]
        cmp eax, 0xA
        ja AddOptNew2

            mov word ptr[edx + 0x33], 0x3
            mov word ptr[edx + 0x35], 0x08
            mov byte ptr[edx + 0x37], 0x01
            xor ecx, ecx
            jmp Inclow
            AddOptNew2 :
        cmp eax, 0x1E
            ja AddOptNew4
            mov word ptr[edx + 0x33], 0x8A
            mov word ptr[edx + 0x35], 0x08
            mov byte ptr[edx + 0x37], 0x01
            xor ecx, ecx
            jmp Inclow
            AddOptNew4 :
        cmp eax, 0x32
            ja AddOptNew6
            mov word ptr[edx + 0x33], 0xF
            mov word ptr[edx + 0x35], 0x08
            mov byte ptr[edx + 0x37], 0x01
            xor ecx, ecx
            jmp Inclow
            AddOptNew6 :
        cmp eax, 0x3C
            ja AddOptNew7
            mov word ptr[edx + 0x33], 0x10
            mov word ptr[edx + 0x35], 0x08
            mov byte ptr[edx + 0x37], 0x01
            xor ecx, ecx
            jmp Inclow
            AddOptNew7:
        cmp eax, 0x4E
            ja AddOptNew8
            mov word ptr[edx + 0x33], 0x2F
            mov word ptr[edx + 0x35], 0x08
            mov byte ptr[edx + 0x37], 0x01
            xor ecx, ecx
            jmp Inclow
            AddOptNew8 :
        cmp eax, 0x60
            ja AddOptNew9
            mov word ptr[edx + 0x33], 0x30
            mov word ptr[edx + 0x35], 0x08
            mov byte ptr[edx + 0x37], 0x01
            xor ecx, ecx
            jmp Inclow
            AddOptNew9 :
        mov word ptr [edx+0x33],0x17
        mov word ptr [edx+0x35],0x320
        mov byte ptr[edx + 0x37], 0x01
        xor ecx,ecx
        jmp Inclow
        Level7:
        cmp ecx,0x17
        jnz Addpercen
        xor ecx,ecx
        mov cl, [edx + 0x18]
        add ecx,0x1
        imul ecx,0x64
        cmp ecx,0x5DC
        ja maxcritCloth
        mov [edx+0x35],cx
        jmp AddpercenComplete
        maxcritCloth:
        mov word ptr [edx + 0x35], 0x5DC
        jmp AddpercenComplete
            Addpercen:
            xor ecx, ecx
            mov cx, [edx + 0x35]
            cmp cx,0xF
            ja NotToAddOPtionVang
            add cx,0x1 
            NotToAddOPtionVang:
            mov[edx + 0x35], cx
            AddpercenComplete:
        xor ecx, ecx
        Inclow:
        xor ecx,ecx
        mov cl,[edx + 0x18]
        cmp ecx,0x0
        jnz NotAddRank
        mov byte ptr[edx + 0x2D], 0x1
        mov byte ptr[edx + 0x28], 0x1
        mov byte ptr[edx + 0x32], 0x01
        NotAddRank:

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
        jbe NotDecco
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
/*void __declspec(naked)Checkfaild()
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
}*/
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
void ProcessAddValueForOptTionAn2()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    for (int i = 140; i < 148; i++)
    {
        for (int z = 0; z < 6; z++)
        {
            __asm
            {
                mov eax, i
                imul eax, 0x60
                mov ecx, StoreECX
                lea ecx, [ecx + eax + 0x128C]
                mov eax, z
                imul eax, 0x5
                xor edx, edx
                mov dx, [ecx + eax + 0x24]
                test edx, edx
                jz CheckAnotherValue
                cmp edx, 47
                jnz CheckValue1
                xor edx, edx
                mov dx, [ecx + eax + 0x24 + 0x2]
                mov ecx, StoreECX
                mov eax, [ecx + 0x724C]
                add eax, edx
                mov[ecx + 0x724C], eax
                jmp CheckAnotherValue


                CheckValue1 :
                cmp edx, 48
                    jnz CheckValue2
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7254]
                    add eax, edx
                    mov[ecx + 0x7254], eax
                    jmp CheckAnotherValue


                    CheckValue2 :
                cmp edx, 53
                    jnz CheckValue3
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7246]
                    add eax, edx
                    mov[ecx + 0x7246], eax
                    jmp CheckAnotherValue


                    CheckValue3 :
                cmp edx, 54
                    jnz CheckValue4
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7248]
                    add eax, edx
                    mov[ecx + 0x7248], eax
                    jmp CheckAnotherValue


                    CheckValue4 :
                cmp edx, 63
                    jnz CheckValue5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7240]
                    add eax, edx
                    mov[ecx + 0x7240], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7242]
                    add eax, edx
                    mov[ecx + 0x7242], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7244]
                    add eax, edx
                    mov[ecx + 0x7244], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7246]
                    add eax, edx
                    mov[ecx + 0x7246], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7248]
                    add eax, edx
                    mov[ecx + 0x7248], ax
                    jmp CheckAnotherValue


                    CheckValue5 :
                cmp edx, 93
                    jnz CheckValue6
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FC8]
                    add eax, edx
                    mov[ecx + 0x6FC8], eax
                    jmp CheckAnotherValue


                    CheckValue6 :
                cmp edx, 219
                    jnz CheckValue7
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7272]
                    add eax, edx
                    mov[ecx + 0x7272], eax
                    jmp CheckAnotherValue


                    CheckValue7 :
                cmp edx, 214
                    jnz CheckValue8
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7276]
                    add eax, edx
                    mov[ecx + 0x7276], eax
                    jmp CheckAnotherValue

                    CheckValue8 :
                cmp edx, 219
                    jnz CheckAnotherValue
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7272]
                    add eax, edx
                    mov[ecx + 0x7276], ax
                    jmp CheckAnotherValue

                    CheckAnotherValue :
            }
        }
    }
    for (int i = 12; i < 20; i++)
    {
        for (int z = 0; z < 6; z++)
        {
            __asm
            {
                mov eax, i
                imul eax, 0x60
                mov ecx, StoreECX
                lea ecx, [ecx + eax + 0x128C]
                mov eax, z
                imul eax, 0x5
                xor edx, edx
                mov dx, [ecx + eax + 0x24]
                test edx, edx
                jz CheckAnotherValue1
                cmp edx, 47
                jnz CheckValue31
                xor edx, edx
                mov dx, [ecx + eax + 0x24 + 0x2]
                mov ecx, StoreECX
                mov eax, [ecx + 0x724C]
                add eax, edx
                mov[ecx + 0x724C], eax
                jmp CheckAnotherValue1


                CheckValue31 :
                cmp edx, 48
                    jnz CheckValue32
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7254]
                    add eax, edx
                    mov[ecx + 0x7254], eax
                    jmp CheckAnotherValue1


                    CheckValue32 :
                cmp edx, 53
                    jnz CheckValue33
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7246]
                    add eax, edx
                    mov[ecx + 0x7246], eax
                    jmp CheckAnotherValue1


                    CheckValue33 :
                cmp edx, 54
                    jnz CheckValue34
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7248]
                    add eax, edx
                    mov[ecx + 0x7248], eax
                    jmp CheckAnotherValue1


                    CheckValue34 :
                cmp edx, 63
                    jnz CheckValue35
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7240]
                    add eax, edx
                    mov[ecx + 0x7240], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7242]
                    add eax, edx
                    mov[ecx + 0x7242], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7244]
                    add eax, edx
                    mov[ecx + 0x7244], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7246]
                    add eax, edx
                    mov[ecx + 0x7246], ax
                    //
                    mov eax, i
                    imul eax, 0x60
                    mov ecx, StoreECX
                    lea ecx, [ecx + eax + 0x128C]
                    mov eax, z
                    imul eax, 0x5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7248]
                    add eax, edx
                    mov[ecx + 0x7248], ax
                    jmp CheckAnotherValue1


                    CheckValue35 :
                cmp edx, 93
                    jnz CheckValue36
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FC8]
                    add eax, edx
                    mov[ecx + 0x6FC8], eax
                    jmp CheckAnotherValue1


                    CheckValue36 :
                cmp edx, 219
                    jnz CheckValue37
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7272]
                    add eax, edx
                    mov[ecx + 0x7272], eax
                    jmp CheckAnotherValue1


                    CheckValue37 :
                cmp edx, 214
                    jnz CheckValue38
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7276]
                    add eax, edx
                    mov[ecx + 0x7276], eax
                    jmp CheckAnotherValue1

                    CheckValue38 :
                cmp edx, 219
                    jnz CheckAnotherValue1
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    xor eax, eax
                    mov ax, [ecx + 0x7272]
                    add eax, edx
                    mov[ecx + 0x7276], ax
                    jmp CheckAnotherValue1

                    CheckAnotherValue1 :
            }
        }
    }
}
void ProcessAddValueForOptTionAn()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    for (int i = 140; i < 148; i++)
    {
        for (int z = 0; z < 6; z++)
        {
            __asm
            {
                mov eax, i
                imul eax, 0x60
                mov ecx, StoreECX
                lea ecx, [ecx + eax + 0x128C]
                mov eax, z
                imul eax, 0x5
                xor edx, edx
                mov dx, [ecx + eax + 0x24]
                test edx, edx
                jz CheckAnotherValue
                cmp edx, 0x3
                jnz CheckValue1
                xor edx, edx
                mov dx, [ecx + eax + 0x24 + 0x2]
                mov ecx, StoreECX
                mov eax, [ecx + 0x6FB8]
                add eax, edx
                mov[ecx + 0x6FB8], eax
                jmp CheckAnotherValue


                CheckValue1 :
                cmp edx, 0xF
                    jnz CheckValue2
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FC8]
                    add eax, edx
                    mov[ecx + 0x6FC8], eax
                    jmp CheckAnotherValue


                    CheckValue2 :
                cmp edx, 0x5F
                    jnz CheckValue3
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7060]
                    add eax, edx
                    mov[ecx + 0x7060], eax
                    jmp CheckAnotherValue


                    CheckValue3 :
                cmp edx, 0x17
                    jnz CheckValue4
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7024]
                    add eax, edx
                    mov[ecx + 0x7024], eax
                    jmp CheckAnotherValue


                    CheckValue4 :
                cmp edx, 0x18
                    jnz CheckValue5
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x702C]
                    add eax, edx
                    mov[ecx + 0x702C], eax
                    jmp CheckAnotherValue


                    CheckValue5 :
                cmp edx, 0x90
                    jnz CheckValue6
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FEC]
                    add eax, edx
                    mov[ecx + 0x6FEC], eax
                    jmp CheckAnotherValue


                    CheckValue6 :
                cmp edx, 0x91
                    jnz CheckValue7
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x701C]
                    add eax, edx
                    mov[ecx + 0x701C], eax
                    jmp CheckAnotherValue

                    CheckValue7 :
                cmp edx, 0x86
                    jnz CheckValue8
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7030]
                    add eax, edx
                    mov[ecx + 0x7030], eax
                    jmp CheckAnotherValue

                    CheckValue8 :
                cmp edx, 0x8A
                    jnz CheckValue9
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FF0]
                    add eax, edx
                    mov[ecx + 0x6FF0], eax
                    jmp CheckAnotherValue

                    CheckValue9 :
                cmp edx, 0x10
                    jnz CheckAnotherValue
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7000]
                    add eax, edx
                    mov[ecx + 0x7000], eax
                    jmp CheckAnotherValue

                    CheckAnotherValue :
            }
        }
    }
    for (int i = 12; i < 20; i++)
    {
        for (int z = 0; z < 6; z++)
        {
            __asm
            {
                mov eax, i
                imul eax, 0x60
                mov ecx, StoreECX
                lea ecx, [ecx + eax + 0x128C]
                mov eax, z
                imul eax, 0x5
                xor edx, edx
                mov dx, [ecx + eax + 0x24]
                test edx, edx
                jz CheckAnotherValue2
                cmp edx, 0x3
                jnz CheckValue11
                xor edx, edx
                mov dx, [ecx + eax + 0x24 + 0x2]
                mov ecx, StoreECX
                mov eax, [ecx + 0x6FB8]
                add eax, edx
                mov[ecx + 0x6FB8], eax
                jmp CheckAnotherValue2


                CheckValue11 :
                cmp edx, 0xF
                    jnz CheckValue21
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FC8]
                    add eax, edx
                    mov[ecx + 0x6FC8], eax
                    jmp CheckAnotherValue2


                    CheckValue21 :
                cmp edx, 0x5F
                    jnz CheckValue31
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7060]
                    add eax, edx
                    mov[ecx + 0x7060], eax
                    jmp CheckAnotherValue2


                    CheckValue31 :
                cmp edx, 0x17
                    jnz CheckValue41
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7024]
                    add eax, edx
                    mov[ecx + 0x7024], eax
                    jmp CheckAnotherValue2


                    CheckValue41 :
                cmp edx, 0x18
                    jnz CheckValue51
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x702C]
                    add eax, edx
                    mov[ecx + 0x702C], eax
                    jmp CheckAnotherValue2


                    CheckValue51 :
                cmp edx, 0x90
                    jnz CheckValue61
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FEC]
                    add eax, edx
                    mov[ecx + 0x6FEC], eax
                    jmp CheckAnotherValue2


                    CheckValue61 :
                cmp edx, 0x91
                    jnz CheckValue71
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x701C]
                    add eax, edx
                    mov[ecx + 0x701C], eax
                    jmp CheckAnotherValue2

                    CheckValue71 :
                cmp edx, 0x86
                    jnz CheckValue81
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7030]
                    add eax, edx
                    mov[ecx + 0x7030], eax
                    jmp CheckAnotherValue2

                    CheckValue81 :
                cmp edx, 0x8A
                    jnz CheckValue91
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x6FF0]
                    add eax, edx
                    mov[ecx + 0x6FF0], eax
                    jmp CheckAnotherValue2

                    CheckValue91 :
                cmp edx, 0x10
                    jnz CheckAnotherValue2
                    xor edx, edx
                    mov dx, [ecx + eax + 0x24 + 0x2]
                    mov ecx, StoreECX
                    mov eax, [ecx + 0x7000]
                    add eax, edx
                    mov[ecx + 0x7000], eax
                    jmp CheckAnotherValue2

                    CheckAnotherValue2 :
            }
        }
    }
}
void __declspec(naked)AddOptionCloth()
{
    __asm
    {

        pushad
        xor esi, esi
        mov eax, [ebp - 0x18]
        mov word ptr [eax+0xD64B],0x0
        mov word ptr [eax + 0xD64D], 0x0
        mov word ptr [eax + 0xD64F], 0x0
        mov dword ptr [eax + 0xD653], 0x0
        LoopCheckType :
        mov eax, [ebp - 0x18]
        //Check Opt Inc Cloth
        xor edx, edx
            xor ecx, ecx
            push esi
            imul esi, esi, 0x60
            mov dl, [eax + esi + 0x128C + 0x18]
            cmp dl, 0x1
            jb NotInct
            //
            xor edi, edi
            LoopCheckOption :

        // bo add ebp,esi
            push edi
            lea edi, [edi + esi]
            xor ebx, ebx
            xor edx,edx
            mov dx, [eax + 0x128C + 0x24 + edi]
            cmp edx, 0x13
            jnz NewOptIon1
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheck

            NewOptIon1:
            cmp edx, 0x2D0
            jnz NewOptIon2
            xor ebx,ebx
            mov bx, [eax + 0x128C + 0x26 + edi]
            xor ecx,ecx
            mov cx, [eax + 0xD64B]
            lea ecx, [ecx + ebx]
            mov[eax + 0xD64B], ecx
            jmp EndCheck

            NewOptIon2:
            cmp edx, 0x41
            jnz NewOptIon3
            xor ebx, ebx
            mov bx, [eax + 0x128C + 0x26 + edi]
            xor ecx, ecx
            mov cx, [eax + 0xD64D]
            lea ecx, [ecx + ebx]
            mov[eax + 0xD64D], ecx
            jmp EndCheck

            NewOptIon3:
            cmp edx, 0xE3
            jnz NewOptIon4
            xor ebx, ebx
            mov bx, [eax + 0x128C + 0x26 + edi]
            xor ecx, ecx
            mov cx, [eax + 0xD64F]
            lea ecx, [ecx + ebx]
            mov[eax + 0xD64F], ecx
            jmp EndCheck

            NewOptIon4:
            cmp edx, 0x29
            jnz CheckType2
            xor ebx, ebx
            mov bx, [eax + 0x128C + 0x26 + edi]
            xor ecx, ecx
            mov cx, [eax + 0xD653]
            lea ecx, [ecx + ebx]
            mov[eax + 0xD653], ecx
            jmp EndCheck

            CheckType2 :
        cmp edx, 0x18
            jnz CheckType3
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + ebx]
            mov[eax + 0x702C], ecx
            jmp EndCheck


            CheckType3 :
        jmp CheckType4
        /*cmp edx, 0x82
            jnz CheckType4
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7250]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7250], ecx
            jmp EndCheck*/


        CheckType4 :
        jmp CheckType5
        /*cmp edx, 0x83
            jnz CheckType5
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7258]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7258], ecx
            jmp EndCheck*/


            CheckType5 :
        cmp edx, 0x17
            jnz CheckType6
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7024], ecx
            jmp EndCheck


            CheckType6 :
        jmp CheckType7
        /*cmp edx, 0x32
            jnz CheckType7
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7240], cx
            jmp EndCheck*/


            CheckType7 :
        cmp edx, 0x3D
            jnz CheckType8
            /*mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FD4], ecx*/
            jmp EndCheck


            CheckType8 :
        cmp edx, 0x2
            jnz CheckType9
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FC4], ecx
            jmp EndCheck


            CheckType9 :
        cmp edx, 0x1
            jnz CheckType10
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck


            CheckType10 :
        cmp edx, 0xF
            jnz CheckType11
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheck


            CheckType11 :
        jmp CheckType12
        /*cmp edx, 0x34
            jnz CheckType12
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x7240 + 0x4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7240], cx
            jmp EndCheck*/


        CheckType12 :
        jmp CheckType13
       /* cmp edx, 0x89
            jnz CheckType13
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck*/


            CheckType13 :
        cmp edx, 0x88
            jnz CheckType14
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FBC], ecx
            jmp EndCheck


            CheckType14 :
        cmp edx, 0x10
            jnz NewOptCheckType14
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7000], ecx
            jmp EndCheck

            NewOptCheckType14 :
        jmp NewOptCheckType141
        /*cmp edx, 0x2F
            jnz NewOptCheckType141
            xor ebx, ebx
            xor ecx, ecx
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x724C]
            lea ecx, [ecx + ebx]
            mov[eax + 0x724C], ecx
            jmp EndCheck*/

            NewOptCheckType141 :
        cmp edx, 0x3
            jnz NewOptCheckType1412
            xor ebx, ebx
            xor ecx, ecx
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x6FB8]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FB8], ecx
            jmp EndCheck

            NewOptCheckType1412 :
        cmp edx, 0x8A
            jnz NewOptCheckType214211
            xor ebx, ebx
            xor ecx, ecx
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x6FF0]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FF0], ecx
            jmp EndCheck


            NewOptCheckType214211 :
             cmp edx, 0x9
            jnz CritDmg
                 xor ebx, ebx
                 xor ecx, ecx
                 mov bx, [eax + 0x128C + 0x26 + edi]
                 mov cx, [eax + 0x6FCC]
                 lea ecx, [ecx + ebx]
                 mov[eax + 0x6FCC], ecx
            jmp EndCheck

            CritDmg:
        cmp edx, 0x86
            jnz EndCheck
            xor ebx, ebx
            xor ecx, ecx
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x7030]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7030], ecx
            jmp EndCheck


            EndCheck :
            pop edi
            add edi, 0x5
            cmp edi, 0x1E
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
        //Check Opt Decco
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
            xor edx,edx
            mov dx, [ebx]
            mov eax, [ebp - 0x18]
            cmp edx, 0x13
            jnz CheckType22
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx
            jmp EndCheck2D

            CheckType22 :
        cmp edx, 0x18
            jnz CheckType23
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + edx]
            mov[eax + 0x702C], ecx
            jmp EndCheck2D


            CheckType23 :
        jmp CheckType24
        /*cmp edx, 0x82
            jnz CheckType24
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7250]
            lea ecx, [ecx + edx]
            mov[eax + 0x7250], ecx
            jmp EndCheck2D*/


        CheckType24 :
        jmp CheckType25
       /* cmp edx, 0x83
            jnz CheckType25
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7258]
            lea ecx, [ecx + edx]
            mov[eax + 0x7258], ecx
            jmp EndCheck2D*/


            CheckType25 :
        cmp edx, 0x17
            jnz CheckType26
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + edx]
            mov[eax + 0x7024], ecx
            jmp EndCheck2D


            CheckType26 :
        jmp CheckType27
        /*cmp edx, 0x32
            jnz CheckType27
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7240]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheck2D*/


            CheckType27 :
        cmp edx, 0x3D
            jnz CheckType28
           /* xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx*/
            jmp EndCheck2D


            CheckType28 :
        cmp edx, 0x2
            jnz CheckType29
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC4], ecx
            jmp EndCheck2D


            CheckType29 :
        cmp edx, 0x1
            jnz CheckType210
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck2D


            CheckType210 :
        cmp edx, 0xF
            jnz CheckType211
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheck2D


            CheckType211 :
        jmp CheckType212
        /*cmp edx, 0x34
            jnz CheckType212
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7240 + 0x4]
            lea ecx, [ecx + edx]
            mov[eax + 0x7240], cx
            jmp EndCheck2D*/


        CheckType212 :
        jmp CheckType213
        /*cmp edx, 0x89
            jnz CheckType213
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx
            jmp EndCheck2D*/


            CheckType213 :
        cmp edx, 0x88
            jnz CheckType214
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FBC], ecx
            jmp EndCheck2D


            CheckType214 :
        cmp edx, 0x10
            jnz CheckType21415
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx
            jmp EndCheck2D

            CheckType21415 :
        jmp CheckType21416
        /*cmp edx, 0x18
            jnz CheckType21416
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + edx]
            mov[eax + 0x702C], ecx
            jmp EndCheck2D*/

            CheckType21416 :
        cmp edx, 0x9
            jnz CheckType21417
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FCC]
            lea ecx, [ecx + edx]
            mov [eax + 0x6FCC], ecx
            jmp EndCheck2D

            CheckType21417 :
        cmp edx, 0xA
            jnz CheckType21418
            xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7004]
            lea ecx, [ecx + edx]
            mov[eax + 0x7004], ecx
            jmp EndCheck2D

            CheckType21418 :
        jmp CheckType21419
        /*cmp edx, 0xB
            jnz CheckType21419
            xor edx, edx
            xor ecx,ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x86B8]
            lea ecx, [ecx + edx]
            mov[eax + 0x86B8], cl
            jmp EndCheck2D*/

        CheckType21419 :
        jmp CheckType21420
        /*cmp edx, 0xC
            jnz CheckType21420
            xor edx, edx
            xor ecx, ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x86D0]
            lea ecx, [ecx + edx]
            mov[eax + 0x86D0], cl
            jmp EndCheck2D*/

        CheckType21420 :
        jmp CheckType21421
        /*cmp edx, 0xD
            jnz CheckType21421
            xor edx, edx
            xor ecx, ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x86C0]
            lea ecx, [ecx + edx]
            mov[eax + 0x86C0], cl
            jmp EndCheck2D*/

            CheckType21421 :
        cmp edx, 0x86
            jnz CheckType21422
            xor edx, edx
            xor ecx, ecx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7030]
            lea ecx, [ecx + edx]
            mov[eax + 0x7030], cx
            jmp EndCheck2D

            CheckType21422 :
        jmp CheckType21423
        /*cmp edx, 0xF
            jnz CheckType21423
            xor edx, edx
            xor ecx, ecx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx
            jmp EndCheck2D*/

        CheckType21423 :
        jmp CheckType215542
        /*cmp edx, 0x10
            jnz CheckType215542
            xor edx, edx
            xor ecx, ecx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx
            jmp EndCheck2D*/

        CheckType215542 :
        jmp CheckType2155
        /*cmp edx, 0x2F
            jnz CheckType2155
            xor edx, edx
            xor ecx, ecx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x724C]
            lea ecx, [ecx + edx]
            mov[eax + 0x724C], ecx
            jmp EndCheck2D*/
        
        CheckType2155 :
        //jmp EndCheck2D
        cmp edx, 0x5B
            jnz EndCheck2D
            xor edx, edx
            xor ecx, ecx
            mov dx, [ebx + 0x4]
            mov cx, [eax + 0x7058]
            lea ecx, [ecx + edx]
            mov[eax + 0x7058], ecx
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

        //Phong ngu sat thuong cm
        mov eax, [ebp - 0x18]
            xor edx, edx
            mov dx, [eax + 0xD636]
            xor ecx, ecx
            mov cx, [eax + 0xD638]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD63A]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD64B]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD63C]
            add edx, ecx
            mov[eax + 0xCAA6], dx
            //Opt Giam Sat Thuong
            mov eax, [ebp - 0x18]
            xor edx, edx
            mov dl, [eax + 0xD581]
            xor ecx, ecx
            mov cl, [eax + 0xD591]
            add edx, ecx
            xor ecx, ecx
            mov cl, [eax + 0xD5A1]
            add edx, ecx
            xor ecx, ecx
            mov cl, [eax + 0xD5B1]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD64D]
            add edx, ecx
            xor ecx, ecx
            mov cl, [eax + 0xD5C1]
            add edx, ecx
            cmp edx, 0x32
            ja MaxOptGiamSatThuong
            mov byte ptr[eax + 0xD561], dl
            jmp EndofGiamSatThuong
            MaxOptGiamSatThuong :
        mov byte ptr[eax + 0xD561], 0x32
            EndofGiamSatThuong :
            //Opt Deff Pvp
            mov eax, [ebp - 0x18]
            xor edx, edx
            mov dx, [eax + 0xD584]
            xor ecx, ecx
            mov cx, [eax + 0xD594]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5A4]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5B4]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD64F]
            add edx, ecx
            xor ecx, ecx
            mov cx, [eax + 0xD5C4]
            add edx, ecx
            mov[eax + 0xD570], dx
            //Opt Phan Dmg
            mov eax, [ebp - 0x18]
            xor edx, edx
            mov edx, [eax + 0xD588]
            xor ecx, ecx
            mov ecx, [eax + 0xD598]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5A8]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD653]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5B8]
            add edx, ecx
            xor ecx, ecx
            mov ecx, [eax + 0xD5C8]
            add edx, ecx
            cmp edx, 0x64
            ja MaxOptPhanDamge
            mov[eax + 0xD574], edx
            jmp EndofPhanDmg
            MaxOptPhanDamge :
            mov[eax + 0xD574], 0x64
            EndofPhanDmg :
            mov ecx, [ebp - 0x18]
            call ProcessAddValueForOptTionAn
            popad
            mov eax, [ebp - 0x18]
            mov byte ptr[eax + 0x00007582], 0x0
            push 0x004D04A5
            ret
    }
}
void __declspec(naked)AddOptionCloth2()
{
    __asm
    {

        pushad
        xor esi, esi
        LoopCheckType :
        mov eax, [ebp - 0x18]
            //Check Opt Inc Cloth
            xor edx, edx
            xor ecx, ecx
            push esi
            imul esi, esi, 0x60
            mov dl, [eax + esi + 0x128C + 0x18]
            cmp dl, 0x1
            jb NotInct
            //
            xor edi, edi
            LoopCheckOption :

        // bo add ebp,esi
        push edi
            lea edi, [edi + esi]
            xor ebx, ebx
            xor edx, edx
            mov dl, [eax + 0x128C + 0x24 + edi]
            jmp CheckType2

            CheckType2 :
            jmp CheckType3


            CheckType3 :
            cmp edx, 0x82
                jnz CheckType4
                mov bx, [eax + 0x128C + 0x26 + edi]
                mov ecx, [eax + 0x7250]
                lea ecx, [ecx + ebx]
                mov[eax + 0x7250], ecx
                jmp EndCheck


        CheckType4:
            cmp edx, 0x83
                jnz CheckType5
                mov bx, [eax + 0x128C + 0x26 + edi]
                mov ecx, [eax + 0x7258]
                lea ecx, [ecx + ebx]
                mov[eax + 0x7258], ecx
                jmp EndCheck


                CheckType5:
            jmp CheckType6
        /*cmp edx, 0x17
            jnz CheckType6
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7024], ecx
            jmp EndCheck*/


            CheckType6 :
            cmp edx, 0x32
                jnz CheckType7
                mov bx, [eax + 0x128C + 0x26 + edi]
                mov cx, [eax + 0x7240]
                lea ecx, [ecx + ebx]
                mov[eax + 0x7240], cx
                jmp EndCheck


        CheckType7:
        cmp edx, 0x3D
            jnz CheckType8
            /*mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FD4], ecx*/
            jmp EndCheck


            CheckType8 :
        cmp edx, 0x2
            jnz CheckType9
            /*mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FC4], ecx*/
            jmp EndCheck


            CheckType9 :
        cmp edx, 0x1
            jnz CheckType10
            /*mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FFC], ecx*/
            jmp EndCheck


            CheckType10 :
        cmp edx, 0xF
            jnz CheckType11
            /*mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FC8], ecx*/
            jmp EndCheck


            CheckType11 :
        jmp CheckType12
            /*cmp edx, 0x34
                jnz CheckType12
                mov bx, [eax + 0x128C + 0x26 + edi]
                mov cx, [eax + 0x7240 + 0x4]
                lea ecx, [ecx + ebx]
                mov[eax + 0x7240], cx
                jmp EndCheck*/


        CheckType12:
        jmp CheckType13
            /* cmp edx, 0x89
                 jnz CheckType13
                 mov bx, [eax + 0x128C + 0x26 + edi]
                 mov ecx, [eax + 0x6FFC]
                 lea ecx, [ecx + ebx]
                 mov[eax + 0x6FFC], ecx
                 jmp EndCheck*/


        CheckType13:
        cmp edx, 0x88
            jnz CheckType14
           /* mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FBC], ecx*/
            jmp EndCheck


            CheckType14 :
        cmp edx, 0x10
            jnz NewOptCheckType14
           /* mov bx, [eax + 0x128C + 0x26 + edi]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7000], ecx*/
            jmp EndCheck

            NewOptCheckType14 :
        //jmp NewOptCheckType141
            cmp edx, 0x2F
                jnz NewOptCheckType141
                xor ebx, ebx
                xor ecx, ecx
                mov bx, [eax + 0x128C + 0x26 + edi]
                mov cx, [eax + 0x724C]
                lea ecx, [ecx + ebx]
                mov[eax + 0x724C], ecx
                jmp EndCheck

        NewOptCheckType141:
        cmp edx, 0x3
            jnz NewOptCheckType1412
            /*xor ebx, ebx
            xor ecx, ecx
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x6FB8]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FB8], ecx*/
            jmp EndCheck

            NewOptCheckType1412 :
        cmp edx, 0x8A
            jnz NewOptCheckType214211
            /*xor ebx, ebx
            xor ecx, ecx
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x6FF0]
            lea ecx, [ecx + ebx]
            mov[eax + 0x6FF0], ecx*/
            jmp EndCheck


            NewOptCheckType214211 :
        //jmp CritDmg
            cmp edx, 0x30
                jnz CritDmg
                xor ebx, ebx
                xor ecx, ecx
                mov bx, [eax + 0x128C + 0x26 + edi]
                mov cx, [eax + 0x7254]
                lea ecx, [ecx + ebx]
                mov[eax + 0x7254], ecx
                jmp EndCheck

        CritDmg:
        cmp edx, 0x86
            jnz EndCheck
           /* xor ebx, ebx
            xor ecx, ecx
            mov bx, [eax + 0x128C + 0x26 + edi]
            mov cx, [eax + 0x7030]
            lea ecx, [ecx + ebx]
            mov[eax + 0x7030], ecx*/
            jmp EndCheck


            EndCheck :
        pop edi
            add edi, 0x5
            cmp edi, 0x19
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
        //Check Opt Decco
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
            cmp eax, 0x00
            jz Default22
            xor edx, edx
            mov ebx, [eax + 0x14]
            test ebx, ebx
            jz Default22
            xor edi, edi
            LoopAdd2 :
        push eax
            xor edx, edx
            mov dx, [ebx]
            mov eax, [ebp - 0x18]
            cmp edx, 0x13
            jnz CheckType22
            /*xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FD4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FD4], ecx*/
            jmp EndCheck2D

            CheckType22 :
        cmp edx, 0x18
            jnz OptEXp
           /* xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x702C]
            lea ecx, [ecx + edx]
            mov[eax + 0x702C], ecx*/
            jmp EndCheck2D

            OptEXp :
#ifdef BoOptEXPDrop
        jmp CheckType23
#endif // BoOptEXPDrop

        cmp edx, 0xDA
            jnz OptDrop
            xor edx, edx
            mov dx, [ebx + 0x4]
            xor ecx, ecx
            mov cx, [eax + 0x7270]
            lea ecx, [ecx + edx]
            mov[eax + 0x7270], cx
            jmp EndCheck2D

            OptDrop :
        cmp edx, 0xDB
            jnz CheckType23
            xor edx, edx
            mov dx, [ebx + 0x4]
            xor ecx, ecx
            mov cx, [eax + 0x7272]
            lea ecx, [ecx + edx]
            mov[eax + 0x7272], cx
            jmp EndCheck2D

            CheckType23 :
        //jmp CheckType24
            cmp edx, 0x82
                jnz CheckType24
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov ecx, [eax + 0x7250]
                lea ecx, [ecx + edx]
                mov[eax + 0x7250], ecx
                jmp EndCheck2D


        CheckType24:
        //jmp CheckType25
             cmp edx, 0x83
                 jnz CheckType25
                 xor edx, edx
                 mov dx, [ebx + 0x4]
                 mov ecx, [eax + 0x7258]
                 lea ecx, [ecx + edx]
                 mov[eax + 0x7258], ecx
                 jmp EndCheck2D


        CheckType25:
        cmp edx, 0x17
            jnz CheckType26
            /*xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7024]
            lea ecx, [ecx + edx]
            mov[eax + 0x7024], ecx*/
            jmp EndCheck2D


            CheckType26 :
        //jmp CheckType27
            cmp edx, 0x32
                jnz CheckType27
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov cx, [eax + 0x7240]
                lea ecx, [ecx + edx]
                mov[eax + 0x7240], cx
                jmp EndCheck2D


        CheckType27:
        jmp CheckType28


            CheckType28 :
        cmp edx, 0x2
            jnz CheckType29
           /* xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC4]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC4], ecx*/
            jmp EndCheck2D


            CheckType29 :
        cmp edx, 0x1
            jnz CheckType210
           /* xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FFC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FFC], ecx*/
            jmp EndCheck2D


            CheckType210 :
        cmp edx, 0xF
            jnz CheckType211
            /*xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FC8]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FC8], ecx*/
            jmp EndCheck2D


            CheckType211 :
        //jmp CheckType212
            cmp edx, 0x34
                jnz CheckType212
                xor edx, edx
                mov dx, [ebx + 0x4]
                mov cx, [eax + 0x7240 + 0x4]
                lea ecx, [ecx + edx]
                mov[eax + 0x7240], cx
                jmp EndCheck2D


        CheckType212:
        jmp CheckType213


        CheckType213:
        cmp edx, 0x88
            jnz CheckType214
            /*xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FBC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FBC], ecx*/
            jmp EndCheck2D


            CheckType214 :
        cmp edx, 0x10
            jnz CheckType21415
            /*xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7000]
            lea ecx, [ecx + edx]
            mov[eax + 0x7000], ecx*/
            jmp EndCheck2D

            CheckType21415 :
        jmp CheckType21416

        CheckType21416:
        cmp edx, 0x9
            jnz CheckType21417
           /* xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x6FCC]
            lea ecx, [ecx + edx]
            mov[eax + 0x6FCC], ecx*/
            jmp EndCheck2D

            CheckType21417 :
        cmp edx, 0xA
            jnz CheckType21418
            /*xor edx, edx
            mov dx, [ebx + 0x4]
            mov ecx, [eax + 0x7004]
            lea ecx, [ecx + edx]
            mov[eax + 0x7004], ecx*/
            jmp EndCheck2D

            CheckType21418 :
        jmp CheckType21419
            /*cmp edx, 0xB
                jnz CheckType21419
                xor edx, edx
                xor ecx,ecx
                mov dl, [ebx + 0x4]
                mov cl, [eax + 0x86B8]
                lea ecx, [ecx + edx]
                mov[eax + 0x86B8], cl
                jmp EndCheck2D*/

        CheckType21419:
        jmp CheckType21420
            /*cmp edx, 0xC
                jnz CheckType21420
                xor edx, edx
                xor ecx, ecx
                mov dl, [ebx + 0x4]
                mov cl, [eax + 0x86D0]
                lea ecx, [ecx + edx]
                mov[eax + 0x86D0], cl
                jmp EndCheck2D*/

        CheckType21420:
        jmp CheckType21421
            /*cmp edx, 0xD
                jnz CheckType21421
                xor edx, edx
                xor ecx, ecx
                mov dl, [ebx + 0x4]
                mov cl, [eax + 0x86C0]
                lea ecx, [ecx + edx]
                mov[eax + 0x86C0], cl
                jmp EndCheck2D*/

        CheckType21421:
        cmp edx, 0x86
            jnz CheckType21422
            /*xor edx, edx
            xor ecx, ecx
            mov dl, [ebx + 0x4]
            mov cl, [eax + 0x7030]
            lea ecx, [ecx + edx]
            mov[eax + 0x7030], cl*/
            jmp EndCheck2D

            CheckType21422 :
        jmp CheckType21423
            /*cmp edx, 0xF
                jnz CheckType21423
                xor edx, edx
                xor ecx, ecx
                mov dx, [ebx + 0x4]
                mov cx, [eax + 0x6FC8]
                lea ecx, [ecx + edx]
                mov[eax + 0x6FC8], ecx
                jmp EndCheck2D*/

        CheckType21423:
        jmp CheckType215542
            /*cmp edx, 0x10
                jnz CheckType215542
                xor edx, edx
                xor ecx, ecx
                mov dx, [ebx + 0x4]
                mov cx, [eax + 0x7000]
                lea ecx, [ecx + edx]
                mov[eax + 0x7000], ecx
                jmp EndCheck2D*/

        CheckType215542:
        jmp CheckType2155
            /*cmp edx, 0x2F
                jnz CheckType2155
                xor edx, edx
                xor ecx, ecx
                mov dx, [ebx + 0x4]
                mov cx, [eax + 0x724C]
                lea ecx, [ecx + edx]
                mov[eax + 0x724C], ecx
                jmp EndCheck2D*/

        CheckType2155:
        jmp EndCheck2D
            /*cmp edx, 0x3F
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
                jmp EndCheck2D*/

        EndCheck2D:
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
            Default22 :
            mov ecx, [ebp - 0x18]
            call ProcessAddValueForOptTionAn2

        popad
            mov eax, [ebp - 0x18]
            mov byte ptr[eax + 0x00007583], 0x0
            push 0x004D0C56
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
        mov al, [edx + 0x4]
        imul eax, 0x60
        mov  ecx, [ebp - 0x6C]
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x8]
        cmp dl, 0x1
        jnz Default
        xor edx, edx
        mov edx,[ebp+0x8]
        xor ecx,ecx
        mov cl, [edx+0xB]
        test ecx,ecx
        jnz CoCuongDo
        mov ecx, [ebp - 0x6C]
        mov dl, [ecx + eax + 0x128C + 0x18]
        sub edx, 0x1
        mov[ecx + eax + 0x128C + 0x18], dl
        push 0x00522819
        ret

        Default :
        xor eax, eax
        mov al, [edx + 0x4]
        push eax
        mov ecx, [ebp - 0x6C]
        push 0x00522814
        ret

        CoCuongDo:
        push 0x00522819
        ret
    }
}
void __declspec(naked)DontDeleteClothInc1()
{
    __asm
    {
        push 0x64
        mov eax, 0x006A06F0
        call eax
        add esp, 0x4
        cmp eax,0x50
        ja HenTinhLuyen
        mov eax, [ebp + 0x8]
        xor ecx,ecx
        mov  cl, [eax + 0x4]
        imul ecx, 0x60
        mov  eax, [ebp - 0x6C]
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x28]
        push 0x11
        push 0x0
        push edx
        xor edx, edx
        mov dx, [ecx + eax + 0x128C + 0xA]
        push edx
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0x8]
        push edx
        push 0x3
        mov ecx, [ebp - 0x6C]
        call addLog
        add esp,0x18
        xor ecx, ecx
        mov eax, [ebp + 0x8]
        mov  cl, [eax + 0x4]
        push ecx
        mov ecx, [ebp - 0x6C]
        push 0x005225A8
        ret


        HenTinhLuyen:
        push 0x005225EC
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
        jb Default
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
        push ecx
        xor ecx,ecx
        mov cl, [eax + 0x6]
        imul ecx, 0x60
        xor eax, eax
        mov eax, [ebp - 0x50]
        xor edx,edx
        mov dl, [eax + ecx + 0x128C + 0x18]
        pop eax
        cmp eax,edx
        jz Default2
        mov ecx,eax
        lea eax, [ebp - 0x2C]
        sub ecx, 0x1
        mov[eax + 0x5], cl
        Default :
        lea eax, [ebp - 0x2C]
            push    eax
            mov     ecx, [ebp - 0x50]
            push 0x00522CB8
            ret

            Default2 :
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
void __declspec(naked)ChageSizePvpModRESULT_MOB()//005CCE8C 10  chieu thuc ky
{
    __asm
    {
        push 0x1C //1B
        push 0x0
        lea eax, [ebp - 0x00008F78]
        push 0x005CCE96
        ret
    }
}
void __declspec(naked)ChageSizepkRoundingResultMob()//005CD09C 10  chieu thuc ky
{
    __asm
    {
        push 0x15
        push 0x0
        lea edx, [ebp - 0x81C]
        push 0x005CD0A6
        ret
    }
}
void __declspec(naked)ChageSizepkRoundingResultMobSend()//005DE6AA  6 chieu thuc ky
{
    __asm
    {
        push 0x14
        lea eax, [ebp - 0x81C]
        push eax
        lea eax, roundresultmod
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, roundresultmod
        mov byte ptr[ecx], 0x16 //1B
        mov byte ptr[ecx + 0x15], al //toc do danh
        mov byte ptr[ecx + 0x14], dl //more dmg
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea edx, roundresultmod
        push 0x005DE6C3
        ret
    }
}
void __declspec(naked)ChageSizepkRoundingResultPvp()//005DF08E  6 chieu thuc ky
{
    __asm
    {
        push 0x13
        lea ecx, [ebp - 0x00000D98]
        push ecx
        lea eax, roundresultpvp2
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, roundresultpvp2
        mov byte ptr[ecx], 0x15 //1B
        mov byte ptr[ecx + 0x14], al //toc do danh
        mov byte ptr[ecx + 0x13], dl //more dmg
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea ecx, roundresultpvp2
        push 0x005DF095
        ret
    }
}
void __declspec(naked)ChageSizepkRoundingResultMobNuker2()//005CD32A 10  chieu thuc ky
{
    __asm
    {
        push 0x15
        lea eax, [ebp - 0x81C]
        push eax
        lea eax, roundresultmod
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, roundresultmod
        mov byte ptr[ecx], 0x16 //1B
        mov byte ptr[ecx + 0x15], dl //more dmg
        mov byte ptr[ecx + 0x14], al //toc do danh
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea edx, roundresultmod
        push 0x005DE6C3
        ret
    }
}
void __declspec(naked)ChageSizepkRoundingResultMobSendNuker2()//005D7AAA  7 chieu thuc ky
{
    __asm
    {
        push 0x14
        lea eax, [ebp - 0x90AC]
        push eax
        lea eax, castingresultmod
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, castingresultmod
        mov byte ptr[ecx], 0x16 //1B
        mov byte ptr[ecx + 0x15], al //more dmg
        mov byte ptr[ecx + 0x14], dl //toc do danh
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea edx, castingresultmod
        push 0x005D7AC3
        ret
    }
}

void __declspec(naked)ChageSizepkActiveResultPvp()//005CCEE7 chieu thuc ky
{
    __asm
    {
        push 0x1B
        push 0x0
        lea ecx, [ebp - 0x0000D840]
        push 0x005CCEF1
        ret
    }
}
void __declspec(naked)ChageSizepkSmashResultMob()//005CCF41 chieu thuong
{
    __asm
    {
        push 0x16
        push 0x0
        lea edx, [ebp - 0x00000844]
        push 0x005CCF4B
        ret
    }
}
void __declspec(naked)ChageSizepkSmashResultPvp()//005CCF9B chieu thuong
{
    __asm
    {
        push 0x15
        push 0x0
        lea eax, [ebp - 0x00000830]
        push 0x005CCFA5
        ret
    }
}
void __declspec(naked)ChangeLenghtPvpModRESULT_MOB()//005D4D74  6 chieu thuc ky
{
    __asm
    {
        push 0x1A
        lea eax,[ebp - 0x00008F78]
        push eax
        lea eax, actresuldmod
        push eax
        mov eax,0x006E3CC0
        call eax
        add esp,0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax,eax
        xor edx,edx
        mov al,[ecx+ 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, actresuldmod
        mov byte ptr[ecx],0x1C //1B
        mov byte ptr[ecx+0x1b], dl //more dmg
        mov byte ptr[ecx+0x1a], al //toc do danh
        mov al,[ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea ecx, actresuldmod
        push 0x005D4D8B
        ret
    }
}
void __declspec(naked)ChangeLenghtActiveResultPvp()//005D58A2 6 chieu thuc ky
{
    __asm
    {
        push 0x1A
        lea eax, [ebp - 0x0000D840]
        push eax
        lea eax, actresuldpvp
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, actresuldpvp
        mov byte ptr[ecx], 0x1C 
        mov byte ptr[ecx + 0x1B], dl //more dmg
        mov byte ptr[ecx + 0x1A], al //toc do danh
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea eax, actresuldpvp
        push 0x005D58BB
        ret
    }
}
void __declspec(naked)ChangeLenghtpkSmashResultMob()//005DD00A 6
{
    __asm
    {
        push 0x14
        lea eax, [ebp - 0x00000844]
        push eax
        lea eax, smashingresultpvp
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, smashingresultpvp
        mov byte ptr[ecx], 0x16 //1B
        mov byte ptr[ecx + 0x15], dl //more dmg
        mov byte ptr[ecx + 0x14], al //toc do danh
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea ecx, smashingresultpvp
        push 0x005DD021
        ret
    }
}
void __declspec(naked)ChangeLenghtpkSmashResultPvp()//005DDDEA 7
{
    __asm
    {
        push 0x14
        lea eax, [ebp - 0x00000830]
        push eax
        lea eax, smashingresultmob
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, smashingresultmob
        mov byte ptr[ecx], 0x16 //1B
        mov byte ptr[ecx + 0x15], dl //more dmg
        mov byte ptr[ecx + 0x14], al //toc do danh
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea ecx, smashingresultmob
        push 0x005DDE01
        ret
    }
}
void __declspec(naked)ChangeLenghtpkSmashResultPvp2()//005DDA7C 7
{
    __asm
    {
        push 0x13
        lea eax, [ebp - 0x00000830]
        push eax
        lea eax, smashingresultpvp
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp, 0xC
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        xor edx, edx
        mov al, [ecx + 0xCAA4]
        mov dl, [ecx + 0xCAB0]
        lea ecx, smashingresultpvp
        mov byte ptr[ecx], 0x14 //1B
        //mov byte ptr[ecx + 0x15], dl //more dmg
        mov byte ptr[ecx + 0x13], al //toc do danh
        lea ecx, smashingresultpvp
        mov al, [ecx]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea ecx, smashingresultpvp
        push 0x005DDA82
        ret
    }
}
void __declspec(naked)BonusDeffence()//004D6DDE 7
{
    __asm
    {
        movsx ecx, byte ptr[ebp + 0x18]
        fild dword ptr[ecx * 0x4 + 0x0075FCD8]
        movsx eax,[ebp+0x18]
        push eax
        fstp dword ptr[ebp+0x18]
        fld dword ptr[ebp - 0x4]
        fsub dword ptr[ebp + 0x18]
        mov eax, 0x006E5A28
        call eax
        push ebx
        mov ebx,0x32
        push edx
        xor edx,edx
        div ebx
        pop edx
        pop ebx
        cmp eax,0x13
        jb Accept
        mov eax,0x13
        Accept:
        mov [ebp-0x4],eax
        fild dword ptr[ebp - 0x4]
        fadd dword ptr[ebp + 0x18]
        fstp dword ptr[ebp - 0x4]
        pop eax
        mov [ebp+0x18],eax
        push 0x004D6DEC
        ret
    }
}
void __declspec(naked)GioiHanDmgVlPvp()//004D6D86 7
{
    __asm
    {
       mov eax, [ebp + 0x10]
       sub eax, [ebp + 0x14]
       mov[ebp - 0x8], eax
       mov eax,[ebp+0x8]
       cmp eax,0x16E360
       jl Default
       mov dword ptr [ebp+0x8], 0x16E360
       Default:
       push 0x004D6D8F
       ret
    }
}
void __declspec(naked)GioiHanDmgVlPvpSauDeff()//004D6E37 7
{
    __asm
    {
        mov eax, [ebp - 0xC]
        cmp eax,0xEA60
        jb Default
        mov eax,0xEA60
        Default:
        mov esp,ebp
        push 0x004D6E3C
        ret
    }
}
void __declspec(naked)GioiHanDmgKCPvpSauDeff()//004D6EF7 7
{
    __asm
    {
        mov eax, [ebp - 0xC]
        cmp eax, 0xEA60
        jb Default
        mov eax, 0xEA60
        Default:
        mov esp, ebp
        push 0x004D6EFC
        ret
    }
}
void __declspec(naked)GioiHanDmgkcPvp()//004D6E46 7
{
    __asm
    {
        mov eax, [ebp + 0x10]
        sub eax, [ebp + 0x14]
        mov[ebp - 0x8], eax
        mov eax, [ebp + 0x8]
        cmp eax, 0x16E360
        jl Default
        mov dword ptr[ebp + 0x8], 0x16E360
        Default:
        push 0x004D6E4F
        ret
    }
}
void __declspec(naked)NdTangCuongDoCloth()//00522013 7
{
    __asm
    {
        mov ecx, [ebp - 0x6C]
        mov eax,0x004B2AD0
        call eax
        cmp eax,0x1
        jz loc_522054
        mov eax,[ebp+0x8]
        xor ecx,ecx
        mov cl,[eax+0x4]
        imul ecx,0x60
        mov eax,[ebp-0x6C]
        xor edx,edx
        mov dl,[eax+ecx+0x128C+0x8]
        cmp edx,0x1
        jnz Default
        mov eax, [ebp + 0x8]
        xor ecx, ecx
        mov cl, [eax + 0x5]
        imul ecx, 0x60
        mov eax, [ebp - 0x6C]
        xor edx, edx
        mov dx, [eax + ecx + 0x128C + 0xA]
        cmp edx, 0x62
        jnz Default
        mov eax, [ebp + 0x8]
        xor ecx, ecx
        mov cl, [eax + 0x4]
        mov [eax+0x531A],cl
        imul ecx, 0x60
        mov eax, [ebp - 0x6C]
        xor edx, edx
        mov dl, [eax + ecx + 0x128C + 0x28]
        add edx,0x1
        mov[eax + ecx + 0x128C + 0x28],dl
        //Delete Item
        mov eax, [ebp + 0x8]
        xor ecx, ecx
        mov cl, [eax + 0x5]
        imul ecx, 0x60
        mov eax, [ebp - 0x6C]
        xor edx, edx
        mov dl, [eax + ecx + 0x128C + 0xF]
        sub dl, 0x1
        mov [eax + ecx + 0x128C + 0xF], dl
        cmp dl, 0x0
        jnz KoBangKhong1
        mov eax, [ebp + 0x8]
        xor ecx, ecx
        mov cl, [eax + 0x5]
        push ecx
        mov ecx, [ebp - 0x6C]
        mov eax, 0x004B2960
        call eax
        KoBangKhong1 :
        push 0x00522054
        ret
        //

        Default:
        push 0x00522020
        ret
        loc_522054:
        push 0x00522054
        ret
    }
}
void __declspec(naked)GoGiaHanCucDai()//00524D80 7
{
    __asm
    {
        mov edx, [ebp - 0x14]
        and edx, 0xFF
        imul edx, 0x60
        mov ecx, [ebp - 0x60]
        xor eax, eax
        mov al, [ecx + 0x128C + edx + 0x8]
        cmp al, 0x1
        jnz Default
        xor eax, eax
        mov al, [ecx + 0x128C + edx + 0x9]
        cmp al, 0x4
        ja Out524939
        mov edx, [ebp - 0x8]
        and edx, 0xFF
        imul edx, 0x60
        mov ecx, [ebp - 0x60]
        xor eax, eax
        mov ax, [ecx + 0x128C + edx + 0xA]
        cmp ax, 0x5B
        jnz Out524939
        mov edx, [ebp - 0x14]
        and edx, 0xFF
        imul edx, 0x60
        mov ecx, [ebp - 0x60]
        xor eax, eax
        mov al, [ecx + 0x128C + edx + 0x18]
        cmp al, 0x0
        jz Out524939
        mov al, [ecx + 0x128C + edx + 0x19]
        test eax, eax
        jz Out524939
        
        xor eax, eax
        mov ax, [ecx + 0x128C + edx + 0x24]
        cmp ax, 0x13
        jnz KhiCong
        lea eax, ListPhycys
        xor ebx, ebx
        mov bl, [ecx + 0x128C + edx + 0x18]
        imul ebx, 0x90
        lea eax, [eax + ebx]
        lea eax, [eax + 0x4]
        xor ebx, ebx
        mov bl, [ecx + 0x128C + edx + 0x9]
        and ebx, 0xFF
        imul ebx, 0x1C
        lea eax, [eax + ebx]
        mov ebx, [eax + 8]
        mov[ecx + 0x128C + edx + 0x26], bx

        mov ebx, [eax + 0x10]
        mov[ecx + 0x128C + edx + 0x2B], bx

        mov ebx, [eax + 0x18]
        mov[ecx + 0x128C + edx + 0x30], bx
        xor ebx, ebx
        mov bl, [ecx + 0x128C + edx + 0x33]
        cmp ebx, 0x17
        jnz NotCrit
        xor ebx, ebx
        mov bl, [ecx + 0x128C + edx + 0x19]
        cmp ebx, 0x1
        jz Remove1
        mov bx, [ecx + 0x128C + edx + 0x35]
        sub bx, 0xC8
        jmp AddBack
        Remove1 :
        mov bx, [ecx + 0x128C + edx + 0x35]
            sub bx, 0x64
            AddBack :
            mov[ecx + 0x128C + edx + 0x35], bx
            jmp SendPackeget
            NotCrit :
        xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x19]
            cmp ebx, 0x1
            jz Remove1NotCrit
            xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            sub bx, 0x2
            jmp AddBack2
            Remove1NotCrit :
        xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            sub bx, 0x1
            AddBack2 :
            mov[ecx + 0x128C + edx + 0x35], bx
            jmp SendPackeget

            KhiCong :
        lea eax, ListChicong
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x18]
            imul ebx, 0x90
            lea eax, [eax + ebx]
            lea eax, [eax + 0x4]
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x9]
            and ebx, 0xFF
            imul ebx, 0x1C
            lea eax, [eax + ebx]
            mov ebx, [eax + 8]
            mov[ecx + 0x128C + edx + 0x26], bx

            mov ebx, [eax + 0x10]
            mov[ecx + 0x128C + edx + 0x2B], bx

            mov ebx, [eax + 0x18]
            mov[ecx + 0x128C + edx + 0x30], bx
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x33]
            cmp ebx, 0x17
            jnz NotCrit23
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x19]
            cmp ebx, 0x1
            jz Remove123
            mov bx, [ecx + 0x128C + edx + 0x35]
            sub bx, 0xC8
            jmp AddBack22
            Remove123 :
        mov bx, [ecx + 0x128C + edx + 0x35]
            sub bx, 0x64
            AddBack22 :
            mov[ecx + 0x128C + edx + 0x35], bx
            jmp SendPackeget
            NotCrit23 :
        xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x19]
            cmp ebx, 0x1
            jz Remove1NotCrit21
            xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            sub bx, 0x2
            jmp AddBack221
            Remove1NotCrit21 :
        xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            sub bx, 0x1
            AddBack221 :
            mov[ecx + 0x128C + edx + 0x35], bx
            SendPackeget :
        mov edx, [ebp - 0x14]
            and edx, 0xFF
            push edx
            call SendInforCloth
            add esp,0x4
            mov edx, [ebp - 0x8]
            and edx, 0xFF
            imul edx, 0x60
            mov ecx, [ebp - 0x60]
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0xF]
            sub eax, 0x1
            mov[ecx + 0x128C + edx + 0xF], al
            cmp eax, 0x0
            jnz KoBangKhong12
            mov edx, [ebp - 0x8]
            and edx, 0xFF
            push ecx
            mov ecx, [ebp - 0x60]
            mov eax, 0x004B2960
            call eax
            KoBangKhong12 :
            lea  ecx, [ebp - 0x4C]
            mov eax, 0x52A790
            call eax
            mov edx, [ebp - 0x8]
            and edx, 0xFF
            mov[ebp - 0x47], dl
            imul edx, 0x60
            mov ecx, [ebp - 0x60]
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0xF]
            mov[ebp - 0x46], al
            mov edx, [ebp - 0x14]
            and edx, 0xFF
            mov[ebp - 0x48], dl
            imul edx, 0x60
            mov ecx, [ebp - 0x60]
            xor eax, eax
            mov byte ptr[ecx + 0x128C + edx + 0x19],0x0
            push 0x00525029
            ret

            Default :
        mov ecx, [ebp - 0x14]
            and ecx, 0x000000FF
            push 0x00524D89
            ret

            Out524939 :
        push 0x00524E73
            ret
    }
}
void __declspec(naked)GiaHanCucDai()//005248D3
{
    __asm
    {
        mov edx, [ebp - 0x14]
        and edx, 0xFF
        imul edx,0x60
        mov ecx,[ebp - 0x60]
        xor eax,eax
        mov al,[ecx+0x128C+edx+0x8]
        cmp al,0x1
        jnz Default
        xor eax, eax
        mov al, [ecx + 0x128C + edx + 0x9]
        cmp al, 0x4
        ja Out524939
        mov edx, [ebp - 0x8]
        and edx, 0xFF
        imul edx, 0x60
        mov ecx, [ebp - 0x60]
        xor eax, eax
        mov ax, [ecx + 0x128C + edx + 0xA]
        cmp ax,0x5A
        jnz Tang1GiaTri
        mov edx, [ebp - 0x14]
        and edx, 0xFF
        imul edx, 0x60
        mov ecx, [ebp - 0x60]
        xor eax, eax
        mov al, [ecx + 0x128C + edx + 0x18]
        cmp al, 0x0
        jz Out524939
        mov al, [ecx + 0x128C + edx + 0x19]
        test eax,eax
        jnz Out524939
        mov [ecx + 0x128C + edx + 0x19],0x2
        xor eax,eax
        mov ax, [ecx + 0x128C + edx + 0x24]
        cmp ax,0x13
        jnz KhiCong
        lea eax, ListPhycys
        xor ebx,ebx
        mov bl, [ecx + 0x128C + edx + 0x18]
        and ebx,0xFF
        add ebx, 0x2
        imul ebx,0x90
        lea eax,[eax+ ebx]
        lea eax,[eax+0x4]
        xor ebx,ebx
        mov bl, [ecx + 0x128C + edx + 0x9]
        and ebx,0xFF
        imul ebx, 0x1C
        lea eax, [eax + ebx]
        mov ebx,[eax+8]
        mov [ecx + 0x128C + edx + 0x26],bx

            mov ebx, [eax+0x10]
            mov[ecx + 0x128C + edx + 0x2B], bx

            mov ebx, [eax+0x18]
            mov[ecx + 0x128C + edx + 0x30], bx
            xor ebx,ebx
            mov bl,[ecx + 0x128C + edx + 0x33]
            cmp ebx,0x17
            jnz NotCrit
            xor ebx,ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            cmp ebx,0x5DC
            ja NotaddCritMax
            add bx,0xC8
            NotaddCritMax:
            mov[ecx + 0x128C + edx + 0x35],bx
            jmp SendPackeget22

            NotCrit:
            xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            cmp ebx,0xF
            ja NotaddValueMax
            add bx, 0x2
            NotaddValueMax:
            mov[ecx + 0x128C + edx + 0x35], bx
                jmp SendPackeget22

        KhiCong:
            lea eax, ListChicong
                xor ebx, ebx
                mov bl, [ecx + 0x128C + edx + 0x18]
                and ebx, 0xFF
                add ebx, 0x2
                imul ebx, 0x90
                lea eax, [eax + ebx]
                lea eax, [eax + 0x4]
                xor ebx, ebx
                mov bl, [ecx + 0x128C + edx + 0x9]
                and ebx, 0xFF
                imul ebx, 0x1C
                lea eax, [eax + ebx]
                mov ebx, [eax + 8]
                mov[ecx + 0x128C + edx + 0x26], bx

                mov ebx, [eax + 0x10]
                mov[ecx + 0x128C + edx + 0x2B], bx

                mov ebx, [eax + 0x18]
                mov[ecx + 0x128C + edx + 0x30], bx
                xor ebx, ebx
                mov bl, [ecx + 0x128C + edx + 0x33]
                cmp ebx, 0x17
                jnz NotCrit11
                xor ebx, ebx
                mov bx, [ecx + 0x128C + edx + 0x35]
                cmp ebx, 0x5DC
                ja NotaddCritMax2
                add bx, 0xC8
                NotaddCritMax2:
                mov[ecx + 0x128C + edx + 0x35], bx
                jmp SendPackeget22

                NotCrit11 :
            xor ebx, ebx
                mov bx, [ecx + 0x128C + edx + 0x35]
                cmp ebx, 0x5DC
                ja NotaddValueMax2
                add bx, 0x2
                NotaddValueMax2:
                mov[ecx + 0x128C + edx + 0x35], bx
                jmp SendPackeget22


        Tang1GiaTri:
        cmp ax, 0x59
        jnz Out524939
            mov edx, [ebp - 0x14]
            and edx, 0xFF
            imul edx, 0x60
            mov ecx, [ebp - 0x60]
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0x18]
            cmp al, 0x0
            jz Out524939
            mov al, [ecx + 0x128C + edx + 0x19]
            test eax, eax
            jnz Out524939
            mov[ecx + 0x128C + edx + 0x19], 0x1
            xor eax, eax
            mov ax, [ecx + 0x128C + edx + 0x24]
            cmp ax, 0x13
            jnz KhiCong11
            lea eax, ListPhycys
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x18]
            and ebx, 0xFF
            add ebx,0x1
            imul ebx, 0x90
            lea eax, [eax + ebx]
            lea eax, [eax + 0x4]
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x9]
            and ebx, 0xFF
            imul ebx, 0x1C
            lea eax, [eax + ebx]
            mov ebx, [eax + 8]
            mov[ecx + 0x128C + edx + 0x26], bx

            mov ebx, [eax + 0x10]
            mov[ecx + 0x128C + edx + 0x2B], bx

            mov ebx, [eax + 0x18]
            mov[ecx + 0x128C + edx + 0x30], bx
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x33]
            cmp ebx, 0x17
            jnz NotCrit321
            xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            cmp ebx, 0x5DC
            ja NotaddCritMax3
            add bx, 0x64
            NotaddCritMax3:
            mov[ecx + 0x128C + edx + 0x35], bx
            jmp SendPackeget22

            NotCrit321 :
        xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            cmp ebx, 0x5DC
            ja NotaddValueMax3
            add bx, 0x1
            NotaddValueMax3:
            mov[ecx + 0x128C + edx + 0x35], bx
            jmp SendPackeget22

            KhiCong11 :
        lea eax, ListChicong
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x18]
            and ebx, 0xFF
            add ebx,0x1
            imul ebx, 0x90
            lea eax, [eax + ebx]
            lea eax, [eax + 0x4]
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x9]
            and ebx, 0xFF
            imul ebx, 0x1C
            lea eax, [eax + ebx]
            mov ebx, [eax + 8]
            mov[ecx + 0x128C + edx + 0x26], bx

            mov ebx, [eax + 0x10]
            mov[ecx + 0x128C + edx + 0x2B], bx

            mov ebx, [eax + 0x18]
            mov[ecx + 0x128C + edx + 0x30], bx
            xor ebx, ebx
            mov bl, [ecx + 0x128C + edx + 0x33]
            cmp ebx, 0x17
            jnz NotCrit1112
            xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            cmp ebx, 0x5DC
            ja NotaddCritMax4
            add bx, 0x64
            NotaddCritMax4:
            mov[ecx + 0x128C + edx + 0x35], bx
            jmp SendPackeget22

            NotCrit1112 :
        xor ebx, ebx
            mov bx, [ecx + 0x128C + edx + 0x35]
            cmp ebx, 0x5DC
            ja NotaddValueMax4
            add bx, 0x1
            NotaddValueMax4:
            mov[ecx + 0x128C + edx + 0x35], bx
            SendPackeget22 :
        mov edx, [ebp - 0x14]
            and edx, 0xFF
            push edx
            call SendInforCloth
            add esp,0x4
            mov edx, [ebp - 0x8]
            and edx, 0xFF
            imul edx, 0x60
            mov ecx, [ebp - 0x60]
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0xF]
            sub eax, 0x1
            mov[ecx + 0x128C + edx + 0xF], al
            cmp eax, 0x0
            jnz KoBangKhong12
            mov edx, [ebp - 0x8]
            and edx, 0xFF
            push ecx
            mov ecx, [ebp - 0x60]
            mov eax, 0x004B2960
            call eax
            KoBangKhong12 :
            lea  ecx, [ebp - 0x4C]
            mov eax,0x52A6C0
            call eax
            mov edx, [ebp - 0x8]
            and edx, 0xFF
            mov [ebp - 0x46], dl
            imul edx, 0x60
            mov ecx, [ebp - 0x60]
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0xF]
            mov [ebp-0x45],al
            mov edx, [ebp - 0x14]
            and edx, 0xFF
            mov[ebp - 0x48], dl
            imul edx, 0x60
            mov ecx, [ebp - 0x60]
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0x19]
            mov [ebp - 0x47], al
            mov  ecx, [ebp - 0x1C]
            push 0x00524BB3
            ret


        Default:
        mov ecx, [ebp - 0x14]
        and ecx, 0x000000FF
        push 0x005248DC
        ret

        Out524939:
        push 0x524939
        ret
    }
}
void __declspec(naked)GetGiaTriCucDai()//0051005E 7
{
    __asm
    {
        mov dl, [ecx + 0x18]
        mov[eax + 0x12], dl
        mov dl, [ecx + 0x19]
        mov[eax + 0x13], dl
        push 0x00510064
        ret
    }
}
void __declspec(naked)BonusDeffenceVL1()//00593E09 7
{
    __asm
    {
        movsx ecx, byte ptr[ebp + 0x18]
        fild dword ptr[ecx * 0x4 + 0x0075FCD8]
        mov eax, [ebp + 0x18]
        push eax
        fstp dword ptr[ebp + 0x18]
        fld dword ptr[ebp - 0x4]
        fsub dword ptr[ebp + 0x18]
        mov eax, 0x006E5A28
        call eax
        push ebx
        mov ebx, 0x32
        push edx
        xor edx, edx
        div ebx
        pop edx
        pop ebx
        mov[ebp - 0x4], eax
        fild dword ptr[ebp - 0x4]
        fadd dword ptr[ebp + 0x18]
        fstp dword ptr[ebp - 0x4]
        pop eax
        mov[ebp + 0x18], eax
        push 0x00593E2C
        ret
    }
}

void __declspec(naked)BonusDeffenceKC()//004D6E9E 7
{
    __asm
    {
        movsx ecx, byte ptr[ebp + 0x18]
        fild dword ptr[ecx * 0x4 + 0x0075FCD8]
        movsx eax, [ebp + 0x18]
        push eax
        fstp dword ptr[ebp + 0x18]
        fld dword ptr[ebp - 0x4]
        fsub dword ptr[ebp + 0x18]
        mov eax, 0x006E5A28
        call eax
        push ebx
        mov ebx, 0x32
        push edx
        xor edx, edx
        div ebx
        pop edx
        pop ebx
        cmp eax,0x13
        jbe Accept
        mov eax,0x13
        Accept:
        mov[ebp - 0x4], eax
        fild dword ptr[ebp - 0x4]
        fadd dword ptr[ebp + 0x18]
        fstp dword ptr[ebp - 0x4]
        pop eax
        mov[ebp + 0x18], eax
        push 0x004D6EAC
        ret
    }
}
void __declspec(naked)BonusDeffenceKC1()//005944F9 7
{
    __asm
    {
        movsx ecx, byte ptr[ebp + 0x18]
        fild dword ptr[ecx * 0x4 + 0x0075FCD8]
        mov eax, [ebp + 0x18]
        push eax
        fstp dword ptr[ebp + 0x18]
        fld dword ptr[ebp - 0x4]
        fsub dword ptr[ebp + 0x18]
        mov eax, 0x006E5A28
        call eax
        push ebx
        mov ebx, 0x32
        push edx
        xor edx, edx
        div ebx
        pop edx
        pop ebx
        mov[ebp - 0x4], eax
        fild dword ptr[ebp - 0x4]
        fadd dword ptr[ebp + 0x18]
        fstp dword ptr[ebp - 0x4]
        pop eax
        mov[ebp + 0x18], eax
        push 0x0059451C
        ret
    }
}
void __declspec(naked)AddNewValue1()//005F894F 5
{
    __asm
    {
        //ID Pet 4 BYTE
        //1 byte tdd 
        //1 byte khang hieu ung
        //2 byte deff crit
        //4 byte dmg boss
        //4 byte time cooldown
        //4 BYTE MORE DMG 
        //CAC8 = Dmg Boss
        //CACC = Blood HSB
        // push 0xCAB4 ko co slot moi
        //D555 1 byte tdd Nick
        //D556 1 byte tdd Item
        //D557 1 byte khang hieu ung Nick
        //D558 1 byte khang hieu ung Item
        //D560 1 Slot CombineSuccess
        //D561 1 Giam ST
        //D562 2 Tang ST Vo cong
        //D564 4 Opt Tang che tao
        //D568 4 Store Gia Tri Tinh Luyen
        //D56C 4 Bonus Dmg Vo Cong
        //D570 2 Deff Pvp
        //D572 2 Xuyen Deff Pvp
        //D574 4 Phan Dmg
        //D578 4 KhangPhanDmg
        //D57C 4 PhanDmgConLai
        //Danh Cho Quan Ao
        //D 1 byte tdd Nick
        //D580 1 byte khang hieu ung
        //D581 1 Giam ST
        //D582 2 Tang ST Vo cong
        //D584 2 Deff Pvp
        //D586 2 Xuyen Deff Pvp
        //D588 4 Phan Dmg
        //D58C 4 KhangPhanDmg
        //End D590
        //Danh Cho Decco
        //D590 1 byte khang hieu ung
        //D591 1 Giam ST
        //D592 2 Tang ST Vo cong
        //D594 2 Deff Pvp
        //D596 2 Xuyen Deff Pvp
        //D598 4 Phan Dmg
        //D59C 4 KhangPhanDmg
        //End D5A0
        //Danh Cho Tin Vat
        //D5A0 1 byte khang hieu ung
        //D5A1 1 Giam ST
        //D5A2 2 Tang ST Vo cong
        //D5A4 2 Deff Pvp
        //D5A6 2 Xuyen Deff Pvp
        //D5A8 4 Phan Dmg
        //D5AC 4 KhangPhanDmg
        //End D5B0
        //Set Quan Ao
        //D5B0 1 byte khang hieu ung
        //D5B1 1 Giam ST
        //D5B2 2 Tang ST Vo cong
        //D5B4 2 Deff Pvp
        //D5B6 2 Xuyen Deff Pvp
        //D5B8 4 Phan Dmg
        //D5BC 4 KhangPhanDmg
        //End D5C0
        //Set Tin Vat
        //D5C0 1 byte khang hieu ung
        //D5C1 1 Giam ST
        //D5C2 2 Tang ST Vo cong
        //D5C4 2 Deff Pvp
        //D5C6 2 Xuyen Deff Pvp
        //D5C8 4 Phan Dmg
        //D5CC 4 KhangPhanDmg
        //End D5D0
        //D5D1 1 TypeId1
        //D5D2 2 TuiBot
        //D5D4 2 Count1
        //D5D6 1 TypeId2
        //D5D7 2 TuiDuong
        //D5D9 2 Count2
        //D5DB 1 TypeId3
        //D5DC 2 TuiTrung
        //D5DE 2 Count3
        //D5E0 0
        //D5E1 1 TypeId1
        //D5E2 2 TuiBot
        //D5E4 2 Count1
        //D5E6 1 TypeId2
        //D5E7 2 TuiDuong
        //D5E9 2 Count2
        //D5EB 1 TypeId3
        //D5EC 2 TuiTrung
        //D5EE 2 Count3
        //D5F0 0
        //D5F1 1 TypeId1
        //D5F2 2 TuiBot
        //D5F4 2 Count1
        //D5F6 1 TypeId2
        //D5F7 2 TuiDuong
        //D5F9 2 Count2
        //D5FB 1 TypeId3
        //D5FC 2 TuiTrung
        //D5FE 2 Count3
        //D600 0
        //D601 1 TypeId1
        //D602 2 TuiBot
        //D604 2 Count1
        //D606 1 TypeId2
        //D607 2 TuiDuong
        //D609 2 Count2
        //D60B 1 TypeId3
        //D60C 2 TuiTrung
        //D60E 2 Count3
        //D610 0
        //D611 1 TypeId1
        //D612 2 TuiBot
        //D614 2 Count1
        //D616 1 TypeId2
        //D617 2 TuiDuong
        //D619 2 Count2
        //D61B 1 TypeId3
        //D61C 2 TuiTrung
        //D61E 2 Count3
        //D620 0
        //D621 4 Diem Boss
        //D625 1 Phe
        //D626 4 Diem TK
        //D62A 4 TOP
        //D62E 4 LienTram
        //D632 4 CountPk
        //D636 2 phong ngu stcm set
        //D638 2 Phong ngu stcm trangbi
        //D63A 2 phong ngu stcm tv
        //D63C 2 phong ngu stcm tv
        //D63E 1 Rank level
        //D63F 1 CountSoloQ
        //D640 1 CountPtQ
        //D641 4 nDiemTichLuyTK
        //D645 4 nDiemhoatDong
        //D649 1 FlagQ
        //D64A 1 KiemTraNgaySolo
        //Opt Them Trang Bi
        //D64B 2 phong thu stcm
        //D64D 2 tru sat thuong
        //D64F 2 Deff Pvp
        //D651 2 Xuyen Deff Pvp
        //D653 4 Phan Dmg
        //D657 4 KhangPhanDmg
        //Opt Them Vu Khi
        //D65B 1 byte khang hieu ung
        //D65C 1 Giam ST
        //D65D 2 Tang ST Vo cong
        //D65F 2 Deff Pvp
        //D661 2 Xuyen Deff Pvp
        //D663 4 Phan Dmg
        //D667 4 KhangPhanDmg
        //New Address - 24 /09
        /*
           ****** Cac gia tri can add
           -- 1 - BYTE số lần đã đi
           ------ Nguyên Lý Hoạt Động Quyết mới
           -- Kiểm tra yêu cầu Level
           -- Kiểm tra số thành viên trong party
           -- Kiêm tra vật phẩm trong người mỗi thành viên
           -- 
        */
        //D66B: Opt Them Phong An
        //--> EBAB
        //ED00 Flag Open
        //ED01 Time Check
        //ED05 End Func
        push 0xED06
        push 0x005F8954
        ret
    }
}
void __declspec(naked)AddNewValue2()//005F8A3C 5
{
    __asm
    {
        push 0xED06
        push 0x005F8954
        ret
    }
}

int TinhToanDeffPVp(int totalDmg, int deffpvp)
{
    int dmgsautru = 0;
    int deffpvpvo = deffpvp;
    int tongdmg = totalDmg;
    float phantramdeff = (float)(deffpvpvo * 0.005);
    dmgsautru = static_cast<int>(((phantramdeff / 100) * tongdmg));
    return dmgsautru;
}
int TinhPhanPhanDmg(int totalDmg, int giatriphandmg)
{
    int dmgphanlai = 0;
    int phantramphandmg;
    float giatrisautin;
    phantramphandmg = (int)giatriphandmg;
    int tongdmg = totalDmg;
    giatrisautin = (float)phantramphandmg / 100.0;
    dmgphanlai = static_cast<int>(giatrisautin * tongdmg);
    return dmgphanlai;
}
void __declspec(naked)TinhToanDeffVaPhanDam()//004B8FBB 8
{
    __asm
    {
        xor ecx,ecx
        xor eax,eax
        mov eax,[ebp-0xA8]
        mov cx,[eax+0xD570]
        test ecx,ecx
        jz PhanDamgge
        xor edx,edx
        mov dx,[eax+0xD570]
        mov eax,[ebp+0x8]
        xor ecx,ecx
        mov cx,[eax+0xD572]
        cmp ecx,edx
        ja PhanDamgge
        sub edx, ecx
        push edx
        mov ecx, [ebp - 0x00000058]
        push ecx
        call TinhToanDeffPVp
        add esp, 0x8
        mov ecx, [ebp - 0x00000058]
        sub ecx, eax
        mov[ebp - 0x00000058], ecx
        //
        PhanDamgge:
        xor ecx,ecx
        mov eax, [ebp - 0xA8]
        mov cl,[eax+0xD574]
        test ecx,ecx
        jz Default
        mov eax,[ebp+0x8]
        xor edx,edx
        mov dl,[eax+0xD578]
        cmp edx,ecx
        ja Default
        sub ecx,edx
        //
        push ecx
        mov ecx, [ebp - 0x00000058]
        push ecx
        call TinhPhanPhanDmg
        add esp,0x8
        push eax
        mov ecx, [ebp + 0x8]
        mov [ecx+0xAC15],0x1
        mov eax,0x4B6B29
        call eax
        Default:
        mov eax,0x00406AD0
        call eax
        push 0x004B8FC0
        ret
    }
}
void __declspec(naked)TinhToanDeffVaPhanDamChieuThucKy()//004B8376 8
{
    __asm
    {
        xor ecx, ecx
        xor eax, eax
        mov eax, [ebp - 0xA4]
        mov cx, [eax + 0xD570]
        test ecx, ecx
        jz PhanDamgge
        xor edx, edx
        mov dx, [eax + 0xD570]
        mov eax, [ebp + 0x8]
        xor ecx, ecx
        mov cx, [eax + 0xD572]
        cmp ecx, edx
        ja PhanDamgge
        sub edx, ecx
        push edx
        mov ecx, [ebp - 0x00000094]
        push ecx
        call TinhToanDeffPVp
        add esp, 0x8
        mov ecx, [ebp - 0x00000094]
        sub ecx, eax
        mov [ebp - 0x00000094],ecx
            PhanDamgge :
        xor ecx, ecx
            mov eax, [ebp - 0xA4]
            mov cl, [eax + 0xD574]
            test ecx, ecx
            jz Default
            mov eax, [ebp + 0x8]
            xor edx, edx
            mov dl, [eax + 0xD578]
            cmp edx, ecx
            ja Default
            sub ecx, edx
            push ecx
            mov ecx, [ebp - 0x00000094]
            push ecx
            call TinhPhanPhanDmg
            add esp, 0x8
            push eax
            mov ecx, [ebp + 0x8]
            mov[ecx + 0xAC15], 0x1
            mov eax, 0x4B6B29
            call eax
        Default:
            xor ecx, ecx
            mov eax, 0x00776345
            mov cl, [eax]
            push 0x004B837E
            ret
    }
}
void __declspec(naked)TinhToanDeffVaPhanDamNuker()//004B9A59 8
{
    __asm
    {
        xor ecx, ecx
        xor eax, eax
        mov eax, [ebp - 0xBC]
        mov cx, [eax + 0xD570]
        test ecx, ecx
        jz PhanDamgge
        xor edx, edx
        mov dx, [eax + 0xD570]
        mov eax, [ebp + 0x8]
        xor ecx, ecx
        mov cx, [eax + 0xD572]
        cmp ecx, edx
        ja XuyenDeffPvpLonHon
        sub edx, ecx
        push edx
        mov ecx, [ebp - 0x00000054]
        push ecx
        call TinhToanDeffPVp
        add esp,0x8
        mov ecx, [ebp - 0x00000054]
        sub ecx, eax
        mov[ebp - 0x00000054], ecx
        jmp PhanDamgge

        XuyenDeffPvpLonHon :
            PhanDamgge :
        xor ecx, ecx
            mov eax, [ebp - 0xBC]
            mov cl, [eax + 0xD574]
            test ecx, ecx
            jz Default
            mov eax, [ebp + 0x8]
            xor edx, edx
            mov dl, [eax + 0xD578]
            cmp edx, ecx
            ja Default
            sub ecx, edx
            push ecx
            mov ecx, [ebp - 0x00000054]
            push ecx
            call TinhPhanPhanDmg
            add esp, 0x8
            push eax
            mov ecx, [ebp + 0x8]
            mov[ecx + 0xAC15], 0x1
            mov eax, 0x4B6B29
            call eax
            Default :
        mov eax, 0x00406AD0
            call eax
            push 0x004B9A5E
            ret
    }
}
void __declspec(naked)TinhToanDeffVaPhanDamNuker2()//004BBF70 8
{
    __asm
    {
        xor ecx, ecx
        xor eax, eax
        mov eax, [ebp - 0x74]
        mov cx, [eax + 0xD570]
        test ecx, ecx
        jz PhanDamgge
        xor edx, edx
        mov dx, [eax + 0xD570]
        mov eax, [ebp + 0x10]
        xor ecx, ecx
        mov cx, [eax + 0xD574]
        cmp ecx, edx
        ja XuyenDeffPvpLonHon
        sub edx, ecx
        mov ecx, [ebp - 0x00000058]
        sub ecx, edx
        mov[ebp - 0x00000058], ecx
        jmp PhanDamgge

        XuyenDeffPvpLonHon :
        sub ecx, edx
            mov edx, [ebp - 0x00000058]
            add edx, ecx
            mov[ebp - 0x00000058], edx

            PhanDamgge :
        xor ecx, ecx
            mov eax, [ebp - 0x74]
            mov cl, [eax + 0xD574]
            test ecx, ecx
            jz Default
            mov eax, [ebp + 0x10]
            xor edx, edx
            mov dl, [eax + 0xD578]
            cmp edx, ecx
            ja Default
            sub ecx, edx
            push ecx
            mov ecx, [ebp - 0x00000058]
            push ecx
            call TinhPhanPhanDmg
            add esp, 0x8
            push eax
            mov ecx, [ebp + 0x10]
            mov[ecx + 0xAC15], 0x1
            mov eax, 0x4B6B29
            call eax
            Default :
            cmp dword ptr[ebp - 0x58], 0x00
            jng n0004BC43D
            push 0x004BBF7A
            ret 
            n0004BC43D:
            push 0x004BC43D
            ret 
    }
}
void __declspec(naked)ChangeCodePercentHealthMob()//00592E50 5
{
    __asm
    {
        mov  ecx, [ebp - 0x4]
        push 0x64
        fild [esp]
        fimul dword ptr[ecx+0x118]
        fidiv dword ptr [ecx+0x268]
        mov eax,0x006E5A28
        call eax
        pop ecx
        push 0x00592E66
        ret
    }
}
void __declspec(naked)ChangeCodePercentHealthMob2()//00592E2F 5
{
    __asm
    {
        mov  ecx, [ebp - 0x4]
        push 0x64
        fild[esp]
        fimul dword ptr[ecx + 0x118]
        fidiv dword ptr[ecx + 0x268]
        mov eax, 0x006E5A28
        call eax
        pop ecx
        push 0x00592E45
        ret
    }
}
void __declspec(naked)PhongThuChiMang()//004B811A 5
{
    __asm
    {
        mov ecx,[ebp-0xA4]
		xor edx,edx
		mov dx,[ecx+0xCAA6]
        cmp eax,edx
        jbe AddZeroSTCM
        sub eax,edx
        add eax,0x96
        push 0x004B811F
        ret
        AddZeroSTCM:
        mov eax,0x00
        add eax, 0x96
        push 0x004B811F
        ret

    }
}
void __declspec(naked)PhongThuChiMang23()//004B8D47 5
{
    __asm
    {
        mov ecx, [ebp - 0xA8]
        xor edx, edx
        mov dx, [ecx + 0xCAA6]
        cmp eax, edx
        jbe AddZeroSTCM
        sub eax, edx
        add eax, 0x96
        push 0x004B8D4C
        ret
        AddZeroSTCM :
        mov eax, 0x00
            add eax, 0x96
            push 0x004B8D4C
            ret

    }
}
void __declspec(naked)PhongThuChiMang24()//004B8D69 5
{
    __asm
    {
        mov ecx, [ebp - 0xA8]
        xor edx, edx
        mov dx, [ecx + 0xCAA6]
        cmp eax, edx
        jbe AddZeroSTCM
        sub eax, edx
        add eax, 0x96
        push 0x004B8D6E
        ret
        AddZeroSTCM :
        mov eax, 0x00
            add eax, 0x96
            push 0x004B8D6E
            ret

    }
}
void __declspec(naked)PhongThuChiMang2()//004B813C 5
{
    __asm
    {
        mov ecx, [ebp - 0xA4]
		xor edx,edx
		mov dx,[ecx + 0xCAA6]
        cmp eax, edx
        jbe AddZeroSTCM
        sub eax, edx
        add eax, 0x96
        push 0x004B8141
        ret

        AddZeroSTCM :
        mov eax, 0x00
            add eax, 0x96
            push 0x004B8141
            ret
    }
}
void __declspec(naked)PhongThuChiMangKC()//004B98A3 5
{
    __asm
    {
        mov ecx, [ebp - 0xBC]
		xor eax,eax
		mov ax,[ecx + 0xCAA6]
        cmp edx,eax
        jbe AddZeroSTCM
        sub edx,eax
        add edx, 0x96
        push 0x004B98A9
        ret
        AddZeroSTCM :
        mov edx, 0x00
            add edx, 0x96
            push 0x004B98A9
            ret

    }
}
void __declspec(naked)PhongThuChiMang2KC()//004B98C9 5
{
    __asm
    {
        mov eax, [ebp - 0xBC]
		xor edx,edx
		mov dx,[eax + 0xCAA6]
        cmp ecx,edx 
        jbe AddZeroSTCM
        sub ecx, edx
        add ecx, 0x96
        push 0x004B98CF
        ret

        AddZeroSTCM :
        mov ecx, 0x00
            add ecx, 0x96
            push 0x004B98CF
            ret
    }
}
DWORD BossId = 0;
void __declspec(naked)GetEventIngame()//004134B7 5
{
    __asm
    {
       mov edx, 0x007711F2
       movsx edx, [edx]
       cmp edx, 0xF
       jnz OutCheck
       lea  eax, [ebp - 0x98]
       xor ecx,ecx
       mov cl,[eax+0x15]
       cmp ecx,0x40
       jnz CheckMessage2
       push 0x64
       mov eax, 0x006A06F0
       call eax
       add esp, 0x4
       cmp eax,0x19
       ja GetBossMini2
       mov BossId, 0x1D0E
       jmp EndGetIDBossMini
       GetBossMini2:
       cmp eax, 0x32
       ja GetBossMini23
       mov BossId, 0x1D0F
       jmp EndGetIDBossMini
       GetBossMini23 :
       cmp eax, 0x4B
       ja GetBossMini24
       mov BossId, 0x1D10
       jmp EndGetIDBossMini
       GetBossMini24 :
       mov BossId, 0x1D11
       EndGetIDBossMini:
       push 0x64
       mov eax, 0x006A06F0
       call eax
       add esp, 0x4
       ShowBossFromNewMap:
       cmp eax,0x19
       ja CheckToaDo1
       //
       lea eax, ListToaDoBossMini
       mov ecx,[eax]
       lea edx, toadoBoss
       mov [edx],ecx
       mov ecx, [eax+0x4]
       mov[edx+0x4], ecx
       mov eax, BossId
       call CallBoss
       jmp OutCheck
       //
       CheckToaDo1:
       cmp eax, 0x32
       ja CheckToaDo12
           //
           lea eax, ListToaDoBossMini
           mov ecx, [eax+0x8]
           lea edx, toadoBoss
           mov[edx], ecx
           mov ecx, [eax + 0xC]
           mov[edx + 0x4], ecx
           mov eax, BossId
           call CallBoss
           jmp OutCheck
           //
           CheckToaDo12 :
       cmp eax, 0x4B
           ja CheckToaDo13
           //
           lea eax, ListToaDoBossMini
           mov ecx, [eax+0x10]
           lea edx, toadoBoss
           mov[edx], ecx
           mov ecx, [eax + 0x14]
           mov[edx + 0x4], ecx
           mov eax, BossId
           call CallBoss
           jmp OutCheck
           //

           CheckToaDo13 :
           //
           lea eax, ListToaDoBossMini
           mov ecx, [eax+0x18]
           lea edx, toadoBoss
           mov[edx], ecx
           mov ecx, [eax + 0x1C]
           mov[edx + 0x4], ecx
           mov eax, BossId
           call CallBoss
           jmp OutCheck
           //

       CheckMessage2:
       cmp ecx, 0x3F
       jnz CheckMessage3
           mov BossId, 0x1D12
           lea eax, ListToaDoBoss
           mov ecx, [eax ]
           lea edx, toadoBoss
           mov[edx], ecx
           mov ecx, [eax + 0x4]
           mov[edx + 0x4], ecx
           mov eax, BossId
           call CallBoss
           jmp OutCheck
       CheckMessage3 :
       cmp ecx, 0x3E
       jnz OutCheck
       push 0x0
       mov eax,0x6B3115
       call eax
       add esp,0x4

       OutCheck:
       mov dx, [ebp - 0x00000098]
       push 0x004134BE
       ret

           CallBoss:
           push 0x0
           push 0x0
           push 0x0
           lea edx, toadoBoss
           push edx
           push 0x0
           push eax
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
           ret

    }
}
//Nuker
void __declspec(naked)GetDmgFromBoss()//00587E44 5
{
    __asm
    {
        mov ecx, [ebp - 0xA4]
        xor edx,edx
        mov dx,[ecx+0x14]
        cmp edx, 0x1D12
        jz AddDmgBossUser
        cmp edx, 0x1CF6
        jz AddDmgBossUser
        cmp edx, 0x1410
        jz AddDmgBossUser
        /*cmp edx, 0x19DF
        jz AddDmgBossUser
        cmp edx, 0x19E0
        jz AddDmgBossUser
        cmp edx, 0x19E1
        jz AddDmgBossUser
        cmp edx, 0x19E2
        jz AddDmgBossUser
        cmp edx, 0x19E3
        jz AddDmgBossUser
        cmp edx, 0x19E4
        jz AddDmgBossUser
        cmp edx, 0x19E5
        jz AddDmgBossUser
        cmp edx, 0x19E6
        jz AddDmgBossUser
        cmp edx, 0x19E7
        jz AddDmgBossUser
        cmp edx, 0x19E8
        jz AddDmgBossUser
        cmp edx, 0x19E9
        jz AddDmgBossUser*/
        cmp edx, 0x19EA
        jz TinhDiemBossCLS
        cmp edx, 0x19EB
        jz TinhDiemBossCLS
        cmp edx, 0x19EC
        jz TinhDiemBossCLS
        cmp edx, 0x19ED
        jz TinhDiemBossCLS
        jmp Default1
        AddDmgBossUser:
        mov ecx,[ebp+0x8]
        test ecx,ecx
        jz Default1
        mov edx,[ecx+0xCAA8]
        mov eax, [ebp - 0x24]
        add edx,eax
        mov [ecx+0xCAA8],edx
        xor edx,edx
        jmp Default1

        TinhDiemBossCLS:
        mov ecx, [ebp + 0x8]
        test ecx, ecx
        jz Default1
        mov edx, [ecx + 0xD621]
        mov eax, [ebp - 0x24]
        add edx, eax
        mov[ecx + 0xD621], edx
        xor edx, edx
        jmp Default1

        Default1 :
        movsx ecx, byte ptr[ebp - 0x68]
        mov eax, [ebp - 0x24]
        push 0x00587E4B
        ret
    }
}
void __declspec(naked)GetDmgSkillFromBoss()//00588E22 6
{
    __asm
    {

        mov ecx, [ebp - 0x90]
        xor edx, edx
        mov dx, [ecx + 0x14]
        cmp edx, 0x1CE6
        jz AddDmgBossUser
        /*cmp edx, 0x1CF6
        jz AddDmgBossUser
        cmp edx, 0x1410
        jz AddDmgBossUser
        cmp edx, 0x19DF
        jz AddDmgBossUser
        cmp edx, 0x19E0
        jz AddDmgBossUser
        cmp edx, 0x19E1
        jz AddDmgBossUser
        cmp edx, 0x19E2
        jz AddDmgBossUser
        cmp edx, 0x19E3
        jz AddDmgBossUser
        cmp edx, 0x19E4
        jz AddDmgBossUser
        cmp edx, 0x19E5
        jz AddDmgBossUser
        cmp edx, 0x19E6
        jz AddDmgBossUser
        cmp edx, 0x19E7
        jz AddDmgBossUser
        cmp edx, 0x19E8
        jz AddDmgBossUser
        cmp edx, 0x19E9
        jz AddDmgBossUser
        cmp edx, 0x19EA
        jz TinhDiemBossCLS
        cmp edx, 0x19EB
        jz TinhDiemBossCLS
        cmp edx, 0x19EC
        jz TinhDiemBossCLS
        cmp edx, 0x19ED
        jz TinhDiemBossCLS*/
        jmp Default3
        AddDmgBossUser:
        mov ecx, [ebp + 0x8]
        test ecx,ecx
        jz Default3
        mov edx, [ecx + 0xCAA8]
        mov eax, [ebp - 0x38]
        add edx, eax
        mov [ecx + 0xCAA8], edx
        xor edx, edx
        jmp Default3

        TinhDiemBossCLS :
        mov ecx, [ebp + 0x8]
        test ecx, ecx
        jz Default3
        mov edx, [ecx + 0xD621]
        mov eax, [ebp - 0x38]
        add edx, eax
        mov[ecx + 0xD621], edx
        xor edx, edx
        jmp Default3

        Default3 :
        mov ecx, [ebp - 0x00000090]
        push 0x00588E28
        ret
    }
}
void __declspec(naked)GetDmgSkillNukerFromBoss()//00589A84 6
{
    __asm
    {

        mov ecx, [ebp - 0x98]
        xor edx, edx
        mov dx, [ecx + 0x14]
        cmp edx, 0x1CE6
        jz AddDmgBossUser
        /*cmp edx, 0x1CF6
        jz AddDmgBossUser
        cmp edx, 0x1410
        jz AddDmgBossUser
        cmp edx, 0x19DF
        jz AddDmgBossUser
        cmp edx, 0x19E0
        jz AddDmgBossUser
        cmp edx, 0x19E1
        jz AddDmgBossUser
        cmp edx, 0x19E2
        jz AddDmgBossUser
        cmp edx, 0x19E3
        jz AddDmgBossUser
        cmp edx, 0x19E4
        jz AddDmgBossUser
        cmp edx, 0x19E5
        jz AddDmgBossUser
        cmp edx, 0x19E6
        jz AddDmgBossUser
        cmp edx, 0x19E7
        jz AddDmgBossUser
        cmp edx, 0x19E8
        jz AddDmgBossUser
        cmp edx, 0x19E9
        jz AddDmgBossUser
        cmp edx, 0x19EA
        jz TinhDiemBossCLS
        cmp edx, 0x19EB
        jz TinhDiemBossCLS
        cmp edx, 0x19EC
        jz TinhDiemBossCLS
        cmp edx, 0x19ED
        jz TinhDiemBossCLS*/
        jmp Default4
        AddDmgBossUser:
        mov ecx, [ebp + 0x8]
        test ecx, ecx
        jz Default4
        mov edx, [ecx + 0xCAA8]
        mov eax, [ebp - 0x40]
        add edx, eax
        mov[ecx + 0xCAA8], edx
        xor edx, edx
        jmp Default4


        TinhDiemBossCLS :
        mov ecx, [ebp + 0x8]
        test ecx, ecx
        jz Default4
        mov edx, [ecx + 0xD621]
        mov eax, [ebp - 0x40]
        add edx, eax
        mov[ecx + 0xD621], edx
        xor edx, edx
        jmp Default4
        
        Default4 :
        mov ecx, [ebp - 0x98]
        push 0x00589A8A
        ret
    }
}
DWORD ListTopDmg[11];
DWORD tempTop;
DWORD tempTop2;
DWORD storeECX;
char ListDetail[81];
int QuaTuBoss[15][3] =
{
    {7,1925,1},
    {7,1548,1},
    {7,1548,1},
    {7,1548,1},
    {7,1614,1},
    {7,3556,1},
    {7,1612,1},
    {7,1612,1},
    {7,1613,1},
    {7,1613,1},
    {7,1548,1},
    {7,3556,1},
    {7,3556,1},
    {7,1613,1},
    {7,1613,1}
};
void __declspec(naked)GetEventKillMob()//00586EFC 6
{
    __asm
    {
        mov ecx,[ebp - 0x28]
        xor eax,eax
        mov ax,[ecx+0x14]
        cmp eax, 0x1CE6
        jnz Default
        //AddQuaTop:
        push 0x0
        push 0x1FB5
        mov ecx, 0x007763AC
        mov ecx,[ecx]
        mov eax,0x606F5B
        call eax
        jmp Default

        CheckEvent2:
        mov ecx, [ebp - 0x28]
        xor eax, eax
        mov ax, [ecx + 0x14]
        cmp eax, 0x1CF6
        jnz CheckEvent3
        push 0x0
        push 0x1FB6
        mov ecx, 0x007763AC
        mov ecx, [ecx]
        mov eax, 0x606F5B
        call eax
        jmp Default
        CheckEvent3 :
        mov ecx, [ebp - 0x28]
            xor eax, eax
            mov ax, [ecx + 0x14]
            cmp eax, 0x1410
#ifdef EventHSB
            jnz CheckEvent4
#endif
            jnz Default
            push 0x0
            push 0x1FB7
            mov ecx, 0x007763AC
            mov ecx, [ecx]
            mov eax, 0x606F5B
            call eax
            jmp Default
            //Event Moi
#ifdef EventHSB
            CheckEvent4 :
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0xE
            jnz SuKienTongKim
            mov ecx, [ebp - 0x28]
            xor eax, eax
            mov ax, [ecx + 0x14]
            cmp eax, 0x19DF
            jb Default
            cmp eax, 0x19ED
            ja Default
            push eax
            call SpawnModBossSuKien
            add esp, 0x4
#endif // EventHSB
        
#ifdef TestTK
            SuKienTongKim:
            mov edx, 0x007711F2
                movsx edx, [edx]
                cmp edx, 0xB
                jnz Default
                mov ecx, [ebp - 0x28]
                xor eax, eax
                mov ax, [ecx + 0x14]
                cmp eax, 0x1A2F
                jz AddDiemChoNam
                cmp eax, 0x1A30
                jz AddDiemChoNam
                cmp eax, 0x1A31
                jz AddDiemChoNam
                cmp eax, 0x1A32
                jz AddDiemChoHan
                cmp eax, 0x1A33
                jz AddDiemChoHan
                cmp eax, 0x1A34
                jz AddDiemChoHan
                jmp Default
                AddDiemChoNam:
            cmp eax, 0x1A2F
                jnz KiemTraRankBoss21
                mov  ecx, [ebp + 0x8]
                xor edx, edx
                mov edx, [ecx + 0xD626]
                add edx, 0x190
                mov[ecx + 0xD626], edx
                lea ecx, nDiemTong
                mov edx, [ecx]
                add edx, 0x190
                mov[ecx], edx
                jmp AddDiemChoToanBoUser1
                KiemTraRankBoss21 :
            cmp eax, 0x1A30
                jnz KiemTraRankBoss22
                mov  ecx, [ebp + 0x8]
                xor edx, edx
                mov edx, [ecx + 0xD626]
                add edx, 0x320
                mov[ecx + 0xD626], edx
                lea ecx, nDiemTong
                mov edx, [ecx]
                add edx, 0x320
                mov[ecx], edx
                jmp AddDiemChoToanBoUser1

                KiemTraRankBoss22 :
            cmp eax, 0x1A31
                jnz Default
                mov  ecx, [ebp + 0x8]
                xor edx, edx
                mov edx, [ecx + 0xD626]
                add edx, 0x640
                mov[ecx + 0xD626], edx
                lea ecx, nDiemTong
                mov edx, [ecx]
                add edx, 0x640
                mov[ecx], edx
                AddDiemChoToanBoUser1 :
                push 0x0
                push eax
                mov ecx, 0x007763AC
                mov ecx, [ecx]
                mov eax, 0x606F5B
                call eax
                call SendDiemTongKim
                jmp Default

                AddDiemChoHan:
                cmp eax, 0x1A32
                jnz KiemTraRankBoss
                mov  ecx, [ebp + 0x8]
                xor edx, edx
                mov edx, [ecx + 0xD626]
                add edx, 0x190
                mov [ecx+0xD626],edx
                lea ecx,nDiemKim
                mov edx,[ecx]
                add edx,0x190
                mov [ecx],edx
                jmp AddDiemChoToanBoUser
                KiemTraRankBoss:
                cmp eax, 0x1A33
                jnz KiemTraRankBoss2
                mov  ecx, [ebp + 0x8]
                xor edx, edx
                mov edx, [ecx + 0xD626]
                add edx, 0x320
                mov[ecx + 0xD626], edx
                lea ecx, nDiemKim
                mov edx, [ecx]
                add edx, 0x320
                mov[ecx], edx
                jmp AddDiemChoToanBoUser

                KiemTraRankBoss2:
                cmp eax, 0x1A34
                jnz Default
                mov  ecx, [ebp + 0x8]
                xor edx,edx
                mov edx,[ecx+0xD626]
                add edx, 0x640
                mov[ecx + 0xD626], edx
                lea ecx, nDiemKim
                mov edx, [ecx]
                add edx, 0x640
                mov[ecx], edx
                AddDiemChoToanBoUser:
                push 0x0
                push eax
                mov ecx, 0x007763AC
                mov ecx, [ecx]
                mov eax, 0x606F5B
                call eax
                call SendDiemTongKim
                jmp Default
#endif // TestTK

        Default:
        xor eax,eax
        mov al, 0x1
        mov ecx, [ebp - 0x10]
        push 0x00586F01
        ret
    }
}
bool ProcessAddQua(int ThangThua, unsigned int GiaTri, unsigned int nHuyetTinh)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    unsigned int GiaMil;
    unsigned int HuyetTinh;
    GiaMil = GiaTri;
    HuyetTinh = nHuyetTinh;
    if (ThangThua == 0)
    {
        __asm
        {
            mov eax, GiaMil
            push eax
            mov ecx, StoreECX
            call AddMoneyForEvent
            add esp, 0x4
        }
    }
    else if(ThangThua == 1)
    {
        __asm
        {
            mov eax, GiaMil
            push eax
            mov ecx, StoreECX
            call AddMoneyForEvent
            add esp, 0x4
            //Add HT
            mov eax, HuyetTinh
            push eax
            push 0x13
            push 0x2
            push 0xA
            mov ecx, StoreECX
            call AddItemLoadChien
            add esp, 0x10
        }
    }
    
}
bool AddQuaTongKim(int typeUser)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int TypePhe;
    TypePhe = typeUser;
    if(TypePhe == 1)
    {
        if (nDiemTong > nDiemKim)
        {
            //Thang
            __asm
            {
                mov ecx, StoreECX
                xor eax,eax
                mov eax, [ecx + 0xD626]
                cmp eax, 0x1F4
                jae HieuUy
                push 0x19
                push 0x1312D00
                push 0x1
                mov ecx, StoreECX
                call ProcessAddQua
                add esp,0xC
                jmp EndProcessAdd
                //Add Qua Tuong
                HieuUy :
                cmp eax, 0x7D0
                jae ThongLinh
                push 0x64
                push 0x5F5E100
                push 0x1
                mov ecx, StoreECX
                call ProcessAddQua
                add esp, 0xC
                jmp EndProcessAdd
                //Add Qua Tuong
                ThongLinh :
                cmp eax, 0xFA0
                jae PhoTuong
                push 0x96
                push 0xBEBC200
                push 0x1
                mov ecx, StoreECX
                call ProcessAddQua
                add esp, 0xC
                jmp EndProcessAdd
                //Add Qua Tuong
                PhoTuong :
                cmp eax, 0x1770
                jae DaiTuong
                push 0xC8
                push 0x11E1A300
                push 0x1
                mov ecx, StoreECX
                call ProcessAddQua
                add esp, 0xC
                jmp EndProcessAdd
                //Add Qua Tuong
                DaiTuong :
                push 0xFA
                push 0x1AD27480
                push 0x1
                mov ecx, StoreECX
                call ProcessAddQua
                add esp, 0xC
                EndProcessAdd:
            }
        }
        else
        {
            //Thua
            __asm
            {
                mov ecx, StoreECX
                xor eax, eax
                mov eax, [ecx + 0xD626]
                cmp eax, 0x1F4
                jae HieuUy1
                push 0x19
                push 0x989680
                push 0x0
                mov ecx, StoreECX
                call ProcessAddQua
                add esp, 0xC
                jmp EndProcessAdd1
                //Add Qua Tuong
                HieuUy1 :
                cmp eax, 0x7D0
                    jae ThongLinh1
                    push 0x64
                    push 0x2FAF080
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp EndProcessAdd1
                    //Add Qua Tuong
                    ThongLinh1 :
                cmp eax, 0xFA0
                    jae PhoTuong1
                    push 0x96
                    push 0x5F5E100
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp EndProcessAdd1
                    //Add Qua Tuong
                    PhoTuong1 :
                cmp eax, 0x1770
                    jae DaiTuong1
                    push 0xC8
                    push 0xBEBC200
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp EndProcessAdd1
                    //Add Qua Tuong
                    DaiTuong1 :
                push 0xFA
                    push 0x11E1A300
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    EndProcessAdd1:
            }

        }
    }
    else if (TypePhe == 2)
    {
        if (nDiemKim > nDiemTong)
        {
            //Thang
            __asm
            {
                mov ecx, StoreECX
                xor eax, eax
                mov eax, [ecx + 0xD626]
                cmp eax, 0x1F4
                jae KimHieuUy
                push 0x19
                push 0x1312D00
                push 0x1
                mov ecx, StoreECX
                call ProcessAddQua
                add esp, 0xC
                jmp KimEndProcessAdd
                //Add Qua Tuong
                KimHieuUy :
                cmp eax, 0x7D0
                    jae KimThongLinh
                    push 0x64
                    push 0x5F5E100
                    push 0x1
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp KimEndProcessAdd
                    //Add Qua Tuong
                    KimThongLinh :
                cmp eax, 0xFA0
                    jae KimPhoTuong
                    push 0x96
                    push 0xBEBC200
                    push 0x1
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp KimEndProcessAdd
                    //Add Qua Tuong
                    KimPhoTuong :
                cmp eax, 0x1770
                    jae KimDaiTuong
                    push 0xC8
                    push 0x11E1A300
                    push 0x1
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp KimEndProcessAdd
                    //Add Qua Tuong
                    KimDaiTuong :
                push 0xFA
                    push 0x1AD27480
                    push 0x1
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    KimEndProcessAdd:
            }
        }
        else
        {
            //Thua
            __asm
            {
                mov ecx, StoreECX
                xor eax, eax
                mov eax, [ecx + 0xD626]
                cmp eax, 0x1F4
                jae KimHieuUy1
                push 0x19
                push 0x989680
                push 0x0
                mov ecx, StoreECX
                call ProcessAddQua
                add esp, 0xC
                jmp KimEndProcessAdd1
                //Add Qua Tuong
                KimHieuUy1 :
                cmp eax, 0x7D0
                    jae KimThongLinh1
                    push 0x64
                    push 0x2FAF080
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp KimEndProcessAdd1
                    //Add Qua Tuong
                    KimThongLinh1 :
                cmp eax, 0xFA0
                    jae KimPhoTuong1
                    push 0x96
                    push 0x5F5E100
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp KimEndProcessAdd1
                    //Add Qua Tuong
                    KimPhoTuong1 :
                cmp eax, 0x1770
                    jae KimDaiTuong1
                    push 0xC8
                    push 0xBEBC200
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    jmp KimEndProcessAdd1
                    //Add Qua Tuong
                    KimDaiTuong1 :
                    push 0xFA
                    push 0x11E1A300
                    push 0x0
                    mov ecx, StoreECX
                    call ProcessAddQua
                    add esp, 0xC
                    KimEndProcessAdd1:
            }

        }
    }
    
    

}
void __declspec(naked)AddEventKillMob()//00606FFE 6
{
    __asm
    {
        xor edx,edx
        mov dx, [ebp + 0x8]
        cmp edx,0x1FB5
        jnz Default
        mov ecx, [ebp - 0x24]
        xor eax,eax
        mov eax,[ecx+0xCAA8]
        test eax,eax
        jz NotHaveDamge
        //add money
        mov ecx, [ebp - 0x24]
        xor eax, eax
        mov eax, [ecx + 0xCAA8]
        push eax
        mov ecx, [ebp - 0x24]
        call AddMoneyForEvent
        add esp,0x4
        //add exp
        mov ecx, [ebp - 0x24]
        xor eax, eax
        mov eax, [ecx + 0xCAA8]
        push eax
        mov ecx, [ebp - 0x24]
        call AddJinUser
        add esp, 0x4
        jmp NotHaveDamge
        Default:
        push 0x2164
        push 0x00607003
        ret

        NotHaveDamge:
        mov ecx, [ebp - 0x24]
        mov dword ptr [ecx + 0xCAA8],0x0000
        push 0x00607033
        ret
            /*
            Event2:
            //Event Tong Kim
            cmp edx, 0x2FFF
            jnz AddDiemChoNam
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0xB
            jnz Default
            mov ecx, [ebp - 0x24]
            xor eax,eax
            mov al,[ecx+0xD625]
            push eax
            mov ecx, [ebp - 0x24]
            call AddQuaTongKim
            add esp,0x4
            mov ecx, [ebp - 0x24]
            mov byte ptr[ecx + 0xD625], 0x0
            mov dword ptr[ecx + 0xD626], 0x0
            mov dword ptr[ecx + 0xD62A], 0x0
            mov dword ptr[ecx + 0xD62E], 0x0
            mov dword ptr[ecx + 0xD632], 0x0
            jmp NotHaveDamge

            AddDiemChoNam:
                cmp edx, 0x1A2F
                jz BatDauAddDiem
                cmp edx, 0x1A30
                jz BatDauAddDiem
                cmp edx, 0x1A31
                jz BatDauAddDiem
                jmp AddDiemChoHan
                BatDauAddDiem:
                cmp edx, 0x1A2F
                jnz KiemTraBossLoai2
                mov eax,0x64
                jmp DaCoGiaTriAdd
                KiemTraBossLoai2:
                cmp edx, 0x1A30
                jnz KiemTraBossLoai3
                mov eax, 0xC8
                jmp DaCoGiaTriAdd
                KiemTraBossLoai3:
                cmp edx, 0x1A31
                jnz KhongTimThayBoss
                mov eax, 0x190
                jmp DaCoGiaTriAdd
                KhongTimThayBoss:
                mov eax, 0x1
                DaCoGiaTriAdd:
                mov ecx, [ebp - 0x24]
                xor edx,edx
                mov dl, [ecx + 0xD625]
                cmp edx,0x2
                jnz NotHaveDamge
                xor edx, edx
                mov edx, [ecx + 0xD626]
                add edx,eax
                mov ecx, [ebp - 0x24]
                mov [ecx + 0xD626],edx
                lea ecx, nDiemKim
                mov edx, [ecx]
                add edx, eax
                mov[ecx], edx
                mov ecx, [ebp - 0x24]
                call SendDiemTongKimUser
                jmp NotHaveDamge

            AddDiemChoHan:
                cmp edx, 0x1A32
                    jz BatDauAddDiemHan
                    cmp edx, 0x1A33
                    jz BatDauAddDiemHan
                    cmp edx, 0x1A34
                    jz BatDauAddDiemHan
                    jmp CheckEvent3
                BatDauAddDiemHan:
                cmp edx, 0x1A32
                    jnz KiemTraBossLoai21
                    mov eax, 0x64
                    jmp DaCoGiaTriAdd
                    KiemTraBossLoai21:
                    cmp edx, 0x1A33
                    jnz KiemTraBossLoai31
                    mov eax, 0xC8
                    jmp DaCoGiaTriAdd
                    KiemTraBossLoai31 :
                    cmp edx, 0x1A34
                    jnz KhongTimThayBoss1
                    mov eax, 0x190
                    jmp DaCoGiaTriAdd1
                    KhongTimThayBoss1 :
                    mov eax, 0x1
                    DaCoGiaTriAdd1 :
                    mov ecx, [ebp - 0x24]
                    xor edx, edx
                    mov dl, [ecx + 0xD625]
                    cmp edx, 0x1
                    jnz NotHaveDamge
                    xor edx, edx
                    mov edx, [ecx + 0xD626]
                    add edx, eax
                    mov ecx, [ebp - 0x24]
                    mov[ecx + 0xD626], edx
                    lea ecx, nDiemTong
                    mov edx, [ecx]
                    add edx, eax
                    mov[ecx], edx
                    mov ecx, [ebp - 0x24]
                    call SendDiemTongKimUser

            //Add Jin
            CheckEvent3:
            cmp edx, 0x1FB6
            jnz CheckEvent4
            mov ecx, [ebp - 0x24]
            xor eax, eax
            mov eax, [ecx + 0xCAA8]
            test eax, eax
            jz NotHaveDamgeEvent3
                //add money
                push eax
                mov ecx, [ebp - 0x24]
                call AddMoneyForEvent
                add esp, 0x4
                //add exp
                mov ecx, [ebp - 0x24]
                xor eax, eax
                mov eax, [ecx + 0xCAA8]
                push eax
                call AddJinUser
                add esp, 0x4
                NotHaveDamgeEvent3:
                jmp NotHaveDamge

                    CheckEvent4 :
                    cmp edx, 0x1FB7
                    jnz Default
                    mov ecx, [ebp - 0x24]
                    xor eax, eax
                    mov eax, [ecx + 0xCAA8]
                    test eax, eax
                    jz NotHaveDamgeEvent4
                    //add money
                        push 0x1
                        push 0xF62
                        push 0x1E
                        push 0x3
                        mov ecx, [ebp - 0x24]
                        call AddItemLoadChien
                        add esp, 0x10
                    //add exp
                    mov ecx, [ebp - 0x24]
                    xor eax, eax
                    mov eax, [ecx + 0xCAA8]
                    imul eax,0x2
                    push eax
                    call AddJinUser
                    add esp, 0x4
                    NotHaveDamgeEvent4:
                jmp NotHaveDamge*/

    }
}
void __declspec(naked)LoadValueFromNewSlot()//0050E5D1 6
{
    __asm
    {
        mov ecx, [ebp + 0xC]
        mov byte ptr[ecx + 0x5], 0xFF
        xor eax,eax
        mov al, [ebp - 0x4]
        cmp eax,0x8C
        jb CheckPutOut
        cmp eax,0x93
        ja Default
        mov eax,0x00
        xor edx,edx
        mov dl, [ebp - 0x4]
        jmp ProcessAddValueNewitem
        CheckPutOut:
        xor eax, eax
        mov al, [ebp - 0x8]
        cmp eax,0x8C
        jb Default
        cmp eax, 0x93
        ja Default
        mov eax, 0x01
        xor edx, edx
        mov dl, [ebp - 0x8]
        ProcessAddValueNewitem:
        push eax
        push edx
        mov ecx, [ebp - 0x4C]
        mov eax, 0x00512942
        call eax


            Default:

        push 0x0050E5D8
        ret
    }
}
void __declspec(naked)BypassCheckiD()//004CBADF 6
{
    __asm
    {
        xor edx,edx
        mov dl, [ebp + 0x8]
        cmp edx,0x8C
        jb Default
        cmp edx,0x93
        ja Default
        xor eax, eax
        mov al, [ebp + 0x8]
        push 0x004CBAFC
        ret
        Default:
        xor edx, edx
        mov dl, [ebp + 0x8]
        push edx
        mov ecx, [ebp - 0x30]
        push 0x004CBAE6
        ret
    }
}
void __declspec(naked)XoaSlotMoi()//004CC3CA 6
{
    __asm
    {
       add esp, 0xC
       mov byte ptr[ebp - 0x4], 0x0
       push 0x94C
       push 0x0
       mov eax, [ebp - 0x8]
       add eax, 0x0000CAB4
       push eax
       mov eax,0x006E3B70
       call eax
       add esp,0xC
       push 0x004CC3D1
       ret
    }
}
void __declspec(naked)UnknowFun()//00616F8F 6
{
    __asm
    {
        push 0x00617CD0
        push 0x7
        push 00000154
        mov edx, [ebp - 0x1C]
        add edx, 0x0000CAB4
        push edx
        mov eax,0x00401160
        call eax
        mov ecx, [ebp - 0x1C]
        add ecx, 0x00009A98
        push 0x00616F98
        ret
    }
}
void __declspec(naked)GetAddressNewSlot()//004CBAA3 6
{
    __asm
    {
        cmp edx,0x8C
        jb Default
        sub edx,0x8C
        imul edx, edx, 0x00000154
        mov eax, [ebp - 0x30]
        lea ecx, [eax + edx + 0x0000CAB4]
        mov [ebp - 0x4], ecx
        push 0x004CBAB6
        ret
        Default:
        imul edx, edx, 0x00000154
        push 0x004CBAA9
        ret
    }
}
void __declspec(naked)GetAddressNewSlot2()//004D1601 6
{
    __asm
    {
        cmp edx,0x8C
        jb Default
        sub edx, 0x8C
        imul edx, edx, 0x00000154
        mov eax, [ebp - 0x20]
        lea ecx, [eax + edx + 0x0000CAB4]
        push 0x004D1611
        ret
        Default:
        imul edx, edx, 0x00000154
        push 0x004D1607
        ret
    }
}
void __declspec(naked)CheckADdressNewSlot()//00507972 6
{
    __asm
    {
        xor edx,edx
        mov dl, byte ptr[ebp - 0x4]
        cmp edx,0x8C
        jb Default
        sub edx,0x8C
        imul edx, edx, 0x00000154
        mov eax, [ebp - 0x34]
        lea ecx, [eax + edx + 0x0000CAB4]
        push 0x00507986
        ret
        Default:
        imul edx, edx, 0x00000154
        push 0x0050797C
        ret
    }
}
void __declspec(naked)CheckADdressNewSlot2()//00507C57 6
{
    __asm
    {
        xor edx, edx
        mov dl, byte ptr[ebp - 0x4]
        cmp edx, 0x8C
        jb Default
        sub edx, 0x8C
        imul edx, edx, 0x00000154
        mov eax, [ebp - 0x34]
        lea ecx, [eax + edx + 0x0000CAB4]
        push 0x00507C6B
        ret
        Default:
        imul edx, edx, 0x00000154
        push 0x00507C61
        ret
    }
}
void __declspec(naked)CheckADdressNewSlot3()//00507C57 6
{
    __asm
    {
        xor eax, eax
        mov al, byte ptr[ebp - 0x4]
        cmp eax, 0x8C
        jb Default
        sub eax, 0x8C
        imul eax, eax, 0x00000154
        mov ecx, [ebp - 0x34]
        lea ecx, [ecx + eax + 0x0000CAB4]
        push 0x0050786E
        ret
        Default:
        imul eax, eax, 0x00000154
        push 0x00507864
        ret
    }
}
void __declspec(naked)CheckADdressNewSlot4()//00507AA5 6
{
    __asm
    {
        xor eax, eax
        mov al, byte ptr[ebp - 0x4]
        cmp eax, 0x8C
        jb Default
        sub eax, 0x8C
        imul eax, eax, 0x00000154
        mov ecx, [ebp - 0x34]
        lea ecx, [ecx + eax + 0x0000CAB4]
        push 0x00507AB9
        ret
        Default:
        imul eax, eax, 0x00000154
            push 0x00507AAF
            ret
    }
};
void __declspec(naked)CheckADdressNewSlot5()//0050755A 6
{
    __asm
    {
        xor ecx, ecx
        mov cl, byte ptr[ebp - 0x4]
        cmp ecx, 0x8C
        jb Default
        sub ecx, 0x8C
        imul ecx, ecx, 0x00000154
        mov edx, [ebp - 0x34]
        lea ecx, [edx + ecx + 0x0000CAB4]
        push 0x0050756E
        ret
        Default:
        imul ecx, ecx, 0x00000154
            push 0x00507564
            ret
    }
};
void __declspec(naked)CheckADdressNewSlot6()//005076AA 6
{
    __asm
    {
        xor ecx, ecx
        mov cl, byte ptr[ebp - 0x4]
        cmp ecx, 0x8C
        jb Default
        sub ecx, 0x8C
        imul ecx, ecx, 0x00000154
        mov edx, [ebp - 0x34]
        lea ecx, [edx + ecx + 0x0000CAB4]
        push 0x005076BE
        ret
        Default:
        imul ecx, ecx, 0x00000154
            push 0x005076B4
            ret
    }
};
void __declspec(naked)CheckADdressNewSlot7()//00507D6D 6
{
    __asm
    {
        xor ecx, ecx
        mov cl, byte ptr[ebp - 0x4]
        cmp ecx, 0x8C
        jb Default
        sub ecx, 0x8C
        imul ecx, ecx, 0x00000154
        mov edx, [ebp - 0x34]
        lea ecx, [edx + ecx + 0x0000CAB4]
        push 0x00507D81
        ret
        Default:
        imul ecx, ecx, 0x00000154
            push 0x00507D77
            ret
    }
};
void __declspec(naked)AddNewValueFromNick()//004E1606 6
{
    __asm
    {
        mov edx, [ebp - 0x20]
        xor eax, eax
        mov byte ptr [edx + 0xD557],0x00
        mov byte ptr [edx + 0xD555],0x00
        cmp dword ptr[ebp - 0x1C], 0x00
        jz NotHaveNick
        mov eax,[ebp-0x1C]
        xor ecx,ecx
        mov cx,[eax+0xC0]
        cmp ecx,0x14
        jnz CheckTypeHieuUng
        xor ecx,ecx
        mov cx, [eax + 0xC4]
        mov edx, [ebp - 0x20]
        mov byte ptr[edx + 0xD555],cl
        jmp CoDanhHiue
        CheckTypeHieuUng:
        cmp ecx, 0x2D2
        jnz CoDanhHiue
        xor ecx, ecx
        mov cx, [eax + 0xC4]
        mov edx, [ebp - 0x20]
        mov byte ptr[edx + 0xD557], cl
        CoDanhHiue :
        mov edx, [ebp - 0x20]
            xor eax, eax
            mov al, [edx + 0xD557]
            xor ecx, ecx
            mov cl, [edx + 0xD558]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu100HU1
            mov[edx + 0xCAA5], 0x64
            jmp XogTocHieuUng1
            ChuaDu100HU1 :
        mov[edx + 0xCAA5], al
            XogTocHieuUng1 :
        mov edx, [ebp - 0x20]
            xor eax, eax
            mov al, [edx + 0xD555]
            xor ecx, ecx
            mov cl, [edx + 0xD556]
            add eax, ecx
            xor ecx, ecx
            mov cl, [edx + 0xD590]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu1001
            mov[edx + 0xCAA4], 0x64
            jmp XogTocDoDanh1
            ChuaDu1001 :
        mov[edx + 0xCAA4], al
            XogTocDoDanh1 :
        push 0x004E1610
        ret



        NotHaveNick:
        mov edx, [ebp - 0x20]
            xor eax, eax
            mov al, [edx + 0xD557]
            xor ecx, ecx
            mov cl, [edx + 0xD558]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu100HU2
            mov[edx + 0xCAA5], 0x64
            jmp XogTocHieuUng2
            ChuaDu100HU2 :
        mov[edx + 0xCAA5], al
            XogTocHieuUng2 :
        mov edx, [ebp - 0x20]
            xor eax, eax
            mov al, [edx + 0xD555]
            xor ecx, ecx
            mov cl, [edx + 0xD556]
            add eax, ecx
            xor ecx, ecx
            mov cl, [edx + 0xD590]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu1002
            mov[edx + 0xCAA4], 0x64
            jmp XogTocDoDanh2
            ChuaDu1002 :
        mov[edx + 0xCAA4], al
            XogTocDoDanh2 :
        push 0x004E1739
        ret

            
    }
};
void __declspec(naked)ReloadInforNick()//004E1589 6
{
    __asm
    {
        mov edx, [ebp - 0x8]
        xor eax, eax
        mov byte ptr[edx + 0xD557], 0x00
        mov byte ptr[edx + 0xD555], 0x00
        cmp dword ptr[ebp - 0x4], 0x00
        jz NotHaveNick
        mov eax, [ebp - 0x4]
        xor ecx, ecx
        mov cx, [eax + 0xC0]
        cmp ecx, 0x14
        jnz CheckTypeHieuUng
        xor ecx, ecx
        mov cx, [eax + 0xC4]
        mov edx, [ebp - 0x8]
        mov byte ptr[edx + 0xD555], cl
        jmp CoDanhHiue
        CheckTypeHieuUng :
        cmp ecx, 0x2D2
            jnz CoDanhHiue
            xor ecx, ecx
            mov cx, [eax + 0xC4]
            mov edx, [ebp - 0x8]
            mov byte ptr[edx + 0xD557], cl
            CoDanhHiue :
        mov edx, [ebp - 0x8]
            xor eax, eax
            mov al, [edx + 0xD557]
            xor ecx, ecx
            mov cl, [edx + 0xD558]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu100HU1
            mov[edx + 0xCAA5], 0x64
            jmp XogTocHieuUng1
            ChuaDu100HU1 :
        mov[edx + 0xCAA5], al
            XogTocHieuUng1 :
        mov edx, [ebp - 0x8]
            xor eax, eax
            mov al, [edx + 0xD555]
            xor ecx, ecx
            mov cl, [edx + 0xD556]
            add eax, ecx
            xor ecx, ecx
            mov cl, [edx + 0xD590]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu1001
            mov[edx + 0xCAA4], 0x64
            jmp XogTocDoDanh1
            ChuaDu1001 :
        mov[edx + 0xCAA4], al
            XogTocDoDanh1 :
        push 0x004E158F
            ret



        NotHaveNick:
        mov edx, [ebp - 0x8]
            xor eax, eax
            mov al, [edx + 0xD557]
            xor ecx, ecx
            mov cl, [edx + 0xD558]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu100HU2
            mov[edx + 0xCAA5], 0x64
            jmp XogTocHieuUng2
            ChuaDu100HU2 :
        mov[edx + 0xCAA5], al
            XogTocHieuUng2 :
        mov edx, [ebp - 0x8]
            xor eax, eax
            mov al, [edx + 0xD555]
            xor ecx, ecx
            mov cl, [edx + 0xD556]
            add eax, ecx
            xor ecx, ecx
            mov cl, [edx + 0xD556]
            add eax, ecx
            cmp eax, 0x64
            jb ChuaDu1002
            mov[edx + 0xCAA4], 0x64
            jmp XogTocDoDanh2
            ChuaDu1002 :
        mov[edx + 0xCAA4], al
            XogTocDoDanh2 :
        push 0x4E15A0
            ret


    }
};
void __declspec(naked)ThayDoiTiLeQuanAo1()//0063B0FC 6
{
    __asm
    {
        xor eax,eax
        mov al, [ebp + 0x8]
        cmp eax,0x1
        jnz Default
        lea edx, TiLeTinhLuyenQuanAo
        xor ecx,ecx
        mov cl, [ebp + 0x10]
        xor eax,eax
        mov eax, [edx +ecx*0x4]
        mov[ebp - 0x8], eax
        push 0x0063B102
        ret
        Default:
        mov eax, [edx + 0x4]
        mov [ebp - 0x8], eax
        push 0x0063B102
        ret
    }
};
void __declspec(naked)ThayDoiTiLeQuanAo2()//0063B1ED 6
{
    __asm
    {
        xor eax, eax
        mov al, [ebp + 0x8]
        cmp eax, 0x1
        jnz Default
        lea eax, TiLeTinhLuyenQuanAo
        xor ecx, ecx
        mov cl, [ebp + 0x10]
        xor edx, edx
        mov edx, [eax + ecx * 0x4]
        mov[ebp - 0x8], edx
        push 0x0063B1F2
        ret
        Default :
        mov edx, [ecx]
            mov[ebp - 0x8], edx
            push 0x0063B1F2
            ret
    }
};
void __declspec(naked)AddBonusEventEXp()//004A19CA 6
{
    __asm
    {
        mov edx, [ebp - 0x24]
        mov eax, [ebp + 0x8]
        add eax,[edx+0x5C56]
        push 0x004A19D0
        ret
    }
};
void __declspec(naked)AddBonusEventEXp2()//004A19E4 6
{
    __asm
    {
        mov eax, [ebp - 0x24]
        mov ecx, [ebp + 0x8]
        add ecx, [eax + 0x5C56]
        push 0x004A19EA
        ret
    }
};
void __declspec(naked)AddBonusEventEXp3()//004A19D8 6
{
    __asm
    {
        mov ecx, [ebp - 0x24]
        mov edx, [ecx + 0x00005CB0]
        mov [ebp + 0x8], edx
        mov [ecx + 0x00005C56],edx
        push 0x004A19F0
        ret
    }
};
void __declspec(naked)FixGiaoDichMatDoHanhTrang8C()//0051A604 6
{
    __asm
    {
        cmp eax, 0x0000008C
        push 0x0051A609
        ret
    }
};
void __declspec(naked)TestRediem()//00525911 6
{
    __asm
    {
        mov eax, 0x006FF224
        call[eax]
        push eax
        mov eax, 0x006E4F34
        call eax
        add esp,0x4
        push 0x00002710
        push 0x00525916
        ret
    }
};
void __declspec(naked)ChangeValueCombine()//0052511C 6
{
    __asm
    {
        cmp [ebp - 0x4], 0x0000008C
        push 0x00525123
        ret
    }
};
void __declspec(naked)ChangeValueCombine2()//0050AE54 6
{
    __asm
    {
        cmp edx, 0x0000008C
        push 0x0050AE5A
        ret
    }
};
void __declspec(naked)ChangeValueCombine3()//0051DDC4 6
{
    __asm
    {
        cmp[ebp - 0x20], 0x0000008C
        push 0x0051DDCB
        ret
    }
};
void __declspec(naked)GetSlotSuccess()//00525B11 6
{
    __asm
    {
        and ecx, 0x000000FF
        mov eax, [ebp - 0x000000C4]
        mov [eax+0xD560],cl
        push 0x00525B1A
        ret
    }
};
bool CheckBoQuaTangTiLe(int idCombine)
{
    bool nreturn;
    nreturn = true;
    for (int i = 0; i < 200; i++)
    {

        if (idCombine == ListDieuCheKhongTacDungSach[i])
        {
            nreturn = false;
        }
    }
    return nreturn;
}
bool CheckListGiuNguyenLieu(int idCombine)
{
    bool nreturn;
    nreturn = false;
#ifdef ListIDCombineZplay
    for (int i = 0; i < 134; i++)
    {

        if (idCombine == ListDieuCheChoPhepSuDungBua[i])
        {
            nreturn = true;
        }
    }
#endif // ListIDCombineZplay
#ifdef ListIDCombineCp
    for (int i = 0; i < 200; i++)
    {

        if (idCombine == ListDieuCheChoPhepSuDungBua[i])
        {
            nreturn = true;
        }
    }
#endif // DEBUG

    
    return nreturn;
}
void __declspec(naked)TangTiLeCombine()//00525921 6
{
    __asm
    {
        push eax
       /* mov eax, 0x007711F2
        xor ecx, ecx
        mov cl, [eax]
        push ecx
        push 0x0
        push 0x0
        push 0x0
        mov ecx, [ebp + 0x8]
        xor edx, edx
        mov dx, [ecx + 0x4]
        push edx
        push 0x7
        mov ecx, [ebp - 0x000000C4]
        call addLog
        add esp,0x18*/
        mov ecx,[ebp+0x8]
        xor edx,edx
        mov dx,[ecx+0x4]
        push edx
        call CheckBoQuaTangTiLe
        add esp,0x4
        xor ecx,ecx
        mov cl,al
        test ecx,ecx
        jz Default
        mov ecx, [ebp - 0x000000C4]
        xor edx,edx
        mov dx,[ecx+0xD564]
        test edx,edx
        jz Default
        mov ecx, [ebp - 0x000000C4]
        mov edx, [ebp - 0x24]
        xor eax,eax
        mov ax, [edx + 0xC]
        mov[ecx + 0xD568], eax
        fild [ecx+0xD564]
        fimul dword ptr [ecx + 0xD568]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax,0x006E5A28
        call eax
        xor edx, edx
        mov ecx, [ebp - 0x24]
        mov dx,[ecx+0xC]
        add edx,eax
        mov ecx, [ebp - 0x000000C4]
        mov dword ptr [ecx + 0xD568],0x0
        mov dword ptr [ecx + 0xD564],0x0
        mov ecx, [ebp - 0x24]
        pop eax
        push 0x00525927
        ret

        Default:
        pop eax
        mov ecx, [ebp - 0x24]
        xor edx, edx
        mov dx, [ecx + 0xC]
        push 0x00525927
        ret
    }
};
void __declspec(naked)GetSlotFail()//00525D85 6
{
    __asm
    {

        mov eax,[ebp - 0x20]
        and eax,0xFF
        mov ecx, [ebp - 0x000000C4]
        test eax,eax
        cmp eax,0x4
        jnz Default
        mov byte ptr [ecx + 0xD560], 0x0
        Default:
        push 0x00525D8D
        ret
    }
};
void __declspec(naked)DieuCheGiuNguyenTiLe()//0051DE2F 6
{
    __asm
    {
        mov [ebp - 0x4], 0x00000000
        mov ecx, [ebp - 0x20]
        imul ecx,0x60
        mov eax, [ebp - 0x98]
        xor edx,edx
        mov dl,[eax + 0xD560]
        test edx,edx
        jz Default
        xor edx,edx
        mov dl,[eax+ecx+0x128C+0x18]
        test edx,edx
        jz Default
        xor edx, edx
        mov dl, [eax + ecx + 0x128C + 0x8]
        cmp edx,0x13
        jz VuKhi
        cmp edx, 0x1
        jnz Default
        lea edx,[eax+ecx+0x128C]
        xor ecx,ecx
        mov cl,[eax + 0xD560]
        imul ecx,0x60
        lea eax,[eax+ecx+0x128C]
        xor ecx,ecx
        mov cl,[edx+0x18]
        mov [eax+0x18],cl
        xor ecx,ecx
        mov ecx, [edx + 0x20]
        mov[eax + 0x20], ecx
        xor ecx, ecx
        mov ecx, [edx + 0x24]
        mov[eax + 0x24], ecx
        xor ecx, ecx
        mov ecx, [edx + 0x28]
        mov[eax + 0x28], ecx
        xor ecx, ecx
        mov ecx, [edx + 0x2C]
        mov[eax + 0x2C], ecx
        xor ecx, ecx
        mov ecx, [edx + 0x30]
        mov[eax + 0x30], ecx
        xor ecx, ecx
        mov ecx, [edx + 0x34]
        mov[eax + 0x34], ecx
        jmp Default

        VuKhi:
        lea edx, [eax + ecx + 0x128C]
        xor ecx, ecx
        mov cl, [eax + 0xD560]
        imul ecx, 0x60
        lea eax, [eax + ecx + 0x128C]
        xor ecx, ecx
        mov cl, [edx + 0x18]
        mov[eax + 0x18], cl

        Default:
        push 0x0051DE36
        ret
    }
};
void __declspec(naked)KhongXoaVpDieuChe()//00525DA3 6
{
    __asm
    {
        xor eax, eax
        mov dword ptr[ebp - 0xBC], 0x0
        mov al, [ebp - 0x20]
        cmp eax, 0x4
        jnz Default
        mov ecx, [ebp + 0x8]
        xor edx, edx
        mov dx, [ecx + 0x4]
        push edx
        call CheckListGiuNguyenLieu
        add esp,0x4
        xor ecx, ecx
        mov cl, al
        test ecx, ecx
        jz Default
        mov dword ptr[ebp - 0xBC], 0x1
        Default:
        push 0x00525DAD
        ret
    }
};
void __declspec(naked)TestFixAmDamg1()//0051A604 6
{
    __asm
    {
        mov [ebp - 0x00000088], eax
        push 0x004B98C3
        ret
    }
};
void __declspec(naked)AllowlearnSkill()//00628499 6
{
    __asm
    {
        push 0x00628492
        ret
    }
};
DWORD NOTICE[26];
const char NoticeEvent1[37] = "Su Kien Chien Truong Nam Han Bat Dau";
const char NoticeEvent102[25] = "Su Kien Nam Han Ket Thuc";
const char NoticeEventTKBoss1[26] = "Thong Linh Da Xuat Hien";
const char NoticeEventTKBoss2[26] = "Dai Tuong Da Xuat Hien";
const char NoticeEventTKBoss3[26] = "Nguyen Soai Da Xuat Hien";
#ifdef SKBossTGCP
const char NoticeEventBossTG[34] = "Boss The Gioi Xuat Hien O Hai Nam";
#endif // SKBossTGCP

#ifdef SKBossTGZplay
const char NoticeEventBossTG[39] = "Boss The Gioi Xuat Hien O Dao Hoa Vien";
#endif // SKBossTGZplay


const char ThongBaoDaNhatHop[22] = " Da Nhan Duoc Hop Qua";
const char NoticeEvent2[44] = "Su Kien Nhat Hop O Hop Phi Chuan Bi Bat Dau";
const char NoticeEvent3[48] = "BOSS SU KIEN,HEO VANG XUAT HIEN O HUYET SA BINH";
const char NoticeEvent4[29] = "Boss Nho Xuat Hien O Hop Phi";
const char NoticeEvent5[29] = "Boss Lon Xuat Hien O Hop Phi";
const char NoticeEvent6[34] = "Su Kien Mon Phai Chuan Bi Bat Dau";
const char NoticeEvent7[35] = "Dam Phan Loan Xuat Hien O Mon Phai";
const char NoticeEvent8[32] = "Ke Phan Do Xuat Hien O Mon Phai";
const char NoticeEvent9[41] = "Boss Su Kien Xuat Hien O Map Con Lon Son";
const char NoticeEvent19[22] = "Boss Su Kien Ket Thuc";
const char NoticeEvent10[32] = "Boss Mini Xuat Hien O Thanh Dao";
const char NoticeEventHeo[35] = "Dan Heo Con Da Xuat Hien O Hop Phi";
int Event1 = 0;
int Event2 = 0;
int Event3 = 0;
int Event4 = 0;
int Event5 = 0;
int Event6 = 0;
int Event7 = 0;
int Event8 = 0;
int Event9 = 0;
int Event10 = 0;
int Event11 = 0;
int Event12 = 0;
int Event13 = 0;
int Event14 = 0;
int Event15 = 0;
int flagBossTG = 0;
int flagEventHeo = 0;
int flagBoxEvent = 0;
int CheckEventDays(int Maps)
{
    int resultevent;
    resultevent = 0;
    int  acceptmove = 0;
    int vitrimap = Maps;
    SYSTEMTIME checktime;
    GetLocalTime(&checktime);
    if (vitrimap == 1)
    {
        __asm
        {
            lea eax, checktime
            xor ecx, ecx
            mov cl, [eax + 0x4]
            cmp ecx, 0x2
            jz NgayLeMonPhai
            cmp ecx, 0x4
            jz NgayLeMonPhai
            jmp HaveValueEventMonPhai
            NgayLeMonPhai:
            lea eax, checktime
                mov cl, [eax + 0x8]
                cmp ecx, 0x13
                jnz CheckEvent2MonPhai
                mov cl, [eax + 0xA]
                cmp ecx, 0xA
                jnz CheckEvent2MonPhai
                xor ecx, ecx
                lea eax, Event10
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventMonPhai
                lea eax, Event10
                mov[eax], 0x1
                lea eax, resultevent
                mov [eax], 0xA
                jmp HaveValueEventMonPhai

                CheckEvent2MonPhai :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x15
                jnz CheckEvent3MonPhai
                mov cl, [eax + 0xA]
                cmp ecx, 0xA
                jnz CheckEvent3MonPhai
                xor ecx, ecx
                lea eax, Event11
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventMonPhai
                lea eax, Event11
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB
                jmp HaveValueEventMonPhai

                CheckEvent3MonPhai :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x13
                jnz CheckEvent4MonPhai
                mov cl, [eax + 0xA]
                cmp ecx, 0xF
                jnz CheckEvent4MonPhai
                xor ecx, ecx
                lea eax, Event12
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventMonPhai
                lea eax, Event12
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xC
                jmp HaveValueEventMonPhai

                CheckEvent4MonPhai :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x13
                jnz CheckEvent5MonPhai
                mov cl, [eax + 0xA]
                cmp ecx, 0x1E
                jnz CheckEvent5MonPhai
                xor ecx, ecx
                lea eax, Event13
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventMonPhai
                lea eax, Event13
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xD
                jmp HaveValueEventMonPhai

                CheckEvent5MonPhai :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x15
                jnz CheckEvent6MonPhai
                mov cl, [eax + 0xA]
                cmp ecx, 0xF
                jnz CheckEvent6MonPhai
                xor ecx, ecx
                lea eax, Event14
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventMonPhai
                lea eax, Event14
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xE
                jmp HaveValueEventMonPhai

                CheckEvent6MonPhai :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x15
                jnz CheckEvent7
                mov cl, [eax + 0xA]
                cmp ecx, 0x1E
                jnz HaveValueEventMonPhai
                xor ecx, ecx
                lea eax, Event15
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventMonPhai
                lea eax, Event15
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xF
                jmp HaveValueEventMonPhai

                CheckEvent7 :
                lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x17
                jnz HaveValueEventMonPhai
                mov cl, [eax + 0xA]
                cmp ecx, 0x00
                jnz HaveValueEventMonPhai
                lea eax, Event10
                mov dword ptr[eax], 0x0
                lea eax, Event11
                mov dword ptr[eax], 0x0
                lea eax, Event12
                mov dword ptr[eax], 0x0
                lea eax, Event13
                mov dword ptr[eax], 0x0
                lea eax, Event14
                mov dword ptr[eax], 0x0
                lea eax, Event15
                mov dword ptr[eax], 0x0

            HaveValueEventMonPhai:
        }
    }
    else if (vitrimap == 2)
    {
        __asm
        {
#ifdef Check_TimeEvent
                lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0xC
                jnz SuKienBossTG2
                mov cl, [eax + 0xA]
                cmp ecx, 0x2D
                jnz SuKienBossTG2
                xor ecx, ecx
                lea eax, flagBossTG
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventConLonSon
                lea eax, flagBossTG
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB1
                jmp HaveValueEventConLonSon

                SuKienBossTG2 :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0xD
                jnz SuKienBossTG3
                mov cl, [eax + 0xA]
                cmp ecx, 0x2D
                jnz SuKienBossTG3
                xor ecx, ecx
                lea eax, flagBossTG
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventConLonSon
                lea eax, flagBossTG
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB1
                jmp HaveValueEventConLonSon

                SuKienBossTG3 :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x13
                jnz SuKienBossTG4
                mov cl, [eax + 0xA]
                cmp ecx, 0x2D
                jnz SuKienBossTG4
                xor ecx, ecx
                lea eax, flagBossTG
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventConLonSon
                lea eax, flagBossTG
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB1
                jmp HaveValueEventConLonSon

                SuKienBossTG4 :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x14
                jnz SuKienBossTG5
                mov cl, [eax + 0xA]
                cmp ecx, 0x2D
                jnz SuKienBossTG5
                xor ecx, ecx
                lea eax, flagBossTG
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventConLonSon
                lea eax, flagBossTG
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB1
                jmp HaveValueEventConLonSon

                SuKienBossTG5 :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x15
                jnz SuKienBossTG6
                mov cl, [eax + 0xA]
                cmp ecx, 0x2D
                jnz SuKienBossTG6
                xor ecx, ecx
                lea eax, flagBossTG
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventConLonSon
                lea eax, flagBossTG
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB1
                jmp HaveValueEventConLonSon

                SuKienBossTG6 :
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x16
                jnz RemoveFlag
                mov cl, [eax + 0xA]
                cmp ecx, 0x2D
                jnz RemoveFlag
                xor ecx, ecx
                lea eax, flagBossTG
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventConLonSon
                lea eax, flagBossTG
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB1
                jmp HaveValueEventConLonSon

                RemoveFlag :
            lea eax, flagBossTG
                mov[eax], 0x0
                jmp HaveValueEventConLonSon

                HaveValueEventConLonSon :
#endif // Check_TimeEvent
#ifdef EventZplay
            lea eax, checktime
                xor ecx, ecx
                mov cl, [eax + 0x8]
                cmp ecx, 0x14
                jnz RemoveFlagTG
                mov cl, [eax + 0xA]
                cmp ecx, 0x00
                jnz RemoveFlagTG
                xor ecx, ecx
                lea eax, flagBossTG
                mov ecx, [eax]
                test ecx, ecx
                jnz HaveValueEventConLonSon
                lea eax, flagBossTG
                mov[eax], 0x1
                lea eax, resultevent
                mov[eax], 0xB1
                jmp HaveValueEventConLonSon

                RemoveFlagTG:
                lea eax, flagBossTG
                mov dword ptr [eax],0x0
                HaveValueEventConLonSon:
#endif // EventZplay 
        }
    }
    else if (vitrimap == 3)
    {
        __asm
        {
        lea eax, checktime
        xor ecx, ecx
        mov cl, [eax + 0x8]
        cmp ecx, 0x14
        jnz ThaBoss1
        mov cl, [eax + 0xA]
        cmp ecx, 0x00
        jnz ThaBoss1
        xor ecx, ecx
        lea eax, Event1
        mov ecx, [eax]
        test ecx, ecx
        jnz HaveValueEventHSB
        lea eax, Event1
        mov[eax], 0x1
        lea eax, resultevent
        mov[eax], 0x1
        jmp HaveValueEventHSB

        ThaBoss1 :
        mov cl, [eax + 0x8]
            cmp ecx, 0x14
            jnz ThaBoss2
            mov cl, [eax + 0xA]
            cmp ecx, 0xA
            jnz ThaBoss2
            xor ecx, ecx
            lea eax, Event1
            mov ecx, [eax]
            test ecx, ecx
            jnz HaveValueEventHSB
            lea eax, Event1
            mov[eax], 0x1
            lea eax, resultevent
            mov[eax], 0xE3
            jmp HaveValueEventHSB

            ThaBoss2 :
        mov cl, [eax + 0x8]
            cmp ecx, 0x14
            jnz ThaBoss3
            mov cl, [eax + 0xA]
            cmp ecx, 0x14
            jnz ThaBoss3
            xor ecx, ecx
            lea eax, Event1
            mov ecx, [eax]
            test ecx, ecx
            jnz HaveValueEventHSB
            lea eax, Event1
            mov[eax], 0x1
            lea eax, resultevent
            mov[eax], 0xE4
            jmp HaveValueEventHSB

            ThaBoss3 :
        mov cl, [eax + 0x8]
            cmp ecx, 0x14
            jnz KetThucAddQua
            mov cl, [eax + 0xA]
            cmp ecx, 0x1E
            jnz KetThucAddQua
            xor ecx, ecx
            lea eax, Event1
            mov ecx, [eax]
            test ecx, ecx
            jnz HaveValueEventHSB
            lea eax, Event1
            mov[eax], 0x1
            lea eax, resultevent
            mov[eax], 0xE5
            jmp HaveValueEventHSB


        KetThucAddQua:
        mov cl, [eax + 0x8]
        cmp ecx, 0x14
        jnz NgayChanHSB2
        mov cl, [eax + 0xA]
        cmp ecx, 0x28
        jnz NgayChanHSB2
        xor ecx, ecx
        lea eax, Event1
        mov ecx, [eax]
        test ecx, ecx
        jnz HaveValueEventHSB
        lea eax, Event1
        mov[eax], 0x1
        lea eax, resultevent
        mov[eax], 0xD3
        jmp HaveValueEventHSB

            NgayChanHSB2:
            lea eax, Event1
            mov dword ptr[eax], 0x0
            HaveValueEventHSB:
        }
    }
    else if (vitrimap == 4)
    {
        __asm
        {
            lea eax, checktime
            xor ecx, ecx
            mov cl, [eax + 0x4]
            cmp ecx, 0x2
            jz KetThucNgay
            cmp ecx, 0x4
            jz KetThucNgay
            cmp ecx, 0x6
            jz KetThucNgay
            cmp ecx, 0x7
            jz KetThucNgay
            lea eax, checktime
            xor ecx, ecx
            mov cl, [eax + 0x8]
            cmp ecx, 0x15
            jnz KetThucNgay
            mov cl, [eax + 0xA]
            cmp ecx, 0x00
            jnz KetThucNgay
            xor ecx, ecx
            lea eax, flagEventHeo
            mov ecx, [eax]
            test ecx, ecx
            jnz HaveValueEventHP
            lea eax, flagEventHeo
            mov dword ptr [eax], 0x1
                lea eax, resultevent
                mov[eax], 0xA1
            jmp HaveValueEventHP

                KetThucNgay:
            lea eax, flagEventHeo
                mov dword ptr [eax], 0x0

            HaveValueEventHP:
        }
    }
    else
    {
    }
    return resultevent;
}
#ifdef Check_TimeEvent
float DiachiBossTGCLS[1][2] =
{
    {180.521 ,35.505},
};
float DiachiBossBossSK1[1][2] =
{
    {-31.315 ,13.617},
};
float DiachiBossBossSK2[1][2] =
{
    {28.165 ,-27.399},
};
float DiachiBossBossSK3[1][2] =
{
    {38.661,8.872},
};
float DiachiBossBossSK4[1][2] =
{
    {-22.559,-33.204},
};
#endif // Check_TimeEvent
#ifdef EventZplay
float DiachiBossTGCLS[1][2] =
{
    {-59.503 ,130.418},
};
#endif // EventZplay
#ifdef TestTK
float DiachiBossTKNam[1][2] =
{
    {-319.543 ,-385.054},
};
float DiachiBossTKHan[1][2] =
{
    {-405.685 ,-411.115},
};
#endif // Check_TimeEvent
void AddQuaChoTopTongKim()
{
    int CountList;
    CountList = 0;
    __asm
    {
           LoopBackCheckTop:
           lea eax,CountList
           mov ecx,[eax]
           lea eax, TopTongKim
           xor edx,edx
           mov edx,[eax+ecx*0x4]
           test edx,edx
           jz NotFountTop
           cmp ecx,0x0
           jnz AddTopTongKim2
           mov dword ptr [eax+ecx*0x4],0x0
           push 0x1
           push 0x75A
           push 0xA
           push 0x7
           mov ecx,edx
           call AddItemLoadChien
           add esp, 0x10
           jmp LoopAgain
           AddTopTongKim2:
           cmp ecx, 0x1
           jnz AddTopTongKim3
           mov dword ptr[eax + ecx * 0x4], 0x0
           push 0x1
           push 0x75A
           push 0xA
           push 0x7
           mov ecx, edx
           call AddItemLoadChien
           add esp, 0x10
           jmp LoopAgain
           AddTopTongKim3:
           cmp ecx, 0x2
           jnz AddTopTongKim4
           mov dword ptr[eax + ecx * 0x4], 0x0
           push 0x1
           push 0x75A
           push 0xA
           push 0x7
           mov ecx, edx
           call AddItemLoadChien
           add esp, 0x10
           jmp LoopAgain
           AddTopTongKim4:
           mov dword ptr[eax + ecx * 0x4], 0x0
           push 0x1
           push 0x75A
           push 0xA
           push 0x7
           mov ecx, edx
           call AddItemLoadChien
           add esp, 0x10

           LoopAgain:
           lea eax, CountList
           mov ecx, [eax]
           add ecx,0x1
           mov [eax],ecx
           cmp ecx,0x9
           jl LoopBackCheckTop
           NotFountTop:


    }
}
void __declspec(naked)GetTimeEvent()//0053A7FC 6
{
    __asm
    {
#ifdef Check_TimeEvent
        mov edx, 0x007711F2
        movsx edx, [edx]
        /*cmp edx, 0x1
        jb Default
        cmp edx, 0x6
        ja MapsKhac
        push 0x1
        call CheckEventDays
        add esp, 0x4
        cmp eax, 0xA
        jnz ThongBaoSkMonPhai1
        mov edx, 0x007711F2
        movsx edx, [edx]
        cmp edx, 0x1
        jnz Default
        lea eax, NoticeEvent6
        push eax
        call NoticeToServer
        jmp Default

        ThongBaoSkMonPhai1 :
        cmp eax, 0xB
            jnz BatDauSkMonPhai
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x1
            jnz Default
            lea eax, NoticeEvent6
            push eax
            call NoticeToServer
            jmp Default


            BatDauSkMonPhai :
        cmp eax, 0xC
            jnz SK13
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x1
            jnz RunFunProcess1
            lea eax, NoticeEvent7
            push eax
            call NoticeToServer
            RunFunProcess1 :
        call ThaQuaiMonPhaiSuKien
            jmp Default
            //

            SK13 :
        cmp eax, 0xD
            jnz SK14
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x1
            jnz RunFunProcess2
            lea eax, NoticeEvent8
            push eax
            call NoticeToServer
            RunFunProcess2 :
        call ThaBossMonPhai
            jmp Default


            SK14 :
        cmp eax, 0xE
            jnz SK15
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x1
            jnz RunFunProcess3
            lea eax, NoticeEvent7
            push eax
            call NoticeToServer
            RunFunProcess3 :
        call ThaQuaiMonPhaiSuKien
            jmp Default

            SK15 :
        cmp eax, 0xF
            jnz Default
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x1
            jnz RunFunProcess4
            lea eax, NoticeEvent8
            push eax
            call NoticeToServer
            RunFunProcess4 :
        call ThaBossMonPhai
            jmp Default
            //Su Kien O CLS
            MapsKhac :*/
        cmp edx, 0x12
            jnz MapsKhac2
            push 0x2
            call CheckEventDays
            add esp, 0x4
            cmp eax, 0xB1
            jnz Default
            lea eax, NoticeEventBossTG
            push eax
            call NoticeToServer
            lea eax, DiachiBossTGCLS
            push eax
            push 0x1CE6
            call ThaBossMP
            jmp Default
            SK55 :
        cmp eax, 0x37
            jnz SKFF
            lea eax, NoticeEvent9
            push eax
            call NoticeToServer
            lea eax, DiachiBossLonHP
            push eax
            push 0x19DF
            call ThaBossMP
            jmp Default

            SKFF :
        cmp eax, 0xFF
            jnz Default
            lea eax, NoticeEvent19
            push eax
            call NoticeToServer
            lea eax, DanhSachBoss
            mov ecx, [eax + 0x3C]
            test ecx, ecx
            jz Default
            mov eax, 0x00586F11
            call eax
            lea eax, DanhSachBoss
            mov dword ptr[eax + 0x3C], 0x0
            jmp Default
            //Su Kien
            MapsKhac2 :
        cmp edx, 0x14
            jnz MapsKhac3
            push 0x4
            call CheckEventDays
            add esp, 0x4
            cmp eax, 0xA1
            jnz Default
            lea eax, NoticeEvent3
            push eax
            call NoticeToServer
           /* mov eax, 0x006FF224
            call[eax]
            push eax
            mov eax, 0x006E4F34
            call eax
            add esp, 0x4
            mov eax, 0x006E4F41
            call eax
            cdq
            mov ecx, 0x3
            xor edx, edx
            idiv ecx
            cmp edx, 0x0
            jnz ThanViTri2*/
            /*jmp Spawnheo
            //Tha O Vi tri 2
            ThanViTri2 :
        cmp edx, 0x1
            jnz ThanViTri3
            lea eax, ListHeo2
            jmp Spawnheo
            //Tha O Vi tri 2
            ThanViTri3 :
        lea eax, ListHeo3
            Spawnheo :*/
            lea eax, ListHeo1
            push 0x0
            push eax
            call ThaHopQua
            //Boss 1
            lea eax, DiachiBossBossSK1
            push eax
            push 0x1C13
            call ThaBossMP
            //Boss 2
            lea eax, DiachiBossBossSK2
            push eax
            push 0x1C13
            call ThaBossMP
            //Boss 3
            lea eax, DiachiBossBossSK3
            push eax
            push 0x1C13
            call ThaBossMP
            //Boss 4
            lea eax, DiachiBossBossSK4
            push eax
            push 0x1C13
            call ThaBossMP
           /* lea eax, ListHeo1
            push 0x0
            push eax
            call ThaHopQua*/
            jmp Default
            //Su Kien HSB
            MapsKhac3 :
            cmp edx, 0xFF
            jnz Default
#ifdef TestTK
            push 0x3
            call CheckEventDays
            add esp, 0x4
            cmp eax, 0x1
            jnz ThaBoss1
            lea eax, NoticeEvent1
            push eax
            call NoticeToServer
            jmp Default
            //
            ThaBoss1:
            cmp eax, 0xE3
            jnz ThaBoss2
            lea eax, NoticeEventTKBoss1
            push eax
            call NoticeToServer
            lea eax, DiachiBossTKNam
            push eax
            push 0x1A2F
            call ThaBossMP
            lea eax, DiachiBossTKHan
            push eax
            push 0x1A32
            call ThaBossMP
            jmp Default

            ThaBoss2:
            cmp eax, 0xE4
            jnz ThaBoss3
            lea eax, NoticeEventTKBoss2
            push eax
            call NoticeToServer
            lea eax, DiachiBossTKNam
            push eax
            push 0x1A30
            call ThaBossMP
            lea eax, DiachiBossTKHan
            push eax
            push 0x1A33
            call ThaBossMP
            jmp Default

            ThaBoss3:
            cmp eax, 0xE5
            jnz KetThucSuKienTK
            lea eax, NoticeEventTKBoss3
            push eax
            call NoticeToServer
            lea eax, DiachiBossTKNam
            push eax
            push 0x1A31
            call ThaBossMP
            lea eax, DiachiBossTKHan
            push eax
            push 0x1A34
            call ThaBossMP
            jmp Default
            //
            //
            KetThucSuKienTK:
            cmp eax,0xD3
            jnz Default
            lea eax, NoticeEvent102
            push eax
            call NoticeToServer
            push 0x0
            push 0x2FFF
            mov ecx, 0x007763AC
            mov ecx, [ecx]
            mov eax, 0x606F5B
            call eax
            lea eax,nDiemKim
            mov [eax],0x0
            lea eax, nDiemTong
            mov[eax], 0x0
            //call AddQuaChoTopTongKim
            jmp Default
#endif // TestTK
            jmp Default
#endif // Check_TimeEvent
#ifdef EventZplay
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0xF
            jnz Default
            push 0x2
            call CheckEventDays
            add esp, 0x4
            cmp eax, 0xB1
            jnz Default
            lea eax, NoticeEventBossTG
            push eax
            call NoticeToServer
            lea eax, DiachiBossTGCLS
            push eax
            push 0x1CF0
            call ThaBossMP
            jmp Default
#endif // EventZplay

        

        /// Fun Load
            ThaQuaiMonPhaiSuKien :
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x1
            jnz Mp2
            push 0x0
            lea eax, ListQuaiThieuLam
            push eax
            call ThaQuaiMonPhai
            ret
            //
            Mp2 :
        cmp edx, 0x2
            jnz Mp3
            push 0x0
            lea eax, ListQuaiCaiBang
            push eax
            call ThaQuaiMonPhai
            ret
            //
            Mp3 :
        cmp edx, 0x3
            jnz Mp4
            push 0x0
            lea eax, ListQuaiLucLam
            push eax
            call ThaQuaiMonPhai
            ret
            //
            Mp4 :
        cmp edx, 0x4
            jnz Mp5
            push 0x0
            lea eax, ListQuaiBiCung
            push eax
            call ThaQuaiMonPhai
            ret
            //
            Mp5 :
        cmp edx, 0x5
            jnz Mp6
            push 0x0
            lea eax, ListQuaiVoDang
            push eax
            call ThaQuaiMonPhai
            ret
            //
            Mp6 :
        cmp edx, 0x6
            jnz NotFoundMap
            push 0x0
            lea eax, ListQuaiMaGiao
            push eax
            call ThaQuaiMonPhai
            NotFoundMap :
            ret

            ThaBossMonPhai :
        mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x1
            jnz BossMp2
            lea eax, ListBossThieuLam
            push eax
            push 0x1CF6
            call ThaBossMP
            ret
            //
            BossMp2 :
        cmp edx, 0x2
            jnz BossMp3
            lea eax, ListBossCaiBang
            push eax
            push 0x1CF6
            call ThaBossMP
            ret
            //
            BossMp3 :
        cmp edx, 0x3
            jnz BossMp4
            lea eax, ListBossLucLam
            push eax
            push 0x1CF6
            call ThaBossMP
            ret
            //
            BossMp4 :
        cmp edx, 0x4
            jnz BossMp5
            lea eax, ListBossBiCung
            push eax
            push 0x1CF6
            call ThaBossMP
            ret
            //
            BossMp5 :
        cmp edx, 0x5
            jnz BossMp6
            lea eax, ListBossVoDang
            push eax
            push 0x1CF6
            call ThaBossMP
            ret
            //
            BossMp6 :
        cmp edx, 0x6
            jnz NotFoundMapBoss
            lea eax, ListBossMaGiao
            push eax
            push 0x1CF6
            call ThaBossMP
            NotFoundMapBoss :
            ret


            ThaHopQua :
            xor ecx, ecx
            LoopSpawnBox :
            //Random
            mov ecx,[esp+0x8]
            mov edx, [esp + 0x4]
            lea eax, [edx + ecx * 0x4]
            mov ecx, [eax]
            lea edx, toadoBoss
            mov[edx], ecx
            mov ecx, [eax + 0x4]
            mov[edx + 0x4], ecx
            mov eax, 0x1463
            lea edx, toadoBoss
            push edx
            push eax
            call CallBoss
            mov ecx, [esp + 0x8]
            add ecx, 0x2
            mov[esp + 0x8], ecx
            cmp ecx, 0x258
            jae EndLoopBox
            jmp LoopSpawnBox
            EndLoopBox :
            ret 0x8

            ThaBossNho :
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x11
            jnz Default
            xor ecx, ecx
            LoopSpawnBossNho :
            mov ecx, [esp + 0x8]
            mov eax, [esp + 0x4]
            lea eax, [eax + ecx * 0x4]
            mov ecx, [eax]
            lea edx, toadoBoss
            mov[edx], ecx
            mov ecx, [eax + 0x4]
            mov[edx + 0x4], ecx
            mov eax, 0x1D12
            lea edx, toadoBoss
            push edx
            push eax
            call CallBoss
            mov ecx, [esp + 0x8]
            add ecx, 0x2
            mov[esp + 0x8], ecx
            cmp ecx, 0x8
            jae EndLoopBossNho
            jmp LoopSpawnBossNho
            EndLoopBossNho :
        ret 0x8

            ThaBossLonHP :
            mov edx, 0x007711F2
            movsx edx, [edx]
            cmp edx, 0x11
            jnz Default
            lea eax, [esp + 0x4]
            mov ecx, [eax]
            lea edx, toadoBoss
            mov[edx], ecx
            mov ecx, [eax + 0x4]
            mov[edx + 0x4], ecx
            mov eax, 0x1D11
            lea edx, toadoBoss
            push edx
            push eax
            call CallBoss
            ret 0x4

            ThaQuaiMonPhai:
            LoopSpawnQuaiMP:
            mov ecx, [esp + 0x8]
            mov eax, [esp + 0x4]
            lea eax, [eax + ecx * 0x4]
            mov ecx, [eax]
            lea edx, toadoBoss
            mov[edx], ecx
            mov ecx, [eax + 0x4]
            mov[edx + 0x4], ecx
            mov eax, 0x1D31
            lea edx, toadoBoss
            push edx
            push eax
            call CallBoss
            mov ecx, [esp + 0x8]
            add ecx, 0x2
            mov[esp + 0x8], ecx
            cmp ecx, 0x28
            jae OutLoadQuaiMP
            jmp LoopSpawnQuaiMP
            OutLoadQuaiMP :
        ret 0x8

            ThaBossMP :
            mov eax, [esp + 0x8]
            mov ecx, [eax]
            lea edx, toadoBoss
            mov[edx], ecx
            mov ecx, [eax + 0x4]
            mov[edx + 0x4], ecx
            mov eax, [esp+0x4]
            lea edx, toadoBoss
            push edx
            push eax
            call CallBoss
            ret 0x8





        CallBoss:
            push 0x0
            push 0x0
            push 0x0
            mov edx, [esp + 0x14]
            push edx
            push 0x0
            mov eax, [esp + 0x18]
            push eax
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
            ret 0x8




        Default:
        lea  ecx, [ebp - 0x9C]
        push 0x0053A802
        ret

            NoticeToServer:
            push 0x67
            push 0x0
            lea  edx, NOTICE
            push edx
            mov eax, 0x006E3B70
            call eax
            add esp, 0xC
            lea  edx, NOTICE
            mov word ptr[edx], 0x67
            mov byte ptr[edx + 0x2], 0x73
            mov byte ptr[edx + 0x3], 0x7F
            mov dword ptr[edx + 0x4], 0x0
            mov byte ptr[edx + 0x8], 0x0
            push 0x50
            mov eax, [esp+0x8]
            push eax
            lea edx, [edx + 0x15]
            push edx
            mov eax, 0x006E4100
            call eax
            add esp, 0xC
            lea  edx, NOTICE
            push edx
            xor eax, eax
            mov ax, [edx]
            push eax
            mov ecx, 0x00776390
            mov ecx, [ecx]
            mov eax, 0x0041A639
            call eax
            ret 0x4
    }
};
void __declspec(naked)KhoaHapKhiPK()//004C0000 6
{
    __asm
    {
        xor edx,edx
        mov edx, [ecx + 0xAC18]
        test edx,edx
        jz Default
        mov word ptr [eax + 0x46], 0x0
        mov word ptr [eax + 0x48], 0x0
        push 0x004C001C
        ret 

        Default:
        mov dx, [ecx + 0x0000756A]
        push 0x004C0007
        ret
    }
};
void __declspec(naked)KhoaHapKhiPK2()//  004B6987
{
    __asm
    {
        mov [ebp - 0x14], ecx
        xor eax, eax
        mov eax, [ecx + 0xAC18]
        test eax, eax
        jz Default
        push 0x004B6990
        ret

        Default :
        cmp dword ptr[ebp + 0x8], 0x0
        push 0x004B698E
        ret
    }
};
void __declspec(naked)KhoaHapKhiPK3()//004C0AAF 6
{
    __asm
    {
        xor eax, eax
        mov eax, [edx + 0xAC18]
        test eax, eax
        jz Default
        mov word ptr[ecx + 0x46], 0x0
        mov word ptr[ecx + 0x48], 0x0
        push 0x004C0ACB
        ret

        Default :
        mov ax, [edx + 0x0000756A]
            push 0x004C0AB6
            ret
    }
};
void __declspec(naked)KhoaHapKhiPK4()//004C1811 6
{
    __asm
    {
        xor ecx, ecx
        mov ecx, [eax + 0xAC18]
        test ecx, ecx
        jz Default
        mov word ptr[edx + 0x46], 0x0
        mov word ptr[edx + 0x48], 0x0
        push 0x004C182D
        ret

        Default :
        mov cx, [eax + 0x0000756A]
            push 0x004C1818
            ret
    }
};
void __declspec(naked)KhoaHapKhiPK5()//004C19F7 6
{
    __asm
    {
        xor ecx, ecx
        mov ecx, [eax + 0xAC18]
        test ecx, ecx
        jz Default
        mov word ptr[edx + 0x46], 0x0
        mov word ptr[edx + 0x48], 0x0
        push 0x004C1A13
        ret

        Default :
        mov cx, [eax + 0x0000756A]
            push 0x004C19FE
            ret
    }
};
void __declspec(naked)KhoaHapKhiPK6()//004C287A 6
{
    __asm
    {
        xor edx, edx
        mov edx, [ecx + 0xAC18]
        test edx, edx
        jz Default
        mov word ptr[eax + 0x50], 0x0
        mov word ptr[eax + 0x52], 0x0
        push 0x004C2896
        ret

        Default :
        mov dx, [ecx + 0x0000756A]
            push 0x004C2881
            ret
    }
};
void __declspec(naked)KhoaHapKhiPK7()//004C3161 6
{
    __asm
    {
        xor edx, edx
        mov edx, [ecx + 0xAC18]
        test edx, edx
        jz Default
        mov word ptr[eax + 0x50], 0x0
        mov word ptr[eax + 0x52], 0x0
        push 0x004C317D
        ret

        Default :
        mov dx, [ecx + 0x0000756A]
            push 0x004C3168
            ret
    }
};
void __declspec(naked)KhoaHapKhiPK8()//004C3E80 6
{
    __asm
    {
        xor edx, edx
        mov edx, [ecx + 0xAC18]
        test edx, edx
        jz Default
        mov word ptr[eax + 0x50], 0x0
        mov word ptr[eax + 0x52], 0x0
        push 0x004C3E9C
        ret

        Default :
        mov dx, [ecx + 0x0000756A]
            push 0x004C3E87
            ret
    }
};
void __declspec(naked)KhoaHapKhiPK9()//004C4A65 6
{
    __asm
    {
        xor ecx, ecx
        mov ecx, [eax + 0xAC18]
        test ecx, ecx
        jz Default
        mov word ptr[edx + 0x46], 0x0
        mov word ptr[edx + 0x48], 0x0
        push 0x004C4A81
        ret

        Default :
        mov cx, [eax + 0x0000756A]
            push 0x004C4A6C
            ret
    }
};
void __declspec(naked)KhoaHapKhiPK10()//004C5BAD 6
{
    __asm
    {
        xor edx, edx
        mov edx, [ecx + 0xAC18]
        test edx, edx
        jz Default
        mov word ptr[eax + 0x50], 0x0
        mov word ptr[eax + 0x52], 0x0
        push 0x004C5BC9
        ret

        Default :
        mov dx, [ecx + 0x0000756A]
            push 0x004C5BB4
            ret
    }
};
void __declspec(naked)TangPhanTramDmgTank()//004BFE1F 6
{
    __asm
    {
        xor eax,eax
        mov ax,[edx+0xD562]
        test eax,eax
        jz Default
        //Min
        mov ecx, [ebp - 0x24]
        fild [ecx + 0xD562]
        fimul dword ptr[ecx + 0x000075AC]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax    
        mov edx, [ebp - 0x24]
        mov ecx, [edx + 0x000077B8]
        add ecx,eax
        mov edx, [ebp - 0x24]
        add ecx, [edx + 0x000075AC]
        mov eax, [ebp + 0x8]
        mov [eax], ecx
        // Max
        mov ecx, [ebp - 0x24]
        fild[ecx + 0xD562]
        fimul dword ptr[ecx + 0x000075B0]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov edx, [ebp - 0x24]
        mov ecx, [edx + 0x000077BC]
        add ecx, eax
        mov edx, [ebp - 0x24]
        add ecx, [edx + 0x000075B0]
        mov eax, [ebp + 0x8]
        mov[eax+0x4], ecx
        push 0x004BFE42
        ret 

        Default:
        add ecx, [edx + 0x000075AC]
        push 0x004BFE25
        ret
    }
};
void __declspec(naked)TangPhanTramDmgThucKy()//004C486A 6
{
    __asm
    {
        xor edx, edx
        mov dx, [ecx + 0xD562]
        test edx, edx
        jz Default
        //Min
        mov edx, [ebp - 0x38]
        fild[ecx + 0xD562]
        fimul dword ptr[ecx + 0x00007654]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov edx, [ebp - 0x38]
        mov ecx, [edx + 0x000077B8]
        add ecx, eax
        mov edx, [ebp - 0x38]
        add ecx, [edx + 0x00007654]
        mov eax, [ebp + 0x8]
        mov[eax], ecx
        // Max
        mov ecx, [ebp - 0x38]
        fild[ecx + 0xD562]
        fimul dword ptr[ecx + 0x00007658]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov edx, [ebp - 0x24]
        mov ecx, [edx + 0x000077BC]
        add ecx, eax
        mov edx, [ebp - 0x24]
        add ecx, [edx + 0x00007658]
        mov eax, [ebp + 0x8]
        mov[eax + 0x4], ecx
        push 0x004C488D
        ret

        Default :
        add eax, [ecx + 0x00007654]
            push 0x004C4870
            ret
    }
};
void __declspec(naked)TangPhanTramDmgNuker()//004C2EB0 6
{
    __asm
    {
        xor eax, eax
        mov ax, [edx + 0xD562]
        test eax, eax
        jz Default
        //Min
        mov edx, [ebp - 0x44]
        fild [edx + 0xD562]
        fimul dword ptr[edx + 0x000076C4]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov edx, [ebp - 0x44]
        mov ecx, [edx + 0x0007738]
        add ecx, eax
        mov edx, [ebp - 0x44]
        add ecx, [edx + 0x000076C4]
        mov eax, [ebp + 0x8]
        mov[eax], ecx
        // Max
        mov edx, [ebp - 0x44]
        fild[edx + 0xD562]
        fimul dword ptr[edx + 0x000076C8]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov edx, [ebp - 0x44]
        mov ecx, [edx + 0x000773C]
        add ecx, eax
        mov edx, [ebp - 0x44]
        add ecx, [edx + 0x000076C8]
        mov eax, [ebp + 0x8]
        mov[eax+0x4], ecx
        push 0x004C2ED3
        ret

        Default :
        add ecx, [edx + 0x000076C4]
        push 0x004C2EB6
        ret
    }
};
void __declspec(naked)TruSatThuong()//004B833C 6
{
    __asm
    {
        xor edx, edx
        mov ecx, [ebp - 0xA4]
        mov dl,[ecx+0xD561]
        test edx, edx
        jz Default
        mov [ecx+0xD56C],eax
        //Min
        mov ecx, [ebp - 0xA4]
        fild[ecx + 0xD561]
        fimul dword ptr[ecx + 0x0000D56C]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov ecx, [ebp - 0xA4]
        mov edx, [ecx + 0x0000D56C]
        sub edx,eax
        mov [ebp - 0x00000094], edx
        push 0x004B8342
        ret

        Default :
        mov [ebp - 0x00000094], eax
            push 0x004B8342
            ret
    }
};
void __declspec(naked)TruSatThuong1()//004B82EA 6
{
    __asm
    {
        xor edx, edx
        mov ecx, [ebp - 0xA4]
        mov dl, [ecx + 0xD561]
        test edx, edx
        jz Default
        mov[ecx + 0xD56C], eax
        //Min
        mov ecx, [ebp - 0xA4]
        fild[ecx + 0xD561]
        fimul dword ptr[ecx + 0x0000D56C]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov ecx, [ebp - 0xA4]
        mov edx, [ecx + 0x0000D56C]
        sub edx, eax
        mov[ebp - 0x00000094], edx
        push 0x004B82F0
        ret

        Default :
        mov[ebp - 0x00000094], eax
            push 0x004B82F0
            ret
    }
};
void __declspec(naked)TruSatThuongKC()//004B9A17 6
{
    __asm
    {
        add eax, edx
        xor edx, edx
        mov ecx, [ebp - 0xBC]
        mov dl, [ecx + 0xD561]
        test edx, edx
        jz Default
        mov[ecx + 0xD56C], eax
        //Min
        mov ecx, [ebp - 0xBC]
        fild[ecx + 0xD561]
        fimul dword ptr[ecx + 0x0000D56C]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov ecx, [ebp - 0xBC]
        mov edx, [ecx + 0x0000D56C]
        sub edx, eax
        mov [ebp - 0x54], edx
        push 0x004B9A1C
        ret

        Default :
        mov[ebp - 0x54], eax
            push 0x004B9A1C
            ret
    }
};
void __declspec(naked)TruSatThuongKC1()//004B99FE 6
{
    __asm
    {
        xor edx, edx
        mov ecx, [ebp - 0xBC]
        mov dl, [ecx + 0xD561]
        test edx, edx
        jz Default
        mov[ecx + 0xD56C], eax
        //Min
        mov ecx, [ebp - 0xA4]
        fild[ecx + 0xD561]
        fimul dword ptr[ecx + 0x0000D56C]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        mov ecx, [ebp - 0xBC]
        mov edx, [ecx + 0x0000D56C]
        sub edx, eax
        mov[ebp - 0x54], edx
        push 0x004B9A01
        ret

        Default :
        mov[ebp - 0x54], eax
            push 0x004B9A01
            ret
    }
};
void __declspec(naked)FixAmMauHap()//005885EF 6
{
    __asm
    {
        xor eax,eax
        mov ax, word ptr[ebp - 0x2C]
        test eax, eax
        jle Adr00588606
        xor ecx,ecx
        mov cx, word ptr[ebp - 0x2C]
        push ecx
        mov ecx, [ebp + 0x8]
        mov eax,0x004B6981
        call eax
        push 0x00588604
        ret 
        Adr00588606:
        test eax,eax
        jz KhongCoHap
        push 0x1388
        mov ecx, [ebp + 0x8]
        mov eax, 0x004B6981
        call eax
        push 0x00588604
        ret

        KhongCoHap:
        push 0x0058861D
        ret
    }
};
void __declspec(naked)FixAmMauHap2()//00589052 6
{
    __asm
    {
        xor eax, eax
        mov ax, word ptr[ebp - 0x28]
        test eax, eax
        jle Adr589069
        xor ecx, ecx
        mov cx, word ptr[ebp - 0x28]
        push ecx
        mov ecx, [ebp + 0x8]
        mov eax, 0x004B6981
        call eax
        push 0x00589067
        ret
        Adr589069 :
        test eax,eax
        jz KhongCoHap
        push 0x1388
        mov ecx, [ebp + 0x8]
        mov eax, 0x004B6981
        call eax
        push 0x00589067
        ret
        KhongCoHap:
        push 0x00589080
        ret
    }
};
void __declspec(naked)FixAmMauHapNuker()//005899CD 6
{
    __asm
    {
        xor eax, eax
        mov ax, word ptr[ebp - 0x2C]
        test eax, eax
        jle loc_5899E4
        xor ecx, ecx
        mov cx, word ptr[ebp - 0x2C]
        push ecx
        mov ecx, [ebp + 0x8]
        mov eax, 0x004B6981
        call eax
        push 0x005899E2
        ret
        loc_5899E4 :
        test eax,eax
        jz KhongCoHap
        push 0x1388
        mov ecx, [ebp + 0x8]
        mov eax, 0x004B6981
        call eax
        push 0x005899E2
        ret

        KhongCoHap:
        push 0x005899FB
        ret
    }
};
void __declspec(naked)TestDoiGiaTriDeff()//004D6D96 6
{
    __asm
    {
        lea eax, deffnew
        fmul dword ptr[eax]
        push 0x004D6D9D
        ret
    }
};
void __declspec(naked)TestDoiGiaTriDeffNuker()//005944C6 6
{
    __asm
    {
        lea eax, deffnew
        fmul dword ptr[eax]
        push 0x004D6E5D
        ret
    }
};
void __declspec(naked)AddNewOptCloth()//004CABB6 6
{
    __asm
    {
        
        push 0x0
        push 0x1
        mov  ecx, [ebp - 0x50]
        call AddNewOptionForItem
        add esp,0x8
        mov edx, [ebp - 0x50]
        mov byte ptr[edx + 0x00007960], 0x1
        push 0x004CABC0
        ret
    }
};
void __declspec(naked)AddBonusForPackageEXP()//004A1A37 6
{
    __asm
    {
        push ecx
        mov eax, [ebp - 0x24]
        xor ecx,ecx
        mov ecx,[eax+0x5C56]
        lea edx, [ebp - 0x20]
        mov [edx+0x3],ecx
        push edx
        push 0x004A1A3C
        ret
    }
};
void __declspec(naked)FixMaxCritGiamRage()//0059432C 6
{
    __asm
    {
        mov ecx, 0x00000BB8
        push 0x00594331
        ret
    }
};
void __declspec(naked)FixMaxCritSend()//00587A18 6
{
    __asm
    {
        mov eax, [edx + 0xC]
        push eax
        push 0x00587A1D
        ret
    }
};
void __declspec(naked)FixCritAll()//0059433E 6
{
    __asm
    {
        mov eax,[ebp+0x8]
        cmp eax,0x1
        jae loc_59436F
        mov dword ptr[ebp - 0xC], 0x1
        jmp EndCritCheck
        loc_59436F:
        mov ecx, [ebp + 0x8]
        mov [ebp - 0xC], ecx
        EndCritCheck:
        mov edx, [ebp - 0xC]
        mov [ebp + 0x8], edx
        mov eax,[ebp+0x8]
        xor ecx,ecx
        cmp eax, [ebp - 0x4]
        setnle  cl
        mov [ebp - 0x8], cl
        push 0x005944A5
        ret
    }
};
void __declspec(naked)FixSendCrit2()//00588B19 6
{
    __asm
    {
        mov eax, [edx + 0xC]
        push eax
        push 0x00588B1E
        ret
    }
};
void __declspec(naked)FixSendCrit3()//005895EE 6
{
    __asm
    {
        mov edx, [ecx + 0xC]
        push edx
        push 0x005895F3
        ret
    }
};
void __declspec(naked)FixLoiDeoTinVatMatDo()//0050AFED 6
{
    __asm
    {
        cmp eax, 0x0000008C
        push 0x0050AFF2
        ret
    }
};
void __declspec(naked)TestSkillAOE()//00605D12 5
{
    __asm
    {
        //GetDmg Real
        //Max DMG
        mov ecx, [ebp + 0x8]
        mov eax,[ecx+0x7738]
        mov ecx, [ebp + 0x8]
        add eax,[ecx+0x76C4]
        mov ecx, [ebp + 0xC]
        mov [ecx],eax
        //Min DMG
        mov ecx, [ebp + 0x8]
        mov eax, [ecx + 0x773C]
        mov ecx, [ebp + 0x8]
        add eax, [ecx + 0x76C8]
        mov ecx, [ebp + 0xC]
        mov[ecx+0x4], eax
        //Max Dmg
        mov ecx, [ebp + 0xC]
        mov edx, [ecx + 0x40]
        add edx, 0x96
        mov eax, [ecx]
        imul eax,edx
        cdq
        mov ecx,0x64
        idiv ecx
        mov ecx,[ebp + 0xC]
        mov [ecx],eax
        //Min Dmg
        mov ecx, [ebp + 0xC]
        mov edx, [ecx + 0x40]
        add edx, 0x96
        mov eax, [ecx+0x4]
        imul eax, edx
        cdq
        mov ecx, 0x64
        idiv ecx
        mov ecx, [ebp + 0xC]
        mov[ecx+0x4], eax
        // Tinh Defff
        mov ecx, [ebp - 0x64]
        add ecx,0x8
        mov eax,0x5A4470
        call eax
        cmp eax,0x3
        jnz KhongBiet
        mov ecx, [ebp + 0xC]
        mov dl,[ecx+0x45]
        push edx
        mov ecx, [ebp - 0x64]
        mov eax,0x4332C0
        call eax
        push eax
        mov eax, [ebp + 0xC]
        mov cx,[eax+0x14]
        push ecx
        mov eax, [ebp + 0xC]
        mov ecx,[eax]
        push ecx
        mov ecx, [ebp + 0xC]
        mov dl, [ecx + 0x34]
        push edx
        mov ecx, [ebp - 0x64]
        mov eax,0x58BA56
        call eax
        cmp eax,0xF423F
        jle NhoHonMaxDmg
        mov ecx, [ebp + 0xC]
        mov dword ptr [ecx],0xF423F
        jmp TinhDmgMin
        NhoHonMaxDmg:
        mov ecx, [ebp + 0xC]
        mov [ecx], eax
        jmp TinhDmgMin
        //
        KhongBiet:
        push 0x0
        push 0x0
        push 0x0
        mov eax, [ebp + 0xC]
        mov ecx, [eax]
        push ecx
        mov ecx, [ebp + 0xC]
        mov dl, [ecx + 0x34]
        push edx
        mov ecx, [ebp - 0x64]
        mov eax, 0x58BA56
        call eax
        cmp eax, 0xF423F
        jle NhoHonMaxDmg2
        mov ecx, [ebp + 0xC]
        mov dword ptr[ecx], 0xF423F
        jmp TinhDmgMin
        NhoHonMaxDmg2 :
        mov ecx, [ebp + 0xC]
        mov[ecx], eax
        jmp TinhDmgMin

        DefaultDmg:
        push 0x1EFA
        push 0x00605D17
        ret

        TinhDmgMin:
        mov ecx, [ebp - 0x64]
            add ecx, 0x8
            mov eax, 0x5A4470
            call eax
            cmp eax, 0x3
            jnz KhongBiet2
            mov ecx, [ebp + 0xC]
            mov dl, [ecx + 0x45]
            push edx
            mov ecx, [ebp - 0x64]
            mov eax, 0x4332C0
            call eax
            push eax
            mov eax, [ebp + 0xC]
            mov cx, [eax + 0x14]
            push ecx
            mov eax, [ebp + 0xC]
            mov ecx, [eax+0x4]
            push ecx
            mov ecx, [ebp + 0xC]
            mov dl, [ecx + 0x34]
            push edx
            mov ecx, [ebp - 0x64]
            mov eax, 0x58BA56
            call eax
            cmp eax, 0xF423F
            jle NhoHonMaxDmg3
            mov ecx, [ebp + 0xC]
            mov dword ptr[ecx], 0xF423F
            jmp DefaultDmg
            NhoHonMaxDmg3 :
        mov ecx, [ebp + 0xC]
            mov[ecx], eax
            jmp DefaultDmg
            //
            KhongBiet2 :
        push 0x0
            push 0x0
            push 0x0
            mov eax, [ebp + 0xC]
            mov ecx, [eax+0x4]
            push ecx
            mov ecx, [ebp + 0xC]
            mov dl, [ecx + 0x34]
            push edx
            mov ecx, [ebp - 0x64]
            mov eax, 0x58BA56
            call eax
            cmp eax, 0xF423F
            jle NhoHonMaxDmg4
            mov ecx, [ebp + 0xC]
            mov dword ptr[ecx+0x4], 0xF423F
            jmp DefaultDmg
            NhoHonMaxDmg4 :
            mov ecx, [ebp + 0xC]
            mov[ecx+0x4], eax
            jmp DefaultDmg
    }
};
void __declspec(naked)TestSkillAOE2()//0042BF48 5
{
    __asm
    {
        //GetDmg Real
        //Max DMG
        mov ecx, [ebp + 0x8]
        mov eax, [ecx + 0x7738]
        mov ecx, [ebp + 0x8]
        add eax, [ecx + 0x76C4]
        mov ecx, [ebp + 0xC]
        mov[ecx], eax
        //Min DMG
        mov ecx, [ebp + 0x8]
        mov eax, [ecx + 0x773C]
        mov ecx, [ebp + 0x8]
        add eax, [ecx + 0x76C8]
        mov ecx, [ebp + 0xC]
        mov[ecx + 0x4], eax
        //Max Dmg
        mov ecx, [ebp + 0xC]
        mov edx, [ecx + 0x40]
        add edx, 0x96
        mov eax, [ecx]
        imul eax, edx
        cdq
        mov ecx, 0x64
        idiv ecx
        mov ecx, [ebp + 0xC]
        mov[ecx], eax
        //Min Dmg
        mov ecx, [ebp + 0xC]
        mov edx, [ecx + 0x40]
        add edx, 0x96
        mov eax, [ecx + 0x4]
        imul eax, edx
        cdq
        mov ecx, 0x64
        idiv ecx
        mov ecx, [ebp + 0xC]
        mov[ecx + 0x4], eax
        // Tinh Defff
        mov ecx, [ebp - 0x24]
        add ecx, 0x8
        mov eax, 0x5A4470
        call eax
        cmp eax, 0x3
        jnz KhongBiet
        mov ecx, [ebp + 0xC]
        mov dl, [ecx + 0x45]
        push edx
        mov ecx, [ebp - 0x24]
        mov eax, 0x4332C0
        call eax
        push eax
        mov eax, [ebp + 0xC]
        mov cx, [eax + 0x14]
        push ecx
        mov eax, [ebp + 0xC]
        mov ecx, [eax]
        push ecx
        mov ecx, [ebp + 0xC]
        mov dl, [ecx + 0x34]
        push edx
        mov ecx, [ebp - 0x24]
        mov eax, 0x58BA56
        call eax
        cmp eax, 0xF423F
        jle NhoHonMaxDmg
        mov ecx, [ebp + 0xC]
        mov dword ptr[ecx], 0xF423F
        jmp TinhDmgMin
        NhoHonMaxDmg :
        mov ecx, [ebp + 0xC]
            mov[ecx], eax
            jmp TinhDmgMin
            //
            KhongBiet :
        push 0x0
            push 0x0
            push 0x0
            mov eax, [ebp + 0xC]
            mov ecx, [eax]
            push ecx
            mov ecx, [ebp + 0xC]
            mov dl, [ecx + 0x34]
            push edx
            mov ecx, [ebp - 0x24]
            mov eax, 0x58BA56
            call eax
            cmp eax, 0xF423F
            jle NhoHonMaxDmg2
            mov ecx, [ebp + 0xC]
            mov dword ptr[ecx], 0xF423F
            jmp TinhDmgMin
            NhoHonMaxDmg2 :
        mov ecx, [ebp + 0xC]
            mov[ecx], eax
            jmp TinhDmgMin

            DefaultDmg :
            push 0x12F4
            push 0x0042BF4D
            ret

            TinhDmgMin :
        mov ecx, [ebp - 0x24]
            add ecx, 0x8
            mov eax, 0x5A4470
            call eax
            cmp eax, 0x3
            jnz KhongBiet2
            mov ecx, [ebp + 0xC]
            mov dl, [ecx + 0x45]
            push edx
            mov ecx, [ebp - 0x24]
            mov eax, 0x4332C0
            call eax
            push eax
            mov eax, [ebp + 0xC]
            mov cx, [eax + 0x14]
            push ecx
            mov eax, [ebp + 0xC]
            mov ecx, [eax + 0x4]
            push ecx
            mov ecx, [ebp + 0xC]
            mov dl, [ecx + 0x34]
            push edx
            mov ecx, [ebp - 0x24]
            mov eax, 0x58BA56
            call eax
            cmp eax, 0xF423F
            jle NhoHonMaxDmg3
            mov ecx, [ebp + 0xC]
            mov dword ptr[ecx], 0xF423F
            jmp DefaultDmg
            NhoHonMaxDmg3 :
        mov ecx, [ebp + 0xC]
            mov[ecx], eax
            jmp DefaultDmg
            //
            KhongBiet2 :
        push 0x0
            push 0x0
            push 0x0
            mov eax, [ebp + 0xC]
            mov ecx, [eax + 0x4]
            push ecx
            mov ecx, [ebp + 0xC]
            mov dl, [ecx + 0x34]
            push edx
            mov ecx, [ebp - 0x24]
            mov eax, 0x58BA56
            call eax
            cmp eax, 0xF423F
            jle NhoHonMaxDmg4
            mov ecx, [ebp + 0xC]
            mov dword ptr[ecx + 0x4], 0xF423F
            jmp DefaultDmg
            NhoHonMaxDmg4 :
        mov ecx, [ebp + 0xC]
            mov[ecx + 0x4], eax
            jmp DefaultDmg
    }
};

void __declspec(naked)ThongBaoDaNhatQua()//005ABBB5 6
{
    __asm
    {
        mov ecx, [ebp - 0x4]
        xor edx, edx
        mov dx, [ecx + 0x14]
        cmp edx, 0x11C6
        jnz Default
        //Notice to Server
        lea eax, ThongBaoDaNhatHop
        push eax
        call NoticeToServerEvent
        jmp Default
        NoticeToServerEvent:
        push 0x67
        push 0x0
        lea  edx, NOTICE
        push edx
        mov eax, 0x006E3B70
        call eax
        add esp, 0xC
        lea  edx, NOTICE
        mov word ptr[edx], 0x67
        mov byte ptr[edx + 0x2], 0x73
        mov byte ptr[edx + 0x3], 0x7F
        mov dword ptr[edx + 0x4], 0x0
        mov byte ptr[edx + 0x8], 0x0
        mov ecx, [ebp + 0x8]
        call get_name1
        push eax
        mov eax, 0x006E45A0
        call eax
        add esp, 0x4
        push eax
        mov ecx, [ebp + 0x8]
        call get_name1
        push eax
        lea edx, NOTICE
        lea eax, [edx + 0x15]
        push eax
        mov eax, 0x006E3CC0
        call eax
        add esp,0xC
        mov ecx, [ebp + 0x8]
        call get_name1
        push eax
        mov eax, 0x006E45A0
        call eax
        add esp, 0x4
        lea  edx, NOTICE
        lea edx,[edx+eax]
        push 0x50
        mov eax, [esp + 0x8]
        push eax
        lea edx, [edx + 0x15]
        push edx
        mov eax, 0x006E4100
        call eax
        add esp, 0xC
        lea  edx, NOTICE
        push edx
        xor eax, eax
        mov ax, [edx]
        push eax
        mov ecx, 0x00776390
        mov ecx, [ecx]
        mov eax, 0x0041A639
        call eax
        ret 0x4
        //
            Default:
        mov eax, [ebp - 0x4]
        mov edx, [eax]
        mov ecx, [ebp - 0x4]
        push 0x005ABBBA
        ret


    }
};
void __declspec(naked)FixLoiMaxDoKTC()//00414AFE 6
{
    __asm
    {
        mov ecx, [ebp - 0x2048]
        mov eax,0x0050B05F
        call eax
        and eax,0xFF
        cmp eax,0xFF
        jz MaxHanhTrang
        push 0x4
        mov edx, [ebp - 0x00001C24]
        push 0x00414B06
        ret
        MaxHanhTrang:
        push 0x00414D73
        ret 
    }
};
void __declspec(naked)TestReadFile()//00414AFE 6
{
    __asm
    {
        call ReadLuckBox
        push 0x7D0
        push 0x006B2A51
        ret
    }
};
void __declspec(naked)CheckRealCritNotFunc()//004D76BF 6
{
    __asm
    {
        cmp dword ptr[ebp - 0x4], 0x1
        jle Ad004D76CD
        mov eax,0x1
        push 0x004D76EF
        ret 
        Ad004D76CD:
        push 0x004D76CD
        ret
    }
};
void __declspec(naked)ThemDmgChoBoss()//004BC576 6
{
    __asm
    {
        add eax,0xAFC8
        mov ecx, [ebp + 0x8]
        mov [ecx + 0x4], eax
        push 0x004BC57C
        ret
    }
};
void __declspec(naked)ShowMoreUser()//0060B61E 6
{
    __asm
    {
        cmp dword ptr[ebp - 0x1C], 0x64
        jnl Adr0060B6D2
        push 0x0060B628
        ret 
        Adr0060B6D2:
        push 0x0060B6D2
        ret
    }
};
void __declspec(naked)BypassAddMill()//0050FA9F 6
{
    __asm
    {
        add edx, 0x2FAF0800
        push 0x0050FAA5
        ret
    }
};
int YeuCauDiem [4] = {21000000,23000000,25000000,27000000};
struct GetFailNhanQua
{
    _sHeader			header;
    u_char				ucMessage;
    char				cResult;
    int				SoDiem;
    char    cThongBaoRieng;
    int             nStoreAddressCanTrenClient;
};
void SendRequestKhongDuDiem(int result,int DiemQua)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    GetFailNhanQua pkUserQua;
    __asm
    {
        lea eax, pkUserQua
        mov byte ptr [eax],0xD
        mov byte ptr [eax+0x1], 0x0
        mov byte ptr[eax + 0x2], 0x3B
        mov byte ptr[eax + 0x8], 0xF1
        mov dword ptr[eax + 0x9], 0x00
        mov ecx, result
        mov [eax + 0x3], cl
        mov ecx, DiemQua
        mov[eax + 0x4], ecx
        lea eax, pkUserQua
        mov cx,[eax]
        and cx,0x7FFF
        and ecx,0xFFFF
        push ecx
        lea eax, pkUserQua
        push eax
        mov ecx, StoreECX
        mov eax,0x0069479A
        call eax
    }

}
void __declspec(naked)TruDiemNhanQua()//005ABA81 6
{
    __asm
    {
        mov[ebp - 0x8], eax
        mov eax, 0x007711F2
        movsx eax, [eax]
        cmp eax, 0x11
        jz Default
        mov ecx,[ebp-0x4]
        xor eax,eax
        mov eax,[ecx+0x14]
        cmp eax,0x19F4
        jb Default
        cmp eax,0x19F7
        ja Default
        mov eax, [ebp+0x8]
        xor ecx,ecx
        mov ecx,[eax+0xD621]
        test ecx,ecx
        jz KhongCoDiem
        mov ecx, [ebp - 0x4]
        xor eax, eax
        mov eax, [ecx + 0x14]
        sub eax,0x19F4
        lea ecx, YeuCauDiem
        xor edx,edx
        mov edx,[ecx+eax*0x4]
        mov eax, [ebp + 0x8]
        xor ecx, ecx
        mov ecx, [eax + 0xD621]
        cmp ecx,edx
        jb KhongDuDiem
        sub ecx,edx
        mov eax, [ebp + 0x8]
        mov [eax+0xD621],ecx
        push ecx
        push 0x0
        mov ecx, [ebp + 0x8]
        call SendRequestKhongDuDiem
        add esp,0x8
        Default:
        cmp dword ptr[ebp - 0x8], 0xE
        push 0x005ABA88
        ret


        KhongCoDiem:
        push ecx
        push 0x1
        mov ecx, [ebp + 0x8]
        call SendRequestKhongDuDiem
        add esp, 0x8
        push 0x005ABA9B
        ret 

        KhongDuDiem:
        sub edx,ecx
        push edx
        push 0x2
        mov ecx, [ebp + 0x8]
        call SendRequestKhongDuDiem
        add esp, 0x8
        push 0x005ABA9B
        ret
    }
};
void __declspec(naked)GetGiaTriVaoMapTK()//00492F29 6
{
    __asm
    {
        mov edx, 0x007711F2
        movsx edx, [edx]
        cmp edx, 0xB
        jnz Default
        mov edx, [ebp - 0x0000082C]
        xor eax,eax
        mov al,[edx+0xD625]
        mov[ebp - 0x800], al
        xor eax, eax
        mov eax, [edx + 0xD626]
        mov [ebp - 0x7FE],ax
        push 0x00492F35
        ret

        Default:
        mov edx, [ebp - 0x0000082C]
        mov eax, [edx + 0x00005C5A]
        push 0x00492F2F
        ret 
    }
};
void __declspec(naked)ByPassSaiDoiTuong()//005D5463 6
{
    __asm
    {
        push 0x005D548E
        ret
    }
};
void __declspec(naked)ByPassGMADDSlot96()//0041F381 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x0041F386
        ret
    }
};
void __declspec(naked)ChangeSlotRoom1()//00524CB3 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x00524CB9
        ret
    }
};
void __declspec(naked)ChangeSlotRoom2()//00524D25 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x00524D2B
        ret
    }
};
void __declspec(naked)ChangeSlotRoom3()//00524806 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x0052480C
        ret
    }
};
void __declspec(naked)ChangeSlotRoom4()//00524878 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x0052487E
        ret
    }
};
void __declspec(naked)ChangeSlotRoom5()//005236AF 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x005236B5
        ret
    }
};
void __declspec(naked)ChangeSlotRoom6()//00510229 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x0051022F
        ret
    }
};
void __declspec(naked)ChangeSlotRoom7()//004B2A13 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x004B2A19
        ret
    }
};
void __declspec(naked)ChangeSlotRoom8()//00524057 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x0052405D
        ret
    }
};
void __declspec(naked)ChangeSlotRoom9()//00524028 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x0052402E
        ret
    }
};
void __declspec(naked)ChangeSlotRoom10()//00523FF9 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x00523FFF
        ret
    }
};
void __declspec(naked)ChangeSlotRoom11()//0052368E 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x00523694
        ret
    }
};
void __declspec(naked)ChangeSlotRoom12()//00520460 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x00520466
        ret
    }
};
void __declspec(naked)ChangeSlotRoom13()//00520442 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x00520448
        ret
    }
};
void __declspec(naked)ChangeSlotRoom14()//00520416 6
{
    __asm
    {
        cmp edx, 0x8C
        push 0x0052041C
        ret
    }
};
void __declspec(naked)ChangeSlotRoom15()//0051E234 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x0051E23A
        ret
    }
};
void __declspec(naked)ChangeSlotRoom16()//0050B2E2 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x0050B2E8
        ret
    }
};
void __declspec(naked)ChangeSlotRoom17()//0050AD23 6
{
    __asm
    {
        cmp ecx, 0x8C
        push 0x0050AD29
        ret
    }
};
void __declspec(naked)ChangeSlotRoom18()//00528DE9 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x00528DEE
        ret
    }
};
void __declspec(naked)ChangeSlotRoom19()//005236D0 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x005236D5
        ret
    }
};
void __declspec(naked)ChangeSlotRoom20()//00520E19 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x00520E1E
        ret
    }
};
void __declspec(naked)ChangeSlotRoom21()//0050CF48 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x0050CF4D
        ret
    }
};
void __declspec(naked)ChangeSlotRoom221()//0050ACC4 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x0050ACC9
        ret
    }
};
void __declspec(naked)ChangeSlotRoom22()//0050AC61 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x0050AC66
        ret
    }
};
void __declspec(naked)ChangeSlotRoom23()//00508AF6 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x00508AFB
        ret
    }
};
void __declspec(naked)ChangeSlotRoom24()//004AB8E2 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x004AB8E7
        ret
    }
};
void __declspec(naked)ChangeSlotRoom25()//004AB5B6 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x004AB5BB
        ret
    }
};
void __declspec(naked)ChangeSlotRoom26()//0049255C 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x00492561
        ret
    }
};
void __declspec(naked)ChangeSlotRoom27()//00489D32 6
{
    __asm
    {
        cmp eax, 0x8C
        push 0x00489D37
        ret
    }
};
bool ReadDataPetDao(DataUseItemPet& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InforPet/%d.txt", UniqueID);
    DataUseItemPet* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        FILE* fp = fopen(fname, "w");
        fclose(fp);
        goto OutFun;
    }
    while (1)
    {
        ++iLine;
        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        //rewind(fp);
        sscanf(line, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
            &InnforUserLoad->typePet, &InnforUserLoad->idPet, &InnforUserLoad->level, &InnforUserLoad->statusPet, &InnforUserLoad->idSkill5, &InnforUserLoad->dHonNang, &InnforUserLoad->timedaobatdau, &InnforUserLoad->timedaoofEnd, &InnforUserLoad->MapsDao, &InnforUserLoad->UnknowByte, &InnforUserLoad->typePet1, &InnforUserLoad->idPet1, &InnforUserLoad->level1, &InnforUserLoad->statusPet1, &InnforUserLoad->idSkill51, &InnforUserLoad->dHonNang1, &InnforUserLoad->timedaobatdau1, &InnforUserLoad->timedaoofEnd1, &InnforUserLoad->MapsDao1, &InnforUserLoad->UnknowByte1, &InnforUserLoad->typePet2, &InnforUserLoad->idPet2, &InnforUserLoad->level2, &InnforUserLoad->statusPet2, &InnforUserLoad->idSkill52, &InnforUserLoad->dHonNang2, &InnforUserLoad->timedaobatdau2, &InnforUserLoad->timedaoofEnd2, &InnforUserLoad->MapsDao2, &InnforUserLoad->UnknowByte2, &InnforUserLoad->typePet3, &InnforUserLoad->idPet3, &InnforUserLoad->level3, &InnforUserLoad->statusPet3, &InnforUserLoad->idSkill53, &InnforUserLoad->dHonNang3, &InnforUserLoad->timedaobatdau3, &InnforUserLoad->timedaoofEnd3, &InnforUserLoad->MapsDao3, &InnforUserLoad->UnknowByte3);

        returninfo = true;
    }
    fclose(fp);
OutFun:
    return returninfo;
}
bool ReadDataPetDaoFromText()
{
    DWORD StoreEcx;
    bool returnresult;
    __asm mov StoreEcx, ecx
    returnresult = false;
    __asm
    {
        xor eax, eax
        mov ecx, StoreEcx
        mov eax, [ecx + 0x1054]
        push eax
        lea eax, [ecx + 0xD5D1]
        push eax
        call ReadDataPetDao
        add esp, 0x8
        push 0x0
        push 0x0
        mov ecx, StoreEcx
        lea ecx, [ecx + 0xD5D1]
        push ecx
        push 0xB4
        mov ecx, StoreEcx
        call SendPackagePetDao
        add esp, 0x10
        CreateNewFile:

    }
    return returnresult;
}
void __declspec(naked)GetInforFromText()//00491403 6
{
    __asm
    {
        mov  ecx, [ebp - 0x134]
        call ReadDataPetDaoFromText
        mov  ecx, [ebp - 0x134]
        call ReadDataSlotFromText
        mov ecx, [ebp + 0x8]
        add ecx, 0x00007BB4
        push 0x0049140C
        ret
    }
};
void __declspec(naked)GetValueTongKim()//004AAAD1 6
{
    __asm
    {
        mov edx, 0x007711F2
        movsx edx, [edx]
        cmp edx, 0xB
        jnz Default
        mov ecx,[ebp - 0xC]
        xor edx,edx
        mov dl,[ecx+0xD625]
        mov [ebp - 0x4], dl
        xor edx, edx
        mov dx, [ecx + 0xD626]
        mov [ebp - 0x2], dx
        push 0x004AAAD7
        ret
        Default:
        mov edx, [ebp + 0x8]
        mov [ebp - 0x4], edx
        push 0x004AAAD7
        ret
    }
};
float nTongToaDo[1][2] =
{ -43.788 ,417.951 };
float nKimToaDo[1][2] =
{ 131.560 ,-422.212 };
void __declspec(naked)GetPozTongKim()//004916EF 6
{
    __asm
    {
        mov edx, 0x007711F2
        movsx edx, [edx]
        cmp edx, 0xB
        jnz Default
        mov ecx, [ebp - 0x00000134]
        xor eax, eax
        mov al,[ecx+0xD625]
        cmp eax,0x1
        jnz ToaDoKim
        lea eax, nTongToaDo
        xor edx, edx
        mov edx, [eax]
        mov[ecx + 0x5bc8], edx
        xor edx, edx
        mov edx, [eax + 0x4]
        mov[ecx + 0x5BCC], edx
        jmp Default
        ToaDoKim:
        cmp eax, 0x2
        jnz Default
        lea eax, nKimToaDo
        xor edx,edx
        mov edx,[eax]
        mov [ecx+0x5bc8],edx
        xor edx, edx
        mov edx, [eax+0x4]
        mov[ecx + 0x5BCC], edx
        Default :
        mov ecx, [ebp - 0x00000134]
        push 0x004916F5
        ret
    }
};
struct Infochar
{
    char pad_0000[138]; //0x0000
};
void SendInforChar(Infochar * ptInfochar)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    Infochar Inforchar;
    memset(&Inforchar, 0, sizeof(Infochar));
    memcpy(&Inforchar, ptInfochar, 138);
    __asm
    {
        mov ecx, StoreECX
        xor eax,eax
        mov al,[ecx+ 0xD63E]
        lea edx, Inforchar
        mov [edx+0x85],al
        xor eax, eax
        mov eax, [ecx + 0xD641]
        mov [edx + 0x86], eax
        mov byte ptr [edx],0x8A
        push 0x8A
        lea edx, Inforchar
        push edx
        mov ecx, StoreECX
        mov eax,0x0069479A
        call eax
    }
}
void __declspec(naked)injectHookCharInfor() // 00493238
{
    __asm
    {
        lea eax, [ebp - 0x824]
        push eax
        mov ecx, [ebp - 0x82C]
        call SendInforChar
        add esp,0x4
        push 0x0049324B
        ret
    }
    
}
int listQuaiPhe[6]{ 6703,6704,6705,6706,6707,6708};
int KiemTraPheCuaQuai(int idMod)
{
    int nPhe;
    nPhe = 0;
    for (int i = 0; i < 6; i++)
    {
        if (listQuaiPhe[i] == idMod)
        {
            if (i <= 2)
            {
                nPhe = 1;
            }
            else
            {
                nPhe = 2;
            }
        }
    }
    return nPhe;
}
void __declspec(naked)KiemTraPheBoQuaDmg()//005874AF 6
{
    __asm
    {
        mov ecx, [ebp - 0xA4]
        xor eax,eax
        mov ax,[ecx+0x14]
        push eax
        call KiemTraPheCuaQuai
        add esp,0x4
        test eax,eax
        jz Default
        mov ecx,[ebp+0x8]
        xor edx,edx
        mov dl,[ecx+0xD625]
        cmp eax,edx
        jz CungPhe
        push 0x0058757C
        ret

        CungPhe:
        push 0x005874CE
        ret

        Default:
        mov edx, [ebp + 0x10]
        xor eax,eax
        mov al, [edx + 0x38]
        push 0x005874B5
        ret
    }
};
void __declspec(naked)KiemTraPheBoQuaDmg2()//0058892D 6
{
    __asm
    {
        mov ecx, [ebp - 0x90]
        xor eax, eax
        mov ax, [ecx + 0x14]
        push eax
        call KiemTraPheCuaQuai
        add esp, 0x4
        test eax, eax
        jz Default
        mov ecx, [ebp + 0x8]
        xor edx, edx
        mov dl, [ecx + 0xD625]
        cmp eax, edx
        jz CungPhe
        push 0x00588958
        ret

        CungPhe :
        push 0x00588948
        ret

        Default :
        mov eax, [ebp + 0xC]
        xor ecx, ecx
        mov cl, [eax + 0x38]
        push 0x00588933
        ret
    }
};
void __declspec(naked)KiemTraPheBoQuaDmg3()//00589395 6
{
    __asm
    {
        mov ecx, [ebp - 0x98]
        xor eax, eax
        mov ax, [ecx + 0x14]
        push eax
        call KiemTraPheCuaQuai
        add esp, 0x4
        test eax, eax
        jz Default
        mov ecx, [ebp + 0x8]
        xor edx, edx
        mov dl, [ecx + 0xD625]
        cmp eax, edx
        jz CungPhe
        push 0x005893C0
        ret

        CungPhe :
        push 0x005893B0
        ret

        Default :
        mov eax, [ebp + 0xC]
        xor ecx, ecx
        mov cl, [eax + 0x38]
        push 0x0058939B
        ret
    }
};
void __declspec(naked)KiemTraRankLevel()//0049B506 6
{
    __asm
    {
        //Kiem tra User đã đủ rảnh chưa
        xor ecx,ecx
        mov cx,[eax + 0x5C54]
        cmp ecx,0xFC
        jbe Default
        xor ecx,ecx
        mov cl,[eax+0xD63E]
        cmp cl,0x5
        jz AcceptUpLevel
        add ecx,0x1
        mov [eax+0xD63E],cl
        mov dword ptr [eax + 0x5C56], 0x0
        mov ecx, [ebp - 0x18]
        call StoreUserDB
        jmp Adr0049B768
        AcceptUpLevel:
        mov byte ptr [eax + 0xD63E], 0x0
        mov ecx, [ebp - 0x18]
        call StoreUserDB
        push 0x0049B512
        ret

        Adr0049B768:
        push 0x0049B768
        ret

        Default:
        mov ecx, [edx + 0x5C56]
        cmp ecx, [eax + 0x5CB0]
        push 0x0049B50C
        ret

    }
};
void __declspec(naked)ChangeTypeLevelUp()//005F6EC6 6
{
    __asm
    {
        lea edx, [ebp - 0x7C]
        mov ecx, [ebp - 0x60]
        xor eax,eax
        mov al,[ecx+0xD63E]
        test eax,eax
        jz Default
        add eax,0x10
        mov [edx+0x9],al
        Default:
        lea edx, [ebp - 0x7C]
        push edx
        mov ecx, [ebp - 0x60]
        push 0x005F6ECD
        ret
    }
};
void __declspec(naked)KiemTraMuaShop()//0050BA69 6
{
    __asm
    {
        xor ecx,ecx
        mov ecx,[ebp+0x8]
        xor eax,eax
        mov ax,[ecx+0x4]
        cmp eax,0x3B29
        jnz Default
        mov ecx, [ebp - 0xC]
        xor eax,eax
        mov eax,[ecx+0xD641]
        mov ecx, [ebp + 0x8]
        cmp eax, [ecx + 0xB]
        jnb Adr0050BA93
        push 0x0050BA79
        ret

        Adr0050BA93:
        push 0x0050BA93
        ret

        Default:
        mov ecx, [ebp - 0xC]
        mov eax,0x0050F9E2
        call eax
        push 0x0050BA71
        ret
    }
};
void __declspec(naked)KiemTraMuaShopBoQuaTruTien()//0050BB3F 6
{
    __asm
    {
        mov ecx,[ebp+0x8]
        xor eax,eax
        mov ax,[ecx+0x4]
        cmp eax, 0x3B29
        jnz Default
        mov ecx, [ebp - 0xC]
        xor eax, eax
        mov eax, [ecx + 0xD641]
        mov ecx, [ebp + 0x8]
        sub eax, [ecx + 0xB]
        mov ecx, [ebp - 0xC]
        mov[ecx + 0xD641], eax
        push 0x0050BB58
        ret

        Default:
        push 0x1
        mov ecx, [ebp - 0xC]
        push 0x0050BB44
        ret
    }
};
void __declspec(naked)KiemTraMuaShopBoQuaTruTien2()//0050BD16 6
{
    __asm
    {
        mov ecx, [ebp + 0x8]
        xor eax, eax
        mov ax, [ecx + 0x4]
        cmp eax, 0x3B29
        jnz Default
        mov ecx, [ebp - 0xC]
        xor eax,eax
        mov eax,[ecx+0xD641]
        mov ecx, [ebp + 0x8]
        sub eax,[ecx+0xB]
        mov ecx, [ebp - 0xC]
        mov [ecx+0xD641],eax
        push 0x0050BD2F
        ret

        Default :
        push 0x1
        mov ecx, [ebp - 0xC]
        push 0x0050BD1B
        ret
    }
};
struct InforBuyDiemTichLuy
{
    char pad_0000[103]; //0x0000
};
void SendInforMoneyChar(InforBuyDiemTichLuy* ptInfochar)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    InforBuyDiemTichLuy Inforchar;
    memset(&Inforchar, 0, sizeof(InforBuyDiemTichLuy));
    memcpy(&Inforchar, ptInfochar, 99);
    __asm
    {
        mov ecx, StoreECX
        xor eax, eax
        mov eax, [ecx + 0xD641]
        lea edx, Inforchar
        mov[edx + 0x63], eax
        mov byte ptr[edx], 0x67
        push 0x67
        lea edx, Inforchar
        push edx
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
}
void __declspec(naked)SendMoneyAfterBuy()//005E30D1 6
{
    __asm
    {
        xor eax, eax
        mov ecx,[ebp-0xE960]
        mov ax, [ecx + 0x4]
        cmp eax, 0x3B29
        jnz Default
        lea ecx, [ebp - 0x0000E9C4]
        push ecx
        mov ecx, [ebp - 0x00000DBC]
        call SendInforMoneyChar
        add esp,0x4
        push 0x005E30E4
        ret

        Default :
        mov ax, [ebp - 0xE9C4]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push eax
        lea ecx, [ebp - 0x0000E9C4]
        push 0x005E30D8
        ret
    }
};
void __declspec(naked)Giam1NuaDmg()//005941BB 6
{
    __asm
    {
        lea eax, giamdmg
        fmul dword ptr[eax]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax,0x006E5A28
        call eax
        push 0x005941C0
        ret
    }
};
void __declspec(naked)Giam1NuaDmg2()//00594316 6
{
    __asm
    {
        lea eax, giamdmg
        fmul dword ptr[eax]
        mov eax, 0x0070104C
        fdiv dword ptr[eax]
        mov eax, 0x006E5A28
        call eax
        push 0x0059431B
        ret
    }
};
struct InforInventorySlot
{
    char pad_0000[8]; //0x0000
    char Type1; //0x0008
    char Type2; //0x0009
    u_short idItem; //0x000A
    char pad_000C[44]; //0x000C
    u_short Option5; //0x0038
    u_short Valu5; //0x003A
    char pad_003C[1]; //0x003C
    u_short Option6; //0x003D
    u_short Valu6; //0x003F
    char pad_0041[1]; //0x0041
    u_short Option7; //0x0042
    u_short Valu7; //0x0044
    char pad_0046[1]; //0x0046
    u_short Option8; //0x0047
    u_short Valu8; //0x0049
    char pad_004B[1]; //0x004B
    u_short Option9; //0x004C
    u_short Valu9; //0x004E
    char pad_0050[1]; //0x0050
    u_short Option10; //0x0051
    u_short Valu10; //0x0053
    char pad_0055[11]; //0x0055


};
int InchantNewOptForItem(int SlotItemNeed,int Slot1ItemTarget,int type)
{
    DWORD StoreECX;
    int resultProcess = 0;
    __asm mov StoreECX,ecx
    char typeItem = 0;
    InforInventorySlot* pkUserSlot;
    __asm
    {
        xor eax,eax
        mov eax, Slot1ItemTarget
        imul eax,0x60
        mov ecx, StoreECX
        lea eax,[ecx+0x128C+eax]
        lea ecx, pkUserSlot
        mov [ecx],eax
    }
    if (*(&pkUserSlot->Type1) == 1)//Quan Ao
    {
        resultProcess = 211;
        if (*(&pkUserSlot->Option5) == 0)
        {
            //Chua co gia tri
            srand(timeGetTime());
            int Tile = rand() % 10000;
            if (Tile > 9500)
            {
                if (type == 113)
                {
                    pkUserSlot->Option5 = 720;
                    pkUserSlot->Valu5 = 10;
                }
                else if (type == 114)
                {
                    pkUserSlot->Option5 = 65;
                    pkUserSlot->Valu5 = 1;
                }
                else if (type == 115)
                {
                    pkUserSlot->Option5 = 41;
                    pkUserSlot->Valu5 = 1;
                }
                else if (type == 116)
                {
                    
                    pkUserSlot->Option5 = 227;
                    pkUserSlot->Valu5 = 100;
                }
                resultProcess = 214;
            }
            
        }
        else
        {
            if (type == 113 && *(&pkUserSlot->Option5) == 720)
            {
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9500)
                {
                    pkUserSlot->Valu5 = *(&pkUserSlot->Valu5) + 10;
                    resultProcess = 214;
                }
            }
            else if (type == 114 && *(&pkUserSlot->Option5) == 65)
            {
                if (*(&pkUserSlot->Valu5) > 10)
                {
                    resultProcess = 213;
                    return resultProcess;
                }
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9500)
                {
                    pkUserSlot->Valu5 = *(&pkUserSlot->Valu5) + 1;
                    resultProcess = 214;
                }
            }   
            else if (type == 115 && *(&pkUserSlot->Option5) == 41)
            {
                if (*(&pkUserSlot->Valu5) > 10)
                {
                    resultProcess = 213;
                    return resultProcess;
                }
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9500)
                {
                    pkUserSlot->Valu5 = *(&pkUserSlot->Valu5) + 1;
                    resultProcess = 214;
                }
            }
            else if (type == 116 && *(&pkUserSlot->Option5) == 227)
            {
                if (*(&pkUserSlot->Valu5) > 1000)
                {
                    resultProcess = 213;
                    return resultProcess;
                }
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9500)
                {
                    pkUserSlot->Valu5 = *(&pkUserSlot->Valu5) + 100;
                    resultProcess = 214;
                }
            }
            else
            {
                resultProcess = 213;
                return resultProcess;
            }
            
        }
        return resultProcess;
    }
    else if (*(&pkUserSlot->Type1) == 119)//Vu khi
    {
        resultProcess = 212;
        if (*(&pkUserSlot->Option7) == 0)
        {
            //Chua co gia tri
            srand(timeGetTime());
            int Tile = rand() % 10000;
            if (Tile > 9000)
            {
                if (type == 117)
                {
                    pkUserSlot->Option7 = 134;
                    pkUserSlot->Valu7 = 10;
                }
                else if (type == 118)
                {
                    pkUserSlot->Option7 = 67;
                    pkUserSlot->Valu7 = 10;
                }
                else if (type == 119)
                {
                    pkUserSlot->Option7 = 836;
                    pkUserSlot->Valu7 = 100;
                }
                else if (type == 120)
                {
                    pkUserSlot->Option7 = 830;
                    pkUserSlot->Valu7 = 1;
                }
                resultProcess = 215;
            }

        }
        else
        {
            if (type == 117 && *(&pkUserSlot->Option7) == 134)
            {
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9000)
                {
                    pkUserSlot->Valu7 = *(&pkUserSlot->Valu7) + 10;
                    resultProcess = 215;
                }
            }
            else if (type == 118 && *(&pkUserSlot->Option7) == 67)
            {
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9000)
                {
                    pkUserSlot->Valu7 = *(&pkUserSlot->Valu7) + 10;
                    resultProcess = 215;
                }
            }
            else if (type == 119 && *(&pkUserSlot->Option7) == 836)
            {
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9000)
                {
                    pkUserSlot->Valu7 = *(&pkUserSlot->Valu7) + 100;
                    resultProcess = 215;
                }
            }
            else if (type == 120 && *(&pkUserSlot->Option7) == 830)
            {
                srand(timeGetTime());
                int Tile = rand() % 10000;
                if (Tile > 9000)
                {
                    pkUserSlot->Valu7 = *(&pkUserSlot->Valu7) + 1;
                    resultProcess = 215;
                }
            }
            else
            {
                resultProcess = 213;
            }

        }
        return resultProcess;
    }
    else
    {
        return resultProcess;
    }
    return resultProcess;
}
struct PackageInChant
{
    u_short	usLength;
    u_char	cMessage;
    u_char  ucMode;
    u_char  InforReport;
    u_char UpdTargetSlot;
    u_short TypeOpt;
    u_short ValueOpt;
    u_char UpdNeedItemSlot;
    u_char UpdCountItem;
    u_int cdMoney;
};
int ListValuePhongAn[29][6] =
{
    {3,2,4,6,8,10},
    {3,2,4,6,8,10},
    {3,2,4,6,8,10},
    {15,1,2,3,5,7},
    {16,1,2,3,5,7},
    {15,1,2,3,5,7},
    {15,1,2,3,5,7},
    {16,1,2,3,5,7},
    {16,1,2,3,5,7},
    {16,1,2,3,5,7},
    {15,1,2,3,5,7},
    {47,1,2,3,4,6},
    {48,1,2,3,4,6},
    {53,1,2,3,4,6},
    {54,1,2,3,4,6},
    {54,1,2,3,4,6},
    {63,1,2,3,5,7},
    {93,1,2,3,4,6},
    {95,1,2,3,4,6},
    {219,1,2,3,4,5},
    {134,1,2,3,4,7},
    {138,1,2,3,4,6},
    {23,100,200,300,400,600},
    {24,100,200,300,400,600},
    {144,1,2,3,4,6},
    {145,1,2,3,4,6},
    {214,1,2,3,4,6},
    {144,1,2,3,4,6},
    {145,1,2,3,4,6},
};
void SendInforInchantNewOption(int TypeRepot,int ItemNeedtSlot,int slotTarget)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    PackageInChant pkSendUser;

    if (TypeRepot == 200)
    {
        // Khong Du Tien
        __asm
        {
            lea eax, pkSendUser
            mov word ptr [eax],0x10
            mov byte ptr [eax+0x2], 0x7C
            mov byte ptr [eax + 0x3], 0xC8
            mov dword ptr[eax + 0x4], 0x0
            mov dword ptr[eax + 0x8], 0x0
            mov dword ptr[eax + 0xC], 0x0
            lea eax, pkSendUser
            mov cx,[eax]
            and cx,0x7FFF
            and ecx,0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax,0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 201)
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xC9
            mov dword ptr[eax + 0x4], 0x0
            mov dword ptr[eax + 0x8], 0x0
            mov dword ptr[eax + 0xC], 0x0
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 202)
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xCA
            mov dword ptr[eax + 0x4], 0x0
            mov dword ptr[eax + 0x8], 0x0
            mov dword ptr[eax + 0xC], 0x0
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 203)
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xCB
            mov dword ptr[eax + 0x4], 0x0
            mov dword ptr[eax + 0x8], 0x0
            mov dword ptr[eax + 0xC], 0x0
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 211)//That Bai Quan Ao
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xD3
            mov ecx, slotTarget
            mov [eax + 0x5], cl
            imul ecx,0x60
            mov edx, StoreECX
            lea edx,[edx+ecx+0x128C]
            xor ecx,ecx
            mov cx,[edx+0x38]
            mov [eax+0x6],cx
            xor ecx, ecx
            mov cx, [edx + 0x3A]
            mov[eax + 0x8], cx
            mov ecx, ItemNeedtSlot
            mov[eax + 0xA], cl
            imul ecx, 0x60
            mov edx, StoreECX
            lea edx, [edx + ecx + 0x128C]
            xor ecx, ecx
            mov cl, [edx + 0xF]
            mov[eax + 0xB], cl
            mov ecx, StoreECX
            mov eax, 0x0050F9E2
            call eax
            lea ecx, pkSendUser
            mov [ecx+0xC],eax
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 212)//That Bai Vu Khi
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xD4
            mov ecx, slotTarget
            mov[eax + 0x5], cl
            imul ecx, 0x60
            mov edx, StoreECX
            lea edx, [edx + ecx + 0x128C]
            xor ecx, ecx
            mov cx, [edx + 0x42]
            mov[eax + 0x6], cx
            xor ecx, ecx
            mov cx, [edx + 0x44]
            mov[eax + 0x8], cx
            mov ecx, ItemNeedtSlot
            mov[eax + 0xA], cl
            imul ecx, 0x60
            mov edx, StoreECX
            lea edx, [edx + ecx + 0x128C]
            xor ecx, ecx
            mov cl, [edx + 0xF]
            mov[eax + 0xB], cl
            mov ecx, StoreECX
            mov eax, 0x0050F9E2
            call eax
            lea ecx, pkSendUser
            mov[ecx + 0xC], eax
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 213)//Khong Ro Nguyen Nhan
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xD5
            mov dword ptr[eax + 0x4], 0x0
            mov dword ptr[eax + 0x8], 0x0
            mov dword ptr[eax + 0xC], 0x0
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 214)//Thanh Cong Quan Ao
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xD6
            mov ecx, slotTarget
            mov[eax + 0x5], cl
            imul ecx, 0x60
            mov edx, StoreECX
            lea edx, [edx + ecx + 0x128C]
            xor ecx, ecx
            mov cx, [edx + 0x38]
            mov[eax + 0x6], cx
            xor ecx, ecx
            mov cx, [edx + 0x3A]
            mov[eax + 0x8], cx
            mov ecx, ItemNeedtSlot
            mov[eax + 0xA], cl
            imul ecx, 0x60
            mov edx, StoreECX
            lea edx, [edx + ecx + 0x128C]
            xor ecx, ecx
            mov cl, [edx + 0xF]
            mov[eax + 0xB], cl
            mov ecx, StoreECX
            mov eax, 0x0050F9E2
            call eax
            lea ecx, pkSendUser
            mov[ecx + 0xC], eax
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (TypeRepot == 215)//Thanh Cong Vu Khi
    {
        __asm
        {
            lea eax, pkSendUser
            mov word ptr[eax], 0x10
            mov byte ptr[eax + 0x2], 0x7C
            mov byte ptr[eax + 0x3], 0xD7
            mov ecx, slotTarget
            mov[eax + 0x5], cl
            imul ecx, 0x60
            mov edx, StoreECX
            lea edx, [edx + ecx + 0x128C]
            xor ecx, ecx
            mov cx, [edx + 0x42]
            mov[eax + 0x6], cx
            xor ecx, ecx
            mov cx, [edx + 0x44]
            mov[eax + 0x8], cx
            mov ecx, ItemNeedtSlot
            mov[eax + 0xA], cl
            imul ecx, 0x60
            mov edx, StoreECX
            lea edx, [edx + ecx + 0x128C]
            xor ecx, ecx
            mov cl, [edx + 0xF]
            mov[eax + 0xB], cl
            mov ecx, StoreECX
            mov eax, 0x0050F9E2
            call eax
            lea ecx, pkSendUser
            mov[ecx + 0xC], eax
            lea eax, pkSendUser
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, pkSendUser
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
}
int MoRongTinVat( int slotTinVat)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int resultback = 0;
    int loopcheckSlot = 0;
    srand(timeGetTime());
    int Tile = rand() % 10000;
    if (Tile >= 8000)
    {
        //Thanh Cong
        __asm
        {
            LoopCheckValue:
            mov ecx, slotTinVat
            imul ecx,0x60
            mov eax, StoreECX
            xor edx,edx
            lea eax,[eax+0x128C+ecx]
            mov ecx, loopcheckSlot
            imul ecx,0x5
            xor edx,edx
            mov dl,[eax+0x24+ecx+0x4]
            test edx,edx
            jnz InceaseCheckAnotherValue
            mov byte ptr [eax + 0x24 + ecx + 0x4],0x1
            lea eax, resultback
            mov[eax], 0x1
            jmp EndFuncMoRong
            InceaseCheckAnotherValue:
            mov ecx, loopcheckSlot
            add ecx,0x1
            lea eax, loopcheckSlot
            mov [eax],ecx
            cmp ecx,0x6
            jb LoopCheckValue
            lea eax, resultback
            mov [eax],0x2
            EndFuncMoRong:
        }
        return resultback;
    }
    return 0x0;
}
int ChangeOptTinVat( int slotTinVat,int SlotOption, int RankItem)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    srand(timeGetTime());
    int OptionChoose = rand() % 29;
    int OptRank;
   // OptionChoose = OptionChoose + 1;
    if (RankItem == 1)
    {
        __asm
        {
            mov ecx, slotTinVat
            imul ecx,0x60
            mov eax, StoreECX
            lea eax,[eax+ecx+0x128C+0x24]
            mov ecx, SlotOption
            sub ecx,0x1
            imul ecx,0x5
            lea eax,[eax+ecx]
            lea edx, ListValuePhongAn
            mov ecx, OptionChoose
            imul ecx,0x18
            lea edx,[edx+ecx]
            xor ecx,ecx
            mov ecx,[edx]
            mov [eax],cx
            xor ecx, ecx
            mov ecx, [edx+0x4]
            mov[eax + 0x2], cx
            mov[eax + 0x4], 0x11
        }
        //std::cout << OptionChoose << " | " << OptRank << std::endl;
        return 0x3;
    }
    else if (RankItem == 2)
    {
        srand(timeGetTime());
        int RandomOpt = rand() % 100;
        if (RandomOpt <= 40 && RandomOpt >=0)
        {
            OptRank = 0;
        }
        else if (RandomOpt > 40 && RandomOpt <= 65 )
        {
            OptRank = 1;
        }
        else if (RandomOpt > 65 && RandomOpt <= 85)
        {
            OptRank = 2;
        }
        else if (RandomOpt > 85 && RandomOpt <= 95)
        {
            OptRank = 3;
        }
        else if (RandomOpt > 95 && RandomOpt <= 100)
        {
            OptRank = 4;
        }
        __asm
        {
            mov ecx, slotTinVat
            imul ecx, 0x60
            mov eax, StoreECX
            lea eax, [eax + ecx + 0x128C + 0x24]
            mov ecx, SlotOption
            sub ecx, 0x1
            imul ecx, 0x5
            lea eax, [eax + ecx]
            lea edx, ListValuePhongAn
            mov ecx, OptionChoose
            imul ecx, 0x18
            lea edx, [edx + ecx]
            xor ecx, ecx
            mov ecx, [edx]
            mov[eax], cx
            xor ecx, ecx
            mov ecx, OptRank
            mov ecx, [edx + 0x4 + ecx*0x4]
            mov[eax + 0x2], cx
            mov ecx, OptRank
            cmp ecx,0x0
            jnz CheckRank2
            mov ecx,0x11
            jmp AddRankToitem

            CheckRank2:
            cmp ecx,0x1
            jnz CheckRank3
            mov ecx, 0x12
            jmp AddRankToitem

            CheckRank3:
            cmp ecx,0x2
            jnz CheckRank4
            mov ecx, 0x13
            jmp AddRankToitem

            CheckRank4:
            cmp ecx, 0x3
            jnz CheckRank5
            mov ecx, 0x14
            jmp AddRankToitem

            CheckRank5 :
            cmp ecx, 0x4
            jnz UnknowRank
            mov ecx, 0x15
            jmp AddRankToitem

            UnknowRank:
            mov ecx, 0x11
            AddRankToitem:
            mov[eax + 0x4], cl
        }
        //std::cout << OptionChoose << " | " << OptRank << std::endl;
        return 0x3;
    }
    else if (RankItem == 3)
    {
        srand(timeGetTime());
        int RandomOpt = rand() % 100;
        if (RandomOpt <= 30 && RandomOpt >= 0)
        {
            OptRank = 0;
        }
        else if (RandomOpt > 30 && RandomOpt <= 55)
        {
            OptRank = 1;
        }
        else if (RandomOpt > 55 && RandomOpt <= 80)
        {
            OptRank = 2;
        }
        else if (RandomOpt > 80 && RandomOpt <= 95)
        {
            OptRank = 3;
        }
        else if (RandomOpt > 95 && RandomOpt <= 100)
        {
            OptRank = 4;
        }
        __asm
        {
            mov ecx, slotTinVat
            imul ecx, 0x60
            mov eax, StoreECX
            lea eax, [eax + ecx + 0x128C + 0x24]
            mov ecx, SlotOption
            sub ecx, 0x1
            imul ecx, 0x5
            lea eax, [eax + ecx]
            lea edx, ListValuePhongAn
            mov ecx, OptionChoose
            imul ecx, 0x18
            lea edx, [edx + ecx]
            xor ecx, ecx
            mov ecx, [edx]
            mov[eax], cx
            xor ecx, ecx
            mov ecx, OptRank
            mov ecx, [edx + 0x4 + ecx * 0x4]
            mov[eax + 0x2], cx
            mov ecx, OptRank
            cmp ecx, 0x0
            jnz CheckRank21
            mov ecx, 0x11
            jmp AddRankToitem1

            CheckRank21 :
            cmp ecx, 0x1
                jnz CheckRank31
                mov ecx, 0x12
                jmp AddRankToitem1

                CheckRank31 :
            cmp ecx, 0x2
                jnz CheckRank41
                mov ecx, 0x13
                jmp AddRankToitem1

                CheckRank41 :
            cmp ecx, 0x3
            jnz CheckRank51
                mov ecx, 0x14
                jmp AddRankToitem1


                CheckRank51 :
            cmp ecx, 0x4
                jnz UnknowRank1
                mov ecx, 0x15
                jmp AddRankToitem1

                UnknowRank1 :
            mov ecx, 0x11
                AddRankToitem1 :
                mov[eax + 0x4], cl
        }
        //std::cout << OptionChoose << " | " << OptRank << std::endl;
        return 0x3;
    }
}
struct PackagePhongAn
{
    u_short	usLength;
    u_char	cMessage;
    u_char  ucMode;
    u_char  InforReport;//0x4
    u_char UpdTargetSlot;//0x5
    u_short TypeOpt1;//0x6
    u_short ValueOpt1;//0x8
    u_char anotherRank1;//0xA
    u_short TypeOpt2;//0x
    u_short ValueOpt2;
    u_char anotherRank2;
    u_short TypeOpt3;
    u_short ValueOpt3;
    u_char anotherRank3;
    u_short TypeOpt4;
    u_short ValueOpt4;
    u_char anotherRank4;
    u_short TypeOpt5;
    u_short ValueOpt5;
    u_char anotherRank5;
    u_short TypeOpt6;
    u_short ValueOpt6;
    u_char anotherRank6;
    u_char UpdNeedItemSlot;
    u_char UpdCountItem;
    u_int cdMoney;
    u_char UpdNeedItemSlot2;
    u_char UpdCountItem2;
    u_char UpdCountItem3;
};
struct PackageAnti
{
    u_short	usLength;
    u_char	cMessage;
    u_char  ucMode;
    u_char  InforReport;//0x4
};
void SendPackageAnti(int resultCheck)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    PackageAnti userPackageAnti;
    memset((&userPackageAnti), 0, sizeof(PackageAnti));
    userPackageAnti.usLength = sizeof(PackageAnti);
    userPackageAnti.cMessage = 219;
    userPackageAnti.InforReport = static_cast<u_char>(resultCheck);
    __asm
    {
        lea eax, userPackageAnti
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackageAnti
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
}
void SendPackagePhongAn(int SlotVPRequest, int slotTinVat, int InforPackage, int SlotVpRequest2)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    PackagePhongAn userPackagePhongAn;
    memset((&userPackagePhongAn), 0, sizeof(PackagePhongAn));
    if (InforPackage == 0 || InforPackage == 100 || InforPackage == 103 )//Mo Rong
    {
        __asm
        {
            lea eax, userPackagePhongAn
            mov byte ptr[eax], 0x2D
            mov byte ptr[eax + 0x1], 0x0
            mov byte ptr[eax + 0x2], 0x65
            mov ecx, InforPackage
            test ecx,ecx
            jnz TinhNangMoiOther
            mov byte ptr[eax + 0x3], 0xE4
            jmp ContinueOptionTinhNang
            TinhNangMoiOther:
            mov byte ptr[eax + 0x3], 0xEE
            ContinueOptionTinhNang:
            mov ecx, InforPackage
            mov byte ptr[eax + 0x4], cl
            mov eax, 0x0050F9E2
            mov ecx, StoreECX
            call eax
            lea ecx, userPackagePhongAn
            mov[ecx + 0x27], eax
            mov eax, SlotVPRequest
            imul eax, 0x60
            mov ecx, StoreECX
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            test edx, edx
            jnz VanConNguyenLieuTBMoRong
            mov dl, 0xFF
            VanConNguyenLieuTBMoRong:
            lea ecx, userPackagePhongAn
                mov[ecx + 0x26], dl
                //
                mov eax, SlotVpRequest2
                test eax,eax 
                jz KhongCoVpReqeust2
                lea ecx, userPackagePhongAn
                mov[ecx + 0x2B], al
                imul eax, 0x60
                mov ecx, StoreECX
                xor edx, edx
                mov dl, [ecx + eax + 0x128C + 0xF]
                test edx, edx
                jnz VanConNguyenLieuTBVp2
                mov dl, 0xFF
                VanConNguyenLieuTBVp2:
                lea ecx, userPackagePhongAn
                mov[ecx + 0x2C], dl
                KhongCoVpReqeust2:
                mov eax, SlotVPRequest
                mov[ecx + 0x25], al
                mov ecx, StoreECX
                xor edx, edx
                //Get Slot
                mov eax, slotTinVat
                lea ecx, userPackagePhongAn
                mov[ecx + 0x5], al
                imul eax, 0x60
                mov ecx, StoreECX
                lea eax, [eax + ecx + 0x128C]
                //Get Infr Item
                //Option 1
                lea ecx, userPackagePhongAn
                xor edx, edx
                mov dx, [eax + 0x24]
                mov[ecx + 0x6], dx
                //Value 1
                xor edx, edx
                mov dx, [eax + 0x26]
                mov[ecx + 0x8], dx
                //Another Type 1
                xor edx, edx
                mov dl, [eax + 0x28]
                mov[ecx + 0xA], dl
                //Option 2
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5]
                mov[ecx + 0x6 + 0x5], dx
                //Value 2
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5]
                mov[ecx + 0x8 + 0x5], dx
                //Another Type 2
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5]
                mov[ecx + 0xA + 0x5], dl
                //
                //Option 3
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5], dx
                //Value 3
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5], dx
                //Another Type 3
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5], dl
                //Option 4 
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5], dx
                //Value 4
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5], dx
                //Another Type 4
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5], dl
                //Option 5
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 5
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 5
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5], dl
                //Option 6
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 6
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 6
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dl
                lea eax, userPackagePhongAn
                mov cx, [eax]
                and cx, 0x7FFF
                and ecx, 0xFFFF
                push ecx
                lea eax, userPackagePhongAn
                push eax
                mov ecx, StoreECX
                mov eax, 0x0069479A
                call eax
        }
    }
    else if (InforPackage == 1)//Mo Rong Thanh Cong
    {
        __asm {
            lea eax, userPackagePhongAn
            mov byte ptr[eax], 0x2B
            mov byte ptr[eax + 0x1], 0x0
            mov byte ptr[eax + 0x2], 0x65
            mov byte ptr[eax + 0x3], 0xE4
            mov ecx, InforPackage
            mov byte ptr[eax + 0x4], cl
            mov eax, 0x0050F9E2
            mov ecx, StoreECX
            call eax
            lea ecx, userPackagePhongAn
            mov[ecx + 0x27], eax
            mov eax, SlotVPRequest
            imul eax, 0x60
            mov ecx, StoreECX
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            test edx, edx
            jnz VanConNguyenLieu
            mov dl, 0xFF
            VanConNguyenLieu:
            lea ecx, userPackagePhongAn
                mov[ecx + 0x26], dl
                mov eax, SlotVPRequest
                mov[ecx + 0x25], al
                mov ecx, StoreECX
                xor edx, edx
                //Get Slot
                mov eax, slotTinVat
                lea ecx, userPackagePhongAn
                mov[ecx + 0x5], al
                imul eax, 0x60
                mov ecx, StoreECX
                lea eax, [eax + ecx + 0x128C]
                //Get Infr Item
                //Option 1
                lea ecx, userPackagePhongAn
                xor edx, edx
                mov dx, [eax + 0x24]
                mov[ecx + 0x6], dx
                //Value 1
                xor edx, edx
                mov dx, [eax + 0x26]
                mov[ecx + 0x8], dx
                //Another Type 1
                xor edx, edx
                mov dl, [eax + 0x28]
                mov[ecx + 0xA], dl
                //Option 2
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5]
                mov[ecx + 0x6 + 0x5], dx
                //Value 2
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5]
                mov[ecx + 0x8 + 0x5], dx
                //Another Type 2
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5]
                mov[ecx + 0xA + 0x5], dl
                //
                //Option 3
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5], dx
                //Value 3
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5], dx
                //Another Type 3
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5], dl
                //Option 4 
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5], dx
                //Value 4
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5], dx
                //Another Type 4
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5], dl
                //Option 5
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 5
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 5
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5], dl
                //Option 6
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 6
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 6
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dl
                lea eax, userPackagePhongAn
                mov cx, [eax]
                and cx, 0x7FFF
                and ecx, 0xFFFF
                push ecx
                lea eax, userPackagePhongAn
                push eax
                mov ecx, StoreECX
                mov eax, 0x0069479A
                call eax
        }
    }
    else if (InforPackage == 2)//Khong The Mo Rong Them Nua
    {
        __asm {
            lea eax, userPackagePhongAn
            mov byte ptr[eax], 0x2B
            mov byte ptr[eax + 0x1], 0x0
            mov byte ptr[eax + 0x2], 0x65
            mov byte ptr[eax + 0x3], 0xE4
            mov ecx, InforPackage
            mov byte ptr[eax + 0x4], cl
            mov eax, 0x0050F9E2
            mov ecx, StoreECX
            call eax
            lea ecx, userPackagePhongAn
            mov[ecx + 0x27], eax
            mov eax, SlotVPRequest
            imul eax, 0x60
            mov ecx, StoreECX
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            test edx, edx
            jnz VanConNguyenLieuMaxSlot
            mov dl, 0xFF
            VanConNguyenLieuMaxSlot:
            lea ecx, userPackagePhongAn
                mov[ecx + 0x26], dl
                mov eax, SlotVPRequest
                mov[ecx + 0x25], al
                mov ecx, StoreECX
                xor edx, edx
                //Get Slot
                mov eax, slotTinVat
                lea ecx, userPackagePhongAn
                mov[ecx + 0x5], al
                imul eax, 0x60
                mov ecx, StoreECX
                lea eax, [eax + ecx + 0x128C]
                //Get Infr Item
                //Option 1
                lea ecx, userPackagePhongAn
                xor edx, edx
                mov dx, [eax + 0x24]
                mov[ecx + 0x6], dx
                //Value 1
                xor edx, edx
                mov dx, [eax + 0x26]
                mov[ecx + 0x8], dx
                //Another Type 1
                xor edx, edx
                mov dl, [eax + 0x28]
                mov[ecx + 0xA], dl
                //Option 2
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5]
                mov[ecx + 0x6 + 0x5], dx
                //Value 2
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5]
                mov[ecx + 0x8 + 0x5], dx
                //Another Type 2
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5]
                mov[ecx + 0xA + 0x5], dl
                //
                //Option 3
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5], dx
                //Value 3
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5], dx
                //Another Type 3
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5], dl
                //Option 4 
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5], dx
                //Value 4
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5], dx
                //Another Type 4
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5], dl
                //Option 5
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 5
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 5
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5], dl
                //Option 6
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 6
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 6
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dl
                lea eax, userPackagePhongAn
                mov cx, [eax]
                and cx, 0x7FFF
                and ecx, 0xFFFF
                push ecx
                lea eax, userPackagePhongAn
                push eax
                mov ecx, StoreECX
                mov eax, 0x0069479A
                call eax
        }
    }
    else if (InforPackage == 3)//Pha Mo Thanh Cong
    {
        __asm {
            lea eax, userPackagePhongAn
            mov byte ptr[eax], 0x2B
            mov byte ptr[eax + 0x1], 0x0
            mov byte ptr[eax + 0x2], 0x65
            mov byte ptr[eax + 0x3], 0xE4
            mov ecx, InforPackage
            mov byte ptr[eax + 0x4], cl
            mov eax, 0x0050F9E2
            mov ecx, StoreECX
            call eax
            lea ecx, userPackagePhongAn
            mov[ecx + 0x27], eax
            mov eax, SlotVPRequest
            imul eax, 0x60
            mov ecx, StoreECX
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            test edx, edx
            jnz VanConNguyenLieu2
            mov dl, 0xFF
            VanConNguyenLieu2:
            lea ecx, userPackagePhongAn
                mov[ecx + 0x26], dl
                mov eax, SlotVPRequest
                mov[ecx + 0x25], al
                mov ecx, StoreECX
                xor edx, edx
                //Get Slot
                mov eax, slotTinVat
                lea ecx, userPackagePhongAn
                mov[ecx + 0x5], al
                imul eax, 0x60
                mov ecx, StoreECX
                lea eax, [eax + ecx + 0x128C]
                //Get Infr Item
                //Option 1
                lea ecx, userPackagePhongAn
                xor edx, edx
                mov dx, [eax + 0x24]
                mov[ecx + 0x6], dx
                //Value 1
                xor edx, edx
                mov dx, [eax + 0x26]
                mov[ecx + 0x8], dx
                //Another Type 1
                xor edx, edx
                mov dl, [eax + 0x28]
                mov[ecx + 0xA], dl
                //Option 2
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5]
                mov[ecx + 0x6 + 0x5], dx
                //Value 2
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5]
                mov[ecx + 0x8 + 0x5], dx
                //Another Type 2
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5]
                mov[ecx + 0xA + 0x5], dl
                //
                //Option 3
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5], dx
                //Value 3
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5], dx
                //Another Type 3
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5], dl
                //Option 4 
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5], dx
                //Value 4
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5], dx
                //Another Type 4
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5], dl
                //Option 5
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 5
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 5
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5], dl
                //Option 6
                xor edx, edx
                mov dx, [eax + 0x24 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x6 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Value 6
                xor edx, edx
                mov dx, [eax + 0x26 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0x8 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dx
                //Another Type 6
                xor edx, edx
                mov dl, [eax + 0x28 + 0x5 + 0x5 + 0x5 + 0x5 + 0x5]
                mov[ecx + 0xA + 0x5 + 0x5 + 0x5 + 0x5 + 0x5], dl
                lea eax, userPackagePhongAn
                mov cx, [eax]
                and cx, 0x7FFF
                and ecx, 0xFFFF
                push ecx
                lea eax, userPackagePhongAn
                push eax
                mov ecx, StoreECX
                mov eax, 0x0069479A
                call eax
        }
    }
    else if (InforPackage == 4)//Khong Phai Tin Vat
    {
        __asm {
            lea eax, userPackagePhongAn
            mov byte ptr[eax], 0x2B
            mov byte ptr[eax + 0x1], 0x0
            mov byte ptr[eax + 0x2], 0x65
            mov byte ptr[eax + 0x3], 0xE4
            mov ecx, InforPackage
            mov byte ptr[eax + 0x4], cl
                lea eax, userPackagePhongAn
                mov cx, [eax]
                and cx, 0x7FFF
                and ecx, 0xFFFF
                push ecx
                lea eax, userPackagePhongAn
                push eax
                mov ecx, StoreECX
                mov eax, 0x0069479A
                call eax
        }
    }
    else if (InforPackage == 5)//Khong Dung Nguyen Lieu
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xE4
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 6)//Khong Du Nguyen Lieu
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xE4
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 7)//Khong Du Tien
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xE4
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
        }
    }
    else if (InforPackage == 8)//Send Package HuyetLong
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xE4
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        mov eax, SlotVPRequest
        imul eax, 0x60
        mov ecx, StoreECX
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0xF]
        test edx, edx
        jnz VanConNguyenLieuHl
        mov dl, 0xFF
        VanConNguyenLieuHl:
        lea ecx, userPackagePhongAn
        mov[ecx + 0x26], dl
        mov eax, SlotVPRequest
        mov[ecx + 0x25], al
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 9)//Send Package HuyetLong Sai Vp
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xE4
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 10)//Send Package HuyetLong Ko Du Vp
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xE4
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
        }
    }
    else if (InforPackage == 64)//Send Package Rs opt
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        mov eax, 0x0050F9E2
        mov ecx, StoreECX
        call eax
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], eax
        mov eax, SlotVPRequest
        imul eax, 0x60
        mov ecx, StoreECX
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0xF]
        test edx, edx
        jnz VanConNguyenLieuTBRsOPt
        mov dl, 0xFF
        VanConNguyenLieuTBRsOPt:
        lea ecx, userPackagePhongAn
        mov[ecx + 0x26], dl
        mov eax, SlotVPRequest
        mov[ecx + 0x25], al
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
        }
    }
    else if (InforPackage == 65)//Send Package Rs opt
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        mov eax, 0x0050F9E2
        mov ecx, StoreECX
        call eax
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], eax
        mov eax, SlotVPRequest
        imul eax, 0x60
        mov ecx, StoreECX
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0xF]
        test edx, edx
        jnz VanConNguyenLieuTBRsCuonDo
        mov dl, 0xFF
        VanConNguyenLieuTBRsCuonDo:
        lea ecx, userPackagePhongAn
            mov[ecx + 0x26], dl
            mov eax, SlotVPRequest
            mov[ecx + 0x25], al
            mov eax, slotTinVat
            lea ecx, userPackagePhongAn
            mov[ecx + 0x5], al
            mov ecx, StoreECX
            xor edx, edx
            lea eax, userPackagePhongAn
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, userPackagePhongAn
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (InforPackage == 80)//Send Package Phan Giai Vk
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        mov eax, slotTinVat
        lea ecx, userPackagePhongAn
            mov[ecx + 0x5], al
            mov[ecx + 0x26], 0x0
            mov[ecx + 0x25], 0x0
            mov ecx, StoreECX
            xor edx, edx
            lea eax, userPackagePhongAn
            mov cx, [eax]
            and cx, 0x7FFF
            and ecx, 0xFFFF
            push ecx
            lea eax, userPackagePhongAn
            push eax
            mov ecx, StoreECX
            mov eax, 0x0069479A
            call eax
        }
    }
    else if (InforPackage == 213)//Send Package Phan Giai Vk
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 81)//Send Package Phan Giai Vk
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x5], 0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
        }
    }
    else if (InforPackage == 96)//Send Package Sai Vk
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], 0x0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov[ecx + 0x5], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
        }
    }
    else if (InforPackage == 97)//Send Package Khong Dung Nl
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], 0x0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov[ecx + 0x5], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
        }
    }
    else if (InforPackage == 98)//Send Package Khong Du NL
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], 0x0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov[ecx + 0x5], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
        }
    }
    else if (InforPackage == 99)//Send Package Khong Du TInh luyen
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], 0x0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov[ecx + 0x5], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 101)//Send Package Khong Du TInh luyen
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], 0x0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov[ecx + 0x5], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 102)//Send Package Khong Du TInh luyen
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], 0x0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov[ecx + 0x5], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }
    else if (InforPackage == 110)//Send Package Khong Du TInh luyen
    {
    __asm {
        lea eax, userPackagePhongAn
        mov byte ptr[eax], 0x2B
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x65
        mov byte ptr[eax + 0x3], 0xEE
        mov ecx, InforPackage
        mov byte ptr[eax + 0x4], cl
        lea ecx, userPackagePhongAn
        mov[ecx + 0x27], 0x0
        mov[ecx + 0x26], 0x0
        mov[ecx + 0x25], 0x0
        mov[ecx + 0x5], 0x0
        mov ecx, StoreECX
        xor edx, edx
        lea eax, userPackagePhongAn
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, userPackagePhongAn
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
    }

}
void QuayOptQuanAo(int slotQuanAo,int Tinhluyen)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    DWORD TypeOption;
    DWORD ValueOtion;
    srand(timeGetTime());
    int Tile = rand() % 100;
    if (Tile <= 15)
    {
        TypeOption = 3;
        ValueOtion = Tinhluyen;
    }
    else if (Tile >= 16 && Tile <= 30)
    {
        TypeOption = 138;
        ValueOtion = Tinhluyen;
    }
    else if (Tile >= 31 && Tile <= 45)
    {
        TypeOption = 15;
        ValueOtion = Tinhluyen;
    }
    else if (Tile >= 46 && Tile <= 60)
    {
        TypeOption = 16;
        ValueOtion = Tinhluyen;
    }
    else if (Tile >= 61 && Tile <= 75)
    {
        TypeOption = 47;
        ValueOtion = Tinhluyen;
    }
    else if (Tile >= 76 && Tile <= 90)
    {
        TypeOption = 48;
        ValueOtion = Tinhluyen;
    }
    else if (Tile >= 91 && Tile <= 96)
    {
        TypeOption = 134;
        ValueOtion = Tinhluyen;
    }
    else if (Tile >= 97 && Tile <= 99)
    {
        TypeOption = 23;
        ValueOtion = Tinhluyen*100;
    }
    __asm
    {
        mov ecx, StoreECX
        mov eax, slotQuanAo
        imul eax,0x60
        lea edx,[ecx+eax+0x128C]
        mov eax, TypeOption
        mov [edx+0x33],ax
        mov eax, ValueOtion
        mov [edx + 0x35],ax
        mov byte ptr [edx + 0x37],0x1
    }
}
int NangCapOptionVuKhiFunc(int slotVuKhi,int SlotOption)
{
    DWORD StoreECX;
    int resultNangCapOtion;
    __asm mov StoreECX, ecx
    DWORD TypeOption;
    DWORD ValueOtion;
    __asm
    {
        mov ecx, StoreECX
        mov eax, slotVuKhi
        imul eax,0x60
        lea edx,[ecx+eax+0x128C]
        xor eax,eax
        mov ecx, SlotOption
        imul ecx,0x5
        mov ax,[edx+0x24+ecx]
        mov TypeOption,eax
        mov ax, [edx + 0x24 + ecx+0x2]
        mov ValueOtion, eax
    }
    srand(timeGetTime());
    int Tile = rand() % 100;
    if (Tile >= 1)
    {
        if (TypeOption == 23)
        {
            ValueOtion = ValueOtion + 100;
        }
        else
        {
            ValueOtion = ValueOtion + 1;
        }
        resultNangCapOtion = 103;
        __asm
        {
            mov ecx, StoreECX
            mov eax, slotVuKhi
            imul eax, 0x60
            lea edx, [ecx + eax + 0x128C]
            mov ecx, SlotOption
            imul ecx, 0x5
            mov eax, TypeOption
            mov[edx+ecx+0x24], ax
            mov eax, ValueOtion
            mov[edx+ecx+0x24+0x2], ax
            xor eax, eax
            mov al, [edx + ecx + 0x24+0x4]
            add eax, 0x10
            mov[edx + ecx + 0x24 + 0x4], al
        }
    }
    else
    {
        resultNangCapOtion = 110;
    }
    return resultNangCapOtion;
}
int gettotalcount(int levelrank)
{
    if (levelrank < 0x10)
    {
        return 0;
    }
    else if (levelrank < 0x20)
    {
        return 1;
    }
    else if (levelrank < 0x30)
    {
        return 2;
    }
    else if (levelrank < 0x40)
    {
        return 3;
    }
    else if (levelrank < 0x50)
    {
        return 4;
    }
    else if (levelrank < 0x60)
    {
        return 5;
    }
    else if (levelrank < 0x70)
    {
        return 6;
    }
    else if (levelrank < 0x80)
    {
        return 7;
    }
    else if (levelrank < 0x90)
    {
        return 8;
    }
    else if (levelrank < 0xA0)
    {
        return 9;
    }
}
int GetNumberKH(int levelrank)
{
    if (levelrank < 0x10)
    {
        return 1;
    }
    else if (levelrank < 0x20)
    {
        return 2;
    }
    else if (levelrank < 0x30)
    {
        return 3;
    }
    else if (levelrank < 0x40)
    {
        return 4;
    }
    else if (levelrank < 0x50)
    {
        return 5;
    }
    else if (levelrank < 0x60)
    {
        return 6;
    }
    else if (levelrank < 0x70)
    {
        return 7;
    }
    else if (levelrank < 0x80)
    {
        return 8;
    }
    else if (levelrank < 0x90)
    {
        return 9;
    }
    else if (levelrank < 0xA0)
    {
        return 10;
    }
}
int ListVpRequestOption[33][2]
{
    {3,758},
    {11,768},
    {12,778},
    {13,788},
    {14,798},
    {15,808},
    {16,818},
    {47,828},
    {48,838},
    {49,848},
    {50,858},
    {51,868},
    {52,878},
    {53,888},
    {54,898},
    {55,908},
    {56,918},
    {61,928},
    {63,938},
    {93,948},
    {95,958},
    {96,968},
    {134,978},
    {138,988},
    {23,998},
    {144,1008},
    {145,1018},
    {208,1038},
    {209,1048},
    {211,1068},
    {212,1078},
    {213,1088},
    {214,1098},
};
int KiemTraDieuKienVatPhamNcOption(int LevelRank, int OptionChon, int vpDa, int vpthem)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int tempCheck;
    int resultCheck;
    resultCheck = 0;
    int idCheckvo;
    int idCheckvo2;
    int idCheckcountvo2;
    __asm
    {
        mov eax, vpDa
        imul eax, 0x60
        xor edx, edx
        mov ecx, StoreECX
        mov dx, [ecx + eax + 0x128C + 0xA]
        mov idCheckvo, edx
        //
        mov eax, vpthem
        imul eax, 0x60
        xor edx, edx
        mov ecx, StoreECX
        mov dx, [ecx + eax + 0x128C + 0xA]
        mov idCheckvo2, edx
        xor edx, edx
        mov dl, [ecx + eax + 0x128C + 0xF]
        mov idCheckcountvo2, edx
    }
    for (int i = 0; i < 33; i++)
    {
        if (OptionChon == ListVpRequestOption[i][0])
        {
            tempCheck = ListVpRequestOption[i][1];
            int temidCheckvo = 0;
            if (LevelRank >= 0x10)
            {
                temidCheckvo = idCheckvo - gettotalcount(LevelRank);
            }
            else
            {
                temidCheckvo = idCheckvo;
            }
            if (tempCheck == temidCheckvo)
            {
                if (idCheckvo2 == 3397)
                {

                    int totalitemcount = GetNumberKH(LevelRank) * 5;
                    if (idCheckcountvo2 >= totalitemcount)
                    {
                        resultCheck = 1;
                    }
                }

            }
        }
    }
    return resultCheck;
}
bool KiemTraThongTinPet(int typePet, int idPet)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int totalcount = 0;
    int loopcheck;
    bool resultGetInforPet = false;
    __asm
    {
        xor ecx, ecx
        mov eax, StoreECX
        mov loopcheck, ecx
        lea eax, [eax + 0xD5D1]
        LoopbackCheck:
        mov ecx, loopcheck
            imul ecx, 0x14
            xor edx, edx
            mov dx, [eax + ecx]
            test edx, edx
            jnz CheckNextPet
            mov edx, typePet
            mov[eax + ecx], dx
            mov edx, idPet
            mov[eax + ecx + 0x2], dx
            xor edx, edx
            mov[eax + ecx + 0x4], edx
            mov[eax + ecx + 0x8], edx
            mov[eax + ecx + 0xC], edx
            mov[eax + ecx + 0x10], edx
            mov edx, 0x1
            mov resultGetInforPet, dl
            jmp EndFuncGetPet
            CheckNextPet :
        mov ecx, loopcheck
            add ecx, 0x1
            mov loopcheck, ecx
            cmp ecx, 0x4
            jb LoopbackCheck
            EndFuncGetPet :
    }
    return resultGetInforPet;
}
int ListPet[20][5] =
{ // 1 id item , 2 type, 3 idmod, 4  skill, 5 iditem phong an
    {1183,1,3453,8277,1205},
    {1184,1,3454,8278,1210},
    {1185,1,3455,8279,1215},
    {1186,1,3456,8280,1220},
    {1187,1,3457,8281,1225},
    {1188,1,3458,8282,1230},
    {1189,1,3459,8283,1235},
    {1190,1,3460,8284,1240},
    {1191,1,3461,8285,1250},
    {1192,1,3462,8286,1255},
    {1193,1,3463,8295,0},
    {1194,1,3464,8298,0},
    {1195,1,3465,8301,0},
    {1196,1,3466,8302,1260},
    {1197,1,3467,8303,1265},
    {1198,2,3468,8304,1270},
    {1199,2,3469,8305,1275},
    {1200,2,3470,8306,1280},
    {1201,2,3471,8314,0},
    {1202,2,3472,8315,0},

};
int ProcessUpgradeLevelPet(int LevelCurPet, int vitriPet)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    srand(timeGetTime());
    int Tile = rand() % 100;
    int thanhcong = 0;
    switch (LevelCurPet)
    {
    case 1:
        if (Tile > 30)
        {
            thanhcong = 1;
        }
        else
        {
            thanhcong = 0;
        }
        break;
    case 2:
        if (Tile > 40)
        {
            thanhcong = 1;
        }
        else
        {
            thanhcong = 0;
        }
        break;
    case 3:
        if (Tile > 60)
        {
            thanhcong = 1;
        }
        else
        {
            thanhcong = 0;
        }
        break;
    case 4:
        if (Tile > 70)
        {
            thanhcong = 1;
        }
        else
        {
            thanhcong = 0;
        }
        break;
    case 5:
        return 1;
    default:
        return 3;
        break;
    }
    if (thanhcong == 1)
    {
        __asm
        {
            mov ecx, StoreECX
            lea ecx, [ecx + 0xD5D1]
            mov eax, vitriPet
            imul eax, 0x14
            xor edx, edx
            mov dl, [ecx + eax + 0x4]
            add edx, 0x1
            mov[ecx + eax + 0x4], dl
        }
        return 0;
    }
    else if (thanhcong == 0)
    {
        __asm
        {
            mov ecx, StoreECX
            lea ecx, [ecx + 0xD5D1]
            mov eax, vitriPet
            imul eax, 0x14
            xor edx, edx
            mov dl, [ecx + eax + 0x4]
            cmp edx, 0x1
            jz KhongTruLvKhiThatBai
            sub edx, 0x1
            mov[ecx + eax + 0x4], dl
            KhongTruLvKhiThatBai :

        }
        return 2;
    }


}
void ProcessAddFoodPet(int vitriPet, int levelPet, int honnangCur, int idVpThucAn)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int totalHonNang = 0;
    switch (idVpThucAn)
    {
    case 252:
        totalHonNang = honnangCur + 10; break;
    case 253:
        totalHonNang = honnangCur + 50; break;
    case 254:
        totalHonNang = honnangCur + 100; break;
    default:
        break;
    }
    switch (levelPet)
    {
    case 1:
        if (totalHonNang > 200)
        {
            totalHonNang = 200;
        }
        break;
    case 2:
        if (totalHonNang > 300)
        {
            totalHonNang = 300;
        }
        break;
    case 3:
        if (totalHonNang > 400)
        {
            totalHonNang = 400;
        }
        break;
    case 4:
        if (totalHonNang > 500)
        {
            totalHonNang = 500;
        }
        break;
    case 5:
        if (totalHonNang > 600)
        {
            totalHonNang = 600;
        }
        break;
    default:
        break;
    }
    __asm
    {
        mov ecx, StoreECX
        lea ecx, [ecx + 0xD5D1]
        mov eax, vitriPet
        imul eax, 0x14
        xor edx, edx
        mov edx, totalHonNang
        mov[ecx + eax + 0x8], dx
    }

}
struct DataPetPhongAn {
    unsigned short typePet;
    unsigned short idPet;
    unsigned char level;
    unsigned char statusPet;
    u_short idSkill5;
    u_short dHonNang;
    unsigned int timedaobatdau;
    unsigned int timedaoofEnd;
    u_char MapsDao;
    u_char UnknowByte;
};
int SearchAndGetInforPet(DataPetPhongAn& PetGet, unsigned long long uniqueID_ItemPet)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char fname[200];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InforPet/PhongAnPet/%llu.txt", uniqueID_ItemPet);
    DataPetPhongAn* InforOnePet;
    InforOnePet = &PetGet;
    int iLine = 0;
    char line[256];
    bool returninfo;
    returninfo = false;
    string filname;
    FILE* fp = fopen(fname, "r");
    if (fp)
    {
        return 2;
        fclose(fp);
    }
    FILE* fp1 = fopen(fname, "w");
    if (fp1)
    {
        fprintf(fp1, "%u %u %u %u %u %u %u %u %u %u",
            InforOnePet->typePet, InforOnePet->idPet, InforOnePet->level, InforOnePet->statusPet, InforOnePet->idSkill5, InforOnePet->dHonNang, InforOnePet->timedaobatdau, InforOnePet->timedaoofEnd, InforOnePet->MapsDao, InforOnePet->UnknowByte
        );
        fclose(fp1);
        InforOnePet->typePet = 0;
        InforOnePet->idPet = 0;
        InforOnePet->level = 0;
        InforOnePet->statusPet = 0;
        InforOnePet->idSkill5 = 0;
        InforOnePet->dHonNang = 0;
        InforOnePet->timedaobatdau = 0;
        InforOnePet->timedaoofEnd = 0;
        InforOnePet->MapsDao = 0;
        InforOnePet->UnknowByte = 0;
        return 1;
    }
    else
    {
        std::cout << "Error Phong An Pet " << uniqueID_ItemPet << std::endl;
        return 0;
    }
}
int GetInforPetFromText(unsigned long long uniqueID_ItemPet, DataPetPhongAn& AddressPetEmpty)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char fname[200];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InforPet/PhongAnPet/%llu.txt", uniqueID_ItemPet);
    DataPetPhongAn* InforOnePet;
    InforOnePet = &AddressPetEmpty;
    int iLine = 0;
    char line[256];
    bool returninfo;
    returninfo = false;
    string filname;
    FILE* fp = fopen(fname, "r");
    if (!fp)
    {
        return 1;
    }
    while (1)
    {
        ++iLine;
        if (fgets(line, 256, fp) == NULL)
        {
            break;
        }
        if (!isdigit(line[0]))
        {
            continue;
        }
        //rewind(fp);
        sscanf(line, "%hu %hu %hhu %hhu %hu %hu %u %u %hhu %hhu",
            &InforOnePet->typePet, &InforOnePet->idPet, &InforOnePet->level, &InforOnePet->statusPet, &InforOnePet->idSkill5, &InforOnePet->dHonNang, &InforOnePet->timedaobatdau, &InforOnePet->timedaoofEnd, &InforOnePet->MapsDao, &InforOnePet->UnknowByte);
    }
    fclose(fp);
    if (remove(fname) != 0)
    {
        std::cout << "Remove Txt Error Pet" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Remove Txt Success" << std::endl;
        return 0;
    }
}
int AddPetPhongAnforUser(int IdPet, int Levelpet)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char Listpackage[100];
    int slot = 0;
    int idPet;
    int IdPetAdd = 0;
    memset(&Listpackage, 0, 100);
    Listpackage[0] = 96;
    Listpackage[2] = 80;
    for (int i = 0; i < 20; i++)
    {
        if (IdPet == ListPet[i][0])
        {
            IdPetAdd = ListPet[i][4];
            IdPetAdd = IdPetAdd + Levelpet - 1;
        }
    }
    __asm
    {
        push 0x1
        mov eax, IdPetAdd
        push eax
        push 0x9
        lea eax, Listpackage
        push eax
        mov ecx, StoreECX
        mov eax, 0x00509EF3
        call eax
        mov slot, eax
    }
    return slot;
}
int AddQuaChoDao(int typeItem, int idItem, int count)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char Listpackage[100];
    int slot = 0;
    int idPet;
    int IdPetAdd = 0;
    memset(&Listpackage, 0, 100);
    Listpackage[0] = 96;
    Listpackage[2] = 80;
    __asm
    {
        mov eax, count
        push 0x1
        mov eax, idItem
        push eax
        mov eax, typeItem
        push eax
        lea eax, Listpackage
        push eax
        mov ecx, StoreECX
        mov eax, 0x00509EF3
        call eax
        mov slot, eax
    }
    return slot;
}
int AddItemPhanGiaiVK(int typeItem, int idItem, int count)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    char Listpackage[100];
    int slot = 0;
    int idPet;
    int IdPetAdd = 0;
    memset(&Listpackage, 0, 100);
    Listpackage[0] = 96;
    Listpackage[2] = 80;
    __asm
    {
        mov eax, count
        push eax
        mov eax, idItem
        push eax
        mov eax, typeItem
        push eax
        lea eax, Listpackage
        push eax
        mov ecx, StoreECX
        mov eax, 0x00509EF3
        call eax
        mov slot, eax
    }
    return slot;
}
int listIdBuffPetDefault[4] = { 8275,8274,8272,8271 };
bool FindBuffAndDelete()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int idBuffPet;
    for (int i = 0; i < 4; i++)
    {
        idBuffPet = listIdBuffPetDefault[i];
        __asm
        {
            mov eax, idBuffPet
            push eax
            mov ecx, StoreECX
            mov eax, 0x00506BF0
            call eax
            test eax, eax
            jz KoCoBuff
            push 0xE1
            mov eax, idBuffPet
            push eax
            mov ecx, StoreECX
            mov eax, 0x004ECA80
            call eax
            pop eax
            KoCoBuff :
        }
    }
}

int BuffPetForUser(int loaiBuff, DataPetPhongAn& PetChooseBuff, int HoaNangPet, int levelPet, int idPet)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int leftHonNang = 0;
    int idBuff;
    switch (loaiBuff)
    {
    case 1: // Buff 1
        if (levelPet >= 1)
        {
            if (HoaNangPet >= 90)
            {
                leftHonNang = HoaNangPet - 90;
                try
                {
                    __asm
                    {
                        mov ecx, StoreECX
                        call FindBuffAndDelete
                        push 0x0
                        push 0x0
                        mov eax, levelPet
                        push eax
                        push 8275
                        mov ecx, StoreECX
                        mov eax, 0x004DB99D
                        call eax
                    }
                }
                catch (const std::exception&)
                {
                    std::cout << "Error Buff Pet 1" << std::endl;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 2:
        if (levelPet >= 1)
        {
            if (HoaNangPet >= 90)
            {
                leftHonNang = HoaNangPet - 90;
                try
                {
                    __asm
                    {
                        mov ecx, StoreECX
                        call FindBuffAndDelete
                        push 0x0
                        push 0x0
                        mov eax, levelPet
                        push eax
                        push 8274
                        mov ecx, StoreECX
                        mov eax, 0x004DB99D
                        call eax
                    }
                }
                catch (const std::exception&)
                {
                    std::cout << "Error Buff Pet 2" << std::endl;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 3:
        if (levelPet >= 3)
        {
            if (HoaNangPet >= 90)
            {
                leftHonNang = HoaNangPet - 90;
                try
                {
                    __asm
                    {
                        mov ecx, StoreECX
                        call FindBuffAndDelete
                        push 0x0
                        push 0x0
                        mov eax, levelPet
                        push eax
                        push 8272
                        mov ecx, StoreECX
                        mov eax, 0x004DB99D
                        call eax
                    }
                }
                catch (const std::exception&)
                {
                    std::cout << "Error Buff Pet 3" << std::endl;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 4:
        if (levelPet >= 4)
        {
            if (HoaNangPet >= 90)
            {
                leftHonNang = HoaNangPet - 90;
                try
                {
                    __asm
                    {
                        mov ecx, StoreECX
                        call FindBuffAndDelete
                        push 0x0
                        push 0x0
                        mov eax, levelPet
                        push eax
                        push 8271
                        mov ecx, StoreECX
                        mov eax, 0x004DB99D
                        call eax
                    }
                }
                catch (const std::exception&)
                {
                    std::cout << "Error Buff Pet 4" << std::endl;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 5:
        if (levelPet >= 5)
        {
            if (HoaNangPet >= 180)
            {
                leftHonNang = HoaNangPet - 180;
                for (int i = 0; i < 20; i++)
                {
                    if (idPet == ListPet[i][0])
                    {
                        idBuff = ListPet[i][3];
                    }
                }
                try
                {
                    __asm
                    {
                        /*mov ecx, StoreECX
                        call FindBuffAndDelete*/
                        push 0x0
                        push 0x0
                        mov eax, levelPet
                        push eax
                        mov eax, idBuff
                        push eax
                        mov ecx, StoreECX
                        mov eax, 0x004DB99D
                        call eax
                    }
                }
                catch (const std::exception&)
                {
                    std::cout << "Error Buff Pet 5" << std::endl;
                }
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    default:
        return 3;
        break;
    }
    __asm
    {
        mov ecx, PetChooseBuff
        mov eax, leftHonNang
        mov[ecx + 0x8], ax
        //

        //
    }
    return 0;
}
int ProcessDaoMapsForPet(int VPDaoPhuTro, int slotVPPhuTro, int MapsDao, DataPetPhongAn& PetChooseDao, int HonNangPet, int LevelPet, int idPet)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int rankTime;
    int bonusPet;
    int timedaolef = 0;
    int leftHonNang = 0;
    switch (MapsDao)
    {
    case 1:
        if (LevelPet >= 1)
        {

            if (HonNangPet >= 200)
            {
                leftHonNang = HonNangPet - 200;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 2:
        if (LevelPet >= 1)
        {

            if (HonNangPet >= 200)
            {
                leftHonNang = HonNangPet - 200;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 3:
        if (LevelPet >= 3)
        {

            if (HonNangPet >= 200)
            {
                leftHonNang = HonNangPet - 200;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 4:
        if (LevelPet >= 4)
        {

            if (HonNangPet >= 200)
            {
                leftHonNang = HonNangPet - 200;
            }
            else
            {
                return 2;
            }
        }
        else
        {
            return 1;
        }
        break;
    case 5:
        if (LevelPet >= 5)
        {
            if (VPDaoPhuTro != 0)
            {
                if (HonNangPet >= 200)
                {
                    leftHonNang = HonNangPet - 200;
                    __asm
                    {
                        mov eax, slotVPPhuTro
                        imul eax, 0x60
                        mov ecx, StoreECX
                        xor edx, edx
                        mov dl, [ecx + 0x128C + eax + 0xF]
                        sub edx, 0x1
                        mov[ecx + 0x128C + eax + 0xF], dl
                        test edx, edx
                        jnz ConVpHoTroDaoPetMaps5
                        mov eax, slotVPPhuTro
                        push eax
                        mov ecx, StoreECX
                        mov eax, 0x004B2960
                        call eax
                        ConVpHoTroDaoPetMaps5 :
                    }
                }
                else
                {
                    return 2;
                }
            }
            else
            {
                return 3;
            }

        }
        else
        {
            return 1;
        }
        break;
    default:
        break;
    }
    for (int i = 0; i < 20; i++)
    {
        if (idPet == ListPet[i][0])
        {
            bonusPet = ListPet[i][1];
        }
    }
    srand(timeGetTime());
    int TilerandomTimes = rand() % 100;
    TilerandomTimes = TilerandomTimes + bonusPet;
    if (TilerandomTimes < 30)
    {
        timedaolef = 3600;
        rankTime = 1;
    }
    else if (TilerandomTimes >= 30 && TilerandomTimes < 65)
    {
        timedaolef = 10800;
        rankTime = 2;
    }
    else if (TilerandomTimes >= 65 && TilerandomTimes < 75)
    {
        timedaolef = 18000;
        rankTime = 3;
    }
    else if (TilerandomTimes >= 75 && TilerandomTimes < 90)
    {
        timedaolef = 25200;
        rankTime = 4;
    }
    else if (TilerandomTimes >= 90 && TilerandomTimes < 97)
    {
        timedaolef = 32400;
        rankTime = 5;
    }
    else if (TilerandomTimes >= 97)
    {
        timedaolef = 39600;
        rankTime = 6;
    }
    time_t timestarDao = time(nullptr);
    DWORD timeDaoStart = (DWORD)timestarDao;
    DWORD timeDaoEnd = timeDaoStart + timedaolef;
    __asm
    {
        mov eax, PetChooseDao
        mov edx, timedaolef;
        mov[eax + 0xA], edx
            mov edx, timeDaoEnd;
        mov[eax + 0xE], edx
            mov byte ptr[eax + 0x5], 0x2
            mov edx, MapsDao
            mov[eax + 0x12], dl
            mov edx, rankTime
            mov[eax + 0x13], dl
            mov edx, leftHonNang
            mov[eax + 0x8], dx
    }
    return 0;

}
int ListQuaMaps1[6][19] =
{
    {1,7,2080,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,7,2080,50,7,2081,50,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,7,2080,25,7,2081,25,7,2082,50,0,0,0,0,0,0,0,0,0},
    {7,7,2080,10,7,2081,15,7,2082,25,7,2083,50,0,0,0,0,0,0},
    {9,7,2080,5,7,2081,5,7,2082,15,7,2083,25,7,2084,50,0,0,0},
    {11,7,2080,2,7,2081,3,7,2082,5,7,2083,15,7,2084,25,7,2085,50},
};
int ListQuaMaps2[6][19] =
{
    {1,7,2086,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,7,2086,60,7,2087,40,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,7,2086,25,7,2087,25,7,2088,50,0,0,0,0,0,0,0,0,0},
    {7,7,2086,10,7,2087,15,7,2088,25,7,2089,50,0,0,0,0,0,0},
    {9,7,2086,5,7,2087,5,7,2088,15,7,2089,25,7,2090,50,0,0,0},
    {11,7,2086,2,7,2087,3,7,2088,5,7,2089,15,7,2090,25,7,2090,50},
};
int ListQuaMaps3[6][19] =
{
    {1,7,2092,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,7,2092,50,7,2093,50,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,7,2092,25,7,2093,25,7,2094,50,0,0,0,0,0,0,0,0,0},
    {7,7,2092,10,7,2093,15,7,2094,25,7,2095,50,0,0,0,0,0,0},
    {9,7,2092,5,7,2093,5,7,2094,15,7,2095,25,7,2096,50,0,0,0},
    {11,7,2092,2,7,2093,3,7,2094,5,7,2095,15,7,2096,25,7,2097,50},
};

int ListQuaMaps4[6][19] =
{
    {1,7,2098,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,7,2098,50,7,2099,50,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,7,2098,25,7,2099,25,7,2100,50,0,0,0,0,0,0,0,0,0},
    {7,7,2098,10,7,2099,15,7,2100,25,7,2101,50,0,0,0,0,0,0},
    {9,7,2098,5,7,2099,5,7,2100,15,7,2101,25,7,2102,50,0,0,0},
    {11,7,2098,2,7,2099,3,7,2100,5,7,2101,15,7,2102,25,7,2103,50},
};
int ListQuaMaps5[6][19] =
{
    {1,7,1940,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,7,1940,50,7,1941,50,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,7,1940,25,7,1941,25,7,1942,50,0,0,0,0,0,0,0,0,0},
    {7,7,1940,10,7,1941,15,7,1942,25,7,1943,50,0,0,0,0,0,0},
    {9,7,1940,5,7,1941,5,7,1942,15,7,1943,25,7,1944,50,0,0,0},
    {11,7,1940,2,7,1941,3,7,1942,5,7,1943,15,7,1944,25,7,1945,50},
};
int ProcessAddQuaPetDap(DataPetPhongAn& PetChooseDao)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    time_t timestarDao = time(nullptr);
    DWORD timeDaoStart = (DWORD)timestarDao;
    DWORD TimeDaoEnd = PetChooseDao.timedaoofEnd;
    char MapsDao = PetChooseDao.MapsDao;
    char ranktime = PetChooseDao.UnknowByte;
    int TypeReward = 0;
    int idItemReward = 0;
    int resultcheck = 0;
    int TileNhanQua = 0;
    if (TimeDaoEnd < timeDaoStart)
    {
        switch (MapsDao)
        {
        case 1:
            srand(timeGetTime());
            TileNhanQua = rand() % 100;
            for (int i = 0; i < 6; i++)
            {
                ranktime = ranktime - 1;
                if (!(ListQuaMaps1[ranktime][i * 3 + 1]))
                {
                    if (ListQuaMaps1[ranktime][i * 3 + 3] >= TileNhanQua)
                    {
                        TypeReward = ListQuaMaps1[ranktime][i * 3 + 1];
                        idItemReward = ListQuaMaps1[ranktime][i * 3 + 2];
                        break;
                    }
                }
                else
                {
                    TypeReward = ListQuaMaps1[ranktime][1];
                    idItemReward = ListQuaMaps1[ranktime][2];
                }
            }
            break;
        case 2:
            srand(timeGetTime());
            TileNhanQua = rand() % 100;
            for (int i = 0; i < 6; i++)
            {
                ranktime = ranktime - 1;
                if (!(ListQuaMaps2[ranktime][i * 3 + 1]))
                {
                    if (ListQuaMaps2[ranktime][i * 3 + 3] >= TileNhanQua)
                    {
                        TypeReward = ListQuaMaps2[ranktime][i * 3 + 1];
                        idItemReward = ListQuaMaps2[ranktime][i * 3 + 2];
                        break;
                    }
                }
                else
                {
                    TypeReward = ListQuaMaps2[ranktime][1];
                    idItemReward = ListQuaMaps2[ranktime][2];
                }
            }
            break;
        case 3:
            srand(timeGetTime());
            TileNhanQua = rand() % 100;
            for (int i = 0; i < 6; i++)
            {
                ranktime = ranktime - 1;
                if (!(ListQuaMaps3[ranktime][i * 3 + 1]))
                {
                    if (ListQuaMaps3[ranktime][i * 3 + 3] >= TileNhanQua)
                    {
                        TypeReward = ListQuaMaps3[ranktime][i * 3 + 1];
                        idItemReward = ListQuaMaps3[ranktime][i * 3 + 2];
                        break;
                    }
                }
                else
                {
                    TypeReward = ListQuaMaps3[ranktime][1];
                    idItemReward = ListQuaMaps3[ranktime][2];
                }
            }
            break;
        case 4:
            srand(timeGetTime());
            TileNhanQua = rand() % 100;
            for (int i = 0; i < 6; i++)
            {
                ranktime = ranktime - 1;
                if (!(ListQuaMaps4[ranktime][i * 3 + 1]))
                {
                    if (ListQuaMaps4[ranktime][i * 3 + 3] >= TileNhanQua)
                    {
                        TypeReward = ListQuaMaps4[ranktime][i * 3 + 1];
                        idItemReward = ListQuaMaps4[ranktime][i * 3 + 2];
                        break;
                    }
                }
                else
                {
                    TypeReward = ListQuaMaps4[ranktime][1];
                    idItemReward = ListQuaMaps4[ranktime][2];
                }
            }
            break;
        case 5:
            srand(timeGetTime());
            TileNhanQua = rand() % 100;
            for (int i = 0; i < 6; i++)
            {
                ranktime = ranktime - 1;
                if (!(ListQuaMaps5[ranktime][i * 3 + 1]))
                {
                    if (ListQuaMaps5[ranktime][i * 3 + 3] >= TileNhanQua)
                    {
                        TypeReward = ListQuaMaps5[ranktime][i * 3 + 1];
                        idItemReward = ListQuaMaps5[ranktime][i * 3 + 2];
                        break;
                    }
                }
                else
                {
                    TypeReward = ListQuaMaps5[ranktime][1];
                    idItemReward = ListQuaMaps5[ranktime][2];
                }
            }
            break;
        default:
            return 2;
            break;
        }
    }
    else
    {
        return 1;
    }
    __asm
    {
        push 0x1
        mov eax, idItemReward
        push eax
        mov eax, TypeReward
        push eax
        mov ecx, StoreECX
        call AddQuaChoDao
        add esp, 0xC
        cmp eax, 0xFF
        jz ErrorAdd
        mov eax, 0x0
        mov resultcheck, eax
        jmp EndFuncAddQuaDao
        ErrorAdd :
        mov eax, 0x3
            mov resultcheck, eax
            EndFuncAddQuaDao :
    }
    return resultcheck;

}
int ProcessSpawnPet(int idPet)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    _point CurPozUser;
    int idPetSpaw;
    int resultSpawnPet = 0;
    __asm
    {
        mov eax, [ecx + 0xD629]
        test eax, eax
        jz EndFuncDisappear
        // Xoa Pet
        mov ecx, eax
        mov eax, 0x00586F11
        call eax
        // Xoa Hieu Ung
        push 0x1
        mov ecx, StoreECX
        mov eax, 0x004F563B
        call eax
        EndFuncDisappear :
        mov ecx, StoreECX
            mov eax, 0x00431F70
            call eax
            fstp CurPozUser.m_posX
            mov ecx, StoreECX
            mov eax, 0x00431F90
            call eax
            fstp CurPozUser.m_posZ
    }

    if (idPet != 0)
    {

        for (int i = 0; i < 20; i++)
        {
            if (ListPet[i][0] == idPet)
            {
                idPetSpaw = ListPet[i][2];
                idPetSpaw = idPetSpaw + 4000;
                __asm
                {
                    push 0x0
                    push 0x0
                    push 0x0
                    lea edx, CurPozUser
                    push edx
                    push 0x0
                    mov eax, idPetSpaw
                    push eax
                    mov eax, 0x00406B10
                    call eax
                    mov ecx, eax
                    mov eax, 0x005BB34D
                    call eax
                    mov ecx, StoreECX
                    mov[ecx + 0xD625], ax
                    xor ecx, ecx
                    mov cx, ax
                    push ecx
                    mov eax, 0x00406B10
                    call eax
                    mov ecx, eax
                    mov eax, 0x0005BBB29
                    call eax
                    xor eax, eax
                    mov ecx, StoreECX
                    mov ax, [ecx + 0xD625]
                    push eax
                    mov eax, 0x00406B10
                    call eax
                    mov ecx, eax
                    mov eax, 0x0040AD70
                    call eax
                    mov ecx, StoreECX
                    mov[ecx + 0xD629], eax
                }
                return 0;
            }
        }
    }
    else
    {
        return 1;
    }
    return 1;
}
void XoaThongTinSpawnKhac(int SlotPet)
{
    DWORD StoreECX;
    int countpet = 0;
    __asm
    {
        mov StoreECX, ecx
        xor ecx, ecx
        mov eax, StoreECX
        lea eax, [eax + 0xD5D1]
        BackLoopCheckPet:
        mov ecx, countpet
            imul ecx, 0x14
            xor edx, edx
            mov dx, [eax + ecx + 0x2]
            test edx, edx
            jz CheckNextPet
            mov ecx, countpet
            mov edx, SlotPet
            cmp edx, ecx
            jz CheckNextPet
            mov ecx, countpet
            imul ecx, 0x14
            xor edx, edx
            mov dl, [eax + ecx + 0x5]
            cmp edx, 0x1
            jnz CheckNextPet
            mov byte ptr[eax + ecx + 0x5], 0x0
            CheckNextPet:
        mov ecx, countpet
            add ecx, 0x1
            mov countpet, ecx
            cmp ecx, 0x4
            jl BackLoopCheckPet

    }

}
int ProcessHuyTrieuHoiPet()
{
    DWORD StoreECX;
    int resultHuyTrieuHoi = 1;
    __asm
    {
        mov StoreECX, ecx
        mov eax, [ecx + 0xD629]
        test eax, eax
        jz EndFuncDisappear
        // Xoa Pet
        mov ecx, eax
        mov eax, 0x00586F11
        call eax
        // Xoa Hieu Ung
        push 0x1
        mov ecx, StoreECX
        mov eax, 0x004F563B
        call eax
        mov ecx, StoreECX
        mov eax, 0x0
        mov resultHuyTrieuHoi, eax
        EndFuncDisappear :
        mov ecx, StoreECX
            mov DWORD PTR[ecx + 0xD625], 0x0
            mov DWORD PTR[ecx + 0xD629], 0x0
    }
}


bool WriteDataPetDao(DataUseItemPet& InnforUser, int UniqueID)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/DBUserInfo/InforPet/%d.txt", UniqueID);
    DataUseItemPet* InnforUserLoad;
    bool returninfo;
    returninfo = false;
    InnforUserLoad = &InnforUser;
    int iLine = 0;
    char line[256];
    string filname;
    FILE* fp = fopen(fname, "w");
    if (fp)
    {
        fprintf(fp, "%u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u",
            InnforUserLoad->typePet, InnforUserLoad->idPet, InnforUserLoad->level, InnforUserLoad->statusPet, InnforUserLoad->idSkill5, InnforUserLoad->dHonNang, InnforUserLoad->timedaobatdau, InnforUserLoad->timedaoofEnd, InnforUserLoad->MapsDao, InnforUserLoad->UnknowByte,
            InnforUserLoad->typePet1, InnforUserLoad->idPet1, InnforUserLoad->level1, InnforUserLoad->statusPet1, InnforUserLoad->idSkill51, InnforUserLoad->dHonNang1, InnforUserLoad->timedaobatdau1, InnforUserLoad->timedaoofEnd1, InnforUserLoad->MapsDao1, InnforUserLoad->UnknowByte1,
            InnforUserLoad->typePet2, InnforUserLoad->idPet2, InnforUserLoad->level2, InnforUserLoad->statusPet2, InnforUserLoad->idSkill52, InnforUserLoad->dHonNang2, InnforUserLoad->timedaobatdau2, InnforUserLoad->timedaoofEnd2, InnforUserLoad->MapsDao2, InnforUserLoad->UnknowByte2,
            InnforUserLoad->typePet3, InnforUserLoad->idPet3, InnforUserLoad->level3, InnforUserLoad->statusPet3, InnforUserLoad->idSkill53, InnforUserLoad->dHonNang3, InnforUserLoad->timedaobatdau3, InnforUserLoad->timedaoofEnd3, InnforUserLoad->MapsDao3, InnforUserLoad->UnknowByte3
        );
        //fwrite(InnforUserLoad, sizeof(int), sizeof(DataUseItem), fp);
        returninfo = true;
        fclose(fp);
    }
    else
    {
        std::cout << "Error Create File and Write" << std::endl;
    }

    return returninfo;
};
int DanhSachVpRank[9][3] =
{
    {0,1,1},
    {1,1,1},
    {2,1,1},
    {3,1,1},
    {4,2,1},
    {5,3,2},
    {6,4,2},
    {7,5,3},
    {8,6,4},
};
void ProcessPhanGiaiVkAdd(int RankItem, int InchantItem)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    for (int i = 0; i < 9; i++)
    {
        if (RankItem == DanhSachVpRank[i][0])
        {
            int countItemadd = 0;
            int IdItem = 0;
            if (InchantItem >= 12)
            {
                 countItemadd = DanhSachVpRank[i][2];
                 IdItem = 1256;
                 countItemadd = countItemadd * InchantItem;
            }
            else
            {
                 countItemadd = DanhSachVpRank[i][1];
                 IdItem = 1255;
                 if (InchantItem == 0)
                 {
                     countItemadd = countItemadd;
                 }
                 else
                 {
                     countItemadd = countItemadd * InchantItem;
                 }
                 
            }
            __asm
            {
                push countItemadd
                push IdItem
                push 7
                mov ecx, StoreECX
                call AddItemPhanGiaiVK
                add esp, 0xC
            }
            break;
        }
    }

}
void BlockAccount(const char * IDUser, int reason)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/Login/nfofile/AutoCheckBlockIP/ListIPBlock.txt");
    char fname2[128];
    sprintf(fname2, "C:/9Dragons/Login/nfofile/AutoCheckBlockIP/Log_ListIPBlock.txt");
    FILE* fp = fopen(fname, "a");
    if (fname)
    {
        //fprintf(fp, "%s\n", IDUser);
        //
        FILE* fp2 = fopen(fname2, "a");
        SYSTEMTIME checktime;
        GetLocalTime(&checktime);
        int years = checktime.wYear;
        int months = checktime.wMonth;
        int days = checktime.wDay;
        int hours = checktime.wHour;
        int minutes = checktime.wMinute;
        if (reason == 1)
        {
            fprintf(fp2, "Block Account ( Reason : Incorrect Masterry ) %d/%d/%d %d:%d : %s\n", years, months, days, hours, minutes, IDUser);
        }
        else if (reason == 2)
        {
            fprintf(fp2, "Block Account ( Reason : Learn Incorrect Masterry ) %d/%d/%d %d:%d : %s\n", years, months, days, hours, minutes, IDUser);
        }
        else if (reason == 3)
        {
            fprintf(fp2, "Block Account ( Not Match SCR Client vs SCR Server ) %d/%d/%d %d:%d : %s\n", years, months, days, hours, minutes, IDUser);
        }
        else if (reason == 4)
        {
            fprintf(fp2, "Block Account ( Not receive Package SCR within 4 minutes ) %d/%d/%d %d:%d : %s\n", years, months, days, hours, minutes, IDUser);
        }
        else if (reason == 5)
        {
            fprintf(fp2, "Block Account ( Not Match the Skill on Server vs Client ) %d/%d/%d %d:%d : %s\n", years, months, days, hours, minutes, IDUser);
        }
        else if (reason == 0)
        {
            fprintf(fp2, "Block Account ( SCR on Client was changed ) %d/%d/%d %d:%d : %s\n", years, months, days, hours, minutes, IDUser);
        }
        else
        {
            fprintf(fp2, "Block Account ( Not Found Reason ) %d/%d/%d %d:%d : %s\n", years, months, days, hours, minutes, IDUser);
        }
        fclose(fp);
        fclose(fp2);

    }
    else
    {
        std::cout << "Error Load File Block" << std::endl;
    }
}
float tang1 = 1.0f;
float tang2 = 2.0f;
float tang3 = 3.0f;
float tang0 = 0.0f;
float GetGiaTangKhoangCachThem(int MonPhai, int ChucTrach)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    float giatricounttang = 1.0f;
    int giatricounttangadd = 0;
    int idSkillForCheck = 0;
    switch (MonPhai)
    {
    case 0:
        idSkillForCheck = -1;
        break;
    case 1:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 75;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 69;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 2:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 110;
        }
        else if (ChucTrach == 7)
        {
            idSkillForCheck = 95;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 3:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 115;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 98;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 4:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 120;
        }
        else if (ChucTrach == 8)
        {
            idSkillForCheck = 101;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 5:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 125;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 104;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 6:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 130;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 107;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    default:
        break;
    }
    if (idSkillForCheck == -1 )
    {
        return tang0;
    }
    for (int i = 0; i < 60; i++)
    {
        __asm
        {
            xor eax,eax
            mov eax,i
            imul eax,0x8
            xor edx,edx
            mov ecx, StoreECX
            mov dx,[ecx+eax]
            mov ecx, idSkillForCheck
            cmp edx,ecx
            jnz CheckNextSkillMastery
            mov ecx, StoreECX
            xor edx,edx
            mov dl,[ecx + eax+0x2]
            mov giatricounttangadd,edx
            CheckNextSkillMastery:
        }
    }
    if (giatricounttangadd == 1)
    {
        return tang1;
    }
    else if(giatricounttangadd == 2)
    {
        return tang2;
    }
    else if(giatricounttangadd == 3)
    {
        return tang3;
    }
    else
    {
        return tang0;
    }
}
int GetGiaTangKhoangCachThemCheck(int MonPhai, int ChucTrach)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    float giatricounttang = 1.0f;
    int giatricounttangadd = 0;
    int idSkillForCheck = 0;
    switch (MonPhai)
    {
    case 0:
        idSkillForCheck = -1;
        break;
    case 1:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 75;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 69;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 2:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 110;
        }
        else if (ChucTrach == 7)
        {
            idSkillForCheck = 95;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 3:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 115;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 98;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 4:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 120;
        }
        else if (ChucTrach == 8)
        {
            idSkillForCheck = 101;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 5:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 125;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 104;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    case 6:
        if (ChucTrach == 1)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 2)
        {
            idSkillForCheck = -1;
        }
        else if (ChucTrach == 3)
        {
            idSkillForCheck = 130;
        }
        else if (ChucTrach == 4)
        {
            idSkillForCheck = 107;
        }
        else
        {
            idSkillForCheck = -1;
        }
        break;
    default:
        break;
    }
    if (idSkillForCheck == -1)
    {
        return 0;
    }
    for (int i = 0; i < 60; i++)
    {
        __asm
        {
            xor eax, eax
            mov eax, i
            imul eax, 0x8
            xor edx, edx
            mov ecx, StoreECX
            mov dx, [ecx + eax]
            mov ecx, idSkillForCheck
            cmp edx, ecx
            jnz CheckNextSkillMastery
            mov ecx, StoreECX
            xor edx, edx
            mov dl, [ecx + eax + 0x2]
            mov giatricounttangadd, edx
            CheckNextSkillMastery :
        }
    }
    if (giatricounttangadd != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int ListSkillGiamDelay[6] = {};
int GetGiaGiamThoiGiaDelaySkill(int MonPhai,int ChucTrach)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int giatricounttang = 0;
    for (int i = 0; i < 60; i++)
    {
        __asm
        {
            xor eax, eax
            mov eax, i
            imul eax, 0x8
            xor edx, edx
            mov ecx, StoreECX
            mov dx, [ecx + eax]
            cmp edx, 102
            jnz CheckNextSkillMastery
            xor edx, edx
            mov dl, [ecx + eax + 0x2]
            mov giatricounttang, edx
            CheckNextSkillMastery:
        }
    }
    return giatricounttang * 1000;
}
bool CheckValueKhoangCach(float client, float addmore, float sv)
{
    if (client != (addmore+sv))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void KickDissUser()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    _point pozUser;
    __asm
    {
        lea eax, pozUser
        push eax
        mov ecx, StoreECX
        mov eax, 0x0049C06D
        call eax
        lea eax, pozUser
        push eax
        push ecx
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov eax, 0x00602064
        call eax
    }
};
FILE* m_PackageFileptr;
BYTE* m_PackageVirtualMemory;
bool OpenSCRandCheck(int sizeofFile, DWORD BeginFile, const char* FilefromClient)
{
    char fname[128];
    bool resultback = false;
    sprintf(fname, "SCR_BASE.XP");
    m_PackageFileptr = fopen(fname, "rb");
    if (!m_PackageFileptr || m_PackageFileptr == NULL)
    {
        std::cout << "Can't Open File " << std::endl;
        return 0;
    }
    //BYTE* m_PackageVirtualMemory;
    m_PackageVirtualMemory = new BYTE[1300];
    if (!m_PackageVirtualMemory)
    {
        std::cout << "Can't Create " << std::endl;
        return 0;
    }
    if (fseek(m_PackageFileptr, BeginFile, SEEK_SET) == 0)
    {
        if (fread(m_PackageVirtualMemory, 1280, 1, m_PackageFileptr) >= 0)
        {
            if (strncmp(reinterpret_cast<const char*>(m_PackageVirtualMemory), FilefromClient, sizeofFile) == 0)
            {
                resultback = true;
            }
        }
    }
    delete[] m_PackageVirtualMemory;
    fclose(m_PackageFileptr);
    return resultback;
};
void DebugLogCheckSkill(int idSkill,int iLevelSkill)
{
    char fname[128];
    sprintf(fname, "C:/9Dragons/Login/nfofile/AutoCheckBlockIP/LogSkill.txt");
    FILE* fp = fopen(fname, "a");
    if (fname)
    {
        SYSTEMTIME checktime;
        GetLocalTime(&checktime);
        int Skill = idSkill;
        int LevelSkill = iLevelSkill;
        int days = checktime.wDay;
        int hours = checktime.wHour;
        int minutes = checktime.wMinute;
        fprintf(fp, "%d:%d \n", Skill, LevelSkill);
        fclose(fp);

    }
    else
    {
        std::cout << "Error Load File Block" << std::endl;
    }
};
struct PackageListComnbine
{
    u_short usLength;
    u_char cMessage;
    u_char cMessage2;
    int ListIDCombineAcceptBook[200];
    int ListIDCombineAcceptBook2[200];
};
void FuncSendPackageListIDCombine()
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    PackageListComnbine ListPackage;
    memset(&ListPackage, 0, sizeof(PackageListComnbine));
    memcpy(&ListPackage.ListIDCombineAcceptBook, &ListDieuCheKhongTacDungSach, 4 * 200);
    memcpy(&ListPackage.ListIDCombineAcceptBook2, &ListDieuCheChoPhepSuDungBua, 4 * 200);
    ListPackage.usLength = sizeof(PackageListComnbine);
    ListPackage.cMessage = 60;
    ListPackage.cMessage2 = 25;

    __asm
    {
        lea eax, ListPackage
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, ListPackage
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
};
struct PackageListWeaponSkill
{
    u_short usLength;
    u_char cMessage;
    u_char cMessage2;
    int ListSkillAddSkill[60][2];
};
void FuncSendPackageWeaponSkill()
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    PackageListWeaponSkill ListPackage;
    memset(&ListPackage, 0, sizeof(PackageListWeaponSkill));
    memcpy(&ListPackage.ListSkillAddSkill, &ListSkillAdd, 8 * 60);
    ListPackage.usLength = sizeof(PackageListWeaponSkill);
    ListPackage.cMessage = 60;
    ListPackage.cMessage2 = 26;

    __asm
    {
        lea eax, ListPackage
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, ListPackage
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
};

void __declspec(naked)NewInchant1()//005E80D0 6
{
    __asm
    {
        xor edx, edx
        mov dl, [ecx + 0x3]
        cmp dl, 0xA5
        jz ResetOptTinhChe
        cmp dl, 0xA6
        jz ResetCuongDo
        cmp dl, 0xA7
        jz cnPhanGiaiVukhi
        cmp dl, 0xA8
        jz cnQuayOptionQuanAo
        cmp dl, 0xA9
        jz cnNangCapOptionVk
        cmp dl, 0xB0
        jz MoPet
        cmp dl, 0xB1
        jz ThucTinhPet
        cmp dl, 0xE1
        jz KhoaTaiKhoanAdr
        /*cmp dl, 0xE7
        jz CheckFileClient*/
        cmp dl, 0xE8
        jz SendPackageListIDCombine
        cmp dl, 0xB2
        jz PhongAnPet
        cmp dl, 0xB3
        jz UpLevelPet
        cmp dl, 0xB4
        jz ThucAnChoPet
        cmp dl, 0xB5
        jz BuffofPet
        /*cmp dl, 0xE5
        jz CheckAntiLevel2*/
        cmp dl, 0xB6
        jz DaoPet
        cmp dl, 0xB7
        jz TrieuHoiPet
        cmp dl, 0xB8
        jz PhaPhongAnPet
        cmp dl, 0xB9
        jz HuyTrieuHoi
        cmp dl, 0xBA
        jz HuyDao
        cmp dl, 0xBB
        jz NhanQuaDaoPet
        cmp dl, 0xBC
        jz MoRongTinVatAdr
        cmp dl, 0xBD
        jz ThayDoiVaPhaBo
        cmp dl, 0x70
        ja NewInchantCloth
        cmp dl, 0x68
        ja NewInchantCloth2

        Default :
        push 0x005E80D5
            ret

            KhoaTaiKhoanAdr:
            mov ecx, [ebp - 0x00000DBC]
            xor eax,eax
            push 0x0
            lea eax,[ecx+0xE74]
            push eax
            call BlockAccount
            add esp, 0x8
            push 0x005E832E
            ret

            SendPackageListIDCombine:
            mov ecx, [ebp - 0x00000DBC]
            call FuncSendPackageListIDCombine
            mov ecx, [ebp - 0x00000DBC]
            call FuncSendPackageWeaponSkill
            push 0x005E832E
            ret

            CheckFileClient:
            mov ecx, [ebp - 0x00000DBC]
            mov byte ptr [ecx+0xED00],0x0
            mov dword ptr[ecx + 0xED01], 0x0
            push 0x005E832E
            ret

            
            CheckAntiLevel2:
            //Kiem Tra Khoang Cach
            sub esp,0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov ax, [ecx + 0x4]
            push eax
            mov ecx, DWORD PTR SS:[0x007763B4]
            mov eax,0x0040EF50
            call eax
            test eax,eax
            jz NotFoundSkillCheck
            fld DWORD PTR [eax+0x3C]
            mov ecx, [ebp - 0x00000DBC]
            xor eax,eax
            mov al, [ecx + 0x1275]
            push eax
            xor eax, eax
            mov al, [ecx + 0x1264]
            push eax
            add ecx,0xA6D4
            call GetGiaTangKhoangCachThemCheck
            add esp,0x8
            //
            test al,al
            jz KhongTruThemKC
            mov ecx, [ebp - 0x00000DBC]
            xor eax, eax
            mov al, [ecx + 0x1275]
            push eax
            xor eax, eax
            mov al, [ecx + 0x1264]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            add ecx, 0xA6D4
            call GetGiaTangKhoangCachThem
            add esp,0x8
            fadd st(0),st(1)
            fstp st(1)
            KhongTruThemKC:

            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov eax,[ecx+0x8]
            push eax
            fld dword ptr [esp]
            fcomp st(1)
            fnstsw  ax
            test ah, 0x41
            jz NotFoundSkillCheck
            pop eax
            fstp st(0)
            // Thoi gian thi trien
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov ax, [ecx + 0x4]
            push eax
            mov ecx, DWORD PTR SS : [0x007763B4]
            mov eax, 0x0040EF50
            call eax
            test eax, eax
            jz NotFoundSkillCheck
            mov [esp],eax
            mov ecx, [ebp - 0x0000F1A0]
            xor edx, edx
            mov dx, [ecx + 0x6]
            imul edx,0x50
            mov ecx,[eax+edx+0x90]
            imul ecx,100
            mov eax, [ebp - 0x0000F1A0]
            xor edx, edx
            mov edx, [eax + 0x10]
            cmp edx,ecx
            jnz NotFoundSkillCheck
            //
            // Thoi gian hoi skill
            mov eax,[esp]
            xor ecx,ecx
            mov cl,[eax+0x17]
            cmp ecx,10
            jz CheckTimeSkillKy
            cmp ecx,8
            jz CheckTimeSkillKy
            cmp ecx,5
            jz CheckTimeSkillKy
            mov ecx, [ebp - 0x0000F1A0]
            xor edx, edx
            mov dx, [ecx + 0x6]
            imul edx, 0x50
            mov ecx, [eax + edx + 0x98]
            mov eax, [esp + 0x4]
            imul ecx, 100
            mov eax, [ebp - 0x0000F1A0]
            xor edx, edx
            mov edx, [eax + 0x14]
            cmp ecx,edx
            jnz NotFoundSkillCheck
            add esp, 0x8
            /*push 5
            mov ecx, [ebp - 0x00000DBC]
            call SendPackageAnti
            add esp, 0x4*/
            push 0x005E832E
            ret

            CheckTimeSkillKy:
            mov ecx, [ebp - 0x0000F1A0]
            xor edx, edx
            mov dx, [ecx + 0x6]
            imul edx, 0x50
            mov ecx, [eax + edx + 0x98]
            mov eax,[esp+0x4]
            imul ecx,100
            mov eax, [ebp - 0x0000F1A0]
            xor edx, edx
            mov edx, [eax + 0x14]
            cmp ecx,edx
            ja NotFoundSkillCheck
            sub ecx,edx
            cmp ecx,3000
            ja NotFoundSkillCheck
            add esp, 0x8
            /*push 5
            mov ecx, [ebp - 0x00000DBC]
            call SendPackageAnti
            add esp, 0x4*/
            push 0x005E832E
            ret

            //
            NotFoundSkillCheck:
            pop eax
            fstp st(0)
            add esp,0x8
            mov ecx, [ebp - 0x00000DBC]
            xor eax, eax
            lea eax, [ecx + 0xE74]
            push 0x5
            push eax
            call BlockAccount
            add esp, 0x8
            mov ecx, [ebp - 0x00000DBC]
            call KickDissUser
           /* push 0
            mov ecx, [ebp - 0x00000DBC]
            call SendPackageAnti
            add esp, 0x4*/
            push 0x005E832E
            ret


            /// <summary>
            /// Chuc nang cua Pet
            /// </summary>
            HuyTrieuHoi:
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            test eax, eax
            jz KhongTimThayPet
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x5]
            cmp edx, 0x1
            jnz PetKhongHuyTrieuHoi
            xor edx, edx
            mov byte ptr[ecx + 0xD5D1 + eax + 0x5], 0x0
            mov ecx, [ebp - 0x00000DBC]
            call ProcessHuyTrieuHoiPet
            cmp eax, 0x0
            jnz KhongTheHuyTrieuHoiPet
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xDD
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhongTheHuyTrieuHoiPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xDF
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PetKhongHuyTrieuHoi :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xDE
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            NhanQuaDaoPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0xD5D1 + 0x5]
            cmp edx, 0x2
            jnz PetHienTaiChuaDao
            xor edx, edx
            lea edx, [ecx + eax + 0xD5D1]
            push edx
            call ProcessAddQuaPetDap
            add esp, 0x4
            cmp eax, 0x1
            jz ChuaDuThoiGianNhanQua
            cmp eax, 0x2
            jz KhongRoLoiNhanQua
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov byte ptr[ecx + eax + 0xD5D1 + 0x5], 0x0
            mov dword ptr[ecx + eax + 0xD5D1 + 0xA], 0x0
            mov dword ptr[ecx + eax + 0xD5D1 + 0xE], 0x0
            mov byte ptr[ecx + eax + 0xD5D1 + 0x12], 0x0
            mov byte ptr[ecx + eax + 0xD5D1 + 0x13], 0x0
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD9
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            ChuaDuThoiGianNhanQua :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD7
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhongRoLoiNhanQua :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD8
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            HuyDao :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0xD5D1 + 0x5]
            cmp edx, 0x2
            jnz PetHienTaiChuaDao
            mov byte ptr[ecx + eax + 0xD5D1 + 0x5], 0x0
            mov dword ptr[ecx + eax + 0xD5D1 + 0xA], 0x0
            mov dword ptr[ecx + eax + 0xD5D1 + 0xE], 0x0
            mov byte ptr[ecx + eax + 0xD5D1 + 0x12], 0x0
            mov byte ptr[ecx + eax + 0xD5D1 + 0x13], 0x0
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD5
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PetHienTaiChuaDao :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD6
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            //
            PhaPhongAnPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0x8]
            cmp edx, 0x9
            jnz nKhongPhaiPet
            //
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            xor edx, edx
            mov dx, [ecx]
            test edx, edx
            jnz KiemTraViTriPet2
            //
            push ecx
            jmp ProcessGetInforPetFromPhongAn
            //
            KiemTraViTriPet2 :
        xor edx, edx
            mov dx, [ecx + 0x14]
            test edx, edx
            jnz KiemTraViTriPet3
            lea ecx, [ecx + 0x14]
            push ecx
            jmp ProcessGetInforPetFromPhongAn

            KiemTraViTriPet3 :
        xor edx, edx
            mov dx, [ecx + 0x28]
            test edx, edx
            jnz KiemTraViTriPet4
            lea ecx, [ecx + 0x28]
            push ecx
            jmp ProcessGetInforPetFromPhongAn

            KiemTraViTriPet4 :
        xor edx, edx
            mov dx, [ecx + 0x3C]
            test edx, edx
            jnz DaMaxGioiHanPet
            lea ecx, [ecx + 0x3C]
            push ecx
            ProcessGetInforPetFromPhongAn :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov edx, [ecx + 0x128C + eax + 0x4]
            push edx
            mov edx, [ecx + 0x128C + eax]
            push edx
            call GetInforPetFromText
            add esp, 0xC
            test eax, eax
            jnz KhongThePhaBoPhongAn
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xC9
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            //
            push 0x005E832E
            ret

            KhongThePhaBoPhongAn :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xCA
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            //
            push 0x005E832E
            ret


            MoPet :
        //Kiem Tra InfoPet
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0x8]
            cmp edx, 0x9
            jnz nKhongPhaiPet
            xor edx, edx
            mov dx, [ecx + 0x128C + eax + 0xA]
            cmp edx, 0x49F
            jb nKhongPhaiPet
            cmp edx, 0x4B2
            ja nKhongPhaiPet
            push edx
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0x8]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call KiemTraThongTinPet
            add esp, 0x8
            cmp al, 0x1
            jnz DaMaxGioiHanPet
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push 0x0
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB1
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            //
            push 0x005E832E
            ret

            ThucTinhPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0x8]
            cmp edx, 0x7
            jnz KhonPhaiVPThucTinhPet
            xor edx, edx
            mov dx, [ecx + 0x128C + eax + 0xA]
            cmp edx, 0x101
            jnz KhonPhaiVPThucTinhPet
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            cmp edx, 0x1
            jb KhongDuSlVpThucTinh
            sub edx, 0x1
            mov[ecx + 0x128C + eax + 0xF], dl
            test edx, edx
            jnz ConVpThucTinh
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConVpThucTinh :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dx, [ecx + eax + 0xD5D1]
            test edx, edx
            jz KhongTimThayPet
            xor edx, edx
            mov dx, [ecx + eax + 0xD5D1 + 0x5]
            test edx, edx
            jnz PetDaThucTinhRoi
            mov byte ptr[ecx + eax + 0xD5D1 + 0x4], 0x1
            mov word ptr[ecx + eax + 0xD5D1 + 0x8], 0xC8
            //
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB8
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PhongAnPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0x8]
            cmp edx, 0x7
            jnz KoDungYeuCauRequestVpPhongAn
            xor edx, edx
            mov dx, [ecx + 0x128C + eax + 0xA]
            cmp edx, 0x103
            jnz KoDungYeuCauRequestVpPhongAn
            xor edx, edx
            mov dx, [ecx + 0x128C + eax + 0xF]
            cmp edx, 0x1
            jb KoDungYeuCauRequestVpPhongAn
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            test eax, eax
            jz KhongTimThayPet
            sub eax, 0x1
            cmp eax, 0x4
            ja KhongTimThayPet
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0xD5D1 + 0x5]
            test edx, edx
            jnz YeuCauPetDungHoatDong
            //
            xor edx, edx
            mov dl, [ecx + eax + 0xD5D1 + 0x4]
            test edx, edx
            jz PhongAnThatBai
            xor edx, edx
            mov dl, [ecx + eax + 0xD5D1 + 0x4]
            push edx
            xor edx, edx
            mov dx, [ecx + eax + 0xD5D1 + 0x2]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call AddPetPhongAnforUser
            add esp, 0x8
            cmp eax, 0xFF
            jz PhongAnThatBai
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov edx, [ecx + 0x128C + eax + 0x4]
            push edx
            xor edx, edx
            mov edx, [ecx + 0x128C + eax]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            lea edx, [ecx + eax + 0xD5D1]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SearchAndGetInforPet
            add esp, 0xC
            cmp al, 0x1
            jnz KiemTraPetTonTaiPhongAn
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            cmp edx, 0x1
            jb PhongAnThatBai
            sub edx, 0x1
            mov[ecx + 0x128C + eax + 0xF], dl
            test edx, edx
            jnz ConVpPhongAnPet
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConVpPhongAnPet :
        //
        mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBD
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KiemTraPetTonTaiPhongAn :
        cmp al, 0x2
            jnz PhongAnThatBai
            push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xCB
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KoDungYeuCauRequestVpPhongAn :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBC
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            YeuCauPetDungHoatDong :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBC
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PhongAnThatBai :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBC
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            TrieuHoiPet :
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            test eax, eax
            jz KhongTimThayPet
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x5]
            test edx, edx
            jnz KhongTheTrieuHoiKhiDangHoatDongKhac
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax + 0x2]
            mov byte ptr[ecx + 0xD5D1 + eax + 0x5], 0x1
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call ProcessSpawnPet
            add esp, 0x4
            cmp eax, 0x1
            jz KhongTheTrieuHoiPet
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub al, 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call XoaThongTinSpawnKhac
            add esp, 0x4
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xDB
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhongTheTrieuHoiPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xDA
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhongTheTrieuHoiKhiDangHoatDongKhac :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xDC
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            UpLevelPet :
        //
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x4]
            cmp edx, 0x5
            jz DaMaxLevelKoTheNangCap
            cmp edx, 0x0
            jz KhongRoLoiNangCapPet
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0x8]
            cmp edx, 0x7
            jnz KoPhaiVpNangCapLv
            xor edx, edx
            mov dx, [ecx + 0x128C + eax + 0xA]
            cmp edx, 0x100
            jnz KoPhaiVpNangCapLv
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            cmp edx, 0x1
            jb KoDuVpNangCapLv
            sub edx, 0x1
            mov[ecx + 0x128C + eax + 0xF], dl
            test edx, edx
            jnz ConVpNangCapPet
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConVpNangCapPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            push eax
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x4]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call ProcessUpgradeLevelPet
            add esp, 0x8
            cmp eax, 0x0
            jnz KiemtrathatainangcapPet
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBA
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KiemtrathatainangcapPet :
        cmp eax, 0x2
            jnz KhongRoLoiNangCapPet
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBB
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret


            ThucAnChoPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0x8]
            cmp edx, 0x7
            jnz KoPhaiThucAnCuaPet
            xor edx, edx
            mov dx, [ecx + 0x128C + eax + 0xA]
            cmp edx, 0xFC
            jz TiepTucFuncThucAnCHoPet
            cmp edx, 0xFD
            jz TiepTucFuncThucAnCHoPet
            cmp edx, 0xFE
            jz TiepTucFuncThucAnCHoPet
            jmp KoPhaiThucAnCuaPet

            TiepTucFuncThucAnCHoPet :
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            cmp edx, 0x1
            jb KoDuSlThucAnPet
            xor edx, edx
            mov dx, [ecx + 0x128C + eax + 0xA]
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            test eax, eax
            jz KhongTimThayPet
            sub eax, 0x1
            push edx
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax + 0x8]
            push edx
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x4]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call ProcessAddFoodPet
            add esp, 0x10
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            sub edx, 0x1
            mov[ecx + 0x128C + eax + 0xF], dl
            test edx, edx
            jnz ConThucAnChoPet
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConThucAnChoPet :
        //
        mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBF
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            DaoPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax]
            test edx, edx
            jz KhongTimThayPet
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax + 0x5]
            test edx, edx
            jnz YeuCauPetKhongHoatDong
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax + 0x2]
            push edx // idPet Dao
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x4]
            push edx // level pet
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax + 0x8]
            push edx // Hon Nang
            xor edx, edx
            lea edx, [ecx + 0xD5D1 + eax]
            push edx // ADdress Pet
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            push eax // Map Dao
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            test eax, eax
            jz KhongCoVpDaoPet
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x7
            jnz KhongCoVpDaoPet
            mov dx, [ecx + eax + 0x128C + 0xA]
            cmp edx, 0xFF
            jnz KhongCoVpDaoPet
            push edx
            jmp ProcessContinuePetDao
            KhongCoVpDaoPet :
            push 0x0
            ProcessContinuePetDao :
            call ProcessDaoMapsForPet
            add esp, 0x1C
            cmp eax, 0x1
            jz KhongDuDieuKienLevelDaoPet
            cmp eax, 0x2
            jz PetKhongDuHonNang
            cmp eax, 0x3
            jz DaoMaps5KhongCoVPHoTro
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD3
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret
            //


        DaoMaps5KhongCoVPHoTro:
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD2
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhongDuDieuKienLevelDaoPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD1
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            YeuCauPetKhongHoatDong :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD4
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            BuffofPet :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            sub eax, 0x1
            imul eax, 0x14
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax]
            test edx, edx
            jz KhongTimThayPet
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x5]
            cmp edx, 0x1
            jnz PetPhaiTrieuHoiMoiBuffDc
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax + 0x2]
            push edx // ID Pet
            xor edx, edx
            mov dl, [ecx + 0xD5D1 + eax + 0x4]
            push edx // Level Pet
            xor edx, edx
            mov dx, [ecx + 0xD5D1 + eax + 0x8]
            push edx // Hoa Nang
            lea ecx, [ecx + 0xD5D1 + eax]
            push ecx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call BuffPetForUser
            add esp, 0x14
            cmp eax, 0x1
            jz PetKhongDulevelDeBuff
            cmp eax, 0x2
            jz PetKhongDuHonNang
            cmp eax, 0x3
            jz KoRoLoiBuffPet
            mov ecx, [ebp - 0x00000DBC]
            mov eax, [ecx + 0x1054]
            push eax
            lea ecx, [ecx + 0xD5D1]
            push ecx
            call WriteDataPetDao
            add esp, 0x8
            push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xCF
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PetKhongDuHonNang :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xCC
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PetKhongDulevelDeBuff :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xCD
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KoRoLoiBuffPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xD0
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret


            //

        KhongRoLoiNangCapPet:
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + 0x128C + eax + 0xF]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xC3
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            DaMaxLevelKoTheNangCap :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xC2
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            NangCapThatBaiPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xBB
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PetPhaiTrieuHoiMoiBuffDc :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xCE
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhonPhaiVPThucTinhPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB5
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KoPhaiVpNangCapLv :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xC0
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KoDuVpNangCapLv :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xC1
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhongDuSlVpThucTinh :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB9
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            PetDaThucTinhRoi :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB7
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KhongTimThayPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB6
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            DaMaxGioiHanPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB3
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KoPhaiThucAnCuaPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xC4
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            KoDuSlThucAnPet :
        push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xC6
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret

            nKhongPhaiPet :
            push 0x0
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + 0xD5D1]
            push ecx
            push 0xB2
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePetDao
            add esp, 0x10
            push 0x005E832E
            ret


            cnPhanGiaiVukhi :
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 19
            jz AcceptVuKhiPhanGiai19
            cmp edx, 0
            jz AcceptVuKhiPhanGiai0
            jmp TrangBiNayKhongThePhanGiai

            AcceptVuKhiPhanGiai19 :
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            cmp edx,12016
            jb ProcessContinuePhanGiai
            cmp edx, 12025
            ja ProcessContinuePhanGiai
            jmp TrangBiNayKhongThePhanGiai

            ProcessContinuePhanGiai:
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x18]
            push edx
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            push edx
            mov ecx, DWORD PTR SS:[0x00776388]
            mov eax,0x004D8460
            call eax
            jmp ProcessAddItemPhanGiai
            AcceptVuKhiPhanGiai0:
            //Add VP
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x18]
            push edx
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            push edx
            mov ecx, DWORD PTR SS : [0x00776388]
            mov eax,0x004D81C0
            call eax
            ProcessAddItemPhanGiai:
            xor ecx,ecx
            mov cl,[eax+0x1F]
            push ecx // RankItem
            mov ecx, [ebp - 0x00000DBC]
            call ProcessPhanGiaiVkAdd
            add esp,0x8
            // Xoa Vu Khi
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            push 0x0
            push 0x50
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            TrangBiNayKhongThePhanGiai:
            push 0x0
            push 0x51
            push 0
            push 0
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            cnQuayOptionQuanAo :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x1
            jnz KhongPhaiQuanAo
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x18]
            cmp edx, 0x8
            jb KhongDuTinhLuyenTnMoi
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            cmp eax, 0x4C4B40
            jb KhongDuTien
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0xA
            jnz KhongDungNguyenLieu
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            cmp edx, 0x59
            jnz KhongDungNguyenLieu
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            cmp edx, 0x1
            jb KhongDuNguyenLieuTnMoi
            sub edx, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            jnz ConnguyenLieuQuayopt
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConnguyenLieuQuayopt :
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            sub eax, 0x4C4B40
            push 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x50FA03
            call eax
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            mov ecx, [ebp - 0x00000DBC]
            imul eax, 0x60
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x18]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call QuayOptQuanAo
            add esp, 0x8
            //Send package Quay opt
            push 0x0
            push 0x64
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            KhongPhaiVuKhi :
        push 0x0
            push 0x60
            push 0x0
            push 0x00
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            KhongPhaiQuanAo :
        push 0x0
            push 0x65
            push 0x0
            push 0x00
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            KhongDuTinhLuyenTnMoi :
        push 0x0
            push 0x63
            push 0x0
            push 0x00
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            KhongDungNguyenLieu :
        push 0x0
            push 0x61
            push 0x0
            push 0x00
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            KhongDuNguyenLieuTnMoi :
        push 0x0
            push 0x62
            push 0x0
            push 0x00
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            MaxGioiHanNangCapOption :
        push 0x0
            push 0x66
            push 0x0
            push 0x00
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            cnNangCapOptionVk :
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x13
            jnz KhongPhaiVuKhi
            xor edx, edx
            lea edx, [ecx + eax + 0x128C]
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x7]
            sub eax, 0x1
            imul eax, 0x5
            xor ecx, ecx
            mov cl, [edx + 0x24 + eax + 0x4]
            cmp ecx, 0xA0
            jae MaxGioiHanNangCapOption
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            cmp eax, 0x1312D00
            jb KhongDuTien
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x7
            jnz KhongDungNguyenLieu
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x7
            jnz KhongDungNguyenLieu
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            push eax
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            lea edx, [ecx + eax + 0x128C]
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x7]
            xor ecx, ecx
            sub eax, 0x1
            imul eax, 0x5
            mov cx, [edx + eax + 0x24]
            push ecx
            xor ecx, ecx
            mov cl, [edx + eax + 0x24 + 0x4]
            push ecx
            mov ecx, [ebp - 0x00000DBC]
            call KiemTraDieuKienVatPhamNcOption
            add esp, 0x10
            cmp eax, 0x1
            jnz KhongDungNguyenLieu
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            mov ecx, [ebp - 0x00000DBC]
            imul eax, 0x60
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            cmp edx, 0x1
            jb KhongDuNguyenLieuTnMoi
            sub edx, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            jnz ConnguyenlieuDaOption
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            //
            ConnguyenlieuDaOption :
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            imul eax, 0x60
            xor edx, edx
            mov ecx, [ebp - 0x00000DBC]
            lea ecx, [ecx + eax + 0x128C]
            mov dl, [ecx + 0xF]
            push edx
            //Get Count
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            lea edx, [ecx + eax + 0x128C]
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x7]
            xor ecx, ecx
            sub eax, 0x1
            imul eax, 0x5
            mov cl, [edx + eax + 0x24 + 0x4]
            push ecx
            call GetNumberKH
            add esp, 0x4
            imul eax, 0x5
            pop edx
            //
            cmp edx, eax
            jb KhongDuNguyenLieuTnMoi
            sub edx, eax
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            jnz ConnguyenLieuVpThemOptionVk
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConnguyenLieuVpThemOptionVk :
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            sub eax, 0x1312D00
            push 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x50FA03
            call eax
            //
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x7]
            sub al, 0x1
            push eax
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call NangCapOptionVuKhiFunc
            add esp, 0x8
            mov edx, eax
            //Send package Quay opt
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            push eax
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret



        ResetOptTinhChe:
        mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            cmp eax, 0x1312D00
            jb KhongDuTien
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x13
            jnz KhongPhaiVuKhiRs
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0xA
            jnz KhongPhaiHuyetLong
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            cmp edx, 78
            jnz KhongPhaiHuyetLong
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            test edx, edx
            jbe KhongDuNguyenLieuHL
            sub edx, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            ja ConNguyenLieuRSOption
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConNguyenLieuRSOption :
        push 0x0
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            push edx
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            push 0x0
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004A257B
            call eax
            and eax, 0x000000FF
            test eax, eax
            jz SendInforRSOptionItem
            mov ecx, [ebp - 0x00000DBC]
            add ecx, 0x1058
            push ecx
            push 0x0071D6D0
            mov eax, 0x006A01DF
            call eax
            add esp, 0x8
            SendInforRSOptionItem:
        mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            sub eax, 0x1312D00
            push 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x50FA03
            call eax
            push 0x0
            push 0x40
            push 0x0
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            ResetCuongDo :
        mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            cmp eax, 0x2625A00
            jb KhongDuTien
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x13
            jnz KhongPhaiVuKhiRs
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0xA
            jnz KhongPhaiHuyetLong
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            cmp edx, 77
            jnz KhongPhaiHuyetLong
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            test edx, edx
            jz KhongDuNguyenLieuHL
            sub edx, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            ja ConNguyenLieuRSCD
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConNguyenLieuRSCD :
        mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x4]
            imul edx, 0x60
            mov ecx, [ebp - 0x00000DBC]
            mov byte ptr[ecx + edx + 0x128C + 0x1C], 0x0
            mov byte ptr[ecx + edx + 0x128C + 0x1D], 0x23
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            sub eax, 0x2625A00
            push 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x50FA03
            call eax
            push 0x0
            push 0x41
            mov ecx, [ebp - 0x0000F1A0]
            xor edx, edx
            mov dl, [ecx + 0x4]
            push edx
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret


            NewInchantCloth2 :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0xB]
            test eax, eax
            jz KhongCoBaoHo
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0xA
            jnz KhongPhaiHuyetLong
            xor edx, edx
            mov dx, [ecx + eax + 0x128C + 0xA]
            cmp edx, 0x62
            jnz KhongPhaiHuyetLong
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            cmp edx, 0x0
            jbe KhongDuNguyenLieuHL
            sub edx, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            cmp edx, 0x0
            jnz Conguyenlieuhuyetlong
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0xB]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            Conguyenlieuhuyetlong :
        push 0x0
            push 0x8
            push 0x0
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0xB]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            KhongCoBaoHo:
        push 0x005E80FD
            ret


            KhongPhaiHuyetLong :
        push 0x0
            push 0x9
            push 0x0
            push 0x0
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            KhongDuNguyenLieuHL :
        push 0x0
            push 0xA
            push 0x0
            push 0x0
            call SendPackagePhongAn
            add esp, 0x10
            push 0x005E832E
            ret

            NewInchantCloth :
        cmp dl, 0x80
            ja EndFunc
            xor edx, edx
            mov dl, [ecx + 0x5]
            imul edx, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor eax, eax
            mov al, [ecx + edx + 0x128C + 0x8]
            cmp eax, 0x7
            jnz Default
            xor eax, eax
            mov ax, [ecx + edx + 0x128C + 0xA]
            cmp eax, 0x2F6
            jl OptNewGmae
            cmp eax, 0x453
            ja OptNewGmae
            mov ecx, [ebp - 0x0000F1A0]
            mov byte ptr[ecx + 0x3], 0x0
            xor edx, edx
            mov dl, [ecx + 0x3]
            jmp Default

            OptNewGmae :
        mov eax, 0x0050F9E2
            call eax
            cmp eax, 0x2625A00
            jbe KhongDuTien
            //Kiem Tra Tinh Luyen
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x4]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x8]
            cmp edx, 0x1
            jnz KiemTraVuKhiTinhLuyen
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x18]
            cmp edx, 0xF
            jl KhongDuTinhLuyen
            jmp DaKiemTraTinhLuyen

            KiemTraVuKhiTinhLuyen :
        cmp edx, 0x13
            jmp KhongRoloi
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0x18]
            cmp edx, 0x12
            jl KhongDuTinhLuyen
            DaKiemTraTinhLuyen :
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            cmp edx, 0x0
            jle KhongDuNguyenLieu
            //Tru Tien
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            sub eax, 0x2625A00
            push 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x50FA03
            call eax
            //Tru Nguyen Lieu
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            sub dl, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            jnz ConNguyenLieu
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConNguyenLieu :
        //
        mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x3]
            push eax
            xor eax, eax
            mov al, [ecx + 0x4]
            push eax
            xor eax, eax
            mov al, [ecx + 0x5]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call InchantNewOptForItem
            add esp, 0xC
            mov ecx, [ebp - 0x0000F1A0]
            xor edx, edx
            mov dl, [ecx + 0x4]
            push edx
            xor edx, edx
            mov dl, [ecx + 0x5]
            push edx
            push eax
            mov ecx, [ebp - 0x00000DBC]
            call SendInforInchantNewOption
            add esp, 0xC
            push 0x005E832E
            ret

            KhongDuTien :
        push 0x0
            push 0x0
            push 0xC8
            mov ecx, [ebp - 0x00000DBC]
            call SendInforInchantNewOption
            add esp, 0xC
            push 0x005E832E
            ret

            KhongRoloi :
        push 0x0
            push 0x0
            push 0xC9
            mov ecx, [ebp - 0x00000DBC]
            call SendInforInchantNewOption
            add esp, 0xC
            push 0x005E832E
            ret

            KhongDuTinhLuyen :
        push 0x0
            push 0x0
            push 0xCA
            mov ecx, [ebp - 0x00000DBC]
            call SendInforInchantNewOption
            add esp, 0xC
            push 0x005E832E
            ret

            KhongDuNguyenLieu :
        push 0x0
            push 0x0
            push 0xCB
            mov ecx, [ebp - 0x00000DBC]
            call SendInforInchantNewOption
            add esp, 0xC
            push 0x005E832E
            ret


            ThayDoiVaPhaBo :
        xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            mov ecx, [ebp - 0x00000DBC]
            imul edx, 0x60
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0x8]
            cmp eax, 0x9
            jnz KhongPhaiTinVat
            //
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            mov ecx, [ebp - 0x00000DBC]
            imul edx, 0x60
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0x8]
            cmp eax, 0x7
            jnz KhongPhaiVatPhamYeuCau
            xor eax, eax
            mov ax, [ecx + 0x128C + edx + 0xA]
            cmp eax, 0x769
            jz AcceptItemRequestChange
            cmp eax, 0x76A
            jz AcceptItemRequestChange
            cmp eax, 0x76B
            jz AcceptItemRequestChange
            jmp KhongDuVatPhamYeuCau
            AcceptItemRequestChange :
        xor eax, eax
            mov al, [ecx + 0x128C + edx + 0xF]
            cmp eax, 0x1
            jb KhongDuVatPhamYeuCau
            mov eax, 0x0050F9E2
            mov ecx, [ebp - 0x00000DBC]
            call eax
            cmp eax, 0x989680
            jbe KhongDuTienThuchien
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            sub eax, 0x989680
            push 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x50FA03
            call eax
            //Tru Nguyen Lieu
            //GetRank
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            mov ecx, [ebp - 0x00000DBC]
            imul edx, 0x60
            xor eax, eax
            mov ax, [ecx + 0x128C + edx + 0xA]
            cmp eax, 0x769
            jnz CheckRank2
            push 0x1
            jmp ContinueProcessChangeOption
            //
            CheckRank2 :
        cmp eax, 0x76A
            jnz CheckRank3
            push 0x2
            jmp ContinueProcessChangeOption
            //
            CheckRank3 :
        cmp eax, 0x76B
            jnz KhongPhaiVatPhamYeuCau
            push 0x3
            ContinueProcessChangeOption :
            //
            xor eax, eax
            mov ecx, [ebp - 0x0000F1A0]
            mov al, [ecx + 0x6]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            sub dl, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            jnz ConNguyenLieuThayDoi
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConNguyenLieuThayDoi :
        xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x7]
            push edx
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call ChangeOptTinVat
            add esp, 0xC
            push 0x0
            push eax
            mov ecx, [ebp - 0x0000F1A0]
            xor edx, edx
            mov dl, [ecx + 0x5]
            push edx
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            jmp EndFunc

            //Mo Rong
            MoRongTinVatAdr :
        xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            mov ecx, [ebp - 0x00000DBC]
            imul edx, 0x60
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0x8]
            cmp eax, 0x9
            jnz KhongPhaiTinVat
            //
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            mov ecx, [ebp - 0x00000DBC]
            imul edx, 0x60
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0x8]
            cmp eax, 0x7
            jnz KhongPhaiVatPhamYeuCau
            xor eax, eax
            mov ax, [ecx + 0x128C + edx + 0xA]
            cmp eax, 0x76D
            jnz KhongDuVatPhamYeuCau
            xor eax, eax
            mov al, [ecx + 0x128C + edx + 0xF]
            cmp eax, 0x1
            jb KhongDuVatPhamYeuCau
            mov eax, 0x0050F9E2
            mov ecx, [ebp - 0x00000DBC]
            call eax
            cmp eax, 0x4C4B40
            jbe KhongDuTienThuchien
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x0050F9E2
            call eax
            sub eax, 0x4C4B40
            push 0x1
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x50FA03
            call eax
            //Tru Nguyen Lieu
            xor eax, eax
            mov ecx, [ebp - 0x0000F1A0]
            mov al, [ecx + 0x6]
            imul eax, 0x60
            mov ecx, [ebp - 0x00000DBC]
            xor edx, edx
            mov dl, [ecx + eax + 0x128C + 0xF]
            sub dl, 0x1
            mov[ecx + eax + 0x128C + 0xF], dl
            test edx, edx
            jnz ConNguyenLieuMoRong3
            mov ecx, [ebp - 0x0000F1A0]
            xor eax, eax
            mov al, [ecx + 0x6]
            push eax
            mov ecx, [ebp - 0x00000DBC]
            mov eax, 0x004B2960
            call eax
            ConNguyenLieuMoRong3 :
        //
        xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call MoRongTinVat
            add esp, 0x4
            push 0x0
            push eax
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            xor edx, edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10

            EndFunc:
        push 0x005E832E
            ret


            KhongPhaiVuKhiRs :
            push 0x0
            push 0xA5
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            jmp EndFunc


            KhongPhaiTinVat :
        push 0x0
            push 0x4
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            jmp EndFunc

            KhongPhaiVatPhamYeuCau :
        push 0x0
            push 0x5
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            jmp EndFunc

            KhongDuVatPhamYeuCau :
        push 0x0
            push 0x6
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            jmp EndFunc

            KhongDuTienThuchien :
        push 0x0
            push 0x7
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x5]
            push edx
            mov ecx, [ebp - 0x0000F1A0]
            mov dl, [ecx + 0x6]
            push edx
            mov ecx, [ebp - 0x00000DBC]
            call SendPackagePhongAn
            add esp, 0x10
            jmp EndFunc
    }
};
void __declspec(naked)InchantNewOpt()//005E80E8 6
{
    __asm
    {
        mov ecx, [ebp - 0x0000F1A0]
        xor eax,eax
        mov al,[ecx+0x3]
        cmp eax,0x70
        jl Default
        push eax
        xor eax, eax
        mov al, [ecx + 0x4]
        push eax
        xor eax, eax
        mov al, [ecx + 0x5]
        push eax
        mov ecx, [ebp - 0x00000DBC]
        call InchantNewOptForItem
        add esp,0xC
        cmp eax,0x0
        jz Default
        push 0x005E832E
        ret


        Default:
        mov ecx, [ebp - 0x00010ED0]
        push 0x005E80EE
        ret
    }
};
void __declspec(naked)ResetRanDomInchant()//0063B141 6
{
    __asm
    {
        mov eax, 0x006FF224
        call[eax]
        push eax
        mov eax, 0x006E4F34
        call eax
        add esp, 0x4
        push 0x000F4240
        push 0x0063B146
        ret
    }
};
void __declspec(naked)ResetRanDomInchant2()//0063B231 6
{
    __asm
    {
        mov eax, 0x006FF224
        call[eax]
        push eax
        mov eax, 0x006E4F34
        call eax
        add esp, 0x4
        push 0x000F4240
        push 0x0063B236
        ret
    }
};
void __declspec(naked)ByPassRecordLog()//004D2CD0 6
{
    __asm
    {
        mov eax, 0x007711F2
        movsx eax, [eax]
        cmp eax, 0xB
        jnz Default
        push 0x004D367F
        ret

        Default:
        sub esp, 0x20
        mov [ebp - 0x1C], ecx
        push 0x004D2CD6
        ret
    }
};
int LangNhan[20] = { 18,5,3,12,1,7,16,25,14,20,8,11,2,6,21,24,15,19,13,26};
int CBTanker[29] = { 3,5,28,13,27,16,18,29,26,47,60,65,59,55,58,46,51,56,61,50,57,54,52,53,157,159,158,161,162 };
int CBBuff[54] = { 3,5,28,13,27,16,18,29,26,70,72,71,51,56,373,374,57,375,376,54,52,377,379,53,393,394,136,396,395,133,134,55,58,388,389,390,313,314,392,317,318,315,316,319,320,321,322,381,382,383,384,385,386,387 };
int CB2B[35] = { 3,5,28,13,27,16,18,29,26,70,72,56,71,57,73,76,54,52,74,77,53,75,55,58,256,255,247,248,250,251,249,252,253,254,257 };
int CBNuker[33] = { 3,5,28,13,27,16,18,29,26,48,66,49,51,56,50,57,54,52,67,68,53,69,55,58,195,194,193,196,198,199,197,200,201 };
int TLTanker[29] = { 12,5,13,25,18,26,33,34,35,46,61,47,51,56,50,57,54,52,83,81,53,82,55,58,169,171,170,173,174 };
int TLBuff[54] = { 12,5,13,25,18,26,33,34,35,70,72,71,51,56,373,374,57,375,376,54,52,377,379,53,393,394,144,396,395,141,142,55,58,388,389,390,333,334,392,337,338,335,336,339,340,341,342,381,382,383,384,385,386,387 };
int TL2B[35] = { 12,5,13,25,18,26,33,34,35,70,72,71,56,57,113,116,54,52,114,117,53,115,55,58,269,270,273,272,271,274,276,277,275,279,278 };
int TLNuker[33] = { 12,5,13,25,18,26,33,34,35,48,66,49,51,56,50,57,54,52,96,97,53,98,55,58,211,214,216,217,212,215,213,218,219 };
int LLTanker[29] = { 11,7,13,24,20,26,36,37,38,46,61,47,51,62,50,63,54,52,86,84,53,85,55,64,175,177,176,179,180 };
int LLBuff[54] = { 11,7,13,24,20,26,36,37,38,70,72,71,51,62,373,374,63,375,376,54,52,377,379,53,393,394,148,396,395,145,146,55,64,388,389,390,343,344,392,347,348,345,346,349,350,351,352,381,382,383,384,385,386,387 };
int LL2B[35] = { 11,7,13,24,20,26,36,37,38,70,72,71,62,63,118,121,54,52,119,122,53,120,55,64,280,281,284,283,282,285,287,288,286,290,289 };
int LLNuker[35] = { 11,7,13,24,20,26,36,37,38,48,66,49,51,62,50,63,54,52,99,100,53,101,55,64,220,223,225,226,221,224,222,227,228 };
int VDTanker[30] = { 1,5,13,14,18,26,39,40,41,42,46,61,47,51,56,50,57,54,52,89,87,53,88,55,58,181,183,182,185,186 };
int VDBuff[55] = { 1,5,13,14,18,26,39,40,41,42,70,72,71,51,56,373,374,57,375,376,54,52,377,379,53,393,394,152,396,395,149,150,55,58,388,389,390,353,354,392,357,358,355,356,359,360,361,362,381,382,383,384,385,386,387 };
int VD2B[36] = { 1,5,13,14,18,26,39,40,41,42,70,72,71,56,57,123,126,54,52,124,127,53,125,55,58,291,292,295,294,293,296,298,299,297,301,300 };
int VDNuker[34] = { 1,5,13,14,18,26,39,40,41,42,48,66,49,51,56,50,57,54,52,102,103,53,104,55,58,229,232,234,235,230,233,231,236,237 };
int MGTanker[29] = { 15,18,2,5,26,13,43,44,45,46,61,47,51,62,50,63,54,52,92,90,53,91,55,64,187,189,188,191,192 };
int MGBuff[54] = { 15,18,2,5,26,13,43,44,45,70,72,71,51,62,373,374,63,375,376,54,52,377,379,53,393,394,156,396,395,153,154,55,64,388,389,390,363,364,392,367,368,365,366,369,370,371,372,381,382,383,384,385,386,387 };
int MG2B[35] = { 15,18,2,5,26,13,43,44,45,70,72,71,62,63,128,131,54,52,129,132,53,130,55,64,302,303,306,305,304,307,309,310,308,312,311 };
int MGNuker[33] = { 15,18,2,5,26,13,43,44,45,48,66,49,51,62,50,63,54,52,105,106,53,107,55,64,238,241,243,244,239,242,240,245,246 };
int BCTanker[29] = { 8,6,21,13,19,26,30,31,32,46,61,47,51,62,50,63,54,52,80,78,53,55,64,79,163,165,167,164,168 };
int BCBuff[54] = { 8,6,21,13,19,26,30,31,32,70,72,71,51,62,373,374,63,375,376,54,52,377,379,53,393,394,140,396,395,137,138,55,64,386,387,381,382,383,325,326,388,389,328,390,323,324,392,327,329,330,331,332,384,385 };
int BC2B[35] = { 8,6,21,13,19,26,30,31,32,70,72,71,62,63,108,111,54,52,109,112,53,110,55,64,265,266,258,259,264,262,261,260,263,267,268 };
int BCNuker[33] = { 8,6,21,13,19,26,30,31,32,48,66,49,51,62,50,63,54,52,93,94,53,55,64,95,204,203,202,205,207,208,206,209,210 };
bool CheckNgoY(int *ValueSkillArray,int SkillCur)
{
    for (int i = 0; i < 60; i++)
    {
        if (SkillCur == ValueSkillArray[i])
        {
            return 1;
        }
    }
    return 0;
};
bool CheckHocNgoy(int MonPhai, int ChucTrach, int SkillChoosed)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int* ptrArrayUsed;
    switch (MonPhai)
    {
    case 0:
        ptrArrayUsed = LangNhan;
        break;
    case 1:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = CBTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = CBBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = CB2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = CBNuker;
        }
        else
        {
            ptrArrayUsed = CBNuker;
        }
        break;
    case 2:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = BCTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = BCBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = BC2B;
        }
        else if (ChucTrach == 7)
        {
            ptrArrayUsed = BCNuker;
        }
        else
        {
            ptrArrayUsed = BCNuker;
        }
        break;
    case 3:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = TLTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = TLBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = TL2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = TLNuker;
        }
        else
        {
            ptrArrayUsed = TLNuker;
        }
        break;
    case 4:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = LLTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = LLBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = LL2B;
        }
        else if (ChucTrach == 8)
        {
            ptrArrayUsed = LLNuker;
        }
        else
        {
            ptrArrayUsed = LLNuker;
        }
        break;
    case 5:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = VDTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = VDBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = VD2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = VDNuker;
        }
        else
        {
            ptrArrayUsed = VDNuker;
        }
        break;
    case 6:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = MGTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = MGBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = MG2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = MGNuker;
        }
        else
        {
            ptrArrayUsed = MGNuker;
        }
        break;
    default:
        return 0;
        break;
    }
    for (int x = 0; x < 60; x++)
    {
        if (SkillChoosed == ptrArrayUsed[x])
        {
            return 1;
        }
    }
    return 0;
};
bool CheckNgoYUser(int MonPhai,int ChucTrach)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    int* ptrArrayUsed;
    switch (MonPhai)
    {
    case 0:
        ptrArrayUsed = LangNhan;
        break;
    case 1:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = CBTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = CBBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = CB2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = CBNuker;
        }
        else
        {
            ptrArrayUsed = CBTanker;
        }
        break;
    case 2:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = BCTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = BCBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = BC2B;
        }
        else if (ChucTrach == 7)
        {
            ptrArrayUsed = BCNuker;
        }
        else
        {
            ptrArrayUsed = BCNuker;
        }
        break;
    case 3:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = TLTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = TLBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = TL2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = TLNuker;
        }
        else
        {
            ptrArrayUsed = TLNuker;
        }
        break;
    case 4:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = LLTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = LLBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = LL2B;
        }
        else if (ChucTrach == 8)
        {
            ptrArrayUsed = LLNuker;
        }
        else
        {
            ptrArrayUsed = LLNuker;
        }
        break;
    case 5:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = VDTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = VDBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = VD2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = VDNuker;
        }
        else
        {
            ptrArrayUsed = VDNuker;
        }
        break;
    case 6:
        if (ChucTrach == 1)
        {
            ptrArrayUsed = MGTanker;
        }
        else if (ChucTrach == 2)
        {
            ptrArrayUsed = MGBuff;
        }
        else if (ChucTrach == 3)
        {
            ptrArrayUsed = MG2B;
        }
        else if (ChucTrach == 4)
        {
            ptrArrayUsed = MGNuker;
        }
        else
        {
            ptrArrayUsed = MGNuker;
        }
        break;
    default:
        return 0;
        break;
    }
    for (int i = 0; i < 60; i++)
    {
        int SkillCurChekc = 0;
        __asm
        {
            mov ecx, StoreECX
            add ecx, 0xA6D4
            xor edx, edx
            xor eax, eax
            mov eax, i
            imul eax,0x8
            mov dx, [ecx + eax]
            mov SkillCurChekc, edx
        }
        if (SkillCurChekc == 0)
        {
            return 1;
        }
        for (int x = 0; x < 60; x++)
        {
            if (SkillCurChekc != ptrArrayUsed[x])
            {
                if (x >= 59)
                {
                    return 0;
                }
            }
            else
            {
                break;
            }
        }
    }
    return 1;
};
int GetIdPetCurTrieuHoi()
{
    DWORD StoreAddressPet;
    __asm mov StoreAddressPet,ecx
    int idPetTrieuHoi = 0;
    int idPet = 0;
    __asm
    {
        BackLoopCheckPetTrieuHoi:
        mov ecx, StoreAddressPet
        mov eax, idPet
        imul eax,0x14
        xor edx,edx
        mov dl,[ecx+eax+0x5]
        test edx,edx
        jz KhongTrieuHoiPet
        xor edx,edx
        mov dx,[ecx+ eax +0x2]
        mov idPetTrieuHoi,edx
        jmp EndOfCheckTrieuHoiPet
        KhongTrieuHoiPet:
        mov eax, idPet
        add eax,0x1
        cmp eax,0x4
        jz EndOfCheckTrieuHoiPet
        mov idPet,eax
        jmp BackLoopCheckPetTrieuHoi
        EndOfCheckTrieuHoiPet:
    }
    return idPetTrieuHoi;
}
void __declspec(naked)DisableEffect()
{
    __asm
    {
        //
        /*call GetTimeRunCheckAnti
        mov ecx, [ebp - 0x8B0]
        mov byte ptr [ecx+0xED00],0x1
        mov [ecx + 0xED01], eax*/
        //
        mov ecx, [ebp - 0x8B0]
        xor eax, eax
        mov al, [ecx + 0x1275]
        push eax
        xor eax, eax
        mov al, [ecx + 0x1264]
        push eax
        call CheckNgoYUser
        add esp, 0x8
        test al,al
        jz KhoaAccBugNgoY
        /*mov ecx, [ebp - 0x8B0]
        add ecx,0xD5D1
        call GetIdPetCurTrieuHoi
        test eax,eax
        jz KhongTrieuHoiPetCur
        push eax
        mov ecx, [ebp - 0x8B0]
        call ProcessSpawnPet
        add esp, 0x4*/
        KhongTrieuHoiPetCur:
        //
        mov ecx, 0x007711F2
        movsx ecx, [ecx]
        cmp ecx, 0x15
        jnz NotDeleteEffect
        mov ecx, [ebp - 0x000008B0]
        push 0x00495666
        ret

        NotDeleteEffect :
        push 0x1
        mov ecx, [ebp - 0x8B0]
        mov eax, 0x004F563B
        call eax
        mov ecx, [ebp - 0x000008B0]
        push 0x00495666
        ret

        KhoaAccBugNgoY:
        mov ecx, [ebp - 0x8B0]
        xor eax, eax
        lea eax, [ecx + 0xE74]
        push 0x1
        push eax
        call BlockAccount
        add esp, 0x8
        mov ecx, [ebp - 0x8B0]
        call KickDissUser
        /*push 0
        mov ecx, [ebp - 0x8B0]
        call SendPackageAnti
        add esp, 0x4*/
        mov ecx, [ebp - 0x000008B0]
        push 0x00495666
        ret
    }
}
void __declspec(naked)CheckSkillBeforeAddMastery()//004CC56A 6
{
    __asm
    {
        mov eax,[ebp+0x8]
        xor ecx,ecx
        mov cx,[eax+0x4]
        push ecx
        mov ecx, [ebp - 0x20]
        xor eax, eax
        mov al, [ecx + 0x1275]
        push eax
        xor eax, eax
        mov al, [ecx + 0x1264]
        push eax
        call CheckHocNgoy
        add esp,0xC
        test al,al
        jz KhoaAcc
        mov eax, [ebp - 0x20]
        movsx ecx, word ptr[eax + 0x00005C3A]
        push 0x004CC571
        ret

        KhoaAcc:
        mov ecx, [ebp - 0x20]
        xor eax, eax
        lea eax, [ecx + 0xE74]
        push 0x2
        push eax
        call BlockAccount
        add esp, 0x8
        mov ecx, [ebp - 0x20]
        call KickDissUser
        push 0
        mov ecx, [ebp - 0x20]
        call SendPackageAnti
        add esp, 0x4
        mov eax, [ebp - 0x20]
        movsx ecx, word ptr[eax + 0x00005C3A]
        push 0x004CC571
        ret
    }
};
void __declspec(naked)AcceptOptionHanhNang()//004CC3F6 6
{
    __asm
    {
        mov edx, [ebp - 0xC]
        xor ecx, ecx
        cmp edx, 0x15
        jz AcceptItem
        cmp edx, 0x16
        jz AcceptItem
        push 0x004CC3FB
        ret

        AcceptItem :
        push 0x004CC408
            ret
    }
};
struct SendInforPackageStar
{
    _sHeader			header;
    u_char				ucMessage;
    u_char				ucMessage2;
    u_char				cStarLevel;
};
void FuncSendInforLevel()
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    SendInforPackageStar pkUserInfolv;
    __asm
    {
        lea eax, pkUserInfolv
        mov byte ptr[eax], 0x5
        mov byte ptr[eax + 0x1], 0x0
        mov byte ptr[eax + 0x2], 0x6A
        mov byte ptr[eax + 0x3], 0xE4
        mov ecx, StoreECX
        xor edx,edx
        mov dl,[ecx+0xD63E]
        mov [eax + 0x4], dl
        lea eax, pkUserInfolv
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, pkUserInfolv
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }

}
void __declspec(naked)SendInfoLeveltoUser()//00491D45
{
    __asm
    {
        mov ecx, [ebp - 0x00000134]
        call FuncSendInforLevel
        mov ecx,[ebp - 0x00000134]
        push 0x00491D4B
        ret
    }
};
struct PackageQuyet
{
    _sHeader			header;
    u_char				ucMessage;//C0
    u_char				ucMessage2;
};
void SendPackageQuetBack(int typeError)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    PackageQuyet ifPackageQuyet;
    char Errortype;
    if (typeError == 0)
    {
        __asm lea eax, Errortype
        __asm mov [eax],0xF1
    }
    else if (typeError == 1)
    {
        __asm lea eax, Errortype
        __asm mov[eax], 0xF2
    }
    else if (typeError == 2)
    {
        __asm lea eax, Errortype
        __asm mov[eax], 0xF3
    }
    __asm
    {
        lea eax, ifPackageQuyet
        mov word ptr[eax],0x4
        mov byte ptr[eax+0x2], 0xC0
        lea eax, Errortype
        xor ecx,ecx
        mov cl,[eax]
        lea eax, ifPackageQuyet
        mov byte ptr[eax+0x3], cl
        lea eax, ifPackageQuyet
        mov cx, [eax]
        and cx, 0x7FFF
        and ecx, 0xFFFF
        push ecx
        lea eax, ifPackageQuyet
        push eax
        mov ecx, StoreECX
        mov eax, 0x0069479A
        call eax
    }
};
int KiemTraTimeSoloQ(int TgcuaUSer)
{
    DWORD StoreECX;
    __asm mov StoreECX,ecx
    SYSTEMTIME checktime;
    GetLocalTime(&checktime);
    if (TgcuaUSer == checktime.wDay)
    {
        return 10;
    }
    else
    {
        return checktime.wDay;
    }

}
int KiemTraSetDo(int NumberQ)
{
    DWORD StoreECX;
    int result;
    result = 0;
    __asm mov StoreECX, ecx
    int numberslot;
    if (NumberQ == 0)
    {
        return 0;
    }
    else if (NumberQ == 1)
    {
        __asm
        {
            lea eax, numberslot
            mov dword ptr[eax], 0x0
            xor ecx, ecx
            BackLoopCheck:
            mov eax, StoreECX
            xor edx,edx
            imul ecx,0x60
            mov dx,[eax+ecx+0x128C+0xA]
            cmp dx,0x2F24
            jz CheckSlotNext
            lea eax, result
            mov[eax], 0x1
            jmp CompleteCheck1
            CheckSlotNext:
            lea eax, numberslot
            mov ecx,[eax]
            add ecx,0x1
            mov [eax],ecx
            cmp ecx,0x5
            jl BackLoopCheck
            lea eax, result
            mov [eax],0x0
            CompleteCheck1:
        }
    }
    else if (NumberQ == 2)
    {
        __asm
        {
            lea eax, numberslot
            mov dword ptr[eax], 0x0
            xor ecx, ecx
            BackLoopCheck1 :
            mov eax, StoreECX
                xor edx, edx
                imul ecx, 0x60
                mov dx, [eax + ecx + 0x128C + 0xA]
                cmp dx, 0x2F24
                jz CheckSlotNext1
                lea eax, result
                mov[eax], 0x2
                jmp CompleteCheck2
                CheckSlotNext1 :
            lea eax, numberslot
                mov ecx, [eax]
                add ecx, 0x1
                mov[eax], ecx
                cmp ecx, 0x5
                jl BackLoopCheck1
                lea eax, result
                mov[eax], 0x0
                CompleteCheck2:
        }
    }
    return result;
    
};
void __declspec(naked)ByPassQ1()//005EE2B2
{
    __asm
    {
        mov eax, [ebp - 0x00010DA4]
        xor ecx,ecx
        mov cl,[eax+0x3]
        cmp ecx,0x41
        jnz DefaultQCu
        mov ecx, [ebp - 0xDBC]
        mov eax, 0x004B3870
        call eax
        test eax, eax
        jnz MaxSolanDi
        mov ecx, [ebp - 0x00000DBC]
        xor eax,eax
        mov al,[ecx+0xD649]
        test eax,eax
        jz Default
        push 0x005EE2EF
        ret

        DefaultQCu:
        mov eax, [ebp - 0x00010DA4]
        push 0x005EE2B8
        ret

        Default:
        xor eax,eax
        mov ecx, [ebp - 0x00000DBC]
        mov al,[ecx+0xD64A]
        push eax
        mov ecx, [ebp - 0x00000DBC]
        call KiemTraTimeSoloQ
        add esp,0x4
        cmp eax,0xA
        jnz NgayMoi
        ProcessKiemTra:
        mov ecx, [ebp - 0x00000DBC]
        mov al, [ecx + 0xD63F]
        add eax,0x1
        cmp eax,0x3
        ja MaxSolanDi
        mov eax, [ebp - 0x00010DA4]
        xor ecx,ecx
        mov cl,[eax+0x4]
        push ecx
        mov ecx, [ebp - 0x00000DBC]
        call KiemTraSetDo
        add esp,0x4
        cmp eax,0x1
        jz KhongDuDieuKienSet1
        cmp eax, 0x2
        jz KhongDuDieuKienSet2
        xor eax, eax
        mov ecx, [ebp - 0x00000DBC]
        mov al, [ecx + 0xD63F]
        add eax, 0x1
        mov[ecx + 0xD63F], al
        mov ecx, [ebp - 0x00000DBC]
        call StoreUserDB

        mov eax, [ebp - 0x00010DA4]
        push 0x005EE2B8
        ret

        MaxSolanDi:
        push 0x0
        mov ecx, [ebp - 0x00000DBC]
        call SendPackageQuetBack
        add esp, 0x4
        push 0x005EE2C2
        ret

        NgayMoi:
        mov ecx, [ebp - 0x00000DBC]
        mov [ecx + 0xD64A],al
        mov [ecx + 0xD63F],0x0
        jmp ProcessKiemTra

            KhongDuDieuKienSet1:
            push 0x1
            mov ecx, [ebp - 0x00000DBC]
            call SendPackageQuetBack
            add esp, 0x4
            push 0x005EE2C2
            ret

                KhongDuDieuKienSet2:
            push 0x2
            mov ecx, [ebp - 0x00000DBC]
            call SendPackageQuetBack
            add esp,0x4
            push 0x005EE2C2
            ret
    }
};
void __declspec(naked)ByPassQ2()//005EE587
{
    __asm
    {
        mov eax, [ebp - 0x00010DA4]
        xor ecx, ecx
        mov cl, [eax + 0x3]
        cmp ecx, 0x41
        jnz Default
        mov edx, [ebp - 0x00000DBC]
        xor eax, eax
        mov al, [edx + 0xD649]
        test eax, eax
        jz Default
        mov byte ptr [edx+0xD649],0x0
        mov byte ptr [ebp - 0x10DA8],0x00
        push 0x005EE5FF
        ret

        Default :
        mov edx, [ebp - 0x00010DB8]
        push 0x005EE58D
        ret
    }
};
int ListOptionAdd[39][3] =
{
    {63,3,5},// ngu khi
    {23,1,28},// crit
    {134,1,12},//stcm
    {130,2,1},//mau value
    {55,5,0},//hap mau
    {56,5,1},//hap mana
    {148,1,68},//deff vl/kc %d
    {61,3,7},//toc do di chuyen
    {21,1,9},//ti le do don
    {124,1,50},//suc de khang tat ca
    {5,1,46},//st am
    {6,1,47},//suc sat thuong
    {7,1,48},//suc sat hon
    {8,1,49},//suc sat than
    {90,1,40},//suc sat thuong cua vk
    {9,1,5},//suc sat vl tang
    {10,1,20},//suc sat kc tang
    {3,3,3},//do chinh xac %
    {11,1,55},//st am %
    {12,1,56},//st duong %
    {15,1,4},//st vl %
    {16,1,19},//st kc %
    {37,1,51},//suc de khang am
    {38,1,52},//suc de khang duong
    {39,1,53},//suc de khang hon
    {40,1,54},//suc de khang than
    {47,2,0},//tang mau %
    {48,2,2},//tang mana %
    {53,3,3},//tang sl 
    {54,3,4},//tang mt
    {80,1,21},//phng thu kc %
    {93,1,44},//tang mt
    {95,1,42},//tang mt
    {24,1,30},//tang mt
    {133,1,6},//tang mt
    {219,3,14},//tang mt
    {138,1,15},//tang mt
    {144,1,14},//tang mt
    {145,1,26},//tang mt
};
void __declspec(naked)GetOption()//004CBE04
{
    __asm
    {
       mov ecx, [ebp - 0x30]
       xor edx,edx
       mov dl, [ebp + 0x8]
       imul edx,0x60
       xor eax,eax
       mov ax,[ecx+0x128C+edx+0x24]
       test eax,eax
       jz Default
       lea edx, [ecx + 0x128C + edx]
       push edx
       call AddOptionToNewAddress
       add esp,0x4
       Default:
       mov edx, [ebp - 0x10]
       mov eax, [edx + 0x44]
       push 0x004CBE0A
       ret


       AddOptionToNewAddress:
       //
       sub esp, 0x4
       mov eax,[esp+0x8]
       push eax
       call GetCountOpt
       xor edx,edx
       mov dl, [ebp + 0x8]
       cmp edx,0x8B
       ja SlotCao
       sub dl, 0xC
       jmp ProcessContinue1
       SlotCao:
       sub dl,0x84
       ProcessContinue1:
       imul edx,0x154
       mov ecx, [ebp - 0x30]
       mov [ecx+edx+ 0xD66B+0x150],eax
       xor ecx, ecx
       mov [esp],ecx
       BackLoopGetValue :
       xor edx, edx
       mov dl, [ebp + 0x8]
       imul edx, 0x60
       mov eax, [ebp - 0x30]
       lea eax,[eax+edx+0x128C]
       xor edx,edx
       imul ecx,0x5
       mov dx,[eax+0x24+ecx]
       test edx,edx
       jz EndFuncGetValue
       push edx
       call GetAddressOption
       test eax,eax
       jz EndFuncGetValue
       xor edx,edx
       mov dl, [ebp + 0x8]
       cmp edx, 0x8B
       ja SlotCao1
       sub dl, 0xC
       jmp ProcessContinue2
       SlotCao1 :
       sub dl, 0x84
       ProcessContinue2 :
       imul edx, 0x154
       mov ecx, [ebp - 0x30]
       lea edx, [edx + ecx + 0xD66B]
       mov ecx,[esp]
       imul ecx,0x8
       lea edx,[edx+ecx]
       xor ecx,ecx
       mov ecx,[eax+0x4]
       mov [edx],cx
       xor ecx, ecx
       mov ecx, [eax + 0x8]
       mov [edx+0x2], cx
       //GetValue
       xor edx,edx
       mov dl, [ebp + 0x8]
       imul edx, 0x60
       mov eax, [ebp - 0x30]
       lea eax, [eax + edx + 0x128C]
       xor edx, edx
       mov ecx,[esp]
       imul ecx, 0x5
       mov dx,[eax+0x24+ecx+0x2]
       xor eax, eax
       mov al, [ebp + 0x8]
       cmp eax, 0x8B
       ja SlotCao3
       sub al, 0xC
       jmp ProcessContinue3
       SlotCao3 :
       sub al, 0x84
       ProcessContinue3 :
       imul eax, 0x154
       mov ecx, [ebp - 0x30]
       lea eax, [eax + ecx + 0xD66B]
       mov ecx, [esp]
       imul ecx,0x8
       lea eax,[eax+ecx]
       mov [eax+0x4],dx
       mov ecx, [esp]
       add ecx,0x1
       mov [esp],ecx
       jmp BackLoopGetValue

        EndFuncGetValue:
        add esp,0x4
        ret


       GetCountOpt:
       sub esp,0x4
       mov dword ptr [esp],0x0
       mov ecx,[esp]
       BackCheckCount:
       mov eax,[esp+0x8]
       xor edx,edx
       mov ecx, [esp]
       imul ecx,0x5
       mov dx,[eax+0x24+ecx]
       test edx,edx
       jz CompleteCheckGetCount
       mov eax, [esp]
       add eax,0x1
       mov [esp],eax
       jmp BackCheckCount
       CompleteCheckGetCount:
       mov eax,[esp]
       add esp,0x4
       ret 0x4

           GetAddressOption :
           sub esp,0x4
           xor ecx,ecx
           mov [esp],ecx
           LoopCheckOptionInList:
           imul ecx,0xC
           lea eax, ListOptionAdd
           mov edx,[esp+0x8]
           cmp edx,[eax+ecx]
           jnz IncreaseToCheckValue
           lea eax,[eax+ecx]
           add esp, 0x4
           ret 0x4
           IncreaseToCheckValue:
           mov ecx,[esp]
           add ecx,0x1
           mov [esp],ecx
           cmp ecx,0x27
           jbe LoopCheckOptionInList
           mov eax,0x0
           add esp,0x4
           ret 0x4
    }
};
void __declspec(naked)AcceptValueNewPhongAn()//004D1691
{
    __asm
    {
        //LoopAddOption
        push ecx
        mov ecx,0xC
        LoopCheck:
        mov [esp],ecx
        imul ecx,0x60
        mov eax, [ebp - 0x20]
        xor edx,edx
        mov dx,[eax+ecx+0x128C+0xA]
        test edx,edx
        jz CheckAnotherSlot
        mov ecx, [esp]
        push ecx
        call AddOptionToUser
        CheckAnotherSlot:
        mov ecx,[esp]
        add ecx,0x1
        cmp ecx,0x13
        jbe LoopCheck
        //Check Slot Cao
        mov ecx, 0x8C
        LoopCheck2:
        mov [esp], ecx
        imul ecx, 0x60
        mov eax, [ebp - 0x20]
        xor edx, edx
        mov dx, [eax + ecx + 0x128C + 0xA]
        test edx, edx
        jz CheckAnotherSlot2
        mov ecx, [esp]
        push ecx
        call AddOptionToUser
        CheckAnotherSlot2:
        mov ecx, [esp]
        add ecx, 0x1
        cmp ecx, 0x93
        jbe LoopCheck2
        //
        pop ecx
        mov[ebp - 0x14], 0x00000000
        push 0x004D1698
        ret


        AddOptionToUser:
        sub esp,0x4
        mov dword ptr [esp],0x0
        mov ecx,[esp+0x8]
        cmp ecx,0x13
        ja SlotCao
        LoopCheckAnotherValue:
        mov ecx, [esp + 0x8]
        sub ecx,0xC
        mov eax, [ebp - 0x20]
        imul ecx,0x154
        xor edx,edx
        mov edx,[eax+ecx+0xD66B+0x150]
        mov ecx,[esp]
        cmp ecx,edx
        jae CompleteAddOption
        mov ecx, [esp + 0x8]
        sub ecx, 0xC
        mov eax, [ebp - 0x20]
        imul ecx, 0x154
        xor edx, edx
        lea edx, [eax + ecx + 0xD66B]
        mov ecx, [esp]
        imul ecx,0x8
        lea edx,[edx+ecx]
        push edx
        mov ecx, [ebp - 0x20]
        mov eax,0x004F8E5A
        call eax
        mov ecx,[esp]
        add ecx,0x1
        mov [esp],ecx
        jmp LoopCheckAnotherValue
        SlotCao:
        LoopCheckAnotherValueCao:
        mov ecx, [esp + 0x8]
        sub ecx, 0x84
        mov eax, [ebp - 0x20]
        imul ecx, 0x154
        xor edx, edx
        mov edx, [eax + ecx + 0xD66B + 0x150]
        mov ecx, [esp]
        cmp ecx, edx
        jae CompleteAddOption
        mov ecx, [esp + 0x8]
        sub ecx, 0x84
        mov eax, [ebp - 0x20]
        imul ecx, 0x154
        xor edx, edx
        lea edx, [eax + ecx + 0xD66B]
        mov ecx, [esp]
        imul ecx, 0x8
        lea edx, [edx + ecx]
        push edx
        mov ecx, [ebp - 0x20]
        mov eax, 0x004F8E5A
        call eax
        mov ecx, [esp]
        add ecx, 0x1
        mov[esp], ecx
        jmp LoopCheckAnotherValueCao
        CompleteAddOption:
        add esp,0x4
        ret 0x4
    }
};
int ListSkillBuffCrit[6] = {1207,2218,3211,4211,5200,6200};
int ListSkillBuffSTCM[6] = {1146,2157,3150,4150,5139,6139};
bool CheckListSkillCrit(int idSkill)
{
    bool rsCheckSkill;
    rsCheckSkill = false;
    for (int i = 0; i < 6; i++)
    {
        if (idSkill == ListSkillBuffCrit[i])
        {
            rsCheckSkill = true;
        }
    }
    return rsCheckSkill;
}
bool CheckListSkillSTCM(int idSkill)
{
    bool rsCheckSkill;
    rsCheckSkill = false;
    for (int i = 0; i < 6; i++)
    {
        if (idSkill == ListSkillBuffSTCM[i])
        {
            rsCheckSkill = true;
        }
    }
    return rsCheckSkill;
}
bool CheckDieuKienBuffCrit()
{
    DWORD StoreECX;
    int LoopCheck;
    LoopCheck = 0;
    __asm mov StoreECX,ecx
    bool resultinfo;
    resultinfo = false;
    __asm
    {
        LoopCheckBuffNext:
        mov ecx, StoreECX
        lea ecx,[ecx+0xAED8]
        xor eax,eax
        mov edx, LoopCheck
        mov ax,[ecx+edx]
        push eax
        call CheckListSkillCrit
        add esp,0x4
        test eax,eax
        jnz CompleteCheckSkill
        mov edx, LoopCheck
        add edx,0x10
        mov LoopCheck,edx
        cmp edx,0x230
        jbe LoopCheckBuffNext
        jmp CompleteFuncCheck
        CompleteCheckSkill:
        mov resultinfo,0x1
        CompleteFuncCheck:
    }
    return resultinfo;
}
bool CheckDieuKienBuffSTCM()
{
    DWORD StoreECX;
    int LoopCheck;
    LoopCheck = 0;
    __asm mov StoreECX, ecx
    bool resultinfo;
    resultinfo = false;
    __asm
    {
    LoopCheckBuffNext:
        mov ecx, StoreECX
            lea ecx, [ecx + 0xAED8]
            xor eax, eax
            mov edx, LoopCheck
            mov ax, [ecx + edx]
            push eax
            call CheckListSkillSTCM
            add esp, 0x4
            test eax, eax
            jnz CompleteCheckSkill
            mov edx, LoopCheck
            add edx, 0x10
            mov LoopCheck, edx
            cmp edx, 0x230
            jbe LoopCheckBuffNext
            jmp CompleteFuncCheck
            CompleteCheckSkill :
        mov resultinfo, 0x1
            CompleteFuncCheck :
    }
    return resultinfo;
}
void __declspec(naked)KhoaBuffCritKhacPhai()//005DED93
{
    __asm
    {
        //Check
        lea ecx, [ebp - 0x92A8]
        xor eax, eax
        mov ax, [ecx + 0x30]
        push eax
        call CheckListSkillCrit
        add esp, 0x4
        cmp al, 0x1
        jz ProcessCheckSkillCrit
        lea ecx, [ebp - 0x92A8]
        xor eax, eax
        mov ax, [ecx + 0x30]
        push eax
        call CheckListSkillSTCM
        add esp, 0x4
        cmp al, 0x1
        jz CheckSkillSTCMNguoiKhac
        jmp Default
        //
        ProcessCheckSkillCrit:
        mov ecx, [ebp - 0xE708]
        xor eax,eax
        mov ax,[ecx+0x4]
        push eax
        mov ecx,DWORD PTR SS:[0x007763AC]
        mov eax,0x00607FB4
        call eax
        test eax,eax
        jz KhongChoPhepBuff
        mov ecx,eax
        call CheckDieuKienBuffCrit
        xor ecx,ecx
        mov cl,al
        test ecx,ecx
        jnz KhongChoPhepBuff
        push 0x005DEDB6
        ret
        //Check Skill STCm
        CheckSkillSTCMNguoiKhac:
        mov ecx, [ebp - 0xE708]
        xor eax, eax
        mov ax, [ecx + 0x4]
        push eax
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov eax, 0x00607FB4
        call eax
        test eax, eax
        jz KhongChoPhepBuff
        mov ecx, eax
        call CheckDieuKienBuffSTCM
        xor ecx, ecx
        mov cl, al
        test ecx, ecx
        jnz KhongChoPhepBuff
        Default:
        push 0x005DEDB6
        ret
        KhongChoPhepBuff:
        push 0x005DF6B6
        ret
    }
};
void __declspec(naked)KhoaBuffCritBanThan()//005DF7DA
{
    __asm
    {
        lea ecx, [ebp - 0x92A8]
        xor eax,eax
        mov ax,[ecx+0x30]
        push eax
        call CheckListSkillCrit
        add esp,0x4
        cmp al,0x1
        jz ProcessCheckSkillSTCM
        lea ecx, [ebp - 0x92A8]
        xor eax, eax
        mov ax, [ecx + 0x30]
        push eax
        call CheckListSkillSTCM
        add esp,0x4
        cmp al,0x1
        jz CheckSkillSTCmBanThanProcess
        jmp Default
        ProcessCheckSkillSTCM:
        mov ecx, [ebp - 0xDBC]
        call CheckDieuKienBuffCrit
        xor ecx, ecx
        mov cl, al
        test ecx, ecx
        jnz KhongChoPhepBuff
        push 0x005DF7FE
        ret
        //Check Skill STCm
        CheckSkillSTCmBanThanProcess:
        mov ecx, [ebp - 0xDBC]
        call CheckDieuKienBuffSTCM
        xor ecx, ecx
        mov cl, al
        test ecx, ecx
        jnz KhongChoPhepBuff
        Default:
        push 0x005DF7FE
        ret
        KhongChoPhepBuff :
        push 0x005E07FF
        ret
    }
};
void __declspec(naked)KhoaParty()//005EBA31
{
    __asm
    {
        push 0x005EBB41
        ret
    }
};
void __declspec(naked)DebugCheckAddress()//006948F6
{
    __asm
    {
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        mov eax,[esp+0x4]
        xor ecx,ecx
        mov cx,[eax]
        cmp ecx,0x23
        jnz Default
        xor ecx, ecx
        mov cl, [eax+0x2]
        cmp ecx, 0xA7
        jnz Default

        Default:
        push 0x006948FC
        ret
    }
};
void __declspec(naked)DebugCheckAddress2()//00439376
{
    __asm
    {
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        mov eax, [esp + 0x4]
        xor ecx, ecx
        mov cx, [eax]
        cmp ecx, 0x23
        jnz Default
        xor ecx, ecx
        mov cl, [eax + 0x2]
        cmp ecx, 0xA7
        jnz Default

        Default :
        push 0x0043937C
        ret
    }
};
void __declspec(naked)FixLoiXepChongTinVat()//0050DBC8
{
    __asm
    {
        xor ecx, ecx
        mov cl, [ebp - 0x8]
        imul ecx, 0x60
        mov edx, [ebp - 0x4C]
        xor eax, eax
        mov al, [edx + ecx + 0x128C + 0x8]
        cmp al, 0x9
        jnz Default
        push 0x0050DE16
        ret

        Default :
        mov cl, [ebp - 0x8]
            push ecx
            mov ecx, [ebp - 0x4C]
            push 0x0050DBCF
            ret
    }
};
void SendPackageMovePet(DWORD& tUser)
{
    DWORD StoreECXPet;
    __asm mov StoreECXPet, ecx
    float PoszSub = 1.5f;
    _point ptUser;
    __asm
    {
        mov ecx, tUser
        mov eax, 0x00431F70
        call eax
        fsub PoszSub
        fstp ptUser.m_posX
        mov ecx, tUser
        mov eax, 0x00431F90
        call eax
        fstp ptUser.m_posZ
        mov 	ecx, StoreECXPet
        mov 	eax, 0x0059BCC0
        call 	eax
        mov 	ecx, StoreECXPet
        add     ecx, 0x1C8
        mov 	eax, 0x00433320
        call 	eax
        mov 	ecx, StoreECXPet
        fstp    dword ptr[ecx + 0x1F]
        mov 	ecx, StoreECXPet
        add     ecx, 0x1C8
        mov 	eax, 0x00433360
        call 	eax
        mov 	edx, StoreECXPet
        fstp    dword ptr[edx + 0x23]
        //
        fld     ptUser.m_posX
        mov 	eax, StoreECXPet
        fstp    dword ptr[eax + 0x27]
        //
        fld     ptUser.m_posZ
        mov 	eax, StoreECXPet
        fstp    dword ptr[eax + 0x2B]
        //
        mov 	ecx, StoreECXPet
        mov 	eax, 0x00592E00
        call 	eax
        mov 	edx, StoreECXPet
        mov[edx + 0x2F], al
        mov 	ecx, StoreECXPet
        mov byte ptr[ecx + 0x30], 0xF5
        mov     ecx, StoreECXPet
        mov     edx, [ecx + 0xB4]
        push    edx
        mov     eax, StoreECXPet
        mov     ecx, [eax + 0x208]
        push    ecx
        mov     ecx, StoreECXPet
        add     ecx, 0x1C8
        mov 	eax, 0x005A0FA0
        call 	eax
        push 	eax
        mov     edx, StoreECXPet
        mov     ax, [edx + 0x18]
        and ax, 0x7FFF
        and eax, 0xFFFF
        push    eax
        mov     ecx, StoreECXPet
        add     ecx, 0x18
        push    ecx
        mov ecx, DWORD PTR SS : [0x007763AC]
        mov 	eax, 0x0060342E
        call 	eax
        push 	0x0
        mov     edx, StoreECXPet
        push    edx
        push    0x0
        push    0xA5
        push    0x2
        mov 	eax, 0x00406B20
        call 	eax
        mov     ecx, eax
        mov 	eax, 0x0040AE50
        call 	eax
        mov eax, ptUser.m_posX
        mov ecx, StoreECXPet
        add ecx, 0x1C8
        mov[ecx + 0xC], eax
        mov eax, ptUser.m_posZ
        mov ecx, StoreECXPet
        add ecx, 0x1C8
        mov[ecx + 0x10], eax
        /*mov ecx, StoreECXPet
        mov eax,0x0059ADD0
        call eax*/
        // NeverDie
        mov ecx, StoreECXPet
        mov eax, 0x004331E0
        call eax
        // Off Attack
        mov ecx, StoreECXPet
        mov eax, 0x0059B3B0
        call eax
    }
}
void AddItemfromString(const char* str)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    int typeitem, id, count, inchant = 0;
    sscanf(str, "%d %d %d %d", &typeitem, &id, &count, &inchant);
    __asm
    {
        push inchant
        push count
        push id
        push typeitem
        mov ecx, StoreECX
        call AddItemFromBox
        add esp, 0x10
    }
}
void __declspec(naked)AddDmg()//005CE39A
{
    __asm
    {
        mov ecx, [ebp - 0x00000848]
        add ecx, 0x5
        xor edx, edx
        mov dl, [ecx + 0x15]
        cmp edx, 0x5B
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x16]
        cmp edx, 0x24
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x17]
        cmp edx, 0x24
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x18]
        cmp edx, 0x48
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x19]
        cmp edx, 0x53
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x1A]
        cmp edx, 0x47
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x1B]
        cmp edx, 0x21
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x1C]
        cmp edx, 0x40
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x1D]
        cmp edx, 0x21
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x1E]
        cmp edx, 0x5D
        jnz Default
        xor edx, edx
        mov dl, [ecx + 0x1E]
        cmp edx, 0x5D
        jnz Default
        lea edx, [ecx + 0x20]
        push edx
        mov ecx, [ebp - 0x00000DBC]
        call AddItemfromString
        add esp, 0x4
        Default:
        mov ecx, [ebp - 0x00000848]
        push 0x005CE3A0
        ret
    }
};
void __declspec(naked)MovePetUser()//005CDF51
{
    __asm
    {
        mov ecx, [ebp - 0x00000DBC]
        xor eax, eax
        mov eax, [ecx + 0xD629]
        test eax, eax
        jz Default
        mov ecx, eax
        mov eax, [ebp - 0x00000DBC]
        push eax
        call SendPackageMovePet
        add esp, 0x4

        Default :
        mov ecx, [ebp - 0x00000DBC]
            push 0x005CDF57
            ret
    }
};
void __declspec(naked)BypassCheckTimeEffect()//004ECABD
{
    __asm
    {
        mov eax, [ebp + 0xC]
        cmp eax, 0xE1
        jnz Default
        push 0x004ECAC8
        ret

        Default :
        sub edx, 0x000003E8
            push 0x004ECAC3
            ret
    }
};
bool CheckTimeAnti(DWORD TimeCheck)
{
    DWORD StoreECX;
    __asm mov StoreECX, ecx
    time_t timestarDao = time(nullptr);
    DWORD timeDaoStart = (DWORD)timestarDao;
    if (TimeCheck > timeDaoStart)
    {
        return 1;
    }
    else
    {
        return 0;
    }

};
void __declspec(naked)CheckTimePackageAnti()//00694AA3
{
    __asm
    {
        mov[edx + 0x3C], ecx
        //
        xor eax, eax
        mov al, [edx + 0xED00]
        test al, al
        jz FuncStillNotWork
        //
        xor eax, eax
        mov eax, [edx + 0xED01]
        test eax, eax
        jz FuncStillNotWork
        push eax
        mov ecx, edx
        call CheckTimeAnti
        add esp, 0x4
        test al, al
        jz AntiNotRun
        FuncStillNotWork :
        mov eax, [ebp - 0x4]
        push 0x00694AA9
        ret

            AntiNotRun :
            mov ecx, [ebp - 0x4]
            xor eax, eax
            lea eax, [ecx + 0xE74]
            push 0x4
            push eax
            call BlockAccount
            add esp, 0x8
            mov ecx, [ebp - 0x4]
            call KickDissUser
            mov eax, [ebp - 0x4]
            push 0x00694AA9
            ret

    }
};
void __declspec(naked)PauseCheckWhenMove()// 005E3C31
{
    __asm
    {
        mov [ebp - 0x0000EAB0], al
        mov ecx, [ebp - 0x00000DBC]
        push 3
        call SendPackageAnti
        add esp, 0x4
        push 0x005E3C37
        ret
    }
}
int listBuffFromPetByPass[24] = { 8275,8274,8272,8271,8277,8278,8279,8280,8281,8282,8283,8284,8285,8286,8295,8298,8301,8302,8303,8304,8305,8306,8314,8315 };
bool checkBuffByPass(int idBuff)
{
    for (int i = 0; i < 24; i++)
    {
        if (idBuff == listBuffFromPetByPass[i])
        {
            return 0;
        }
    }
    return 1;
}
void __declspec(naked)BoQuaXoaBuffPet()//004F5695
{
    __asm
    {
        movsx eax, word ptr[edx + ecx + 0x0000AED8]
        push eax
        call checkBuffByPass
        add esp,0x4
        test al,al
        jz FoundBuffPet
        mov ecx, [ebp - 0x4]
        shl ecx, 0x4
        mov edx, [ebp - 0x00008030]
        movsx eax, word ptr[edx + ecx + 0x0000AED8]
        push 0x004F569D
        ret 

        FoundBuffPet:
        push 0x004F56AE
        ret
    }
};
void __declspec(naked)BoQuaXoaBuffPet2()//004F5973
{
    __asm
    {
        movsx ecx, word ptr[eax + edx + 0x0000AED8]
        push ecx
        call checkBuffByPass
        add esp, 0x4
        test al, al
        jz FoundBuffPet
        mov edx, [ebp - 0x4]
        shl edx, 0x4
        mov eax, [ebp - 0x00008030]
        movsx ecx, word ptr[eax + edx + 0x0000AED8]
        push 0x004F597B
        ret

        FoundBuffPet :
        push 0x004F59A3
        ret
    }
};
void __declspec(naked)HuyPetKhiOutGame()//00602391
{
    __asm
    {
        mov ecx, [ebp + 0x8]
        mov eax, [ecx + 0xD629]
        test eax,eax
        jz KhongCoPet
        mov ecx, eax
        mov eax, 0x00586F11
        call eax
        KhongCoPet:
        mov ecx, [ebp + 0x8]
        mov DWORD PTR SS:[ecx+0xD629],0x0
        xor edx, edx
        mov dl, byte PTR SS:[0x00776348]
        push 0x00602399
        ret 
    }
};
void __declspec(naked)HuyPetKhiOutGame2()//00602643
{
    __asm
    {
        mov ecx, [ebp + 0x8]
        mov eax, [ecx + 0xD629]
        test eax, eax
        jz KhongCoPet
        mov ecx, eax
        mov eax, 0x00586F11
        call eax
        KhongCoPet :
        mov ecx, [ebp + 0x8]
            mov DWORD PTR SS : [ecx + 0xD629] , 0x0
            xor eax, eax
            mov al, byte PTR SS : [0x00776348]
            push 0x0060264A
            ret
    }
};
struct NewInchantInfor
{
    int		special_success_prob;	// ±âº¸ µîÀÇ ¼º°ø È®·ü
    int		normal_success_prob;	// ÀÏ¹Ý ¾ÆÀÌÅÛÀÇ ¼º°ø È®·ü
    int		fail_prob;		// ¿ÏÀü ½ÇÆÐ È®·ü

    // ÇÊ¿ä Á¤º¸
    short	need_type;
    short	need_count;
    short	need_id_1;
    u_char  unknow1;
    u_char  unknow2;
    unsigned int unknow3;
};
NewInchantInfor InforInchant[26];
int			m_iInchantPlusValue[26];
float		m_fInchantTimesValue[26];
int			m_iInchantM_PlusValue[26];
float		m_fInchantM_TimesValue[26];
u_char		m_ucInchant_LeftItemCount[26];

void __declspec(naked)ChangeLimiteInchant()//00639472
{
    __asm
    {
        cmp dword ptr[ebp - 0x00000138], 20
        push 0x00639479
        ret
    }
};
void __declspec(naked)ChangeLimiteInchant2()//00639700
{
    __asm
    {
        cmp dword ptr[ebp - 0x00000138], 20
        push 0x00639707
        ret
    }
};
void __declspec(naked)ChangeLimiteInchant3()//0063997D
{
    __asm
    {
        cmp dword ptr[ebp - 0x00000138], 20
        push 0x00639984
        ret
    }
};
void __declspec(naked)ChangeLimiteInchant4()//00639D2B
{
    __asm
    {
        cmp dword ptr[ebp - 0x00000138], 20
        push 0x00639D32
        ret
    }
};
void __declspec(naked)ChangeInchantGetLoad()//00639508
{
    __asm
    {
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x140]
        mov     [eax + edx], ecx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x114]
        mov[eax + edx + 0x4], ecx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x108]
        mov[eax + edx + 0x8], ecx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cx, [ebp - 0x124]
        mov[eax + edx + 0x8 + 0x6], cx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cx, [ebp - 0x124]
        mov [eax + edx + 0x8 + 0x6 + 0x2], cx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cx, [ebp - 0x124]
        mov[eax + edx + 0x8 + 0x6 + 0x2 + 0x2], cx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cl, [ebp - 0x118]
        mov[eax + edx + 0x8 + 0x4], cl
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cl, [ebp - 0x10C]
        mov[eax + edx + 0x8 + 0x4 + 0x1], cl
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x110]
        mov[eax + edx + 0x8 + 0x6 + 0x2 + 0x2 + 0x2], ecx
        push 0x0063960A
        ret
    }
};
void __declspec(naked)ChangeInchantGetLoad2()//00639C7C
{
    __asm
    {
        mov     edx, [ebp - 0x138]
        lea     eax, m_iInchantPlusValue
        mov     ecx, [ebp - 0x12C]
        mov [eax + edx * 4], ecx
        mov     edx, [ebp - 0x138]
        lea     eax, m_fInchantTimesValue
        mov     ecx, [ebp - 0x148]
        mov [eax + edx * 4], ecx
        mov     edx, [ebp - 0x138]
        lea     eax, m_iInchantM_PlusValue
        mov     ecx, [ebp - 0x104]
        mov [eax + edx * 4], ecx
        mov     edx, [ebp - 0x138]
        lea     eax, m_fInchantM_TimesValue
        mov     ecx, [ebp - 0x134]
        mov [eax + edx * 4], ecx
        push 0x00639CE0
        ret
    }
};
void __declspec(naked)ChangeInchantGetLoad3()//00639CFF
{
    __asm
    {
        lea     edx, m_ucInchant_LeftItemCount
        add     edx, [ebp - 0x138]
        mov     al, [ebp - 0x120]
        mov     [edx], al
        push    0x00639D17
        ret
    }
};
void __declspec(naked)ChangeInchantGetLoad4()//00639794
{
    __asm
    {
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     eax, [ebp - 0x140]
        mov     [edx + ecx], eax
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     eax, [ebp - 0x114]
        mov     [edx + ecx + 0x4], eax
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     eax, [ebp - 0x108]
        mov     [edx + ecx + 0x8], eax
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     ax, [ebp - 0x124]
        mov     [edx + ecx + 0x8 + 0x6], ax
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     ax, [ebp - 0x128]
        mov[edx + ecx + 0x8 + 0x6+0x2], ax
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     ax, [ebp - 0x128]
        mov[edx + ecx + 0x8 + 0x6 + 0x2 + 0x2], ax
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     al, [ebp - 0x118]
        mov[edx + ecx + 0x8 + 0x4], al
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     al, [ebp - 0x10C]
        mov [edx + ecx + 0x8 + 0x4 + 0x1], al
        mov     ecx, [ebp - 0x138]
        imul    ecx, 0x18
        lea     edx, InforInchant
        mov     eax, [ebp - 0x110]
        mov[edx + ecx + 0x8 + 0x6 + 0x2 + 0x2+0x2], eax
        push    0x00639896
        ret
    }
};
void __declspec(naked)ChangeInchantGetLoad5()//00639A13
{
    __asm
    {
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x140]
        mov[eax + edx], ecx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x114]
        mov[eax + edx + 0x4], ecx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x108]
        mov[eax + edx + 0x8], ecx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cx, [ebp - 0x124]
        mov[eax + edx + 0x8 + 0x6], cx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cx, [ebp - 0x128]
        mov[eax + edx + 0x8 + 0x6 + 0x2], cx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cx, [ebp - 0x130]
        mov[eax + edx + 0x8 + 0x6 + 0x2 + 0x2], cx
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cl, [ebp - 0x118]
        mov[eax + edx + 0x8 + 0x4], cl
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     cl, [ebp - 0x10C]
        mov[eax + edx + 0x8 + 0x4 + 0x1], cl
        mov     edx, [ebp - 0x138]
        imul    edx, 0x18
        lea     eax, InforInchant
        mov     ecx, [ebp - 0x110]
        mov[eax + edx + 0x8 + 0x6 + 0x2 + 0x2 + 0x2], ecx
        push 0x00639B15
        ret 
    }
};
void __declspec(naked)ChangeAddressInchant()//0063B0C1
{
    __asm
    {
        lea edx, InforInchant
        lea eax, [edx + ecx]
        push 0x0063B0C8
        ret
    }
};
void __declspec(naked)ChangeAddressInchant2()//0063AFE6
{
    __asm
    {
        lea edx, InforInchant
        lea eax, [edx + ecx]
        push 0x0063AFED
        ret
    }
};
void __declspec(naked)ChangeAddressInchant3()//0052BD00
{
    __asm
    {
        lea edx, m_iInchantPlusValue
        mov eax, [edx + ecx*0x4]
        push 0x0052BD07
        ret
    }
};
void __declspec(naked)MoGioiHanInchantOKho()// 005083DB
{
    __asm
    {
        mov dl, [ecx + 0x18]
        cmp edx, 0x12
        push 0x005083E1
        ret
    }
};
void __declspec(naked)ChangeAddressInchant31()//0052BD0C
{
    __asm
    {
        lea edx, m_iInchantPlusValue
        mov ecx, 20
        mov eax, [edx + ecx*0x4]
        push 0x0052BD12
        ret
    }
};
void __declspec(naked)ChangeAddressInchant4()// 0052BD40
{
    __asm
    {
        lea edx, m_fInchantTimesValue
        fld dword ptr [edx + ecx * 0x4]
        push 0x0052BD47
        ret
    }
};
void __declspec(naked)ChangeAddressInchant41()// 0052BD4C
{
    __asm
    {
        lea edx, m_fInchantTimesValue
        mov ecx, 20
        fld dword ptr[edx + ecx * 0x4]
        push 0x0052BD52
        ret
    }
};
void __declspec(naked)ChangeAddressInchant5()// 0052BD80
{
    __asm
    {
        lea edx, m_iInchantM_PlusValue
        mov eax, [edx + ecx * 0x4]
        push 0x0052BD87
        ret
    }
};
void __declspec(naked)ChangeAddressInchant51()// 0052BD8C
{
    __asm
    {
        lea edx, m_iInchantM_PlusValue
        mov ecx, 20
        mov eax, [edx + ecx * 0x4]
        push 0x0052BD92
        ret
    }
};
void __declspec(naked)ChangeAddressInchant6()// 0052BDC0
{
    __asm
    {
        lea edx, m_fInchantM_TimesValue
        fld dword ptr[edx + ecx * 0x4]
        push 0x0052BDC7
        ret
    }
};
void __declspec(naked)ChangeAddressInchant61()// 0052BDCC
{
    __asm
    {
        lea edx, m_fInchantM_TimesValue
        mov ecx, 20
        fld dword ptr[edx + ecx * 0x4]
        push 0x0052BDD2
        ret
    }
};
void __declspec(naked)ChangeAddressInchant7()// 0052BE00
{
    __asm
    {
        lea edx, m_ucInchant_LeftItemCount
        mov al, [edx + ecx]
        push 0x0052BE07
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant()// 0052BDEA
{
    __asm
    {
        and eax, 0xFF
        cmp eax, 0x14
        push 0x0052BDF2
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant2()// 0052BCEA
{
    __asm
    {
        and eax, 0xFF
        cmp eax, 0x14
        push 0x0052BCF2
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant3()// 0052BD2A
{
    __asm
    {
        and eax, 0xFF
        cmp eax, 0x14
        push 0x0052BD32
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant4()// 0052BD6A
{
    __asm
    {
        and eax, 0xFF
        cmp eax, 0x14
        push 0x0052BD72
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant5()// 0052BDAA
{
    __asm
    {
        and eax, 0xFF
        cmp eax, 0x14
        push 0x0052BDB2
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant6()// 0063B064
{
    __asm
    {
        and eax, 0xFF
        cmp eax, 18
        push 0x0063B06C
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant7()// 0063AFC6
{
    __asm
    {
        and eax, 0xFF
        cmp eax, 18
        push 0x0063AFCE
        ret
    }
};
void __declspec(naked)ChangeLimitedInchant9()// 00508007
{
    __asm
    {
        mov cl, [eax + 0x18]
        cmp ecx, 18
        push 0x0050800D
        ret
    }
};
void __declspec(naked)MoGioiHanDamg1()// 00587E34
{
    __asm
    {
        cmp [ebp - 0x24], 0x000F423F
        push 0x00587E3B
        ret
    }
};
void __declspec(naked)MoGioiHanDamg2()// 00587E3D
{
    __asm
    {
        mov [ebp - 0x24], 0x000F423F
        push 0x00587E44
        ret
    }
};

void __declspec(naked)MoGioiHanDamg3()// 00588DBE
{
    __asm
    {
        cmp[ebp - 0x38], 0x000F423F
        push 0x00588DC5
        ret
    }
};
void __declspec(naked)MoGioiHanDamg4()// 00588DC7
{
    __asm
    {
        mov[ebp - 0x38], 0x000F423F
        push 0x00588DCE
        ret
    }
};
void __declspec(naked)MoGioiHanDamg5()// 00589817
{
    __asm
    {
        cmp [ebp - 0x40], 0x000F423F
        push 0x0058981E
        ret
    }
};
void __declspec(naked)MoGioiHanDamg6()// 00589820
{
    __asm
    {
        mov [ebp - 0x40], 0x000F423F
        push 0x00589827
        ret
    }
};
// Fix Loi Quai Giet Khong Chet
void __declspec(naked)FixLoiKhongChet()// 004C7D12
{
    __asm
    {
        xor ecx, ecx
        mov cx, word ptr[ebp - 0x1C]
        push ecx
        push 0x004C7D17
        ret
    }
};
void __declspec(naked)FixLoiKhongChet2()// 004C8557
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x1C]
        push eax
        push 0x004C855C
        ret
    }
};
void __declspec(naked)FixLoiKhongChet3()// 004C8592
{
    __asm
    {
        xor edx, edx
        mov dx, [ebp - 0x50]
        push edx
        push 0x004C8597
        ret
    }
};
void __declspec(naked)FixLoiKhongChet4()// 004C8DC4
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x1C]
        push eax
        push 0x004C8DC9
        ret
    }
};
void __declspec(naked)FixLoiKhongChet5()// 004C8DFF
{
    __asm
    {
        xor edx, edx
        mov dx, [ebp - 0x50]
        push edx
        push 0x004C8E04
        ret
    }
};
void __declspec(naked)FixLoiKhongChet6()// 004E1129 7
{
    __asm
    {
        mov eax, [ebp - 0x1C]
        xor ecx, ecx
        mov cx, [eax + 0x4]
        push 0x004E1131
        ret
    }
};
void __declspec(naked)FixLoiKhongChet7()// 004E1287
{
    __asm
    {
        xor ecx, ecx
        mov cx, [ebp - 0x24]
        push ecx
        push 0x004E128C
        ret
    }
};
void __declspec(naked)FixLoiKhongChet8()// 004E1296
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x24]
        push eax
        push 0x004E129E
        ret
    }
};
void __declspec(naked)FixLoiKhongChet9()// 004E12AB
{
    __asm
    {
        xor edx, edx
        mov dx, [ecx + 0x4]
        push edx
        push 0x004E12B0
        ret
    }
};
void __declspec(naked)FixLoiKhongChet10()// 004E12E8
{
    __asm
    {
        xor eax, eax
        mov ax, [edx + 0x4]
        push eax
        push 0x004E12ED
        ret
    }
};
void __declspec(naked)FixLoiKhongChet11()// 004EDE64
{
    __asm
    {
        xor edx, edx
        mov dx, [ecx + 0x4]
        push edx
        push 0x004EDE69
        ret
    }
};
void __declspec(naked)FixLoiKhongChet12()// 004EDFEA
{
    __asm
    {
        xor edx, edx
        mov dx, [ecx + 0x4]
        push edx
        push 0x004EDFEF
        ret
    }
};
void __declspec(naked)FixLoiKhongChet13()// 004EE09C
{
    __asm
    {
        xor ecx, ecx
        mov cx, [ebp - 0x24]
        push ecx
        push 0x004EE0A1
        ret
    }
};
void __declspec(naked)FixLoiKhongChet14()// 004EE0AE
{
    __asm
    {
        xor eax, eax
        mov ax, [edx + 0x4]
        push eax
        push 0x004EE0B3
        ret
    }
};
void __declspec(naked)FixLoiKhongChet15()// 004EE157 7
{
    __asm
    {
        mov edx, [ebp + 0x8]
        xor eax, eax
        mov eax, [edx + 0x4]
        push 0x004EE15E
        ret
    }
};
void __declspec(naked)FixLoiKhongChet16()// 004EE658
{
    __asm
    {
        xor ecx, ecx
        mov cx, [ebp - 0x4C]
        push ecx
        push 0x004EE65D
        ret
    }
};
void __declspec(naked)FixLoiKhongChet17()// 004EE6B4
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x50]
        push eax
        push 0x004EE6B9
        ret
    }
};
void __declspec(naked)FixLoiKhongChet18()// 004EE703
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x54]
        push eax
        push 0x004EE708
        ret
    }
};
void __declspec(naked)FixLoiKhongChet19()// 004EE752
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x58]
        push eax
        push 0x004EE757
        ret
    }
};
void __declspec(naked)FixLoiKhongChet20()// 004EE7A1
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x5C]
        push eax
        push 0x004EE7A6
        ret
    }
};
void __declspec(naked)FixLoiKhongChet21()// 004EE9B3
{
    __asm
    {
        xor eax, eax
        mov ax, [edx + 0x4]
        push eax
        push 0x004EE9B8
        ret
    }
};
void __declspec(naked)FixLoiKhongChet22()// 004F1C8E
{
    __asm
    {
        xor ecx, ecx
        mov cx, [eax + 0x4]
        push ecx
        push 0x004F1C93
        ret
    }
};
void __declspec(naked)FixLoiKhongChet23()// 004F1E17
{
    __asm
    {
        xor ecx, ecx
        mov cx, [eax + 0x4]
        push ecx
        push 0x004F1E1C
        ret
    }
};
void __declspec(naked)FixLoiKhongChet24()// 004F1E4D
{
    __asm
    {
        xor ecx, ecx
        mov cx, [eax + 0x4]
        push ecx
        push 0x004F1E52
        ret
    }
};
void __declspec(naked)FixLoiKhongChet25()// 004F1E5F
{
    __asm
    {
        xor eax, eax
        mov ax, [edx + 0x4]
        push eax
        push 0x004F1E64
        ret
    }
};
void __declspec(naked)FixLoiKhongChet26()// 0058860E
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x2C]
        neg eax
        push 0x00588614
        ret
    }
};
void __declspec(naked)FixLoiKhongChet27()// 00589071
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x28]
        neg eax
        push 0x00589077
        ret
    }
};
void __declspec(naked)FixLoiKhongChet29()// 005899EC
{
    __asm
    {
        xor eax, eax
        mov ax, [ebp - 0x48]
        neg eax
        push 0x005899F2
        ret
    }
};
DWORD WINAPI MainThread(LPVOID param)
{
    
    int hooklenght = 7;
    int hooklenghtAddSkill = 8;
    //DWORD ChangeTimeUse = 0x52CD72;
    //Patch((BYTE*)ChangeTimeUse, (BYTE*)"\x90\xE2\x00\x00", 4);
    LoadInforItemFunc();
    LoadInforDieuCheCoTDBuaFunc();
    LoadInforDieuCheKhongCoTDSachFunc();
    LoadInforWeaponSkillFunc();
    DWORD KhoaBuffCritKhacPhaiAdr = 0x005DED93;
    DWORD KhoaBuffCritBanThanAdr = 0x005DF7DA;
    DWORD ByPassQ2Adr = 0x005EE587;
    DWORD ByPassQ1Adr = 0x005EE2B2;
    DWORD InchantNewOptAdr = 0x005E80E8;
    DWORD SendInfoLeveltoUserAdr = 0x00491D45;
    DWORD NewInchant1Adr = 0x005E80D0;
    DWORD AcceptOptionHanhNangAdr = 0x004CC3F6;
    DWORD ByPassRecordLogAdr = 0x004D2CD0;
    DWORD ResetRanDomInchantAdr = 0x0063B141;
    DWORD ResetRanDomInchant2Adr = 0x0063B231;
    DWORD Giam1NuaDmg2Adr = 0x00594316;
    DWORD Giam1NuaDmgAdr = 0x005941BB;
    DWORD SendMoneyAfterBuyAdr = 0x005E30D1;
    DWORD KiemTraMuaShopAdr = 0x0050BA69;
    DWORD KiemTraMuaShopBoQuaTruTienAdr = 0x0050BB3F;
    DWORD KiemTraMuaShopBoQuaTruTien2Adr = 0x0050BD16;
    DWORD injectHookCharInforAdr = 0x00493238;
    DWORD KiemTraRankLeveAdr = 0x0049B506;
    DWORD ChangeTypeLevelUpAdr = 0x005F6EC6;
    DWORD KiemTraPheBoQuaDmgAdr = 0x05874AF;
    DWORD KiemTraPheBoQuaDmg2Adr = 0x0058892D;
    DWORD KiemTraPheBoQuaDmg3Adr = 0x00589395;
    DWORD GetPozTongKimAdr = 0x004916EF;
    DWORD GetValueTongKimAdr = 0x004AAAD1;
    DWORD GetInforFromTextAdr = 0x00491403;
    DWORD GetGiaTriVaoMapTKAdr = 0x00492F29;
    DWORD ThayDoiTiLeQuanAo1Adr = 0x0063B0FC;
    DWORD AddBonusForPackageEXPAdr = 0x004A1A37;
    DWORD ThayDoiTiLeQuanAo2Adr = 0x0063B1ED;
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
    DWORD AddOptionClothAdr = 0x004D049E;
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
    DWORD ProcessDeletePetAdr = 0x0049338E;
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
    DWORD AddEffectAfterAttackAdr = 0x005D4881;
    DWORD ChangeCheckSlotAdr = 0x00519030;
    DWORD ChangeCheckSlot2Adr = 0x0050B111;//GM add
    DWORD ChangeCheckSlot3Adr = 0x00517B26;
    DWORD ChangeCheckSlot4Adr = 0x00519A3A;
    DWORD ChangeCheckSlot5Adr = 0x005F0CCF;
    DWORD ChangeCheckSlot6Adr = 0x005F0C89;
    DWORD ChangeCheckSlot7Adr = 0x005E71BB;
    DWORD IncFailedAdr = 0x005222B2;
    DWORD ByPassCheckRunNext1TestAdr = 0x0059D924;
    DWORD TestCheckTimeMoveVillageAdr = 0x005E3C6E;
    DWORD LoadChienAdr = 0x005E3C67;
    DWORD AddBloodPkAdr = 0x004D29D4;
    DWORD ImprisonmentPlayerAdr = 0x0049F91F;
    DWORD ChangeCheckSlot8Adr = 0x0050E2AE;
    DWORD TestBoChanKhiSatThuongAdr = 0x004C92B3;
    DWORD TangPhongThuSinhLucAdr = 0x004C90E3;
    DWORD DoiTTSangManTiepAdr = 0x004C93A8;
    DWORD DoiTTSangManTiep1Adr = 0x004C9411;
    DWORD DoiTTSangManTiep2Adr = 0x004C948A;
    DWORD DoiTTSangManTiep3Adr = 0x004C94B4;
    DWORD CheckTimeDelayAdr = 0x005D4719;
    DWORD GetStepSkillNukeAdr = 0x004C2CE0;
    DWORD CheckTimeDelayNukerAdr = 0x005354A2;
    DWORD DisableStackRelicAdr = 0x0052BC36;
    DWORD DisableCallAdr = 0x00413ABB;
    DWORD DisableCancelMaskAdr = 0x005F6AB0;
    DWORD RemovePetDieAdr = 0x005D170D;
    DWORD RemovePetDie2Adr = 0x004B5CFD;
    DWORD RemovePetDie3Adr = 0x004B5EF5;
    DWORD DisabledMoveAdr = 0x00413ABB;
    DWORD ChageSizePvpModRESULT_MOBAdr = 0x005CCE8C;
    DWORD ChageSizepkActiveResultPvpAdr = 0x005CCEE7;
    DWORD ChageSizepkSmashResultMobAdr = 0x005CCF41;
    DWORD ChageSizepkSmashResultPvpAdr = 0x005CCF9B;
    DWORD ChangeLenghtPvpModRESULT_MOBAdr = 0x005D4D74;
    DWORD ChangeLenghtActiveResultPvpAdr = 0x005D58A2;
    DWORD ChangeLenghtpkSmashResultMobAdr = 0x005DD00A;
    DWORD ChangeLenghtpkSmashResultPvpAdr = 0x005DDDEA;
    DWORD ProcessDeletePetRelogAdr = 0x005D0F15;
    DWORD BonusDeffenceAdr = 0x004D6DDE;
    DWORD NdTangCuongDoClothAdr = 0x00522013;
    DWORD GiaHanCucDaiAdr = 0x005248D3;
    DWORD GoGiaHanCucDaiAdr = 0x00524D80;
    DWORD GetGiaTriCucDaiAdr = 0x0051005E;
    DWORD BonusDeffenceVL1Adr = 0x00593E09;
    DWORD BonusDeffenceKC1Adr = 0x005944F9;
    DWORD KhangHieuUngAdr = 0x004DBFFD;
    DWORD DisabledStackRelic2Adr = 0x0052BB92;
    DWORD AddNewValue1Adr = 0x005F894F;
    DWORD AddNewValue2Adr = 0x005F8A3C;
    DWORD ChangeCodePercentHealthMobAdr = 0x00592E50;
    DWORD ChangeCodePercentHealthMob2Adr = 0x00592E2F;
    DWORD KhangHieuUng2Adr = 0x004ED614;
    DWORD KhangHieuUng1Adr = 0x004ED6AA;
    DWORD PhongThuChiMangAdr = 0x004B811A;
    DWORD PhongThuChiMang2Adr = 0x004B813C;
    DWORD BonusDeffenceKCAdr = 0x004D6E9E;
    DWORD PhongThuChiMangKCAdr = 0x004B98A3;
    DWORD PhongThuChiMang2KCAdr = 0x004B98C9;
    DWORD GetEventIngameAdr = 0x004134B7;
    DWORD GetDmgFromBossAdr = 0x00587E44;
    DWORD GetDmgSkillFromBossAdr = 0x00588E22;
    DWORD GetDmgSkillNukerFromBossAdr = 0x00589A84;
    DWORD AddEventKillMobAdr = 0x00606FFE;
    DWORD GetEventKillMobAdr = 0x00586EFC;
    DWORD GetCoolDownSkillNuker2Adr = 0x004C26B6;
    DWORD ChageSizepkRoundingResultMobAdr = 0x005CD09C;
    DWORD ChageSizepkRoundingResultMobSendAdr = 0x005DE6AA;
    DWORD ChageSizepkRoundingResultMobNuker2Adr = 0x005CD32A;
    DWORD ChageSizepkRoundingResultMobSendNuker2Adr = 0x005D7AAA;
    DWORD AddOptionNewSlot607Adr = 0x004CC4AD;
    DWORD PhongThuChiMang23Adr = 0x004B8D47;
    DWORD PhongThuChiMang24Adr = 0x004B8D69;
    DWORD LoadValueFromNewSlotAdr = 0x0050E5D1;
    DWORD BypassCheckiDAdr = 0x004CBADF;
    DWORD GioiHanDmgVlPvpAdr = 0x004D6D86;
    DWORD GioiHanDmgkcPvpAdr = 0x004D6E46;
    DWORD GioiHanDmgVlPvpSauDeffAdr = 0x004D6E37;
    DWORD GioiHanDmgKCPvpSauDeffAdr = 0x004D6EF7;
    DWORD XoaSlotMoiAdr = 0x004CC3CA;
    DWORD UnknowFunAdr = 0x00616F8F;
    DWORD GetAddressNewSlotAdr = 0x004CBAA3;
    DWORD GetAddressNewSlot2Adr = 0x004D1601;
    DWORD CheckADdressNewSlotAdr = 0x00507972;
        DWORD CheckADdressNewSlot2Adr = 0x00507C57;
        DWORD CheckADdressNewSlot3Adr = 0x00507C57;
        DWORD CheckADdressNewSlot4Adr = 0x00507AA5;
        DWORD CheckADdressNewSlot5Adr = 0x0050755A;
        DWORD CheckADdressNewSlot6Adr = 0x005076AA;
        DWORD CheckADdressNewSlot7Adr = 0x00507D6D;
        DWORD AddNewValueFromNickAdr = 0x004E1606;
        DWORD ReloadInforNickAdr = 0x004E1589;
        DWORD AddBonusEventEXpAdr = 0x004A19CA;
        DWORD AddBonusEventEXp2Adr = 0x004A19E4;
        DWORD GetCoolDownSkillNuker3Adr = 0x004C1C60;
        DWORD FixGiaoDichMatDoHanhTrang8CAdr = 0x0051A604;
        DWORD AddOptionCloth2Adr = 0x004D0C4F;
        DWORD KhongXoaVpDieuCheAdr = 0x00525DA3;
        DWORD TestFixAmDamg1Adr = 0x004B98BA;
        DWORD AllowlearnSkillAdr = 0x00628499;
        DWORD TestRediemAdr = 0x00525911;
        DWORD CheckIPConnectAdr = 0x006B1E6B;
        DWORD GetTimeEventAdr = 0x0053A7FC;
        DWORD ChangeValueCombineAdr = 0x052511C;
        DWORD ChangeValueCombine2Adr = 0x0050AE54;
        DWORD ChangeValueCombine3Adr = 0x0051DDC4;
        DWORD GetSlotSuccessAdr = 0x00525B14;
        DWORD DieuCheGiuNguyenTiLeAdr = 0x0051DE2F;
        DWORD GetSlotFailAdr = 0x00525D85;
        DWORD KhoaHapKhiPKAdr = 0x004C0000;
        DWORD KhoaHapKhiPK2Adr = 0x004B6987;
        DWORD KhoaHapKhiPK3Adr = 0x004C0AAF;
        DWORD KhoaHapKhiPK4Adr = 0x004C1811;
        DWORD KhoaHapKhiPK5Adr = 0x004C19F7;
        DWORD KhoaHapKhiPK6Adr = 0x004C287A;
        DWORD KhoaHapKhiPK7Adr = 0x004C3161;
        DWORD KhoaHapKhiPK8Adr = 0x004C3E80;
        DWORD KhoaHapKhiPK9Adr = 0x004C4A65;
        DWORD KhoaHapKhiPK10Adr = 0x004C5BAD;
        DWORD TangTiLeCombineAdr = 0x00525921;
        DWORD TangPhanTramDmgTankAdr = 0x004BFE1F;
        DWORD TangPhanTramDmgThucKyAdr = 0x004C486A;
        DWORD TruSatThuongAdr = 0x004B833C;
        DWORD TruSatThuong1Adr = 0x004B82EA;
        DWORD TruSatThuongKCAdr = 0x004B9A17;
        DWORD TruSatThuongKC1Adr = 0x004B99FE;
        DWORD TangPhanTramDmgNukerAdr = 0x004C2EB0;
        DWORD FixAmMauHapAdr = 0x005885EF;
        DWORD TestDoiGiaTriDeffAdr = 0x004D6D96;
        DWORD TinhToanDeffVaPhanDamAdr = 0x004B8FBB;
        DWORD TinhToanDeffVaPhanDamChieuThucKyAdr = 0x004B8376;
        DWORD TinhToanDeffVaPhanDamNukerAdr = 0x004B9A59;
        DWORD TinhToanDeffVaPhanDamNuker2Adr = 0x004BBF70;
        DWORD DeleteOptSetItemAdr = 0x004CC020;
        DWORD AddOptFromSetItemAdr = 0x004CC02F;
        DWORD AddNewOptClothAdr = 0x004CABB6;
        DWORD ThongBaoDaNhatQuaAdr = 0x005ABBB5;
        DWORD ChangeLenghtpkSmashResultPvp2Adr = 0x005DDA7B;
        DWORD TestSkillAOEAdr = 0x00605D12;
        DWORD ChageSizepkRoundingResultPvpAdr = 0x005DF08E;
        DWORD TestSkillAOE2Adr = 0x0042BF48;
        DWORD FixMaxCritGiamRageAdr = 0x059432C;
        DWORD FixCritAllAdr = 0x0059433E;
        DWORD FixMaxCritSendAdr = 0x00587A18;
        DWORD FixSendCrit2Adr = 0x00588B19;
        DWORD FixSendCrit3Adr = 0x005895EE;
        DWORD StoreInfoUserTxtAdr = 0x005D0F01;
        DWORD StoreInfoUserTxt2Adr = 0x00602391;
        DWORD StoreInfoUserTxt3Adr = 0x00602645;
        DWORD FixLoiDeoTinVatMatDoAdr = 0x0050AFED;
        DWORD AddBonusEventEXp3Adr = 0x004A19D8;
        DWORD FixLoiMaxDoKTCAdr = 0x00414AFE;
        DWORD TestReadFileAdr = 0x006B2A4C;
        DWORD FixAmMauHapNukerAdr = 0x005899CD;
        DWORD TestDoiGiaTriDeffNukerAdr = 0x004D6E56;
        DWORD CheckRealCritNotFuncAdr = 0x004D76BF;
        DWORD ThemDmgChoBossAdr = 0x004BC576;
        DWORD TruDiemNhanQuaAdr = 0x005ABA81;
        DWORD FixAmMauHap2Adr = 0x00589052;
        DWORD ShowMoreUserAdr = 0x0060B61E;
        DWORD BypassAddMillAdr = 0x0050FA9F;
        DWORD ByPassSaiDoiTuongAdr = 0x005D5463;
        DWORD ByPassGMADDSlot96Adr = 0x0041F381;
        DWORD ChangeSlotRoom1Adr = 0x00524CB3;
        DWORD ChangeSlotRoom2Adr = 0x00524D25;
        DWORD ChangeSlotRoom3Adr = 0x00524806;
        DWORD ChangeSlotRoom4Adr = 0x00524878;
        DWORD ChangeSlotRoom5Adr = 0x005236AF;
        DWORD ChangeSlotRoom6Adr = 0x00510229;
        DWORD ChangeSlotRoom7Adr = 0x004B2A13;
        DWORD ChangeSlotRoom8Adr = 0x00524057;
        DWORD ChangeSlotRoom9Adr = 0x00524028;
        DWORD ChangeSlotRoom10Adr = 0x00523FF9;
        DWORD ChangeSlotRoom11Adr = 0x0052368E;
        DWORD ChangeSlotRoom12Adr = 0x00520460;
        DWORD ChangeSlotRoom13Adr = 0x00520442;
        DWORD ChangeSlotRoom14Adr = 0x00520416;
        DWORD ChangeSlotRoom15Adr = 0x0051E234;
        DWORD ChangeSlotRoom16Adr = 0x0050B2E2;
        DWORD ChangeSlotRoom17Adr = 0x0050AD23;
        DWORD ChangeSlotRoom18Adr = 0x00528DE9;
        DWORD ChangeSlotRoom19Adr = 0x005236D0;
        DWORD ChangeSlotRoom20Adr = 0x00520E19;
        DWORD ChangeSlotRoom21Adr = 0x0050CF48;
        DWORD ChangeSlotRoom221Adr = 0x0050ACC4;
        DWORD ChangeSlotRoom22Adr = 0x0050AC61;
        DWORD ChangeSlotRoom23Adr = 0x00508AF6;
        DWORD ChangeSlotRoom24Adr = 0x004AB8E2;
        DWORD ChangeSlotRoom25Adr = 0x004AB5B6;
        DWORD ChangeSlotRoom26Adr = 0x0049255C;
        DWORD ChangeSlotRoom27Adr = 0x00489D32;
        DWORD GetOptionAdr = 0x004CBE04;
        DWORD AcceptValueNewPhongAnAdr = 0x004D1691;
        DWORD KhoaPartyAdr = 0x005EBA31;
        DWORD DebugCheckAddressAdr = 0x006948F6;
        DWORD DebugCheckAddress2Adr = 0x00439376;
        DWORD FixLoiXepChongTinVatAdr = 0x0050DBC8;
        DWORD PauseCheckWhenMoveAdr = 0x005E3C31;
        // Load Inchant Moi
        DWORD ChangeInchantGetLoad5Adr = 0x00639A13;
        DWORD ChangeInchantGetLoad4Adr = 0x00639794;
        DWORD ChangeInchantGetLoad3Adr = 0x00639CFF;
        DWORD ChangeInchantGetLoad2Adr = 0x00639C7C;
        DWORD ChangeInchantGetLoadAdr = 0x00639508;
        DWORD ChangeLimiteInchantAdr = 0x00639472;
        DWORD ChangeLimiteInchant2Adr = 0x00639700;
        DWORD ChangeLimiteInchant3Adr = 0x0063997D;
        DWORD ChangeLimiteInchant4Adr = 0x00639D2B;
        DWORD ChangeAddressInchantAdr = 0x0063B0C1;
        DWORD ChangeAddressInchant2Adr = 0x0063AFE6;
        DWORD ChangeAddressInchant3Adr = 0x0052BD00;
        DWORD ChangeAddressInchant31Adr = 0x0052BD0C;
        DWORD ChangeAddressInchant4Adr = 0x0052BD40;
        DWORD ChangeAddressInchant41Adr = 0x0052BD4C;
        DWORD ChangeAddressInchant5Adr = 0x0052BD80;
        DWORD ChangeAddressInchant51Adr = 0x0052BD8C;
        DWORD ChangeAddressInchant6Adr = 0x0052BDC0;
        DWORD ChangeAddressInchant61Adr = 0x0052BDCC;
        DWORD ChangeAddressInchant7Adr = 0x0052BE00;
        DWORD ChangeLimitedInchantAdr = 0x0052BDEA;
        DWORD ChangeLimitedInchant2Adr = 0x0052BCEA;
        DWORD ChangeLimitedInchant3Adr = 0x0052BD2A;
        DWORD ChangeLimitedInchant4Adr = 0x0052BD6A;
        DWORD ChangeLimitedInchant5Adr = 0x0052BDAA;
        DWORD ChangeLimitedInchant6Adr = 0x0063B064;
        DWORD ChangeLimitedInchant7Adr = 0x0063AFC6;
        DWORD ChangeLimitedInchant9Adr = 0x00508007;
        DWORD MoGioiHanDamg2Adr = 0x00587E3D;
        DWORD MoGioiHanDamg3Adr = 0x00588DBE;
        DWORD MoGioiHanDamg4Adr = 0x00588DC7;
        DWORD MoGioiHanDamg1Adr = 0x00587E34;
        DWORD MoGioiHanInchantOKhoAdr = 0x005083DB;
        DWORD FixLoiKhongChetAdr = 0x004C7D12;
        DWORD FixLoiKhongChet2Adr = 0x004C8557;
        DWORD FixLoiKhongChet3Adr = 0x004C8592;
        DWORD FixLoiKhongChet4Adr = 0x004C8DC4;
        DWORD FixLoiKhongChet5Adr = 0x004C8DFF;
        DWORD FixLoiKhongChet6Adr = 0x004E1129;
        DWORD FixLoiKhongChet7Adr = 0x004E1287;
        DWORD FixLoiKhongChet8Adr = 0x004E1296;
        DWORD FixLoiKhongChet9Adr = 0x004E12AB;
        DWORD FixLoiKhongChet10Adr = 0x004E12E8;
        DWORD FixLoiKhongChet11Adr = 0x004EDE64;
        DWORD FixLoiKhongChet12Adr = 0x004EDFEA;
        DWORD FixLoiKhongChet13Adr = 0x004EE09C;
        DWORD FixLoiKhongChet14Adr = 0x004EE0AE;
        DWORD FixLoiKhongChet15Adr = 0x004EE157;
        DWORD FixLoiKhongChet16Adr = 0x004EE658;
        DWORD FixLoiKhongChet17Adr = 0x004EE6B4;
        DWORD FixLoiKhongChet18Adr = 0x004EE703;
        DWORD FixLoiKhongChet19Adr = 0x004EE752;
        DWORD FixLoiKhongChet20Adr = 0x004EE7A1;
        DWORD FixLoiKhongChet21Adr = 0x004EE9B3;
        DWORD FixLoiKhongChet22Adr = 0x004F1C8E;
        DWORD FixLoiKhongChet23Adr = 0x004F1E17;
        DWORD FixLoiKhongChet24Adr = 0x004F1E4D;
        DWORD FixLoiKhongChet25Adr = 0x004F1E5F;
        DWORD FixLoiKhongChet26Adr = 0x0058860E;
        DWORD FixLoiKhongChet27Adr = 0x00589071;
        DWORD FixLoiKhongChet29Adr = 0x005899EC;
        DWORD MoGioiHanDamg6Adr = 0x00589820;
        DWORD MoGioiHanDamg5Adr = 0x00589817;


        hook((void*)FixLoiKhongChetAdr, FixLoiKhongChet, 5);
        hook((void*)FixLoiKhongChet2Adr, FixLoiKhongChet2, 5);
        hook((void*)FixLoiKhongChet3Adr, FixLoiKhongChet3, 5);
        hook((void*)FixLoiKhongChet4Adr, FixLoiKhongChet4, 5);
        hook((void*)FixLoiKhongChet5Adr, FixLoiKhongChet5, 5);
        hook((void*)FixLoiKhongChet6Adr, FixLoiKhongChet6, 7);
        hook((void*)FixLoiKhongChet7Adr, FixLoiKhongChet7, 5);
        hook((void*)FixLoiKhongChet8Adr, FixLoiKhongChet8, 7);
        hook((void*)FixLoiKhongChet9Adr, FixLoiKhongChet9, 5);
        hook((void*)FixLoiKhongChet10Adr, FixLoiKhongChet10, 5);
        hook((void*)FixLoiKhongChet11Adr, FixLoiKhongChet11, 5);
        hook((void*)FixLoiKhongChet12Adr, FixLoiKhongChet12, 5);
        hook((void*)FixLoiKhongChet13Adr, FixLoiKhongChet13, 5);
        hook((void*)FixLoiKhongChet14Adr, FixLoiKhongChet14, 5);
        hook((void*)FixLoiKhongChet15Adr, FixLoiKhongChet15, 7);
        hook((void*)FixLoiKhongChet16Adr, FixLoiKhongChet16, 5);
        hook((void*)FixLoiKhongChet17Adr, FixLoiKhongChet17, 5);
        hook((void*)FixLoiKhongChet18Adr, FixLoiKhongChet18, 5);
        hook((void*)FixLoiKhongChet19Adr, FixLoiKhongChet19, 5);
        hook((void*)FixLoiKhongChet20Adr, FixLoiKhongChet20, 5);
        hook((void*)FixLoiKhongChet21Adr, FixLoiKhongChet21, 5);
        hook((void*)FixLoiKhongChet22Adr, FixLoiKhongChet22, 5);
        hook((void*)FixLoiKhongChet23Adr, FixLoiKhongChet23, 5);
        hook((void*)FixLoiKhongChet24Adr, FixLoiKhongChet24, 5);
        hook((void*)FixLoiKhongChet25Adr, FixLoiKhongChet25, 5);
        hook((void*)FixLoiKhongChet26Adr, FixLoiKhongChet26, 6);
        hook((void*)FixLoiKhongChet27Adr, FixLoiKhongChet27, 6);
        hook((void*)FixLoiKhongChet29Adr, FixLoiKhongChet29, 6);
        hook((void*)MoGioiHanInchantOKhoAdr, MoGioiHanInchantOKho, 6);
        hook((void*)MoGioiHanDamg2Adr, MoGioiHanDamg2, 7);
        hook((void*)MoGioiHanDamg3Adr, MoGioiHanDamg3, 7);
        hook((void*)MoGioiHanDamg4Adr, MoGioiHanDamg4, 7);
        hook((void*)MoGioiHanDamg1Adr, MoGioiHanDamg1, 7);
        hook((void*)MoGioiHanDamg6Adr, MoGioiHanDamg6, 7);
        hook((void*)MoGioiHanDamg5Adr, MoGioiHanDamg5, 7);
        hook((void*)ChangeAddressInchant3Adr, ChangeAddressInchant3,7);
        hook((void*)ChangeAddressInchant31Adr, ChangeAddressInchant31, 6);
        hook((void*)ChangeAddressInchant4Adr, ChangeAddressInchant4,7);
        hook((void*)ChangeAddressInchant41Adr, ChangeAddressInchant41,6);
        hook((void*)ChangeAddressInchant5Adr, ChangeAddressInchant5,7);
        hook((void*)ChangeAddressInchant51Adr, ChangeAddressInchant51,6);
        hook((void*)ChangeAddressInchant6Adr, ChangeAddressInchant6,7);
        hook((void*)ChangeAddressInchant61Adr, ChangeAddressInchant61,6);
        hook((void*)ChangeAddressInchant7Adr, ChangeAddressInchant7,7);
        hook((void*)ChangeLimitedInchantAdr, ChangeLimitedInchant,5);
        hook((void*)ChangeLimitedInchant2Adr, ChangeLimitedInchant2,5);
        hook((void*)ChangeLimitedInchant3Adr, ChangeLimitedInchant3,5);
        hook((void*)ChangeLimitedInchant4Adr, ChangeLimitedInchant4,5);
        hook((void*)ChangeLimitedInchant5Adr, ChangeLimitedInchant5,5);
        hook((void*)ChangeLimitedInchant6Adr, ChangeLimitedInchant6,5);
        hook((void*)ChangeLimitedInchant7Adr, ChangeLimitedInchant7,5);
        hook((void*)ChangeLimitedInchant9Adr, ChangeLimitedInchant9,6);

        hook((void*)ChangeAddressInchant2Adr, ChangeAddressInchant2, 7);
        hook((void*)ChangeAddressInchantAdr, ChangeAddressInchant, 7);
        hook((void*)ChangeLimiteInchant4Adr, ChangeLimiteInchant4, 7);
        hook((void*)ChangeLimiteInchantAdr, ChangeLimiteInchant, 7);
        hook((void*)ChangeLimiteInchant2Adr, ChangeLimiteInchant2, 7);
        hook((void*)ChangeLimiteInchant3Adr, ChangeLimiteInchant3, 7);
        hook((void*)ChangeInchantGetLoad5Adr, ChangeInchantGetLoad5, 6);
        hook((void*)ChangeInchantGetLoad4Adr, ChangeInchantGetLoad4, 6);
        hook((void*)ChangeInchantGetLoad3Adr, ChangeInchantGetLoad3, 6);
        hook((void*)ChangeInchantGetLoad2Adr, ChangeInchantGetLoad2, 6);
        hook((void*)ChangeInchantGetLoadAdr, ChangeInchantGetLoad, 6);

        //
        //hook((void*)PauseCheckWhenMoveAdr, PauseCheckWhenMove, 6);
#ifdef Fun289   
        DWORD BoQuaXoaBuffPetAdr = 0x004F5695;
        hook((void*)BoQuaXoaBuffPetAdr, BoQuaXoaBuffPet, 8);
        DWORD BoQuaXoaBuffPet2Adr = 0x004F5973;
        hook((void*)BoQuaXoaBuffPet2Adr, BoQuaXoaBuffPet2, 8);
        DWORD HuyPetKhiOutGameAdr = 0x00602391;
        hook((void*)HuyPetKhiOutGameAdr, HuyPetKhiOutGame, 8);
        DWORD HuyPetKhiOutGame2Adr = 0x00602643;
        hook((void*)HuyPetKhiOutGame2Adr, HuyPetKhiOutGame2, 7);

        DWORD BypassCheckTimeEffectAdr = 0x004ECABD;
        DWORD CheckTimePackageAntiAdr = 0x00694AA3;
        //hook((void*)CheckTimePackageAntiAdr, CheckTimePackageAnti, 6);

        DWORD CheckSkillBeforeAddMasteryAdr = 0x004CC56A;
        hook((void*)CheckSkillBeforeAddMasteryAdr, CheckSkillBeforeAddMastery, 7);
        hook((void*)BypassCheckTimeEffectAdr, BypassCheckTimeEffect, 6);
        DWORD AddInchantForItemBoxAdr = 0x00509FDA;
        hook((void*)AddInchantForItemBoxAdr, AddInchantForItemBox, 6);
        DWORD MovePetUserAdr = 0x005CDF51;
        hook((void*)MovePetUserAdr, MovePetUser, 6);
        DWORD AddDmgAdr = 0x005CE39A;
        hook((void*)FixLoiXepChongTinVatAdr, FixLoiXepChongTinVat, 7);
        hook((void*)KhoaBuffCritBanThanAdr, KhoaBuffCritBanThan, 6);
        hook((void*)KhoaBuffCritKhacPhaiAdr, KhoaBuffCritKhacPhai, 5);
        //hook((void*)AcceptValueNewPhongAnAdr, AcceptValueNewPhongAn, 7);
        //hook((void*)GetOptionAdr, GetOption, 6);
        //hook((void*)ByPassQ1Adr, ByPassQ1, 6);
        //hook((void*)ByPassQ2Adr, ByPassQ2, 6);
        hook((void*)NewInchant1Adr, NewInchant1, 5);
        //hook((void*)SendInfoLeveltoUserAdr, SendInfoLeveltoUser,6);
        //hook((void*)ByPassRecordLogAdr, ByPassRecordLog, 6);
        //hook((void*)SendMoneyAfterBuyAdr, SendMoneyAfterBuy, 7);
        //hook((void*)KiemTraMuaShopAdr, KiemTraMuaShop, 8);
        //hook((void*)KiemTraMuaShopBoQuaTruTienAdr, KiemTraMuaShopBoQuaTruTien, 5);
        //hook((void*)KiemTraMuaShopBoQuaTruTien2Adr, KiemTraMuaShopBoQuaTruTien2, 5);
        //hook((void*)injectHookCharInforAdr, injectHookCharInfor, 7);
        //hook((void*)ChangeTypeLevelUpAdr, ChangeTypeLevelUp, 7);
        //hook((void*)KiemTraRankLeveAdr, KiemTraRankLevel, 6);
#endif // Fun289


    //
#ifdef TestTK
        hook((void*)KiemTraPheBoQuaDmgAdr, KiemTraPheBoQuaDmg, 6);
        hook((void*)KiemTraPheBoQuaDmg2Adr, KiemTraPheBoQuaDmg2, 6);
        hook((void*)KiemTraPheBoQuaDmg3Adr, KiemTraPheBoQuaDmg3, 6);
        hook((void*)GetPozTongKimAdr, GetPozTongKim, 6);
        hook((void*)GetValueTongKimAdr, GetValueTongKim, 6);
        hook((void*)GetGiaTriVaoMapTKAdr, GetGiaTriVaoMapTK, 6);
#endif // TestTK

#ifdef TestHapMau
        
        //hook((void*)TestReadFileAdr, TestReadFile, 5);
        hook((void*)FixAmMauHap2Adr, FixAmMauHap2, 6);
        hook((void*)FixAmMauHapNukerAdr, FixAmMauHapNuker, 6);
        hook((void*)FixAmMauHapAdr, FixAmMauHap, 6);
        //hook((void*)KhoaHapKhiPKAdr, KhoaHapKhiPK, 7);
        hook((void*)KhoaHapKhiPK2Adr, KhoaHapKhiPK2, 7);
        /*hook((void*)KhoaHapKhiPK3Adr, KhoaHapKhiPK3, 7);
        hook((void*)KhoaHapKhiPK4Adr, KhoaHapKhiPK4, 7);
        hook((void*)KhoaHapKhiPK5Adr, KhoaHapKhiPK5, 7);
        hook((void*)KhoaHapKhiPK6Adr, KhoaHapKhiPK6, 7);
        hook((void*)KhoaHapKhiPK7Adr, KhoaHapKhiPK7, 7);
        hook((void*)KhoaHapKhiPK8Adr, KhoaHapKhiPK8, 7);
        hook((void*)KhoaHapKhiPK9Adr, KhoaHapKhiPK9, 7);
        hook((void*)KhoaHapKhiPK10Adr, KhoaHapKhiPK10, 7);*/
#endif // TestHapMau
#ifdef FuncCp
        //hook((void*)ShowMoreUserAdr, ShowMoreUser, 10);
        hook((void*)ResetRanDomInchantAdr, ResetRanDomInchant, 5);
        hook((void*)ResetRanDomInchant2Adr, ResetRanDomInchant2, 5);
        hook((void*)GetInforFromTextAdr, GetInforFromText, 9);
        hook((void*)BypassAddMillAdr, BypassAddMill, 6);
        //hook((void*)TruDiemNhanQuaAdr, TruDiemNhanQua, 7);
        //hook((void*)ThemDmgChoBossAdr, ThemDmgChoBoss, 6);
        //hook((void*)ThongBaoDaNhatQuaAdr, ThongBaoDaNhatQua, 5);
        //hook((void*)AddBonusEventEXp3Adr, AddBonusEventEXp3, 9);
        //hook((void*)StoreInfoUserTxt3Adr, StoreInfoUserTxt3, 5);
        //hook((void*)StoreInfoUserTxt2Adr, StoreInfoUserTxt2, 8);
        //hook((void*)StoreInfoUserTxtAdr, StoreInfoUserTxt, 6);
        //hook((void*)Giam1NuaDmgAdr, Giam1NuaDmg, 5);
        //hook((void*)Giam1NuaDmg2Adr, Giam1NuaDmg2, 5);
        //Bo Qua Slot 8C>
        /*hook((void*)ChangeSlotRoom1Adr, ChangeSlotRoom1, 6);
        hook((void*)ChangeSlotRoom2Adr, ChangeSlotRoom2, 6);
        hook((void*)ChangeSlotRoom3Adr, ChangeSlotRoom3, 6);
        hook((void*)ChangeSlotRoom4Adr, ChangeSlotRoom4, 6);
        hook((void*)ChangeSlotRoom5Adr, ChangeSlotRoom5, 6);
        hook((void*)ChangeSlotRoom6Adr, ChangeSlotRoom6, 6);
        //hook((void*)ChangeSlotRoom7Adr, ChangeSlotRoom7, 6);
        hook((void*)ChangeSlotRoom8Adr, ChangeSlotRoom8, 6);
        hook((void*)ChangeSlotRoom9Adr, ChangeSlotRoom9, 6);
        hook((void*)ChangeSlotRoom10Adr, ChangeSlotRoom10, 6);
        hook((void*)ChangeSlotRoom11Adr, ChangeSlotRoom11, 6);
        hook((void*)ChangeSlotRoom12Adr, ChangeSlotRoom12, 6);
        hook((void*)ChangeSlotRoom13Adr, ChangeSlotRoom13, 6);
        hook((void*)ChangeSlotRoom14Adr, ChangeSlotRoom14, 6);
        hook((void*)ChangeSlotRoom15Adr, ChangeSlotRoom15, 6);
        hook((void*)ChangeSlotRoom16Adr, ChangeSlotRoom16, 6);
        hook((void*)ChangeSlotRoom17Adr, ChangeSlotRoom17, 6);
        hook((void*)ChangeSlotRoom18Adr, ChangeSlotRoom18, 6);
        hook((void*)ChangeSlotRoom19Adr, ChangeSlotRoom19, 6);
        hook((void*)ChangeSlotRoom20Adr, ChangeSlotRoom20, 6);
        hook((void*)ChangeSlotRoom21Adr, ChangeSlotRoom21, 6);
        hook((void*)ChangeSlotRoom221Adr, ChangeSlotRoom221, 6);
        hook((void*)ChangeSlotRoom22Adr, ChangeSlotRoom22, 6);
        hook((void*)ChangeSlotRoom23Adr, ChangeSlotRoom23, 6);
        hook((void*)ChangeSlotRoom24Adr, ChangeSlotRoom24, 6);
        hook((void*)ChangeSlotRoom25Adr, ChangeSlotRoom25, 6);
        hook((void*)ChangeSlotRoom26Adr, ChangeSlotRoom26, 6);
        hook((void*)ChangeSlotRoom27Adr, ChangeSlotRoom27, 6);*/
#endif // FuncCp

#ifdef TestFuncMoi
        hook((void*)FixLoiMaxDoKTCAdr, FixLoiMaxDoKTC, 8);
        hook((void*)FixCritAllAdr, FixCritAll, 5); 
        hook((void*)FixMaxCritSendAdr, FixMaxCritSend, 5);
        hook((void*)FixSendCrit2Adr, FixSendCrit2, 5);
        hook((void*)FixSendCrit3Adr, FixSendCrit3, 5);
        hook((void*)TestSkillAOEAdr, TestSkillAOE, 5);
        hook((void*)TestSkillAOE2Adr, TestSkillAOE2, 5);
        hook((void*)ChageSizepkRoundingResultPvpAdr, ChageSizepkRoundingResultPvp, 7);
#endif // TestFuncMoi

#ifdef TestNewFunc
        hook((void*)AcceptOptionHanhNangAdr, AcceptOptionHanhNang, 5);
        hook((void*)ByPassGMADDSlot96Adr, ByPassGMADDSlot96, 5);
        hook((void*)ByPassSaiDoiTuongAdr, ByPassSaiDoiTuong, 7);
        hook((void*)FixLoiDeoTinVatMatDoAdr, FixLoiDeoTinVatMatDo, 5);
        hook((void*)ChangeLenghtpkSmashResultPvp2Adr, ChangeLenghtpkSmashResultPvp2, 7);
        hook((void*)AddBonusForPackageEXPAdr, AddBonusForPackageEXP, 5);
        hook((void*)AddNewOptClothAdr, AddNewOptCloth, 10);
        hook((void*)AddOptFromSetItemAdr, AddOptFromSetItem, 7);
        hook((void*)DeleteOptSetItemAdr, DeleteOptSetItem, 10);
        hook((void*)TinhToanDeffVaPhanDamChieuThucKyAdr, TinhToanDeffVaPhanDamChieuThucKy, 8);
        hook((void*)TinhToanDeffVaPhanDamNukerAdr, TinhToanDeffVaPhanDamNuker, 5);
        hook((void*)TinhToanDeffVaPhanDamNuker2Adr, TinhToanDeffVaPhanDamNuker2, 10);
        hook((void*)TinhToanDeffVaPhanDamAdr, TinhToanDeffVaPhanDam, 5);
        hook((void*)TestDoiGiaTriDeffAdr, TestDoiGiaTriDeff, 7);
        hook((void*)TestDoiGiaTriDeffNukerAdr, TestDoiGiaTriDeffNuker, 7);
       
        hook((void*)TangPhanTramDmgNukerAdr, TangPhanTramDmgNuker, 6);
        hook((void*)TruSatThuongKCAdr, TruSatThuongKC, 5);
        hook((void*)TruSatThuongAdr, TruSatThuong, 6);
        hook((void*)TruSatThuong1Adr, TruSatThuong1, 6);
        hook((void*)TangPhanTramDmgThucKyAdr, TangPhanTramDmgThucKy, 6);
        hook((void*)TangPhanTramDmgTankAdr, TangPhanTramDmgTank, 6);
        hook((void*)TangTiLeCombineAdr, TangTiLeCombine, 6);
        hook((void*)GetSlotFailAdr, GetSlotFail, 8);
        hook((void*)DieuCheGiuNguyenTiLeAdr, DieuCheGiuNguyenTiLe, 7);
        hook((void*)GetSlotSuccessAdr, GetSlotSuccess, 6);
        hook((void*)ChangeValueCombine3Adr, ChangeValueCombine3, 6);
        hook((void*)ChangeValueCombine2Adr, ChangeValueCombine2, 6);
        hook((void*)ChangeValueCombineAdr, ChangeValueCombine, 7);
        hook((void*)GetEventKillMobAdr, GetEventKillMob, 5);
        hook((void*)AddEventKillMobAdr, AddEventKillMob, 5);
        hook((void*)GetDmgSkillFromBossAdr, GetDmgSkillFromBoss, 6);
        hook((void*)GetDmgFromBossAdr, GetDmgFromBoss, 7);
        hook((void*)GetDmgSkillNukerFromBossAdr, GetDmgSkillNukerFromBoss, 6);
#endif // TestNewFunc
#ifdef Check_TimeEvent
        //hook((void*)GetTimeEventAdr, GetTimeEvent, 6);
#endif // Check_TimeEvent
#ifdef EventZplay
        hook((void*)GetTimeEventAdr, GetTimeEvent, 6);
#endif // EventZplay

        hook((void*)TestRediemAdr, TestRediem, 5);
        hook((void*)AllowlearnSkillAdr, AllowlearnSkill, 8);
        hook((void*)TestFixAmDamg1Adr, TestFixAmDamg1, 9);
        hook((void*)KhongXoaVpDieuCheAdr, KhongXoaVpDieuChe, 10);
        hook((void*)AddOptionCloth2Adr, AddOptionCloth2, 7);
        hook((void*)FixGiaoDichMatDoHanhTrang8CAdr, FixGiaoDichMatDoHanhTrang8C, 5);
        //hook((void*)AddBonusEventEXp2Adr, AddBonusEventEXp2, 6);
        //hook((void*)AddBonusEventEXpAdr, AddBonusEventEXp, 6);
        hook((void*)ThayDoiTiLeQuanAo1Adr, ThayDoiTiLeQuanAo1, 6);
        hook((void*)ThayDoiTiLeQuanAo2Adr, ThayDoiTiLeQuanAo2, 5);
        hook((void*)ReloadInforNickAdr, ReloadInforNick, 6);
        hook((void*)AddNewValueFromNickAdr, AddNewValueFromNick, 10);
        //16Slot
        hook((void*)XoaSlotMoiAdr, XoaSlotMoi, 7);
        hook((void*)UnknowFunAdr, UnknowFun, 9);
        hook((void*)GetAddressNewSlotAdr, GetAddressNewSlot, 6);
        hook((void*)GetAddressNewSlot2Adr, GetAddressNewSlot2, 6);
        hook((void*)CheckADdressNewSlotAdr, CheckADdressNewSlot, 10);
        hook((void*)CheckADdressNewSlot2Adr, CheckADdressNewSlot2,10);
        //hook((void*)CheckADdressNewSlot3Adr, CheckADdressNewSlot3, 10);
        hook((void*)CheckADdressNewSlot4Adr, CheckADdressNewSlot4, 10);
        hook((void*)CheckADdressNewSlot5Adr, CheckADdressNewSlot5,10);
        hook((void*)CheckADdressNewSlot6Adr, CheckADdressNewSlot6, 10);
        hook((void*)CheckADdressNewSlot7Adr, CheckADdressNewSlot7, 10);
        //
        hook((void*)GioiHanDmgVlPvpAdr, GioiHanDmgVlPvp, 6);
        hook((void*)GioiHanDmgkcPvpAdr, GioiHanDmgkcPvp, 6);
        hook((void*)GioiHanDmgVlPvpSauDeffAdr, GioiHanDmgVlPvpSauDeff, 5);
        hook((void*)GioiHanDmgKCPvpSauDeffAdr, GioiHanDmgKCPvpSauDeff, 5);
        hook((void*)PhongThuChiMang23Adr, PhongThuChiMang23, 5);
        hook((void*)PhongThuChiMang24Adr, PhongThuChiMang24, 5);
    hook((void*)ChageSizepkRoundingResultMobSendAdr, ChageSizepkRoundingResultMobSend, 7);
    hook((void*)ChageSizepkRoundingResultMobSendNuker2Adr, ChageSizepkRoundingResultMobSendNuker2, 7);
    //
    hook((void*)PhongThuChiMangKCAdr, PhongThuChiMangKC, 6);
    hook((void*)PhongThuChiMang2KCAdr, PhongThuChiMang2KC, 6);
    hook((void*)PhongThuChiMang2Adr, PhongThuChiMang2, 5);
    hook((void*)PhongThuChiMangAdr, PhongThuChiMang, 5);
    hook((void*)ChangeCodePercentHealthMob2Adr, ChangeCodePercentHealthMob2, 9);
    hook((void*)ChangeCodePercentHealthMobAdr, ChangeCodePercentHealthMob, 6);
    hook((void*)AddNewValue1Adr, AddNewValue1, 5);
    hook((void*)AddNewValue2Adr, AddNewValue2, 5);

    hook((void*)ChangeLenghtPvpModRESULT_MOBAdr, ChangeLenghtPvpModRESULT_MOB, 7);
    hook((void*)ChangeLenghtActiveResultPvpAdr, ChangeLenghtActiveResultPvp, 7);
    hook((void*)ChangeLenghtpkSmashResultMobAdr, ChangeLenghtpkSmashResultMob, 7);
    hook((void*)ChangeLenghtpkSmashResultPvpAdr, ChangeLenghtpkSmashResultPvp, 7);
    hook((void*)ImprisonmentPlayerAdr, ImprisonmentPlayer, 5);
#ifdef EventHSBLoanChien
    hook((void*)AddBloodPkAdr, AddBloodPk, 9);
#endif // EventHSBLoanChien
    hook((void*)IncFailedAdr, IncFailed, 7);
    //Test
    hook((void*)LoadChienAdr, runFuneditZonetest, 7);
    //hook((void*)MoveMobNearUserAdr, MoveMobNearUser, 6);
    //hook((void*)ByPassCheckRun2Adr, ByPassCheckRun2, 6);
    //hook((void*)DisableMoveRandomPetAdr, DisableMoveRandomPet, 7);
    //hook((void*)TestMovePetAdr, TestMovePet, 6);

    
    hook((void*)FixErrorDmgAdr, FixErrorDmg, 10);


    hook((void*)FixMaxCritNuker3Adr, FixMaxCritNuker3, 7);
    hook((void*)FixMaxCritNuker4Adr, FixMaxCritNuker4, 7);
    hook((void*)FixMaxCritNuker5Adr, FixMaxCritNuker5, 7);
    hook((void*)FixMaxCritNuker31Adr, FixMaxCritNuker31, 6);
    hook((void*)FixMaxCritNuker41Adr, FixMaxCritNuker41, 6);
    hook((void*)FixMaxCritNuker51Adr, FixMaxCritNuker51, 6); 

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
    hook((void*)MoreDamageSkillNuker1Adr, MoreDamageSkillNuker1, 7);
    hook((void*)MoreDamageSkillNukerAdr, MoreDamageSkillNuker, 7);
    hook((void*)MoreDamageThuc1Adr, MoreDamageThuc1, 8);
    hook((void*)MoreDamageThuc2Adr, MoreDamageThuc2, 8);
    hook((void*)MoreDamageThuc3Adr, MoreDamageThuc3, 8);

    //hook((void*)CheckTypeKcorPhAdr, CheckTypeKcorPh, 6);
    hook((void*)AcceptType8Adr, AcceptType8, 6);
    hook((void*)SendPacketIncCloAdr, SendPacketIncClo, 10);
    hook((void*)CheckIncClotAdr, CheckIncClot, 5);
    hook((void*)AddOptionClothAdr, AddOptionCloth, 7);
    hook((void*)LockSkill, DisableEffect, 6);
    //hook((void*)CheckTypeUsedAdr, CheckTypeUsed, 6); Tang Thoi gian Delay Su Dung Potion
    hook((void*)AcceptIntNewItemAdr, AcceptIntNewItem, 7);
    hook((void*)FixResetWeaponAdr, FixResetWeapon, 7);
    jmpBackAdd = hookAddress + hooklenght;
    jmpBackAdd2 = hookAddSKill + hooklenghtAddSkill;
    hook((void*)hookAddress, DeccoEffect, hooklenght);
    hook((void*)UseItemSpawAdr, UseItemSpawn, 6);
    //hook((void*)ExchangeItemAdr, ExchangeItem, 6);
    hook((void*)MoreDamageDr, MoreDamageSkill, 7);
    hook((void*)FixIncahnt, FixInchantBlood, 10);
    //hook((void*)AdreFixDame1, FixDmage1, hooklenght);
    hook((void*)AdInchant, InChantCloth, 9);
    /*hook((void*)AdreFixDame2, FixDmage2, hooklenght);
    hook((void*)AdreFixDame3, FixDmage3, hooklenght);
    hook((void*)AdreFixDame4, FixDmage4, hooklenght);*/
    ReadLuckBox();
    Bypass:
    uintptr_t moBase = (uintptr_t)GetModuleHandle(NULL);
    gms_ctrl_add_skill1 = (gms_ctrl_add_skill)(moBase + 0x0020E2E2);
    gms_ctrl_rem_skill1 = (gms_ctrl_rem_skill)(moBase + 0x0020E374);
    get_name1 = (get_name)(moBase + 0x1F690);
    makeUniqueIDItem = (SM_Item_Make_UniqueID)(moBase + 0x23AC95);
    edit_zone_gamer = (gms_edit_zone)(moBase + 0x20D6B1);
    bool checkrunEvent = true;

    EndCode:
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

