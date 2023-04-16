bool cmp(P a, P b) {
	#define ng(k) (sign(k.Y) < 0 || (sign(k.Y) == 0 && sign(k.X) < 0))
	int A = ng(a), B = ng(b);
	if(A != B) return A < B;
	if(sign(cross(a, b)) == 0) return abs2(a) < abs2(b);
	return sign(cross(a, b)) > 0;
}