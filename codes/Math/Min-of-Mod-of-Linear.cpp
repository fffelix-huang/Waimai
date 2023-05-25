// \min{Ax + B (mod M) | 0 <= x < N}
int min_of_mod_of_linear(int n, int m, int a, int b) {
	ll v = floor_sum(n, m, a, b);
	int l = -1, r = m - 1;
	while(r - l > 1) {
		int k = (l + r) / 2;
		if(floor_sum(n, m, a, b + (m - 1 - k)) < v + n) r = k;
		else l = k;
	}
	return r;
}