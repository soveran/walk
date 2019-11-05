#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <fts.h>
#include <stdio.h>
#include <string.h>

static int tree(char * const argv[]) {
	FTS *ftsp;
	FTSENT *p, *chp;

	int fts_options = FTS_COMFOLLOW | FTS_LOGICAL | FTS_NOCHDIR;

	if ((ftsp = fts_open(argv, fts_options, NULL)) == NULL) {
		warn("fts_open");
		return -1;
	}

	chp = fts_children(ftsp, 0);

	if (chp == NULL) {
		return 0;
	}

	while ((p = fts_read(ftsp)) != NULL) {
		switch (p->fts_info) {
		case FTS_D:

			if (p->fts_name[0] == '.' &&
				p->fts_name[1] != '\0') {

				fts_set(ftsp, p, FTS_SKIP);
			}
			
			break;
		case FTS_F:
			printf("%s\n", p->fts_path);
			break;
		default:
			break;
		}
	}

	fts_close(ftsp);
	return 0;
}

int main(int argc, char * const argv[]) {
	int len;

	if (argc < 2) {
		char * const strs[1] = { "." };

		if (tree(strs) != 0) {
			return 1;
		} else {
			return 0;
		}
	} else {
		for (int i = 0; i < argc; i++) {
			len = strlen(argv[i]);
			
			if (argv[i][len-1] == '/') {
				argv[i][len-1] = '\0';
			}
		}

		if (tree(argv + 1) != 0) {
			return 1;
		} else {
			return 0;
		}
	}
}
