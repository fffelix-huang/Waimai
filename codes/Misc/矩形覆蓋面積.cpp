const int N = 2e6 + 5; // [-1e6, 1e6]
int tag[N * 4], seg[N * 4];
void pull(int v, int l, int r) {
	seg[v] = 0;
	if(tag[v] > 0) seg[v] = r - l + 1;
	else if(l < r) seg[v] = seg[v * 2] + seg[v * 2 + 1];
}
void update(int ql, int qr, int x, int v = 1, int l = 0, int r = N - 1) {
	if(ql > r || qr < l) return;
	if(ql <= l && r <= qr) {
		tag[v] += x;
	} else {
		int m = (l + r) / 2;
		update(ql, qr, x, v * 2, l, m);
		update(ql, qr, x, v * 2 + 1, m + 1, r);
	}
	pull(v, l, r);
}
int main() {
	int n; cin >> n;
	vector<array<int, 4>> ev(2 * n);
	REP(i, n) {
		int x, y, x2, y2;
		cin >> x >> y >> x2 >> y2;
		x += N / 2; y += N / 2;
		x2 += N / 2; y2 += N / 2;
		ev[2 * i] = {x, y, y2, +1};
		ev[2 * i + 1] = {x2, y, y2, -1};
	}
	sort(all(ev));
	ll ans = 0, prev = 0;
	REP(i, 2 * n) {
		ans += (ev[i][0] - prev) * seg[1];
		int j = i;
		while(j < 2 * n && ev[i][0] == ev[j][0]) {
			update(ev[j][1], ev[j][2] - 1, ev[j][3]);
			j++;
		}
		prev = ev[i][0], i = j - 1;
	}
	cout << ans << "\n";
}