const ll M30 = (1LL << 30) - 1;
const ll M31 = (1LL << 31) - 1;
const ll M61 = (1LL << 61) - 1;
ull modulo(ull x){
	ull xu = x >> 61;
	ull xd = x & M61;
	ull res = xu + xd;
	if(res >= M61) res -= M61;
	return res;
}
ull mul(ull a, ull b){
	ull au = a >> 31, ad = a & M31;
	ull bu = b >> 31, bd = b & M31;
	ull mid = au * bd + ad * bu;
	ull midu = mid >> 30;
	ull midd = mid & M30;
	return modulo(au * bu * 2 + midu + (midd << 31) + ad * bd);
}