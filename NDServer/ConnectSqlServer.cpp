#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "ConnectSqlServer.h"
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 240

int connectSQl()
{
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmlHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
	UCHAR insertLog[] = "INSERT INTO [dbo].[UseItem] ([TestTable])VALUES (2)";
	sqlConnHandle = NULL;
	sqlStmlHandle = NULL;

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&sqlEnvHandle))
	{
		goto COMPLETED;
	}
	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle,SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3,0))
	{
		goto COMPLETED;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
	{
		goto COMPLETED;
	}
	
	//Attempt connect SQl

	std::cout << "Attempt Connect SQL \n";

	switch (SQLDriverConnect(sqlConnHandle,NULL,(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=103.200.20.156, 1433;DATABASE=LogUser;UID=logadd;PWD=9dcuuphung@@!@2021;;Trusted=true;",SQL_NTS,retconstring,1024,NULL,SQL_DRIVER_NOPROMPT))
	{
	case SQL_SUCCESS:
		std::cout << "Connect Success\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		std::cout << "Connect Success 1\n";
		break;
	case SQL_INVALID_HANDLE:
		std::cout << "Could not connect to SQL \n";
		goto COMPLETED;
	case SQL_ERROR:
		std::cout << "Could not connect to SQL 2\n";
		goto COMPLETED;
		default:
			break;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT,sqlConnHandle,&sqlStmlHandle))
	{
		goto COMPLETED;
	}
	std::cout << "\n";
	std::cout << "Executing SQl query...\n";

	if (SQL_SUCCESS != SQLPrepare(sqlStmlHandle,(SQLWCHAR*)insertLog,SQL_NTS))
	{
		std::cout << "Erorr query SQl server\n";
		goto COMPLETED;
	}
	if (SQLExecute(sqlStmlHandle) != SQL_SUCCESS || SQLExecute(sqlStmlHandle) != SQL_SUCCESS_WITH_INFO)
	{
		std::cout << "Error Insert\n";
		goto COMPLETED;
	}
	else
	{
		/*SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLINTEGER ptrSqlVersion;
		while (SQLFetch(sqlStmlHandle) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmlHandle, 1, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);
			std::cout << "\nQuery Result: ";
			std::cout << sqlVersion << std::endl;
			return 1;
		}*/
		std::cout << "\nSuccess ";
	}
COMPLETED:
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmlHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	return 0;
}