template<class T>
struct DinicLowerBound {
	using Maxflow = Dinic<T>;
	int n;
	Maxflow d;
	vector<T> in;
	DinicLowerBound(int _n) : n(_n), d(_n + 2), in(_n) {}
	int add_edge(int from, int to, T low, T high) {
		assert(0 <= low && low <= high);
		in[from] -= low, in[to] += low;
		return d.add_edge(from, to, high - low);
	}
	T flow(int s, int t) {
		T sum = 0;
		REP(i, n) {
			if(in[i] > 0) {
				d.add_edge(n, i, in[i]);
				sum += in[i];
			}
			if(in[i] < 0) d.add_edge(i, n + 1, -in[i]);
		}
		d.add_edge(t, s, numeric_limits<T>::max());
		if(d.flow(n, n + 1) < sum) return -1;
		return d.flow(s, t);
	}
};
