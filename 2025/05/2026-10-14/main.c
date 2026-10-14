#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define N 192
#define M 1000

typedef struct Range Range;
struct Range {
	uint64_t start;
	uint64_t end;
};

static Range ranges[N];

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		perror("fopen");
		exit(1);
	}

	char buf[64];
	int count = 0;

	for (int i = 0; i < N; ++i) {
		assert(fgets(buf, sizeof(buf), fp));
		assert(sscanf(buf, "%lu-%lu", &ranges[i].start, &ranges[i].end) == 2);
	}

	assert(fgets(buf, sizeof(buf), fp));
	assert(buf[0]=='\n' && buf[1]=='\0');

	for (int i = 0; i < M; ++i) {
		assert(fgets(buf, sizeof(buf), fp));
		uint64_t id = strtoul(buf, NULL, 10);
		for (int j = 0; j < N; ++j) {
			if (ranges[j].start <= id && id <= ranges[j].end) {
				++count;
				break;
			}
		}
	}

	assert(!fgets(buf, sizeof(buf), fp));
	assert(feof(fp) && !ferror(fp));

	if (fclose(fp)) {
		perror("fclose");
		exit(1);
	}

	printf("%d\n", count);

	return 0;
}
