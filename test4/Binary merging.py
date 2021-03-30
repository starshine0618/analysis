def merge(a, b):
    l1 = []
    f = s = 0
    while f < len(a) and s < len(b):
        if a[f] < b[s]:
            l1.append(a[f])
            f += 1
        else:
            l1.append(b[s])
            s += 1
    # 某一数组遍历完另一数组还有剩余
    if f == len(a):
        for i in b[s:]:
            l1.append(i)
    else:
        for i in a[f:]:
            l1.append(i)
    return l1


def separate(list1):
    if len(list1) <= 1:
        return list1
    mid = len(list1) // 2
    left = separate(list1[:mid])
    right = separate(list1[mid:])
    return merge(left, right)


l = [2, 3, 1, -2, 10]
p = separate(l)
print(p)
