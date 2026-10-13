#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#define N 100

uint64_t max_joltage(char buf[N], unsigned int digits, unsigned int i) {
	if (digits == 0) {
		return 0;
	}

	assert(digits <= N);
	assert(i < N);

	unsigned int idx = i;
	for (unsigned int j = i+1; j < N-digits+1; ++j) {
		if (buf[j]-'0' > buf[idx]-'0') {
			idx = j;
		}
	}

	uint64_t res = buf[idx] - '0';
	if (digits > 1) {
		res *= pow(10, digits-1);
	}
	res += max_joltage(buf, digits-1, idx+1);

	return res;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		perror("fopen");
		exit(1);
	}

	uint64_t sum = 0;

	char buf[N+2]; // ...\n\0
	while (fgets(buf, sizeof(buf), fp)) {
		assert(buf[N] == '\n');
		sum += max_joltage(buf, 12, 0);
	}

	assert(feof(fp) && !ferror(fp));

	if (fclose(fp)) {
		perror("fclose");
		exit(1);
	}

	printf("%lu\n", sum);

	return 0;
}
