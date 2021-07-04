def solution(seoul):
    answer = ''
    for i in range(len(seoul)):
        if seoul[i] == 'Kim':
            x = i
            break
        
    
    answer = f'김서방은 {x}에 있다'
    return answer

print(solution(["Jane", "Kim"]))