# clipboard-logger
A simple command line program that just automatically appends new clipboard to a text file.

This program is built using cmake 
CMAKE uses microsoft [vcpkg](https://github.com/microsoft/vcpkg) as the buildchain tool.
##installation
if you want you can run the setup.bat to get vcpkg installed cloned automatically
otherwise ensure that sdl3 is installed and setup the build tools include that library
## Usage
Run the program in terminal
-  given no other command arguments it will output to the relative path as "clipboard.log"
-  Exit Process with Escape key on terminal/command line
## options
-  -n | --no-terminal
-  -h | --no-headers

