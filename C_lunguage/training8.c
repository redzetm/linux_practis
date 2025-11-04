#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024  
#define TAIL_LINES 10

void print_tail(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        close(fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    off_t pos = file_size;
    int newline_count = 0;
    ssize_t bytes_read;
    size_t total_read = 0;

    // スキャンして末尾から改行を数える
    //while文全体読まないとnewline_countが\nの改行コード数えてるってわからないね
    while (pos > 0 && newline_count <= TAIL_LINES) {
        size_t to_read = (pos >= BUFFER_SIZE) ? BUFFER_SIZE : pos;
        pos -= to_read;
        lseek(fd, pos, SEEK_SET);
        bytes_read = read(fd, buffer, to_read);
        if (bytes_read <= 0) break;

        for (ssize_t i = bytes_read - 1; i >= 0; i--) {
            if (buffer[i] == '\n') {
                newline_count++;
                if (newline_count > TAIL_LINES) {
                    pos += i + 1;
                    goto found;
                }
            }
        }
    }

found:
    lseek(fd, pos, SEEK_SET);
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    print_tail(argv[1]);
    return 0;
}