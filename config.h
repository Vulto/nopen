#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <magic.h>
#include <unistd.h>
#include <getopt.h>     // For getopt(3) and optind
#include <stdbool.h>
#include <ctype.h>

const char *findProg(const char *mime_type) {
    char mime_lower[256];
    strncpy(mime_lower, mime_type, sizeof(mime_lower) - 1);
    mime_lower[sizeof(mime_lower) - 1] = '\0';
    for (char *p = mime_lower; *p; p++)
        *p = (char)tolower((unsigned char)*p);

    const char *editor = getenv("NOPEN_EDITOR");
    if (!editor) editor = "nvim";

    const char *imgv = getenv("NOPEN_IMGV");
    if (!imgv) imgv = "nsxiv";

    const char *player = getenv("NOPEN_PLAYER");
    if (!player) player = "mpv";

    const char *pdf = getenv("NOPEN_PDF");
    if (!pdf) pdf = "zathura";

    const char *browser = getenv("NOPEN_BROWSER");
    if (!browser) browser = "surf";

    const char *filemgr = getenv("NOPEN_FILEMGR");
    if (!filemgr) filemgr = "spf";

    const char *audio = getenv("NOPEN_AUDIO");
    if (!audio) audio = "mpg123";

    const char *wine = getenv("NOPEN_WINE");
    if (!wine) wine = "wine";

    const char *bash = getenv("NOPEN_BASH");
    if (!bash) bash = "bash";

    const struct {
        const char *file_type;
        const char *application;
    } fileTypes[] = {
        {"text/plain",                      editor},
        {"text/x-c",                        editor},
        {"text/csv",                        editor},
        {"text/x-makefile",                 editor},
        {"text/x-shellscript",              bash},
        {"text/x-tex",                      editor},
        {"text/html",                       editor},
        {"x-www-browser",                   browser},
        {"application/json",                editor},
        {"inode/x-empty",                   editor},
        {"application/octet-stream",        editor},
        {"application/vnd.microsoft.portable-executable", wine},
        {"application/javascript",          editor},
        {"inode/directory",                 filemgr},
        {"video/mp4",                       player},
        {"video/webm",                      player},
        {"image/png",                       imgv},
        {"image/jpg",                       imgv},
        {"image/jpeg",                      imgv},
        {"image/gif",                       imgv},
        {"audio/x-wav",                     audio},
        {"audio/mpeg",                      audio},
        {"application/pdf",                 pdf},
    };

    for (size_t i = 0; i < sizeof(fileTypes) / sizeof(fileTypes[0]); ++i) {
        if (strcmp(fileTypes[i].file_type, mime_lower) == 0) {
            return fileTypes[i].application;
        }
    }

    return editor;  // fallback
}
