import itertools
import random

x, y = map(int, input("ipucu: ").split(','))
ipucu = (x,y)


answer = 0
a = range(1,7)
b = 4

possibilities = [p for p in itertools.product(a, repeat=b)]

# choosen = random.choice(possibilities) 

choosen = (1,2,3,4)



table = {}

for posibility in possibilities:
    white = 0
    black = 0
    counted = []

    for i in range(b):
        if choosen[i] == posibility[i]:
            black += 1
    
    for e in choosen:
        if e in counted:
            continue
        
        e_count = choosen.count(e)
        p_count = posibility.count(e)

        counted.append(e)

        if p_count == 0:
            continue

        white += p_count if e_count > p_count else e_count
    
    white -= black

    table[posibility] = (black, white)


for key, value in table.items():
    if value == ipucu:
        answer += 1

print("cevap:", answer)