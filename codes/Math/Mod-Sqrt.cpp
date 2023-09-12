// return -1 if sqrt DNE
ll mod_sqrt(ll a, ll mod) {
	a %= mod;
	if(mod == 2 || a < 2) return a;
	if(mod_pow(a, (mod-1)/2, mod) != 1) return -1;
	ll b = 1;
	while(mod_pow(b, (mod-1)/2, mod) == 1) b++;
	int m = mod-1, e = __builtin_ctz(m);
	m >>= e;
	ll x = mod_pow(a, (m-1)/2, mod);
	ll y = a * x % mod * x % mod;
	x = x * a % mod;
	ll z = mod_pow(b, m, mod);
	while(y != 1) {
		int j = 0;
		ll t = y;
		while(t != 1) t = t * t % mod, j++;
		z = mod_pow(z, 1LL << (e - j - 1), mod);
		x = x*z%mod, z = z*z%mod, y = y*z%mod;
		e = j;
	}
	return min(x, mod-x); // neg is $mod-x$
}