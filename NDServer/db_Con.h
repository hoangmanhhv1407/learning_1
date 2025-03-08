#pragma once
#include <objbase.h>
#include <atldbcli.h>
#include <oledb.h>
#include "ole_db_module.h"

class CNDThread
{
public:

	CNDThread() : m_hThread(INVALID_HANDLE_VALUE)
	{
	}

	~CNDThread()
	{
		if (m_hThread != INVALID_HANDLE_VALUE)
		{
			::CloseHandle(m_hThread);
		}

		m_hThread = INVALID_HANDLE_VALUE;
	}


	HANDLE GetHandle() const
	{
		return m_hThread;
	}

	bool Start()
	{
		if (m_hThread == INVALID_HANDLE_VALUE)
		{
			unsigned int threadID = 0;

			m_hThread = (HANDLE)::_beginthreadex(0, 0, ThreadFunction, this, 0, &threadID);

			if (m_hThread == INVALID_HANDLE_VALUE)
			{
				return false;
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	bool Wait() const
	{
		if (!Wait(INFINITE))
		{
			return false;
		}
		return true;
	}

	bool Wait(DWORD timeoutMillis) const
	{
		// TODO base class? Waitable?
		bool ok;

		DWORD result = ::WaitForSingleObject(m_hThread, timeoutMillis);

		if (result == WAIT_TIMEOUT)
		{
			ok = false;
		}
		else if (result == WAIT_OBJECT_0)
		{
			ok = true;
		}
		else
		{
			ok = false;
		}

		return ok;
	}

	static unsigned int __stdcall ThreadFunction(void* pV)
	{
		int result = 0;

		CNDThread* pThis = (CNDThread*)pV;

		if (pThis)
		{
			try
			{
				result = pThis->Run();
				pThis->Release();
			}
			catch (...)
			{
				printf("CThread::Run Exception\n");
			}
		}

		_endthreadex(result);

		return result;
	}

	void Terminate(
		DWORD exitCode /* = 0 */)
	{
		if (!::TerminateThread(m_hThread, exitCode))
		{
			// TODO we could throw an exception here...
		}
	}

	void Release() {
		m_hThread = INVALID_HANDLE_VALUE;
	}

private:

	virtual int Run() = 0;

	HANDLE m_hThread;

	// No copies do not implement
	CNDThread(const CNDThread& rhs);
	CNDThread& operator=(const CNDThread& rhs);

};
template <typename TNode>
class CPool
{
protected:
	TNode* pMem;
	TNode* pFirst;
	TNode* pEnd;
	size_t	m_size;

public:
	CPool(size_t size) : pMem(NULL), pFirst(NULL), pEnd(NULL), m_size(0)
	{
		pMem = new TNode[size];
		for (u_int i = 0; i < size; i++)
		{
			push_back(&pMem[i]);			// 단방향 링크드 리스트를 만든다..			
		}
	}
	~CPool()
	{
		delete[] pMem;
	}

	inline TNode* GetFirst() { return pFirst; }
	inline TNode* GetLast() { return pEnd; }
	inline size_t GetSize() { return m_size; }

	inline TNode* pop(TNode* p = NULL)			// 풀에서 꺼내줌..
	{
		if (p == NULL) p = pFirst;
		if (m_size > 0)
		{

			TNode* pPrev = NULL;
			TNode* pTemp = NULL;
			for (pTemp = pFirst; pTemp != NULL; pTemp = pTemp->pNext)
			{
				if (p == pTemp)						// 조건이 맞을때만 삭제한다.
				{
					if (pPrev == NULL)					// 첫번째 노드
					{
						pFirst = pTemp->pNext;
					}
					else								// 중간 노드..
					{
						pPrev->pNext = pTemp->pNext;
					}
					--m_size;
					break;
				}
				pPrev = pTemp;
			}

			return pTemp;
		}
		else
		{
			return NULL;
		}

	}

	inline void push_back(void* pNode)	// 풀에 넣어줌..
	{
		TNode* pTemp = (TNode*)pNode;
		if (m_size == 0)
		{
			pFirst = pEnd = pTemp;
			m_size = 1;
		}
		else
		{
			pEnd->pNext = pTemp;
			pTemp->pNext = NULL;
			pEnd = pTemp;
			++m_size;
		}
	}

};

class CDB_Connector : public CNDThread
{

protected:

	HRESULT hr;
	CDataSource _db;
	LPCOLESTR lpConStr;

	DWORD dwDBReConnectThreadID;
	HANDLE hDBReConnectThread;

	CPool<CDB_Session>	m_SessionPool;

	int Run()
	{
		bThreadRun = true;


		while (1)
		{
			hr = ReTryConnect();
			if (FAILED(hr))
			{
				Sleep(1000);
				continue;
			}

			Sleep(3000);
			hr = ReSessionLink();
			if (FAILED(hr))
			{
				printf("** Session link failed\n");
				// todo : 여기에 에러처리..
				continue;
			}

			printf("** Session link success\n");
			break;
		}

		bThreadRun = false;

		return 0;
	}

public:

	bool bThreadRun;
	CDB_Connector() : m_SessionPool(0), bThreadRun(false)
	{
	}
	~CDB_Connector()
	{
	}

	inline CDB_Session* NewSession()
	{
		CDB_Session* pTemp = new CDB_Session;
		if (pTemp)
		{
			HRESULT hr = SessionLink(pTemp->GetSessionPtr());
			if (FAILED(hr))
			{
				delete pTemp;
				pTemp = NULL;
			}
			else
			{
				m_SessionPool.push_back(pTemp);
			}
			CSession s = *pTemp->GetSessionPtr();

		}
		return pTemp;
	}

	inline void FreeSession(CDB_Session* p)
	{
		SessionClose(p->GetSessionPtr());
		m_SessionPool.pop(p);
		delete p;
	}

	bool initialize(LPCOLESTR ConStr) /* = OLESTR(str) */
	{
		lpConStr = ConStr;

		// Initialize the OLE COM Library (if STM Model use CoInisialize )
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

		if (hr != S_OK)	// MTM Model Com Lib Initialize
			if (hr != S_FALSE)
				return false;

		// DB Connect	
		hr = _db.OpenFromInitializationString(lpConStr);
		if (FAILED(hr)) {
			return false;
		}
		return true;

	}

	void release()
	{
		_db.Close();
		CoUninitialize();	// release Com Library

	}

	HRESULT ReSessionLink()
	{
		HRESULT hr;
		for (CDB_Session* p = m_SessionPool.GetFirst(); p != NULL; p = p->pNext)
		{
			SessionClose(p->GetSessionPtr());
			hr = SessionLink(p->GetSessionPtr());
			if (FAILED(hr))
			{
				return hr;
			}
		}
		return hr;
	}

	HRESULT ReTryConnect()
	{
		printf("** DB Reconnecting ...\n");
		_db.Close();
		HRESULT hr = _db.OpenFromInitializationString(lpConStr);
		if (FAILED(hr))
		{
			printf("** DB Reconnect failed\n");
		}
		else
		{
			printf("** DB Reconnect success\n");
		}
		return hr;
	}


	HRESULT SessionLink(CSession* pSession)
	{
		//Session open			--Ninedragons	
		return pSession->Open(_db);
	}

	void SessionClose(CSession* pSession)
	{
		pSession->Close();
	}

	CDataSource& GetDataSourse() { return _db; }

	// OLE-DB ReConnection Thread creat & running..	
	void CallReConTh()
	{
		if (bThreadRun == false) {							// Running thread is true		
			Start();
		}
	}


	HRESULT GetHresult() { return hr; }
};
class CDB_Session
{

protected:
	CSession m_session;

public:

	CDB_Session* pNext;
	CDB_Session() : pNext(NULL)
	{
	}

	inline void CloseSession()
	{
		m_session.Close();
	}
	inline CSession* GetSessionPtr()
	{
		return &m_session;
	}

	// Tracsaction function
	HRESULT StartTran(ISOLEVEL ioslevel = ISOLATIONLEVEL_READCOMMITTED)
	{
		return m_session.StartTransaction(ioslevel);
	}

	HRESULT CommitTran()
	{
		return m_session.Commit();
	}

	HRESULT AbortTran()
	{
		return m_session.Abort();
	}

private:
};

class COleDBExcuterBase
{
protected:
	CDB_Connector* const m_pDBCon;
	CDB_Session* const  m_pDBSession;
protected:
	const CSession* const m_session;

public:
	COleDBExcuterBase(CDB_Connector* pDBCon)
		: m_pDBCon(pDBCon),
		m_pDBSession(pDBCon->NewSession()),
		m_session(m_pDBSession->GetSessionPtr())
	{
		if (m_session == NULL)
		{
			throw "";
		}
	}

	void DisConnect()
	{
		m_pDBCon->FreeSession(m_pDBSession);
	}

	virtual ~COleDBExcuterBase() = 0;
	virtual void CallReConTh() = 0;
};
class C_USER_DB_COMMAND : public COleDBExcuterBase
{
private:
	auto_ptr<CEventGetCount> mp_EventGetCount;

public:
	C_USER_DB_COMMAND(CDB_Connector* pDBCon) : COleDBExcuterBase(pDBCon),
		mp_EventGetCount(new CEventGetCount)
	{

	}
	~C_USER_DB_COMMAND()
	{

	}
};