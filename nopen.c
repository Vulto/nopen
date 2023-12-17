#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>
#include <unistd.h>

#include "config.h"

//TODO: ask for a program to bind to this mimetype
//		write in the config.h array.

void Run(const char *filename, const char *application) {
    execlp(application, application, filename, (char *)NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

	const char *filename = argv[1];
		
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    // Create magic library handle
    magic_t magic = magic_open(MAGIC_MIME_TYPE);
    if (magic == NULL) {
        fprintf(stderr, "Unable to initialize magic library\n");
        exit(EXIT_FAILURE);
    }

    // Load the default magic database
    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "Cannot load magic database: %s\n", magic_error(magic));
        magic_close(magic);
        exit(EXIT_FAILURE);
    }

    // Get the MIME type of the file
    const char *mime_type = magic_file(magic, filename);
    if (mime_type == NULL) {
        fprintf(stderr, "Cannot determine file type: %s\n", magic_error(magic));
        magic_close(magic);
        exit(EXIT_FAILURE);
    }

    // Find the associated application in the mapping
    const char *application = NULL;
    for (size_t i = 0; i < sizeof(fileTypes) / sizeof(FileTypeMapping); ++i) {
        if (strcmp(fileTypes[i].file_type, mime_type) == 0) {
            application = fileTypes[i].application;
            break;
        }
    }

    if (application != NULL) {
        Run(filename, application);
    } else {
        fprintf(stderr, "No predefined application for file type %s\n", mime_type);
    }

    magic_close(magic);

    return EXIT_SUCCESS;
}
