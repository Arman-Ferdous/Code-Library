const int SIZE = 1e6+10;
int mark[SIZE], phi[SIZE];
void sievephi(int n) {
  for(int i = 1; i <= n; i++) phi[i] = i; mark[1] = 1;
  for(int i = 2; i <= n; i++) if(!mark[i]) {
	for(int j = i; j <= n; j+=i) {
	  mark[j] = 1;
	  phi[j] = phi[j] / i * (i-1);
	}
  }
}
int Phi(int n) {
  int ret = n;
  for(int i = 2; i * i <= n; i++) {
	if(n % i == 0) ret -= ret/i;
	while(n % i == 0) n /= i;
  }
  if(n > 1) ret -= ret/n;
  return ret;
}