import time
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def make_change(d, change):
	# "i" == not possible, "n" == not defined
	n = len(d)
	c = [[0 for x in range(change+1)] for y in range(n)]
	for i in range(n):
		for j in range (1, change+1):
			if i==0 and j<d[0]:
				c[i][j] = float('inf')
			elif i==0:
				c[i][j] = 1 + c[i][j - d[i]]
			else:
				if j < d[i]:
					c[i][j] = c[i-1][j]
				else:
					c[i][j] = min(c[i-1][j], 1+c[i][j-d[i] ])
	return c[n-1][change]

def time_elapsed(d, change):
	t_0 = time.time()
	make_change(d, change)
	t_1 = time.time()
	return t_1 - t_0

# key = [[],[],[],[],[],[],[],[],[],[]]
vrc = []
vrd = []
# x_axis = []
x_axisc = []
x_axisd = []
# my_max = 50000

den = [
	[1, 2, 3], # 1
	[1, 2, 3, 5], # 2
	[1, 2, 3, 5, 8], # 3
	[1, 2, 3, 5, 8, 10], # 4
	[1, 2, 3, 5, 8, 10, 11], # 5
	[1, 2, 3, 5, 8, 10, 11, 21], # 6
	[1, 2, 3, 5, 8, 10, 11, 21, 27], # 7
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33], # 8
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57], # 9
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71], # 10
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97], # 11
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103], # 12
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137], # 13
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161], # 14
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197], # 15
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219], # 16
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241], # 17
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267], # 18
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281], # 19
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315], # 20
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357], # 21
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379], # 22
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431], # 23
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431, 477], # 24
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431, 477, 527], # 25
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431, 477, 527, 579], # 26
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431, 477, 527, 579, 623], # 27
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431, 477, 527, 579, 623, 674], # 28
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431, 477, 527, 579, 623, 674, 741], # 29
	[1, 2, 3, 5, 8, 10, 11, 21, 27, 33, 57, 71, 97, 103, 137, 161, 197, 219, 241, 267, 281, 315, 357, 379, 431, 477, 527, 579, 623, 674, 741, 796]] # 30

# for ch in range(1000, my_max, 1000):
# 	print ch
# 	for m in range(7):
# 		key[m].append(time_elapsed(den[m], ch))
# 	x_axis.append(ch)

for dh in range(30):
	print dh
	vrd.append(time_elapsed(den[dh], 15000))
	x_axisd.append(dh)

for ch1 in range(1000, 31000, 1000):
	print ch1
	vrc.append(time_elapsed(den[12], ch1))
	x_axisc.append(ch1)

fig = plt.figure()
# ax0 = fig.add_subplot(211)
#
# ax0.scatter(x_axis, key[0], s=20, c='#ff0088', marker='o')
# ax0.scatter(x_axis, key[1], s=20, c='#ffaa00', marker='o')
# ax0.scatter(x_axis, key[2], s=20, c='#ffff00', marker='o')
# ax0.scatter(x_axis, key[3], s=20, c='#00ff00', marker='o')
# ax0.scatter(x_axis, key[4], s=20, c='#00ffff', marker='o')
# ax0.scatter(x_axis, key[5], s=20, c='#0000ff', marker='o')
# ax0.scatter(x_axis, key[6], s=20, c='#8800ff', marker='o')
# ##################################################
# b1 = mpatches.Patch(color='#ff0088', label='C == 3')
# b2 = mpatches.Patch(color='#ff8800', label='C == 4')
# b3 = mpatches.Patch(color='#ffff00', label='C == 5')
# b4 = mpatches.Patch(color='#00ff00', label='C == 6')
# b5 = mpatches.Patch(color='#00ffff', label='C == 7')
# b6 = mpatches.Patch(color='#0000ff', label='C == 8')
# b7 = mpatches.Patch(color='#8800ff', label='C == 9')
# plt.legend(handles=[b1,b2,b3,b4,b5,b6,b7])
# ##################################################
# ax0.plot([0, my_max], [0, 0], 'k-', lw=0)
# plt.ylabel("Time elapsed")
# plt.xlabel("value of change (int)")

ax1 = fig.add_subplot(211)
ax1.plot(x_axisc, vrc, 'o', x_axisc, vrc, 'k', c='#ffaa00')
ax1.plot([0, 30000], [0, 0], 'k-', lw=0)
plt.ylabel("Time elapsed", fontsize=18)
plt.xlabel("value of change (int)", fontsize=18)
plt.title("Empirical analysis making_change dynamic Algorithm (matrix update as basic operation)", fontsize=24)

ax2 = fig.add_subplot(212)
ax2.plot(x_axisd, vrd, 'o', x_axisd, vrd, 'k', c='#ff00aa')
ax2.plot([0, 30], [0, 0], 'k-', lw=0)
plt.ylabel("Time elapsed", fontsize=18)
plt.xlabel("number of coins in denomination", fontsize=18)

plt.show()
