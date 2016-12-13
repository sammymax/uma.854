import math 

F_vals = {}

def F(K,N,a,b): 
	key = (K,N,a,b)
	if key in F_vals:
		#print 'true'
		return F_vals[key]
	if K == 0: 
		F_vals[key] = 0.
		return 0.
	if N == 0: 
		F_vals[key] = (a+1.)/(a+b+2.)
		return F_vals[key]	

	heads = (a+1.)/(a+b+2.)*(1. + F(K-1, N, a+1,b))
	tails = (b+1.)/(a+b+2.)*max(F(K-1,N-1,0,0), F(K-1,N,a,b+1))
	F_vals[key] = heads+tails
	return heads+tails

#N = 4
#K = 100

#print F(10,100,0,0)/10
#exit()

if __name__ == "__main__":

	#print F(50,50,0,0)
	#exit()

	f = open('optiver.txt', 'w') #########DO NOT RUN WITHOUT SAVING PREVIOUS TEXT FILE
	plotvals = []
	theoret = []
	theoret2 = []

	#increasing a 
	# for b in range(0, 100): 
	# 	key = (K,N,0, b)
	# 	if key not in F_vals: 
	# 		F(K,N,0,b)

	# 	print F_vals[key]/K
	# 	plotvals.append(F_vals[key]/K)

	k = 1
	#increasing k 
	while True:

	#for k in range(3, int(K)): 
	
		N = k
		key = (k,N,0,0)
		if key not in F_vals: 
			F(k, N, 0,0)
		
		if k % 100 == 0:
			print k, F_vals[key]/k
		
		f.write(str(F_vals[key]/k)+"\n")
		k += 1
		
		#plotvals.append(F_vals[key]/k)
		#theoret.append(1-1/math.log(k+1))
		#theoret2.append(1-1/(math.log(k+1)*math.log(math.log(k))))



	#import matplotlib.pyplot as plt
	#plt.plot(plotvals, label = 'DP')
	#plt.plot(theoret, label = 'theoretical')
	#plt.plot(theoret2, label = 'theoretical 2')
	#plt.legend(loc = 'lower right')
	#plt.show()

