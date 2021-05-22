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

#ifndef BITBOARD_H
#define BITBOARD_H

/**
 * MARKER Includes
 */
#pragma region 
#include <iostream>
#include <intrin.h>
#include <sstream>
#include <bitset>
#include "bitutils.hpp"
#pragma endregion

/**
 * Using standard namespace
 */
using namespace std;

/**
 * MARKER Microsoft C++ Bitscan utils
 */
#pragma region 
#pragma intrinsic(_BitScanReverse64)
#pragma intrinsic(_BitScanForward64)
#pragma endregion

/**
 * MARKER Base bitboard class (Used to handle bitwise operations in board of 8x8 and 16x16)
 */
class Bitboard
{
public:
    U64 main; //Used for 8x8 board / 4 first rows (16x16 board)
    U64 b;    //Rows 5-8 (16x16 board)
    U64 c;    //Rows 9-12 (16x16 board)
    U64 d;    //Rows 13-16 (16x16 board)

public:
    bool is16_16;
    int squares;
    int size;

    /**
     * MARKER Constructors
     */
    #pragma region 
    Bitboard() //NULL Bitboard (Used only by arrays)
    {
    }

    /**
     * MARKER 8X8 Bitboard constructor
     */
    Bitboard(U64 a)
    {
        this->is16_16 = false;
        this->main = a;
        size = 64;
        size = 8;
    }

    /**
     * MARKER 16X16 Bitboard constructor
     */
    Bitboard(U64 d, U64 c, U64 b, U64 a)
    {
        this->is16_16 = true;
        this->main = a;
        this->b = b;
        this->c = c;
        this->d = d;
        size = 256;
        size = 16;
    }
    #pragma endregion

    /**
     * MARKER Bit Get And Set
     */
    #pragma region 
    bool get(U8 x, U8 y)
    {
        if (is16_16)
        {
            U8 s = y * 16 + x;

            if (s < 64)
                return (d & (1ULL << s)) >> s;
            else if (s < 128)
                return (c & (1ULL << s)) >> s;
            else if (s < 192)
                return (b & (1ULL << s)) >> s;
            else
                return (main & (1ULL << s)) >> s;
        }
        else
        {
            U8 s = y * 8 + x;
            return (main & (1 << s)) >> s;
        }
    }
    
    bool get(U8 s)
    {
        if (is16_16)
        {
            if (s < 64)
                return (d & (1ULL << s)) >> s;
            else if (s < 128)
                return (c & (1ULL << s)) >> s;
            else if (s < 192)
                return (b & (1ULL << s)) >> s;
            else
                return (main & (1ULL << s)) >> s;
        }
        else
        {
            return (main & (1 << s)) >> s;
        }
    }

    void set(U8 x, U8 y, bool value)
    {
        if (is16_16)
        {
            U8 s = y * 16 + x;

            if (value)
            {
                if (s < 64)
                    d |= u64a1 << (s % 64);
                else if (s < 128)
                    c |= u64a1 << (s % 64);
                else if (s < 192)
                    b |= u64a1 << (s % 64);
                else
                    main |= u64a1 << (s % 64);
            }
            else
            {
                if (s < 64)
                    d &= ~(u64a1 << (s % 64));
                else if (s < 128)
                    c &= ~(u64a1 << (s % 64));
                else if (s < 192)
                    b &= ~(u64a1 << (s % 64));
                else
                    main &= ~(u64a1 << (s % 64));
            }
        }
        else
        {
            U8 s = y * 8 + x;

            if (value)
                main |= u64a1 << s;
            else
                main &= ~(u64a1 << s);
        }
    }

    void set(U8 s, bool value)
    {
        if (is16_16)
        {
            if (value)
            {
                if (s < 64)
                    d |= u64a1 << (s % 64);
                else if (s < 128)
                    c |= u64a1 << (s % 64);
                else if (s < 192)
                    b |= u64a1 << (s % 64);
                else
                    main |= u64a1 << (s % 64);
            }
            else
            {
                if (s < 64)
                    d &= ~(u64a1 << (s % 64));
                else if (s < 128)
                    c &= ~(u64a1 << (s % 64));
                else if (s < 192)
                    b &= ~(u64a1 << (s % 64));
                else
                    main &= ~(u64a1 << (s % 64));
            }
        }
        else
        {
            if (value)
                main |= u64a1 << s;
            else
                main &= ~(u64a1 << s);
        }
    }
    #pragma endregion

