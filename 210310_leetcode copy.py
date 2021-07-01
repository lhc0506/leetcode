class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        count = 0
        coins.sort(reverse=True)
        # for coin in coins:
        #     while amount > coin:
        #         amount -= coin
        #         count += 1
        #         break

        while amount > 0:
            for coin in coins:
                if (amount - coin) > 0:
                    amount -= coin
                    count += 1
                break
        if amount == 0:
            return count
        else: 
            return -1