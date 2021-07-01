class Solution:
    def threeSumMulti(self, arr: List[int], target: int) -> int:
        n = len(arr)
        count = 0
        for i in range(n-2):
            for j in range(i+1,n-1):
                if arr[i] + arr[j] > target:
                    continue
                else:
                    for k in range(j+1,n):
                        if arr[i] + arr[j] + arr[k] == target:
                            count += 1
        return count


