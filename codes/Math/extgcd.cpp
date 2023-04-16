// ax + by = gcd(a, b)
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	ll x1, y1;
	ll g = ext_gcd(b, a % b, x1, y1);
	x = y1, y = x1 - (a / b) * y1;
	return g;
}
