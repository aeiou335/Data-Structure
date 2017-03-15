#Consider two sets of positive integers, A and B.  We say an integer x is “between” two sets if it follows the following rules:
#All elements in set A are factors of x. (In other words, x is a multiple of a, for all a in A.)
#x is a factor of all elements in set B.
#For example,
#For A=[2, 8], B=[32, 48, 96], then the set of all integers that are between A and B is X=[8, 16]
#Goal: Implement an algorithm that can find all the integers between sets A and B

import functools


def gcd (x, y):
	if y == 0:
		return x
	else:
		return gcd(y, x % y)

def lcm (x, y):
	return int( x*y / gcd(x, y))

def integers_between_sets(set_a, set_b):
	# We first calculate both the gcd of set b and lcm of set a.
	gcd_of_set_b = functools.reduce(lambda x, y: gcd(x,y), set_b)
	lcm_of_set_a = functools.reduce(lambda s, t: lcm(s,t), set_a)
	num = []
	num.append(gcd_of_set_b)
	# Our strategy is to find all the numbers that satisfy two conditions.
	# First, it needs to be the factor of the gcd of set b.
	# Second, it needs to be the multiple of the lcm of set a.
	for i in range(lcm_of_set_a, int(gcd_of_set_b/2)+1):
		if gcd_of_set_b % i == 0 and i % lcm_of_set_a == 0:
			num.append(i)

	print (num)
	
str_a = input()
str_b = input()
str_a = str_a.split(" ")
str_b = str_b.split(" ")
num_a = []
num_b = []
for i in range(len(str_a)):
        num_a.append(int(str_a[i]))
for i in range(len(str_b)):
        num_b.append(int(str_b[i]))

integers_between_sets(num_a, num_b)
