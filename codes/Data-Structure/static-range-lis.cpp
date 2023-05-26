struct static_range_lis {
	int n;
	vector<vector<pii>> qry;
	vi invp, res_monge, ans;
	static_range_lis(vi a) : n(SZ(a)), qry(n + 1), invp(n), res_monge(n) {
		// a must be permutation of [0, n)
		REP(i, n) invp[a[i]] = i;
	}
	void add_query(int l, int r) { qry[l].pb({r, SZ(ans)}), ans.pb(r - l); }
	void unit_monge_mult(vi& a, vi& b, vi& r) {
		int n = SZ(a);
		if(n == 2){
			if(!a[0] && !b[0]) r[0] = 0, r[1] = 1;
			else r[0] = 1, r[1] = 0;
			return;
		}
		if(n == 1) return r[0] = 0, void();
		int d = n / 2;
		vi a1(d), a2(n - d), b1(d), b2(n - d);
		vi mpa1(d), mpa2(n - d), mpb1(d), mpb2(n - d);
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
		vi c1(d), c2(n - d);
		unit_monge_mult(a1, b1, c1), unit_monge_mult(a2, b2, c2);
		vi cpx(n), cpy(n), cqx(n), cqy(n);
		REP(i, d) cpx[mpa1[i]] = mpb1[c1[i]], cpy[mpa1[i]] = 0;
		REP(i, n - d) cpx[mpa2[i]] = mpb2[c2[i]], cpy[mpa2[i]] = 1;
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
	}
	void subunit_monge_mult(vi& a, vi& b, vi& c) {
		int n = SZ(a);
		vi za(n), zb(n), res(n), vis(n), mpa(n, -1), mpb(n, -1), rb(n, -1);
		int ca = n;
		IREP(i, n) if(a[i] != -1) vis[a[i]] = 1, za[--ca] = a[i], mpa[ca] = i;
		IREP(i, n) if(!vis[i]) za[--ca] = i;
		fill(ALL(vis), -1);
		REP(i, n) if(b[i] != -1) vis[b[i]] = i;
		ca = 0;
		REP(i, n) if(vis[i] != -1) mpb[ca] = i, rb[vis[i]] = ca++;
		REP(i, n) if(rb[i] == -1) rb[i] = ca++;
		REP(i, n) zb[rb[i]] = i;
		unit_monge_mult(za, zb, res);
		fill(ALL(c), -1);
		REP(i, n) if(mpa[i] != -1 && mpb[res[i]] != -1) c[mpa[i]] = mpb[res[i]];
	}
	void solve(vi& p, vi& ret) {
		int n = SZ(p);
		if(n == 1) return ret[0] = -1, void();
		int d = n / 2;
		vi pl(d), pr(n - d);
		REP(i, d) pl[i] = p[i];
		REP(i, n - d) pr[i] = p[i + d];
		vi vis(n, -1);
		REP(i, d) vis[pl[i]] = i;
		vi tl(d), tr(n - d), mpl(d), mpr(n - d);
		int ca = 0;
		REP(i, n) if(vis[i] != -1) mpl[ca] = i, tl[vis[i]] = ca++;
		ca = 0;
		fill(ALL(vis), -1);
		REP(i, n - d) vis[pr[i]] = i;
		REP(i, n) if(vis[i] != -1) mpr[ca] = i, tr[vis[i]] = ca++;
		vi vl(d), vr(n - d);
		solve(tl, vl), solve(tr, vr);
		vi sl(n), sr(n);
		iota(ALL(sl), 0), iota(ALL(sr), 0);
		REP(i, d) sl[mpl[i]] = (vl[i] == -1 ? -1 : mpl[vl[i]]);
		REP(i, n - d) sr[mpr[i]] = (vr[i] == -1 ? -1 : mpr[vr[i]]);
		subunit_monge_mult(sl, sr, ret);
	}
	vi solve() {
		solve(invp, res_monge);
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
		return ans;
	}
};
