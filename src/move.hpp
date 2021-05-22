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

/**
 * MARKER Includes
 */
#pragma region 
#include <vector>
#include "bitutils.hpp"
#pragma endregion

/**
 * Move information holder
 */
class Move
{
public:
    U8 from; //From position
    U8 to; //To position
    U8 piecetype; //Moving piece type
    U8 flag; //Move flags
    U8 capturedpiecetype; //Captured piece type
    U8 promotionpiecetype; //Promoted piece type

    Move() //NULL
    {
        this->flag = 0;
    }

    Move(int from, int to, U8 piecetype, U8 flag)
    {
        this->from = from;
        this->to = to;
        this->piecetype = piecetype;
        this->flag = flag;
        this->promotionpiecetype = 255;
    }

    //Check if move is valid or NULL
    bool isValid()
    {
        return flag > 0;
    }
};

/**
 * MARKER Variable types
 */
#pragma region 
typedef std::vector<Move> MoveList;
#pragma endregion