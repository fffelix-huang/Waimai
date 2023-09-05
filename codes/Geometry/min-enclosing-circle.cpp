pdd excenter(pdd x, pdd y, pdd z) {
	#define f(x, y) (x*x+y*y)
	auto [x1, y1] = x;
	auto [x2, y2] = y;
	auto [x3, y3] = z;
	double d1 = f(x2, y2) - f(x1, y1), d2 = f(x3, y3) - f(x2, y2);
	double fm = 2 * ((y3 - y2) * (x2 - x1) - (y2 - y1) * (x3 - x2));
	double ans_x =((y3 - y2) * d1 - (y2 - y1) * d2) / fm;
	double ans_y =((x2 - x1) * d2 - (x3 - x2) * d1) / fm;
	#undef f
	return {ans_x, ans_y};
}

pdd min_enclosing_circle(vector<pdd> dots, double& r) {
	random_shuffle(ALL(dots));
	pdd C = dots[0];
	r = 0;
	#define check(i, j) REP(i, j) if(abs(dots[i] - C) > r)
	check(i, SZ(dots)) {
		C = dots[i], r = 0;
		check(j, i) {
			C = (dots[i] + dots[j]) / 2.0;
			r = abs(dots[i] - C);
			check(k, j) {
				C = excenter(dots[i], dots[j], dots[k]);
				r = abs(dots[i] - C);
			}
		}
	}
	#undef check
	return C;
}
