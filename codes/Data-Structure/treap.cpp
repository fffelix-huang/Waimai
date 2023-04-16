struct Node {
	bool rev = false;
	int sz = 1, pri = rng();
 	Node *l = NULL, *r = NULL, *p = NULL;
 	// TODO
}
void pull(Node*& v) {
	v->sz = 1 + size(v->l) + size(v->r);
	// TODO
}
void push(Node*& v) {
	if(v->rev) {
		swap(v->l, v->r);
		if(v->l) v->l->rev ^= 1;
		if(v->r) v->r->rev ^= 1;
		v->rev = false;
	}
}
Node* merge(Node* a, Node* b) {
	if(!a || !b) return (a ? a : b);
	push(a), push(b);
	if(a->pri > b->pri) {
		a->r = merge(a->r, b);
		pull(a); return a;
	} else {
		b->l = merge(a, b->l);
		pull(b); return b;
	}
}
pair<Node*, Node*> split(Node* v, int k) {
	if(!v) return {NULL, NULL};
	push(v);
	if(size(v->l) >= k) {
		auto p = split(v->l, k);
		if(p.first) p.first->p = NULL;
		v->l = p.second;
		pull(v); return {p.first, v};
	} else {
		auto p = split(v->r, k - size(v->l) - 1);
		if(p.second) p.second->p = NULL;
		v->r = p.first;
		pull(v); return {v, p.second};
	}
}
int get_position(Node* v) { // 0-indexed
	int k = (v->l != NULL ? v->l->sz : 0);
	while(v->p != NULL) {
		if(v == v->p->r) {
			k++;
			if(v->p->l != NULL) k += v->p->l->sz;
		}
		v = v->p;
	}
	return k;
}