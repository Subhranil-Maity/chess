#include "../raylib/include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define memzero(ptr, size) memset(ptr, 0, size)
typedef struct {
  Color background;
} Game;
static Game *game;

void game_update(void) {
	BeginDrawing();
  ClearBackground(RED);
	EndDrawing();
}
void game_init(void) {
  game = malloc(sizeof(*game));
  memzero(game, sizeof(*game));

  if (game == NULL) {
    fprintf(stderr, "[err] failed to malloc GAME; Fix Buy More Ram");
    exit(-1);
  }
  game->background = GREEN;
}
void *game_pre_reload(void) { return game; }
void game_post_reload(void *state) { game = state; }
