class Solution:
    def intToRoman(self, num: int) -> str:
        #숫자-로마 딕셔너리
        Dict_roman={1000:'M',900:'CM',500:'D',400:'CD',100:'C',90:'XC',50:'L',40:'XL',10:'X',9:'IX',5:'V',4:'IV',1:'I'}

        #리턴할 str
        result = ''
        
        #nums값 이상이면 빼고, str에 추가
        while num!=0:
            for nums in Dict_roman:
                if (num - nums) >=0:
                    num -= nums
                    result += Dict_roman[nums]

        return result



