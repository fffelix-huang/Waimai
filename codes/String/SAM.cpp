// cnt 要先用 bfs 往回推, 第一次出現的位置是 state.first_pos - |S| + 1
struct Node { int go[26] = {}, len, link, cnt, first_pos; };
Node SA[N]; int sz;
void sa_init() { SA[0].link = -1, SA[0].len = 0, sz = 1; }
int sa_extend(int p, int c) {
	int u = sz++;
	SA[u].first_pos = SA[u].len = SA[p].len + 1;
	SA[u].cnt = 1;
	while(p != -1 && SA[p].go[c] == 0) {
		SA[p].go[c] = u;
		p = SA[p].link;
	}
	if(p == -1) {
		SA[u].link = 0;
		return u;
	}
	int q = SA[p].go[c];
	if(SA[p].len + 1 == SA[q].len) {
		SA[u].link = q;
		return u;
	}
	int x = sz++;
	SA[x] = SA[q];
	SA[x].cnt = 0;
	SA[x].len = SA[p].len + 1;
	SA[q].link = SA[u].link = x;
	while(p != -1 && SA[p].go[c] == q) {
		SA[p].go[c] = x;
		p = SA[p].link;
	}
	return u;
}