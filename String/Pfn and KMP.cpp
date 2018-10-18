/* Prefix Function : for each position i 
 * it gives another index pi[i] which means,
 * s[0] = s[ i-pi[i] ]
 * s[1] = s[ i-pi[i] + 1]
 * ....
 * s[p[i]] = s[ i ] 
 * which is => length(not length but length - 1 aka index) of the logest prefix ending at i
 */

const int N = 1e5+10;
int pi[N]; char s[N], t[N];
void prefix_function() {
	int n = strlen(s);
	int now; pi[0] = now = -1;
	for(int i = 1; i < n; i++) {
		while(now != -1 && s[now + 1] != s[i]) now = pi[now];
		if(s[now + 1] == s[i]) pi[i] = ++now;
		else pi[i] = now = -1;
	} // “ababaca” = {-1,-1,0,1,2,-1,0}
}
void kmp() { // find whether s is inside t, need to calc pi(s) first
	int n = strlen(t), m = strlen(s); 
	int now = -1;	// s[0...now] == t[...i-1], now check now + 1 with i
	for(int i = 0; i < n; i++) {
		while(now != -1 && s[now + 1] != t[i]) now = pi[now];
		if(s[now + 1] == t[i]) ++now;
		else now = -1;
		if(now == m-1) cout << "found match starting at t[" << i - m + 1 << "]\n";
	}
}