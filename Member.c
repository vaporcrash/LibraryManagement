
#include<time.h>
#include "checklist.c"
#include "Book.c"
#include "Misc.c"
#include<conio.h>

#define MAX_BOOK_LIMIT 5

typedef struct{
	char MemName[50];
	char UserName[20];
	char Password[20];
	int MemID;
	int NoBooks;
	double wallet;
	int flag;
	Book list[MAX_BOOK_LIMIT];
	int DateOfIssue[MAX_BOOK_LIMIT][3];
}Member;

void TestMember(Member *m){
    (*m).MemName[0]='\0';
    (*m).UserName[0]='\0';
    (*m).Password[0]='\0';
    (*m).wallet=0;
    (*m).MemID=0;
    (*m).flag=1;
    (*m).NoBooks=0;
    for(int i=0;i<MAX_BOOK_LIMIT;i++)
        TestBook(&((*m).list[i]));

    for(int i=0;i<MAX_BOOK_LIMIT;i++)
        for(int j=0;j<3;j++)
            (*m).DateOfIssue[i][j]=0;

}
int AssignMemID(){
	Member count;
	int NoM=0;
	FILE *f;
	f=fopen("MemberDetails.dat","r");
	if(!f)
        return 1;
	fread(&count,sizeof(Member),1,f);
	while(!feof(f)){
		NoM++;
		fread(&count,sizeof(Member),1,f);
	}
	return NoM+1;
}

void ReadDetails(Member *m){
	int flag=1;char CheckPassword[20];
	int i=0;
	printf("Enter name: ");scanf("%s",&(m->MemName));
	printf("Enter username: ");scanf("%s",&(m->UserName));
	do{
		printf("Enter password: ");

		i=0;(m->Password)[0]=getch();
        for( i=0;(i<25)&&((m->Password)[i]!=13)&&((m->Password)[i])&&i>-1;){
            if((m->Password)[i]=='\b'){
                printf("\b \b");
                m->Password[i]='\0';
                i-=2;
            }
            else
                printf("*");
            ++i;
            m->Password[i]=getch();
        }
        m->Password[i+1]='\0';
		printf("\n");
		if(strlen(m->Password)<8){
			printf("Minimum length of password to be 8 characters.Please reenter\n ");
			flag=0;
		}
		else{
			printf("Confirm password: ");//scanf("%s",&CheckPassword);
			i=0;

			i=0;CheckPassword[0]=getch();
            for( i=0;(i<25)&&(CheckPassword[i]!=13)&&(CheckPassword[i])&&i>-1;){
                if(CheckPassword[i]=='\b'){
                    printf("\b \b");
                    CheckPassword[i]='\0';
                    i-=2;
                }
                else
                    printf("*");
                ++i;
                CheckPassword[i]=getch();
            }
            CheckPassword[i+1]='\0';

			if(!strcmp(CheckPassword,(m->Password))){
                flag=1;
            }
			if(!flag)
				printf("Incorrect Password. Please re-enter\n ");
		}
	}while(!flag);
	m->MemID=AssignMemID();
	(m->wallet)=100;
	m->NoBooks=0;
	(*m).flag=1;
	for(int i=0;i<MAX_BOOK_LIMIT;i++)
        TestBook(&((*m).list[i]));

    for(int i=0;i<MAX_BOOK_LIMIT;i++)
        for(int j=0;j<3;j++)
            (*m).DateOfIssue[i][j]=0;

}

void Display(Member m){
    if(m.flag){
	printf("------------------------------\n");
	printf("Name :%s\n",m.MemName);
	printf("Username :%s\n",m.UserName);
	printf("Member ID:%d\n",m.MemID);
	printf("Wallet :%lf\n",m.wallet);
	printf("Number of Books:%d\n",m.NoBooks);
	printf("------------------------------\n");
    }
}

void DisplayMembers(){
	FILE *f=NULL;
	Member dummy;
	f=fopen("MemberDetails.dat","r");
	if(!f){
		printf("ERROR 404! Unable to access file ");
	}
	else{
		fread(&dummy,sizeof(dummy),1,f);
		while(!feof(f)){
            //fread(&dummy,sizeof(dummy),1,f);
			Display(dummy);
			fread(&dummy,sizeof(Member),1,f);
        }
        fclose(f);
	}
}

