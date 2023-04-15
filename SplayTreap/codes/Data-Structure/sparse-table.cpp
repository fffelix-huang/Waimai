template<class T, T (*op)(T, T)>
class sparse_table {
public:
	sparse_table() {}
	sparse_table(const vector<T>& a) : n(a.size()) {
		int max_log = __lg(n) + 1;
		mat.resize(max_log);
		mat[0] = a;
		for(int j = 1; j < max_log; ++j) {
			mat[j].resize(n - (1 << j) + 1);
			for(int i = 0; i <= n - (1 << j); ++i) {
				mat[j][i] = op(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
	T prod(int from, int to) const {
		assert(0 <= from && from <= to && to <= n - 1);
		int lg = __lg(to - from + 1);
		return op(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
	}
	
private:
	int n;
	vector<vector<T>> mat;
};
