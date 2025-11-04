#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAIL_LINES 10
#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char *lines[TAIL_LINES];
    int count = 0;
    char buffer[MAX_LINE];

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (count == TAIL_LINES) {
            free(lines[0]);
            memmove(lines, lines + 1, (TAIL_LINES - 1) * sizeof(char *));
            count--;
        }
        lines[count++] = strdup(buffer);
    }

    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    fclose(fp);
    return 0;
}