/*
 * Description: Solves a general linear maximization problem: maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
 * Returns -inf if there is no solution, inf if there are arbitrarily good solutions, or the maximum value of $c^T x$ otherwise.
 * The input vector is set to an optimal $x$ (or in the unbounded case, an arbitrary solution fulfilling the constraints).
 * Numerical stability is not guaranteed. For better performance, define variables such that $x = 0$ is viable.
 * Usage:
 * vvd A = {{1,-1}, {-1,1}, {-1,-2}};
 * vd b = {1,1,-4}, c = {-1,-1}, x;
 * T val = LPSolver(A, b, c).solve(x);
 * Time: O(NM * \#pivots), where a pivot may be e.g. an edge relaxation. O(2^n) in the general case.
 *
 * 將最小化改成最大化 -> 去除等式 -> 去除大於等於 -> 去除自由變數，將 x1 用 x1−x3 取代
*/
typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

struct LP {
	const T eps = 1e-8, inf = 1/.0;
	#define MP make_pair
	#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j
	int m, n;
	vi N, B;
	vvd D;
	LP(const vvd& A, const vd& b, const vd& c) : m(SZ(b)), n(SZ(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
		REP(i, m) REP(j, n) D[i][j] = A[i][j];
		REP(i, m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
		REP(j, n) { N[j] = j; D[m][j] = -c[j]; }
		N[n] = -1; D[m+1][n] = 1;
	}
	void pivot(int r, int s) {
		T *a = D[r].data(), inv = 1 / a[s];
		REP(i, m + 2) if(i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			REP(j, n + 2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		REP(j, n + 2) if(j != s) D[r][j] *= inv;
		REP(i, m + 2) if(i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}
	bool simplex(int phase) {
		int x = m + phase - 1;
		while(true) {
			int s = -1;
			REP(j, n + 1) if(N[j] != -phase) ltj(D[x]);
			if(D[x][s] >= -eps) return true;
			int r = -1;
			REP(i, m) {
				if(D[i][s] <= eps) continue;
				if(r == -1 || MP(D[i][n+1] / D[i][s], B[i]) < MP(D[r][n+1] / D[r][s], B[r])) r = i;
			}
			if(r == -1) return false;
			pivot(r, s);
		}
	}
	T solve(vd &x) {
		int r = 0;
		FOR(i, 1, m) if(D[i][n+1] < D[r][n+1]) r = i;
		if(D[r][n+1] < -eps) {
			pivot(r, n);
			if(!simplex(2) || D[m+1][n+1] < -eps) return -inf;
			REP(i, m) if(B[i] == -1) {
				int s = 0;
				FOR(j, 1, n + 1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		REP(i, m) if(B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};
