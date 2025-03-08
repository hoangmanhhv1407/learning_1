#pragma once
#include "pch.h"
#include <cassert>

class _XFileInfo
{
public:
	WORD	m_length;
	LPSTR	m_filename;

	_XFileInfo()
	{
		m_length = 0;
		m_filename = NULL;
	}

	~_XFileInfo()
	{
		if (m_filename)
		{
			delete[] m_filename;
			m_filename = NULL;
		}
		m_length = 0;
	}

	void Set(LPSTR filename)
	{
		assert(filename);
		if (m_filename) delete[] m_filename;
		int length = strlen(filename);

		m_filename = new TCHAR[length + 1];
		if (m_filename)
		{
			m_length = length;
			//m_filename[m_length] = 0;
			memset(m_filename, 0, m_length + 1);
			strcpy(m_filename, filename);

			int i = 0; for (i = 0; i < m_length; i++) // make lower class
			{
				if (m_filename[i] >= 97 && m_filename[i] <= 122)
				{
					m_filename[i] -= 32;
				}
			}
		}
		else
		{
			std::cout << "Error Load " << std::endl;
		}
	}
};