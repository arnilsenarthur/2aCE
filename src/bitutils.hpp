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

#ifndef BITUTILS_H
#define BITUTILS_H

/**
 * MARKER Util to generate U64 rays values (8x8 and 16x16)
 */
#pragma region 
inline U64 _eastN(U64 board, U8 n)
{
    U64 newBoard = board;
    for (U8 i = 0; i < n; i++)
        newBoard = ((newBoard << 1) & (~FILE_A));

    return newBoard;
}

inline U64 _westN(U64 board, U8 n)
{
    U64 newBoard = board;
    for (U8 i = 0; i < n; i++)
        newBoard = ((newBoard >> 1) & (~FILE_H));

    return newBoard;
}

inline U8 _row(U8 square)
{
    return square / 8;
}

inline U8 _col(U8 square)
{
    return square % 8;
}

//Calc north coordinates of 16x16
inline U64 _1616calcn(U8 square, U8 min)
{
    U64 a = 0x01000100010001;
    if (square < min)
        return a << (square % 16);

    if (square + 16 >= min + 64)
        return 0;

    return a << square + 16;
}

//Calc south coordinates of 16x16
inline U64 _1616calcs(U8 square, U8 min)
{
    U64 a = 0x01000100010001;
    if (square <= min)
        return 0;

    if (64 <= (square - min))
        return a << (-(64 - (square - min))) % 16;

    return a >> 64 - (square - min);
}

inline U64 _1616calce(U8 square, U8 min)
{
    if (square < min || square >= min + 64)
        return 0;

    return 2 * ((u64a1 << (square | 15)) - (u64a1 << square));
}

inline U64 _1616calcw(U8 square, U8 min)
{
    if (square < min || square >= min + 64)
        return 0;

    return (u64a1 << square) - (u64a1 << (square & 240));
}
#pragma endregion
#endif