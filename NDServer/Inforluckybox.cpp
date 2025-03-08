#include "pch.h"
#include "Inforluckybox.h"
#define Test_Open_File "nfofile/luckybox.txt"
bool BoxLucky::ReadFileText()
{
	FILE* fp;
	if ((fp = fopen(Test_Open_File,"r")) == NULL)
	{
		std::cout << "Error Read LuckyBox" << std::endl;
		return false;
	}
	char buf[255] = { 0 };
	char rankR[4];
	int nRead = 1;
	DataBox* BoxRef = NULL;
	int _TEMP_[6] = {0};
	u_short idRank2;
	int i = 0;
	bool BBRead = true;
	while (!feof(fp))
	{
		BoxRef = new DataBox;
		::ZeroMemory(BoxRef, sizeof(DataBox));
		i = 0;
		if (fgets(buf,sizeof(buf),fp) == NULL)
		{
			break;
		}
		if (buf[0]== 'E')
		{
			break;
		}
		if (sscanf(buf,"%d", &idRank2) == 1)
		{
			BoxRef->RankIDBox = static_cast<u_short>(idRank2);
			ReloadValue:
			if (fgets(buf, sizeof(buf), fp) == NULL)
			{
				break;
			}
			if (buf[0] == ';')
			{
				goto LoopLoadNextRank;
			}
			nRead = sscanf(buf, "%d %d %d %d %d %d", &_TEMP_[0], &_TEMP_[1], &_TEMP_[2], &_TEMP_[3], &_TEMP_[4], &_TEMP_[5]);
			if (nRead < 6)
			{
				std::cout << "Error Load File" << std::endl;
			}

			if (BoxRef == NULL)
			{
				BBRead = false;
			}
			
			BoxRef->Item[i].indexItem = static_cast<int>(_TEMP_[0]);
			BoxRef->Item[i].idType = static_cast<BYTE>(_TEMP_[1]);
			BoxRef->Item[i].idItem = static_cast<int>(_TEMP_[2]);
			BoxRef->Item[i].CountId = static_cast<int>(_TEMP_[3]);
			BoxRef->Item[i].InchantItem = static_cast<BYTE>(_TEMP_[4]);
			BoxRef->Item[i].RateIt = static_cast<int>(_TEMP_[5]);
			i++;
			goto ReloadValue;
		}
		LoopLoadNextRank:
		std::cout << *(&BoxRef->RankIDBox) << std::endl;
		m_LuckyBoxmap[BoxRef->RankIDBox] = BoxRef;
	}
	return BBRead;
}