    /**
     * MARKER Print bitboard in 8x8 or 16x16 bits format
     */
    void print()
    {
        if (is16_16)
        {
            unsigned long long arr[4] = {main, b, c, d};

            printf("\n");
            for (int i = 0; i < 4; i++)
            {
                stringstream ss;
                ss << arr[i];

                U64 x;
                ss >> x;
                bitset<64> b(x);
                string tmp = b.to_string();
                int count = 0;
                for (int i = 0; i < 4; i++)
                {
                    printf("\n");
                    for (int j = 0; j < 16; j++)
                    {
                        printf("%c ", tmp[count + (15 - j)]);
                    }

                    count += 16;
                }
            }
        }
        else
        {
            printf("\n");
            stringstream ss;
            ss << main;

            U64 x;
            ss >> x;
            bitset<64> b(x);
            string tmp = b.to_string();
            int count = 0;
            for (int i = 0; i < 8; i++)
            {
                printf("\n");
                for (int j = 0; j < 8; j++)
                {
                    printf("%c ", tmp[count + (7 - j)]);
                }

                count += 8;
            }
        }
    }

    /**
     * MARKER Clear bitboard data
     */
    void clear()
    {
        main = 0;

        if(is16_16)
        {
            b = 0;
            c = 0;
            d = 0;    
        }
    }
    /**
     * MARKER Bitwise utils
     */
    #pragma region 
    //Count all 1 of board
    U8 popCount()
    {
        if (this->is16_16)
        {
            return __popcnt64(main) + __popcnt64(b) + __popcnt64(c) + __popcnt64(d);
        }
        else
            return __popcnt64(main);
    }

    //Scan previous and pop
    int bitScanPopNext()
    {
        unsigned long pos = 0;

        if (this->is16_16)
        {
            if (_BitScanReverse64(&pos, d))
            {
                d &= ~(u64a1 << pos);
                return pos;
            }

            if (_BitScanReverse64(&pos, c))
            {
                c &= ~(u64a1 << pos);
                return pos + 64;
            }

            if (_BitScanReverse64(&pos, b))
            {
                b &= ~(u64a1 << pos);
                return pos + 128;
            }

            if (_BitScanReverse64(&pos, main))
            {
                main &= ~(u64a1 << pos);
                return pos + 192;
            }
        }
        else
        {
            _BitScanReverse64(&pos, main);
            {
                main &= ~(u64a1 << pos);
                return pos;
            }
        }

        return -1;
    }

    //Scan previous
    int bitScanReverse()
    {
        unsigned long pos = 0;

        if (this->is16_16)
        {
            if (_BitScanReverse64(&pos, d))
                return pos;

            if (_BitScanReverse64(&pos, c))
                return pos + 64;

            if (_BitScanReverse64(&pos, b))
                return pos + 128;

            if (_BitScanReverse64(&pos, main))
                return pos + 192;
        }
        else
        {
            if (_BitScanReverse64(&pos, main))
                return pos;
        }

        return -1;
    }
    
    //Scan forward and pop
    int bitScanForward()
    {
        unsigned long pos = 0;

        if (this->is16_16)
        {
            if (_BitScanForward64(&pos, d))
                return pos;

            if (_BitScanForward64(&pos, c))
                return pos + 64;

            if (_BitScanForward64(&pos, b))
                return pos + 128;

            if (_BitScanForward64(&pos, main))
                return pos + 192;
        }
        else
        {
            if (_BitScanForward64(&pos, main))
                return pos;
        }

        return -1;
    }
    #pragma endregion

    /**
     * MARKER Return true if at least one bit is set as true (popCount() > 0)
     */
    bool has()
    {
        if (is16_16)
            return main | b | c | d;
        else
            return main;
    }

    /**
     * MARKER Operators
     */
    #pragma region 
    //Bitwise & (AND) 
    Bitboard operator&(const Bitboard &board)
    {
        Bitboard b;
        b.is16_16 = is16_16;
        b.main = this->main & board.main;

        if (this->is16_16)
        {
            b.b = this->b & board.b;
            b.c = this->c & board.c;
            b.d = this->d & board.d;
        }
        return b;
    }

    //Bitwise | (OR)
    Bitboard operator|(const Bitboard &board)
    {
        Bitboard b;
        b.is16_16 = is16_16;
        b.main = this->main | board.main;

        if (is16_16)
        {
            b.b = this->b | board.b;
            b.c = this->c | board.c;
            b.d = this->d | board.d;
        }
        return b;
    }

