int merge(int a[], int at[], int L, int R, int end)//排序核心算法
{
	int temp = L;
	int num = end - L + 1;
	int Lend = R - 1;
	while (L <= Lend && R <= end)
	{
		if (a[L] <= a[R])
			at[temp++] = a[L++];
		else at[temp++] = a[R++];
	}
	while (L <= Lend)
		at[temp++] = a[L++];
	while (R <= end)
		at[temp++] = a[R++];
	for (int i = 0; i < num; i++, end--)			//注意这里的边界条件
		a[end] = at[end];							
	return end;
}
int msort(int a[], int at[], int L, int end)		//分
{
	if (end > L)
	{
		int center = (end + L) / 2;
		msort(a, at, L, center);
		msort(a, at, center + 1, end);
		merge(a, at, L, center + 1, end);
	}
	return 0;
}
int mergersort(int a[], int n)						//对外调用的接口
{
	int *at = new int[n];
	msort(a, at, 0, n - 1);
	delete at;
	at = NULL;
	return 0;
}
