#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFFER_SIZE 128

static const char *filename;
static bool displayMimeType = false;

void Run(const char *filename, const char *prog) {
    execlp(prog, prog, filename, NULL);
    fprintf(stderr, "Could not find application %s\n", prog);
    exit(EXIT_FAILURE);
}

const char *readFromStdin(void) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    
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
    if (!mime_type) {
        fprintf(stderr, "Cannot determine file type: %s\n", magic_error(magic));
        magic_close(magic);
        exit(EXIT_FAILURE);
    }
    return mime_type;
}

typedef struct {
    const char *file_type;
    const char *application;
} FileTypeMapping;

const char *findProg(const char *mime_type) {
    const char *editor = getenv("NOPEN_EDITOR") ?: "nvim";
    const char *imgv = getenv("NOPEN_IMGV") ?: "nsxiv";
    const char *player = getenv("NOPEN_PLAYER") ?: "mpv";
    const char *pdf = getenv("NOPEN_PDF") ?: "zathura";
    const char *browser = getenv("NOPEN_BROWSER") ?: "surf";
    const char *filemgr = getenv("NOPEN_FILEMGR") ?: "spf";
    const char *audio = getenv("NOPEN_AUDIO") ?: "mpg123";
    const char *wine = getenv("NOPEN_WINE") ?: "wine";
    const char *bash = getenv("NOPEN_BASH") ?: "bash";

    const FileTypeMapping fileTypes[] = {
        {"text/plain", editor},
        {"text/x-c", editor},
        {"text/csv", editor},
        {"text/x-makefile", editor},
        {"text/x-shellscript", editor},
        {"text/x-tex", editor},
        {"text/html", editor},
        {"x-www-browser", browser},
        {"application/json", editor},
        {"inode/x-empty", editor},
        {"application/octet-stream", editor},
        {"application/vnd.microsoft.portable-executable", wine},
        {"application/javascript", editor},
        {"inode/directory", filemgr},
        {"video/mp4", player},
        {"video/webm", player},
        {"image/png", imgv},
        {"image/jpg", imgv},
        {"image/jpeg", imgv},
        {"image/gif", imgv},
        {"audio/x-wav", audio},
        {"audio/mpeg", audio},
        {"application/pdf", pdf},
        {"application/x-executable", bash},
        {"application/x-pie-executable", bash},
    };

    for (size_t i = 0; i < sizeof(fileTypes) / sizeof(fileTypes[0]); ++i) {
        if (strcmp(fileTypes[i].file_type, mime_type) == 0) {
            return fileTypes[i].application;
        }
    }
    return NULL;
}

void handleNoProg(const char *mime_type) {
    fprintf(stderr, "No predefined application for file type %s\n", mime_type);
    exit(EXIT_FAILURE);
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
    } else if (!displayMimeType && isatty(STDIN_FILENO)) {
        printUsage(argv[0]);
    } else {
        filename = readFromStdin();
    }

    magic_t magic = magic_open(MAGIC_MIME_TYPE);
    if (!magic) {
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
        if (application) {
            Run(filename, application);
        } else {
            handleNoProg(mime_type);
        }
    }

    magic_close(magic);
    return EXIT_SUCCESS;
}
