template<class S,
         S (*e)(),
         S (*op)(S, S),
         S (*reversal)(S),
         class F,
         F (*id)(),
         S (*mapping)(F, S),
         F (*composition)(F, F)>
struct lazy_lct {
	struct Node {
		S val = e(), sum = e();
		F lz = id();
		bool rev = false;
		int sz = 1;
		Node *l = nullptr, *r = nullptr, *p = nullptr;
		Node() {}
		Node(const S& s) : val(s), sum(s) {}
		bool is_root() const { return p == nullptr || (p->l != this && p->r != this); }
	};
	int n;
	vector<Node> a;
	lazy_lct() : n(0) {}
	explicit lazy_lct(int _n) : lazy_lct(vector<S>(_n, e())) {}
	explicit lazy_lct(const vector<S>& v) : n(SZ(v)) { REP(i, n) a.eb(v[i]); }
	Node* access(int u) {
		Node* v = &a[u];
		Node* last = nullptr;
		for(Node* p = v; p != nullptr; p = p->p) splay(p), p->r = last, pull(last = p);
		splay(v);
		return last;
	}
	void make_root(int u) { access(u), a[u].rev ^= 1, push(&a[u]); }
	void link(int u, int v) { make_root(v), a[v].p = &a[u]; }
	void cut(int u) {
		access(u);
		if(a[u].l != nullptr) a[u].l->p = nullptr, a[u].l = nullptr, pull(&a[u]);
	}
	void cut(int u, int v) { make_root(u), cut(v); }
	bool is_connected(int u, int v) {
		if(u == v) return true;
		return access(u), access(v), a[u].p != nullptr;
	}
	int get_lca(int u, int v) { return access(u), access(v) - &a[0]; }
	void set(int u, const S& s) { access(u), a[u].val = s, pull(&a[u]); }
	S get(int u) { return access(u), a[u].val; }
	void apply(int u, int v, const F& f) { make_root(u), access(v), all_apply(&a[v], f), push(&a[v]); }
	S prod(int u, int v) { return make_root(u), access(v), a[v].sum; }
	void rotate(Node* v) {
		auto attach = [&](Node* p, bool side, Node* c) {
			(side ? p->r : p->l) = c;
			pull(p);
			if(c != nullptr) c->p = p;
		};
		Node *p = v->p, *g = p->p;
		bool rgt = (p->r == v);
		bool rt = p->is_root();
		attach(p, rgt, (rgt ? v->l : v->r));
		attach(v, !rgt, p);
		if(!rt) attach(g, (g->r == p), v);
		else v->p = g;
	}
	void splay(Node* v) {
		push(v);
		while(!v->is_root()) {
			auto p = v->p;
			auto g = p->p;
			if(!p->is_root()) push(g);
			push(p), push(v);
			if(!p->is_root()) rotate((g->r == p) == (p->r == v) ? p : v);
			rotate(v);
		}
	}
	void all_apply(Node* v, F f) {
		v->val = mapping(f, v->val), v->sum = mapping(f, v->sum);
		v->lz = composition(f, v->lz);
	}
	void push(Node* v) {
		if(v->lz != id()) {
			if(v->l != nullptr) all_apply(v->l, v->lz);
			if(v->r != nullptr) all_apply(v->r, v->lz);
			v->lz = id();
		}
		if(v->rev) {
			swap(v->l, v->r);
			if(v->l != nullptr) v->l->rev ^= 1;
			if(v->r != nullptr) v->r->rev ^= 1;
			v->sum = reversal(v->sum);
			v->rev = false;
		}
	}
	void pull(Node* v) {
		v->sz = 1;
		v->sum = v->val;
		if(v->l != nullptr) {
			push(v->l);
			v->sum = op(v->l->sum, v->sum);
			v->sz += v->l->sz;
		}
		if(v->r != nullptr) {
			push(v->r);
			v->sum = op(v->sum, v->r->sum);
			v->sz += v->r->sz;
		}
	}
};
