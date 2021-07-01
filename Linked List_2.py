class Node:
    def __init__(self,data):
        self.data = data #노드가 저장하는 데이터
        self.next = None # 다음노드에 대한 레퍼런스

class LinkedList:
    """링크드 리스트 클래스"""
    def __init__(self):
        self.head = None
        self.tail = None

    def delete_after(self, previous_node):
        """링크드 리스트 삭제 연산. 주어진 노드 뒤 노드를 삭제한다."""
        data = previous_node.next.data

        if previous_node.next is self.tail:
            previous_node.next = None
            self.tail = previous_node
        else:
            previous_node.next = previous_node.next.next

        return data

    def insert_after(self,previous_node, data):
        """링크드 리스트 주어진 노드 뒤 삽입 연산 메소드"""
        new_node = Node(data)

        #마지막에 삽입
        if previous_node is self.tail:
            self.tail.next = new_node
            self.tail = new_node
        else:
            new_node.next = previous_node.next
            previous_node.next = new_node

    def find_node_at(self,index):
        """링크드 리스트 접근 연산 메소드. 파라미터 인덱스는 항상 있다고 가정"""
        iterator = self.head

        for _ in range(index):
            iterator = iterator.next

        return iterator

    def append(self,data):
        """링크드 리스트 추가 연산 메소드"""
        new_node = Node(data)

        if self.head == None:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
    
    def __str__(self):
        res_str ="|"
        iterator = my_list.head
        while iterator is not None:
            res_str += f"{iterator.data}|"
            iterator = iterator.next
        return res_str


#새로운 링크드 리스트 생성
my_list = LinkedList()

# 링크드 리스트에 데이터 추가
my_list.append(2)
my_list.append(3)
my_list.append(5)
my_list.append(7)

# 링크드 리스트 노드에 접근
print(my_list.find_node_at(3).data)

my_list.find_node_at(2).data = 13

print(my_list)

node_2 = my_list.find_node_at(2)
my_list.insert_after(node_2,6)

print(my_list)

head_node = my_list.head
my_list.insert_after(head_node,9)
print(my_list)

node_2 = my_list.find_node_at(2)
my_list.delete_after(node_2)

print(my_list)

second_to_last_node = my_list.find_node_at(3)
print(my_list.delete_after(second_to_last_node))
print(my_list)