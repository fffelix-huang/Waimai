using P = pair<ll, ll>;
P operator+(P a, P b) { return P{a.X + b.X, a.Y + b.Y}; }
P operator-(P a, P b) { return P{a.X - b.X, a.Y - b.Y}; }
P operator*(P a, ll b) { return P{a.X * b, a.Y * b}; }
P operator/(P a, ll b) { return P{a.X / b, a.Y / b}; }
ll dot(P a, P b) { return a.X * b.X + a.Y * b.Y; }
ll cross(P a, P b) { return a.X * b.Y - a.Y * b.X; }
ll abs2(P a) { return dot(a, a); }
double abs(P a) { return sqrt(abs2(a)); }
int sign(ll x) { return x < 0 ? -1 : (x == 0 ? 0 : 1); }
int ori(P a, P b, P c) { return sign(cross(b - a, c - a)); }
bool collinear(P a, P b, P c) { return sign(cross(a - c, b - c)) == 0; }
bool btw(P a, P b, P c) {
	if(!collinear(a, b, c)) return 0;
	return sign(dot(a - c, b - c)) <= 0;
}
bool seg_intersect(P a, P b, P c, P d) {
	int a123 = ori(a, b, c);
	int a124 = ori(a, b, d);
	int a341 = ori(c, d, a);
	int a342 = ori(c, d, b);
	if(a123 == 0 && a124 == 0) {
		return btw(a, b, c) || btw(a, b, d) || btw(c, d, a) || btw(c, d, b);
	}
	return a123 * a124 <= 0 && a341 * a342 <= 0;
}

P intersect(P a, P b, P c, P d) {
	int a123 = cross(b - a, c - a);
	int a124 = cross(b - a, d - a);
	return (d * a123 - c * a124) / (a123 - a124);
}
struct line { P A, B; };
P vec(line L) { return L.B - L.A; }
P projection(P p, line L) { return L.A + vec(L) / abs(vec(L)) * dot(p - L.A, vec(L)) / abs(vec(L)); }