calls = set()
nt = 5
kt = 5

def f(n,k,a,b):
	if (n,k,a,b) in calls:
		return
	calls.add((n,k,a,b))
	if n == 0 or k == 0:
		return
	f(n-1,k-1,0,0)
	f(min(n,k-1),k-1,a+1,b)
	f(min(n,k-1),k-1,a,b+1)

f(nt,kt,0,0)
print(len(calls))
#calls = list(calls)
#calls.sort()
#for c in calls:
#	print(c)

itcalls = set()
for n in range(nt+1):
	for a in range(nt-n+1):
		for b in range(nt-n-a+1):
			itcalls.add((n,n,a,b))
print(len(itcalls))
print(len(itcalls & calls))
l = sorted(list(calls))
#for c in l:
#	print(c[0], c[1], c[2], c[3])
print(sorted(list(calls - itcalls)))
