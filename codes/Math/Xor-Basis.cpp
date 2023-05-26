template<int B>
struct xor_basis {
	using T = long long;
	bool zero = false, change = false;
	int cnt = 0;
	array<T, B> p = {};
	vector<T> d;
	void insert(T x) {
		IREP(i, B) {
			if(x >> i & 1) {
				if(!p[i]) {
					p[i] = x, cnt++;
					change = true;
					return;
				} else x ^= p[i];
			}
		}
		if(!zero) zero = change = true;
	}
	T get_min() {
		if(zero) return 0;
		REP(i, B) if(p[i]) return p[i];
	}
	T get_max() {
		T ans = 0;
		IREP(i, B) ans = max(ans, ans ^ p[i]);
		return ans;
	}
	T get_kth(long long k) {
		k++;
		if(k == 1 && zero) return 0;
		k -= zero;
		if(k >= (1LL << cnt)) return -1;
		update();
		T ans = 0;
		REP(i, SZ(d)) if(k >> i & 1) ans ^= d[i];
		return ans;
	}
	bool contains(T x) {
		if(x == 0) return zero;
		IREP(i, B) if(x >> i & 1) x ^= p[i];
		return x == 0;
	}
	void merge(const xor_basis& other) { REP(i, B) if(other.p[i]) insert(other.p[i]); }
	void update() {
		if(!change) return;
		change = false;
		d.clear();
		REP(j, B) IREP(i, j) if(p[j] >> i & 1) p[j] ^= p[i];
		REP(i, B) if(p[i]) d.pb(p[i]);
	}
};