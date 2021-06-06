def findTheCharFrequency(text):
    result = dict()
    with open(text,'r') as f:
        for line in f.readlines():
            line = line.lower()
            for i in line:
                if i.isalpha():     #判断字符是否为英文字母
                    if i in result:
                        result[i] += 1
                    else:
                        result.update({i:1})
    return result

#创建节点类
class Node(object):
    def __init__(self, name=None, value=None):
        self.name = name
        self.value = value
        self.lchild = None
        self.rchild = None

#创建Huffman树
class HuffmanTree(object):
    #根据Huffman树的思想：以节点为基础，反向建立Huffman树
    def __init__(self, char_Weights):
        self.Leaf = [Node(k,v) for k, v in char_Weights.items()]
        while len(self.Leaf) != 1:
            self.Leaf.sort(key=lambda node:node.value, reverse=True)
            n = Node(value=(self.Leaf[-1].value + self.Leaf[-2].value))
            n.lchild = self.Leaf.pop(-1)
            n.rchild = self.Leaf.pop(-1)
            self.Leaf.append(n)
        self.root = self.Leaf[0]
        self.Buffer = list(range(10))

    #用递归地思想生成编码
    def Hu_generate(self, tree, length):
        node = tree
        if (not node):
            return
        elif node.name:
            print(node.name + ' 的Huffman编码为: ', end='')
            for i in range(length):
                print(self.Buffer[i], end='')
            print('\n')
            return
        self.Buffer[length] = 0
        self.Hu_generate(node.lchild, length + 1)
        self.Buffer[length] = 1
        self.Hu_generate(node.rchild, length + 1)

    #输出哈夫曼编码
    def get_code(self):
        self.Hu_generate(self.root, 0)

if __name__=='__main__':
    text = r'123.txt'           #输入文本
    result = findTheCharFrequency(text)
    #print(result)
    tree = HuffmanTree(result)
    tree.get_code()