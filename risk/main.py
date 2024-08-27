import random
import time

def run_one_round():
    sorted_rolls = sorted([random.randint(1,6), random.randint(1,6), random.randint(1,6)])[::-1]
    sorted_defense = sorted([random.randint(1,6), random.randint(1,6)])[::-1]
    lost_defending = 0

    if sorted_rolls[0] > sorted_defense[0]:
        lost_defending += 1
    
    if sorted_rolls[1] > sorted_defense[1]:
        lost_defending += 1
    
    return 2 - lost_defending

def run_1000_times():
    total = 0
    for _ in range(10000000):
        total += run_one_round()

    print(total / 10000000)

start = time.perf_counter()
run_1000_times()
end = time.perf_counter()

print(end - start)