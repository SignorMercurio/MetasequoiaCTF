#include "magic.h"

char flag[5] = {-1,-1,-1,-1,-1};
int cnt = 0;

void gold_shield(int a)
{
    if (a == 0xdeadbeef) {
        flag[cnt++] = 1;
        puts("Gold Shield Activated!");
    }
}
void wood_shield(int a, int b)
{
    if (a == 0xcafebabe && b == 0xdeadbaad) {
        flag[cnt++] = 4;
        puts("Wood Shield Activated!");
    }
}
void water_shield(int a, int b, int c)
{
    if (a == 0xbaaaaaad && b == 0x8badf00d && c == 0xd15ea5e) {
        flag[cnt++] = 3;
        puts("Water Shield Activated!");
    }
}
void fire_shield(int a, int b)
{
    if (a == 0xdeadbabe && b == 0xdeadfa11) {
        flag[cnt++] = 0;
        puts("Fire Shield Activated!");
    }
}
void earth_shield(int a)
{
    if (a == 0xfee1dead) {
        flag[cnt++] = 2;
        puts("Earth Shield Activated!");
    }
}

void check(int pos[])
{
    int i;
    for (i = 0; i < 5; ++i) {
        if (flag[i] != pos[i]) break;
    }
    if (i == 5) system("cat flag");
}