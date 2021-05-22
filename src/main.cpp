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
 *
 * ------------------------------------------------------------------------
 *
 *    .d8888b.            .d8888b.  8888888888 
 *   d88P  Y88b          d88P  Y88b 888        
 *          888          888    888 888        
 *        .d88P  8888b.  888        8888888    
 *    .od888P"      "88b 888        888        
 *   d88P"      .d888888 888    888 888        
 *   888"       888  888 Y88b  d88P 888        
 *   888888888  "Y888888  "Y8888P"  8888888888 
 * 
 *   - Árnilsen's Adaptable Chess Engine
 *
 *   Author: Árnilsen Arthur Castilho Lopes
 *   Github:
 *   Linkedin:
 */

/**
 * MARKER Includes
 */
#pragma region
#include <iostream>
#include <intrin.h>
#include <sstream>
#include <bitset>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "defs.hpp"
#include "bitboard.hpp"
#include "board.hpp"
#include "standard/standard.hpp"
#pragma endregion

/**
 * Using standard namespace
 */
using namespace std;

/**
 * Generate all rays (Optmization)
 */
#pragma region
void initRays()
{
    auto start = chrono::steady_clock::now();
    //8x8 rays
    for (int square = 0; square < 64; square++)
    {
        rays88[NORTH][square] = 0x0101010101010100ULL << square;
        rays88[SOUTH][square] = 0x0080808080808080ULL >> (63 - square);
        rays88[EAST][square] = 2 * ((u64a1 << (square | 7)) - (u64a1 << square));
        rays88[WEST][square] = (u64a1 << square) - (u64a1 << (square & 56));
        rays88[NORTH_WEST][square] = _westN(0x102040810204000ULL, 7 - _col(square)) << (_row(square) * 8);
        rays88[NORTH_EAST][square] = _eastN(0x8040201008040200ULL, _col(square)) << (_row(square) * 8);
        rays88[SOUTH_WEST][square] = _westN(0x40201008040201ULL, 7 - _col(square)) >> ((7 - _row(square)) * 8);
        rays88[SOUTH_EAST][square] = _eastN(0x2040810204080ULL, _col(square)) >> ((7 - _row(square)) * 8);
    }

    //8x8 border
    for (int square = 0; square < 256; square++)
    {
        border88[square] = _88cp(square, 9, 1, 1, 1) | _88cp(square, 7, 1, -1, 1) | _88cp(square, -9, 1, -1, -1) | _88cp(square, -7, 1, 1, -1) | _88cp(square, 1, 1, 1, 0) | _88cp(square, 8, 1, 0, 1) | _88cp(square, -1, 1, -1, 0) | _88cp(square, -8, 1, 0, -1);
    }

    for (int square = 0; square < 64; square++)
    {
        knight88[square] = _88cp(square, 10, 1, 1, 1) | _88cp(square, 17, 1, 1, 1) | _88cp(square, 6, 1, -1, 1) | _88cp(square, 15, 1, -1, 1) |
                           _88cp(square, -10, 1, -1, -1) | _88cp(square, -6, 1, 1, -1) | _88cp(square, -17, 1, -1, -1) | _88cp(square, -15, 1, 1, -1);
    }

    for (int square = 0; square < 256; square++)
    {
        knight1616[square] = _1616cp(square, 18, 1, 1, 1) | _1616cp(square, 33, 1, 1, 1) | _1616cp(square, 14, 1, -1, 1) | _1616cp(square, 31, 1, -1, 1) |
                             _1616cp(square, -18, 1, -1, -1) | _1616cp(square, -14, 1, 1, -1) | _1616cp(square, -33, 1, -1, -1) | _1616cp(square, -31, 1, 1, -1);
    }

    //16x16 rays
    for (int square = 0; square < 256; square++)
    {
        rays1616[NORTH][square] = _1616n(square);
        rays1616[SOUTH][square] = _1616s(square);
        rays1616[EAST][square] = _1616e(square);
        rays1616[WEST][square] = _1616w(square);
        rays1616[NORTH_EAST][square] = _1616ne(square);
        rays1616[NORTH_WEST][square] = _1616nw(square);
        rays1616[SOUTH_EAST][square] = _1616se(square);
        rays1616[SOUTH_WEST][square] = _1616sw(square);
    }

    //16x16 border
    for (int square = 0; square < 256; square++)
    {
        border1616[square] = (_1616cp(square, 17, 1, 1, 1) | _1616cp(square, 15, 1, -1, 1) | _1616cp(square, -17, 1, -1, -1) | _1616cp(square, -15, 1, 1, -1) | _1616cp(square, 1, 1, 1, 0) | _1616cp(square, 16, 1, 0, 1) | _1616cp(square, -1, 1, -1, 0) | _1616cp(square, -16, 1, 0, -1));
    }

    auto end = chrono::steady_clock::now();
    std::cout << 64 * 8 + 256 * 8 + 256 + 64 + 256 + 64 << " rays generated in " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0 << "ms" << endl;
}
#pragma endregion

/**
 * MARKER Main engine entry
 */
#pragma region
int main()
{
    //Init all rays
    initRays();

    //Create board
    StandardBoard board;

    //Seed
    srand (time(NULL));

    board.print();
    cout << "\nYour Turn:\n";
    
    while(true)
    {
        #pragma region Player
        std::cout << (board.currentPlayer == 0 ? "[w]" : "[b]") << " <<< ";
        std::string move;
        std::getline(std::cin, move);

        cout << "\n";

        if (move == "exit")
            break;
        else
        {
            std::string output;
            Move m = board.parseMove(move, output);
            if (!m.isValid())
            {
                std::cout << ">> " << output;
                cout << "\nYour Turn:\n";
                continue;
            }
            else
            {
                board.doMove(m);
                board.print();

                std::cout << "\n";
            }
        }     
        #pragma endregion

        #pragma region Computer
        auto start = chrono::steady_clock::now();  
        board.genMoves();
        if(board.legalMoves.size() == 0)
        {
            break;
        }
        Move mv = board.legalMoves[rand() % board.legalMoves.size()];
        board.doMove(mv);
        auto end  = chrono::steady_clock::now();  

        std::string output = "";
        board.stringifyMove(mv,output);

        board.print();
        
        cout <<" \nComputer played in " << chrono::duration_cast<chrono::microseconds>(end - start).count()/1000.0 << "ms: " << output;
        cout << ". Your Turn:\n";
        #pragma endregion
    }

    return 0;
}
#pragma endregion