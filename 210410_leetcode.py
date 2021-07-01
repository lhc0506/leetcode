A = [2,0,4,1,2]
B = [1,3,0,0,2]
a_s = sorted(A)
b_s = sorted(B)

result = [0 for _ in range(len(A))]
i = 0
j = 0
while j <len(A):
    if a_s[i] <= b_s[i]:
        a_s.append(a_s.pop(0))
        j += 1
        continue
    else: 
        i += 1
        j += 1
for i in range(len(b_s)):
    n = B.index(b_s[i])
    result[n] = a_s[i]  


print(a_s)
print(b_s)
print(result)

