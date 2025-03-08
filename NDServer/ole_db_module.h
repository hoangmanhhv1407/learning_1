#pragma once
#include "Accessors.h"
#include "My_ole_db.h"

CDataSource ds;
CSession ss;

typedef CDB_Command<CEventGetCountAccessor> CEventGetCount;