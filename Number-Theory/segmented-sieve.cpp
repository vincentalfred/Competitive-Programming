#include <bits/stdc++.h>
using namespace std;

#define pb push_back
const int N = (int)1e6;
const int M = (int)1e3;	// sqrt(N)

bool mark[M+5];
vector<int> primes;

void sieve() {
	for (int i = 0; i < M; i++) mark[i] = 1;
	for (int i = 2; i < M; i++) {
		if (mark[i]) {
			for (int j = i*i; j < M; j+=i) mark[j] = 0;
			primes.pb(i);
		}
	}
}

void segmentedSieve() {
	sieve();
	
	int lo = M, hi = lo+M;
	while (lo < N) {
		if (hi >= N) hi = N;
		for (int i = 0; i < M; i++) mark[i] = 1;
		
		for (int i = 0; i < primes.size(); i++) {
			int p = ((lo+primes[i]-1)/primes[i]) * primes[i];
			for (int j = p; j < hi; j+=primes[i])
				mark[j-lo] = 0;
		}
		
		for (int i = lo; i < hi; i++)
			if (mark[i-lo]) primes.pb(i);
		
		lo = hi;
		hi = hi + M;
	}
}

int main() {
	segmentedSieve();
	printf("%d\n", primes.size());
//	for (int i = 0; i < primes.size(); i++) printf("%6d ", primes[i]);

	return 0;	
}
