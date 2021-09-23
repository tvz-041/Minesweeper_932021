#ifndef CELL_H
#define CELL_H

#include <ostream>

class Cell
{
public:
	Cell(const int number = 0);
	Cell(const bool hasMine);
	~Cell() = default;

	bool isClosed() const;
	bool hasMine() const;
	int number() const;

	void close();
	void open();
	void setClosed(const bool isClosed);
	void setMine(const bool hasMine);
	void setNumber(const int number);

private:
	void init(const int number = 0, const bool hasMine = false, const bool isClosed = true);

	///TODO: implement enum
	bool m_isClosed;
	bool m_hasMine;

	///TODO: name refactor: number -> digit
	int m_number;
};

std::ostream &operator<<(std::ostream &st, Cell &cell);

inline bool Cell::isClosed() const
{
	return m_isClosed;
}

inline bool Cell::hasMine() const
{
	return m_hasMine;
}

inline int Cell::number() const
{
	return m_number;
}

inline void Cell::close()
{
	setClosed(true);
}

inline void Cell::open()
{
	setClosed(false);
}

inline void Cell::setClosed(const bool isClosed)
{
	m_isClosed = isClosed;
}

inline void Cell::setMine(const bool hasMine)
{
	m_hasMine = hasMine;
}

inline void Cell::setNumber(const int number)
{
	m_number = number;
}

#endif // CELL_H
