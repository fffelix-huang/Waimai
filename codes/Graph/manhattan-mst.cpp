template<class T> // [w, u, v]
vector<tuple<T, int, int>> manhattan_mst(vector<T> xs, vector<T> ys) {
    const int n = SZ(xs);
    vi idx(n);
    iota(ALL(idx), 0);
    vector<tuple<T, int, int>> ret;
    REP(s, 2) {
        REP(t, 2) {
            auto cmp = [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; };
            sort(ALL(idx), cmp);
            map<T, int> sweep;
            for(int i : idx) {
                for(auto it = sweep.lower_bound(-ys[i]); it != sweep.end(); it = sweep.erase(it)) {
                    int j = it->second;
                    if(xs[i] - xs[j] < ys[i] - ys[j]) break;
                    ret.eb(abs(xs[i] - xs[j]) + abs(ys[i] - ys[j]), i, j);
                }
                sweep[-ys[i]] = i;
            }
            swap(xs, ys);
        }
        for(auto &x : xs) x = -x;
    }
    sort(ALL(ret));
    return ret;
}