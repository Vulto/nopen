# NOPEN
MimeLauncher, also known as nopen, is a minimalistic utility designed to launch files based on their MIME types. The program utilizes the magic library to identify the MIME type of a given file and then matches it with a predefined application in a user-customizable configuration file.

## Requirements
C compiler
magic library

## Installation

git clone https://github.com/your-username/nopen.git
cd nopen

./c will build the executable
./c install (requires adjustment from doas to sudo)

## Usage
Execute nopen by providing the filename as a command-line argument

./nopen <filename>
If a predefined application is available for the file type, nopen will launch it.

## Configuration
Customize the config.h file to define file type mappings. Add entries for MIME types and their associated applications:
// config.h

typedef struct {
    const char *file_type;
    const char *application;
} FileTypeMapping;

const FileTypeMapping fileTypes[] = {
    { "application/pdf", "evince" },
    // Add more mappings as needed
};

### Contributing
Contribute to nopen by opening issues or submitting pull requests. Your feedback and enhancements are highly appreciated!

#### License
This project is licensed under the MIT License - see the LICENSE file for details.
