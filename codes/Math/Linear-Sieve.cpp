vi primes, least = {0, 1}, phi, mobius;
void LinearSieve(int n) {
	least = phi = mobius = vi(n + 1);
	mobius[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!least[i]) {
			least[i] = i;
			primes.pb(i);
			phi[i] = i - 1;
			mobius[i] = -1;
		}
		for(auto j : primes) {
			if(i * j > n) break;
			least[i * j] = j;
			if(i % j == 0) {
				mobius[i * j] = 0;
				phi[i * j] = phi[i] * j;
				break;
			} else {
				mobius[i * j] = -mobius[i];
				phi[i * j] = phi[i] * phi[j];
			}
		}
	}
}
