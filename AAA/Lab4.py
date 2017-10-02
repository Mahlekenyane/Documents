import random


move_char = ['u', 'd', 'l', 'r']
random.seed()
start_state = [0,0]
goal_state = [9,9]
moves = [[ 0, 1],[ 0,-1],[-1, 0],[ 1, 0]]
teleport = [
    # [[3, 1], [7, 1], [0, 9], 0.6],
    # [[1, 4], [5, 7], [1, 2], 0.4],
    # [[4, 8], [9, 6], [2, 5], 0.7]
    ]   # teleport cells, new cells, probability of first
barriers = [
    [[0, 1], [1, 1]],
    [[0, 2], [1, 2]],
    [[1, 2], [1, 3]],
    [[0, 5], [0, 6]],
    [[1, 5], [1, 6]],
    [[1, 6], [2, 6]],
    [[1, 7], [2, 7]],
    [[7, 7], [7, 8]],
    [[6, 8], [7, 8]],
    [[6, 1], [7, 1]],
    [[6, 2], [7, 2]],
    [[6, 3], [7, 3]],
    [[8, 0], [8, 1]],
    [[9, 0], [9, 1]]
    ]
partials = [
    [[1, 8], [2, 8]],
    [[6, 9], [7, 9]],
    [[7, 0], [7, 1]]
    ]

def change_state(state, move):
    state_p = [state[0]+move[0], state[1]+move[1]]
    if state_p[0] > 9 or state_p[0] < 0 or state_p[1] > 9 or state_p[1] < 0:
        return state
    return state_p


def change_p_state(state, move):
    state_p = [state[0]+move[0], state[1]+move[1]]
    if state_p[0] > 9 or state_p[0] < 0 or state_p[1] > 9 or state_p[1] < 0:
        return state
    for bar in barriers:
        if (state_p == bar[0] and state == bar[1]) or (state_p == bar[1] and state == bar[0]):
            return state
    for tel in teleport:
        if state_p == tel[0]:   # if teleport state_p
            p = random.uniform(0.0, 1.0)    # uniform probability
            if p < tel[3]:
                return tel[1]
            return tel[2]
    return state_p


def reward_fun(state1, state2):
    if state1 == state2:
        return -5
    if state2 == goal_state:
        return 100
    return -1


def reward_p_fun(state1, state2):
    if state1 == state2:
        return -5.0
    if state2 == goal_state:
        return 100.0
    for par in partials:
        if (state1 == par[0] and state2 == par[1]) or (state1 == par[1] and state2 == par[0]):
            return -3.5
    return -1.0


def p_transition(s, a, s_1):
    s_2 = change_state(s, a)
    if s_1 == s_2:
        return 1
    return 0


def p_p_transition(s, a, s_1):
    s_2 = change_state(s, a)    # if probabilistic, transport cell
    s_3 = change_p_state(s, a)
    if s_2 == s_3:      # deterministic
        if s_1 == s_2:
            return 1
        return 0
    if s_3 == s_1:
        for tel in teleport:    # check if transport cell
            if s_2 == tel[0]:   # it was teleported
                if s_1 == tel[1]:
                    return tel[3]
                return 1.0 - tel[3]
        return 1
    return 0


def update_list(list_new, list_old):
    for _3 in range(10):
        for _4 in range(10):
            list_new[_3][_4] = list_old[_3][_4]
    return list_new


def init_empty_list(my_list):
    for _1 in range(10):
        my_row = []
        for _2 in range(10):
            my_row.append(0)
        my_list.append(my_row)
    return my_list


def e_greedy(q, e, state):
    p = random.uniform(0.0, 1.0)
    a = random.randint(0, 3)
    r = state[0]
    c = state[1]
    if p > e:
        for _i1 in range(4):
            if q[r][c][_i1] > q[r][c][a]:
                a = _i1
    return a


def init_q_list(my_list):
    for _1 in range(10):
        my_row = []
        for _2 in range(10):
            my_row.append([0, 0, 0, 0]) # q value for each s and a
        my_list.append(my_row)
    return my_list


def get_max_value(my_list, s):
    c = 1.0 # gamma
    my_max = None   # this apparently evaluates to be less than all floats, python 2.x
    for m in moves:
        move_value = 0
        for _5 in range(10):
            for _6 in range(10):
                p_val = p_p_transition(s, m, [_5, _6])
                r_val = reward_p_fun(s, [_5, _6])
                v_val = my_list[_5][_6]
                move_value = move_value + p_val * (r_val + c * v_val)
        my_max = max(my_max, move_value)
    return my_max


