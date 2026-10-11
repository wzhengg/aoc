#define _DEFAULT_SOURCE

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int is_invalid(uint64_t id) {
	int digits = (int)log10(id) + 1;
	uint64_t div = pow(10, digits/2);
	return id%div == id/div;
}

int main(void) {
	char buf[512];

	int fd = open("input.txt", O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	struct stat fstatus;
	if (fstat(fd, &fstatus) == -1) {
		perror("fstat");
		exit(1);
	}

	assert((long unsigned)fstatus.st_size < sizeof(buf) - 1);

	ssize_t nread = read(fd, buf, sizeof(buf) - 1);
	if (nread == -1) {
		perror("read");
		exit(1);
	}
	buf[nread] = '\0';

	assert(close(fd) == 0);

	uint64_t sum = 0;

	char *curr = buf;
	char *next = buf;
	while ((curr = strsep(&next, ","))) {
		uint64_t start, end;
		assert(sscanf(curr, "%lu-%lu", &start, &end) == 2);
		assert(start <= end);

		for (uint64_t id = start; id <= end; ++id) {
			if (is_invalid(id)) {
				sum += id;
			}
		}
	}

	printf("%lu\n", sum);

	return 0;
}
