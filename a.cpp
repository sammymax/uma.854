#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;
typedef long double ld;

ld *memo1, *memo2;
ld *vipMemo;
int z, zp, zp2;
int curN = 0;

inline ld get(int a, int b) {
	return memo1[a*zp + b];
}
inline void ass(ld x, int a, int b) {
	memo2[a*zp + b] = x;
}

int main(int argc, char *argv[]) {
	if (argc != 2) z = 50;
	else z = atoi(argv[1]);

	zp = z + 1;
	zp2 = zp*zp;
	cout << "Calculating up to f(" << z << ',' << z << ",0,0)\n";
	vipMemo	= (ld*)malloc(zp2 * sizeof(ld));
	memo1	= (ld*)malloc(zp2 * sizeof(ld));
	memo2	= (ld*)malloc(zp2 * sizeof(ld));
	for (; curN <= z; curN++) {
		memset(memo1, 0, sizeof(ld) * zp2);
		memset(memo2, 0, sizeof(ld) * zp2);
		for (int k = 0; k <= z; k++) {
			for (int a = curN; a >= 0; a--)
				for (int b = curN - a; b >= 0; b--) {
					if (k == 0) ass(0, a, b);
					else {
						ld r = (a + 1.0) / (a + b + 2.0);
						if (curN == 0) ass(r, a, b);
						else ass(
							(a + 1.0) / (a + b + 2.0) * (1.0 + get(a+1, b)) +
							(b + 1.0) / (a + b + 2.0) * max(vipMemo[zp*(k-1) + curN-1], get(a, b+1)),
							a, b
						);
					}
				}
			swap(memo1, memo2);
			vipMemo[k*zp + curN] = get(0, 0);
		}
	}

	if (argc == 2) {
		cout << fixed << setprecision(20);
		for (int i = 0; i <= z; i++)
			cout << i << ' ' << vipMemo[i*zp + i] / i << '\n';
	}
	else {
		ld want = 0.80791935290609852608L, got = vipMemo[50*zp + 50] / 50;
		if (abs(want - got) > 1e-10) {
			cout << "Expected " << want << '\n';
			cout << "Got      " << got << '\n';
			cout << "Diff     " << want - got << '\n';
		}
		else cout << "f(50,50,0,0) passed!\n";
	}
}
