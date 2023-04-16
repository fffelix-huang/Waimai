vector<int> lcp(const vector<int>& s, const vector<int>& sa) {
	int n = sz(s), h = 0;
	vi rnk(n), lcp(n - 1);
	REP(i, n) rnk[sa[i]] = i;
	REP(i, n) {
		h -= (h > 0);
		if(rnk[i] == 0) continue;
		int j = sa[rnk[i] - 1];
		for(; j + h < n && i + h < n; h++) if(s[j + h] != s[i + h]) break;
		lcp[rnk[i] - 1] = h;
	}
	return lcp;
}
