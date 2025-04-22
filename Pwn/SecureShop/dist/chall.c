#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char global_username[] = "S3c5r1ty_3ng1n33r";

char encoded_pass[] = "SHB;#@{r";
int pass_len = 8;

void secure_unlock() {
    FILE *f = fopen("flag.txt", "r");
    if (f == NULL) {
        printf("Flag file not found!\n");
        exit(1);
    }
    char flag[100];
    fgets(flag, sizeof(flag), f);
    printf("%s\n", flag);
    fclose(f);
}

void secure_dummy1() {
    int a = 42, b = 84;
    printf("Security Log 1: %d\n", a + b);
}

void secure_dummy2() {
    char buf[16];
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "Encrypting");
    printf("Security Log 2: %s\n", buf);
}

void secure_dummy3() {
    int x = 100, y = 200;
    printf("Security Log 3: %d\n", x * y);
}

void secure_dummy4() {
    for (int i = 0; i < 5; i++) {
         printf("Security Loop %d\n", i);
    }
}

void secure_dummy5() {
    int arr[10];
    for (int i = 0; i < 10; i++) {
         arr[i] = i * i;
    }
    printf("Array Security Check Passed.\n");
}

typedef void (*sec_func_ptr)();
void secure_dummy_table() {
    sec_func_ptr funcs[3] = {secure_dummy1, secure_dummy2, secure_dummy3};
    for (int i = 0; i < 3; i++) {
         funcs[i]();
    }
}

void security_obfuscator() {
    secure_dummy3();
    secure_dummy1();
    secure_dummy5();
    secure_dummy2();
    secure_dummy4();
    secure_dummy_table();
}

int auth_portal() {
    char username_input[32];
    char password_input[32];
    
    printf("== SecureShop Authentication Portal ==\n");
    printf("Username: ");
    scanf("%31s", username_input);
    printf("Password: ");
    scanf("%31s", password_input);
    
    // Check username
    if (strcmp(username_input, global_username) != 0) {
        return 0;
    }
    
    char decoded[32];
    for (int i = 0; i < pass_len; i++) {
        decoded[i] = (((encoded_pass[i] - 32) - (i + 3) - ((i % 3) * 4) + 95) % 95) + 32;
    }
    decoded[pass_len] = '\0';
    
    if (strcmp(password_input, decoded) != 0) {
        return 0;
    }
    
    return 1;
}

int compute_cost(int price, int quantity) {
    int modifier = ((price & 0xFF) % 7) - ((quantity & 0xFF) % 5);
    int total = price * quantity - modifier;
    return total;
}

void purchase_item() {
    int price, quantity;
    printf("\n== SecureShop Purchase Interface ==\n");
    printf("Enter item price: ");
    scanf("%d", &price);
    printf("Enter quantity: ");
    scanf("%d", &quantity);
    
    printf("Calculating total cost...\n");
    int total = compute_cost(price, quantity);
    printf("Total cost: %d\n", total);
    
    if (total < 0) {
        printf("Overflow exploited! Accessing secure vault...\n");
        secure_unlock();
    } else {
        printf("Transaction complete. Thank you for shopping at SecureShop.\n");
    }
}

int main() {
    setbuf(stdout, NULL);
    printf("Welcome to the SecureShop Challenge!\n");
    
    security_obfuscator();
    
    if (!auth_portal()) {
        printf("Authentication failed! Exiting...\n");
        exit(1);
    }
    
    printf("Authentication successful. Proceeding to purchase interface.\n");
    purchase_item();
    
    return 0;
}
