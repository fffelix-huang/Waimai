template<int mod>
struct Poly {
	vector<ll> a;
	Poly() {}
	Poly(int n) : a(n) {}
	Poly(const vector<ll>& _a) : a(_a) {}
	Poly(const initializer_list<ll>& _a) : a(_a) {}
	int size() const { return SZ(a); }
	void resize(int n) { a.resize(n); }
	void shrink() {
		while(size() && a.back() == 0) a.ppb();
	}
	ll at(int idx) const {
		return idx >= 0 && idx < size() ? a[idx] : 0;
	}
	ll& operator[](int idx) { return a[idx]; }
	friend Poly operator+(const Poly& a, const Poly& b) {
		Poly c(max(SZ(a), SZ(b)));
		REP(i, SZ(c)) c[i] = (a.at(i) + b.at(i)) % mod;
		return c;
	}
	friend Poly operator-(const Poly& a, const Poly& b) {
		Poly c(max(SZ(a), SZ(b)));
		REP(i, SZ(c)) c[i] = (a.at(i) - b.at(i) + mod) % mod;
		return c;
	}
	friend Poly operator*(Poly a, Poly b) {
		return Poly(conv(a.a, b.a)); // see NTT.cpp
	}
	friend Poly operator*(ll a, Poly b) {
		REP(i, SZ(b)) (b[i] *= a) %= mod;
		return b;
	}
	friend Poly operator*(Poly a, ll b) {
		REP(i, SZ(a)) (a[i] *= b) %= mod;
		return a;
	}
	Poly& operator+=(Poly b) { return (*this) = (*this) + b; }
	Poly& operator-=(Poly b) { return (*this) = (*this) - b; }
	Poly& operator*=(Poly b) { return (*this) = (*this) * b; }
	Poly& operator*=(ll b) { return (*this) = (*this) * b; }
	#define MSZ if(m == -1) m = size();
	Poly mulxk(int k) const {
		auto b = a;
		b.insert(b.begin(), k, 0);
		return Poly(b);
	}
	Poly modxk(int k) const {
		k = min(k, size());
		return Poly(vector<ll>(a.begin(), a.begin() + k));
	}
	Poly divxk(int k) const {
		if(size() <= k) return Poly();
		return Poly(vector<ll>(a.begin() + k, a.end()));
	}
	Poly deriv() const {
		if(!SZ(a)) return Poly();
		Poly c(size() - 1);
		REP(i, size() - 1) c[i] = (i + 1LL) * a[i + 1] % mod;
		return c;
	}
	Poly integr() const {
		Poly c(size() + 1);
		REP(i, size()) c[i + 1] = a[i] * mod_pow(i+1, mod-2, mod) % mod;
		return c;
	}
	Poly inv(int m = -1) const { MSZ;
		Poly x{mod_pow(a[0], mod-2, mod)};
		int k = 1;
		while(k < m) {
			k *= 2;
			x = (x * (Poly{2} - modxk(k) * x)).modxk(k);
		}
		return x.modxk(m);
	}
	Poly log(int m = -1) const { MSZ;
		return (deriv() * inv(m)).integr().modxk(m);
	}
	Poly exp(int m = -1) const { MSZ;
		Poly x{1};
		int k = 1;
		while(k < m) {
			k *= 2;
			x = (x * (Poly{1} - x.log(k) + modxk(k))).modxk(k);
		}
		return x.modxk(m);
	}
	Poly pow(ll k, int m = -1) const { MSZ;
		if(k == 0) {
			Poly b(m); b[0] = 1;
			return b;
		}
		int s = 0, sz = size();
		while(s < sz && a[s] == 0) s++;
		if(s == sz) return *this;
		if(m > 0 && s >= (sz + k - 1) / k) return Poly(m);
		if(s * k >= m) return Poly(m);
		return (((divxk(s) * mod_pow(a[s], mod-2, mod)).log(m) * (k % mod)).exp(m) * mod_pow(a[s], k, mod)).mulxk(s * k).modxk(m);
	}
	bool has_sqrt() const {
		if(size() == 0) return true;
		int x = 0;
		while(x < size() && a[x] == 0) x++;
		if(x == size()) return true;
		if(x % 2 == 1) return false;
		ll y = a[x];
		return (y == 0 || mod_pow(y, (mod-1)/2, mod) == 1);
	}
	Poly sqrt(int m = -1) const { MSZ;
		if(size() == 0) return Poly();
		int x = 0;
		while(x < size() && a[x] == 0) x++;
		if(x == size()) return Poly(size());
		Poly f = divxk(x);
		Poly g({mod_sqrt(f[0], mod)});
		ll inv2 = mod_pow(2, mod-2, mod);
		for(int i = 1; i < m; i *= 2) {
			g = (g + f.modxk(i * 2) * g.inv(i * 2)) * inv2;
		}
		return g.modxk(m).mulxk(x / 2);
	}
	Poly shift(ll c) const {
		int n = size();
		Poly b(*this);
		ll f = 1;
		REP(i, n) {
			(b[i] *= f) %= mod;
			(f *= i + 1) %= mod;
		}
		reverse(ALL(b.a));
		Poly exp_cx(vector<ll>(n, 1));
		FOR(i, 1, n) exp_cx[i] = exp_cx[i - 1] * c % mod * mod_pow(i, mod-2, mod) % mod;
		b = (b * exp_cx).modxk(n);
		reverse(ALL(b.a));
		(f *= mod_pow(n, mod-2, mod)) %= mod;
		ll z = mod_pow(f, mod-2, mod);
		IREP(i, n) {
			(b[i] *= z) %= mod;
			(z *= i) %= mod;
		}
		return b;
	}
	Poly mulT(Poly b) const {
		int n = SZ(b);
		if(!n) return Poly();
		reverse(ALL(b.a));
		return ((*this) * b).divxk(n - 1);
	}
	vector<ll> eval(vector<ll> x) const {
		if(size() == 0) return vector<ll>(SZ(x), 0);
		const int n = max(SZ(x), size());
		vector<Poly> q(4 * n);
		vector<ll> ans(SZ(x));
		x.resize(n);
		function<void(int, int, int)> build = [&](int p, int l, int r) {
			if(r - l == 1) q[p] = Poly{1, mod - x[l]};
			else {
				int m = (l + r) / 2;
				build(2 * p, l, m), build(2 * p + 1, m, r);
				q[p] = q[2 * p] * q[2 * p + 1];
			}
		};
		build(1, 0, n);
		function<void(int, int, int, const Poly&)> work = [&](int p, int l, int r, const Poly& num) {
			if(r - l == 1) {
				if(l < SZ(ans)) ans[l] = num.at(0);
			} else {
				int m = (l + r) / 2;
				work(2 * p, l, m, num.mulT(q[2 * p + 1]).modxk(m - l));
				work(2 * p + 1, m, r, num.mulT(q[2 * p]).modxk(r - m));
			}
		};
		work(1, 0, n, mulT(q[1].inv(n)));
		return ans;
	}
};
