#include "raylib/include/raylib.h"
#include <stdio.h>
#include <stdlib.h>

const char *c_args = " -Wall -Wextra -Werror -Wpedantic";
#define debug " -g"

void backup_self() {
	if(system("mv ./make ./make.old") != 0){
		fprintf(stderr, "[err] failed to backup self\n");
		exit(-1);
	}	
}
void restore_self(){
	if(system("mv ./make.old ./make") != 0){
		fprintf(stderr, "[err] failed to restore self\n");
		exit(-1);
	}	
}
void go_rebuild_your_self() {
  const char *command =
      TextFormat("gcc make.c %s -o make -lm -l:libraylib.a -L./raylib/lib/",
                 c_args);
  printf("%s\n", command);
  if (system(command) != 0) {
    fprintf(stderr, "[log] failed to build self\n");
		printf("[log] going back to privious version\n");
		restore_self();
    exit(-1);
  }
  printf("[log] successfully rebuilt self\n");
}
int build_game_as_seperate_shared_library(){
	const char *command = TextFormat("gcc ./src/game.c -o ./build/libgame.so -shared -fPIC %s %s -Wl,-rpath=./raylib/lib  -l:libraylib.so -L./raylib/lib/ -lm", c_args, debug);
	printf("%s", command);
	return system(command);
}
int build_main() { 
	// TODO link with raylib
	const char *command = TextFormat("gcc ./src/main.c -o ./build/main.out %s %s -Wl,-rpath=./raylib/lib  -l:libraylib.so -L./raylib/lib/ -lm", c_args, debug);
	printf("%s", command);
	return system(command);
}

int main(int argc, char *argv[]) {
	(void) argv;
  if (argc == 1) {
		backup_self();
    go_rebuild_your_self();
    if (system("./make build") != 0) {
      fprintf(stderr, "[err] failed to run new self\n");
      return -1;
    }
		return 0;
  }
	printf("\n=========================================\n");
	if(build_main() != 0){
		fprintf(stderr, "failed to build main\n");
		return -1;
	}
	if(build_game_as_seperate_shared_library() != 0){
		fprintf(stderr, "failed to build game.so\n");
		return -1;
	}
	printf("\n=========================================\n");
  return 0;
}