    //Bitwise ^ (XOR)
    Bitboard operator^(const Bitboard &board)
    {
        Bitboard b;
        b.is16_16 = is16_16;
        b.main = this->main ^ board.main;

        if (this->is16_16)
        {
            b.b = this->b ^ board.b;
            b.c = this->c ^ board.c;
            b.d = this->d ^ board.d;
        }
        return b;
    }

    //Bitwise Complement/Inverse
    Bitboard operator~()
    {
        Bitboard b;
        b.is16_16 = is16_16;
        b.main = ~this->main;

        if (this->is16_16)
        {
            b.b = ~this->b;
            b.c = ~this->c;
            b.d = ~this->d;
        }
        return b;
    }

    //Bitwise << (Right Shift)
    Bitboard operator<<(int move)
    {
        Bitboard b;
        b.is16_16 = is16_16;
        b.main = this->main << move;

        if (this->is16_16)
        {
            b.b = this->b << move;
            b.c = this->c << move;
            b.d = this->d << move;
        }
        return b;
    }

    //Bitwise >> (Left Shift)
    Bitboard operator>>(int move)
    {
        Bitboard b;
        b.is16_16 = is16_16;
        b.main = this->main >> move;

        if (this->is16_16)
        {
            b.b = this->b >> move;
            b.c = this->c >> move;
            b.d = this->d >> move;
        }
        return b;
    }

    //Bitwise | (OR)
    Bitboard &operator|=(const Bitboard &board)
    {
        this->main |= board.main;

        if (this->is16_16)
        {
            this->b |= board.b;
            this->c |= board.c;
            this->d |= board.d;
        }

        return *this;
    }

    //Bitwise && (AND)
    Bitboard &operator&=(const Bitboard &board)
    {
        this->main &= board.main;

        if (this->is16_16)
        {
            this->b &= board.b;
            this->c &= board.c;
            this->d &= board.d;
        }

        return *this;
    }

    //Bitwise ^ (XOR)
    Bitboard &operator^=(const Bitboard &board)
    {
        this->main ^= board.main;

        if (this->is16_16)
        {
            this->b ^= board.b;
            this->c ^= board.c;
            this->d ^= board.d;
        }

        return *this;
    }
    #pragma endregion
};

/**
 * MARKER Rays optmization (8x8 and 16x16)
 */
#pragma region 
//Rays (8x8)
Bitboard rays88[8][64];
//Border (8x8)
Bitboard border88[64];
//Border (8x8)
Bitboard knight88[64];
//Rays (16x16)
Bitboard rays1616[8][256];
//Border (16x16)
Bitboard border1616[256];
//Border (16x16)
Bitboard knight1616[256];
#pragma endregion

/**
 * MARKER Rays/Position generation (8x8 and 16x16)
 */
#pragma region 
//Create s 16x16 bitboard
inline Bitboard _1616s(int square)
{
    return Bitboard(_1616calcs(square, 0), _1616calcs(square, 64), _1616calcs(square, 128), _1616calcs(square, 192));
}

//Create n 16x16 bitboard
inline Bitboard _1616n(int square)
{
    return Bitboard(_1616calcn(square, 0), _1616calcn(square, 64), _1616calcn(square, 128), _1616calcn(square, 192));
}

//Create e 16x16 bitboard
inline Bitboard _1616e(int square)
{
    return Bitboard(_1616calce(square, 0), _1616calce(square, 64), _1616calce(square, 128), _1616calce(square, 192));
}

//Create w 16x16 bitboard
inline Bitboard _1616w(int square)
{
    return Bitboard(_1616calcw(square, 0), _1616calcw(square, 64), _1616calcw(square, 128), _1616calcw(square, 192));
}

//Create ne 16x16 bitboard
inline Bitboard _1616ne(int square)
{
    U64 a = u64zero;
    U64 b = u64zero;
    U64 c = u64zero;
    U64 d = u64zero;

    int cC = square % 16;
    int rC = square / 16;

    int s = square + 17;

    int cs = s % 16;
    int rs = s / 16;

    while (s < 256 && cs > cC && rs > rC)
    {
        if (s < 64)
            a |= u64a1 << (s % 64);
        else if (s < 128)
            b |= u64a1 << (s % 64);
        else if (s < 192)
            c |= u64a1 << (s % 64);
        else
            d |= u64a1 << (s % 64);

        s += 17;
        cs = s % 16;
        rs = s / 16;
    }

    return Bitboard(a, b, c, d);
}

