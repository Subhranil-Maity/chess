#include "../raylib/include/raylib.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	Color background;
} Game ;
static Game *game;
void game_init(void){
	game = malloc(sizeof(*game));
	if(game == NULL){
		fprintf(stderr, "[err] failed to malloc GAME; Fix Buy More Ram");
		exit(-1);
	}
	game->background = RED;
}
void *game_pre_reload(void){
return game;	
}
void post_post_reload(void * state){
	game = state;
}
void game_update(void){
    BeginDrawing();
    ClearBackground(game->background);
    EndDrawing();
}
