#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fts.h>
#include <stdio.h>
#include <string.h>

static int tree(char *const argv[]) {
	FTS *ftsp;
	FTSENT *f, *children;

	int fts_options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR;

	if ((ftsp = fts_open(argv, fts_options, NULL)) == NULL) {
		return -1;
	}

	children = fts_children(ftsp, 0);

	if (children == NULL) {
		return 0;
	}

	while ((f = fts_read(ftsp)) != NULL) {
		switch (f->fts_info) {
		case FTS_D:
			break;
		case FTS_F:
			printf("%s\n", f->fts_path);
			break;
		default:
			break;
		}
	}

	fts_close(ftsp);

	return 0;
}

int main(int argc, char *const argv[]) {
	int len, i;
	char *const *dirs;

	if (argc < 2) {
		fprintf(stderr, "usage: %s path\n", argv[0]);
		return 1;
	} else {
		dirs = argv+1;

		for (i = 0; i < argc-1; i++) {
			len = strlen(dirs[i]);

			if (dirs[i][len-1] == '/') {
				dirs[i][len-1] = '\0';
			}
		}
	}

	return (tree(dirs) && 1);
}
