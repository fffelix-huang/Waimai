#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,inline
inline char gc() {
	static const size_t sz = 65536;
	static char buf[sz];
	static char *p = buf, *end = buf;
	if(p == end) end = buf + fread(buf, 1, sz, stdin), p = buf;
	return *p++;
}