void RechargeWallet(Member m){
	Member dummy;
	FILE *f;
	float recharge;
	f=fopen("MemberDetails.dat","r+");
	if(!f){
		printf("ERROR 404! Could not access Member file");
	}
	else{
		fread(&dummy,sizeof(dummy),1,f);
		while(!feof(f)){
			if(dummy.MemID==0){
				fseek(f,-sizeof(dummy),SEEK_CUR);
				printf("Enter amount you want to recharge with ");scanf("%lf",&recharge);
				(dummy.wallet)+=recharge;
				printf("%d\n",fwrite(&dummy,sizeof(dummy),1,f));fclose(f);
				break;
			}
			fread(&dummy,sizeof(dummy),1,f);
		}
		fclose(f);
	}
}

double CheckBalance(Member m){
    Member dummy;
	FILE *f;

	f=fopen("MemberDetails.dat","r");
	if(!f){
		printf("ERROR 404! Could not access Member file");
	}
	else{
		fread(&dummy,sizeof(m),1,f);
		while(!feof(f)){
			if(dummy.MemID==m.MemID){
                fclose(f);
				return (dummy.wallet);
			}
			fread(&dummy,sizeof(m),1,f);
		}
        fclose(f);
	}
	return 0;
}

int WriteToFile(Member m){
	FILE *f;
	f=fopen("MemberDetails.dat","w");
	if(!f){
		printf("ERROR 404! Could not access Member file ");
		return 0;
	}
	else{
		fwrite(&m,sizeof(m),1,f);fclose(f);
		return 1;
	}

}
int CopyToArray(Member m[]){
    FILE *f;int i=0;
    Member dummy;
    f=fopen("MemberDetails.dat","r");
    if(!f)
        return 0;
    while(!feof(f)){
        fread(&dummy,sizeof(dummy),1,f);
        m[i++]=dummy;
    }
    fclose(f);
    return i;
}

int CheckWallet(Member m){
	return (m.wallet<100)?1:0;
}

void SetDateOfIssue(Member *m){
	time_t t = time(NULL);
	struct tm now = *localtime(&t);

	(*m).DateOfIssue[(*m).NoBooks-1][0]=now.tm_mday;
	(*m).DateOfIssue[(*m).NoBooks-1][1]=now.tm_mon;
	(*m).DateOfIssue[(*m).NoBooks-1][2]=now.tm_year;
}

