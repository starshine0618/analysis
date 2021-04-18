import math

# 输入
p = [[0, 0], [1, 1], [3, 4], [0, 3], [3.2, 4.2], [0, -1], [-2, -2], [-1, -2], [0, 0.4], [-1, 2], [0, 2], [0.5, 2]]
# p = [[0,0], [1,1], [3,4]]
n = len(p)


# 预期输出：最近点对是 ( 3.2 , 4.2 ) 和 ( 3 , 4 ), 最短距离为 0.2828427124746193
# 查找最接近的目标的y下标
def find_closed_index(collections, target):
    n = len(collections)
    low = 0
    high = n - 1
    mid = 0
    while low <= high:
        mid = math.floor((low + high) / 2)
        if target > collections[mid][1]:
            low = mid + 1
        elif target < collections[mid][1]:
            high = mid - 1
        else:
            return mid

    return mid


def distance(p1, p2):
    return math.sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2))


def divide(l, r, res):
    if l == r:
        return float("inf"), []
    if (l + 1) == r:
        return distance(p[l], p[r]), [p[l], p[r]]
    mid = math.floor((l + r) / 2)
    d1, res1 = divide(l, mid, res)
    d2, res2 = divide(mid + 1, r, res)
    if d1 >= d2:
        d = d2
        res = res2
    else:
        d = d1
        res = res1
    # 先将所有左子域、右子域、同一x值的中间子域，删选出来
    left = []
    right = []
    midd = []
    b = p[mid][0]
    bl = b - d
    br = b + d
    for i in range(n):
        if ((p[i][0] >= bl) & (p[i][0] <= b)) == True:
            left.append(p[i])
            if p[i][0] == b:
                midd.append(p[i])
        elif ((p[i][0] <= br) & (p[i][0] >= b)) == True:
            right.append(p[i])

    if len(right) == 0:
        return d, res
    # 将右子域先按照y值大小排好序
    right.sort(key=lambda x: x[1])
    # 遍历左子域中的每一个点，在右子域中寻找y值最邻近的四个点，求出最小距离以及最近点对
    for i in range(len(left)):
        closed_point = []
        right_num = len(right)
        if right_num <= 4:
            closed_point = right
        else:
            index = find_closed_index(right, left[i][1])
            if index >= 4:
                start = index - 4
            else:
                start = 0
            if index + 5 > len(right) - 1:
                end = len(right) - 1
            else:
                end = index + 5

            for j in range(start, end):
                closed_point.append(right[j])
            # 前四个就是右子域中离左子域最近的四个点
            closed_point.sort(key=lambda x: abs(x[1] - left[i][1]))

        if len(closed_point) >= 4:
            end2 = 4
        else:
            end2 = len(closed_point)

        for k in range(0, end2):
            dist = distance(closed_point[k], left[i])
            if dist < d:
                res = [closed_point[k], left[i]]
                d = dist
    # 再在中间子域的内部进行比较，看看有没有x值相同，且距离最近的两个点
    if len(midd) > 1:
        midd.sort()
        for j in range(len(midd) - 1):
            dist = distance(midd[j], midd[j + 1])
            if dist < d:
                res = [midd[j], midd[j + 1]]
                d = dist

    return d, res


# 前期需要按照x值排序
p.sort()
d, res = divide(0, n - 1, [])
print("最近点对是 (", res[0][0], ",", res[0][1], ") 和 (", res[1][0], ",", res[1][1], "), 最短距离为", d)