#pragma once
#include <objbase.h>
#include <atldbcli.h>
#include <oledb.h>
#include <atldbcli.h>

template <class TAccessor = CNoAccessor,template <typename T> class TRowset = CRowset>
class CDB_Command
{
protected:
	CCommand<CAccessor<TAccessor>, TRowset >* m_pSet;
public:
	CDB_Command()
	{
		m_pSet = new CCommand<CAccessor<TAccessor>, TRowset >;
	}
	~CDB_Command()
	{
		delete m_pSet;
	}

	HRESULT OpenCommand(CSession session)
	{
		return  m_pSet->Open(session);
	}

	void CloseCommand()
	{
		m_pSet->Close();
		m_pSet->ReleaseCommand();
	}

	TAccessor* GetAccessor()
	{
		return (TAccessor*)m_pSet;
	}

private:
}; 