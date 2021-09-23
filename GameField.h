#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <vector>

#include "Cell.h"

class GameField
{
public:
	GameField(const int size = 10);

	friend std::ostream &operator<<(std::ostream &st, GameField &gameField);
private:
	std::vector<std::vector<Cell>> m_matrix;
	int m_size;
};

#endif // GAMEFIELD_H
