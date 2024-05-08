double mid(int* a, int count) {

	double mid = 0;
	for (int i = 0; i < count; i++) {
		mid += a[i];
	}
	return double(mid) / count;
}