#define MEM(a, x, n) memset(a, x, sizeof(int) * n)
using I = int*;
struct static_range_lis {
	int n, ps = 0;
	I invp, res_monge, pool;
	vector<vector<pii>> qry;
	vi ans;
	static_range_lis(vi a) : n(SZ(a)), qry(n + 1) {
		// a must be permutation of [0, n)
		pool = (I) malloc(sizeof(int) * n * 100);
		invp = A(n), res_monge = A(n);
		REP(i, n) invp[a[i]] = i;
	}
	inline I A(int x) { return pool + (ps += x) - x; }
	void add_query(int l, int r) { qry[l].pb({r, SZ(ans)}), ans.pb(r - l); }
	void unit_monge_mult(I a, I b, I r, int n) {
		if(n == 2){
			if(!a[0] && !b[0]) r[0] = 0, r[1] = 1;
			else r[0] = 1, r[1] = 0;
			return;
		}
		if(n == 1) return r[0] = 0, void();
		int lps = ps, d = n / 2;
		I a1 = A(d), a2 = A(n - d), b1 = A(d), b2 = A(n - d);
		I mpa1 = A(d), mpa2 = A(n - d), mpb1 = A(d), mpb2 = A(n - d);
		int p[2] = {};
		REP(i, n) {
			if(a[i] < d) a1[p[0]] = a[i], mpa1[p[0]++] = i;
			else a2[p[1]] = a[i] - d, mpa2[p[1]++] = i;
		}
		p[0] = p[1] = 0;
		REP(i, n) {
			if(b[i] < d) b1[p[0]] = b[i], mpb1[p[0]++] = i;
			else b2[p[1]] = b[i] - d, mpb2[p[1]++] = i;
		}
		I c1 = A(d), c2 = A(n - d);
		unit_monge_mult(a1, b1, c1, d), unit_monge_mult(a2, b2, c2, n - d);
		I cpx = A(n), cpy = A(n), cqx = A(n), cqy = A(n);
		REP(i, d) cpx[mpa1[i]] = mpb1[c1[i]], cpy[mpa1[i]]=0;
		REP(i, n - d) cpx[mpa2[i]] = mpb2[c2[i]], cpy[mpa2[i]]=1;
		REP(i, n) r[i] = cpx[i];
		REP(i, n) cqx[cpx[i]] = i, cqy[cpx[i]] = cpy[i];
		int hi = n, lo = n, his = 0, los = 0;
		REP(i, n) {
			if(cqy[i] ^ (cqx[i] >= hi)) his--;
			while(hi > 0 && his < 0) {
				hi--;
				if(cpy[hi] ^ (cpx[hi] > i)) his++;
			}
			while(lo > 0 && los <= 0) {
				lo--;
				if(cpy[lo] ^ (cpx[lo] >= i)) los++;
			}
			if(los > 0 && hi == lo) r[lo] = i;
			if(cqy[i] ^ (cqx[i] >= lo)) los--;
		}
		ps = lps;
	}
	void subunit_monge_mult(I a, I b, I c, int n) {
		int lps = ps;
		I za = A(n), zb = A(n), res = A(n), vis = A(n), mpa = A(n), mpb = A(n), rb = A(n);
		MEM(vis, 0, n), MEM(mpa, -1, n), MEM(mpb, -1, n), MEM(rb, -1, n);
		int ca = n;
		IREP(i, n) if(a[i] != -1) vis[a[i]] = 1, za[--ca] = a[i], mpa[ca] = i;
		IREP(i, n) if(!vis[i]) za[--ca] = i;
		MEM(vis, -1, n);
		REP(i, n) if(b[i] != -1) vis[b[i]] = i;
		ca = 0;
		REP(i, n) if(vis[i] != -1) mpb[ca] = i, rb[vis[i]] = ca++;
		REP(i, n) if(rb[i] == -1) rb[i] = ca++;
		REP(i, n) zb[rb[i]] = i;
		unit_monge_mult(za, zb, res, n);
		MEM(c, -1, n);
		REP(i, n) if(mpa[i] != -1 && mpb[res[i]] != -1) c[mpa[i]] = mpb[res[i]];
		ps = lps;
	}
	void solve(I p, I ret, int n) {
		if(n == 1) return ret[0] = -1, void();
		int lps = ps, d = n / 2;
		I pl = A(d), pr = A(n - d);
		REP(i, d) pl[i] = p[i];
		REP(i, n - d) pr[i] = p[i + d];
		I vis = A(n); MEM(vis, -1, n);
		REP(i, d) vis[pl[i]] = i;
		I tl = A(d), tr = A(n - d), mpl = A(d), mpr = A(n - d);
		int ca = 0;
		REP(i, n) if(vis[i] != -1) mpl[ca] = i, tl[vis[i]] = ca++;
		ca = 0; MEM(vis, -1, n);
		REP(i, n - d) vis[pr[i]] = i;
		REP(i, n) if(vis[i] != -1) mpr[ca] = i, tr[vis[i]] = ca++;
		I vl = A(d), vr = A(n - d);
		solve(tl, vl, d), solve(tr, vr, n - d);
		I sl = A(n), sr = A(n);
		iota(sl, sl + n, 0); iota(sr, sr + n, 0);
		REP(i, d) sl[mpl[i]] = (vl[i] == -1 ? -1 : mpl[vl[i]]);
		REP(i, n - d) sr[mpr[i]] = (vr[i] == -1 ? -1 : mpr[vr[i]]);
		subunit_monge_mult(sl, sr, ret, n);
		ps = lps;
	}
	vi solve() {
		solve(invp, res_monge, n);
		vi fenw(n + 1);
		IREP(i, n) {
			if(res_monge[i] != -1) {
				for(int p = res_monge[i] + 1; p <= n; p += p & -p) fenw[p]++;
			}
			for(auto& z : qry[i]){
				auto [id, c] = z;
				for(int p = id; p; p -= p & -p) ans[c] -= fenw[p];
			}
		}
		free(pool);
		return ans;
	}
};
