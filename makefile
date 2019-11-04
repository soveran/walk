PREFIX?=/usr/local
MANPREFIX?=${PREFIX}/share/man
STRIP?=strip

default: walk

walk: walk.c
	$(CC) -Wall -Os -o walk walk.c

clean:
	@echo cleaning
	@rm -f walk

install: walk
	@echo stripping executable
	@${STRIP} walk
	@echo installing executable to ${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	@cp -f walk ${PREFIX}/bin/walk
	@chmod 755 ${PREFIX}/bin/walk

	@echo installing manual pages to ${MANPREFIX}/man1
	@mkdir -p ${MANPREFIX}/man1
	@cp -f walk.1 ${MANPREFIX}/man1/walk.1
	@chmod 644 ${MANPREFIX}/man1/walk.1

uninstall:
	@echo removing executable from ${PREFIX}/bin
	@rm ${PREFIX}/bin/walk
	@echo removing manual pages from ${MANPREFIX}/man1
	@rm ${MANPREFIX}/man1/walk.1

test:
	@sh test/tests.sh

.PHONY: clean install uninstall test
