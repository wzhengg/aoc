#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#define N 135

static char grid[N][N];

int is_accessible(int r, int c) {
	assert(0 <= r && r < N);
	assert(0 <= c && c < N);

	int count = 0;

	if (r-1 >= 0 && grid[r-1][c] == '@')
		++count;
	if (r+1 < N && grid[r+1][c] == '@')
		++count;
	if (c-1 >= 0 && grid[r][c-1] == '@')
		++count;
	if (c+1 < N && grid[r][c+1] == '@')
		++count;
	if (r-1 >= 0 && c-1 >= 0 && grid[r-1][c-1] == '@')
		++count;
	if (r-1 >= 0 && c+1 < N && grid[r-1][c+1] == '@')
		++count;
	if (r+1 < N && c-1 >= 0 && grid[r+1][c-1] == '@')
		++count;
	if (r+1 < N && c+1 < N && grid[r+1][c+1] == '@')
		++count;

	return count < 4;
}

int remove_roll(int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= N || grid[r][c] != '@' || !is_accessible(r, c)) {
		return 0;
	}

	grid[r][c] = '.';

	return 1 + remove_roll(r-1, c) + remove_roll(r+1, c) + remove_roll(r, c-1) + remove_roll(r, c+1) +
		remove_roll(r-1, c-1) + remove_roll(r-1, c+1) + remove_roll(r+1, c-1) + remove_roll(r+1, c+1);
}

int main(void) {
	int fd = open("input.txt", O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	for (int i = 0; i < N; ++i) {
		ssize_t nread = read(fd, grid[i], N);
		if (nread == -1) {
			perror("read");
			exit(1);
		}
		assert(nread == N);

		char buf[1];
		nread = read(fd, buf, sizeof(buf));
		if (nread == -1) {
			perror("read");
			exit(1);
		}
		assert(nread == 1);
	}

	if (close(fd) == -1) {
		perror("close");
		exit(1);
	}

	int count = 0;

	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			if (grid[r][c] == '@') {
				count += remove_roll(r, c);
			}
		}
	}

	printf("%d\n", count);

	return 0;
}
