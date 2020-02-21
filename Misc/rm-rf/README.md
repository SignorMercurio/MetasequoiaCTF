# rm -rf /

出题人背锅的一道题，存在很多非预期解。

预期解法是

```bash
while read -r line;do echo $line;done</.flag
```

但实际做下来发现，因为没有对输入进行限制，`sed`等命令就可以读到flag。删去的命令基本上是`cat, grep, head,more, tail, less, base64`等，其实还删去了`/usr/bin/`下的内容。