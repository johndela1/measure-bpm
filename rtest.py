#!/usr/bin/python3

from sys import stdin
from time import sleep, time

bpm = 80
count = 4
tol = .05
t2 = 0

dur = 60 / bpm

for b in range(1, count+1):
    sleep(dur)
    print(b)

t2 = time()

for b in range(1, count+1):
    stdin.readline()
    t1 = t2
    t2 = time()
    err = (t2 - t1) - dur
    print(err)
    if abs(err) > tol:
        print('fail')
        exit() 
print('pass')
