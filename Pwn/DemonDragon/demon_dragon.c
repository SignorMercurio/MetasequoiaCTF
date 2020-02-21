/* gcc -fno-stack-protector -o demon_dragon demon_dragon.c -L. -lmagic */
#include "magic.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

void shuffle(int *array, int n, int num_shuffles)
{ 
    srand((unsigned)time(NULL)); 
    for (int j = 0; j < num_shuffles; j++) { 
        for (int i = 0; i < n - 1; i++) { 
            size_t j = i + rand()/(RAND_MAX/(n - i) + 1); 
            int t = array[j]; 
            array[j] = array[i]; 
            array[i] = t; 
        } 
    } 
}

int cnt = 0;
int pos[5] = {0,1,2,3,4};

void fill_plt()
{
    gold_shield(1);
    wood_shield(1,2);
    water_shield(1,2,3);
    fire_shield(1,2);
    earth_shield(1);
    check(pos);
}

void black_magic()
{
    asm("pop %rdi\n\t"
        "pop %rsi\n\t"
        "pop %rdx\n\t"
        "ret\n\t");
}

void fight()
{
    char elements[5][6] = {"gold","wood","water","fire","earth"};
    shuffle(pos,5,10);
    puts("Finally, you're standing in front of the Demon Dragon...\n");
    printf("Suddenly, the Demon Dragon attacked you with %s, %s, %s, %s, %s!\n\n",elements[pos[0]], elements[pos[1]], elements[pos[2]], elements[pos[3]], elements[pos[4]]);
    printf("What are you going to do?!!\nSkill > ");
    char buf[0x20];
    gets(buf);
}

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    gid_t gid = getegid();
    setresgid(gid, gid, gid);
    fill_plt();
    fight();
    puts("You die!");
    return 0;
}