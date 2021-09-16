#include "Cell.h"

Cell::Cell(const int number)
{
	init(number);
}

Cell::Cell(const bool hasMine)
{
	init(0, hasMine);
}


//private:

void Cell::init(const int number, const bool hasMine, const bool isClosed)
{
	m_isClosed = isClosed;
	m_hasMine = hasMine;
	m_number = number;
}
