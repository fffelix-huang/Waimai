// Counts x, y >= 0 such that Ax + By <= C. Requires A, B > 0. Runs in log time.
// Also representable as sum_{0 <= x <= C / A} floor((C - Ax) / B + 1).
ll count_triangle(ll A, ll B, ll C) {
    if(C < 0) return 0;
    if(A < B) swap(A, B);
    ll m = C / A, k = A / B;
    ll h = (C - m * A) / B + 1;
    return m * (m + 1) / 2 * k + (m + 1) * h + count_triangle(B, A - k * B, C - B * (k * m + h));
}
 
// Counts 0 <= x < RA, 0 <= y < RB such that Ax + By <= C. Requires A, B > 0.
ll count_triangle_rectangle_intersection(ll A, ll B, ll C, ll RA, ll RB) {
    if(C < 0 || RA <= 0 || RB <= 0) return 0;
    if(C >= A * (RA - 1) + B * (RB - 1)) return RA * RB;
    return count_triangle(A, B, C) - count_triangle(A, B, C - A * RA) - count_triangle(A, B, C - B * RB);
}