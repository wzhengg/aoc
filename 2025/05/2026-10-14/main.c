#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define N 192

#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct Range Range;
struct Range {
	uint64_t start;
	uint64_t end;
};

static Range ranges[N];

static int cmp(const void *p1, const void *p2) {
	const Range *r1 = p1;
	const Range *r2 = p2;

	if (r1->start < r2->start) {
		return -1;
	} else if (r1->start > r2->start) {
		return 1;
	} else {
		return 0;
	}
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		perror("fopen");
		exit(1);
	}

	char buf[64];
	for (int i = 0; i < N; ++i) {
		assert(fgets(buf, sizeof(buf), fp));
		assert(sscanf(buf, "%lu-%lu", &ranges[i].start, &ranges[i].end) == 2);
		assert(ranges[i].start <= ranges[i].end);
	}

	assert(fgets(buf, sizeof(buf), fp));
	assert(buf[0]=='\n' && buf[1]=='\0');

	if (fclose(fp)) {
		perror("fclose");
		exit(1);
	}

	qsort(ranges, N, sizeof(Range), cmp);

	int i = 0;
	for (int j = 1; j < N; ++j) {
		if (ranges[j].start <= ranges[i].end) {
			ranges[i].end = max(ranges[i].end, ranges[j].end);
		} else {
			ranges[++i] = ranges[j];
		}
	}

	uint64_t count = 0;
	for (int j = 0; j <= i; ++j) {
		count += ranges[j].end - ranges[j].start + 1;
	}

	printf("%lu\n", count);

	return 0;
}
