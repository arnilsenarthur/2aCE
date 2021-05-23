
# 2aCE
### Árnilsen's Adaptable Chess Engine
<center>
<img src="https://badgen.net/badge/license/GNU/red">
<img src="https://badgen.net/badge/Version/1.0.0/blue">
<img src="https://badgen.net/badge/Language/C++/pink">
<img src="https://badgen.net/badge/Status/Not-stable yet/yellow">
</center>



2aCE is a chess engine in development, created for standard and custom chess game modes. Created by **Árnilsen Arthur** in 2021, using bitboard method in C++

## Features
- [X] Very Fast/Optmized
- [X] Bitboard (8x8 and 16x16)
- [X] Rays optmization (8x8 and 16x16)
- [X] Standard test Mode (8x8)
- - [X] Legal move generation 
- - - [X] En Passant
- - - [X] Castling
- - [X] Random plays
- - [X] **FEN** load/save
- - [X] **PGN** Move parsing/stringifier
- [ ] Test mode (16x16)

## Future Targets
- 16x16 board size limit (For custom games like 2x2 players)
- Team support
- **AI** system
- Game analysis
- **UCI** Support

## Simple Usage Example
```c++
//Create standard chess board (8x8, White x Black)
StandardBoard board;

std::string status;
//Parse Move
Move mv = board.parseMove("c4",status);
if(mv.isValid())
{
	//Do Move
	board.doMove(mv);
    board.print();
}
else
	//Print what is wrong
    cout << status;
````

## I/O
For now, 2aCE don't support **UCI**, but you can use built methods to test engine. All the outputs are also formatted as you can see bellow:

```c++
Bitboard bitboard = ...;
bitboard.print();

//8x8
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0

//16x16
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

```c++
StandardBoard board = ...;
board.print();

8 r n b q k b n r
7 p p p p p p p p
6 . . . . . . . .
5 . . . . . . . .
4 . . . . . . . .
3 . . . . . . . .
2 P P P P P P P P
1 R N B Q K B N R
  a b c d e f g h
```
	
## Performance
### Version 1.0.0

Performance Test code:
```c++
//Create board
StandardBoard board;

//Seed
srand (time(NULL));
auto start  = chrono::steady_clock::now();

//Do n random moves
for(int i = 0; i < n; i ++)
{
    board.genMoves();
  
    if(board.legalMoves.size() == 0)
    {
        cout << "Break: " << i;
  	    break;
    }

    Move mv = board.legalMoves[rand() % board.legalMoves.size()];
    board.doMove(mv);
}

//Finalize, print elapsed time and moves    
auto end  = chrono::steady_clock::now();
cout <<" Test ended in " << chrono::duration_cast<chrono::microseconds>(end - start).count()/1000.0 << "ms" << endl;
```

| Moves | Tests | Average (ms) | Min (ms) | Max (ms)|
|-------|-------|---------|-----|-----|
|1      | 10    | 0.038  | 0.03|0.072|
|100    | 10    | 0.945  |0.845|1.232|
|500000|10|1258.606|1184.92|1391.27|

