template<class Func, bool MAX>
ll Aliens(ll l, ll r, int k, Func f) {
	while(l < r) {
		ll m = l + (r - l) / 2;
		auto [score, op] = f(m);
		if(op == k) return score + m * k * (MAX ? +1 : -1);
		if(op < k) r = m;
		else l = m + 1;
	}
	return f(l).first + l * k * (MAX ? +1 : -1);
}
