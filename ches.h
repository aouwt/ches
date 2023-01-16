#ifndef CHES_H
	#define CHES_H
	
	#define PIECE_MASK_TYPE  0x0F
	#define PIECE_MASK_COLOR 0xF0
	
	#define PIECE_PAWN   0x01
	#define PIECE_ROOK   0x02
	#define PIECE_KNIGHT 0x03
	#define PIECE_BISHOP 0x04
	#define PIECE_KING   0x05
	#define PIECE_QUEEN  0x06
	
	#define PIECE_WHITE  0x10
	#define PIECE_BLACK  0x20
	
	#define PIECE_WHITE_PAWN   (PIECE_WHITE | PIECE_PAWN)
	#define PIECE_WHITE_ROOK   (PIECE_WHITE | PIECE_ROOK)
	#define PIECE_WHITE_KNIGHT (PIECE_WHITE | PIECE_KNIGHT)
	#define PIECE_WHITE_BISHOP (PIECE_WHITE | PIECE_BISHOP)
	#define PIECE_WHITE_KING   (PIECE_WHITE | PIECE_KING)
	#define PIECE_WHITE_QUEEN  (PIECE_WHITE | PIECE_QUEEN)
	
	#define PIECE_BLACK_PAWN   (PIECE_BLACK | PIECE_PAWN)
	#define PIECE_BLACK_ROOK   (PIECE_BLACK | PIECE_ROOK)
	#define PIECE_BLACK_KNIGHT (PIECE_BLACK | PIECE_KNIGHT)
	#define PIECE_BLACK_BISHOP (PIECE_BLACK | PIECE_BISHOP)
	#define PIECE_BLACK_KING   (PIECE_BLACK | PIECE_KING)
	#define PIECE_BLACK_QUEEN  (PIECE_BLACK | PIECE_QUEEN)
	
	
	typedef unsigned short Piece;
	typedef Move (*AlgoFunc) (AlgoCtx *ctx, )
	
	struct _Board {
		Piece p [8] [8];
	};
	
	struct _AlgoCtx {
		Board b;
		
	};
	
	
	void NewBoard ()
#endif
