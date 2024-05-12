#include "../raylib/include/raylib.h"
#include "game.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void *game_dl = NULL;
void load_symbols() {
  if (game_dl != NULL) {
    dlclose(game_dl);
  }
  game_dl = dlopen("./build/libgame.so", RTLD_NOW);
  if (game_dl == NULL) {
    fprintf(stderr, "[err] %s\n", dlerror());
  }
  game_init = dlsym(game_dl, "game_init");
  if (game_init == NULL) {
    fprintf(stderr, "[err] %s\n", dlerror());
    exit(-1);
  }
  game_update = dlsym(game_dl, "game_update");
  if (game_update == NULL) {
    fprintf(stderr, "[err] %s\n", dlerror());
    exit(-1);
  }
  game_pre_reload = dlsym(game_dl, "game_pre_reload");
  if (game_pre_reload == NULL) {
    fprintf(stderr, "[err] %s\n", dlerror());
    exit(-1);
  }
  game_post_reload = dlsym(game_dl, "game_post_reload");
  if (game_post_reload == NULL) {
    fprintf(stderr, "[err] %s\n", dlerror());
    exit(-1);
  }
}

int main(void) {
  load_symbols();

  InitWindow(100, 100, "game");
  SetTargetFPS(60);
  game_init();
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_R)) {
      void *state = game_pre_reload();
      load_symbols();
      game_post_reload(state);
    }
    game_update();
  }
  return 0;
}
