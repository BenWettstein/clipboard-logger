#define _CRT_SECURE_NO_WARNINGS //stupid warnings are annoying, just let me be unsafe with fopen()
//standard
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
//platform specific
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define PATH_MAX MAX_PATH
#else
#include <termios.h>
#include <unistd.h>
#include <limits.h>
#endif
//SDL
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_clipboard.h>

int main(int argc, char* argv[]) {
    static char OUTPUT_PATH[PATH_MAX] = { 0 };
    bool term_log = true;
    bool display_info = true;
    FILE* fout = NULL;

    // Argument parsing
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--no-terminal") == 0) {
            term_log = false;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--no-headers") == 0) {
            display_info = false;
        } else if (argv[i][0] != '-' && argv[i][0] != '\0') {
            // Use snprintf for safe string copy
            snprintf(OUTPUT_PATH, sizeof(OUTPUT_PATH), "%s", argv[i]);
        }
    }

#ifdef _WIN32
    if (OUTPUT_PATH[0] == '\0') {
        snprintf(OUTPUT_PATH, sizeof(OUTPUT_PATH), "clipboard.log");
    }
#else
    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    if (OUTPUT_PATH[0] == '\0') {
        snprintf(OUTPUT_PATH, sizeof(OUTPUT_PATH), "./clipboard.log");
    }
#endif
    if (OUTPUT_PATH[0] != '\0') fout = fopen(OUTPUT_PATH, "a+");
    if (!fout) {
        printf("Failed to open: %s to append\n", OUTPUT_PATH);
        exit(1);
    }
#ifdef DEBUG
    SDL_SetAppMetadata("Clipboard Logger", "Debug:1.0.0", "clipboard-logging-tool");
#else
    SDL_SetAppMetadata("Clipboard Logger", "Release:1.0.0", "clipboard-logging-tool");
#endif // DEBUG
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }
    char* clipboard = SDL_GetClipboardText();
    bool AppContinue = true;
    if (display_info) printf("Press esc to close the logging.\n");
    while (AppContinue) {
        int ch = 0;
#ifdef _WIN32
        if (_kbhit()) {
            ch = _getch();
        }
#else
        ch = getchar();
#endif
        if (ch == 27) { // ESC
            if (display_info) printf("quitting\n");
            break;
        }
        char* newClipboard = SDL_GetClipboardText();
        if (strcmp(clipboard, newClipboard) != 0) {
            if (term_log) printf("%s\n", newClipboard);
            if (fout != NULL) fprintf(fout, "%s\n", newClipboard);
            SDL_free(clipboard);
            clipboard = newClipboard;
        }
        SDL_Delay(1);
    }
    SDL_Quit();
    if (fout != NULL) {
        fclose(fout);
        fout = NULL;
    }
    return 0;
}