#include <iostream>
#include <cstring>
#include <iomanip>
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
		for (int i = 0; i < zp2*zp; i++) memo[i] = 0;
		for (int k = 0; k <= z; k++) {
			for (int a = curN; a >= 0; a--)
				for (int b = curN - a; b >= 0; b--) {
					if (k == 0) ass(0, k, a, b);
					else {
						ld r = (a + 1.0) / (a + b + 2.0);
						if (curN == 0) ass(r, k, a, b);
						else ass(
							(a + 1.0) / (a + b + 2.0) * (1.0 + get(k-1, a+1, b)) +
							(b + 1.0) / (a + b + 2.0) * max(vipMemo[zp*(k-1) + curN-1], get(k-1, a, b+1)),
							k, a, b
						);
					}
				}
			vipMemo[k*zp + curN] = get(k, 0, 0);
		}
	}

	cout << fixed << setprecision(20);
	for (int i = 0; i <= z; i++)
		cout << vipMemo[i*zp + i] / i << '\n';
}
