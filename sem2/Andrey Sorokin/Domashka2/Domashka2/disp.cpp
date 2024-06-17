double disp(int* a, int count) {

	double mid = 0;
	for (int i = 0; i < count; i++) {
		mid += a[i];
	}
	mid = double(mid) / count;

	double disp = 0;
	for (int i = 0; i < count; i++) {
		disp += (a[i] - mid) * (a[i] - mid);
	}

	return double(disp) / count;
}