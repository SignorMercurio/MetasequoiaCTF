from Crypto.Util import number
from gmpy2 import *

# enc
n_length = 2048
p = number.getPrime(n_length)
q = number.getPrime(n_length)
n = p*q
print(n)
phi = (p-1)*(q-1)

e1 = 65537
e2 = 395327
d1 = invert(e1,phi)
d2 = invert(e2,phi)

#flag = b'flag{rS4_c0mOon_MOdu1u5_a7k}'
flag = b'7=28LC$c04_>~@?0|~5F`Fd02f<N'
flag = number.bytes_to_long(flag)
c1 = powmod(flag,e1,n)
c2 = powmod(flag,e2,n)
print(c1)
print(c2)

# dec
def exgcd(a,b):
    if b==0:
        return 1, 0, a
    x2, y2, r = exgcd(b, a%b)
    x1 = y2
    y1 = x2-(a//b)*y2
    return x1, y1, r

s1,s2,t = exgcd(e1,e2)
m = powmod(c1,s1,n) * powmod(c2,s2,n) % n
print(number.long_to_bytes(m))
