import math
from decimal import *
getcontext().prec = 30

F_vals = {}

def F(K,N,a,b):
	key = (K,N,a,b)
	if key in F_vals:
		return F_vals[key]
	if K == 0:
		F_vals[key] = Decimal(0)
		return Decimal(0)
	if N == 0:
		F_vals[key] = Decimal(a+1)/Decimal(a+b+2)
		return F_vals[key]

	heads = Decimal(a+1)/Decimal(a+b+2)*(Decimal(1) + F(K-1, N, a+1,b))
	tails = Decimal(b+1)/Decimal(a+b+2)*max(F(K-1,N-1,0,0), F(K-1,N,a,b+1))
	F_vals[key] = heads+tails
	return heads+tails

if __name__ == "__main__":
	plotvals = []
	theoret = []
	theoret2 = []

	print(F(50,50,0,0))
	exit()

	k = 1
	#increasing k 
	while True:
		N = k
		key = (k,N,0,0)
		if key not in F_vals: 
			F(k, N, 0,0)
		
		f.write(str(F_vals[key]/k)+"\n")
		k += 1

