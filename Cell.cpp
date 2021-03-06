#include "Cell.h"

Cell::Cell(const int row, const int column, const Value value) :
    m_row(row),
    m_column(column)
{
    init(value);
}

//private:

void Cell::init(const Value value, const bool isClosed, const bool hasFlag)
{
    m_hasFlag = hasFlag;
    m_isClosed = isClosed;
    m_value = value;
}

//external functions:

std::ostream &operator<<(std::ostream &st, Cell &cell)
{
	if (cell.isClosed()) {
		st << char(254);
	} else if (cell.hasMine()) {
		st << char(15);
	} else {
        st << cell.value();
	}

	return st;
}
