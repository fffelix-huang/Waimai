vector<vector<T>> rotate90(const vector<vector<T>>& a) {
    int n = sz(a), m = sz(a[0]);
    vector<vector<T>> b(m, vector<T>(n));
    REP(i, n) REP(j, m) b[j][i] = a[i][m - 1 - j];
    return b;
}