 struct rule rules[] = {
 	{ .regex = "\\.(avi|mp4|mkv|mp3|ogg|flac|mov)$", .file = "mpv", .argv = { "mpv", "{}", NULL } },
 	{ .regex = "\\.(cue|nes|smc|fig|sfc)$", .file = "mednafen", .argv = { "mednafen", "{}", NULL } },
 	{ .regex = "\\.(z64|n64)$", .file = "mupen64plus", .argv = { "mupen64plus", "{}", NULL } },
 	{ .regex = "\\.(png|jpg|gif|webp|jpeg|img|)$", .file = "sxiv", .argv = { "sxiv", "{}", NULL} },
 	{ .regex = "\\.(html|svg)$", .file = "qutebrowser", .argv = { "qutebrowser", "{}", NULL } },
 	{ .regex = "\\.pdf$", .file = "mupdf", .argv = { "mupdf", "{}", NULL} },
 	{ .regex = "\\.zip$", .file = "mame", .argv = { "mame", "{}", NULL} },
 	{ .regex = "\\.sh$", .file = "sh", .argv = { "sh", "{}", NULL} },
 	{ .regex = ".", .file = "nvim", .argv = { "nvim", "{}", NULL } },
 };
