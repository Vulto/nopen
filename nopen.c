#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>
#include <unistd.h>
#include <stdbool.h>

#include "config.h"

#define BUFFER_SIZE 128

    const char *filename;
    bool displayMimeType = false;

void Run(const char *filename, const char *prog) {
    execlp(prog, prog, filename, (char *)NULL);
    fprintf(stderr, "Could not find application %s", prog);
    exit(EXIT_FAILURE);
}

const char *readFromStdin() {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));

    if (bytesRead <= 0) {
        fprintf(stderr, "Error reading from stdin\n");
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';

    if (bytesRead > 0 && buffer[bytesRead - 1] == '\n') {
        buffer[bytesRead - 1] = '\0';
    }

    return strdup(buffer);
}

const char *getMimeType(const char *filename, magic_t magic) {
    const char *mime_type = magic_file(magic, filename);
    if (mime_type == NULL) {
        fprintf(stderr, "Cannot determine file type: %s\n", magic_error(magic));
        magic_close(magic);
        exit(EXIT_FAILURE);
    }
    return mime_type;
}

const char *findProg(const char *mime_type) {
    const char *prog = NULL;
    for (size_t i = 0; i < sizeof(fileTypes) / sizeof(FileTypeMapping); ++i) {
        if (strcmp(fileTypes[i].file_type, mime_type) == 0) {
            prog = fileTypes[i].application;
            break;
        }
    }
    return prog;
}

void handleNoProg(const char *mime_type) {
    fprintf(stderr, "No predefined application for file type %s\n", mime_type);
}

void printMimeType(const char *filename, magic_t magic) {
    const char *mime_type = getMimeType(filename, magic);
    printf("MIME type for %s: %s\n", filename, mime_type);
}

void printUsage(const char *programName) {
    fprintf(stderr, "Usage: %s [-d] [filename]\n", programName);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

    int opt;
    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
            case 'd':
                displayMimeType = true;
                break;
            default:
                printUsage(argv[0]);
        }
    }

    if (optind < argc) {
        filename = argv[optind];
    } else if (displayMimeType) {
        printUsage(argv[0]);
    } else {
        printUsage(argv[0]);
    }

    magic_t magic = magic_open(MAGIC_MIME_TYPE);
    if (magic == NULL) {
        fprintf(stderr, "Unable to initialize magic library\n");
        exit(EXIT_FAILURE);
    }

    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "Cannot load magic database: %s\n", magic_error(magic));
        magic_close(magic);
        exit(EXIT_FAILURE);
    }

    if (displayMimeType) {
        printMimeType(filename, magic);
    } else {
        const char *mime_type = getMimeType(filename, magic);
        const char *application = findProg(mime_type);

        if (application != NULL) {
            Run(filename, application);
        } else {
            handleNoProg(mime_type);
        }
    }

    magic_close(magic);

    return EXIT_SUCCESS;
}
