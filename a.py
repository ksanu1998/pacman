# Heuristic value 1: number of numbers which can fit into a given space
#
#

import sys

def generate_constraints(n, i, j):
    print(n)
    if (n[i][j] != 0):
        return [0, 1, 2, 3, 4]
    l = []
    for i1 in range(4):
        l.append(n[i1][j])
        l.append(n[i][i1])
    if i <= 1 and j <= 1:
        l.append(n[0][0])
        l.append(n[0][1])
        l.append(n[1][0])
        l.append(n[1][1])
    elif i >= 2 and j <= 1:
        l.append(n[2][0])
        l.append(n[2][1])
        l.append(n[3][0])
        l.append(n[3][1])
    elif i <= 1 and j >= 2:
        l.append(n[0][2])
        l.append(n[0][3])
        l.append(n[1][2])
        l.append(n[1][3])
    elif i >= 2 and j >= 2:
        l.append(n[2][2])
        l.append(n[2][3])
        l.append(n[3][2])
        l.append(n[3][3])
    print (l)
    l = list(dict.fromkeys(l)) 
    l1 = [0, 1, 2, 3, 4]
    for i in l:
        l1.remove(i);
    return l1

def generate_full(a):
    k = []
    for i in range(4):
        l = []
        for j in range(4):
            print (i, j)
            l.append((generate_constraints(a, i, j)))
        k.append(l)
    return k

def hill_climb_search(a, k):
    for i in range(4):
        for j in range(4):
            if len(k[i][j]) == 1:
                a[i][j] = k[i][j][0]
                return a
    for i in range(4):
        for j in range(4):
            if len(k[i][j]) == 2:
                a[i][j] = k[i][j][0]
                return a
    

def Possible(k):
    for i in range(4):
        for j in range(4):
            if len(k[i][j]) < 5:
                return True 
    return False

def print_sudoku(a):
    for i in a:
        for j in i:
            print (j, end = " ")
        print ()

def main():
    a = []
    f = open(sys.argv[1], "r+")
    for i in f:
        l = []
        for j in i:
            if j == "\n":
                break;
            l.append(int(j))
        #print (i, end = "")
        a.append(l)
    k = generate_full(a)
    print_sudoku(a)
    print ()
    print ()
    #print (a)
    #print (k)

    while Possible(k):
        a = hill_climb_search(a, k)
        k = generate_full(a)
        #print (a)
        #print (k) 

    print_sudoku(a)    

def main_heuristic_2():
    a = []
    f = open(sys.argv[1], "r+")
    for i in f:
        l = []
        for j in i:
            if j == "\n":
                break;
            l.append(int(j))
        #print (i, end = "")
        a.append(l)
    print_sudoku(a)
    print ()
    print ()

    

main()
