struct DLX {
	int n, m, tot, ans;
	vi first, siz, L, R, U, D, col, row, stk;
	DLX(int _n, int _m) : n(_n), m(_m), tot(_m) {
		int sz = n * m;
		first = siz = L = R = U = D = col = row = stk = vi(sz);
		REP(i, m + 1) {
			L[i] = i - 1, R[i] = i + 1;
			U[i] = D[i] = i;
		}
		L[0] = m, R[m] = 0;
	}
	void insert(int r, int c) { // (r, c) is 1
		r++, c++;
		col[++tot] = c, row[tot] = r, ++siz[c];
		D[tot] = D[c], U[D[c]] = tot, U[tot] = c, D[c] = tot;
		if(!first[r]) first[r] = L[tot] = R[tot] = tot;
		else {
			L[R[tot] = R[first[r]]] = tot;
			R[L[tot] = first[r]] = tot;
		}
	}
	#define TRAV(i, X, j) for(i = X[j]; i != j; i = X[i])
	void remove(int c) {
		int i, j;
		L[R[c]] = L[c], R[L[c]] = R[c];
		TRAV(i, D, c) TRAV(j, R, i) {
			D[U[D[j]] = U[j]] = D[j];
			siz[col[j]]--;
		}
	}
	void recover(int c) {
		int i, j;
		TRAV(i, U, c) TRAV(j, L, i) {
			U[D[j]] = D[U[j]] = j;
			siz[col[j]]++;
		}
		L[R[c]] = R[L[c]] = c;
	}
	bool dance(int dep) {
		if(!R[0]) return ans = dep, true;
		int i, j, c = R[0];
		TRAV(i, R, 0) if(siz[i] < siz[c]) c = i;
		remove(c);
		TRAV(i, D, c) {
			stk[dep] = row[i];
			TRAV(j, R, i) remove(col[j]);
			if(dance(dep + 1)) return true;
			TRAV(j, L, i) recover(col[j]);
		}
		recover(c);
		return false;
	}
	vi solve() {
		if(!dance(1)) return {};
		return vi(stk.begin() + 1, stk.begin() + ans);
	}
};
