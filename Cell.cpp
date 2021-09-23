#include "Cell.h"

std::ostream &operator<<(std::ostream &st, Cell &cell)
{
	if (cell.isClosed()) {
		st << char(254);
	} else if (cell.hasMine()) {
		st << char(15);
	} else {
		st << cell.number();
	}

	return st;
}

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
