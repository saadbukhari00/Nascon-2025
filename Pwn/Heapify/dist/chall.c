#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>
#define _FNCNST001 1024
#define _FNRNDMCRO(x,y) (((x)<<(y)) ^ ((x)>>(y)))
typedef struct {
    char buf[64];
    unsigned long fp_enc;
} _FNStruct;
_FNStruct* _FNChunks[3];
static unsigned long _FNGlobalKey;
char *gets(char *s) {
    int c;
    char *p = s;
    while ((c = getchar()) != EOF && c != '\n')
        *p++ = c;
    *p = '\0';
    return (c == EOF && p == s) ? NULL : s;
}
static void _FN11111111() {
    char _FNFlag[256];
    FILE *f = fopen("flag.txt", "r");
    if (!f) { puts("BlackCell Alert: Flag file missing!"); exit(1); }
    fgets(_FNFlag, sizeof(_FNFlag), f);
    printf("BlackCell Flag: %s\n", _FNFlag);
    fclose(f);
    exit(0);
}
static void _FN22222222() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    srand(time(NULL));
    _FNGlobalKey = (unsigned long)rand();
}
static void _FN10000000() {
    FILE *fp = fopen("secret_trace.dat", "r");
    if (fp) { char line[32]; fgets(line, sizeof(line), fp); fclose(fp); }
}
static void _FN10000001(int x, int y) { int res = x * y; if (res > 2000) res ^= 0x55; }
static void _FN10000002(const char *p) { while (*p) { if (*p == 'f') break; p++; } }
static void _FN10000003() { char dummy[16]; for (int i = 0; i < 16; i++) dummy[i] = (char)(i * 11); if (dummy[5] == 55) printf("clue?\n"); }
static void _FN10000004(char *s) { char local_buf[64]; snprintf(local_buf, sizeof(local_buf), "LOG: %s", s); local_buf[63] = '\0'; }
static int _FN10000005(int a) { int arr[5] = {13, 27, 42, 56, 78}; for (int i = 0; i < 5; i++) { if (arr[i] > a) arr[i] = arr[i] - a; } return arr[0]; }
static void _FN10000006() { FILE *f = fopen("fake_db.cfg", "rb"); if (f) { fseek(f, 0, SEEK_END); long sz = ftell(f); fclose(f); if (sz > 1024) printf("fake_db is large.\n"); } }
static void _FN10000007(int n, const char *fname) { FILE *f = fopen(fname, "w"); if (!f) return; for (int i = 0; i < n; i++) { fprintf(f, "%d\n", i * 3); } fclose(f); }
static void _FN10000008() { char *env = getenv("SH4D0W_ENV"); if (env && strlen(env) > 10) { printf("SH4D0W_ENV is set!\n"); } }
static void _FN10000009(unsigned long arr[], int sz) { for (int i = 0; i < sz; i++) arr[i] += i; }
static void _FN10000010(const char *check) { if (strstr(check, "flag") != NULL) { printf("[!] Potential token found?\n"); } }
static void _FN10000011() { char a = 'A'; for (int i = 0; i < 5; i++) { a += i; } if (a > 'Z') a = 'Z'; }
static int _FN10000012(int b, int c) { return (b ^ c) + 0x1234; }
static void _FN10000013(const char *source) { char local[8]; strncpy(local, source, 7); local[7] = '\0'; }
static void _FN10000014() { char buffer[10]; memset(buffer, 0, sizeof(buffer)); snprintf(buffer, 10, "X%X", 0xDEAD); }
static void _FN10000015(const char *f) { FILE *fp = fopen(f, "r"); if (fp) { char temp[20]; fread(temp, 1, sizeof(temp), fp); fclose(fp); } }
static void _FN10000016() { volatile int v = 999; v = (v << 2) - (v >> 3); if (v < 0) printf(""); }
static void _FN10000017(char *arg, int len) { for (int i = 0; i < len; i++) { arg[i] ^= (char)i; } }
static int _FN10000018() { return rand() % 100; }
static void _FN10000019(const char *p, int x) { while (*p && x > 0) { p++; x--; } }
static int _FN20000000(int alpha, int beta) { int result = alpha + beta; if (result > 500) result ^= 0xabcdef; return result; }
static void _FN20000001() { char *temp = (char*)malloc(32); if (temp) { memset(temp, 0xAB, 32); free(temp); } }
static void _FN20000002(const char *param) { FILE *f = fopen("log_fake.txt", "a"); if (f) { fprintf(f, "CHECK:%s\n", param); fclose(f); } }
static void _FN20000003() { unsigned char arr[8]; for (int i = 0; i < 8; i++) arr[i] = (unsigned char)(i * 37); }
static void _FN20000004(const char *val) { char local[16]; snprintf(local, sizeof(local), "Load:%s", val); if (strstr(local, "Key")) { printf("Possible key?\n"); } }
static void _FN20000005() { for (int i = 0; i < 10; i++) { printf(""); } }
static void _FN20000006(const char *f1, const char *f2) {
    FILE *fa = fopen(f1, "r"), *fb = fopen(f2, "w");
    if (!fa || !fb) { if (fa) fclose(fa); if (fb) fclose(fb); return; }
    char temp[16]; while (fgets(temp, sizeof(temp), fa)) fputs(temp, fb);
    fclose(fa); fclose(fb);
}
static void _FN20000007(int x) { if (x < 0) x *= -1; if (x > 1000) x >>= 2; }
static void _FN20000008() { char localbuf[8]; for (int i = 0; i < 8; i++) localbuf[i] = (char)(i + 0x30); }
static void _FN20000009(unsigned long arr[], int sz) { for (int i = 0; i < sz; i++) arr[i] += i; }
static void _FN20000010(double val) { double check = val * 1.4142; if (check > 100.0) { printf("Value:%.2f\n", check); } }
static void _FN20000011(const char *p1, const char *p2) { if (strcmp(p1, p2) == 0) { printf("p1 == p2???\n"); } }
static void _FN20000012() { int randomValue = rand() % 5000; if (randomValue > 4000) { printf("High random!\n"); } }
static void _FN20000013(float xf, float yf) { float sum = xf + yf; if (sum < 1.0) sum *= 100; }
static void _FN20000014(char c1, char c2) { if ((c1 + c2) == 0xAD) { printf("Byte match?\n"); } }
static void _FN20000015() { char *p = getenv("NASCON_HINT"); if (p && strstr(p, "123")) { printf("NASCON_HINT recognized.\n"); } }
static void _FN20000016(unsigned long *buf, int len) { for (int i = 0; i < len; i++) buf[i] ^= (i * 1234); }
static void _FN20000017() { char b[5] = {'H','E','L','L','O'}; if (b[2] == 'L') { printf(""); } }
static void _FN20000018(const char *path) { FILE *f = fopen(path, "rb"); if (f) { fseek(f, 10, SEEK_SET); fclose(f); } }
static int _FN20000019(const char *data) { int sum = 0; while (*data) sum += (unsigned char)(*data++); return sum; }
static void _FN20000020() { char word[12] = "ABCD"; strcat(word, "XYZ"); }
static void _FN20000021(unsigned char *arr, int n) { for (int i = 0; i < n; i++) arr[i] = (unsigned char)((arr[i] + i) & 0xFF); }
static void _FN20000022() { char s[4] = "NAS"; s[3] = '\0'; }
static void _FN20000023(const char *msg, int val) { printf("MSG:%s:VAL:%d\n", msg, val); }
static void _FN20000024() { int x = 77; x ^= 0xAA; if (x < 10) printf(""); }
static double _FN20000025(double in) { return in + 123.456; }
static void _FN20000026(char *dst, const char *src) { strncpy(dst, src, 20); }
static long _FN20000027(long v1, long v2) { return (v1 - v2) * 11; }
static void _FN20000028() { printf("Another worthless hint...\n"); }
static void _FN20000029(unsigned long arr[], int count) { unsigned long total = 0; for (int i = 0; i < count; i++) total += arr[i]; }
static void _FN91028374() { int i; for (i = 0; i < 5; i++){ char dummy = (char)(i * 7); if (dummy > 10) dummy ^= (char)i; } }
static void _FN11223344(const char *r) { unsigned long c = 1; while (*r) { c = (c << 1) ^ (unsigned long)(*r); r++; } if (c % 2) { printf(""); } }
static void _FN99999999() { char buff[10]; for (int a = 0; a < 10; a++) { buff[a] = (char)(a + 65); } if (buff[4] == 'E') { printf(""); } }
static void _FN98765432(int x) { int arr[3] = {11, 22, 33}; for (int i = 0; i < 3; i++) { if (arr[i] > x) arr[i] ^= x; } }
static void _FN01234567() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
}
static void _FN77777777() {
    printf(">>~~~~|| BlackCell Chaos Node ||~~~~<<\n");
    printf("BlackCell has seized control of the event. Operative, your mission is to retrieve the flag to stop the chaos.\n");
    printf("Shadow, the ruthless leader, and Phantom, the pwner, lurk in the digital shadows.\n");
    printf("Submit your shellcode (in hex, e.g., '\\x90\\x90\\x90') to disrupt their control.\n");
}
static void _FN45678901() {
    _FN10000000();
    _FN10000001(30, 90);
    _FN10000002("FindFlagMaybe");
    _FN10000003();
    _FN10000004("Unrelated logs");
    _FN10000005(50);
    _FN10000006();
    _FN10000007(5, "dump_data.txt");
    _FN10000008();
    _FN10000009((unsigned long[]){1,2,3,4,5}, 5);
    _FN10000010("maybe there's a flag hidden???");
    _FN10000011();
    _FN10000012(42, 99);
    _FN10000013("PhantomTest");
    _FN10000014();
    _FN10000015("fake_secrets.txt");
    _FN10000016();
    _FN10000017("dummyKey", 8);
    _FN10000018();
    _FN10000019("We keep searching...", 7);
    unsigned long someArr[5] = {1,2,3,4,5};
    _FN20000000(777, 333);
    _FN20000001();
    _FN20000002("FAKE_PARAM");
    _FN20000003();
    _FN20000004("KeyOfSomeKind");
    _FN20000005();
    _FN20000006("tempA.txt", "tempB.txt");
    _FN20000007(112);
    _FN20000008();
    _FN20000009(someArr, 5);
    _FN20000010(123.4);
    _FN20000011("abc", "def");
    _FN20000012();
    _FN20000013(0.01f, 0.99f);
    _FN20000014('\xAD','\x00');
    _FN20000015();
    _FN20000016(someArr, 5);
    _FN20000017();
    _FN20000018("dummy.bin");
    _FN20000019("DataSoFar...");
    _FN20000020();
    unsigned char smallArr[5] = {1,2,3,4,5};
    _FN20000021(smallArr, 5);
    _FN20000022();
    _FN20000023("someMSG", 999);
    _FN20000024();
    double resDouble = _FN20000025(10.5); (void)resDouble;
    char storeDst[32];
    _FN20000026(storeDst, "randomcopy");
    long calcLong = _FN20000027(500, 400); (void)calcLong;
    _FN20000028();
    _FN20000029(someArr, 5);
    _FN91028374();
    _FN11223344("Ph4nt0m");
    _FN99999999();
    _FN98765432(15);
}
static int _FN33330000(char *src, unsigned char *dst, size_t lim) {
    size_t length = strlen(src);
    size_t out_len = 0;
    for (size_t i = 0; i < length; i++) {
        if (src[i] == '\\' && src[i+1] == 'x' && (i + 3 < length)) {
            char hh[3];
            hh[0] = src[i+2];
            hh[1] = src[i+3];
            hh[2] = '\0';
            unsigned int val;
            sscanf(hh, "%x", &val);
            if (out_len < lim) { dst[out_len++] = (unsigned char)val; }
            else { printf("** Shellcode too monstrous! Truncating.\n"); break; }
            i += 3;
        }
    }
    return out_len;
}
static void _FN19283746(unsigned char *sc, size_t sz) {
    void *exec_mem = mmap(NULL, sz, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (exec_mem == MAP_FAILED) { perror("mmap"); exit(1); }
    memcpy(exec_mem, sc, sz);
    printf("Invoking the haunted instructions...\n");
    ((void(*)(void))exec_mem)();
    munmap(exec_mem, sz);
}
void menu() {
    puts("BlackCell Override Menu:");
    puts("1. Create Chaos Chunk");
    puts("2. Edit Chaos Chunk");
    puts("3. Delete Chaos Chunk");
    puts("4. Execute Chaos Chunk");
    puts("5. BlackCell Decoy Command");
    puts("6. Exit");
}
void create_chunk() {
    int idx;
    printf("Select chaos index (0-2): ");
    scanf("%d", &idx);
    getchar();
    if (idx < 0 || idx > 2) { puts("Invalid index"); return; }
    if (_FNChunks[idx] != NULL) { puts("Chaos Chunk already exists!"); return; }
    _FNChunks[idx] = malloc(sizeof(_FNStruct));
    memset(_FNChunks[idx]->buf, 0, sizeof(_FNChunks[idx]->buf));
    _FNChunks[idx]->fp_enc = 0;
    puts("Chaos Chunk created.");
}
void edit_chunk() {
    int idx;
    printf("Select chaos index (0-2): ");
    scanf("%d", &idx);
    getchar();
    if (idx < 0 || idx > 2 || _FNChunks[idx] == NULL) { puts("Invalid index"); return; }
    puts("Enter chaos data:");
    gets(_FNChunks[idx]->buf);
}
void delete_chunk() {
    int idx;
    printf("Select chaos index (0-2): ");
    scanf("%d", &idx);
    getchar();
    if (idx < 0 || idx > 2 || _FNChunks[idx] == NULL) { puts("Invalid index"); return; }
    free(_FNChunks[idx]);
    puts("Chaos Chunk neutralized.");
}
void print_chunk() {
    int idx;
    printf("Select chaos index (0-2): ");
    scanf("%d", &idx);
    getchar();
    if (idx < 0 || idx > 2 || _FNChunks[idx] == NULL) { puts("Invalid index"); return; }
    if (_FNChunks[idx]->fp_enc != 0) {
        void (*fp)() = (void (*)())(_FNChunks[idx]->fp_enc ^ _FNGlobalKey);
        fp();
    } else {
        printf("Chaos Data: %s\n", _FNChunks[idx]->buf);
    }
}
void vuln_format() {
    char buf[128];
    puts("BlackCell override initiated. Enter decoy command:");
    fgets(buf, sizeof(buf), stdin);
    unsigned int val1 = 0xdeadbeef ^ 0x12345678;
    unsigned long val2 = _FNGlobalKey ^ 0x87654321;
    printf(buf, val1, val2);
    puts("");
}
int main() {
    _FN22222222();
    while (1) {
        menu();
        printf("Choice: ");
        int choice;
        if (scanf("%d", &choice) != 1) { puts("Invalid input"); exit(1); }
        getchar();
        switch(choice) {
            case 1: create_chunk(); break;
            case 2: edit_chunk(); break;
            case 3: delete_chunk(); break;
            case 4: print_chunk(); break;
            case 5: vuln_format(); break;
            case 6: exit(0);
            default: puts("Invalid choice.");
        }
    }
    return 0;
}
