/**
 * 2aCE (Árnilsen's Adaptable Chess Engine)
 * Copyright (C) 2021 Árnilsen Arthur Castilho Lopes

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ATTACKLINE_H
#define ATTACKLINE_H

/**
 * MARKER Includes
 */
#pragma region 
#include "bitboard.hpp"
#pragma endregion

/**
 * MARKER Attack Line 
 * 
 * Holds an attackline, all attacked squares and blocker position
 */
class AttackLine
{
public:
    Bitboard squares;
    U8 blocker;

    AttackLine(Bitboard squares, U8 blocker)
    {
        this->squares = squares;
        this->blocker = blocker;
    }
};
#endif