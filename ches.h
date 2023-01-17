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
	
	
	#define LOCATION_MASK_X 070
	#define LOCATION_MASK_Y 007
	
	#define LOCATION_X(l) (((l) & LOCATION_MASK_X) >> 3)
	#define LOCATION_Y(l) ((l) & LOCATION_MASK_Y)
	
	#define LOCATION(x,y) ((((x) & 007) << 3) | ((y) & 007))
	
	typedef unsigned short Piece;
	typedef short          Location;
	
	typedef bool (*AlgoInitFunc) (AlgoCtx *ctx);
	typedef Move (*AlgoFunc)     (AlgoCtx *ctx);
	
	struct _Move {
		Location from, to;
	};
	
	struct _Board {
		Piece p [8 * 8];
	};
	
	struct _AlgoCtx {
		AlgoInitFunc deinit;
		AlgoFunc     run;
		const char  *name;
		
		Board        board;
		void        *dat;
		ChesCtx     *ctx;
	};
	
	struct _ChesCtx {
		Board   board;
		
		Move   *history;
		size_t  history_len;
		size_t  history_alloc;
		
		AlgoCtx black;
		AlgoCtx white;
		
		Piece   next_turn;
	};
	
	
	void   Ches_New  (ChesCtx *ctx);
	void   Ches_Step (ChesCtx *ctx);
	
	bool   Algo_CheckMove (AlgoCtx *ctx, Move move);
	size_t Algo_GetMoves  (AlgoCtx *ctx, Move *moves, size_t max_moves);
	size_t Algo_GetMovesM (AlgoCtx *ctx, Move *moves);
	void   Algo_Log       (AlgoCtx *ctx, const char *str);
	void   Algo_LogF      (AlgoCtx *ctx, const char *fmt, ...);
#endif
