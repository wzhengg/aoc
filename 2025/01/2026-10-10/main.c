#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		perror("fopen");
		exit(1);
	}

	int pos = 50;
	int zeros = 0;

	char buf[8];
	while (fgets(buf, sizeof(buf), fp)) {
		char dir;
		int count;
		assert(sscanf(buf, "%c%d", &dir, &count) == 2);
		assert(dir == 'L' || dir == 'R');
		assert(count > 0 && count < 1000);

		zeros += count / N;
		count %= N;

		int old = pos;
		if (dir == 'L') {
			pos -= count;
			if (pos < 0) {
				pos += N;
				if (old != 0) {
					++zeros;
				}
			}
		} else {
			if (pos + count > N) {
				++zeros;
			}
			pos = (pos + count) % N;
		}

		if (pos == 0 && old != 0) {
			++zeros;
		}
	}

	assert(feof(fp) && !ferror(fp));

	if (fclose(fp) != 0) {
		perror("fclose");
		exit(1);
	}

	printf("%d\n", zeros);

	return 0;
}
