#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define SOURCE "nopen.c"
#define BIN "nopen"
#define CC "gcc"
#define LIB "-lmagic"
#define PREFIX "/usr/local/bin/"
#define OLD "c.old"
#define OBJ BIN

void Compile(void) {
    CMD(CC, "-c", LIB, SOURCE);
}

void Link(void) {
    CMD(CC, "-o", BIN, "nopen.o", LIB, NULL);
}

void Install(void) {
    CMD("doas", "cp", "-f", BIN, PREFIX);
}

void Wipe(void) {
    CMD("doas", "rm", "-v", PREFIX""BIN);
    CMD("rm", BIN, "c.old");
}

int main(int argc, char *argv[]) {
    GO_REBUILD_URSELF(argc, argv);

    if (argc < 2) {
        printf("Usage: %s [-c compile] [-l link] [-i install] [-w wipe]\n", argv[0]);
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];

        if (arg[0] == '-') {
            for (unsigned long int j = 1; j < strlen(arg); j++) {

                switch (arg[j]) {
                    case 'c': Compile();  break;
                    case 'l': Link();     break;
                    case 'i': Install();	break;
                    case 'w': Wipe();     break;
                    default: printf("Unknown option: %c\n", arg[j]);
                        break;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