//Create nw 16x16 bitboard
inline Bitboard _1616nw(int square)
{
    U64 a = u64zero;
    U64 b = u64zero;
    U64 c = u64zero;
    U64 d = u64zero;

    int cC = square % 16;
    int rC = square / 16;

    int s = square + 15;

    int cs = s % 16;
    int rs = s / 16;

    while (s < 256 && cs < cC && rs > rC)
    {
        if (s < 64)
            a |= u64a1 << (s % 64);
        else if (s < 128)
            b |= u64a1 << (s % 64);
        else if (s < 192)
            c |= u64a1 << (s % 64);
        else
            d |= u64a1 << (s % 64);

        s += 15;
        cs = s % 16;
        rs = s / 16;
    }

    return Bitboard(a, b, c, d);
}

//Create se 16x16 bitboard
inline Bitboard _1616se(int square)
{
    U64 a = u64zero;
    U64 b = u64zero;
    U64 c = u64zero;
    U64 d = u64zero;

    int cC = square % 16;
    int rC = square / 16;

    int s = square - 15;

    int cs = s % 16;
    int rs = s / 16;

    while (s > 0 && cs > cC && rs < rC)
    {
        if (s < 64)
            a |= u64a1 << (s % 64);
        else if (s < 128)
            b |= u64a1 << (s % 64);
        else if (s < 192)
            c |= u64a1 << (s % 64);
        else
            d |= u64a1 << (s % 64);

        s -= 15;
        cs = s % 16;
        rs = s / 16;
    }

    return Bitboard(a, b, c, d);
}

//Create se 16x16 bitboard
inline Bitboard _1616sw(int square)
{
    U64 a = u64zero;
    U64 b = u64zero;
    U64 c = u64zero;
    U64 d = u64zero;

    int cC = square % 16;
    int rC = square / 16;

    int s = square - 17;

    int cs = s % 16;
    int rs = s / 16;

    while (s > 0 && cs < cC && rs < rC)
    {
        if (s < 64)
            a |= u64a1 << (s % 64);
        else if (s < 128)
            b |= u64a1 << (s % 64);
        else if (s < 192)
            c |= u64a1 << (s % 64);
        else
            d |= u64a1 << (s % 64);

        s -= 17;
        cs = s % 16;
        rs = s / 16;
    }

    return Bitboard(a, b, c, d);
}

//Create custom pattern bitboard
inline Bitboard _88cp(int square, int move, int limit, int column_condition, int row_condition)
{
    U64 main = u64zero;

    int cC = square % 8;
    int rC = square / 8;

    int s = square + move;

    int cs = s % 8;
    int rs = s / 8;

    int cn = 0;

    while (s > 0 && s < 64 && cn < limit && (column_condition == 0 ? cs == cC : (column_condition == 1 ? cs > cC : cs < cC)) && (row_condition == 0 ? rs == rC : (row_condition == 1 ? rs > rC : rs < rC)))
    {
        main |= u64a1 << s;

        cn++;
        s += move;
        cs = s % 8;
        rs = s / 8;
    }

    return Bitboard(main);
}

//Create custom pattern bitboard
inline Bitboard _1616cp(int square, int move, int limit, int column_condition, int row_condition)
{
    U64 a = u64zero;
    U64 b = u64zero;
    U64 c = u64zero;
    U64 d = u64zero;

    int cC = square % 16;
    int rC = square / 16;

    int s = square + move;

    int cs = s % 16;
    int rs = s / 16;

    int cn = 0;

    while (s > 0 && s < 256 && cn < limit && (column_condition == 0 ? cs == cC : (column_condition == 1 ? cs > cC : cs < cC)) && (row_condition == 0 ? rs == rC : (row_condition == 1 ? rs > rC : rs < rC)))
    {
        if (s < 64)
            a |= u64a1 << (s % 64);
        else if (s < 128)
            b |= u64a1 << (s % 64);
        else if (s < 192)
            c |= u64a1 << (s % 64);
        else
            d |= u64a1 << (s % 64);

        cn++;
        s += move;
        cs = s % 16;
        rs = s / 16;
    }

    return Bitboard(a, b, c, d);
}
#pragma endregion

#endif