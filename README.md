MimeLauncher (nopen)
MimeLauncher, also known as nopen, is a minimalistic utility designed to launch files based on their MIME types. The program utilizes the magic library to identify the MIME type of a given file and then matches it with a predefined application in a user-customizable configuration file.

Prerequisites
C compiler (preferably clang)
magic library
config.h file for defining custom file type mappings
efibootmgr for EFI boot on Gentoo Linux
Installation
Clone the repository and build the nopen executable:

sh
Copy code
git clone https://github.com/your-username/nopen.git
cd nopen
make
Usage
Execute nopen by providing the filename as a command-line argument:

sh
Copy code
./nopen <filename>
If a predefined application is available for the file type, nopen will launch it.

Configuration
Customize the config.h file to define file type mappings. Add entries for MIME types and their associated applications:

c
Copy code
// config.h

typedef struct {
    const char *file_type;
    const char *application;
} FileTypeMapping;

const FileTypeMapping fileTypes[] = {
    { "application/pdf", "evince" },
    // Add more mappings as needed
};
Contributing
Contribute to nopen by opening issues or submitting pull requests. Your feedback and enhancements are highly appreciated!

License
This project is licensed under the MIT License - see the LICENSE file for details.
