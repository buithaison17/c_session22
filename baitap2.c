#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Accounts{
	char email[50], pass[50];
};

void loadToFile(struct Accounts a[], int *sizePtr){
	FILE *file = fopen("accounts.bin", "rb");
	if(file == NULL){
		printf("\nKhong the load file\n\n");
		return;
	}
	(*sizePtr) = 0;
	while(fread(&a[*sizePtr], sizeof(struct Accounts), 1, file) == 1, *sizePtr < 100){
		(*sizePtr)++;
	}
	printf("\nLoad file thanh cong\n\n");
	fclose(file);
}

void saveToFile(struct Accounts a[], int *sizePtr){
	FILE *file = fopen("accounts.bin", "wb");
	if(file == NULL){
		printf("\nKhong the luu file\n\n");
		return;
	}
	fwrite(a, sizeof(struct Accounts), *sizePtr, file);
	fclose(file);
}

void signUp(struct Accounts a[], int *sizePtr){
	fflush(stdin);
	printf("\n------Dang ki tai khoan------");
	printf("\nTai khoan: ");
	fgets(a[*sizePtr].email, 50, stdin);
	a[*sizePtr].email[strcspn(a[*sizePtr].email, "\n")] = '\0';
	printf("Mat khau: ");
	fgets(a[*sizePtr].pass, 50, stdin);
	a[*sizePtr].pass[strcspn(a[*sizePtr].pass, "\n")] = '\0';
	(*sizePtr)++;
	printf("\nDang ki thanh cong!!\n\n");
}

void signIn(struct Accounts a[], int *sizePtr){
	fflush(stdin);
	int found = 0;
	char *email, *pass;
	email = (char *)calloc(50, sizeof(char));
	pass = (char *)calloc(50, sizeof(char));
	printf("\n------Dang nhap------\n");
	printf("Tai khoan: ");
	fgets(email, 50, stdin);
	email[strcspn(email, "\n")] = '\0';
	printf("Mat khau: ");
	fgets(pass, 50, stdin);
	pass[strcspn(pass, "\n")] = '\0';
	for(int i = 0; i < *sizePtr; i++) {
	    if(strcmp(email, a[i].email) == 0) {
	        if(strcmp(pass, a[i].pass) == 0) {
	            found = 1;
	            break;
	        }
	    }
	}
	if(found == 0){
		printf("\nDang nhap that bai\n\n");
	}
	else{
		printf("\nDang nhap thanh cong\n\n");
	}
	free(email);
	free(pass);
}

int main(){
	struct Accounts a[100];
	int choice, size = 0;
	int *sizePtr = &size;
	loadToFile(a, sizePtr);
	do{
		printf("1. Dang nhap\n");
		printf("2. Dang ki\n");
		printf("Nhap chuc nang: ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				signIn(a, sizePtr);
				break;
			case 2:
				signUp(a, sizePtr);
				saveToFile(a, sizePtr);
				break;
			case 3:
				break;
			case 4:
				printf("\nThoat thanh cong");
				break;
			default:
				printf("\nChuc nang khong hop le\n\n");
				break;
		}
	}
	while(choice != 3);
	return 0;
}

