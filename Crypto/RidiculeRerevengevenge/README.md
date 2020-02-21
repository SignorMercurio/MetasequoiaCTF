# Ridicule Rerevengevenge

去[这里](https://sagecell.sagemath.org/)，选择`sage`，然后参考[这篇文章](https://code.felinae98.cn/ctf/crypto/rsa大礼包%EF%BC%88二%EF%BC%89coppersmith-相关)

转成十进制后再用如下代码：
```py
n = 0x2519834a6cc3bf25d078caefc5358e41c726a7a56270e425e21515d1b195b248b82f4189a0b621694586bb254e27010ee4376a849bb373e5e3f2eb622e3e7804d18ddb897463f3516b431e7fc65ec41c42edf736d5940c3139d1e374aed1fc3b70737125e1f540b541a9c671f4bf0ded798d727211116eb8b86cdd6a29aefcc7
e = 3
m = randrange(n)
c = pow(m, e, n)
beta = 1
epsilon = beta ^ 2 / 7
nbits = n.nbits()
kbits = floor(nbits * (beta ^ 2 / e - epsilon))
# mbar = m & (2^nbits-2^kbits)
mbar = 0xb11ffc4ce423c77035280f1c575696327901daac8a83c057c453973ee5f4e508455648886441c0f3393fe4c922ef1c3a6249c12d21a000000000000000000
c = 0x1f6f6a8e61f7b5ad8bef738f4376a96724192d8da1e3689dec7ce5d1df615e0910803317f9bafb6671ffe722e0292ce76cca399f2af1952dd31a61b37019da9cf27f82c3ecd4befc03c557efe1a5a29f9bb73c0239f62ed951955718ac0eaa3f60a4c415ef064ea33bbd61abe127c6fc808c0edb034c52c45bd20a219317fb75
#print "upper %d bits (of %d bits) is given" % (nbits - kbits, nbits)
PR.<x> = PolynomialRing(Zmod(n))
f = (mbar + x) ^ e - c
m
x0 = f.small_roots(X=2 ^ kbits, beta=1)[0]  # find root < 2^kbits with factor = n1
mbar + x0
```

解得:
```
0xb11ffc4ce423c77035280f1c575696327901daac8a83c057c453973ee5f4e508455648886441c0f3393fe4c922ef1c3a6249c12d21a4a8c1d4dec4a0e9bf1
```
则对比原来的16进制发现flag为`flag{4a8c1d4dec4a0e9bf1}`。