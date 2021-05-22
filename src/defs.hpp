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

#ifndef DEFS_H
#define DEFS_H

/**
 * MARKER Includes
 */
#pragma region
#include <string>
#include <vector>
#pragma endregion

/**
 * MARKER Variable types
 */
#pragma region 
typedef unsigned long long U64; //Default 64 bit integer implementation (Board)
typedef unsigned char U8; //Default 8 bit integer implementation (Ids and positions)
#pragma endregion

/**
 * MARKER Console Constants
 * 
 * Console color code constants
*/
#pragma region
#define CSL_Reset "\u001b[0m"
#define CLS_Black "\u001b[30m"
#define CLS_Red "\u001b[31m"
#define CLS_Green "\u001b[32m"
#define CLS_Yellow "\u001b[33m"
#define CLS_Blue "\u001b[34m"
#define CLS_Magenta "\u001b[35m"
#define CLS_Cyan "\u001b[36m"
#define CLS_White "\u001b[37m"
#pragma endregion

/**
 * MARKER U64 Constants
 */
#pragma region 
const U64 u64zero = 0b0000000000000000000000000000000000000000000000000000000000000000;
const U64 u64one = 0b1111111111111111111111111111111111111111111111111111111111111111;
const U64 u64a1 = U64(1);
const U64 FILE_A = 0x101010101010101ull;
const U64 FILE_H = 0x8080808080808080ull;
const bool ONE = true;
const bool ZERO = false;
#pragma endregion

/**
 * MARKER Comparision Constations
 */
#pragma region 
const int EQUALS = 0;
const int GREATER = 1;
const int LESS = -1;
const int _88ROW = 16;
const int _1616ROW = 16;
#pragma endregion

/**
 * MARKER Direction Enumeration
 */
enum Direction
{
    NORTH = 0,
    NORTH_EAST = 1,
    EAST = 2,
    SOUTH_EAST = 3,
    SOUTH = 4,
    SOUTH_WEST = 5,
    WEST = 6,
    NORTH_WEST = 7
};

/**
 * MARKER String Utils
 */
#pragma region 
size_t strsplit(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ));
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}
#pragma endregion

#endif