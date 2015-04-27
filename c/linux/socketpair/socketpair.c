/**
 * Socketpair demo
 *
 * This is a basic example of using a socketpair for in-memory async streams.
 * I created this to try it out for custom streams in libuv.
 */

/* Optional headers, not needed for real implementation. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Required for socketpair */
#include <sys/types.h>
#include <sys/socket.h>

const char* test_string = "This is a socketpair test string.";

int main(int argc, char* argv[]) {
    int r;
    int bytes_written;
    int bytes_read;
    int fd[2];
    char read_buf[1024];

    printf("# socketpair start.\n");

    printf("  Creating socket pair.\n");
    r = socketpair(AF_LOCAL, SOCK_STREAM | SOCK_NONBLOCK, 0, fd);
    if (r == -1) {
        perror("socketpair");
        exit(-1);
    }

    printf("  Writing to fd[0].\n");
    bytes_written = write(fd[0], test_string, strlen(test_string));
    if (bytes_written < 0) {
        perror("write");
        exit(-1);
    }
    printf("    wrote %d bytes: '%s'\n", bytes_written, test_string);

    printf("  Reading from fd[1].\n");
    memset(read_buf, 0, sizeof(read_buf));
    bytes_read = read(fd[1], read_buf, sizeof(read_buf));
    if (bytes_read < 0) {
        perror("read");
        exit(-1);
    }
    printf("    read %d bytes: '%s'\n", bytes_read, read_buf);

    printf("  Closing sockets.\n");
    close(fd[0]);
    close(fd[1]);

    printf("# socketpair end.\n");

    return 0;
}

