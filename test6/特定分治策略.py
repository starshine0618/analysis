import random
if __name__ = "__main__":
	num = 100                                               #100个随机数组
	array = [random.randint(1,1000) for i in range(num)]
	random.shuffle(array)
	random.shuffle(array)
	k = 7                                                   #所求第k小的数
	kval = select_fct(array,k)
	print(kval)
	sorted_array = sorted(array)                            #用直接排序得到第k小的数，验证算法
	assert sorted_array[k] == kval


def select_fct(array, k):
	if len(array) <= 10:                                    #边界条件
		array.sort()
		return array[k]
	pivot = get_pivot(array)                                #的到数组支点数
	array_lt, array_gt, array_eq = pation_array(array,pivot)#按照支点数划分数组
	if k < len(array_lt):                                   #支点数在左边
		return select_fct(array_lt,k)
	elif k < len(array_lt) + len(array_eq):                 #所求数为支点数
		return array_eq[0]
	else:#支点数在右边
		normalized_k = k-(len(array_lt) + len(array_eq))
		return select_fct(array_gt, normalized_k)
 

 def get_pivot(array):
 	subset_size = 5                                         #每组5个元素
 	subsets = []                                            #记录各组元素
 	num_medians = len(array) // subset_size
 	if (len(array) % subset_size) > 0:
 		num_medians += 1                                    #不能被5 整除
 	for i in range(num_medians):                            #划分成若干组，每组5个元素
 		beg = i * subset_size
 		end = min(len(array),beg + subset_size)
 		subset  = array[beg:end]
 		subsets.append(subset)
 	medians = []
 	for subset in subsets:
 		medians = select_fct(subset,len(subset)//2)         #计算每组中间数
 		medians.append(medians)
 	pivot = select_fct(medians,len(subset)//2)              #中间数的中间数
 	return pivot


 def pation_array(array,pivot):
 	array_lt = []
 	array_gt = []
 	array_eq = []
 	for item in array:
 		if item < pivot:
 			array_lt.append(item)
 		elif item > pivot:
 			array_gt.append(item)
 		else:
 			array_eq.append(item)
 	return array_lt,array_gt,array_eq


