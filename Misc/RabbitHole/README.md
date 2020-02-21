# RabbitHole

题目非常明显地提示了`dig`，`text`和`rabbit`，并给了一个url，容易想到DNS查询这个url的TXT记录，查询得到：
```
U2FsdGVkX18BkpB/W9lD7ZGSP5BprjbrL/WKn+7fn8gWCXpmDW+y/5FoVYPd5pIFCZfHFiov
```

看起来像Base64，但是解码得到一串乱码，不过是以`Salted__`开头的，显然是经过了正经的加密。那么加密方式是什么？我们还剩一个线索`rabbit`没有用，猜想使用的是RABBIT加密，丢到在线网站上，无需密钥就能解出flag。