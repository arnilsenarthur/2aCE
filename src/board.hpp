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

#ifndef BOARD_H
#define BOARD_H

/**
 * MARKER Includes
 */
#pragma region 
#include <string>
#include "bitboard.hpp"
#include "move.hpp"
#pragma endregion

/**
 * Base class for a board game (8x8 or 16x16)
 */
class Board
{
public:
    /**
     * MARKER Fields
     */
    #pragma region 
    Bitboard valid; //Holds all valid squares (For custom shaped games)
    U8 currentPlayer;

    //Data
    Bitboard _pieces[8][13]; //Pieces types + All pieces
    Bitboard _occupied;
    Bitboard _notoccupied;

    //Moves
    MoveList moves;
    MoveList legalMoves;
    #pragma endregion
    
    /**
     * MARKER Constructors
     */
    #pragma region 
    Board()
    {
    }
    #pragma endregion
    
    /**
     * MARKER Virtual Methods
     */
    #pragma region 
    //Core
    virtual void clear() = 0;
    virtual void print() = 0;

    //Game Situation
    virtual bool playerIsInCheck(U8 player) = 0;

    //Piece Management
    virtual void setPiece(U8 player, U8 piecetype, U8 pos) = 0;
    virtual U8 getPiece(U8 player, U8 pos) = 0;

    //Moves
    virtual void genMoves() = 0;
    virtual void doMove(Move &move) = 0;
    virtual void undoMove(Move &move) = 0;

    //I/O Moves
    virtual void stringifyMove(Move move,std::string &output) = 0;
    virtual Move parseMove(std::string move, std::string &status) = 0;

    //I/O Board
    virtual void loadBoard(std::string notation,std::string &status) = 0;
    virtual void stringifyBoard(std::string &output) = 0;
    #pragma endregion
};

#endif