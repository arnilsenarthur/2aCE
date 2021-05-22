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

#ifndef STANDARD_H
#define STANDARD_H

/**
 * MARKER Includes
 */
#pragma region
#include "../AttackLine.hpp"
#include <cstring>
#pragma endregion

/**
 * MARKER Pieces
 */
#pragma Pieces
const U8 STANDARD_PT_PAWN = 0;
const U8 STANDARD_PT_KING = 1;
const U8 STANDARD_PT_QUEEN = 2;
const U8 STANDARD_PT_BISHOP = 3;
const U8 STANDARD_PT_ROOK = 4;
const U8 STANDARD_PT_KNIGHT = 5;
char piecesChars[6] = {'P','K','Q','B','R','N'};
#pragma endregion

/**
 * MARKER Player Ids
 */
#pragma region
const U8 STANDARD_PLAYER_WHITE = 0;
const U8 STANDARD_PLAYER_BLACK = 1;
#pragma endregion

/**
 * MARKER Moves
 */
#pragma region
const unsigned int MOVE_VALID = 1 << 1; //DONE
const unsigned int MOVE_CAPTURE = 1 << 2; //DONE
const unsigned int MOVE_DOUBLE_PAWN = 1 << 3; //DONE
const unsigned int MOVE_KING_SIDE_CASTLING = 1 << 4;
const unsigned int MOVE_QUEEN_SIDE_CASTLING = 1 << 5;
const unsigned int MOVE_EN_PASSANT = 1 << 6;
const unsigned int MOVE_PROMOTION = 1 << 7; //DONE
#pragma endregion

/**
 * MARKER Ranks (Rows)
 */ 
#pragma region
Bitboard RANK_1 = 0xffull;
Bitboard RANK_2 = 0xff00ull;
Bitboard RANK_3 = 0xff0000ull;
Bitboard RANK_4 = 0xff000000ull;
Bitboard RANK_5 = 0xff00000000ull;
Bitboard RANK_6 = 0xff0000000000ull;
Bitboard RANK_7 = 0xff000000000000ull;
Bitboard RANK_8 = 0xff00000000000000ull;
Bitboard RANKS[8] = {RANK_1,RANK_2,RANK_3,RANK_4,RANK_5,RANK_6,RANK_7,RANK_8};
#pragma endregion

/**
 * MARKER Files (Columns)
 */
#pragma region 
Bitboard BFILE_H = 0x8080808080808080ull;
Bitboard BFILE_G = 0x4040404040404040ull;
Bitboard BFILE_F = 0x2020202020202020ull;
Bitboard BFILE_E = 0x1010101010101010ull;
Bitboard BFILE_D = 0x808080808080808ull;
Bitboard BFILE_C = 0x404040404040404ull;
Bitboard BFILE_B = 0x202020202020202ull;
Bitboard BFILE_A = 0x101010101010101ull;
Bitboard FILES[8] = {BFILE_A,BFILE_B,BFILE_C,BFILE_D,BFILE_E,BFILE_F,BFILE_G,BFILE_H};
#pragma endregion

/**
 * MARKER Standard chess game board
 * 
 * Default 8x8 chess board
 * Default White X Black player
 * 
 * - En Passant Support
 * - Castling Support
 * - Undo Support
 */
#pragma region 
class StandardBoard : public Board
{
    public:  
        /**
         * MARKER Fields
         */
        #pragma region 
        //Player console color
        std::string _playercolor[2];

        //Optmization
        Bitboard otherPieces;
        Bitboard playerPiecesInverse;

        //Temporary variables
        U8 otherPlayer;

        //Attack situation (Legal move optimization)
        std::vector<AttackLine> directAttackLines;
        std::vector<AttackLine> blockedAttackLines;
        Bitboard captureAttackingPieces;
        Bitboard attackBlockers;
        Bitboard attackedSquares;
        
        //Castling info
        int castlingInfo[2][3]; //Player: KingMoves, QSRookMoves, KSRookMoves

        //En-passant information
        std::vector<U8> enpassantHistory;
        int enpassant = -1;
        #pragma endregion