void ChooseBook(Member *m){
	FILE *book;
	book=fopen("Books.dat","r+");
	Book dummy,b;
	char opt;

	do{
		if((*m).NoBooks>MAX_BOOK_LIMIT)
			printf("\n Maximum limit on number of books reached\n ");
		else{
			//Display books in order of average rating(Sort)
			sortByRating();
			DisplayAll();
			//Allocate memory to list[NoBooks]
			//ReadBook onto the data member list
			getchar();
			printf("Enter the name of the book ");scanf("%[^\n]",&b.name);

			fread(&dummy,sizeof(dummy),1,book);
			while(!feof(book)){
                //fread(&dummy,sizeof(dummy),1,book);
				if(!strcmp(b.name,dummy.name)){
					if(!dummy.copies){
						printf("Sorry, The requested book is out of stock\n");break;
					}
					else{
						int confirm;
						fseek(book,-sizeof(dummy),SEEK_CUR);
						printf("You have chosen this book: \n");
						//DisplayBook and confirm
						DisplayBook(dummy);
						printf("\nPress 1-Confirm ");scanf("%d",&confirm);

						if(confirm){
							dummy.copies--;
							(*m).list[(*m).NoBooks]=dummy;

							fwrite(&dummy,sizeof(dummy),1,book);
							//fread(&dummy,sizeof(dummy),1,book);
							SetDateOfIssue(m);
							(*m).NoBooks++;
							break;
						}
					}
				}
				fread(&dummy,sizeof(dummy),1,book);
			}

		}

		printf("\nDo you want to choose another book? (y/n) ");scanf("%c",&opt);getchar();
	}while(opt=='Y'||opt=='y');
}
/*
void main(){
    Member m,n;
    FILE *f=NULL;
    TestMember(&m);
    f=fopen("MemberDetails.dat","a");
    printf("%d",fwrite(&m,sizeof(m),1,f));
    fclose(f);
    f=fopen("MemberDetails.dat","r");
    fread(&n,sizeof(n),1,f);
    if(!f)
        printf("Unable to access File");
    while(!feof(f)){
        Display(n);
        fread(&n,sizeof(n),1,f);
    }
    fclose(f);

}
*/
int Calc_DayDifference(int *date1,int *date2){
	int NoD1=0,NoD2=0;
	int NoY1=0,NoY2=0;

	/*Difference between date 1 and base date */

	NoY1=*(date1+2)-1900;
	NoD1+=(NoY1*365);
	NoD1+=(NoY1/4);

	switch(*(date1+1)){
		case(12):NoD1+=30;
		case(11):NoD1+=31;
		case(10):NoD1+=30;
		case(9):NoD1+=31;
		case(8):NoD1+=31;
		case(7):NoD1+=30;
		case(6):NoD1+=31;
		case(5):NoD1+=30;
		case(4):NoD1+=31;
		case(3):NoD1+=28;
		case(2):NoD1+=31;
		case(1):break;
	}

	NoD1+=(*(date1)-1);

	/*Difference between date 2 and base date */

	NoY2=*(date2+2)-1900;
	NoD2+=(NoY2*365);
	NoD2+=(NoY2/4);

	switch(*(date2+1)){
		case(12):NoD2+=30;
		case(11):NoD2+=31;
		case(10):NoD2+=30;
		case(9):NoD2+=31;
		case(8):NoD2+=31;
		case(7):NoD2+=30;
		case(6):NoD2+=31;
		case(5):NoD2+=30;
		case(4):NoD2+=31;
		case(3):NoD2+=28;
		case(2):NoD2+=31;
		case(1):break;
	}

	NoD2+=(*(date2)-1);

	int NoD=(NoD1>NoD2)?NoD1-NoD2:NoD2-NoD1;

	return NoD;
}

float calc_Amount(int NoD,float amount){
	float sale=0;
	if(NoD>15)
		sale+=((NoD-15)*10);
	sale+=0.1*amount;
	return sale;
}

void ReturnBook(Member *m){
	Book b;double rate;FILE *f;
	Book dummy;
	int *DateOfReturn;float sale;
	DateOfReturn=(int*)malloc(3*sizeof(int));

	//Enter book to return
	printf("Enter book to return ");scanf("%s",&b.name);

	//Get rating
	printf("Rate your experience on a scale of 0-5 ");scanf("%lf",&rate);

	//Average rating and update the book
	f=fopen("Books.dat","r+");
	fread(&dummy,sizeof(dummy),1,f);
	while(!feof(f)){
		if(!strcmp(b.name,dummy.name)){
			b=dummy;
			double sum=dummy.rating*dummy.borrowed;
			sum+=rate;
			dummy.borrowed++;
			sum/=dummy.borrowed;
			dummy.copies++;

			fseek(f,-sizeof(dummy),SEEK_CUR);
			fwrite(&dummy,sizeof(dummy),1,f);
			break;
		}
		fread(&dummy,sizeof(dummy),1,f);
	}

	//Sort file in order of rating
	sortByRating();

	int index;
	for(int i=0;i<(*m).NoBooks;i++)
		if(!strcmp(((*m).list[i].name),b.name)){
			index=i;break;
		}

	//Get date of return
    printf("Enter the date of return dd mm yyyy");scanf("%d %d %d",(DateOfReturn+0),(DateOfReturn+1),(DateOfReturn+2));
    int NoD=Calc_DayDifference((*m).DateOfIssue[index],DateOfReturn);
    (*m).wallet-=sale;(*m).NoBooks--;
    sale=calc_Amount(NoD,b.price);

	//Calculate amount Calc_Amount(NoD,b.amount)


	//Deduct from wallet

	//Print wallet amount
	printf("\nAmount of %f has been debited to your account. Remaining balance: %f\n",sale,(*m).wallet);
}

void ViewBooks(Member m){
	for(int i=0;i<m.NoBooks;i++)
		DisplayBook(m.list[i]);
}
