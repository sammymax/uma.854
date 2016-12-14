#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <thread>
using namespace std;
typedef long double ld;

ld *memo1, *memo2, *vipMemo;
int kt, ktp, ktp2, nt, ntp;
const int NUMT = 4;

inline ld get(int a, int b) {
	return memo1[a*ktp + b];
}

void calcOverA(const int n, const int k, const int tnum) {
	const int rn = n-k + ktp - ntp;
	const int bot = tnum * (rn / NUMT);
	const int top = (tnum == NUMT - 1) ? rn+1 : (tnum + 1) * (rn / NUMT);
	for (int a = bot; a < top; a++)
		for (int b = 0; b <= n-k-a + ktp-ntp; b++)
			memo2[a*ktp + b] = (a + 1.0) / (a + b + 2.0) * (1.0 + get(a+1, b)) +
				   (b + 1.0) / (a + b + 2.0) * max(vipMemo[ntp*(k-1) + n-1], get(a, b+1));
}

int main(int argc, char *argv[]) {
	if (argc != 3) kt = 70, nt = 50;
	else kt = atoi(argv[1]), nt = atoi(argv[2]);
	cout << fixed << setprecision(20);

	ntp = nt + 1, ktp = kt + 1, ktp2 = ktp * ktp;
	cout << "Calculating up to f(" << kt << ',' << nt << ",0,0)\n";
	vipMemo	= new ld[ktp * ntp];
	memo1	= new ld[ktp2];
	memo2	= new ld[ktp2];
	for (int k = 1; k < ktp; k++) vipMemo[k*ntp] = 0.5L;
	for (int n = 1; n < ntp; n++) {
		memset(memo1, 0, sizeof(ld) * ktp2); // result is 0 if k = 0
		for (int k = 1; k <= n + kt-nt; k++) {
			thread ts[NUMT];
			for (int i = 0; i < NUMT; i++) ts[i] = thread(calcOverA, n, k, i);
			for (int i = 0; i < NUMT; i++) ts[i].join();
			swap(memo1, memo2);
			vipMemo[k*ntp + n] = get(0, 0);
		}
		if (argc == 3) cout << n << ' ' << vipMemo[n*n*ntp + n] << '\n';
	}

	if (argc == 1) {
		ld want = 58.2497855290474201635131120762L, got = vipMemo[kt*ntp + nt];
		if (abs(want - got) > 1e-8) {
			cout << "Expected " << want << '\n';
			cout << "Got      " << got << '\n';
			cout << "Diff     " << want - got << '\n';
		}
		else cout << "f(" << kt << ',' << nt << ",0,0) passed!\n";
	}
 }
