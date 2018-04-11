#include "stdio_test.h"

#include <string.h>

#include "stdio.h"

bool test_stdio() {
    puts("* Test getchar");
    puts("Press the ! key. You should see it echoed back.");
    char c = getchar();
    puts("");
    if (c != '!') {
        puts("fail: Received wrong character");
        return false;
    }
    puts("pass");

    puts("* Test gets");
    puts("Type hello. You should see it echoed back.");
    char string[6];
    gets(string, 5);
    puts("");
    if (memcmp(string, "hello\0", 6) != 0) {
        puts("fail: Received wrong characters");
        return false;
    }

    puts("* Test putchar");
    putchar('p');
    putchar('a');
    putchar('s');
    putchar('s');
    puts("");

    puts("* Test puts");
    puts("pass");

    puts("* Test scanf");

    puts("Type hello%. You should see it echoed back.");
    scanf("hello%%");
    puts("");
    
    char string1[10];
    unsigned long u1;

    puts("Type hello and press ENTER. You should see it echoed back.");
    memset(string1, 1, 10);
    scanf("%s\r", string1);
    if (memcmp(string1, "hello\0", 6)) {
        puts("fail: Did not receive hello");
        return false;
    }

    puts("Type 1 and press ENTER. You should see it echoed back.");
    u1 = 0;
    scanf("%u\r", &u1);
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return false;
    }

    puts("Type hello 1 world 2 and press ENTER. You should see it echoed back.");
    memset(string1, 1, 10);
    u1 = 0;
    scanf("%s 1 world %u\r", string1, &u1);
    if (memcmp(string1, "hello\0", 6) != 0) {
        puts("fail: Did not receive hello");
        return false;
    }
    if (u1 != 2) {
        puts("fail: Did not receive 2");
        return false;
    }

    puts("Type hello 1 world 2 and press ENTER. You should see it echoed back.");
    memset(string1, 1, 10);
    u1 = 0;
    scanf("hello %u %s 2\r", &u1, string1);
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return false;
    }
    if (memcmp(string1, "world\0", 6) != 0) {
        puts("fail: Did not receive world");
        return false;
    }

    char string2[10];
    unsigned long u2;

    puts("Type hello 1 world 2 and press ENTER. You should see it echoed back.");
    memset(string1, 1, 10);
    memset(string2, 1, 10);
    u1 = 0;
    u2 = 0;
    scanf("%s %u %s %u\r", string1, &u1, string2, &u2);
    if (memcmp(string1, "hello\0", 6) != 0) {
        puts("fail: Did not receive hello");
        return false;
    }
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return false;
    }
    if (memcmp(string2, "world\0", 6) != 0) {
        puts("fail: Did not receive world");
        return false;
    }
    if (u2 != 2) {
        puts("fail: Did not receive 2");
        return false;
    }

    puts("* Test printf");
    puts("You should 3 lines of text repeated twice.");
    puts("hello");
    puts("hello world");
    puts("hello 1 world 2 !");
    printf("hello\r\n");
    printf("hello %s\r\n", "world");
    printf("hello %u %s %u !\r\n", 1, "world", 2);

    return true;
}
