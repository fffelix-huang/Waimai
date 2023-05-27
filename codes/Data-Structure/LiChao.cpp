template<class T>
struct LiChao {
	static constexpr T INF = numeric_limits<T>::max();
	struct Line {
		T a, b;
		Line(T a, T b) : a(a), b(b) {}
		T operator()(T x) const { return a * x + b; }
	};
	int n;
	vector<Line> fs;
	vector<T> xs;
	LiChao(const vector<T>& xs_) {
		xs = sort_unique(xs_);
		n = SZ(xs);
		fs.assign(2 * n, Line(T(0), INF));
	}
	int index(T x) const { return lower_bound(ALL(xs), x) - xs.begin(); }
	void add_line(T a, T b) { update(a, b, 0, n); }
	// [xl, xr) ax+b
	void add_segment(T xl, T xr, T a, T b) {
		int l = index(xl), r = index(xr);
		update(a, b, l, r);
	}
	void update(T a, T b, int l, int r) {
		Line g(a, b);
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) descend(g, l++);
			if(r & 1) descend(g, --r);
		}
	}
	void descend(Line g, int i) {
		int l = i, r = i + 1;
		while(l < n) l <<= 1, r <<= 1;
		while(l < r) {
			int c = (l + r) / 2;
			T xl = xs[l - n], xr = xs[r - 1 - n], xc = xs[c - n];
			Line& f = fs[i];
			if(f(xl) <= g(xl) && f(xr) <= g(xr)) return;
			if(f(xl) >= g(xl) && f(xr) >= g(xr)) { f = g; return; }
			if(f(xc) > g(xc)) swap(f, g);
			if(f(xl) > g(xl)) i = 2 * i, r = c;
			else i = 2 * i + 1, l = c;
		}
	}
	T get(T x) {
		int i = index(x);
		T res = INF;
		for(i += n; i; i >>= 1) res = min(res, fs[i](x));
		return res;
	}
};