// sum_{i = 0}^{n - 1} floor((ai + b) / c) in O(a + b + c + n)
ll floor_sum(ll n, ll a, ll b, ll c) {
	assert(0 <= n && n < (1LL << 32));
	assert(1 <= c && c < (1LL << 32));
	ull ans = 0;
	if(a < 0) {
		ull a2 = (a % c + c) % c;
		ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / c);
		a = a2;
	}
	if(b < 0) {
		ull b2 = (b % c + c) % c;
		ans -= 1ULL * n * ((b2 - b) / c);
		b = b2;
	}
	ull N = n, C = c, A = a, B = b;
	while(true) {
		if(A >= C) {
			ans += N * (N - 1) / 2 * (A / C);
			A %= C;
		}
		if(B >= C) {
			ans += N * (B / C);
			B %= C;
		}
		ull y_max = A * N + B;
		if(y_max < C) break;
		N = y_max / C, B = y_max % C;
		swap(C, A);
	}
	return ans;
}
