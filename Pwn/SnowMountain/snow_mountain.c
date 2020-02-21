/* gcc -fno-stack-protector -z execstack -o snow_mountain snow_mountain.c */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ACCURACY 1337

typedef void (fn_t)(void);

void initialize()
{
    printf("You set off, and travel a long way");
    for (int i = 0; i < 10; ++i) {
        usleep(300000);
        printf(".");
    }
    puts("Until you are blocked by a snow mountain.\n");
}

void *query_position()
{
  char stk;
  int offset = rand() % ACCURACY - (ACCURACY / 2);
  void *ret = &stk + offset;
  return ret;
}


int main() {
    setbuf(stdout, NULL);

    char buffer[0x1000];
    srand((unsigned) (uintptr_t) buffer);

    initialize();

    puts("You know you have to conquer the mountain before you fight with the Demon Dragon. Luckily, you've prepared a sled for skiing.\n");
    printf("You check the map again. You need to reach the lair of the Demon Dragon.\nCurrent position: %p\n\n", query_position());

    printf("What's your plan, hero?\n> ");
    fgets(buffer, sizeof(buffer), stdin);

    fn_t *location;

    printf("Where are you going to land?\n> ");
    scanf("%p", (void**) &location);

    location();
    return 0;
}