#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define SOURCE "nopen.c"
#define BIN "nopen"
#define CC "gcc"
#define LIB "-lmagic"
#define PREFIX "/usr/local/bin/"
#define OLD "c.old"

void BuildObj(void) {
	CMD(CC, "-c", LIB, SOURCE);
}

void BuildBin(void) {
	CMD(CC, "-o", BIN, SOURCE, LIB, NULL);
}

void Install(void) {
	CMD("doas", "cp", "-f", BIN, PREFIX);
}

void Remove(void) {
	CMD("doas", "rm", "-v", PREFIX""BIN);
}

void Clean(void) {
	CMD("rm", BIN, "c.old");
}

int main(int argc, char *argv[]) {
	GO_REBUILD_URSELF(argc, argv);

	if (argc < 2) {
		printf("Usage: %s [-i install] [-r remove] [-c clean]\n", argv[0]);
	return EXIT_SUCCESS;
	}

	for (int i = 1; i < argc; i++) {
		char *arg = argv[i];

		if (arg[0] == '-') {
			for (unsigned long int j = 1; j < strlen(arg); j++) {

				switch (arg[j]) {
					case 'r': Remove(); 	break;
					case 'i': Install();	break;
					case 'c': Clean();		break;
					case 'b': BuildBin();	break;
					case 'o': BuildObj();	break;
					default: printf("Unknown option: %c\n", arg[j]);
					break;
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
