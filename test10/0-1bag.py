
w = [20,15,30,20]    # 每个货物对应重量
Max = 0    # 初始化第一艘船中的当前最大载重量
x = []    # 初始化中间解
X = []    # 初始化最优解
r = 0
cw = 0
def loading(s1,s2,w):
    global x    # 启动成员变量
    global r
    global cw
    global c1
    global c2
    r = sum(w)    # 初始化未考虑的物品总重量
    x = [0] * len(w)
    trace(0)
    print('第一艘船的装载量为:',Max)
    print('第一艘船装载的货物为:',end='')
    [print(t[0],end=' ') for t in enumerate(X) if t[1] == 1]
    print()
    print('第二艘船的装载量为:',r - Max)
    print('第二艘船装载的货物为:',end='')
    [print(t[0],end=' ') for t in enumerate(X) if t[1] == 0]
def trace(i):    # 回溯函数
    global Max
    global x
    global cw
    global r
    if i == len(w):    # 递归出口，判断是否为最优解
        if cw > Max:
            Max = cw
            global X
            X = x[:]    # 修改最优解
        return
    r -= w[i]
    if w[i] + cw <= c1:    # 通过限界函数，判断是否进入左子树
        x[i] = 1    # 将此物品加入中间解中
        cw += w[i]
        trace(i+1)
        cw -= w[i]    
    if cw + r > Max:    # 通过上界函数，判断是否对右子树进行剪枝操作
        x[i] = 0    # 不考虑此物品
        trace(i+1)
    r += w[i]

