template<class T>
struct wavelet_tree {
	int n, log;
	vector<T> vals;
	vi sums;
	vector<ull> bits;
	void set_bit(int i, ull v) { bits[i >> 6] |= (v << (i & 63)); }
	int get_sum(int i) const { return sums[i >> 6] + __builtin_popcountll(bits[i >> 6] & ((1ULL << (i & 63)) - 1)); }
	wavelet_tree(const vector<T>& _v) : n(SZ(_v)) {
		vals = sort_unique(_v);
		log = __lg(2 * vals.size() - 1);
		bits.resize((log * n + 64) >> 6, 0ULL);
		sums.resize(SZ(bits), 0);
		vi v(SZ(_v)), cnt(SZ(vals) + 1);
		REP(i, SZ(v)) {
			v[i] = lower_bound(ALL(vals), _v[i]) - vals.begin();
			cnt[v[i] + 1] += 1;
		}
		partial_sum(ALL(cnt) - 1, cnt.begin());
		REP(j, log) {
			for(int i : v) {
				int tmp = i >> (log - 1 - j);
				int pos = (tmp >> 1) << (log - j);
				set_bit(j * n + cnt[pos], tmp & 1);
				cnt[pos]++;
			}
			for(int i : v) cnt[(i >> (log - j)) << (log - j)]--;
		}
		FOR(i, 1, SZ(sums)) sums[i] = sums[i - 1] + __builtin_popcountll(bits[i - 1]);
	}

	T get_kth(int a, int b, int k) {
		for(int j = 0, ia = 0, ib = n, res = 0;; j++) {
			if(j == log) return vals[res];
			int cnt_ia = get_sum(n * j + ia);
			int cnt_a = get_sum(n * j + a);
			int cnt_b = get_sum(n * j + b);
			int cnt_ib = get_sum(n * j + ib);
			int ab_zeros = (b - a) - (cnt_b - cnt_a);
			if(ab_zeros > k) {
				res <<= 1;
				ib -= cnt_ib - cnt_ia;
				a -= cnt_a - cnt_ia;
				b -= cnt_b - cnt_ia;
			} else {
				res = (res << 1) | 1;
				k -= ab_zeros;
				ia += (ib - ia) - (cnt_ib - cnt_ia);
				a += (ib - a) - (cnt_ib - cnt_a);
				b += (ib - b) - (cnt_ib - cnt_b);
			}
		}
	}
};
