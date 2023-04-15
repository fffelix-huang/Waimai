// Can correctly work with numbers in range [0; MAXN]
// Supports all std::set operations in O(1) on random queries / dense arrays, O(log_64(N)) in worst case (sparce array).
// Count operation works in O(1) always.
template<uint MAXN>
class fast_set {
private:
	static const uint PREF = (MAXN <= 64 ? 0 :
							  MAXN <= 4096 ? 1 :
							  MAXN <= 262144 ? 1 + 64 :
							  MAXN <= 16777216 ? 1 + 64 + 4096 :
							  MAXN <= 1073741824 ? 1 + 64 + 4096 + 262144 : 227) + 1;
	static constexpr ull lb(int x) {
		if(x == 64) return ULLONG_MAX;
		return (1ULL << x) - 1;
	};
	static const uint SZ = PREF + (MAXN + 63) / 64 + 1;
	ull m[SZ] = {0};
	inline uint left(uint v) const { return (v - 62) * 64; }
	inline uint parent(uint v) const { return v / 64 + 62; }
	inline void setbit(uint v) { m[v >> 6] |= 1ULL << (v & 63); }
	inline void resetbit(uint v) { m[v >> 6] &= ~(1ULL << (v & 63)); }
	inline uint getbit(uint v) const { return m[v >> 6] >> (v & 63) & 1; }
	inline ull childs_value(uint v) const { return m[left(v) >> 6]; }
	inline int left_go(uint x, const uint c) const {
		const ull rem = x & 63;
		uint bt = PREF * 64 + x;
		ull num = m[bt >> 6] & lb(rem + c);
		if(num) return (x ^ rem) | __lg(num);
		for(bt = parent(bt); bt > 62; bt = parent(bt)) {
			const ull rem = bt & 63;
			num = m[bt >> 6] & lb(rem);
			if(num) {
				bt = (bt ^ rem) | __lg(num);
				break;
			}
		}
		if(bt == 62) return -1;
		while(bt < PREF * 64) bt = left(bt) | __lg(m[bt - 62]);
		return bt - PREF * 64;
	}
	inline int right_go(uint x, const uint c) const {
		const ull rem = x & 63;
		uint bt = PREF * 64 + x;
		ull num = m[bt >> 6] & ~lb(rem + c);
		if(num) return (x ^ rem) | __builtin_ctzll(num);
		for(bt = parent(bt); bt > 62; bt = parent(bt)) {
			const ull rem = bt & 63;
			num = m[bt >> 6] & ~lb(rem + 1);
			if(num) {
				bt = (bt ^ rem) | __builtin_ctzll(num);
				break;
			}
		}
		if(bt == 62) return -1;
		while(bt < PREF * 64) bt = left(bt) | __builtin_ctzll(m[bt - 62]);
		return bt - PREF * 64;
	}
 
public:
	fast_set() { assert(PREF != 228); setbit(62); }
	bool empty() const {return getbit(63);}
	void clear() { fill(m, m + SZ, 0); setbit(62); }
	bool count(uint x) const { return m[PREF + (x >> 6)] >> (x & 63) & 1; }
	void insert(uint x) { for(uint v = PREF * 64 + x; !getbit(v); v = parent(v)) setbit(v); }
	void erase(uint x) {
		if(!getbit(PREF * 64 + x)) return;
		resetbit(PREF * 64 + x);
		for(uint v = parent(PREF * 64 + x); v > 62 && !childs_value(v); v = parent(v)) resetbit(v);
	}
	int find_next(uint x) const { return right_go(x, 0); } // >=
	int find_prev(uint x) const { return left_go(x, 1); } // <=
};
