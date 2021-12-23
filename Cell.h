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

    Cell(const int row, const int column, const Value value = Digit0);
	~Cell() = default;

    inline bool isClosed() const;
    inline bool hasFlag() const;
    inline bool hasMine() const;
    inline Value value() const;

    inline int row() const;
    inline int column() const;

    inline void close();
    inline void open();

    inline void setClosed(const bool isClosed);
    inline void setValue(const Value value);
    inline void setFlag(const bool flag);

private:
    void init(const Value value, const bool isClosed = true, const bool hasFlag = false);

	bool m_isClosed;
    bool m_hasFlag;
    Value m_value;

    int m_row;
    int m_column;
};

std::ostream &operator<<(std::ostream &st, Cell &cell);

inline bool Cell::isClosed() const
{
	return m_isClosed;
}

inline bool Cell::hasFlag() const
{
    return m_hasFlag;
}

inline bool Cell::hasMine() const
{
    return (m_value == Value::Mine);
}

inline Cell::Value Cell::value() const
{
    return m_value;
}

inline int Cell::row() const
{
    return m_row;
}

inline int Cell::column() const
{
    return m_column;
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

inline void Cell::setFlag(const bool flag)
{
    m_hasFlag = flag;
}

inline void Cell::setValue(const Value value)
{
    m_value = value;
}

#endif // CELL_H
