#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <thread>
using namespace std;
typedef long double ld;

ld *memo1, *memo2, *vipMemo;
int z, zp, zp2;
const int NUMT = 4;

inline ld get(int a, int b) {
	return memo1[a*zp + b];
}

void calcOverA(int n, int k, int tnum) {
	int rn = n-k;
	int bot = tnum * (rn / NUMT);
	int top = (tnum == NUMT - 1) ? rn+1 : (tnum + 1) * (rn / NUMT);
	for (int a = bot; a < top; a++) {
		ld *cur = &memo2[a*zp];
		for (int b = 0; b <= n-k-a; b++) {
			*cur = (a + 1.0) / (a + b + 2.0) * (1.0 + get(a+1, b)) +
				   (b + 1.0) / (a + b + 2.0) * max(vipMemo[zp*(k-1) + n-1], get(a, b+1));
			cur++;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) z = 50;
	else z = atoi(argv[1]);
	cout << fixed << setprecision(20);

	zp = z + 1;
	zp2 = zp*zp;
	cout << "Calculating up to f(" << z << ',' << z << ",0,0)\n";
	vipMemo	= (ld*)calloc(zp2,  sizeof(ld));
	memo1	= (ld*)malloc(zp2 * sizeof(ld));
	memo2	= (ld*)malloc(zp2 * sizeof(ld));
	for (int n = 1; n <= z; n++) {
		memset(memo1, 0, sizeof(ld) * zp2); // result is 0 if k = 0
		for (int k = 1; k <= n; k++) {
			thread ts[NUMT];
			for (int i = 0; i < NUMT; i++) ts[i] = thread(calcOverA, n, k, i);
			for (int i = 0; i < NUMT; i++) ts[i].join();
			swap(memo1, memo2);
			vipMemo[k*zp + n] = get(0, 0);
		}
		if (argc == 2) cout << n << ' ' << vipMemo[n*zp + n] << '\n';
	}

	if (argc == 1) {
		ld want = 0.80791935290609852608L, got = vipMemo[z*zp + z] / z;
		if (abs(want - got) > 1e-10) {
			cout << "Expected " << want << '\n';
			cout << "Got      " << got << '\n';
			cout << "Diff     " << want - got << '\n';
		}
		else cout << "f(50,50,0,0) passed!\n";
	}
 }
