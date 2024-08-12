import sys
operations = ["", "+", "-", "*", "/"]

class Operation:
    ADD = 1
    SUBTRACT = 2
    MULTIPLY = 3
    DIVIDE = 4

class NumberNode:
    def __init__(self, nums, indexOne, indexTwo, operation, prevNode):
        self.nums = nums.copy()
        self.output = 0
        if(indexOne == -1):
            self.prevNode = None
            self.createNodes()
            return
        self.one = nums[indexOne]
        self.two = nums[indexTwo]
        self.operation = operation
        self.prevNode = prevNode
        if(self.operation == Operation.ADD):
            self.output = self.one + self.two
        if(self.operation == Operation.SUBTRACT):
            self.output = self.one - self.two
        if(self.operation == Operation.DIVIDE):
            if(self.two == 0):
                return
            self.output = self.one / self.two
        if(self.operation == Operation.MULTIPLY):
            self.output = self.one * self.two

        if(self.output < 0 or self.output % 1 != 0):
            return
        
        self.output = int(self.output)
        self.nums.remove(self.one)
        self.nums.remove(self.two)
        self.nums.append(self.output)

        global minDifference
        if(abs(self.output - target) < minDifference):
            minDifference = abs(self.output-target)
            global minNode
            minNode = self

        if(len(self.nums) == 1):
            if(self.output == target):
                print("Target Found")
                node = self
                while(node.prevNode != None):    
                    print(node.one, operations[node.operation], node.two, "=", node.output)
                    node = node.prevNode
                exit()
            return
        self.createNodes()

    def createNodes(self):
        for i in range(len(self.nums)):
            for j in range(len(self.nums)):
                if(i == j):
                    continue
                for o in range(1, 5):
                    NumberNode(self.nums, i, j, o, self)

minDifference = 1000000000
minNode = None

if __name__ == "__main__":
    if(len(sys.argv) != 8):
        print("Invalid number of arguments: target num1,...,num6")
        exit()
    
    target = int(sys.argv[1])
    nums = []
    for i in range(2,8):
        nums.append(int(sys.argv[i]))

    startNode = NumberNode(nums, -1, -1, 0, None)

    print("Closest found:", minNode.output)
    node = minNode
    while(node.prevNode != None):    
        print(node.one, operations[node.operation], node.two, "=", node.output)
        node = node.prevNode