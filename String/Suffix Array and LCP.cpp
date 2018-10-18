const int MAX = 1e5+10;

char s[MAX];
int p[MAX], c[MAX], pn[MAX], cn[MAX], cnt[MAX];

void sort_cyclic_shfits() {
	int n = strlen(s);
	memset(cnt,0,sizeof cnt);
	for(int i = 0; i < n; i++) cnt[s[i]]++;
	for(int i = 1; i < 127; i++) cnt[i] += cnt[i-1];	// 127 is max ASCII
	for(int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
	int idx; c[p[0]] = idx = 0;
	for(int i = 1; i < n; i++) {
		if(s[p[i]] != s[p[i-1]]) idx++;
		c[p[i]] = idx;
	}
	for(int h = 0; (1 << h) < n; h++) {
		for(int i = 0; i < n; i++) {
			pn[i] = p[i] - (1 << h);
			if(pn[i] < 0) pn[i] += n;
		}
		for(int i = 0; i <= idx && i < max(n,127); i++) cnt[i] = 0;
		for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
		for(int i = 1; i <= idx; i++) cnt[i] += cnt[i-1];
		for(int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
		idx = cn[p[0]] = 0;
		for(int i = 1; i < n; i++) {
			pair<int,int> cur = {c[p[i]], c[(p[i] + (1<<h)) % n]};
			pair<int,int> pre = {c[p[i-1]], c[(p[i-1] + (1<<h)) % n]};
			if(cur != pre) idx++;
			cn[p[i]] = idx;
		} for(int i = 0; i < n; i++) c[i] = cn[i];
	}
}

void suffix_array() {
	int n = strlen(s);
	s[n] = '$'; s[n+1] = '\0';
	sort_cyclic_shfits();
	s[n] = '\0';
	for(int i = 0; i < n; i++) swap(p[i],p[i+1]);
}

/***** LCP part *****/
int lcp[MAX], order[MAX];
void build_lcp() { // O(n)
	int n = strlen(s), now = 0;
	memset(lcp,0,sizeof lcp);
	memset(order,0,sizeof order);
	for(int i = 0; i < n; i++) order[p[i]] = i;
	for(int i = 0; i < n; i++) {
		if(order[i] == n-1) { now = 0; continue; }
		int j = p[order[i] + 1];
		while(i + now < n && j + now < n && s[i+now] == s[j+now]) ++now;
		lcp[order[i]] = now;
		if(now) now--;
	}
}

int rmq[MAX][15], lg[MAX];
void Fast_lcp() { // O(nlgn)
	memset(rmq,-1,sizeof rmq);
	int n = strlen(s);
	for(int i = 0; i < n; i++)
		rmq[i][0] = lcp[i];
	for(int j = 1; j < 15; j++) 
		for(int i = 0; i < n; i++) {
			int p = i + (1<<(j-1));
			rmq[i][j] = min(rmq[i][j-1], (p < n ? rmq[p][j-1] : MAX + MAX));
		}
	int cur = 0;
	for(int i = 1; i <= n; i++) {
		if((1<<(cur+1)) <= i) cur++;
		lg[i] = cur;
	}

}
/* ask LCP of the ith and jth suffix in the suffix array
 * by calling LCP(i,j-1) if you store lcp[i] = lcp(p[i],p[i+1])
 */
int LCP(int i, int j) { // O(1)
	int k = lg[j - i + 1];
	return min(rmq[i][k] , rmq[j - (1<<k) + 1][k]);
}