
#include <stdio.h>
#include <stdlib.h>
 
#define MAX 100
#define MAXCOST 0x7fffffff
 
/*
�����������£�
7 11
A B 7
A D 5
B C 8
B D 9
B E 7
C E 5
D E 15
D F 6
E F 8
E G 9
F G 11
���
A - D : 5
D - F : 6
A - B : 7
B - E : 7
E - C : 5
E - G : 9
Total:39
*/
 
int graph[MAX][MAX];
 
int Prim(int graph[][MAX], int n)
{
	/* lowcost[i]��¼��iΪ�յ�ıߵ���СȨֵ����lowcost[i]=0ʱ��ʾ�յ�i���������� */
	int lowcost[MAX];
 
	/* mst[i]��¼��Ӧlowcost[i]����㣬��mst[i]=0ʱ��ʾ���i���������� */
	int mst[MAX];
 
	int i, j, min, minid, sum = 0;
 
	/* Ĭ��ѡ��1�Žڵ��������������2�Žڵ㿪ʼ��ʼ�� */
	for (i = 2; i <= n; i++)
	{
		/* ��̾����ʼ��Ϊ�����ڵ㵽1�Žڵ�ľ��� */
		lowcost[i] = graph[1][i];
 
		/* ������нڵ������ΪĬ�ϵ�1�Žڵ� */
		mst[i] = 1;
	}
 
	/* ���1�Žڵ���������� */
	mst[1] = 0;
 
	/* n���ڵ�������Ҫn-1���߹�����С������ */
	for (i = 2; i <= n; i++)
	{
		min = MAXCOST;
		minid = 0;
 
		/* ��������������СȨֵ�ߵĽڵ�minid */
		for (j = 2; j <= n; j++)
		{
			/* ��Ȩֵ��С�Ҳ����������� */
			if (lowcost[j] < min && lowcost[j] != 0)
			{
				min = lowcost[j];
				minid = j;
			}
		}
		/* ����������ߵ���Ϣ:��㣬�յ㣬Ȩֵ */
		printf("%c - %c : %d\n", mst[minid] + 'A' - 1, minid + 'A' - 1, min);
 
		/* �ۼ�Ȩֵ */
		sum += min;
 
		/* ��ǽڵ�minid���������� */
		lowcost[minid] = 0;
 
		/* ���µ�ǰ�ڵ�minid�������ڵ��Ȩֵ */
		for (j = 2; j <= n; j++)
		{
			/* ���ָ�С��Ȩֵ */
			if (graph[minid][j] < lowcost[j])
			{
				/* ����Ȩֵ��Ϣ */
				lowcost[j] = graph[minid][j];
 
				/* ������СȨֵ�ߵ���� */
				mst[j] = minid;
			}
		}
	}
	/* ������СȨֵ�� */
	return sum;
}
 
int main()
{
	int i, j, k, m, n;
	int x, y, cost;
	char chx, chy;
 
	/* ��ȡ�ڵ�ͱߵ���Ŀ */
	scanf("%d%d", &m, &n);
	getchar();
 
	/* ��ʼ��ͼ�����нڵ�����Ϊ����� */
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			graph[i][j] = MAXCOST;
		}
	}
 
	/* ��ȡ����Ϣ */
	for (k = 0; k < n; k++)
	{
		scanf("%c %c %d", &chx, &chy, &cost);
		getchar();
		i = chx - 'A' + 1;
		j = chy - 'A' + 1;
		graph[i][j] = cost;
		graph[j][i] = cost;
	}
 
	/* �����С������ */
	cost = Prim(graph, m);
 
	/* �����СȨֵ�� */
	printf("��СȨֵ:%d\n", cost);
 
	return 0;	
}
