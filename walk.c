/* We want POSIX.1-2008 + XSI, i.e. SuSv4, features */
#define _XOPEN_SOURCE 700

/* Added on 2017-06-25:
   If the C library can support 64-bit file sizes
   and offsets, using the standard names,
   these defines tell the C library to do so. */
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64 

#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* POSIX.1 says each process has at least 20 file descriptors.
 * Three of those belong to the standard streams.
 * Here, we use a conservative estimate of 15 available;
 * assuming we use at most two for other uses in this program,
 * we should never run into any problems.
 * Most trees are shallower than that, so it is efficient.
 * Deeper trees are traversed fine, just a bit slower.
 * (Linux allows typically hundreds to thousands of open files,
 *  so you'll probably never see any issues even if you used
 *  a much higher value, say a couple of hundred, but
 *  15 is a safe, reasonable value.)
*/
#ifndef USE_FDS
#define USE_FDS 15
#endif

static int print_entry(const char *filepath, const struct stat *info,
                const int typeflag, struct FTW *pathinfo)
{
	if (typeflag == FTW_F) {
	    printf("%s\n", filepath);
	}

	return 0;
}

static int print_directory_tree(const char *const dirpath) {
    int result;

    /* Invalid directory path? */
    if (dirpath == NULL || *dirpath == '\0') {
        return errno = EINVAL;
    }

    result = nftw(dirpath, print_entry, USE_FDS, FTW_PHYS);
    if (result >= 0) {
        errno = result;
    }

    return errno;
}

int main(int argc, char *argv[]) {
    int arg;
    int pos;

    if (argc < 2) {
        if (print_directory_tree(".")) {
            fprintf(stderr, "%s.\n", strerror(errno));
            return EXIT_FAILURE;
        }
    } else {
        for (arg = 1; arg < argc; arg++) {
        	pos = strlen(argv[arg]);

        	if (argv[arg][pos-1] == '/') {
        		argv[arg][pos-1] = '\0';
        	}

            if (print_directory_tree(argv[arg])) {
                fprintf(stderr, "%s.\n", strerror(errno));
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}