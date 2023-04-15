ll floor_div(ll a, ll b) {
	return a/b - ((a^b) < 0 && a%b != 0);
}
ll ceil_div(ll a, ll b) {
	return a/b + ((a^b) > 0 && a%b != 0);
}