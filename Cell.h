#ifndef CELL_H
#define CELL_H

#include <ostream>

class Cell
{
public:
    enum Value
    {
        Mine = -1,
        Digit0,
        Digit1,
        Digit2,
        Digit3,
        Digit4,
        Digit5,
        Digit6,
        Digit7,
        Digit8
    };

    Cell(const Value value = Digit0);
	~Cell() = default;

	bool isClosed() const;
	bool hasMine() const;
    Value value() const;

	void close();
	void open();
    void setClosed(const bool isClosed);
    void setValue(const Value value);

private:
    void init(const Value value, const bool isClosed = true);

	bool m_isClosed;
    Value m_value;
};

std::ostream &operator<<(std::ostream &st, Cell &cell);

inline bool Cell::isClosed() const
{
	return m_isClosed;
}

inline bool Cell::hasMine() const
{
    return (m_value == Value::Mine);
}

inline Cell::Value Cell::value() const
{
    return m_value;
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

inline void Cell::setValue(const Value value)
{
    m_value = value;
}

#endif // CELL_H
