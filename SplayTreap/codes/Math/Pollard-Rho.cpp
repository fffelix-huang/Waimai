void PollardRho(map<ll, int>& mp, ll n) {
	if(n == 1) return;
	if(is_prime(n)) return mp[n]++, void();
	if(n % 2 == 0) {
		mp[2] += 1;
		PollardRho(mp, n / 2);
		return;
	}
	ll x = 2, y = 2, d = 1, p = 1;
	#define f(x, n, p) ((__int128(x) * x % n + p) % n)
	while(true) {
		if(d != 1 && d != n) {
			PollardRho(mp, d);
			PollardRho(mp, n / d);
			return;
		}
		p += (d == n);
		x = f(x, n, p), y = f(f(y, n, p), n, p);
		d = __gcd(abs(x - y), n);
	}
	#undef f
}

vector<ll> get_divisors(ll n) {
	if(n == 0) return {};
	map<ll, int> mp;
	PollardRho(mp, n);
	vector<pair<ll, int>> v(mp.begin(), mp.end());
	vector<ll> res;
	auto f = [&](auto f, int i, ll x) -> void {
		if(i == (int) v.size()) {
			res.push_back(x);
			return;
		}
		for(int j = v[i].second; ; j--) {
			f(f, i + 1, x);
			if(j == 0) break;
			x *= v[i].first;
		}
	};
	f(f, 0, 1);
	sort(res.begin(), res.end());
	return res;
}
