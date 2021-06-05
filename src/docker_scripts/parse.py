from sys import stdin

def parse_line(line):
    ip, mask = line.strip().split('/')

    lower_bound = 0
    for i, byte in enumerate(ip.split('.')[::-1]):
        lower_bound |= (int(byte) << (8 * i))

    end_ones = (1 << (32 - int(mask))) - 1
    assert (lower_bound & end_ones) == 0
    upper_bound  = lower_bound | end_ones

    return lower_bound, upper_bound

lines = stdin.readlines()

ip_ranges = [ parse_line(line) for line in lines ]

for a, b in ip_ranges:
    assert a <= b
    print(a, b)
