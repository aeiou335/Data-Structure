#Given a list of N integers, write code to count the number of pairs
#in this list whose difference is exactly K.
#For example, suppose N=4, K=3 and the list is [1, 3, 4, 6].
#Then the number of pairs is 2, namely [1,4] and [3,6].


import math
# We just assume N>1 and there isn't exists the list like [1, 3, 5] and k = 2
def two_differ(num, target, total_num):
	count = 0
	diff = []
	for i in range(total_num):
		if num[i] in diff:
			print (num[i], abs(target - num[i]))
			count += 1
		# Since we have sorted the list, we will always
		# read the smallest number first. Then we add 
		# (the number + target)  into the list.
		# After that if we find num[i] is in the list, then it means
		# the num[i] minus the number we have read before will 
		# equal to the target number.
		else:
			diff.append (abs(target + num[i]))
	print (count)

str1 = str(input())
k = int(input())
n = int(input())
str1 = str1.split(" ")
num_list = []
for i in range(n):
	num_list.append(int (str1[i]))
num_list.sort()

two_differ(num_list, k, n)
