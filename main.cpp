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

int enpassant;
int move_count = 0;

int piece_lookup(Bitboards &board,int file, int rank)
{
	uint64_t square = 0x8000000000000000 >> (((8 - rank)) * 8 + (file-1));

	uint64_t white=board.white_pawns|board.white_bishops|board.white_rooks|board.white_king|board.white_knights|board.white_queen;
	uint64_t black=board.black_pawns|board.black_bishops|board.black_rooks|board.black_king|board.black_knights|board.black_queen;
	if((square & white)!=0)
	{
		if((square & board.white_pawns)!=0)
		{
			return 1;
		}
		else if((square & board.white_rooks)!=0)
		{
			return 2;
		}
		else if((square & board.white_knights)!=0)
		{
			return 3;
		}
		else if ((square & board.white_bishops)!=0)
		{
			return 4;
		}
		else if ((square & board.white_queen)!=0)
		{
			return 5;
		}
		else if ((square & board.white_king)!=0)
		{
			return 6;
		}
	}
	else if ((square & black)!=0)
	{
		if((square & board.black_pawns)!=0)
		{
			return -1;
		}
		else if((square & board.black_rooks)!=0)
		{
			return -2;
		}
		else if((square & board.black_knights)!=0)
		{
			return -3;
		}
		else if ((square & board.black_bishops)!=0)
		{
			return -4;
		}
		else if ((square & board.black_queen)!=0)
		{
			return -5;
		}
		else if ((square & board.black_king)!=0)
		{
			return -6;
		}

	}
	else {
		return 0;
	}

}


void bishop(Bitboards &board,int file,int rank, int dest_file,int dest_rank)
{
	uint64_t piece = 0x8000000000000000 >> (((8 - rank)) * 8 + (file-1));


	int delx=abs(dest_file - file);
	int dely=abs(dest_rank - rank);
	if(delx != dely)
	{
		cout<<"invalid move";
		return;
	}
	if(dest_file>file)
	{
		if(dest_rank>rank)
		{
			delx--;
			while(delx)
			{
				piece>>(9);
				if(piece_lookup(board,file,rank)!=0)
				{
					cout<<"pieces present en route";
					return;
				}
				delx--;
			}
		}
		else
		{
			delx--;
			while(delx)
			{
				piece<<(7);
				if(piece_lookup(board,file,rank)!=0)
				{
					cout<<"pieces present en route";
					return;
				}
				delx--;
			}
		}
	}
	else
	{
		if(dest_rank>rank)
		{
			delx--;
			while(delx)
			{
				piece>>(7);
				if(piece_lookup(board,file,rank)!=0)
				{
					cout<<"pieces present en route";
					return;
				}
				delx--;
			}
		}
		else
		{
			delx--;
			while(delx)
			{
				piece<<(9);
				if(piece_lookup(board,file,rank)!=0)
				{
					cout<<"pieces present en route";
					return;
				}
				delx--;
			}
		}
	}
	if(piece_lookup(board,file,rank)==4)
	{
		cout<<"White bishop";
		piece = 0x8000000000000000 >> (((8 - rank)) * 8 + (file-1));
		uint64_t capture = 0x8000000000000000 >> (((8 - dest_rank)) * 8 + (dest_file-1));
		if(piece_lookup(board,dest_file,dest_rank)<0)
		{
			switch (piece_lookup(board,dest_file,dest_rank))
			{
			case -1:
				board.black_pawns ^= capture;
				break;
			case -2:
				board.black_rooks ^= capture;
				break;
			case -3:
				board.black_knights ^= capture;
				break;
			case -4:
				board.black_bishops ^= capture;
				break;
			case -5:
				board.black_queen ^= capture;
				break;
			case -6:
				cout<<"Cant capture oppn king";
				return;
				break;
			}
		}
		else if(piece_lookup(board,dest_file,dest_rank)>0)
		{
			cout<<"Own pieces present";
			return;
		}
		board.white_bishops = board.white_bishops ^ capture ^ piece;
	}
	else if(piece_lookup(board,file,rank)==-4)
	{
		cout<<"Black bishop";
		piece = 0x8000000000000000 >> (((8 - rank)) * 8 + (file-1));
		uint64_t capture = 0x8000000000000000 >> (((8 - dest_rank)) * 8 + (dest_file-1));
		if(piece_lookup(board,dest_file,dest_rank)>0)
		{
			switch (piece_lookup(board,dest_file,dest_rank))
			{
			case 1:
				board.white_pawns ^= capture;
				break;
			case 2:
				board.white_rooks ^= capture;
				break;
			case 3:
				board.white_knights ^= capture;
				break;
			case 4:
				board.white_bishops ^= capture;
				break;
			case 5:
				board.white_queen ^= capture;
				break;
			case 6:
				cout<<"Cant capture oppn king";
				return;
				break;
			}
		}
		else if(piece_lookup(board,dest_file,dest_rank)<0)
		{
			cout<<"Own pieces present";
			return;
		}
		board.black_bishops = board.black_bishops ^ capture ^ piece;

	}
	else
	{
		cout<<"no bishop present";
		return;
	}
}

