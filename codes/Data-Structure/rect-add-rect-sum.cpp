template<class Int, class T>
struct RectangleAddRectangleSum {
	struct AQ { Int xl, xr, yl, yr; T val; };
	struct SQ { Int xl, xr, yl, yr; };
	vector<AQ> add_qry;
	vector<SQ> sum_qry;
	// A[x][y] += val for(x, y) in [xl, xr) * [yl, yr)
	void add_rectangle(Int xl, Int xr, Int yl, Int yr, T val) { add_qry.pb({xl, xr, yl, yr, val}); }
	// Get sum of A[x][y] for(x, y) in [xl, xr) * [yl, yr)
	void add_query(Int xl, Int xr, Int yl, Int yr) { sum_qry.pb({xl, xr, yl, yr}); }
	vector<T> solve() {
		vector<Int> ys;
		for(auto &a : add_qry) ys.pb(a.yl), ys.pb(a.yr);
		ys = sort_unique(ys);
		const int Y = SZ(ys);
		vector<tuple<Int, int, int>> ops;
		REP(q, SZ(sum_qry)) {
			ops.eb(sum_qry[q].xl, 0, q);
			ops.eb(sum_qry[q].xr, 1, q);
		}
		REP(q, SZ(add_qry)) {
			ops.eb(add_qry[q].xl, 2, q);
			ops.eb(add_qry[q].xr, 3, q);
		}
		sort(ALL(ops));
		fenwick<T> b00(Y), b01(Y), b10(Y), b11(Y);
		vector<T> ret(SZ(sum_qry));
		for(auto o : ops) {
			int qtype = get<1>(o), q = get<2>(o);
			if(qtype >= 2) {
				const auto& query = add_qry[q];
				int i = lower_bound(ALL(ys), query.yl) - ys.begin();
				int j = lower_bound(ALL(ys), query.yr) - ys.begin();
				T x = get<0>(o);
				T yi = query.yl, yj = query.yr;
				if(qtype & 1) swap(i, j), swap(yi, yj);
				b00.add(i, x * yi * query.val);
				b01.add(i, -x * query.val);
				b10.add(i, -yi * query.val);
				b11.add(i, query.val);
				b00.add(j, -x * yj * query.val);
				b01.add(j, x * query.val);
				b10.add(j, yj * query.val);
				b11.add(j, -query.val);
			} else {
				const auto& query = sum_qry[q];
				int i = lower_bound(ALL(ys), query.yl) - ys.begin();
				int j = lower_bound(ALL(ys), query.yr) - ys.begin();
				T x = get<0>(o);
				T yi = query.yl, yj = query.yr;
				if(qtype & 1) swap(i, j), swap(yi, yj);
				ret[q] += b00.get(i - 1) + b01.get(i - 1) * yi + b10.get(i - 1) * x + b11.get(i - 1) * x * yi;
				ret[q] -= b00.get(j - 1) + b01.get(j - 1) * yj + b10.get(j - 1) * x + b11.get(j - 1) * x * yj;
			}
		}
		return ret;
	}
};