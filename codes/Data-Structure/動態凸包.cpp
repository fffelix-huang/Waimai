struct line_t {
	mutable ll k, m, p;
	bool operator<(const line_t& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};
template<bool MAX>
struct CHT : multiset<line_t, less<>> {
	const ll INF = 1e18L;
	bool isect(iterator x, iterator y) {
		if(y == end()) return x->p = INF, 0;
		if(x->k == y->k) {
			x->p = (x->m > y->m ? INF : -INF);
		} else {
			x->p = floor_div(y->m - x->m, x->k - y->k); // see Math
		}
		return x->p >= y->p;
	}
	void add_line(ll k, ll m) {
		if(!MAX) k = -k, m = -m;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while(isect(y, z)) z = erase(z);
		if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	ll get(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return (l.k * x + l.m) * (MAX ? +1 : -1);
	}
};