def value_iteration():
    v_list = []
    d_list = [] # store updates before updating entire list
    init_empty_list(v_list)
    init_empty_list(d_list)
    eps = 5.0
    delt = 2+eps
    while delt > eps:
        delt = 0
        update_list(v_list, d_list)
        for _r in range(10):
            for _c in range(10):
                if goal_state != [_c, _r]:
                    d_list[_r][_c] = get_max_value(v_list, [_r, _c])
                    delt = max(delt, abs(d_list[_r][_c] - v_list[_r][_c]))
    print_value(v_list)
    return


def update_q(q_list, s, a, s_p, a_p, r):
    r1 = s[0]
    c1 = s[1]
    r2 = s_p[0]
    c2 = s_p[1]
    alph = 0.3
    gamm = 1.0
    q_list[r1][c1][a] = q_list[r1][c1][a] + alph * (r + gamm * q_list[r2][c2][a_p] - q_list[r1][c1][a])
    return


def get_policy(my_list, s):
    a = 0
    c = 1.0 # gamma
    my_max = None   # this apparently evaluates to be less than all floats, python 2.x
    for _j in range(4):
        m = moves[_j]
        move_value = 0
        for _5 in range(10):
            for _6 in range(10):
                p_val = p_p_transition(s, m, [_5, _6])
                r_val = reward_p_fun(s, [_5, _6])
                v_val = my_list[_5][_6]
                move_value = move_value + p_val * (r_val + c * v_val)
                if s == [6, 9] and p_val != 0.0:
                    print "[6, 9] is ", my_list[6][9]
                    print "the value to go ", move_char[_j], " is ", move_value, " with p ", p_val, " and new value ", v_val, [_5, _6] , " and reward ", r_val
        if(move_value > my_max):
            my_max = move_value
            a = _j
    return a


def get_max_action(q_list, state):
    a = random.randint(0, 3)
    r1 = state[0]
    c1 = state[1]
    lol = list(range(4))
    random.shuffle(lol)
    for _i7 in lol:
        if q_list[r1][c1][_i7] > q_list[r1][c1][a]:
            a = _i7
    return a


def round_list(q_list):
    for _r in range(10):
        for _c in range(10):
            q_list[_r][_c] = round(max(q_list[_r][_c]), 2)
    return


def sarsa():
    q_list = []
    init_q_list(q_list)
    for _i2 in range(100000):
        e = 0.1
        my_state = start_state  # [random.randint(0, 9), random.randint(0, 9)]
        while  my_state != goal_state:
            a = e_greedy(q_list, e, my_state)
            state_p = change_state(my_state, moves[a])
            r = reward_fun(my_state, state_p)
            a_p = e_greedy(q_list, e, state_p)
            update_q(q_list, my_state, a, state_p, a_p, r)
            my_state = state_p
            a = a_p
    print("RESULT FOR SARSA")
    print_q(q_list)
    return q_list


def q_learning():
    q_list = []
    init_q_list(q_list)
    for _i2 in range(100000):
        e = 0.1
        my_state = start_state  # [random.randint(0, 9), random.randint(0, 9)]
        while  my_state != goal_state:
            a = e_greedy(q_list, e, my_state)   # choose action
            state_p = change_state(my_state, moves[a]) # observe new state
            r = reward_fun(my_state, state_p)   # observe new reward
            a_p = get_max_action(q_list, state_p)
            update_q(q_list, my_state, a, state_p, a_p, r)
            my_state = state_p
    print ("RESULT FOR Q-LEARNING")
    print_q(q_list)
    return q_list


def print_my_list(my_list):
    mx = 6  # max((len(str(ele)) for sub in my_list for ele in sub))
    for _k1 in reversed(range(10)):
        my_string = ""
        for _k2 in range(10):
            my_string += "{:<{mx}}".format(my_list[_k2][_k1],mx=mx)
        print my_string
    return


def print_q(q_list):
    my_policy = []
    for _i8 in range(10):   # row
        my_line = []
        for _i9 in range(10):
            if _i9 == 9 and _i8 == 9:
                my_line.append('0')
            else:
                my_line.append(move_char[get_max_action(q_list, [_i8, _i9])])
        my_policy.append(my_line)
    print_my_list(my_policy)
    round_list(q_list)
    print_my_list(q_list)
    return


def print_value(my_list):
    print("VALUE ITERATION FUNCTION RESULTS...")
    print_my_list(my_list)
    my_policy = []
    for _i8 in range(10):   # row
        my_line = []
        for _i9 in range(10):
            if _i9 == 9 and _i8 == 9:
                my_line.append('0')
            else:
                my_line.append(move_char[get_policy(my_list, [_i8, _i9])])
        my_policy.append(my_line)
    print_my_list(my_policy)
    return


value_iteration()
#sarsa()
#q_learning()