void pawn_development(Bitboards &board,int file,int rank, int steps)
{
	uint64_t allbits=board.black_king | board.black_queen | board.black_rooks | board.black_bishops | board.black_knights | board.black_pawns|board.white_king | board.white_queen | board.white_rooks | board.white_bishops | board.white_knights | board.white_pawns;
	uint64_t pawn = 0x8000000000000000 >> (((8 - rank)) * 8 + (file-1));
	if ((pawn & board.white_pawns) != 0)
	{
		pawn = pawn<<8;
		if (steps == 2)
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
			enpassant = move_count + 1;
		}
		if ((pawn & allbits)!=0)
		{
			cout<<"square occupied";
			return;
		}
		uint64_t erase =  0x8000000000000000 >> (((8 - rank)) * 8 + ( file - 1));
		if(rank == 7)
		{	//promoting to a queen
			board.white_pawns = (board.white_pawns ^ erase);
			board.white_queen = board.white_queen ^ pawn;
			move_count++;

		}
		else
		{
			board.white_pawns = (board.white_pawns ^ erase) ^ pawn;
			move_count++;
		}
	}
	else if ((pawn & board.black_pawns) != 0)
	{
		pawn = pawn>>8;
		if (steps == 2)
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
			enpassant = move_count + 1;
		}
		if ((pawn & allbits)!=0)
		{
			cout<<"square occupied";
			return;
		}
		uint64_t erase =  0x8000000000000000 >> (((8 - rank)) * 8 + ( file - 1));
		if(rank == 2)
		{	//promoting to a queen
			board.black_pawns = (board.black_pawns ^ erase);
			board.black_queen = board.black_queen ^ pawn;
			move_count++;

		}
		else
		{
			board.black_pawns = (board.black_pawns ^ erase) ^ pawn;
			move_count++;
		}
	}
	else
	{
		cout<<"No Black or White pawn peice present";
		return;
	}
}

