double med(int* a, int count) {
	
	for (int i = 1; i < count; i++)
	{
		int j = i - 1;
		int ps=0;
		while (j >= 0 && a[j] > a[j + 1])
		{
			ps = a[j + 1];
			a[j + 1] = a[j];
			a[j] = ps;
			j--;
		}
	}

	if (count % 2 == 1) {
		return a[count / 2 + 1];
	}
	else {
		return (a[count / 2] + a[count / 2 + 1]) / 2.;
	}
}