        /**
         * MARKER Constructor
         */   
        StandardBoard()
        {
            //Int all squares as valid
            valid = Bitboard(false);
            valid.main = u64one;

            //Clear all data
            clear();

            //Generate default pieces (White)
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_ROOK,0);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_KNIGHT,1);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_BISHOP,2);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_QUEEN,3);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_KING,4);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_BISHOP,5);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_KNIGHT,6);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_ROOK,7);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,8);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,9);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,10);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,11);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,12);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,13);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,14);
            setPiece(STANDARD_PLAYER_WHITE,STANDARD_PT_PAWN,15);

            //Generate default pieces (Black) 
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,48);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,49);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,50);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,51);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,52);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,53);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,54);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_PAWN,55);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_ROOK,56);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_KNIGHT,57);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_BISHOP,58);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_QUEEN,59);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_KING,60);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_BISHOP,61);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_KNIGHT,62);
            setPiece(STANDARD_PLAYER_BLACK,STANDARD_PT_ROOK,63);

            //Colors
            _playercolor[0] = CLS_White;
            _playercolor[1] = CLS_Blue;

            //Init
            currentPlayer = STANDARD_PLAYER_WHITE;
        }

        //Clear all board pieces/information
        /**
         * MARKER Board
         */
        #pragma region
        void clear()
        {
            //Clear all pieces
            for(int i = 0; i < 2;i ++)
                for(int j = 0; j < 7; j ++)
                    _pieces[i][j] = Bitboard(0);

            //Castling
            castlingInfo[0][0] = 0;
            castlingInfo[0][1] = 0;
            castlingInfo[0][2] = 0;
            castlingInfo[1][0] = 0;
            castlingInfo[1][1] = 0;
            castlingInfo[1][2] = 0;

            //EnPassant
            enpassantHistory = std::vector<U8>();
            enpassant = -1;

            directAttackLines.clear();
            blockedAttackLines.clear();

            captureAttackingPieces.clear();
            attackBlockers = Bitboard(0);
            attackedSquares  = Bitboard(0);
            _occupied = Bitboard(0);
            _notoccupied = Bitboard(0);
            
            _occupied = _pieces[STANDARD_PLAYER_WHITE][6] | _pieces[STANDARD_PLAYER_BLACK][6];
            _notoccupied = ~_occupied;
        }
        
        //Print formatted board
        void print()
        {
            int count = 63;
            printf("\n");
            for (int i =0; i < 8; i ++)
            {
                printf("\n");
                printf(std::to_string(8 - i).c_str());
                printf(" ");
                for (int j=0;j <8;j++)
                {
                    //Position
                    int pos = count - (7 - j);

                    //valid square
                    if(((valid.main) >> (pos)) & 1)
                    {   
                        //Pieces
                        bool b = false;
                        for(U8 player = 0; player < 2; player ++)
                            for(U8 type = 0; type < 6; type ++)
                            {
                                if(((_pieces[player][type].main) >> (pos)) & 1)
                                {
                                    printf(_playercolor[player].c_str());
                                    b = true;
                                    printf("%c ",piecesChars[type]);
                                    printf(CSL_Reset);
                                }
                            }

                        if(!b)
                            printf(". ");
                    }
                    else
                        printf("a  ");     
                }
                count -= 8;
            }  

            printf("\n\n  a b c d e f g h"); 
        }     
        
        //Stringify board
        void stringifyBoard(std::string &output)
        {
            std::stringstream ss;
            for(int row = 7; row >= 0; row --)
            {
                ss << "/";
                int empty = 0;
                for(U8 column = 0; column < 8; column ++)
                {
                    int player = 0;
                    U8 piecetype = getPiece(0,row * 8 + column);
                    if(piecetype == 255)
                    {
                        player = 1;
                        piecetype = getPiece(1,row * 8 + column);
                    }

                    if(piecetype == 255)
                    {
                        empty ++;
                    }
                    else
                    {
                        if(empty > 0)
                            ss << empty;

                        empty = 0;
                        char c = piecesChars[piecetype];
                        if(player == 1)
                            c = tolower(c);

                        ss << c;
                    }
                }

                if(empty > 0)
                    ss << empty;
            }

            std::string s = ss.str().substr(1);

            s += (currentPlayer == 0 ? " w " : " b ");
            
            std::string castlingstr = "";

            if(castlingInfo[0][0] == 0 && castlingInfo[0][2] == 0)
                castlingstr += "K";
            if(castlingInfo[1][0] == 0 && castlingInfo[1][2] == 0)
                castlingstr += "k";
            if(castlingInfo[0][0] == 0 && castlingInfo[0][1] == 0)
                castlingstr += "Q";
            if(castlingInfo[1][0] == 0 && castlingInfo[1][1] == 0)
                castlingstr += "q";

            if(castlingstr.length() > 0)
                s += castlingstr;
            else
                s += "-";

            s += " ";
            if(enpassant == -1)
                s += "-";
            else
            {
                int row = enpassant/8;
                int column = enpassant%8;

                s += (char)(column + 97);
                s += (row + 49);
            }

            output = s;
        }

        //Load board
        void loadBoard(std::string notation,std::string &status)
        {
            std::vector<std::string> v;
            strsplit(notation, v,' ');

            //Check length
            std::vector<std::string> rows;
            strsplit(v[0], rows,'/');
            if(rows.size() != 8)
            {
                status = std::string("Error: Expected 8 rows but found '") + std::to_string(rows.size()) + "'";
                return;
            }

            //Hold data
            Bitboard data[2][6] = {{Bitboard(0),Bitboard(0),Bitboard(0),Bitboard(0),Bitboard(0),Bitboard(0)},{Bitboard(0),Bitboard(0),Bitboard(0),Bitboard(0),Bitboard(0),Bitboard(0)}};
            //Parse data
            for(int row = 0; row < 8; row ++)
            {
                int count = 0;
                for (char const &c: rows[7 - row])
                {
                    if(isdigit(c))
                    {
                        count += c - 48;
                    }
                    else
                    {
                        if(count >= 8)
                        {
                            status = std::string("Error: Expected 8 columns but found '") + std::to_string(count) + "' at line '" + std::to_string(row) + "'";
                            return;
                        }

                        int pos = row * 8 + count;

                        switch (c)
                        {
                            case 'P':
                                data[0][STANDARD_PT_PAWN].set(pos,true);
                                break;
                            case 'R':
                                data[0][STANDARD_PT_ROOK].set(pos,true);
                                break;
                            case 'Q':
                                data[0][STANDARD_PT_QUEEN].set(pos,true);
                                break;
                            case 'B':
                                data[0][STANDARD_PT_BISHOP].set(pos,true);
                                break;
                            case 'N':
                                data[0][STANDARD_PT_KNIGHT].set(pos,true);
                                break;
                            case 'K':
                                data[0][STANDARD_PT_KING].set(pos,true);
                                break;

                            case 'p':
                                data[1][STANDARD_PT_PAWN].set(pos,true);
                                break;
                            case 'r':
                                data[1][STANDARD_PT_ROOK].set(pos,true);
                                break;
                            case 'q':
                                data[1][STANDARD_PT_QUEEN].set(pos,true);
                                break;
                            case 'b':
                                data[1][STANDARD_PT_BISHOP].set(pos,true);
                                break;
                            case 'n':
                                data[1][STANDARD_PT_KNIGHT].set(pos,true);
                                break;
                            case 'k':
                                data[1][STANDARD_PT_KING].set(pos,true);
                                break;
                            
                            default:
                                status = std::string("Error: Invalid piece type '") + c + "'";
                                return;
                        }
                        count ++;
                    }
                }

                if(count != 8)
                {
                    status = std::string("Error: Expected 8 columns but found '") + std::to_string(count) + "' at line '" + std::to_string(row + 1) + "'";
                    return;
                }
            }

            //Current player
            int player = 0;
            if(v.size() > 1)
            {
                if(v[1] == "w")
                    player = 0;
                else if(v[1] == "b")
                    player = 1;
                else
                {
                    status = std::string("Error: Invalid player '") + v[1] + "'";
                    return;
                }
            }

            //Castling data
            int castinfo[2][3] = {{0,1,1},{0,1,1}};

            if(v.size() > 2)
            {
                if(v[2] != "-")
                    for (char const &c: v[2])
                    {
                        switch (c)
                        {
                            case 'K':
                                castinfo[0][2] = 0;
                                break;
                            case 'Q':
                                castinfo[0][1] = 0;
                                break;
                            case 'k':
                                castinfo[1][2] = 0;
                                break;
                            case 'q':
                                castinfo[1][1] = 0;
                                break;
                            
                            default:
                                status = std::string("Error: Invalid castling info '") + c + "'";
                                return;
                        }
                    }
            }

            int enpassantinfo = -1;

            if(v.size() > 3)
            {
                //En passant data
                if(v[3] != "-")
                    if(v[3].length() != 2)
                    {
                        status = std::string("Error: Invalid en-passant info '") + v[3] + "'";
                        return;
                    }
                    else if(isalpha(v[3][0]) && islower(v[3][0]) && isdigit(v[3][1]))
                    {
                        int column = v[3][0] - 97;
                        int row = v[3][1] - 49;
                        enpassantinfo = row * 8 + column;
                    }
                    else
                    {
                        status = std::string("Error: Invalid en-passant info '") + v[3] + "'";
                        return;
                    }
            }
            

            //Clear data
            clear();
            //Apply data
            for(int i = 0; i < 2; i ++)
                for(int j = 0; j < 6; j ++)
                    _pieces[i][j] = data[i][j];

            _pieces[STANDARD_PLAYER_WHITE][6] = _pieces[STANDARD_PLAYER_WHITE][5] | _pieces[STANDARD_PLAYER_WHITE][4] | _pieces[STANDARD_PLAYER_WHITE][3] | _pieces[STANDARD_PLAYER_WHITE][2] | _pieces[STANDARD_PLAYER_WHITE][1] | _pieces[STANDARD_PLAYER_WHITE][0];
            _pieces[STANDARD_PLAYER_BLACK][6] = _pieces[STANDARD_PLAYER_BLACK][5] | _pieces[STANDARD_PLAYER_BLACK][4] | _pieces[STANDARD_PLAYER_BLACK][3] | _pieces[STANDARD_PLAYER_BLACK][2] | _pieces[STANDARD_PLAYER_BLACK][1] | _pieces[STANDARD_PLAYER_BLACK][0];

            _occupied = _pieces[STANDARD_PLAYER_WHITE][6] | _pieces[STANDARD_PLAYER_BLACK][6];
            _notoccupied = ~_occupied;

            currentPlayer = player;

            castlingInfo[0][0] = castinfo[0][0];
            castlingInfo[0][1] = castinfo[0][1];
            castlingInfo[0][2] = castinfo[0][2];
            castlingInfo[1][0] = castinfo[1][0];
            castlingInfo[1][1] = castinfo[1][1];
            castlingInfo[1][2] = castinfo[1][2];

            enpassant = enpassantinfo;
            enpassantHistory.push_back(enpassant);
            
        }
        

        #pragma endregion

        /**
         * MARKER Pieces
         */
        #pragma region 
        void setPiece(U8 player,U8 piecetype,U8 pos)
        {
            _addPiece(player,piecetype,pos);
        }   

        U8 getPiece(U8 player,U8 pos)
        {
            Bitboard square = u64a1 << pos;
            if ((square & _pieces[player][0]).has()) return 0;
            else if ((square & _pieces[player][1]).has()) return 1;
            else if ((square & _pieces[player][2]).has()) return 2;
            else if ((square & _pieces[player][3]).has()) return 3;
            else if ((square & _pieces[player][4]).has()) return 4;
            else if ((square & _pieces[player][5]).has()) return 5;

            return 255;
        }

        Bitboard getPieces(U8 player,U8 piecetype)
        {
            return _pieces[player][piecetype];
        }   
        #pragma endregion

        /**
         * MARKER Board/Game situation
         */
        #pragma region
        bool playerIsInCheck(U8 player)
        {   
            int i = _pieces[player][STANDARD_PT_KING].bitScanForward();

            if(i == -1)
                return false;

            return squareIsUnderAttack(player,i);
        }

        bool squareIsUnderAttack(U8 player,U8 pos)
        {
            Bitboard square = u64a1 << pos;
            U8 other = player == 0 ? 1 : 0;

            //Pawn attacks
            #pragma region Pawn
            Bitboard pawns = _pieces[other][0];

            if(other == 0)
            {
                if(((pawns << 7) & ~BFILE_H & square).has())
                    return true;
                if(((pawns << 9) & ~BFILE_A & square).has())
                    return true;
            }
            else
            {
                if(((pawns >> 7) & ~BFILE_A & square).has())
                    return true;
                if(((pawns >> 9) & ~BFILE_H & square).has())
                    return true;
            }
            #pragma endregion

            //King attacks
            #pragma region King
            Bitboard kings = _pieces[other][STANDARD_PT_KING];
            
            while (kings.has())
                if((border88[kings.bitScanPopNext()] & square).has())
                    return true;

            #pragma endregion
        
            //Queen attacks
            #pragma region Queen
            Bitboard queens = (_pieces[other][STANDARD_PT_QUEEN]);

            while (queens.has())
            {
                unsigned int pos = queens.bitScanPopNext();
                
                //All moves
                Bitboard all = genRayMoves(pos,NORTH,other,false) | genRayMoves(pos,SOUTH,other,true) | genRayMoves(pos,EAST,other,false) | genRayMoves(pos,WEST,other,true) | genRayMoves(pos,NORTH_EAST,other,false) | genRayMoves(pos,SOUTH_EAST,other,true) | genRayMoves(pos,NORTH_WEST,other,false) | genRayMoves(pos,SOUTH_WEST,other,true);

                if((all & square).has())
                    return true;
            }
            #pragma endregion

            //Rook attacks
            #pragma region Rook
            Bitboard rooks = (_pieces[other][STANDARD_PT_ROOK]);

            while (rooks.has())
            {
                unsigned int pos = rooks.bitScanPopNext();
                
                //All moves
                Bitboard all = genRayMoves(pos,NORTH,other,false) | genRayMoves(pos,SOUTH,other,true) | genRayMoves(pos,EAST,other,false) | genRayMoves(pos,WEST,other,true);

                if((all & square).has())
                    return true;
            }
            #pragma endregion

            //Bishop attacks
            #pragma region Bishop
            Bitboard bishops = (_pieces[other][STANDARD_PT_BISHOP]);

            while (bishops.has())
            {
                unsigned int pos = bishops.bitScanPopNext();
                
                //All moves
                Bitboard all = genRayMoves(pos,NORTH_EAST,other,false) | genRayMoves(pos,SOUTH_EAST,other,true) | genRayMoves(pos,NORTH_WEST,other,false) | genRayMoves(pos,SOUTH_WEST,other,true);
                if((all & square).has())
                    return true;
            }
            #pragma endregion

            //Knight attacks
            #pragma region Knight
            Bitboard knights = _pieces[other][STANDARD_PT_KNIGHT];
            
            while (knights.has())
                if((knight88[knights.bitScanPopNext()] & square).has())
                    return true;

            #pragma endregion

            return false;
        }
        #pragma endregion

        /**
         * MARKER Moves
         */
        #pragma region            
        void doMove(Move &move)
        {
            //Enpassant generation
            U8 other = currentPlayer == 0 ? 1 : 0;

            if(move.piecetype == STANDARD_PT_KING)
                castlingInfo[currentPlayer][0] ++;
            if((Bitboard(u64a1 << move.from) & Bitboard(FILE_A)).has() && move.piecetype == STANDARD_PT_ROOK)
                castlingInfo[currentPlayer][1] ++;
            if((Bitboard(u64a1 << move.from) & Bitboard(FILE_H)).has() && move.piecetype == STANDARD_PT_ROOK)
                castlingInfo[currentPlayer][2] ++;

            if(move.flag & MOVE_EN_PASSANT)
            {
                if(currentPlayer == 1)
                    _removePiece(other,STANDARD_PT_PAWN,move.to + 8);
                else if(currentPlayer == 0)
                    _removePiece(other,STANDARD_PT_PAWN,move.to - 8);
            }

            if(move.flag & MOVE_DOUBLE_PAWN)
                enpassant = (move.to + move.from)/2;
            else
                enpassant = -1;

            enpassantHistory.push_back(enpassant);

            if(move.flag & MOVE_CAPTURE)
            {
                move.capturedpiecetype = getPiece(other,move.to);
                if(move.capturedpiecetype == 255)
                {
                   
                }

                _removePiece(other,move.capturedpiecetype,move.to);
            }

            _movePiece(currentPlayer,move.piecetype,move.from,move.to);
            
            if(move.flag & MOVE_PROMOTION)
            {
                _removePiece(currentPlayer,move.piecetype,move.to);
                _addPiece(currentPlayer,move.promotionpiecetype,move.to);
            }

            if(move.flag & MOVE_KING_SIDE_CASTLING)
            {
                _movePiece(currentPlayer,STANDARD_PT_ROOK,move.to + 1,move.to - 1);
            }

            if(move.flag & MOVE_QUEEN_SIDE_CASTLING)
            {
                _movePiece(currentPlayer,STANDARD_PT_ROOK,move.to -2,move.to + 1);
            }

            currentPlayer = currentPlayer == 0 ? 1 : 0;
        }

        //Undo board move
        void undoMove(Move &move)
        {
            U8 other = currentPlayer;
            currentPlayer = currentPlayer == 0 ? 1 : 0;

            enpassantHistory.pop_back();

            if(enpassantHistory.size() > 0)
                enpassant = enpassantHistory[enpassantHistory.size() - 1];
            else
                enpassant = -1;

            if(move.flag & MOVE_EN_PASSANT)
            {
                if(currentPlayer == 1)
                    _addPiece(other,STANDARD_PT_PAWN,move.to + 8);
                else if(currentPlayer == 0)
                    _addPiece(other,STANDARD_PT_PAWN,move.to - 8);
            }

            if(move.flag & MOVE_KING_SIDE_CASTLING)
            {
                _movePiece(currentPlayer,STANDARD_PT_ROOK,move.to - 1,move.to + 1);
            }

            if(move.flag & MOVE_QUEEN_SIDE_CASTLING)
            {
                _movePiece(currentPlayer,STANDARD_PT_ROOK,move.to + 1,move.to - 2);
            }

            if(move.flag & MOVE_PROMOTION)
            {
                _removePiece(currentPlayer,move.promotionpiecetype,move.to);
                _addPiece(currentPlayer,move.piecetype,move.to);
            }

            _movePiece(currentPlayer,move.piecetype,move.to,move.from);

            if(move.flag & MOVE_CAPTURE)
                _addPiece(other,move.capturedpiecetype,move.to);  

            if(move.piecetype == STANDARD_PT_KING)
                castlingInfo[currentPlayer][0] --; 
            if((Bitboard(u64a1 << move.from) & Bitboard(FILE_A)).has() && move.piecetype == STANDARD_PT_ROOK)
                castlingInfo[currentPlayer][1] --;
            if((Bitboard(u64a1 << move.from) & Bitboard(FILE_H)).has() && move.piecetype == STANDARD_PT_ROOK)
                castlingInfo[currentPlayer][2] --;
        }

        //Generate all legal moves
        void genMoves()
        {
            moves.clear();
            legalMoves.clear();

            U8 p = currentPlayer;
            //Gen attacks
            int targetpiece = _pieces[p][STANDARD_PT_KING].bitScanForward();
            Bitboard targetsSquares = border88[targetpiece];
            Bitboard targetPieces = u64a1 << targetpiece;
            genAttacks(targetsSquares,targetPieces,targetpiece,p == 0 ? 1 : 0);

            moves = MoveList();

            //Update Temp variables
            playerPiecesInverse = ~_pieces[currentPlayer][6];
            otherPieces = (_occupied & playerPiecesInverse);
            otherPlayer = currentPlayer == 0 ? 1 : 0;
            
            //Pawns (DONE)           
            genPawnMoves();

            //Rooks (DONE)
            genRooksMoves();

            //Bishop (DONE)
            genBishopMoves();

            //Queen (DONE)
            genQueenMoves();

            //Knights (DONE)
            genKnightMoves();

            //King (DONE)
            genKingMoves();         
            
            //Clear legal moves
            legalMoves.clear();

            bool incheck = (attackedSquares & targetPieces).has();

            for (auto move : moves) 
            {
                Bitboard from = u64a1 << move.from;
                Bitboard target = u64a1 << move.to;
                
                //In Check
                if(incheck)
                {
                    //Try to espace from attacked square
                    if(targetpiece == move.from)
                    {
                        if(!(target & attackedSquares).has())
                            legalMoves.push_back(move);
                    }
                    else
                    {  
                        //Check if can capture
                        if(!(captureAttackingPieces & ~target).has())
                            legalMoves.push_back(move);

                        //Check if can protect
                        if(directAttackLines.size() > 0)
                            if((directAttackLines[0].squares & target).has())
                                legalMoves.push_back(move);
                    }
                }
                //Check if will move piece to attacked square
                else if(targetpiece == move.from)
                {
                    if(!(target & attackedSquares).has())
                        legalMoves.push_back(move);
                }
                else if(directAttackLines.size() > 0)
                {
                    if((directAttackLines[0].squares & target).has())
                        legalMoves.push_back(move);
                }
                else if(blockedAttackLines.size() > 0)
                {
                    if((attackBlockers & from).has())
                    {
                        if((blockedAttackLines[0].squares & target).has())
                            legalMoves.push_back(move);
                    }
                    else
                        legalMoves.push_back(move);
                }
                else
                    legalMoves.push_back(move);
            }  
        }

        //Generate all king moves
        void genKingMoves()
        {   
            Bitboard kings = _pieces[currentPlayer][STANDARD_PT_KING];
            
            while (kings.has())
            {
                unsigned int pos = kings.bitScanPopNext();
                Bitboard all = border88[pos] & playerPiecesInverse;
                
                //Captures
                Bitboard captures = all & otherPieces;
                
                //No captures
                Bitboard nocaptures = all & ~captures;
                
                while (nocaptures.has())
                    moves.push_back(Move(pos,nocaptures.bitScanPopNext(),STANDARD_PT_KING,MOVE_VALID));
                while (captures.has())
                {
                    int cpos = captures.bitScanPopNext();

                    Move m = Move(pos,cpos,STANDARD_PT_KING,MOVE_CAPTURE);
                    moves.push_back(m);
                }

                //Castlings
                Bitboard kingside = u64a1 << (pos + 3);
                Bitboard queenside = u64a1 << (pos - 4);

                Bitboard kingsidepath = currentPlayer == 0 ? Bitboard(15 << 4) : (Bitboard(15) << 60);
                Bitboard queensidepath = currentPlayer == 0 ? Bitboard(31) : (Bitboard(31) << 56);

                if(castlingInfo[currentPlayer][0] == 0 && castlingInfo[currentPlayer][2] == 0 && (kingsidepath & _occupied).popCount() == 2)
                    if(!(kingsidepath & attackedSquares).has() && (kingside & _pieces[currentPlayer][STANDARD_PT_ROOK]).has())
                    {
                        //Add kingside
                        Move m = Move(pos,pos + 2,STANDARD_PT_KING,MOVE_KING_SIDE_CASTLING);
                        moves.push_back(m);
                    }

                if(castlingInfo[currentPlayer][1] == 0 && castlingInfo[currentPlayer][1] == 0 && (queensidepath & _occupied).popCount() == 2)
                    if(!(queensidepath & attackedSquares).has() && (queenside & _pieces[currentPlayer][STANDARD_PT_ROOK]).has())
                    {
                        //Add kingside
                        Move m = Move(pos,pos - 2,STANDARD_PT_KING,MOVE_QUEEN_SIDE_CASTLING);
                        moves.push_back(m);
                    }
            }
        }

        //Generate all pawn moves
        void genPawnMoves()
        {
            if(currentPlayer == 0)
            {
                //Pawn single moves
                Bitboard pawns = _pieces[currentPlayer][0];
                Bitboard pawnsm = (pawns << 8) & _notoccupied;
                Bitboard pawndm = (pawnsm << 8) & _notoccupied & RANK_4;
                
                //Gen pawn promotions
                Bitboard pawnpromo = pawnsm & RANK_8;
                pawnsm &= ~RANK_8;

                Bitboard pawnlc = (pawns << 7) & otherPieces & ~BFILE_H & ~RANK_8;
                Bitboard pawnrc = (pawns << 9) & otherPieces & ~BFILE_A & ~RANK_8;

                Bitboard pawnlcpromo = (pawns << 7) & otherPieces & ~BFILE_H & RANK_8;
                Bitboard pawnrcpromo = (pawns << 9) & otherPieces & ~BFILE_A & RANK_8;
 
                while (pawnsm.has())
                {
                    unsigned int pos = pawnsm.bitScanPopNext();
                    moves.push_back(Move(pos - 8,pos,STANDARD_PT_PAWN,MOVE_VALID));
                }

                while (pawndm.has())
                {
                    unsigned int pos = pawndm.bitScanPopNext();
                    moves.push_back(Move(pos - 16,pos,STANDARD_PT_PAWN,MOVE_DOUBLE_PAWN));
                }

                while (pawnlc.has())
                {
                    unsigned int pos = pawnlc.bitScanPopNext();

                    Move m(pos - 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE);
                    moves.push_back(m);
                }

                while (pawnrc.has())
                {
                    unsigned int pos = pawnrc.bitScanPopNext();

                    Move m(pos - 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE);
                    moves.push_back(m);
                }

            
                //Promotions
                while (pawnpromo.has())
                {
                    unsigned int pos = pawnpromo.bitScanPopNext();
                    Move mva(pos - 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mva.promotionpiecetype = STANDARD_PT_ROOK;
                    moves.push_back(mva);

                    Move mvb(pos - 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mvb.promotionpiecetype = STANDARD_PT_QUEEN;
                    moves.push_back(mvb);

                    Move mvc(pos - 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mvc.promotionpiecetype = STANDARD_PT_BISHOP;
                    moves.push_back(mvc);

                    Move mvd(pos - 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mvd.promotionpiecetype = STANDARD_PT_KNIGHT;
                    moves.push_back(mvd);
                }

                while (pawnrcpromo.has())
                {
                    unsigned int pos = pawnrcpromo.bitScanPopNext();

                    Move m(pos - 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    m.promotionpiecetype = STANDARD_PT_ROOK;
                    moves.push_back(m);

                    Move mb(pos - 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mb.promotionpiecetype = STANDARD_PT_KNIGHT;
                    moves.push_back(mb);

                    Move mc(pos - 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mc.promotionpiecetype = STANDARD_PT_QUEEN;
                    moves.push_back(mc);

                    Move md(pos - 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    md.promotionpiecetype = STANDARD_PT_BISHOP;
                    moves.push_back(md);
                }

                while (pawnlcpromo.has())
                {
                    unsigned int pos = pawnlcpromo.bitScanPopNext();

                    Move m(pos - 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    m.promotionpiecetype = STANDARD_PT_ROOK;
                    moves.push_back(m);

                    Move mb(pos - 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mb.promotionpiecetype = STANDARD_PT_KNIGHT;
                    moves.push_back(mb);

                    Move mc(pos - 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mc.promotionpiecetype = STANDARD_PT_QUEEN;
                    moves.push_back(mc);

                    Move md(pos - 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    md.promotionpiecetype = STANDARD_PT_BISHOP;
                    moves.push_back(md);
                }

                if(enpassant != -1)
                {
                    Bitboard enpa = ((u64a1 << enpassant));

                    while(pawns.has())
                    {
                        unsigned int pos = pawns.bitScanPopNext();
                        Bitboard pawn = u64a1 << pos;
                        Bitboard bothcaptures = ((pawn << 7) & ~BFILE_H) | ((pawn << 9) & ~BFILE_A);

                        if((bothcaptures & enpa).has())
                            moves.push_back(Move(pos,enpassant,STANDARD_PT_PAWN,MOVE_EN_PASSANT));
                    }          
                }
            } 
            else
            {
                Bitboard pawns = _pieces[currentPlayer][0];

                Bitboard pawnsm = (pawns >> 8) & _notoccupied; 
                Bitboard pawndm = (pawnsm >> 8) & _notoccupied & RANK_5;

                //Gen pawn promotions
                Bitboard pawnpromo = pawnsm & RANK_1;
                pawnsm &= ~RANK_1;

                Bitboard pawnlc = (pawns >> 7) & otherPieces & ~BFILE_A & ~RANK_1;
                Bitboard pawnrc = (pawns >> 9) & otherPieces & ~BFILE_H & ~RANK_1;

                Bitboard pawnlcpromo = (pawns >> 7) & otherPieces & ~BFILE_A & RANK_1;
                Bitboard pawnrcpromo = (pawns >> 9) & otherPieces & ~BFILE_H & RANK_1;

                while (pawnsm.has())
                {
                    unsigned int pos = pawnsm.bitScanPopNext();
                    moves.push_back(Move(pos + 8,pos,STANDARD_PT_PAWN,MOVE_VALID));
                }
                
                while (pawndm.has())
                {
                    unsigned int pos = pawndm.bitScanPopNext();
                    moves.push_back(Move(pos + 16,pos,STANDARD_PT_PAWN,MOVE_DOUBLE_PAWN));
                }

                while (pawnlc.has())
                {
                    unsigned int pos = pawnlc.bitScanPopNext();

                    Move m(pos + 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE);
                    moves.push_back(m);
                }

                while (pawnrc.has())
                {
                    unsigned int pos = pawnrc.bitScanPopNext();

                    Move m(pos + 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE);
                    moves.push_back(m);
                }

                //Promotions
                while (pawnpromo.has())
                {
                    unsigned int pos = pawnpromo.bitScanPopNext();
                    Move mva(pos + 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mva.promotionpiecetype = STANDARD_PT_ROOK;
                    moves.push_back(mva);

                    Move mvb(pos + 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mvb.promotionpiecetype = STANDARD_PT_QUEEN;
                    moves.push_back(mvb);

                    Move mvc(pos + 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mvc.promotionpiecetype = STANDARD_PT_BISHOP;
                    moves.push_back(mvc);

                    Move mvd(pos + 8,pos,STANDARD_PT_PAWN,MOVE_PROMOTION);
                    mvd.promotionpiecetype = STANDARD_PT_KNIGHT;
                    moves.push_back(mvd);
                }


                while (pawnrcpromo.has())
                {
                    unsigned int pos = pawnrcpromo.bitScanPopNext();

                    Move m(pos + 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    m.promotionpiecetype = STANDARD_PT_ROOK;
                    moves.push_back(m);

                    Move mb(pos + 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mb.promotionpiecetype = STANDARD_PT_KNIGHT;
                    moves.push_back(mb);

                    Move mc(pos + 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mc.promotionpiecetype = STANDARD_PT_QUEEN;
                    moves.push_back(mc);

                    Move md(pos + 9,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    md.promotionpiecetype = STANDARD_PT_BISHOP;
                    moves.push_back(md);
                }

                while (pawnlcpromo.has())
                {
                    unsigned int pos = pawnlcpromo.bitScanPopNext();

                    Move m(pos + 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    m.promotionpiecetype = STANDARD_PT_ROOK;
                    moves.push_back(m);

                    Move mb(pos + 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mb.promotionpiecetype = STANDARD_PT_KNIGHT;
                    moves.push_back(mb);

                    Move mc(pos + 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    mc.promotionpiecetype = STANDARD_PT_QUEEN;
                    moves.push_back(mc);

                    Move md(pos + 7,pos,STANDARD_PT_PAWN,MOVE_CAPTURE | MOVE_PROMOTION);
                    md.promotionpiecetype = STANDARD_PT_BISHOP;
                    moves.push_back(md);
                }

                if(enpassant != -1)
                {
                    Bitboard enpa = ((u64a1 << enpassant));

                    while(pawns.has())
                    {
                        unsigned int pos = pawns.bitScanPopNext();
                        Bitboard pawn = u64a1 << pos;
                        Bitboard bothcaptures = ((pawn >> 7) & ~BFILE_A) | ((pawn >> 9) & ~BFILE_H);

                        if((bothcaptures & enpa).has())
                            moves.push_back(Move(pos,enpassant,STANDARD_PT_PAWN,MOVE_EN_PASSANT));
                    }          
                }
            }  
        }

        //Generate all rook moves
        void genRooksMoves()
        {
            Bitboard pieces = (_pieces[currentPlayer][STANDARD_PT_ROOK]);

            while (pieces.has())
            {
                unsigned int pos = pieces.bitScanPopNext();
                
                //All moves
                Bitboard all = genRayMoves(pos,NORTH,currentPlayer,false) | genRayMoves(pos,SOUTH,currentPlayer,true) | genRayMoves(pos,EAST,currentPlayer,false) | genRayMoves(pos,WEST,currentPlayer,true);
                
                //Captures
                Bitboard captures = all & otherPieces;
                
                //No captures
                Bitboard nocaptures = all & ~captures;

                while (nocaptures.has())
                    moves.push_back(Move(pos,nocaptures.bitScanPopNext(),STANDARD_PT_ROOK,MOVE_VALID));
                while (captures.has())
                {
                    int cpos = captures.bitScanPopNext();

                    Move m = Move(pos,cpos,STANDARD_PT_ROOK,MOVE_CAPTURE);
                    moves.push_back(m);
                }
            }
        }

        //Generate all bishop moves
        void genBishopMoves()
        {
            Bitboard pieces = (_pieces[currentPlayer][STANDARD_PT_BISHOP]);

            while (pieces.has())
            {
                unsigned int pos = pieces.bitScanPopNext();
                
                //All moves
                Bitboard all = genRayMoves(pos,NORTH_EAST,currentPlayer,false) | genRayMoves(pos,SOUTH_EAST,currentPlayer,true) | genRayMoves(pos,NORTH_WEST,currentPlayer,false) | genRayMoves(pos,SOUTH_WEST,currentPlayer,true);
                
                //Captures
                Bitboard captures = all & otherPieces;
                
                //No captures
                Bitboard nocaptures = all & ~captures;

                while (nocaptures.has())
                    moves.push_back(Move(pos,nocaptures.bitScanPopNext(),STANDARD_PT_BISHOP,MOVE_VALID));
                while (captures.has())
                {
                    int cpos = captures.bitScanPopNext();

                    Move m = Move(pos,cpos,STANDARD_PT_BISHOP,MOVE_CAPTURE);
                    moves.push_back(m);
                }
            }
        }

        //Generate all queen moves
        void genQueenMoves()
        {
            Bitboard pieces = (_pieces[currentPlayer][STANDARD_PT_QUEEN]);

            while (pieces.has())
            {
                unsigned int pos = pieces.bitScanPopNext();
                
                //All moves
                Bitboard all = genRayMoves(pos,NORTH,currentPlayer,false) | genRayMoves(pos,SOUTH,currentPlayer,true) | genRayMoves(pos,EAST,currentPlayer,false) | genRayMoves(pos,WEST,currentPlayer,true) | genRayMoves(pos,NORTH_EAST,currentPlayer,false) | genRayMoves(pos,SOUTH_EAST,currentPlayer,true) | genRayMoves(pos,NORTH_WEST,currentPlayer,false) | genRayMoves(pos,SOUTH_WEST,currentPlayer,true);
                
                //Captures
                Bitboard captures = all & otherPieces;
                
                //No captures
                Bitboard nocaptures = all & ~captures;

                while (nocaptures.has())
                    moves.push_back(Move(pos,nocaptures.bitScanPopNext(),STANDARD_PT_QUEEN,MOVE_VALID));
                while (captures.has())
                {
                    int cpos = captures.bitScanPopNext();

                    Move m = Move(pos,cpos,STANDARD_PT_QUEEN,MOVE_CAPTURE);
                    moves.push_back(m);
                }
            }
        }

        //Generate all knight moves
        void genKnightMoves()
        {
            Bitboard pieces = (_pieces[currentPlayer][STANDARD_PT_KNIGHT]);

            while (pieces.has())
            {
                unsigned int pos = pieces.bitScanPopNext();
                Bitboard all = knight88[pos];
                all &= playerPiecesInverse;
                
                //Captures
                Bitboard captures = all & otherPieces;
                
                //No captures
                Bitboard nocaptures = all & ~captures;

                while (nocaptures.has())
                    moves.push_back(Move(pos,nocaptures.bitScanPopNext(),STANDARD_PT_KNIGHT,MOVE_VALID));
                while (captures.has())
                {
                    int cpos = captures.bitScanPopNext();

                    Move m = Move(pos,cpos,STANDARD_PT_KNIGHT,MOVE_CAPTURE);
                    moves.push_back(m);
                }
            }
        }

        //Generate move rays
        Bitboard genRayMoves(int pos,Direction direction,U8 player,bool reverse)
        {
            Bitboard ray = rays88[direction][pos];
            //Get blocker
            int blockindex = reverse ? (ray & _occupied).bitScanReverse() : (ray & _occupied).bitScanForward();
            if(blockindex >= 0)
                ray &= ~rays88[direction][blockindex];

            //Remove player piece
            ray &= ~_pieces[player][6];
            return ray;
        }
        #pragma endregion

        /**
         * MARKER Attacks Utils
         */
        #pragma region
        void genAttacks(Bitboard targetsSquares,Bitboard targetPieces,int targetsquare,U8 player)
        {
            //Get all attacked squares
            attackedSquares.clear();
            attackBlockers.clear();

            //Clear attacks
            directAttackLines.clear();
            blockedAttackLines.clear();
            captureAttackingPieces.clear();

            //Rooks
            {
                Bitboard pieces = (_pieces[player][STANDARD_PT_ROOK]);

                while (pieces.has())
                {
                    unsigned int pos = pieces.bitScanPopNext();

                    genAttackRay(pos,SOUTH,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,WEST,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,EAST,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,NORTH,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                }
            }

            //Bishop
            {
                Bitboard pieces = (_pieces[player][STANDARD_PT_BISHOP]);

                while (pieces.has())
                {
                    unsigned int pos = pieces.bitScanPopNext();

                    genAttackRay(pos,SOUTH_EAST,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,SOUTH_WEST,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,NORTH_EAST,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,NORTH_WEST,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                }
            }

            //Queen
            {
                Bitboard pieces = (_pieces[player][STANDARD_PT_QUEEN]);

                while (pieces.has())
                {
                    unsigned int pos = pieces.bitScanPopNext();

                    genAttackRay(pos,SOUTH,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,WEST,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,EAST,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,NORTH,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,SOUTH_EAST,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,SOUTH_WEST,player,true,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,NORTH_EAST,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    genAttackRay(pos,NORTH_WEST,player,false,targetsquare,targetsSquares,targetPieces,attackedSquares,attackBlockers);
                    
                }
            }

            //King
            {
                Bitboard pieces = (_pieces[player][STANDARD_PT_KING]);

                while (pieces.has())
                {
                    unsigned int pos = pieces.bitScanPopNext();
                    attackedSquares |= border88[pos];

                    if((border88[pos] & targetPieces).has())
                        captureAttackingPieces |= u64a1 << pos;
                }
            }

            //Knight
            {
                Bitboard pieces = (_pieces[player][STANDARD_PT_KNIGHT]);

                while (pieces.has())
                {
                    unsigned int pos = pieces.bitScanPopNext();
                    attackedSquares |= knight88[pos];

                    if((knight88[pos] & targetPieces).has())
                        captureAttackingPieces |= u64a1 << pos;
                }
            }

            //Pawn attacks
            {
                Bitboard pawns = (_pieces[player][STANDARD_PT_PAWN]);

                if(player == 0)
                {
                    Bitboard b = ((pawns << 7) & ~BFILE_H);
                    Bitboard a = ((pawns << 9) & ~BFILE_A);

                    attackedSquares |= b | a;

                    if((b & targetPieces).has())
                        captureAttackingPieces |= (b & targetPieces) >> 7;
                    if((a & targetPieces).has())
                        captureAttackingPieces |= (a & targetPieces) >> 9;
                }
                else
                {
                    Bitboard b = ((pawns >> 7) & ~BFILE_A);
                    Bitboard a = ((pawns >> 9) & ~BFILE_H);

                    attackedSquares |= b | a;

                    if((b & targetPieces).has())
                        captureAttackingPieces |= (b & targetPieces) << 7;
                    if((a & targetPieces).has())
                        captureAttackingPieces |= (a & targetPieces) << 9;
                }
            }
        }

        void genAttackRay(int pos,Direction direction,U8 player,bool reverse,int targetsquare,Bitboard &targetsSquares,Bitboard &targetPieces,Bitboard &squares,Bitboard &blockers)
        {
            //Create next
            Bitboard ray = rays88[direction][pos];

            if((ray & (targetPieces)).has())
            {
                //Targeting piece
                int blockindex = reverse ? (ray & targetPieces).bitScanReverse() : (ray & targetPieces).bitScanForward();
                int blockindexafter = reverse ? (ray & _occupied & (~targetPieces)).bitScanReverse() : (ray & _occupied & (~targetPieces)).bitScanForward();
                
                Bitboard b = ray & (~rays88[direction][blockindex]);

                if(blockindexafter != -1)
                    squares |= (ray & (~rays88[direction][blockindexafter]));
                else
                    squares |= ray;

                if(blockindexafter == -1 || (reverse ? (blockindex > blockindexafter) : (blockindex < blockindexafter)))
                {
                    captureAttackingPieces |= u64a1 << pos;
                    //Add direct attacking lines
                    directAttackLines.push_back(AttackLine((rays88[direction][pos] & ~rays88[direction][targetsquare]) | Bitboard(u64a1 << pos),blockindex));
                }
                else if((b & _occupied).popCount() == 2)
                {
                    blockers |= u64a1 << blockindexafter;
                    //Defended
                    blockedAttackLines.push_back(AttackLine((rays88[direction][pos] & ~rays88[direction][targetsquare]) | Bitboard(u64a1 << pos),blockindex));
                }
                
            }
            else
            {
                int blockindex = reverse ? (ray & _occupied).bitScanReverse() : (ray & _occupied).bitScanForward();
                if(blockindex > -1)            
                    squares |= ray & (~rays88[direction][blockindex]);  
                else
                    squares |= ray;                       
            }  
        }
        #pragma endregion

        /**
         * MARKER Piece utils
         */
        #pragma region 
        void _removePiece(U8 player, U8 piece, U8 pos) 
        {
            Bitboard square = u64a1 << pos;

            _pieces[player][piece] ^= square;
            _pieces[player][6] ^= square;

            _occupied ^= square;
            
            _notoccupied = ~_occupied;
        }

        void _addPiece(U8 player, U8 piece, U8 pos) 
        {
            Bitboard square = u64a1 << pos;

            _pieces[player][piece] |= square;
            _pieces[player][6] |= square;

            _occupied |= square;
            _notoccupied = ~_occupied;
        }

        void _movePiece(U8 player, U8 piece, U8 from, U8 to)
        {
            Bitboard squareMask =  (u64a1 << to) | (u64a1 << from);

            _pieces[player][piece] ^= squareMask;
            _pieces[player][6] ^= squareMask;

            _occupied ^= squareMask;
            _notoccupied = ~_occupied;
        }
        #pragma endregion

        /**
         * MARKER Move Utils
         */
        #pragma region 
        void stringifyMove(Move move,std::string &output)
        {
            char c = piecesChars[move.piecetype];
            std::string s = c == 'P' ? (std::string() + posToInt(move.from)) : (std::string() + c + posToInt(move.from));

            if(move.flag & MOVE_KING_SIDE_CASTLING)
            {
                output = "O-O";
                return;
            }

            if(move.flag & MOVE_QUEEN_SIDE_CASTLING)
            {
                output = "O-O-O";
                return;
            }

            if(move.flag & MOVE_CAPTURE)
                s += "x" + posToInt(move.to);
            else
                s += posToInt(move.to);
            
            if(move.flag & MOVE_PROMOTION)
                s = s + "=" + piecesChars[move.promotionpiecetype];

            if(playerIsInCheck(currentPlayer))
            {
                //Testing only
                genMoves();
                if(legalMoves.size() == 0)
                    s = s + "#";
                else
                    s = s + "+";
            }
            
            output = s;
        }

        std::string posToInt(int pos)
        {   
            int column = pos%8;
            int row = pos/8;

            std::string s = std::string();
            return s + (char)(column + 97) + std::to_string(row + 1);
        }

        Move parseMove(std::string move,std::string &status)
        {
            if(move == "O-O-O")
            {
                genMoves();
                for(auto move : legalMoves)
                {
                    if(move.flag & MOVE_QUEEN_SIDE_CASTLING)
                        return move;
                }

                status = "Error: Illegal move!";
                return Move();
            }
            else if(move == "O-O")
            {
                genMoves();
                for(auto move : legalMoves)
                {
                    if(move.flag & MOVE_KING_SIDE_CASTLING)
                        return move;
                }

                status = "Error: Illegal move!";
                return Move();
            }

            //No length
            if(move.length() == 0)
            {
                status = "Error: Too short move";
                return Move();
            }

            //Expected behaviours
            bool expected_check = false; //DONE
            bool expected_mate = false; //DONE
            bool expected_capture = false; //DONE
            char expected_type = 'P'; //DONE
            U8 promotion_target = 255; //DONE
            int target_destination = 0; //DONE
            int from_column = -1; //DONE
            int from_row = -1; //DONE

            if(move.at(move.length() - 1) == '+')
            {
                expected_check = true;
                move = move.substr(0, move.length()-1);
            }
            else if(move.at(move.length() - 1) == '#')
            {
                expected_mate = true;
                move = move.substr(0, move.length()-1);
            }

            //No length
            if(move.length() == 0)
            {
                status = "Error: Too short move";
                return Move();
            }

            //Piece type first
            if(isupper(move.at(0)))
            {
                expected_type = move.at(0);
                move = move.substr(1);

                if(std::string("KNQRB").find(expected_type) == std::string::npos)
                {
                    status = "Warning: Invalid piece type '";
                    status += expected_type;
                    status += "'\n";
                }
            }

            size_t pos = std::string(move).find('x');
            if(pos != std::string::npos)
            {
                expected_capture = true;
                move = move.replace(pos,1,"");
            }

            //Check promotion
            if(isupper(move.at(move.length() - 1)))
            {
                if(move.length() == 1)
                {
                    status = "Error: Too short move";
                    return Move();
                }
                
                if(move.at(move.length() - 2) != '=')
                {
                    status = "Error: Expected '=' before promotion target";
                    return Move();
                }

                char c = move.at(move.length() - 1);

                switch (expected_type)
                {
                    case 'B':
                        promotion_target = STANDARD_PT_BISHOP;
                        break;

                    case 'R':
                        promotion_target = STANDARD_PT_ROOK;
                        break;

                    case 'N':
                        promotion_target = STANDARD_PT_KNIGHT;
                        break;

                    case 'Q':
                        promotion_target = STANDARD_PT_QUEEN;
                        break;
                
                    default:
                        break;
                }
                
                move = move.substr(0,move.length() - 2);
            }

            if(move.length() < 2)
            {
                status = "Error: No valid destination\n";
                return Move();
            }
            else if(move.length() > 4)
            {
                status = "Error: Too long info\n";
                return Move();
            }

            //Check destination
            if(isalpha(move.at(move.length() - 2)) && islower(move.at(move.length() - 2)) && isdigit(move.at(move.length() - 1)))
            {
                int row = ((int) move.at(move.length() - 1)) - 49;
                int column = ((int) move.at(move.length() - 2)) - 97;

                target_destination = 8 * row + column;
                
                
                if(row < 0 || row > 7 || column < 0 || column > 7)
                {
                    status = "Error: Destination '";
                    status += move.substr(move.length() - 2,2);
                    status += "' is not a valid destination!";
                    return Move();
                }

                move = move.substr(0,move.length() - 2);
                if(move.length() > 0)
                    if(move.length() == 2)
                    {
                        if(isalpha(move.at(move.length() - 2)) && islower(move.at(move.length() - 2)) && isdigit(move.at(move.length() - 1)))
                        {
                            int row = ((int) move.at(move.length() - 1)) - 49;
                            int column = ((int) move.at(move.length() - 2)) - 97;

                            if(row < 0 || row > 7 || column < 0 || column > 7)
                            {
                                status = "Error: Source '";
                                status += move;
                                status += "' is not a valid source!";
                                return Move();
                            }

                            from_column = column;
                            from_row = row;
                        }
                        else
                        {
                            status = "Error: Source '";
                            status += move;
                            status += "' is not a valid source!";
                        }
                    }
                    else if(isdigit(move.at(move.length() - 1)))
                    {
                        int row = ((int) move.at(move.length() - 1)) - 49;
                        from_row = row;

                        if(row < 0 || row > 7)
                        {
                            status = "Error: Source '";
                            status += move;
                            status += "' is not a valid source!";
                            return Move();
                        }
                    }
                    else if(isalpha(move.at(move.length() - 1)) && islower(move.at(move.length() - 1)))
                    {
                        int column = ((int) move.at(move.length() - 1)) - 97;
                        from_column = column;

                        if(column < 0 || column > 7)
                        {
                            status = "Error: Source '";
                            status += move;
                            status += "' is not a valid source!";
                            return Move();
                        }
                    }
                    else
                    {
                        status = "Error: Source '";
                        status += move;
                        status += "' is not a valid source!";
                    }
            }
            else
            {
                status = "Error: Destination '";
                status += move.substr(move.length() - 2,2);
                status += "' is not a valid destination!";
            }

            //Get piece type to move
            int piecetypeid = 0;
            switch (expected_type)
            {
                case 'B':
                    piecetypeid = STANDARD_PT_BISHOP;
                    break;

                case 'R':
                    piecetypeid = STANDARD_PT_ROOK;
                    break;

                case 'N':
                    piecetypeid = STANDARD_PT_KNIGHT;
                    break;

                case 'K':
                    piecetypeid = STANDARD_PT_KING;
                    break;

                case 'Q':
                    piecetypeid = STANDARD_PT_QUEEN;
                    break;
            
                default:
                    break;
            }

            //Piece filter
            Bitboard piece_filter = u64one;
            if(from_row != -1)
                piece_filter &= RANKS[from_row];
            if(from_column != -1)
                piece_filter &= FILES[from_column];

            //Generate moves
            genMoves();
            
            bool found = false;
            Move m;

            //Moves
            for (auto move : legalMoves)
            {
                if(move.piecetype == piecetypeid)
                {
                    if((piece_filter & Bitboard(u64a1 << move.from)).has())
                    {
                        if(move.to == target_destination && move.promotionpiecetype == promotion_target)
                        {
                            if(found)
                            {
                                status = "Error: Ambiguity found in move";
                                return Move();
                            }

                            //Check warnings
                            if((move.flag & MOVE_CAPTURE) != expected_capture)
                            {
                                if(expected_capture)
                                    status += "Warning: Expected capture not found in move\n";
                                else
                                    status += "Warning: Inexpected capture found in move\n";
                            }

                            m = move;
                            found = true;
                        }
                    }
                }
            }

            if(found)
            {
                doMove(m);
                //Check warnings 2
                if(playerIsInCheck(currentPlayer) != (expected_check))
                {
                    if(expected_capture)
                        status += "Warning: Expected check state not found in move\n";
                    else
                        status += "Warning: Inexpected check state found in move\n";
                }

                genMoves();
                //Check warnings 3
                if((legalMoves.size() == 0) != expected_mate)
                {
                    if(expected_mate)
                        status += "Warning: Expected mate state not found in move\n";
                    else
                        status += "Warning: Inexpected mate state found in move\n";
                }
                undoMove(m);

                //Return status
                if(status.length() > 0)
                    status = status.substr(0,status.length() - 1);
                return m;
            }
                
            if((_pieces[currentPlayer][piecetypeid] & piece_filter).has())
            {
                status = "Error: Illegal move!";
                return Move();
            }

            status = "Error: No valid piece found for move!";
            return Move();
        }
        #pragma endregion
};
#pragma endregion
#endif