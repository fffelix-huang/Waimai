clock_t T1 = clock();
double getCurrentTime() { return (double) (clock() - T1) / CLOCKS_PER_SEC; }
