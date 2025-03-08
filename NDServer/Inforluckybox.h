#pragma once
#include <iostream>
#include <Windows.h>


using namespace std;

typedef unsigned short u_short;
struct ItemInBox
{
	int indexItem;
	BYTE idType;
	int idItem;
	int CountId;
	BYTE InchantItem;
	int RateIt;
};
struct DataBox
{
	int RankIDBox;
	ItemInBox Item[105];
};
class BoxLucky
{
protected:
	map<u_short, DataBox*> m_LuckyBoxmap;
public:
	DataBox* GetInforBox(u_short Rankitem)
	{
		map<u_short, DataBox*>::iterator itr = m_LuckyBoxmap.find(Rankitem);
		if (itr != m_LuckyBoxmap.end())
		{
			return itr->second;
		}
		else
		{
			return NULL;
		}
	}
	BoxLucky()
	{
	}
	~BoxLucky()
	{
		map<u_short, DataBox*>::iterator itr = m_LuckyBoxmap.begin();
		while (itr != m_LuckyBoxmap.end())
		{
			delete itr->second;
			++itr;
		}
		m_LuckyBoxmap.clear();
	}

	bool ReadFileText();
	bool Create();

private:

};
