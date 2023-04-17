// Example: 1 -> 2, 4 -> 8, 12(1100) -> 17(10001)
ll next_combination(ll comb) {
	ll x = comb & -comb, y = comb + x;
	return ((comb & ~y) / x >> 1) | y;
}