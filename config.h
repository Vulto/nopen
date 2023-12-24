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
	{"inode/directory", "cd"},
	{"application/octet-stream", "mednafen"},
	{"application/pdf", "zathura"},
};
