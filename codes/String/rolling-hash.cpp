const ll M = 911382323, mod = 972663749;
ll Get(vector<ll>& v, int l, int r) {
	if(!l) return h[r]; // p[i] = M^i % mod
	ll ans = (h[r] - h[l - 1] * p[r - l + 1]) % mod;
	return (ans + mod) % mod;
}
vector<ll> Hash(string s) {
	vector<ll> ans(sz(s));
	ans[0] = s[0];
	for(int i = 1; i < sz(s); i++) ans[i] = (ans[i - 1] * M + s[i]) % mod;
	return ans;
}