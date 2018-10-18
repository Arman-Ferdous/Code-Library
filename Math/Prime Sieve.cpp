const int SIZE = 1e7+10;
int mark[(SIZE>>5) + 10];
vector<int> prime;
#define off(i) (((~mark[i>>5])>>(i&31))&1)
#define put(i) (mark[i>>5]|=(1<<(i&31)))
void sieve(int n) {
	mark[0] = 3; int lim = sqrt(n) + 1;
	for(int i = 2; i <= lim; i++) if(off(i))
		for(int j = i*i; j <= n; j+=i) put(j);
	for(int i = 2; i <= n; i++) if(off(i))
		prime.push_back(i);
	// off(i) means i is prime
}

// Segmented Sieve, requires all primes <= sqrt(b) first
bool arr[SIZE + 10];
int SegSieve(int a, int b) {
	int len = b - a + 1;
	fill(arr,arr + len,1);
	int sz = prime.size();
	for(int i = 0; i < sz && prime[i]*prime[i] <= b; i++) {
		int l = (a/prime[i]) * prime[i];
		if(l < a) l += prime[i];
		if(l == prime[i]) l += prime[i];
		l -= a;
		for(int j = l; j < len; j += prime[i]) arr[j] = 0;
	} if(a == 1) arr[0] = 0;
	// arr[i] = true means a + i is prime
}