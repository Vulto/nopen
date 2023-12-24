#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define SOURCE "nopen.c"
#define BIN "nopen"
#define CC "gcc"
#define LIB "-lmagic"
#define DESTDIR "/usr/local/bin/"

int main(int argc, char *argv[]) {
	GO_REBUILD_URSELF(argc, argv);

	if (argc < 2) {
		CMD(CC, "-o", BIN, SOURCE, LIB, NULL);
		return EXIT_SUCCESS;
	}

	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];

		if (arg[0] == '-') {
			for (int j = 1; j < strlen(arg); j++) {

				switch (arg[j]) {
					case 'i':
						CMD("doas", "cp", "-f", BIN, DESTDIR);
						break;
					case 'r':
						CMD("doas", "rm", "-v", DESTDIR""BIN);
						break;
					case 'c':
						CMD("rm -v", BIN);
						break;
					default:
						PANIC("%s is unknown subcommand", arg);
						break;
				}
			}
		} else {
			printf("Usage: %s [-i] [-r] [-c]\n", argv[0]);
		}
	}

	return EXIT_SUCCESS;
}
