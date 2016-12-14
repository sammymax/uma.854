#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <thread>
using namespace std;
typedef double ld;

ld *memo1, *memo2, *res;
int kt, ktp, ktp2, nt, ntp;
const int NUMT = 8;

void calcOverA(const int n, const int tnum) {
	const int rn = nt - n;
	const int bot = tnum * (rn / NUMT);
	const int top = (tnum == NUMT - 1) ? rn+1 : (tnum + 1) * (rn / NUMT);
	for (int a = bot; a < top; a++)
		for (int b = 0; b <= nt - n - a; b++) {
				memo2[a*ntp + b] = (a+1.0)/(a+b+2.0) * (1.0 + memo1[(a+1)*ntp + b]) + 
								   (b+1.0)/(a+b+2.0) * max(memo1[0], memo1[a*ntp + b+1]);
			}
}

int main(int argc, char *argv[]) {
	if (argc != 2) kt = 50, nt = 50;
	else kt = atoi(argv[1]), nt = kt;
	cout << fixed << setprecision(20);

	ntp = nt + 1, ktp = kt + 1, ktp2  = ktp * ktp;
	cout << "Calculating up to f(" << kt << ',' << nt << ",0,0)\n";
	res		= new ld[ktp];
	memo1	= new ld[ktp2];
	memo2	= new ld[ktp2];
	memset(memo1, 0, ktp2*sizeof(ld));
	thread ts[NUMT];
	for (int n = 1; n < ntp; n++) {
		for (int i = 0; i < NUMT; i++) ts[i] = thread(calcOverA, n, i);
		for (int i = 0; i < NUMT; i++) ts[i].join();
		swap(memo1, memo2);
		res[n] = memo1[0];
		cout << n << ' ' << res[n] << '\n'; 
	}

	if (argc == 1) {
		ld want = 40.3959676453049316072234904126L, got = res[nt];
		if (abs(want - got) > 1e-8) {
			cout << "Expected " << want << '\n';
			cout << "Got      " << got << '\n';
			cout << "Diff     " << want - got << '\n';
		}
		else cout << "f(" << kt << ',' << nt << ",0,0) passed!\n";
	}
 }
