from itertools import permutations
class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        for n in range(1,len(prices)//2+1):
            for i in permutations(prices,n):
                result = 0
                for j in range(len(i)):
                    if j%2 == 1:
                        result += i[j]
                    else:
                        result -= i[j]
                result -= fee*n
                print(result)