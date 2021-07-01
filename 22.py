def solution(program, flag_rules, commands):
    
    
    n = len(commands)
    answer = [_ for _ in range(n)] #답 리스트
    
    '''#commands를 split'''
    result = [[0] for _ in range(n)] 
    for i in range(n):
        result[i] = commands[i].split()
    
    '''반복하며 조건 탐색'''
    for i in range(n):
        if result[i][0] != program: #program 이름 확인
            answer[i] = False
            break
        j = 1
        while j < len(result[i]):
            if result[i][j] == '-n': #-n 일때 조건
                if not result[i][j+1].isdigit():
                    answer[i] = False
                    break
            
            elif result[i][j] == '-s': #-s 일때 조건
                if not result[i][j+1].isalpha():
                    answer[i] = False
                    break
            
            elif result[i][j] == '-e': #-e 일때 조건

                if j is not len(result[i])-1:
                    if result[i][j+1] is not None:
                        answer[i] = False
                        break
            
            else : #flag 없는 argument 일때
                answer[i] = False
                break
            answer[i] = True
            j += 2

    
    print(result)
    print(answer)
    return answer