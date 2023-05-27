void CDQ(int l, int r) {
	if(l + 1 == r) return;
	int mid = (l + r) / 2;
	CDQ(l, mid), CDQ(mid, r);
	int i = l;
	for(int j = mid; j < r; j++) {
		const Q& q = qry[j];
		while(i < mid && qry[i].x >= q.x) {
			if(qry[i].id == -1) fenw.add(qry[i].y, qry[i].w);
			i++;
		}
		if(q.id >= 0) ans[q.id] += q.w * fenw.sum(q.y, sz - 1);
	}
	for(int p = l; p < i; p++) if(qry[p].id == -1) fenw.add(qry[p].y, -qry[p].w);
	inplace_merge(qry.begin() + l, qry.begin() + mid, qry.begin() + r, [](const Q& a, const Q& b) {
		return a.x > b.x;
	});
}