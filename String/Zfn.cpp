/* Z function : for each position i
 * it gives a length z[i] meaning,
 * s[0] = s[i]
 * s[1] = s[i + 1]
 * ....
 * s[z[i] - 1] = s[i + z[i] - 1]
 * which is => length of the logest prefix starting at i
 */

const int N = 1e5+10;
char s[N]; int z[N];
void z_function() {
	int n = strlen(s); z[0] = 0;
	for(int i = 1, l = 0, r = 0; i < n; i++) {
		if(i <= r) z[i] = min(z[i - l], r - i + 1);
		while(i + z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
		if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	} // "aaabab" = {0,2,1,0,2,1,0}, "abacaba" = {0,0,1,0,3,0,1}
}