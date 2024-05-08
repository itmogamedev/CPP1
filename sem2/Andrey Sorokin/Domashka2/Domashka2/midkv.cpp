#include <cmath>

double midkv(int* a, int count) {
	
	double mid = 0;
	for (int i = 0; i < count; i++) {
		mid += a[i];
	}
	mid = double(mid) / count;

	double Ssum = 0;
	for (int i = 0; i < count; i++) {
		Ssum += (a[i] - mid) * (a[i] - mid);
	}

	return sqrt(double(Ssum) / count);
}