// High – Banking System //
#include <stdio.h>
#include <string.h>

#define FILE_NAME "accounts.dat"

struct Account {
    int accNo;
    char name[50];
    float balance;
};

int findAccount(int no, struct Account *out) {
    struct Account a;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == no) { if (out) *out = a; fclose(fp); return 1; }
    }
    fclose(fp);
    return 0;
}

void updateAccount(struct Account *upd) {
    struct Account a;
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) return;
    while (fread(&a, sizeof(a), 1, fp) == 1) {
        if (a.accNo == upd->accNo) {
            fseek(fp, -(long)sizeof(a), SEEK_CUR);
            fwrite(upd, sizeof(*upd), 1, fp);
            break;
        }
    }
    fclose(fp);
}

void createAccount(void) {
    struct Account a;
    printf("Enter new account number: ");
    scanf("%d", &a.accNo);
    if (findAccount(a.accNo, NULL)) { printf("Account already exists!\n"); return; }
    printf("Enter account holder name: ");
    scanf(" %49[^\n]", a.name);
    printf("Enter opening balance: ");
    scanf("%f", &a.balance);
    if (a.balance < 0) { printf("Balance cannot be negative.\n"); return; }
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { printf("File error!\n"); return; }
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    printf("Account created successfully!\n");
}

void deposit(void) {
    struct Account a; int no; float amt;
    printf("Enter account number: "); scanf("%d", &no);
    if (!findAccount(no, &a)) { printf("Account not found.\n"); return; }
    printf("Enter amount to deposit: "); scanf("%f", &amt);
    if (amt <= 0) { printf("Invalid amount.\n"); return; }
    a.balance += amt;
    updateAccount(&a);
    printf("Deposited. New balance: %.2f\n", a.balance);
}

void withdraw(void) {
    struct Account a; int no; float amt;
    printf("Enter account number: "); scanf("%d", &no);
    if (!findAccount(no, &a)) { printf("Account not found.\n"); return; }
    printf("Enter amount to withdraw: "); scanf("%f", &amt);
    if (amt <= 0) { printf("Invalid amount.\n"); return; }
    if (amt > a.balance) { printf("Insufficient balance!\n"); return; }
    a.balance -= amt;
    updateAccount(&a);
    printf("Withdrawn. New balance: %.2f\n", a.balance);
}

void balanceEnquiry(void) {
    struct Account a; int no;
    printf("Enter account number: "); scanf("%d", &no);
    if (!findAccount(no, &a)) { printf("Account not found.\n"); return; }
    printf("Account No: %d\nName: %s\nBalance: %.2f\n", a.accNo, a.name, a.balance);
}

int main(void) {
    int ch;
    do {
        printf("\n===== BANKING SYSTEM =====\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Balance Enquiry\n5. Exit\nEnter choice: ");
        if (scanf("%d", &ch) != 1) { printf("Invalid input.\n"); return 1; }
        switch (ch) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 5: printf("Thank you!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (ch != 5);
    return 0;
}
