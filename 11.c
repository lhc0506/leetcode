#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum DIR_t {
	UP,
	RIGHT,
	DOWN,
	LEFT
} DIR_t;
void geometry_init(int(*geometry)[20]);
int move_start(int(*geometry)[20], unsigned char* idc_set);
void move(int(*geometry)[20], unsigned char idc);
inline void next_location(unsigned char dir, int* last_i, int* last_j);
int find_max(int(*geometry)[20]);
void print(int(*geometry)[20]);
void test(int(*geometry)[20]);
int g_num;
int g_maximum;
int main(int argc, char** argv)
{
	int max = 0, tmp;
	int geometry[20][20];
	unsigned char idc_set[10];
	g_maximum = 0;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
			geometry[i][j] = 0;
	scanf("%d%*c", &g_num);
	if (g_num == 0) return 0;
	if (g_num == 1) return geometry[0][0];
	geometry_init(geometry);
	if (g_maximum == find_max(geometry)) return g_maximum;
	// **************  testcode
	// test(geometry);
	// **************  testcode
	for (unsigned char a = 0; a < 4; a++)
		for (unsigned char b = 0; b < 4; b++)
			for (unsigned char c = 0; c < 4; c++)
				for (unsigned char d = 0; d < 4; d++)
					for (unsigned char e = 0; e < 4; e++)
						for (unsigned char a2 = 0; a2 < 4; a2++)
							for (unsigned char b2 = 0; b2 < 4; b2++)
								for (unsigned char c2 = 0; c2 < 4; c2++)
									for (unsigned char d2 = 0; d2 < 4; d2++)
										for (unsigned char e2 = 0; e2 < 4; e2++)
										{
											idc_set[0] = a;
											idc_set[1] = b;
											idc_set[2] = c;
											idc_set[3] = d;
											idc_set[4] = e;
											idc_set[5] = a2;
											idc_set[6] = b2;
											idc_set[7] = c2;
											idc_set[8] = d2;
											idc_set[9] = e2;
											tmp = move_start(geometry, idc_set);
											if (max < tmp) max = tmp;
											if (max == g_maximum)
											{
												printf("%d", max);
												return 0;
											}
										}
	printf("%d", max);
	return 0;
}
// **************  testcode
void print(int(*geometry)[20])
{
	for (int i = 0; i < g_num; i++)
	{
		for (int j = 0; j < g_num; j++)
		{
			printf("%d ", geometry[i][j]);
		}
		printf("\n");
	}
}
void test(int(*geometry)[20])
{
	int copy[20][20];
	int idc;
	for (int i = 0; i < g_num; i++)
		for (int j = 0; j < g_num; j++)
			copy[i][j] = geometry[i][j];
	while (1)
	{
		scanf("%d%*c", &idc);
		if (idc > 3) break;
		move(copy, idc);
		print(copy);
	}
	return;
}
// **************  testcode
// 일반적인 데카르트 좌표계가 아닌
// 컴퓨터비전에서 이용하는 좌표계 (i, j)
void geometry_init(int(*geometry)[20])
{
	for (int i = 0; i < g_num; i++)
		for (int j = 0; j < g_num; j++)
		{
			scanf("%d%*c", &geometry[i][j]);
			g_maximum += geometry[i][j];
		}
	for (int i = 20; i > 0; i--)
	{
		if (g_maximum & (1 << i) == 1)
		{
			g_maximum = (1 << i);
			break;
		}
	}
			
	return;
}
int move_start(int(*geometry)[20], unsigned char* idc_set)
{
	int copy[20][20];
	for (int i = 0; i < g_num; i++)
		for (int j = 0; j < g_num; j++)
			copy[i][j] = geometry[i][j];
	for (int i = 0; i < (1 + sizeof(idc_set) / sizeof(char)); i++)
	{
		move(copy, *(idc_set+i));
	}
	return find_max(copy);
}
// 컴퓨터 비전 좌표계 (i, j)
void move(int(*geometry)[20], unsigned char idc)
{
	int	t_value = 0;
	int t_i = 0, t_j = 0;
	switch (idc)
	{
	case UP:	// 왼쪽 위에서 시작
		for (int j = 0; j < g_num; j++)
		{
			// 가장 위쪽 위치로 할당
			t_i = 0;
			t_j = j;
			t_value = -1;
			for (int i = 0; i < g_num; i++)
			{
				if (geometry[i][j] == 0) continue;
				else if (t_value == geometry[i][j])	// 한 번 합쳐진 요소는 두번 합쳐질 수 없다.
				{
					geometry[t_i][t_j] = t_value << 1;
					geometry[i][j] = 0;
					next_location(UP, &t_i, &t_j);	// 합쳐진 요소의 다음 위치를 지정
					t_value = -1;
				}
				else  // 첫 번째 요소이거나, 합쳐진 다음 요소이거나, 일치하지 않는 두 번째 이상 요소
				{
					if (t_value > 0)	// 이전 값과 동일하지 않았던 경우
					{
						next_location(UP, &t_i, &t_j);
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
					else // 첫번째 or 합쳐진 다음 t_i와 t_j에 적절한 값이 이미 할당
					{
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
				}
			}
		}
		break;
	case RIGHT: // 오른쪽 위에서 시작
		for (int i = 0; i < g_num; i++)
		{
			// 가장 오른쪽 위치로 할당
			t_i = i;
			t_j = g_num - 1;
			t_value = -1;
			for (int j = g_num -1; j >= 0; j--)
			{
				if (geometry[i][j] == 0) continue;
				else if (t_value == geometry[i][j])	// 한 번 합쳐진 요소는 두번 합쳐질 수 없다.
				{
					geometry[t_i][t_j] = t_value << 1;
					geometry[i][j] = 0;
					next_location(RIGHT, &t_i, &t_j);	// 합쳐진 요소의 다음 위치를 지정
					t_value = -1;
				}
				else  // 첫 번째 요소이거나, 합쳐진 다음 요소이거나, 일치하지 않는 두 번째 이상 요소
				{
					if (t_value > 0)	// 이전 값과 동일하지 않았던 경우
					{
						next_location(RIGHT, &t_i, &t_j);
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
					else // 첫번째 or 합쳐진 다음 t_i와 t_j에 적절한 값이 이미 할당
					{
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
				}
			}
		}
		break;
	case DOWN:	// 왼쪽 아래에서 시작
		for (int j = 0; j < g_num; j++)
		{
			// 가장 아래쪽 위치로 할당
			t_i = g_num - 1;
			t_j = j;
			t_value = -1;
			for (int i = g_num -1; i >= 0; i--)
			{
				if (geometry[i][j] == 0) continue;
				else if (t_value == geometry[i][j])	// 한 번 합쳐진 요소는 두번 합쳐질 수 없다.
				{
					geometry[t_i][t_j] = t_value << 1;
					geometry[i][j] = 0;
					next_location(DOWN, &t_i, &t_j);	// 합쳐진 요소의 다음 위치를 지정
					t_value = -1;
				}
				else  // 첫 번째 요소이거나, 합쳐진 다음 요소이거나, 일치하지 않는 두 번째 이상 요소
				{
					if (t_value > 0)	// 이전 값과 동일하지 않았던 경우
					{
						next_location(DOWN, &t_i, &t_j);
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
					else // 첫번째 or 합쳐진 다음 t_i와 t_j에 적절한 값이 이미 할당
					{
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
				}
			}
		}
		break;
	case LEFT:  // 오른쪽 아래에서 시작
		for (int i = 0; i < g_num; i++)
		{
			// 가장 왼쪽 위치로 할당
			t_i = i;
			t_j = 0;
			t_value = -1;
			for (int j = 0; j < g_num; j++)
			{
				if (geometry[i][j] == 0) continue;
				else if (t_value == geometry[i][j])	// 한 번 합쳐진 요소는 두번 합쳐질 수 없다.
				{
					geometry[t_i][t_j] = t_value << 1;
					geometry[i][j] = 0;
					next_location(LEFT, &t_i, &t_j);	// 합쳐진 요소의 다음 위치를 지정
					t_value = -1;
				}
				else  // 첫 번째 요소이거나, 합쳐진 다음 요소이거나, 일치하지 않는 두 번째 이상 요소
				{
					if (t_value > 0)	// 이전 값과 동일하지 않았던 경우
					{
						next_location(LEFT, &t_i, &t_j);
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
					else // 첫번째 or 합쳐진 다음 t_i와 t_j에 적절한 값이 이미 할당
					{
						t_value = geometry[i][j];
						geometry[i][j] = 0;
						geometry[t_i][t_j] = t_value;
					}
				}
			}
		}
		break;
	}
	return;
}
// 가장 마지막에 넣었던 값
inline void next_location(unsigned char idc, int* last_i, int* last_j)
{
	switch (idc)
	{
	case UP:
		*last_i = *last_i + 1;
		break;
	case RIGHT:
		*last_j = *last_j - 1;
		break;
	case DOWN:
		*last_i = *last_i - 1;
		break;
	case LEFT:
		*last_j = *last_j + 1;
		break;
	}
	return;
}
int find_max(int(*geometry)[20])
{
	int max = 0;
	for (int i = 0; i < g_num; i++)
		for (int j = 0; j < g_num; j++)
			if (max < geometry[i][j]) max = geometry[i][j];
	return max;
}