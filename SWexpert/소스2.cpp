#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct {
	int m, s, d;
}FireBall;

int N, M, K;
FireBall* fb[MAX][MAX];
int cnt_fb[MAX][MAX], len_fb[MAX][MAX];
FireBall* fb_temp[MAX][MAX];
int cnt_fb_temp[MAX][MAX], len_fb_temp[MAX][MAX];
int row_dir1[4] = { -1, -1, 1, 1 };
int col_dir1[4] = { -1, 1, -1, 1 };
int row_dir2[4] = { -1, 0, 0, 1 };
int col_dir2[4] = { 0, -1, 1, 0 };
FireBall* tmp;

void addFireBall(int r, int c, int m, int s, int d) {
	if (fb[r][c] == NULL) {
		len_fb[r][c] = 1;

		fb[r][c] = (FireBall*)malloc(sizeof(FireBall) * (len_fb[r][c]));
		if (fb[r][c] == NULL) {

			printf("HEY\n");
		}
	}
	else if (len_fb[r][c] <= cnt_fb[r][c]) {
		if (len_fb[r][c] == 0) {
			printf("HEEEY\n");
		}
		len_fb[r][c] = len_fb[r][c] << 1;
		tmp = (FireBall*)malloc(sizeof(FireBall) * (len_fb[r][c]));
		if (tmp != NULL) {
			printf("HEY\n");
			memcpy(tmp, fb[r][c], sizeof(FireBall) * (len_fb[r][c] >> 1));
			free(fb[r][c]);
			fb[r][c] = tmp;
		}
	
		//fb[r][c] = (FireBall*)realloc(fb[r][c], sizeof(FireBall) * len_fb[r][c]);
	}

	fb[r][c][cnt_fb[r][c]].m = m;
	fb[r][c][cnt_fb[r][c]].s = s;
	fb[r][c][cnt_fb[r][c]].d = d;
	cnt_fb[r][c] += 1;
}

void addFireBallTemp(int r, int c, int m, int s, int d) {

	if (fb_temp[r][c] == NULL) {
		len_fb_temp[r][c] = 1;
		fb_temp[r][c] = (FireBall*)malloc(sizeof(FireBall) * (len_fb_temp[r][c]));
		if (fb_temp[r][c] == NULL) {

			printf("HEY\n");
		}
	}
	else if (len_fb_temp[r][c] <= cnt_fb_temp[r][c]) {
		if (len_fb_temp[r][c] == 0) {
			printf("HEEEY\n");
		}
		len_fb_temp[r][c] = len_fb_temp[r][c] << 1;
		tmp = (FireBall*)malloc(sizeof(FireBall) * (len_fb_temp[r][c]));
		if (tmp != NULL) {
			printf("HEY\n");
			memcpy(tmp, fb_temp[r][c], sizeof(FireBall) * (len_fb_temp[r][c]/2));
			free(fb_temp[r][c]);
			fb_temp[r][c] = tmp;
		}
		//fb_temp[r][c] = (FireBall*)realloc(fb_temp[r][c], sizeof(FireBall) * len_fb_temp[r][c]);
	}
	//printf("%d %d: %d\n", r, c, cnt_fb_temp[r][c]);
	fb_temp[r][c][cnt_fb_temp[r][c]].m = m;	
	fb_temp[r][c][cnt_fb_temp[r][c]].s = s;
	fb_temp[r][c][cnt_fb_temp[r][c]].d = d;
	cnt_fb_temp[r][c] += 1;
}

int get_direction(int dirR, int dirC) {
	if (dirR == -1) {
		if (dirC == -1) return 7;
		else if (dirC == 0) return 0;
		else return 1;
	}
	else if (dirR == 0) {
		if (dirC == -1) return 6;
		else return 2;
	}
	else {
		if (dirC == -1) return 5;
		else if (dirC == 0) return 4;
		else return 3;
	}
}

void make_a_round(int* num) {
	if (*num < 0) *num = N - (((-1) * (*num)) % N);
	else if (*num > N - 1) *num = (*num) % N;
}

