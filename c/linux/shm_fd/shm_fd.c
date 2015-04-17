/**
 * SHM FD Demo
 *
 * This is a demo of getting a file descriptor to a shm region in linux.
 * I created this to try it out for custom streams in libuv.
 */

/* Optional headers, not needed for real implementation. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Required for using shm */
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const char* shm_name = "/shm_buf";
const off_t shm_size = 2048;
const char* test_string = "This is my test data, it's not much but it will do.";

int main(int argc, char* argv[]) {
    int fd_write;
    int fd_read;
    int bytes_written;
    int bytes_read;
    off_t seek_offset;
    char write_buf[shm_size];
    char read_buf[shm_size];

    printf("# shm start.\n");

    printf("  Creating shm: %s\n", shm_name);
    fd_write = shm_open(shm_name, O_RDWR | O_CREAT | O_EXCL, S_IRWXU);
    if (fd_write <= 0) {
        perror("Error on shm_open");
        exit(-1);
    }

    printf("  Setting size to %ld\n", (unsigned long)shm_size);
    if (ftruncate(fd_write, shm_size) != 0) {
        perror("Error on ftruncate");
        exit(-1);
    }

    printf("  Writing %ld bytes.\n", sizeof(write_buf));
    memset(write_buf, 0, sizeof(write_buf));
    strcpy(write_buf, test_string);
    bytes_written = write(fd_write, write_buf, sizeof(write_buf));
    if (bytes_written < 0) {
        perror("Error on write");
        exit(-1);
    } else if (bytes_written != sizeof(write_buf)) {
        printf("Incomplete write.\n");
        exit(-1);
    }

    /*
     * I had this code in when I was using the same FD to seek
     * to the beginning.  It's no longer needed with opening a
     * separate fd for reading.
     */
    /*
    printf("  Seeking to beginning.\n");
    seek_offset = lseek(fd, 0, SEEK_SET);
    if (seek_offset < 0) {
        perror("Error on seek");
        exit(-1);
    }
    */

    printf("  Opening for read.\n");
    fd_read = shm_open(shm_name, O_RDONLY, S_IRUSR);
    if (fd_read <= 0) {
        perror("Error on shm_open");
        exit(-1);
    }

    printf("  Reading %ld bytes.\n", sizeof(read_buf));
    bytes_read = read(fd_read, read_buf, sizeof(read_buf));
    if (bytes_read < 0) {
        perror("Error on read");
        exit(-1);
    } else if (bytes_read == 0) {
        printf("EOF on read.\n");
    } else if (bytes_read != sizeof(read_buf)) {
        printf("Incomplete read.\n");
        exit(-1);
    }
    printf("  read_buf string: '%s'\n", read_buf);

    printf("  Unlinking shm: %s\n", shm_name);
    if (shm_unlink(shm_name) != 0) {
        perror("Error on shm_unlink");
        exit(-1);
    }

    printf("# shm end.\n");
}
