#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    int n;
    int i, j;
    struct UserAccount users[100];
    struct UserAccount temp;
    
    int initial_mrr = 0;
    int actual_mrr = 0;

    do {
        printf("Nhap so luong tai khoan (1 <= N <= 100): ");
        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            n = 0;
            continue;
        }
        if (n < 1 || n > 100) {
            printf("Loi: So luong tai khoan phai nam trong khoang [1, 100]. Nhap lai!\n");
        }
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan [%d] ---\n", i + 1);
        
        printf("Nhap Ma tai khoan (account_id): ");
        scanf("%d", &users[i].account_id);

        do {
            printf("Nhap Loai goi (0: Free, 1: Standard, 2: Premium): ");
            if (scanf("%d", &users[i].plan_type) != 1) {
                while (getchar() != '\n');
                users[i].plan_type = -1;
            }
        } while (users[i].plan_type < 0 || users[i].plan_type > 2);

        printf("Nhap Phi goi cuoc ban dau (monthly_fee): ");
        scanf("%d", &users[i].monthly_fee);

        printf("Nhap So ngay con lai (remaining_days - co the am): ");
        scanf("%d", &users[i].remaining_days);

        printf("Nhap So thiet bi dang ket noi (active_devices): ");
        scanf("%d", &users[i].active_devices);

        if (users[i].plan_type > 0) {
            initial_mrr += users[i].monthly_fee;
        }
    }

    for (i = 0; i < n; i++) {
        if (users[i].active_devices <= 0) {
            users[i].active_devices = 1;
        }

        if (users[i].remaining_days <= 0) {
            users[i].plan_type = 0;
            users[i].monthly_fee = 0;
        } 
        else {
            if (users[i].plan_type == 1) {
                users[i].monthly_fee = 120000;
            } else if (users[i].plan_type == 2) {
                users[i].monthly_fee = 300000;
            } else {
                users[i].monthly_fee = 0;
            }
        }

        if (users[i].plan_type == 1 && users[i].active_devices > 2) {
            users[i].active_devices = 2;
        } else if (users[i].plan_type == 2 && users[i].active_devices > 5) {
            users[i].active_devices = 5;
        } else if (users[i].plan_type == 0 && users[i].active_devices > 1) {
            users[i].active_devices = 1;
        }

        actual_mrr += users[i].monthly_fee;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int should_swap = 0;

            if (users[j].plan_type == 0 && users[j + 1].plan_type > 0) {
                should_swap = 1;
            }
            else if (users[j].plan_type > 0 && users[j + 1].plan_type > 0) {
                if (users[j].monthly_fee < users[j + 1].monthly_fee) {
                    should_swap = 1;
                }
            }

            if (should_swap) {
                temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }

    printf("\n================================ DANH SACH TAI KHOAN SAU KIEM TOAN ================================\n");
    printf("%-10s %-12s %-15s %-18s %-15s\n", 
           "MA TK", "GOI CUOC", "PHI THANG (VND)", "NGAY CON LAI", "THIET BI");
    printf("--------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-10d %-12d %-15d %-18d %-15d\n",
               users[i].account_id,
               users[i].plan_type,
               users[i].monthly_fee,
               users[i].remaining_days,
               users[i].active_devices);
    }

    printf("--------------------------------------------------------------------------------------------------\n");
    printf(" Doanh thu MRR du kien ban dau : %d VND\n", initial_mrr);
    printf(" Doanh thu MRR thuc te ghi nhan: %d VND\n", actual_mrr);
    printf(" Chech lech doanh thu (Loi/That thoat): %d VND\n", initial_mrr - actual_mrr);
    printf("==================================================================================================\n");

    return 0;
}
