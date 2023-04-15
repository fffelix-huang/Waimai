bool is_prime(ll n, vector<ll> x) {
	ll d = n - 1;
	d >>= __builtin_ctzll(d);
	for(auto a : x) {
		if(n <= a) break;
		ll t = d;
		ll y = 1, b = t;
		while(b) {
			if(b & 1) y = __int128(y) * a % n;
			a = __int128(a) * a % n;
			b >>= 1;
		}
		while(t != n - 1 && y != 1 && y != n - 1) {
			y = __int128(y) * y % n;
			t <<= 1;
		}
		if(y != n - 1 && t % 2 == 0) {
			return false;
		}
	}
	return true;
}

bool is_prime(ll n) {
	if(n <= 1) return false;
	if(n % 2 == 0) return n == 2;
	if(n < (1LL << 30)) return is_prime(n, {2, 7, 61});
	return is_prime(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}