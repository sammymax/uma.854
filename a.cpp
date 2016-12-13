#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

ld *memo;
ld *vipMemo;
int z, zp, zp2;
int curN = 0;

inline ld get(int k, int a, int b) {
	return memo[k*zp2 + a*zp + b];
}
inline void ass(ld x, int k, int a, int b) {
	memo[k*zp2 + a*zp + b] = x;
}

ld f(int k, int a, int b) {
	if (get(k,a,b) >= 0)
		return get(k,a,b);
	if (k == 0) {
		ass(0, k,a,b);
		return 0;
	}
	ld ratio = (a + 1.0) / (a + b + 2.0);
	if (curN == 0) {
		ass(ratio, k,a,b);
		return ratio;
	}
	ld h = ratio * (1.0 + f(k-1, a+1, b));
	ld t = (b + 1.0) / (a + b + 2.0) * max(vipMemo[(k-1)*zp + curN-1], f(k-1,a,b+1));
	ass(h+t, k,a,b);
	return h + t;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "You fucked up.\n";
		return 0;
	}
	z = atoi(argv[1]);
	zp = z + 1;
	zp2 = zp*zp;
	cout << z << '\n';
	vipMemo = (ld*)malloc(zp2 * sizeof(ld));
	memo = (ld*)malloc(zp2*zp * sizeof(ld));
	for (; curN <= z; curN++) {
		for (int i = 0; i < zp*zp2; i++) memo[i] = -1;
		for (int k = 0; k <= z; k++) {
			vipMemo[k*zp + curN] = f(k, 0, 0);
		}
	} 

	cout << fixed << setprecision(20);
	for (int i = 0; i <= z; i++)
		cout << vipMemo[i*zp + i] / i << '\n';
}
