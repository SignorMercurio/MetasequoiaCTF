/* gcc -fno-stack-protector -o blacksmith blacksmith.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFSIZE 32

void win()
{
  system("cat flag");
}

void welcome()
{
    puts(" __  __      _                                   _       ");
    puts("|  \\/  |    | |                                 (_)      ");
    puts("| \\  / | ___| |_ __ _ ___  ___  __ _ _   _  ___  _  __ _ ");
    puts("| |\\/| |/ _ \\ __/ _` / __|/ _ \\/ _` | | | |/ _ \\| |/ _` |");
    puts("| |  | |  __/ || (_| \\__ \\  __/ (_| | |_| | (_) | | (_| |");
    puts("|_|  |_|\\___|\\__\\__,_|___/\\___|\\__, |\\__,_|\\___/|_|\\__,_|");
    puts("                                  | |                    ");
    puts("                                  |_|                    ");
}

void menu()
{
    puts("----------BlackSmith----------");
    puts("1. Forge a sword");
    puts("2. Throw a sword");
    puts("3. Show a sword's name");
    puts("4. Rename a sword");
    puts("5. Exit");
    printf("Your choice > ");
}

void forge()
{
    char buf[0x40];
    size_t size = 0;
    puts("Forging...");
    puts("What's the size of this sword's name?");
    scanf("%d", &size);
    if ((int)size >= 0x40) {
        puts("The name is too long!");
        return;
    }
    puts("And the name is?");
    read(0,buf,size);
    puts("Here you are, the new sword!\n");
}

void throw()
{
    int index = 0;
    puts("Which one?");
    scanf("%d", &index);
    puts("Okay. The sword is thrown.\n");
}

void show()
{
    int index = 0;
    puts("Which one?");
    scanf("%d", &index);
    puts("YOU named the sword. Why do you ask me?\n");
}

void reName()
{
    int index = 0;
    puts("Which one?");
    scanf("%d", &index);
    puts("It's disrespecting to rename a sword!\n");
}

int main(int argc, char **argv)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    gid_t gid = getegid();
    setresgid(gid, gid, gid);

    puts("Welcome 2 MetasequoiaCTF!");
    welcome();
    puts("The Demon Dragon has been destroying our world for long. Many others tried their best to fought him, but none of them ever came back. Now, YOU are our only hope...\n");
    puts("First, let our BEST blacksmith gear you up.\n");
    while(1) {
        menu();
        int op = 0;
        scanf("%d", &op);
        switch(op) {
            case 1: forge(); break;
            case 2: throw(); break;
            case 3: show(); break;
            case 4: reName(); break;
            case 5: exit(0); break;
            default: puts("Invalid choice!");
        }
    }
    return 0;
}