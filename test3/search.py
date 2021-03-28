def binary_search(x, T):  # 二分
    t = []
    low = 0
    length = len(T) - 1
    while low <= length:
        mid = int((low + length) / 2)
        if x < T[mid]:
            length = mid - 1
        elif x > T[mid]:
            low = mid + 1
        else:
            t.append(mid)
            for i in range(1,mid+1):
                if T[mid-i]==x:
                    t.append(mid-i)
                else:
                    break
            for j in range(1,length-mid+1):
                if T[mid+j]==x:
                    t.append(mid+j)
                else:
                    break
            return t


T = [1, 2, 3, 4, 4, 5]
x = input("输入查询的数：")
x = int(x)
print(binary_search(x, T))

'''
# 顺序查找
def sequence_search(list1, m):
    return [i for (i, m) in enumerate(list1) if m == x]


T = [1, 2, 3, 4, 5, 5, 8]
x = input("输入查询的数：")
x = int(x)
if x in T:
    print(sequence_search(T, x))
else:
    print("0")
'''
