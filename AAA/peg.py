# backtracking: general form of DFS. eliminating an option when you find it's impossible
board2 = [
	[0, 0, 0, 1, 1, 1, 0, 0, 0],
	[0, 0, 0, 1, 1, 2, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0],
	[0, 0, 0, 0, 0, 0, 0, 0, 0]
]
board = [
	[0, 0, 0, 1, 1, 1, 0, 0, 0],
	[0, 0, 0, 1, 1, 1, 0, 0, 0],
	[0, 0, 0, 1, 1, 1, 0, 0, 0],
	[1, 1, 1, 1, 1, 1, 1, 1, 1],
	[1, 1, 1, 1, 2, 1, 1, 1, 1],
	[1, 1, 1, 1, 1, 1, 1, 1, 1],
	[0, 0, 0, 1, 1, 1, 0, 0, 0],
	[0, 0, 0, 1, 1, 1, 0, 0, 0],
	[0, 0, 0, 1, 1, 1, 0, 0, 0]
] # n==44

def try_move(configb, xi, xj, yi, yj, zi, zj): # curr_peg, ell_peg, emp_peg
	if xi < 0 or xj < 0 or yi < 0 or yj < 0 or zi < 0 or zj < 0 or xi > 8 or xj > 8 or yi > 8 or yj > 8 or zi > 8 or zj > 8:
		return configb, -1
	if configb[xi][xj]==1 and configb[yi][yj]==1 and configb[zi][zj]==2:
		configb[xi][xj] = 2
		configb[yi][yj] = 2
		configb[zi][zj] = 1
		return configb, 1
	return configb, -1 # no move could be made


def undo_move(configb, xi, xj, yi, yj, zi, zj): # curr_peg, ell_peg, emp_peg
	configb[xi][xj]=1
	configb[yi][yj]=1
	configb[zi][zj]=2
	return configb # no move could be made


def back_track(configb, n):
	print n
	if n == 1:
		return configb, 1
	for i in range(9):
		for j in range(9):
			if configb[i][j] == 1:
				# try to make a move, for each move, if back_track returned 1, return, else undo move
				# try move right
				configb, stat = try_move(configb, i, j, i+1, j, i+2, j)
				if stat == 1:
					configb, stat = back_track(configb, n-1)
					if stat == 1:
						return configb, 1
					else:
						undo_move(configb, i, j, i+1, j, i+2, j)
				# try move left
				configb, stat = try_move(configb, i, j, i-1, j, i-2, j)
				if stat == 1:
					configb, stat = back_track(configb, n-1)
					if stat == 1:
						return configb, 1
					else:
						undo_move(configb, i, j, i-1, j, i-2, j)
				# try move up
				configb, stat = try_move(configb, i, j, i, j+1, i, j+2)
				if stat == 1:
					configb, stat = back_track(configb, n-1)
					if stat == 1:
						return configb, 1
					else:
						undo_move(configb, i, j, i, j+1, i, j+2)
				# try move down
				configb, stat = try_move(configb, i, j, i, j-1, i, j-2)
				if stat == 1:
					configb, stat = back_track(configb, n-1)
					if stat == 1:
						return configb, 1
					else:
						undo_move(configb, i, j, i, j-1, i, j-2)
	return configb, -1


def print_9x9(configb):
	for i in range(9):
		print configb[i];
	return
fin, val = back_track(board2, 5)
if (val == 1):
	print_9x9(fin)
else:
	print "no solution found"
