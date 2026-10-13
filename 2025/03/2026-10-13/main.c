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

	int sum = 0;

	char buf[N+2]; // ...\n\0
	while (fgets(buf, sizeof(buf), fp)) {
		assert(buf[N] == '\n');

		int idx1 = 0;
		for (int i = 1; i < N-1; ++i) {
			if (buf[i]-'0' > buf[idx1]-'0') {
				idx1 = i;
			}
		}

		int idx2 = idx1 + 1;
		for (int i = idx2+1; i < N; ++i) {
			if (buf[i]-'0' > buf[idx2]-'0') {
				idx2 = i;
			}
		}

		sum += (buf[idx1]-'0') * 10 + (buf[idx2]-'0');
	}

	assert(feof(fp) && !ferror(fp));

	if (fclose(fp)) {
		perror("fclose");
		exit(1);
	}

	printf("%d\n", sum);

	return 0;
}
