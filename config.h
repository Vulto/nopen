typedef struct {
    const char *file_type;
    const char *application;
} FileTypeMapping;

const FileTypeMapping fileTypes[] = {
    {"text/plain", "nvim"},
    {"text/x-c", "nvim"},
    {"text/html", "nvim"},
    {"inode/x-empty", "nvim"},
    {"text/x-makefile", "nvim"},
    {"text/x-shellscript", "nvim"},
    {"application/javascript", "nvim"},
    {"text/x-tex", "nvim"},
    {"inode/directory", "cd"},
    {"application/octet-stream", "mednafen"},
    {"application/pdf", "mupdf"},
    {"application/x-n64-rom", "mupen64plus"},
    {"image/png", "sxiv"},
    {"image/jpg", "sxiv"},
    {"image/jpeg", "sxiv"},
    {"image/gif", "sxiv"},
    {"application/x-pie-executable", "bash"},
    {"audio/x-wav", "mpv"},
    {"application/octet-stream", "mednafen"},
    {"x-www-browser", "qutebrowser"},
    {"text/csv", "qutebrowser"},
    {"video/mp4", "mpv"}
};
