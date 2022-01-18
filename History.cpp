#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) 
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 0; r < m_rows; r++) 
	{
		for (int c = 0; c < m_cols; c++) 
		{
			m_mesa[r][c] = 0;
		}
	}
}

bool History::record(int r, int c) 
{
if (r > m_rows || c > m_cols || r < 1 || c < 1)
	{
		return false;
	}

	else
	{
		m_mesa[r-1][c-1]++;
		return true;
	}
}

void History::display() const 
{
	clearScreen();
	for (int r = 0; r < m_rows; r++) 
	{
		for (int c = 0; c < m_cols; c++) 
		{
			if (m_mesa[r][c] == 0)
			{
				cout << ".";
			}
			else
			{
				cout << char('A' + m_mesa[r][c] - 1);
			}		
		}
		cout << '\n';
	}
	cout << endl;
}