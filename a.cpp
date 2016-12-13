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
	int bot = tnum * (n / NUMT);
	int top = (tnum == NUMT - 1) ? n : (tnum + 1) * (n / NUMT);
	for (int a = bot; a < top; a++) {
		ld *cur = &memo2[a*zp + n - a];
		for (int b = n - a; b >= 0; b--) {
			*cur = (a + 1.0) / (a + b + 2.0) * (1.0 + get(a+1, b)) +
				   (b + 1.0) / (a + b + 2.0) * max(vipMemo[zp*(k-1) + n-1], get(a, b+1));
			cur--;
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) z = 50;
	else z = atoi(argv[1]);

	zp = z + 1;
	zp2 = zp*zp;
	cout << "Calculating up to f(" << z << ',' << z << ",0,0)\n";
	vipMemo	= (ld*)calloc(zp2,  sizeof(ld));
	memo1	= (ld*)malloc(zp2 * sizeof(ld));
	memo2	= (ld*)malloc(zp2 * sizeof(ld));
	for (int n = 1; n <= z; n++) {
		memset(memo1, 0, sizeof(ld) * zp2);
		memset(memo2, 0, sizeof(ld) * zp2);
		for (int k = 1; k <= z; k++) {
			thread ts[NUMT];
			for (int i = 0; i < NUMT; i++) ts[i] = thread(calcOverA, n, k, i);
			for (int i = 0; i < NUMT; i++) ts[i].join();
			swap(memo1, memo2);
			vipMemo[k*zp + n] = get(0, 0);
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
