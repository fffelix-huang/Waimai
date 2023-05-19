template<int ALPHABET = 26, char MIN_CHAR = 'a'>
struct ac_automaton {
	struct Node {
		int fail = 0, cnt = 0;
		array<int, ALPHABET> go{};
	};
	vector<Node> node;
	vi que;
	int new_node() { return node.eb(), SZ(node) - 1; }
	Node& operator[](int i) { return node[i]; }
	ac_automaton() { new_node(); }
	int insert(const string& s) {
		int p = 0;
		for(char c : s) {
			int v = c - MIN_CHAR;
			if(node[p].go[v] == 0) node[p].go[v] = new_node();
			p = node[p].go[v];
		}
		node[p].cnt++;
		return p;
	}
	void build() {
		que.reserve(SZ(node)); que.pb(0);
		REP(i, SZ(que)) {
			int u = que[i];
			REP(j, ALPHABET) {
				if(node[u].go[j] == 0) node[u].go[j] = node[node[u].fail].go[j];
				else {
					int v = node[u].go[j];
					node[v].fail = (u == 0 ? u : node[node[u].fail].go[j]);
					que.pb(v);
				}
			}
		}
	}
};
