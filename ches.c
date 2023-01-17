void Ches_Step (ChesCtx *ctx) {
	
}

bool Algo_CheckMove (AlgoCtx *ctx, Move move) {
	if (ctx->board [move.from] & PIECE_MASK_COLOR != ctx->color)
		return false;
	
	if (ctx->board [move.to] & PIECE_MASK_COLOR == ctx->color)
		return false;
	
	switch (ctx->board [move.from] & PIECE_MASK_TYPE) {
		case PIECE_PAWN:
			if (ctx->board [move.to] == 0) {
				if (LOCATION_X (piece))
			}
	}
}
