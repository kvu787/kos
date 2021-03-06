#include "stdio_test.h"

#include "../io.h"
#include "../memory.h"

static bool_t test_sscanf(void);
static void test_stdio_output(void);
static bool_t test_stdio_input(void);

bool_t test_stdio(void) {
    if (!test_sscanf()) {
        return FALSE;
    }
    return TRUE;
}

bool_t test_stdio_interactive(void) {
    test_stdio_output();
    if (!test_stdio_input()) {
        return FALSE;
    }
    return TRUE;
}

static bool_t test_sscanf(void) {
    char_t string1[10];
    char_t string2[10];
    uint_t u1;
    uint_t u2;

    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    sscanf("112", "%u", &u1);
    if (u1 != 112) {
        puts("fail: Did not receive 112");
        return FALSE;
    }

    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    sscanf("hello 1 % world 2", "%s %u %% %s %u", string1, &u1, string2, &u2);
    if (!memory_equals(string1, "hello\0", 6)) {
        puts("fail: Did not receive hello");
        return FALSE;
    }
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return FALSE;
    }
    if (!memory_equals(string2, "world\0", 6)) {
        puts("fail: Did not receive world");
        return FALSE;
    }
    if (u2 != 2) {
        puts("fail: Did not receive 2");
        return FALSE;
    }

    sscanf("hello%", "hello%%");

    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    sscanf("hello\r", "%s\r", string1);
    if (!memory_equals(string1, "hello\0", 6)) {
        puts("fail: Did not receive hello");
        return FALSE;
    }

    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    sscanf("1\r", "%u\r", &u1);
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return FALSE;
    }

    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    sscanf("hello 1 world 2 \r", "%s 1 world %u\r", string1, &u1);
    if (!memory_equals(string1, "hello\0", 6)) {
        puts("fail: Did not receive hello");
        return FALSE;
    }
    if (u1 != 2) {
        puts("fail: Did not receive 2");
        return FALSE;
    }

    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    sscanf("hello 1 world 2\r", "hello %u %s 2\r", &u1, string1);
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return FALSE;
    }
    if (!memory_equals(string1, "world\0", 6)) {
        puts("fail: Did not receive world");
        return FALSE;
    }

    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    sscanf("hello 1 world 2\r", "%s %u %s %u\r", string1, &u1, string2, &u2);
    if (!memory_equals(string1, "hello\0", 6)) {
        puts("fail: Did not receive hello");
        return FALSE;
    }
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return FALSE;
    }
    if (!memory_equals(string2, "world\0", 6)) {
        puts("fail: Did not receive world");
        return FALSE;
    }
    if (u2 != 2) {
        puts("fail: Did not receive 2");
        return FALSE;
    }

    return TRUE;
}

static bool_t test_stdio_input() {
    puts("* Test getchar");
    puts("Press the ! key. You should see it echoed back.");
    char_t c = getchar();
    puts("");
    if (c != '!') {
        puts("fail: Received wrong character");
        return FALSE;
    }
    puts("pass");

    puts("* Test gets");
    puts("Type hello. You should see it echoed back.");
    char_t string[6];
    gets(string, 5);
    puts("");
    if (!memory_equals(string, "hello\0", 6)) {
        puts("fail: Received wrong characters");
        return FALSE;
    }

    puts("* Test scanf");

    char_t string1[10];
    char_t string2[10];
    uint_t u1;
    uint_t u2;

    puts("Type hello 1 world 2 and press ENTER. You should see it echoed back.");
    memory_set(string1, 10, 1);
    memory_set(string2, 10, 1);
    u1 = 0;
    u2 = 0;
    scanf("%s %u %s %u\r", string1, &u1, string2, &u2);
    if (!memory_equals(string1, "hello\0", 6)) {
        puts("fail: Did not receive hello");
        return FALSE;
    }
    if (u1 != 1) {
        puts("fail: Did not receive 1");
        return FALSE;
    }
    if (!memory_equals(string2, "world\0", 6)) {
        puts("fail: Did not receive world");
        return FALSE;
    }
    if (u2 != 2) {
        puts("fail: Did not receive 2");
        return FALSE;
    }

    puts("Press the ! key. You should not see it echoed back");
    getchar_silent();

    return TRUE;
}

static void test_stdio_output(void) {
    puts("* Test putchar");
    putchar('p');
    putchar('a');
    putchar('s');
    putchar('s');
    puts("");

    puts("* Test puts");
    puts("pass");

    puts("* Test printf");
    puts("You should see the following 5 lines repeated twice.");
    puts("hello");
    puts("hello world");
    puts("hello 1 world 2 !");
    puts("pi = 3.14");
    puts("double = -8.19");
    printf("hello\r\n");
    printf("hello %s\r\n", "world");
    printf("hello %u %s %u !\r\n", 1, "world", 2);
    printf("pi = %d\r\n", 3.14159);
    printf("double = %d\r\n", -8.19378);
}
