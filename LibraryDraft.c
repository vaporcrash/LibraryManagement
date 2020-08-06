#include "Admin.c"
/*
Choose/return book
View Members
*/
void main(){
	system("cls");
	system("color 1F");
	fullscreen();

	int login;int i=0;

	Admin a;Member m,Logger;Book b;

	char UName[20],PW[20];

	TestAdmin(&a);
	TestMember(&m);TestMember(&Logger);
	TestBook(&b);



	do{
		system("cls");
		Valign();Halign();

		printf("---------------------------------------------------------------------------------------------------\n");Halign();
		printf("                                 WELCOME TO SSN LIBRARY                                            \n");Halign();
		printf("---------------------------------------------------------------------------------------------------\n");Halign();

		printf("\t Please choose your login\n ");Halign();
		printf("\t Admin[1]\n");Halign();printf("\t Member[2]\n");Halign();printf("\t Exit[0]\n\t");Halign();
		printf(" Your choice: ");scanf("%d",&login);


		switch(login){
			case 1:
				Halign();
				int i,SuccessLogin=0;

				FILE *f;
				f=fopen("AdminDetails.dat","r");

				printf("Enter username ");scanf("%s",UName);getchar();Halign();
				printf("Enter Password ");//scanf("%s",PW);Halign();
				i=0;PW[0]=getch();

                for( i=0;(i<25)&&(PW[i]!=13)&&(PW[i])&&i>-1;){
                    if(PW[i]=='\b'){
                        printf("\b \b");
                        PW[i]='\0';
                        i-=2;
                    }
                    else
                        printf("*");
                    ++i;
                    PW[i]=getch();
                }
                PW[i+1]='\0';

				fread(&a,sizeof(a),1,f);
				while(!feof(f)){
					if(!strcmp(a.UserName,UName)){
						if(!strcmp(a.Password,PW)){
							SuccessLogin=1;
						}
						else{
							printf("Incorrect Login credentails ");break;
						}
					}
					else{
						printf("Incorrect Login credentials ");break;
					}
					fread(&a,sizeof(a),1,f);
				}
				fclose(f);

				if(SuccessLogin){
					int AdminRight;char cont;
					do{
						system("cls");

						printf("WELCOME ADMIN\n ");
						printf("What would you like to do?\n Member Management[1]\n Edition Management[2]");
						printf("\n Checklist[3]\n Back to Login Screen[0]\n");
						printf(" Your choice: ");scanf("%d",&AdminRight);

						if(AdminRight==1){
							system("cls");
							int MemWork;
							printf("MEMBER MANAGEMENT \n");
							printf("What would you like to do?\n Add Member[1]\n Update Member[2]\n");
							printf(" Remove Member[3]\n View Members[4]\n Back to Admin Page[0]\n");
							printf(" Your choice: ");scanf("%d",&MemWork);

							if(MemWork==1){

                                ReadDetails(&m);
                                FILE *f;
                                f=fopen("MemberDetails.dat","a");
                                if(!f){
                                    printf("ERROR 404! Could not access Member file ");
                                }
                                else
                                    fwrite(&m,sizeof(Member),1,f);

                                fclose(f);


							}
							else if(MemWork==2){
								ReadDetails(&m);
								UpdateMember(m);
							}
							else if(MemWork==3){
								ReadDetails(&m);
								DeleteMember(m);
							}
							else if(MemWork==4){
								DisplayMembers();
							}
							else if(!MemWork)
								printf(" Invalid option ");
							else;
						}
						else if(AdminRight==2){
							system("cls");
							int editWork;
							printf("EDITION MANAGEMENT \n");
							printf("What would you like to do?\n Add Edition[1]\n Remove Edition[2]\n");
							printf(" View Books[3]\n Back to Admin Page[0]\n ");
							printf(" Your choice: ");scanf("%d",&editWork);

							if(editWork==1){
								AddEdition(b);
							}
							else if(editWork==2)
								DeleteEdition(b);
                            else if(editWork==3)
                                DisplayAll();
							else if(!editWork)
								printf(" Invalid option ");
							else;
						}
						else if(AdminRight==3){
							system("cls");
							int choice=5;
							while(choice!=0){
								printf("What do you want to do?\n Create a list[1]\n Add Chore[2] Update Chore status[3]\n");
								printf(" Check list[4]\n Back to Admin Page[0]\n");
								printf(" Your choice: ");scanf("%d",&choice);
								if(choice==1)
								{
									list();
								}
								else if(choice==2)
								{
									add();
								}
								else if(choice==3)
								{
									status();
								}
								else if(choice==4)
								{
									display();
								}
								else if(choice!=0)
                                    printf("Invalid option");
							}

						}
						else if(AdminRight!=0)
							printf("Invalid option\n ");
						else;
						getchar();
						printf("\nDo you want to perform any other operation as ADMIN? (y/n) ");scanf("%c",&cont);
					}while(cont=='y'||cont=='Y');
				}
				break;

			case 2:
				Halign();
				int SuccessfulLogin=0;

				FILE *fp;
				fp=fopen("MemberDetails.dat","r");
				i=0;
				printf("Enter username ");scanf("%s",UName);Halign();
				printf("Enter Password ");

				i=0;PW[0]=getch();
				 for( i=0;(i<25)&&(PW[i]!=13)&&(PW[i])&&i>-1;){
                    if(PW[i]=='\b'){
                        printf("\b \b");
                        PW[i]='\0';
                        i-=2;
                    }
                    else
                        printf("*");
                    ++i;
                    PW[i]=getch();
                }
                PW[i+1]='\0';

				//fread(&m,sizeof(m),1,fp);
				while(!feof(fp)){
				    fread(&m,sizeof(m),1,fp);
					if(!strcmp(m.UserName,UName)){
						if(!strcmp(m.Password,PW)){
							SuccessfulLogin=1;
							Logger=m;break;
						}
						else{
							printf("Incorrect Login credentials ");break;
						}
					}

					//fread(&m,sizeof(m),1,fp);
				}
				fclose(fp);

				if(SuccessfulLogin){

					int MemberRight;char cont;
					do{
						system("cls");

						printf("WELCOME %s\n ",Logger.MemName);
						if(CheckWallet(Logger))
							printf("AMOUNT IN WALLET IS LESS THAN 100. PLEASE RECHARGE\n ");
						printf("What would you like to do?\n Book[1]\n Wallet[2]\n Back to Login Screen[0]\n");
						printf("Your choice: ");scanf("%d",&MemberRight);

						if(MemberRight==1){
							system("cls");
							int MemWork;
							printf("BOOK MANAGEMENT \n");
							printf("What would you like to do?\n Choose Book[1]\n Return Book[2]\n");
							printf(" View books checked out[3]\n Back to Member Page[0]\n");
							printf(" Your choice: ");scanf("%d",&MemWork);

							if(MemWork==1){
								ChooseBook(&Logger);
							}
							else if(MemWork==2)
								ReturnBook(&Logger);
							else if(MemWork==3)
								ViewBooks(Logger);
							else if(MemWork!=0)
								printf(" Invalid option ");
							else;
						}
						else if(MemberRight==2){
							system("cls");
							int WalletWork;
							printf("YOUR WALLET \n");
							printf("What would you like to do?\n Recharge[1]\n View Balance[2]\n Back to Admin Page[0]\n");
							printf(" Your choice: ");scanf("%d",&WalletWork);

							if(WalletWork==1){
								RechargeWallet(Logger);
							}
							else if(WalletWork==2)
								printf("\nYou have %lf left in your wallet\n",CheckBalance(Logger));
							else if(WalletWork!=0)
								printf("\n Invalid option \n");
							else;
						}
						else if(MemberRight!=0)
							printf("\nInvalid option\n ");
						else;
						getchar();
						printf("\nDo you want to perform any other operation as Member? (y/n) ");scanf("%c",&cont);
					}while(cont=='y'||cont=='Y');

				}
				break;

			case 0:
			    system("cls");system("color 0F");
			    for(int i=0;i<3;i++){
                    system("cls");
                    Valign();
                    Halign();printf("TTTTTTTT   HH      HH      AA       NNNN    NN   KK   KK     YY    YY   OOOOOOO  UU    UU\n");
                    Halign();printf("   TT      HH      HH     AA AA     NN NN   NN   KK KK        YY  YY    OO   OO  UU    UU\n");
                    Halign();printf("   TT      HHHHHHHHHH    AAAAAAA    NN  NN  NN   KKKK          YYYY     OO   OO  UU    UU\n");
                    Halign();printf("   TT      HH      HH   AA     AA   NN   NN NN   KK KK          YY      OO   OO  UU    UU\n");
                    Halign();printf("   TT      HH      HH  AA       AA  NN    NNNN   KK   KK        YY      OOOOOOO  UUUUUUUU\n");
                    Sleep(1000);
			    }
				CloseConsole();
				exit(0);break;
			default:
				printf("Invalid option ");break;
		}
		printf("\nPress any key to go back to login screen");getch();
	}while(TRUE);
}
