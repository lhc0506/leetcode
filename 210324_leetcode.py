class Solution:
    def hasAllCodes(self, s: str, k: int) -> bool:
        k_bi = []
        l = len(format(k.'b'))
        for i in range(2**k-1):
            k_bi.append(format(i,'b').zfill(l))
        for bi in k_bi:
            if bi not in s:
                return False
        
        return True
        
