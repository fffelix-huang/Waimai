// 0 <= i <= n - m に対し、s[i, i + m) == t かどうか
// abc*b*a***a
// *b*a
// 10111011
template<class T, class U = modint998244353>
vector<bool> wildcard_matching(const vector<T> &s, const vector<T> &t, T wildcard) {
    const int n = s.size(), m = t.size();
    vector<U> s1(n), s2(n), s3(n), t1(m), t2(m), t3(m);
    REP(i, n) {
        s1[i] = s[i] == wildcard ? 0 : s[i] == 0 ? wildcard : s[i];
        s2[i] = s1[i] * s1[i], s3[i] = s2[i] * s1[i];
    }
    REP(j, m) {
        t1[j] = t[m - 1 - j] == wildcard ? 0 : t[m - 1 - j] == 0 ? wildcard : t[m - 1 - j];
        t2[j] = t1[j] * t1[j], t3[j] = t2[j] * t1[j];
    }
    vector<U> u13 = convolution(s1, t3);
    vector<U> u22 = convolution(s2, t2);
    vector<U> u31 = convolution(s3, t1);
    vector<bool> res(n - m + 1);
    REP(i, n - m + 1) res[i] = u13[i + m - 1] - 2 * u22[i + m - 1] + u31[i + m - 1] == 0;
    return res;
}