void get_location(int* r, int* c, int s, int dir) {
	switch (dir) {
	case 0:
		*r -= s;
		break;
	case 1:
		*r -= s;
		*c += s;
		break;
	case 2:
		*c += s;
		break;
	case 3:
		*c += s;
		*r += s;
		break;
	case 4:
		*r += s;
		break;
	case 5:
		*r += s;
		*c -= s;
		break;
	case 6:
		*c -= s;
		break;
	case 7:
		*c -= s;
		*r -= s;
		break;
	}
	make_a_round(r);
	make_a_round(c);
}

void combine_split_FireBall(int r, int c) {
	FireBall temp;
	int flag = 0;

	temp.m = 0;
	temp.s = 0;
	temp.d = fb[r][c][0].d;

	for (int i = 0; i < cnt_fb[r][c]; i++) {
		temp.m += fb[r][c][i].m;
		temp.s += fb[r][c][i].s;
	}

	for (int i = 1; i < cnt_fb[r][c]; i++)
		if (fb[r][c][i].d % 2 != temp.d % 2)
			flag = 1;

	temp.m /= 5;
	temp.s /= cnt_fb[r][c];

	if (temp.m == 0) {
		return;
	}

	if (flag == 0) {
		for (int d = 0; d < 4; d++) {
			addFireBallTemp(r, c, temp.m, temp.s, get_direction(row_dir2[d], col_dir2[d]));
		}
	}
	else {
		for (int d = 0; d < 4; d++) {
			addFireBallTemp(r, c, temp.m, temp.s, get_direction(row_dir1[d], col_dir1[d]));
		}
	}
}

void moveFireBall(int r, int c) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cnt_fb_temp[i][j] = 0;
	int r_temp, c_temp;
	for (int i = 0; i < cnt_fb[r][c]; i++) {
		r_temp = r, c_temp = c;
		get_location(&r_temp, &c_temp, fb[r][c][i].s, fb[r][c][i].d);
		addFireBallTemp(r_temp, c_temp, fb[r][c][i].m, fb[r][c][i].s, fb[r][c][i].d);
	}
	cnt_fb[r][c] = 0;
}

void freeFb() {
	tmp = NULL;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (fb[i][j] != NULL) {
				free(fb[i][j]);
			}
			fb[i][j] = NULL;
			len_fb[i][j] = 0;
			cnt_fb[i][j] = 0;
		}
	}
}

void freeFbTemp() {
	tmp = NULL;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (fb_temp[i][j] != NULL) {
				printf("len: %d\n", len_fb_temp[i][j]);
				free(fb_temp[i][j]);
			}
			fb_temp[i][j] = NULL;
			len_fb_temp[i][j] = 0;
			cnt_fb_temp[i][j] = 0;
		}
	}
}
void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fb_temp[i][j] = NULL;
			fb[i][j] = NULL;
			len_fb[i][j] = 0;
			cnt_fb[i][j] = 0;
			len_fb_temp[i][j] = 0;
			cnt_fb_temp[i][j] = 0;
		}
	}

}

int main() {
	int r, c, m, s, d;
	int sum = 0;

	// input
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &N, &M, &K);
	init();
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &r, &c, &m, &s, &d);
		addFireBall(r - 1, c - 1, m, s, d);
	}

	for (int cnt = 0; cnt < K; cnt++) {
		// move
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (cnt_fb[i][j] > 0)
					moveFireBall(i, j);
			}
		}
		freeFb();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (cnt_fb_temp[i][j] > 0) {
					for (int k = 0; k < cnt_fb_temp[i][j]; k++)
						addFireBall(i, j, fb_temp[i][j][k].m, fb_temp[i][j][k].s, fb_temp[i][j][k].d);
				}
			}
		}
		freeFbTemp();

		// combine and split
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (cnt_fb[i][j] > 1) {
					combine_split_FireBall(i, j);
					cnt_fb[i][j] = 0;
				}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (cnt_fb_temp[i][j] > 0)
					for (int k = 0; k < cnt_fb_temp[i][j]; k++)
						addFireBall(i, j, fb_temp[i][j][k].m, fb_temp[i][j][k].s, fb_temp[i][j][k].d);
		freeFbTemp();
	}

	// get sum of m
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			if (cnt_fb[i][j] > 0)
				for (int k = 0; k < cnt_fb[i][j]; k++)
					sum += fb[i][j][k].m;
		}
	printf("%d", sum);
	freeFb();
	return 0;
}