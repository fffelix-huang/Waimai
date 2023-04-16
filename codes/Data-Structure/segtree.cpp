template<class S, S (*e)(), S (*op)(S, S)>
struct segtree {
	int n, size, log;
	vector<S> st;
	void update(int v) { st[v] = op(st[v << 1], st[v << 1 | 1]); }
	segtree(int _n) : segtree(vector<S>(_n, e())) {}
	segtree(const vector<S>& a): n(sz(a)) {
		log = __lg(2 * n - 1), size = 1 << log;
		st.resize(size << 1, e());
		REP(i, n) st[size + i] = a[i];
		for(int i = size - 1; i; i--) update(i);
	}
	void set(int p, S val) {
		st[p += size] = val;
		for(int i = 1; i <= log; ++i) update(p >> i);
	}
	S get(int p) const {
		return st[p + size];
	}
	S prod(int l, int r) const {
		assert(0 <= l && l <= r && r <= n);
		S sml = e(), smr = e();
		l += size, r += size;
		while(l < r) {
			if(l & 1) sml = op(sml, st[l++]);
			if(r & 1) smr = op(st[--r], smr);
			l >>= 1;
			r >>= 1;
		}
		return op(sml, smr);
	}
	S all_prod() const { return st[1]; }
	template<class F> int max_right(int l, F f) const {
		assert(0 <= l && l <= n && f(e()));
		if(l == n) return n;
		l += size;
		S sm = e();
		do {
			while(~l & 1) l >>= 1;
			if(!f(op(sm, st[l]))) {
				while(l < size) {
					l <<= 1;
					if(f(op(sm, st[l]))) sm = op(sm, st[l++]);
				}
				return l - size;
			}
			sm = op(sm, st[l++]);
		} while((l & -l) != l);
		return n;
	}
	template<class F> int min_left(int r, F f) const {
		assert(0 <= r && r <= n && f(e()));
		if(r == 0) return 0;
		r += size;
		S sm = e();
		do {
			r--;
			while(r > 1 && (r & 1)) r >>= 1;
			if(!f(op(st[r], sm))) {
				while(r < size) {
					r = r << 1 | 1;
					if(f(op(st[r], sm))) sm = op(st[r--], sm);
				}
				return r + 1 - size;
			}
			sm = op(st[r], sm);
		} while((r & -r) != r);
		return 0;
	}
};
