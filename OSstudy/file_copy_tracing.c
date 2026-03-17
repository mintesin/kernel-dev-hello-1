/*
 * use POSIX API
 * check the necessary edge cases
 * - file existence
 * - realistic read/write error handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    ssize_t bytes_read;
    ssize_t bytes_written;
    off_t total_written;
    int src;
    int dest;
    char buffer[BUFFER_SIZE];

    /* Ensure two user arguments: source and destination file names */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open source file read-only. abort on failure. */
    src = open(argv[1], O_RDONLY);
    if (src == -1) {
        perror("open source");
        return EXIT_FAILURE;
    }

    /* Open destination (create/truncate) with rw-r--r-- permissions */
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest == -1) {
        perror("open destination");
        close(src);
        return EXIT_FAILURE;
    }

    /* Read in loop until EOF; each successful read may be partial. */
    while ((bytes_read = read(src, buffer, BUFFER_SIZE)) > 0) {
        total_written = 0;
        while (total_written < bytes_read) {
            bytes_written = write(dest, buffer + total_written, bytes_read - total_written);
            if (bytes_written == -1) {
                perror("write");
                close(src);
                close(dest);
                return EXIT_FAILURE;
            }
            total_written += bytes_written;
        }
    }

    /* If read returns -1, a read error happened; cleanup and report. */
    if (bytes_read == -1) {
        perror("read");
        close(src);
        close(dest);
        return EXIT_FAILURE;
    }

    /* close file descriptors and report any close errors (non-fatal here). */
    if (close(src) == -1) {
        perror("close source");
    }

    if (close(dest) == -1) {
        perror("close destination");
    }

    return EXIT_SUCCESS;
}

/*+===========================TRACING================================+*/

/*execve("./file_copy", ["./file_copy"], 0x7fff9004a8d0 /* 80 vars *///) = 0
//brk(NULL)                               = 0x5768e0467000
//mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x700d0783a000
//access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
//openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
//fstat(3, {st_mode=S_IFREG|0644, st_size=67227, ...}) = 0
//mmap(NULL, 67227, PROT_READ, MAP_PRIVATE, 3, 0) = 0x700d07829000
//close(3)                                = 0
//openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
//read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
//pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
//fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
//pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
//mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x700d07600000
//mmap(0x700d07628000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x700d07628000
//mmap(0x700d077b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x700d077b0000
//mmap(0x700d077ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x700d077ff000
//mmap(0x700d07805000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x700d07805000
//close(3)                                = 0
//mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x700d07826000
//arch_prctl(ARCH_SET_FS, 0x700d07826740) = 0
//set_tid_address(0x700d07826a10)         = 9473
//set_robust_list(0x700d07826a20, 24)     = 0
//rseq(0x700d07827060, 0x20, 0, 0x53053053) = 0
//mprotect(0x700d077ff000, 16384, PROT_READ) = 0
//mprotect(0x5768c3537000, 4096, PROT_READ) = 0
//mprotect(0x700d0787a000, 8192, PROT_READ) = 0
//prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
//munmap(0x700d07829000, 67227)           = 0
//write(2, "Usage: ./file_copy <source> <des"..., 42Usage: ./file_copy <source> <destination>
//) = 42
//exit_group(1)                           = ?
//+++ exited with 1 +++
//*/