// (rem, mod) {0, 0} for no solution
pair<ll, ll> crt(ll r0, ll m0, ll r1, ll m1) {
	r0 = (r0 % m0 + m0) % m0;
	r1 = (r1 % m1 + m1) % m1;
	if(m0 < m1) swap(r0, r1), swap(m0, m1);
	if(m0 % m1 == 0) {
		if(r0 % m1 != r1) return {0, 0};
	}
	ll g, im, qq;
	g = ext_gcd(m0, m1, im, qq);
	ll u1 = (m1 / g);
	if((r1 - r0) % g) return {0, 0};
	ll x = (r1 - r0) / g % u1 * im % u1;
	r0 += x * m0;
	m0 *= u1;
	if(r0 < 0) r0 += m0;
	return {r0, m0};
}
