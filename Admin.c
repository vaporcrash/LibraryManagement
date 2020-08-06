
#include "Member.c"


typedef struct{
	char AdminName[50];
	char UserName[20];
	char Password[20];
	int AdminID;

}Admin;

void TestAdmin(Admin *a){
    (*a).AdminName[0]='\0';
    (*a).UserName[0]='\0';
    (*a).Password[0]='\0';
    (*a).AdminID=0;
}
void ReadAdmin(Admin *a){
	int flag=1;char CheckPassword[20];
	int i=0;
	printf("Enter name: ");scanf("%s",&(a->AdminName));
	printf("Enter username: ");scanf("%s",&(a->UserName));
	do{
		printf("Enter password: ");//scanf("%s",&(a->Password));
		do{
			a->Password[i]=getch();
			if(isalnum(a->Password[i]))
				printf("*");
		}while(a->Password[i++]!='\n');
		a->Password[i]='\0';
		printf("\n");
		if(strlen(a->Password)<8){
			printf("Minimum length of password to be 8 characters.Please reenter\n ");
			flag=0;
		}

		else{
			printf("Confirm password: ");//scanf("%s",&CheckPassword);
			i=0;
			do{
				CheckPassword[i]=getch();
				if(isalnum(CheckPassword[i]))
					printf("*");
			}while(CheckPassword[i++]!='\n');
			CheckPassword[i]='\0';

			if(!strcmp(CheckPassword,(a->Password)))
				flag=0;
			if(flag)
				printf("Incorrect Password. Please re-enter\n ");
		}
	}while(flag);
	(*a).AdminID=1;
}

int WriteAdminFile(Admin a){
	FILE *f;
	f=fopen("AdminDetails.dat","a");
	if(!f){
		printf("ERROR 404! Could not access Admin file ");
		return 0;
	}
	else{
		fwrite(&a,sizeof(a),1,f);fclose(f);
		return 1;
	}

}

int AddMember(Member m){
	FILE *f;
	f=fopen("MemberDetails.dat","a");
	if(!f){
		printf("ERROR 404! Could not access Member file");
		return 0;
	}
	else{
		fwrite(&m,sizeof(m),1,f);fclose(f);
		return 1;
	}
}

int UpdateMember(Member m){
	Member dummy;
	FILE *f;
	f=fopen("MemberDetails.dat","a");
	if(!f){
		printf("ERROR 404! Could not access Member file");
		return 0;
	}
	else{
		fread(&dummy,sizeof(m),1,f);
		while(!feof(f)){
			if(dummy.MemID=m.MemID){
				fseek(f,-sizeof(m),SEEK_CUR);
				fwrite(&m,sizeof(m),1,f);fclose(f);return 1;
			}
			fread(&dummy,sizeof(m),1,f);
		}
		fclose(f);
	}
}

int DeleteMember(Member m){
	Member dummy;
	FILE *f;
	f=fopen("MemberDetails.dat","a");
	if(!f){
		printf("ERROR 404! Could not access Member file");
		return 0;
	}
	else{
		fread(&dummy,sizeof(m),1,f);
		while(!feof(f)){
			if(dummy.MemID=m.MemID){
				fseek(f,-sizeof(m),SEEK_CUR);
				m.flag=0;
				fwrite(&m,sizeof(m),1,f);fclose(f);return 1;
			}
			fread(&dummy,sizeof(m),1,f);
		}
	}
}

void AddEdition(){
	create();
}
