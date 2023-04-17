inline ull rng() {
	static ull Q = 48763;
	Q ^= Q << 7;
	Q ^= Q >> 9;
	return Q & 0xFFFFFFFFULL;
}