

bool Ches_Step (ChesCtx *ctx) {
	Move m;
	AlgoCtx    *actx = ctx->next_turn == PIECE_WHITE ? &ctx->white : &ctx->black;
	const char *name = ctx->next_turn == PIECE_WHITE ? "white"     : "black";
	
	if (ctx->next_turn == PIECE_BLACK) {
		// we need to flip the board along X, and also change PIECE_BLACK to PIECE_WHITE and vice versa
		for (short y = 8; y != 0; y --) {
			for (short x = 8; x != 8; x ++) {
				actx->board.p [LOCATION (x, 8 - y)] = ((ctx->board.p [LOCATION (x, y)] & PIECE_MASK_COLOR) == PIECE_BLACK) ?
					PIECE_WHITE | (ctx->board.p [LOCATION (x, y)] & PIECE_MASK_TYPE)
				:
					PIECE_BLACK | (ctx->board.p [LOCATION (x, y)] & PIECE_MASK_TYPE)
				;
			}
		}
	} else {
		actx->board = ctx->board; // we dont for white
	}
	
	m = (*actx->run) (actx);
	if (Algo_CheckMove (actx, m) == false) {
		fprintf (stderr, "%s (%s) returned bad move\n", name, actx->name);
		return 1;
	}
	
	if (++ ctx->history_len > ctx->history_alloc)
		ctx->history = realloc (sizeof (*ctx->history) * (ctx->history_alloc *= 2));
	ctx->history [ctx->history_len] = m;
	
	if (ctx->board [m.to] & PIECE_MASK_COLOR != PIECE_WHITE)
	
	return 0;
}

bool tramples (AlgoCtx *ctx, Move move) {
	int dx = LOCATION_X (move.to) - LOCATION_X (move.from);
	int dy = LOCATION_Y (move.to) - LOCATION_Y (move.from);
	
	int x = LOCATION_X (move.from);
	int y = LOCATION_Y (move.from);
	while (true) {
		x += dx; y += dy;
		if (LOCATION (x, y) == move.to)
			break;
		
		if (ctx->board [LOCATION (x, y)] != 0)
			return true;
	}
	return false;
}

size_t Algo_GetAllPieces (AlgoCtx *ctx, Location *places, Pieces *pieces, size_t max_locations) {
	size_t out = 0;
	
	for (int y = 0; y != 8; y ++) {
		for (int x = 0; x != 8; x ++) {
		
			if (ctx->board [LOCATION (x, y)] & PIECE_MASK_COLOR == PIECE_WHITE) {
				if (places != NULL)
					places [out] = LOCATION (x, y);
					
				if (pieces != NULL)
					pieces [out] = ctx->board [LOCATION (x, y)];
					
				if (++ out == max_locations)
					return out - 1;
			}
			
		}
	}
	
	return out - 1;
}

// we dont really optimize this because Algo_CheckMove () does everything now, so modifying a piece's code is easy

size_t Algo_GetMoves (AlgoCtx *ctx, Move *moves, size_t max_moves) {
	#define M(dx,dy) {\
		Move m;\
		m.from = places [i];\
		m.to = LOCATION (dx + LOCATION_X (places [i]), dy + LOCATION_Y (places [y]));\
		if (Algo_CheckMove (ctx, m)) {\
			moves [out ++] = m;\
			if (out == max_moves)\
				return out - 1;\
		}\
	}
	
	Pieces   pieces [8 * 8];
	Location places [8 * 8];
	
	size_t count = Algo_GetAllPieces (ctx, places, pieces, 8 * 8);
	for (size_t i = 0; i != count; i ++) {
		for (int y = 0; y != 8; y ++) {
			for (int x = 0; x != 8; x ++) {
			
			Move m;
			m.from = places [i];
			m.to = LOCATION (x, y);
			
			if (Algo_CheckMove (ctx, m)) {
				moves [out ++] = m;
				if (out == max_moves)
					return out - 1;
			}
		}
	}
	
	return out - 1;
	#undef M
}

bool Algo_CheckMove (AlgoCtx *ctx, Move move) {
	#define C(b) \
		if (!(b))\
			return false;
	C (move.to   & 077 == move.to);
	C (move.from & 077 == move.from);
	C (LOCATION_X (move.from) != LOCATION_X (move.to) || LOCATION_Y (move.from) != LOCATION_Y (move.to));
	C (ctx->board [move.from] & PIECE_MASK_COLOR == PIECE_WHITE);
	C (ctx->board [move.to]   & PIECE_MASK_COLOR == PIECE_BLACK || ctx->board [move.to] == 0);
	
	
	int dx = LOCATION_X (move.to) - LOCATION_X (move.from);
	int dy = LOCATION_Y (move.to) - LOCATION_Y (move.from);
	switch (ctx->board [move.from] & PIECE_MASK_TYPE) {
		case PIECE_PAWN:
			C (dy == 1);
			C (abs (dx) <= 1);
			
			C (ctx->board [move.to] == 0 && dx == 0);
			C (ctx->board [move.to] != 0 && dx != 0);
		break;
		
		case PIECE_ROOK:
			C (dx == 0 ^^ dy == 0);	
			C (! tramples (ctx, move));
		break;
		
		case PIECE_KNIGHT:
			C (
				(abs (dx) == 1 && abs (dy) == 3) ^^
				(abs (dx) == 3 && abs (dy) == 1)
			);
		break;
		
		case PIECE_BISHOP:
			C (abs (dx) == abs (dy));
			C (! tramples (ctx, move));
		break;
		
		case PIECE_KING:
			C (abs (dx) == 1 || abs (dy) == 1);
		break;
		
		case PIECE_QUEEN:
			C (
				abs (dx) == abs (dy) ||
				abs (dx) == 0 ||
				abs (dy) == 0
			);
			C (! tramples (ctx, move));
		break;
		
		default:
			return false;
	}
	#undef C
}
