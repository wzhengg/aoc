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

int is_repeating_sequence(uint64_t id, uint64_t seqlen) {
	uint64_t div = pow(10, seqlen);
	uint64_t seq = id % div;
	for (; id > 0; id /= div) {
		if (id % div != seq) {
			return 0;
		}
	}
	return 1;
}

int is_invalid(uint64_t id) {
	int digits = (int)log10(id) + 1;
	for (int n = 1; n <= digits/2; ++n) {
		if (digits%n == 0 && is_repeating_sequence(id, n)) {
			return 1;
		}
	}
	return 0;
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
