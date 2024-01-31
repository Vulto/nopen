#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>
#include <unistd.h>

#include "config.h"

#define BUFFER_SIZE 1024

void runApplication(const char *filename, const char *application) {
    execlp(application, application, filename, (char *)NULL);
    fprintf(stderr, "Could not find application %s", application);
    exit(EXIT_FAILURE);
}

const char *readFilenameFromStdin() {
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

const char *findApplicationForFileType(const char *mime_type) {
    const char *application = NULL;
    for (size_t i = 0; i < sizeof(fileTypes) / sizeof(FileTypeMapping); ++i) {
        if (strcmp(fileTypes[i].file_type, mime_type) == 0) {
            application = fileTypes[i].application;
            break;
        }
    }
    return application;
}

void handleNoPredefinedApplication(const char *mime_type) {
    fprintf(stderr, "No predefined application for file type %s\n", mime_type);
}

int main(int argc, char *argv[]) {
    const char *filename;

    if (argc == 2) {
        filename = argv[1];
    } else if (argc == 1) {
        filename = readFilenameFromStdin();
    } else {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
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

    const char *mime_type = getMimeType(filename, magic);
    const char *application = findApplicationForFileType(mime_type);

    if (application != NULL) {
        runApplication(filename, application);
    } else {
        handleNoPredefinedApplication(mime_type);
    }

    magic_close(magic);

    return EXIT_SUCCESS;
}
