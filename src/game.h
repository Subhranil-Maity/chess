#include <stdio.h>
#ifndef GAME_H_
#define GAME_H_

void (*game_init)(void) = NULL;
void *(*game_pre_reload)(void) = NULL;
void (*post_post_reload)(void *) = NULL;
void (*game_update)(void) = NULL;

#endif // GAME_H_
