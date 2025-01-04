#include <cstdint>
#include <iostream>
using namespace std;

struct Bitboards {
  uint64_t white_pawns;
  uint64_t white_rooks;
  uint64_t white_knights;
  uint64_t white_bishops;
  uint64_t white_queen;
  uint64_t white_king;

  uint64_t black_pawns;
  uint64_t black_rooks;
  uint64_t black_knights;
  uint64_t black_bishops;
  uint64_t black_queen;
  uint64_t black_king;
};

void pawn_development(Bitboards &board,int file ,int rank, int moves) 
{
  uint64_t allbits=board.black_king | board.black_queen | board.black_rooks | board.black_bishops | board.black_knights | board.black_pawns|board.white_king | board.white_queen | board.white_rooks | board.white_bishops | board.white_knights | board.white_pawns;
  uint64_t pawn = 0x8000000000000000 >> (((8 - rank)) * 8 + (8 - file));
  if ((pawn & board.white_pawns) != 0) 
  {
    pawn = pawn<<8;
    if (moves == 2)
    {
      if (rank!=2)
      {
        cout<<"Illegal move(2 move)";
        return;
      }
      if ((pawn & allbits)!=0)
      {
        cout<<"square occupied";
        return;
      }
      pawn = pawn<<8;
    }
    if ((pawn & allbits)!=0)
    {
      cout<<"square occupied";
      return;
    }
    uint64_t erase =  0x8000000000000000 >> (((8 - rank)) * 8 + ( 8 - file));
    board.white_pawns = board.white_pawns ^ erase ^ pawn;
  }
  else if ((pawn & board.black_pawns) != 0)
  {
    pawn = pawn>>8;
    if (moves == 2)
    {
      if (rank!=7)
      {
        cout<<"Illegal move(2 move)";
        return;
      }
      if ((pawn & allbits)!=0)
      {
        cout<<"square occupied";
        return;
      }
      pawn = pawn>>8;
    }
    if ((pawn & allbits)!=0)
    {
      cout<<"square occupied";
      return;
    }
    uint64_t erase =  0x8000000000000000 >> (((8 - rank)) * 8 + ( 8 - file));
    board.black_pawns = board.black_pawns ^ erase ^ pawn;
  }
  else
  {
    cout<<"No Black or White pawn peice present";
    return;
  }
}

void print_board(const Bitboards &board) {
  cout << "  a b c d e f g h" << endl; // File labels
  for (int rank = 7; rank >= 0; --rank) {
    cout << (rank + 1) << " "; // Rank labels
    for (int file = 0; file < 8; ++file) {
      uint64_t square = 1ULL << (rank * 8 + file);

      if (board.white_pawns & square)
        cout << "P ";
      else if (board.white_rooks & square)
        cout << "R ";
      else if (board.white_knights & square)
        cout << "N ";
      else if (board.white_bishops & square)
        cout << "B ";
      else if (board.white_queen & square)
        cout << "Q ";
      else if (board.white_king & square)
        cout << "K ";
      else if (board.black_pawns & square)
        cout << "p ";
      else if (board.black_rooks & square)
        cout << "r ";
      else if (board.black_knights & square)
        cout << "n ";
      else if (board.black_bishops & square)
        cout << "b ";
      else if (board.black_queen & square)
        cout << "q ";
      else if (board.black_king & square)
        cout << "k ";
      else
        cout << ". "; // Empty square
    }
    cout << (rank + 1) << endl; // Rank labels on the right
  }
  cout << "  a b c d e f g h" << endl; // File labels at the bottom
}

int main() {
  Bitboards board = {
      0x000000000000FF00, // white pawns
      0x0000000000000081, // white rooks
      0x0000000000000042, // white knights
      0x0000000000000024, // white bishops
      0x0000000000000008, // white queen
      0x0000000000000010, // white king

      0x00FF000000000000, // black pawns
      0x8100000000000000, // black rooks
      0x4200000000000000, // black knights
      0x2400000000000000, // black bishops
      0x0800000000000000, // black queen
      0x1000000000000000, // black king
  };                      // initializing initial chess board
    print_board(board);
    
}