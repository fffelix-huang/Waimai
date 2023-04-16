// length: (z[i] - (i & 1)) / 2 * 2 + (i & 1)
vi manacher(string t) {
	string s = "&";
	for(char c : t) s.pb(c), s.pb('%');
	int l = 0, r = 0;
	vi z(sz(s));
	REP(i, sz(s)) {
		z[i] = r > i ? min(z[2 * l - i], r - i) : 1;
		while(s[i + z[i]] == s[i - z[i]]) z[i]++;
		if(z[i] + i > r) r = z[i] + 1, l = i;
	}
	return z;
}