void pawn_capture(Bitboards &board,int file,int rank, int capture_file)
{
	uint64_t bits;
	uint64_t pawn = 0x8000000000000000 >> (((8 - rank)) * 8 + ( file - 1));
	uint64_t capture;
	if((pawn & board.white_pawns) != 0)
	{
		if(enpassant==move_count)
		{
			cout<<"enpassant";
			uint64_t erase = 0x8000000000000000 >> (((8 - rank)) * 8 + (capture_file-1));
			uint64_t pos = 0x8000000000000000 >> (((8 - rank - 1)) * 8 + (capture_file-1));
			bits=board.black_pawns;
			if((bits&capture)!=0)
			{
				board.black_pawns = board.black_pawns ^ erase;
				board.white_pawns = board.white_pawns ^ pawn ^ pos;
				move_count++;
				return;
			}
			else
			{
				cout<<"piece missing for enpassant";
			}
		}
		else
		{
			cout<<"Enpassant not valid"<<endl;
		}
		capture = 0x8000000000000000 >> (((8 - rank-1)) * 8 + (capture_file-1));
		bits = board.black_queen | board.black_rooks | board.black_bishops | board.black_knights | board.black_pawns;
		if((bits & capture)!= 0)
		{
			// removing the captured piece
			if((board.black_pawns & capture)!=0)
			{
				board.black_pawns = board.black_pawns ^ capture;
			}
			else if ((board.black_queen & capture)!=0)
			{
				board.black_queen = board.black_queen ^ capture;
			}
			else if ((board.black_rooks & capture)!=0)
			{
				board.black_rooks = board.black_rooks ^ capture;
			}
			else if ((board.black_bishops & capture)!=0)
			{
				board.black_bishops = board.black_bishops ^ capture;
			}
			else if ((board.black_knights & capture)!=0)
			{
				board.black_knights = board.black_knights ^ capture;
			}
			else {
				cout<<"invalid capture";
				return;
			}
			// upadting the pawn position
			if(rank == 7)
			{
				board.white_pawns = board.white_pawns ^ pawn;
				board.white_queen = board.white_queen ^ capture;
				move_count ++;
			}
			else
			{
				board.white_pawns = board.white_pawns ^ pawn ^ capture;
				move_count++;
			}
		}
		else
		{
			cout<<"no piece to capture";
		}
	}
	else if ((pawn & board.black_pawns) != 0)
	{
		if(enpassant==move_count)
		{
			cout<<"enpassant";
			uint64_t erase = 0x8000000000000000 >> (((8 - rank)) * 8 + (capture_file-1));
			uint64_t pos = 0x8000000000000000 >> (((8 - rank + 1)) * 8 + (capture_file-1));
			bits=board.white_pawns;
			if((bits&capture)!=0)
			{
				board.white_pawns = board.white_pawns ^ erase;
				board.black_pawns = board.black_pawns ^ pawn ^ pos;
				move_count++;
				return;
			}
			else
			{
				cout<<"piece missing for enpassant";
			}
		}
		else
		{
			cout<<"Enpassant not valid"<<endl;
		}

		capture = 0x8000000000000000 >> (((8 - rank+1)) * 8 + (capture_file-1));
		bits = board.white_queen | board.white_rooks | board.white_bishops | board.white_knights | board.white_pawns;
		if((bits & capture)!= 0)
		{
			if((board.white_pawns & capture)!=0)
			{
				board.white_pawns = board.white_pawns ^ capture;
			}
			else if ((board.white_queen & capture)!=0)
			{
				board.white_queen = board.white_queen ^ capture;
			}
			else if ((board.white_rooks & capture)!=0)
			{
				board.white_rooks = board.white_rooks ^ capture;
			}
			else if ((board.white_bishops & capture)!=0)
			{
				board.white_bishops = board.white_bishops ^ capture;
			}
			else if ((board.white_knights & capture)!=0)
			{
				board.white_knights = board.white_knights ^ capture;
			}
			else {
				cout<<"invalid capture";
				return;
			}
			if(rank == 2)
			{
				board.black_pawns = board.black_pawns ^ pawn;
				board.black_queen = board.black_queen ^ capture;
				move_count++;
			}
			else
			{
				board.black_pawns = board.black_pawns ^ pawn ^ capture;
				move_count++;
			}
		}
		else
		{
			cout<<"no piece to capture";
		}
	}
	else
	{
		cout<<"No pawn present";
		return;
	}


}

void print_board(const Bitboards &board) {
	cout << "  a b c d e f g h" << endl; // File labels
	for (int rank = 7; rank >= 0; --rank) {
		cout << (rank + 1) << " "; // Rank labels
		for (int file = 1; file <= 8; ++file) {
			uint64_t square = 0x8000000000000000 >> ((7-rank) * 8 + (file-1));
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



	};// initializing initial chess board



}