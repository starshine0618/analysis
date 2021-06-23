n = 0  # 任务数
k = 0  # 机器数
best = 99999  # 最优值(完成全部任务的最早时间)
len = []  # 每台机器已安排的时间
t = []  # 每个任务所需的时间
x = []  # 当前路径(调度)
bestx = []  # 最优路径(调度)

# 计算任务完成的时间
def comp():

    tmp = 0
    for i in range(k):
        if len[i] > tmp:
            tmp = len[i]
    return tmp

# 以深度优先遍历方式遍历解空间树
def search(dep, len, t):

    global best

    if dep == n:
        tmp = comp()
        if tmp < best:
            best = tmp
            for i in range(n):
                bestx[i] = x[i]
        return

    for i in range(k):
        len[i] += t[dep]
        x[dep] = i + 1
        if len[i] < best:
            search(dep + 1, len, t)
        len[i] -= t[dep]

if __name__=="__main__":

    strN = input("请输入任务数n:")
    strK = input("请输入机器数k:")
    n = int(strN)
    k = int(strK)

    strT = input("请输入完成{}个任务需要的时间(以空格分隔，以回车结束):".format(n))
    t = strT.split(" ")
    t = list(map(int, t))  # str转为int

    len = [0 for _ in range(k)]  # k长度
    x = [0 for _ in range(n)]  # n 任务数量并创建列表
    bestx = [0 for _ in range(n)]

    search(0, len, t)
    print("最优值：", best)
    print("最优解：", bestx)