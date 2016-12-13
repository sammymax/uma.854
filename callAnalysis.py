calls = set()
sz = 4

def f(n,k,a,b):
	if (n,k,a,b) in calls:
		return
	calls.add((n,k,a,b))
	if n == 0 or k == 0:
		return
	f(n-1,k-1,0,0)
	f(n,k-1,a+1,b)
	f(n,k-1,a,b+1)

f(sz,sz,0,0)
print(len(calls))
#calls = list(calls)
#calls.sort()
#for c in calls:
#	print(c)

itcalls = set()
for n in range(sz+1):
	#start = 0 if n != sz else sz
	start = 0
	for k in range(start,n+1):
		for a in range(n-k+1):
			if n == sz:
				itcalls.add((n,k,a,n-k-a))
			else:
				for b in range(n-k-a+1):
					itcalls.add((n,k,a,b))
print(len(itcalls))
print(len(itcalls & calls))
l = sorted(list(calls))
for c in l:
	print(c[0], c[1], c[2], c[3])

for c in calls:
	if c[0] < c[1] + c[2] + c[3]:
		print(c)
