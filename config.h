typedef struct {
    const char *file_type;
    const char *application;
} FileTypeMapping;

const FileTypeMapping fileTypes[] = {
    {"text/plain", "nvim"},
    {"text/x-c", "nvim"},
    {"text/csv", "nvim"},
    {"text/x-makefile", "nvim"},
    {"text/x-shellscript", "bash"},
    {"text/x-tex", "nvim"},

    {"text/html", "nvim"},

    {"x-www-browser", "qutebrowser"},

    {"application/json", "nvim"},
    {"inode/x-empty", "nvim"},
    {"application/octet-stream", "nvim"},
    
    {"application/vnd.microsoft.portable-executable", "wine"},
    {"application/javascript", "nvim"},

    {"inode/directory", "cfl"},

    {"video/mp4", "mpv"},
    {"video/webm", "mpv"},

    {"image/png", "sxiv"},
    {"image/jpg", "sxiv"},
    {"image/jpeg", "sxiv"},
    {"image/gif", "sxiv"},

    {"audio/x-wav", "mpg123"},
    {"audio/mpeg", "mpg123"},

    {"application/x-nes-rom", "mednafen"},
    {"application/pdf", "zathura"},
    {"application/x-n64-rom", "mupen64plus"},
    {"application/x-executable", "launcher.sh"},
    {"application/zip", "mame"},

    {"application/x-pie-executable", "launcher.sh"},
};
