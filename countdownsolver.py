operations = ["", "+", "-", "*", "/"]

class Operation:
    ADD = 1
    SUBTRACT = 2
    MULTIPLY = 3
    DIVIDE = 4

class GraphNode:
    def __init__(self, num, inNode, operation):
        self.num = num
        self.inNode = inNode
        self.operation = operation
        self.output = 0
        if(self.inNode != None):
            if(self.inNode.operation == 0):
                self.output = self.num
            else:
                if(self.operation == Operation.ADD):
                    self.output = self.inNode.output + self.num
                if(self.operation == Operation.SUBTRACT):
                    self.output = self.inNode.output - self.num
                if(self.operation == Operation.MULTIPLY):
                    self.output = self.inNode.output * self.num
                if(self.operation == Operation.DIVIDE):
                    self.output = int(self.inNode.output / self.num)

        if(self.output == target):
            node = self
            while(node.inNode.operation != 0):
                print(node.inNode.output, operations[node.operation], node.num, "=", node.output)
                node = node.inNode
            exit()
        global minDifference
        global minNode
        if(abs(self.output - target) < minDifference):
            minNode = self
            minDifference = abs(self.output-target)
        self.nodes = []
    
    def generateNodes(self, nums):
        if(len(nums) <= 1):
            return
        if(self.operation == Operation.DIVIDE and self.inNode.output % self.num != 0):
            return
        for num in nums:
            newNums = nums.copy()
            newNums.remove(num)
            for i in range(1, 5):
                self.nodes.append(GraphNode(num, self, i))
                self.nodes[-1].generateNodes(newNums)


nums = [10, 7, 8, 9, 75, 25]
target = 546
minDifference = 1000000000
minNode = None

startNode = GraphNode(-1, None, 0)
startNode.generateNodes(nums)


node = minNode
while(node.inNode != None):
    print(node.num, operations[node.operation], node.inNode.output, "=", node.output)
    node = node.inNode