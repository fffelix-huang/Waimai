template<class S,
         S (*e)(),
         S (*op)(S, S),
         class F,
         F (*id)(),
         S (*mapping)(F, S),
         F (*composition)(F, F)>
struct lazy_segtree {
	int n, size, log;
	vector<S> d; vector<F> lz;
	void update(int k) { d[k] = op(d[k << 1], d[k << 1 | 1]); }
	void all_apply(int k, F f) {
		d[k] = mapping(f, d[k]);
		if(k < size) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		all_apply(k << 1, lz[k]);
		all_apply(k << 1 | 1, lz[k]);
		lz[k] = id();
	}
	lazy_segtree(int _n) : lazy_segtree(vector<S>(_n, e())) {}
	lazy_segtree(const vector<S>& v) : n(SZ(v)) {
		log = __lg(2 * n - 1), size = 1 << log;
		d.resize(size * 2, e());
		lz.resize(size, id());
		REP(i, n) d[size + i] = v[i];
		for(int i = size - 1; i; i--) update(i);
	}
	void set(int p, S x) {
		p += size;
		for(int i = log; i; --i) push(p >> i);
		d[p] = x;
		for(int i = 1; i <= log; ++i) update(p >> i);
	}
	S get(int p) {
		p += size;
		for(int i = log; i; i--) push(p >> i);
		return d[p];
	}
	S prod(int l, int r) {
		if(l == r) return e();
		l += size; r += size;
		for(int i = log; i; i--) {
			if(((l >> i) << i) != l) push(l >> i);
			if(((r >> i) << i) != r) push(r >> i);
		}
		S sml = e(), smr = e();
		while(l < r) {
			if(l & 1) sml = op(sml, d[l++]);
			if(r & 1) smr = op(d[--r], smr);
			l >>= 1, r >>= 1;
		}
		return op(sml, smr);
	}
	S all_prod() const { return d[1]; }
	void apply(int p, F f) {
		p += size;
		for(int i = log; i; i--) push(p >> i);
		d[p] = mapping(f, d[p]);
		for(int i = 1; i <= log; i++) update(p >> i);
	}
	void apply(int l, int r, F f) {
		if(l == r) return;
		l += size; r += size;
		for(int i = log; i; i--) {
			if(((l >> i) << i) != l) push(l >> i);
			if(((r >> i) << i) != r) push((r - 1) >> i);
		}
		{
			int l2 = l, r2 = r;
			while(l < r) {
				if(l & 1) all_apply(l++, f);
				if(r & 1) all_apply(--r, f);
				l >>= 1, r >>= 1;
			}
			l = l2;
			r = r2;
		}
		for(int i = 1; i <= log; i++) {
			if(((l >> i) << i) != l) update(l >> i);
			if(((r >> i) << i) != r) update((r - 1) >> i);
		}
	}
	template<class G> int max_right(int l, G g) {
		assert(0 <= l && l <= n && g(e()));
		if(l == n) return n;
		l += size;
		for(int i = log; i; i--) push(l >> i);
		S sm = e();
		do {
			while(!(l & 1)) l >>= 1;
			if(!g(op(sm, d[l]))) {
				while(l < size) {
					push(l);
					l <<= 1;
					if(g(op(sm, d[l]))) sm = op(sm, d[l++]);
				}
				return l - size;
			}
			sm = op(sm, d[l++]);
		} while((l & -l) != l);
		return n;
	}
	template<class G> int min_left(int r, G g) {
		assert(0 <= r && r <= n && g(e()));
		if(r == 0) return 0;
		r += size;
		for(int i = log; i >= 1; i--) push((r - 1) >> i);
		S sm = e();
		do {
			r--;
			while(r > 1 && (r & 1)) r >>= 1;
			if(!g(op(d[r], sm))) {
				while(r < size) {
					push(r);
					r = r << 1 | 1;
					if(g(op(d[r], sm))) sm = op(d[r--], sm);
				}
				return r + 1 - size;
			}
			sm = op(d[r], sm);
		} while((r & -r) != r);
		return 0;
	}
};
