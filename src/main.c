#include "../raylib/include/raylib.h"
#include "game.h"
#include <stdio.h>
#include <dlfcn.h>

int main(void){
	void *game_dl = dlopen("./build/libgame.so", RTLD_NOW);
	if (game_dl == NULL) {
		fprintf(stderr, "[err] %s\n", dlerror());
	}

	game_init();

  return 0;
}
