#pragma once
#include "pch.h"

class CEventGetCountAccessor
{
public:
	int uniqueID;
	int idType;
	int idItem;
	int CountUsed;

	DEFINE_COMMAND_EX(CEventGetCountAccessor,L"{ ? = CALL dbo.GetCountItemUsed(?,?,?)}")

	BEGIN_PARAM_MAP(CEventGetCountAccessor)
		SET_PARAM_TYPE(DBPARAMIO_OUTPUT)
		COLUMN_ENTRY(1,CountUsed)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(2, uniqueID)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(3, idType)
		SET_PARAM_TYPE(DBPARAMIO_INPUT)
		COLUMN_ENTRY(4, idItem)
	END_PARAM_MAP()
};