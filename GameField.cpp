#include <iostream>
#include <random>

#include <QtGlobal>

#include "GameField.h"

GameField::GameField(const int size)
{
    Q_ASSERT_X(size > 0, "GameField::GameField", "Size must be greater than zero!");

    if (size > 0) {
        m_size = size;
    } else {
        m_size = 10;
    }

	for (int rowIndex = 0; rowIndex < m_size; ++rowIndex) {
		std::vector<Cell> row;

		for (int columnIndex = 0; columnIndex < m_size; ++columnIndex) {
            Cell cell(rowIndex, columnIndex, Cell::Value(rand() % 10 - 1));
            cell.setClosed(rand() % 2);

			row.push_back(cell);
		}

        m_matrix.push_back(row);
	}
}

std::ostream &operator<<(std::ostream &st, GameField &gameField)
{
	for (int rowIndex = 0; rowIndex < gameField.m_size; ++rowIndex) {
		for (int columnIndex = 0; columnIndex < gameField.m_size; ++columnIndex) {
            st << gameField.m_matrix[rowIndex][columnIndex];
		}
		st << std::endl;
	}

	return st;
}
