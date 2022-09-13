#!/usr/bin/env python3

import time

s = "A" * 10000
input("Press to start: ")

for i in range(0, 10):
    s = s + s
    input("Press for next step: ")
