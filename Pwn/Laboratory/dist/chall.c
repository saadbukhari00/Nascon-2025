#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define _FNCNST001      1024
#define _FNRNDMCRO(x,y) (((x)<<(y)) ^ ((x)>>(y)))

static void _FN91028374() {
    int i; 
    for (i = 0; i < 5; i++){
        char dummy = (char)(i*7);
        if (dummy > 10) dummy ^= (char)i;
    }
}
static void _FN11223344(const char *r) {
    unsigned long c = 1;
    while (*r) {
        c = (c << 1) ^ (unsigned long)(*r);
        r++;
    }
    if (c % 2) {
        printf("");
    }
}
static void _FN99999999() {
    char buff[10];
    for (int a=0; a<10; a++){
        buff[a] = (char)(a + 65);
    }
    if (buff[4] == 'E') {
        printf("");
    }
}
static void _FN98765432(int x) {
    int arr[3] = {11, 22, 33};
    for (int i=0; i<3; i++){
        if (arr[i] > x) {
            arr[i] ^= x;
        }
    }
}


static void _FN01234567() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin,  NULL, _IONBF, 0);
}


static void _FN77777777() {
    printf("Shadow Code's Lab\n");
    printf("Welcome to the secret testing node.\n");
    printf("Present your specialized shellcode, mortal.\n");
    printf("Use hex bytes like '\\x90\\x90\\x90' if you dare...\n");
}

static void _FN45678901() {
    _FN91028374();
    _FN11223344("Ph4nt0m");
    _FN99999999();
    _FN98765432(15);
}

static int _FN33330000(char *src, unsigned char *dst, size_t lim) {
    size_t length = strlen(src);
    size_t out_len = 0;
    for (size_t i=0; i < length; i++) {
        if (src[i] == '\\' && src[i+1] == 'x' && (i+3 < length)) {
            char hh[3];
            hh[0] = src[i+2];
            hh[1] = src[i+3];
            hh[2] = '\0';
            unsigned int val;
            sscanf(hh, "%x", &val);
            if (out_len < lim) {
                dst[out_len++] = (unsigned char)val;
            } else {
                printf("** Shellcode too monstrous! Truncating.\n");
                break;
            }
            i += 3;
        }
    }
    return out_len;
}

static void _FN19283746(unsigned char *sc, size_t sz) {
    void *exec_mem = mmap(NULL, sz, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (exec_mem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    memcpy(exec_mem, sc, sz);
    printf("Invoking the haunted instructions...\n");
    ((void(*)(void))exec_mem)();
    munmap(exec_mem, sz);
}

int main() {
    char    _local_input[_FNCNST001];
    unsigned char _shell_area[_FNCNST001];
    size_t  sc_size;
    _FN01234567();
    _FN45678901();
    _FN77777777();
    printf(">>> Offer your hex-coded incantations:\n");
    printf("> ");
    if (!fgets(_local_input, _FNCNST001, stdin)) {
        printf("~~ Cursed silence...no input found.\n");
        return 1;
    }
    _local_input[strcspn(_local_input, "\n")] = '\0';
    sc_size = _FN33330000(_local_input, _shell_area, _FNCNST001);
    printf("** Detected %zu bytes within your creation.\n", sc_size);
    if (sc_size < 10) {
        printf("** Too feeble. Minimum accepted size: 10 bytes.\n");
        return 1;
    }
    _FN19283746(_shell_area, sc_size);
    int obf_var = (int)sc_size;
    obf_var = _FNRNDMCRO(obf_var, 3);
    _FN98765432(obf_var);
    return 0;
}
