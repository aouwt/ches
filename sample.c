#include "ches.h"

#include <math.h>

bool random (AlgoCtx *ctx) {
	ctx->deinit = NULL;
}

Move run_random (AlgoCtx *ctx) {
	Move *moves;
	size_t cnt = Algo_GetMovesM (ctx, moves);
	
	if (cnt > RAND_MAX)
		Algo_LogF (ctx, "cnt > RAND_MAX (%z > %z)", cnt, RAND_MAX);
	
	Move choice = moves [rand () % cnt];
	free (moves);
	return choice;
}
