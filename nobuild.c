#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define SOURCE "nopen.c"
#define BIN "nopen"
#define CC "gcc"
#define LIB "-lmagic" 
#define DESTDIR "/usr/local/bin/"

int posix_main(int argc, char *argv[]){
    if (argc == 1){
    	CMD(CC, "-o", BIN, SOURCE, LIB, NULL);
		return EXIT_SUCCESS;
	}

    if (argc > 1){
        if (strcmp(argv[1], "install") == 0){
    		CMD(CC, "-o", BIN, SOURCE, LIB, NULL);
			CMD("doas", "cp", BIN, DESTDIR BIN);
        }else if (strcmp(argv[1], "remove") == 0){
			CMD("doas", "rm", "-vi", DESTDIR"/"BIN);
        }else if (strcmp(argv[1], "clean") == 0){
			CMD("rm -vi", BIN);
        }else{
            PANIC("%s is unknown subcommand", argv[1]);
        }
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    GO_REBUILD_URSELF(argc, argv);

	posix_main(argc, argv);

    return EXIT_SUCCESS;
}

