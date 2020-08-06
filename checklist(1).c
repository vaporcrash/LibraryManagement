#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
	char chore[200];
	char status;
}duty;
void list()
{
	FILE *fp;
	duty x;
	fp=fopen("Checklist.dat","w");
	printf("Enter the chore to be added:\n");
	getchar();
	scanf("%[^\n]",x.chore);
	printf("Print the status\nC for complete, I for incomplete\n");
	getchar();
	scanf("%c",&x.status);
	fwrite(&x,sizeof(x),1,fp);
	fclose(fp);

}
void add()
{
	FILE *fp;
	duty x;
	fp=fopen("Checklist.dat","a+");
	printf("Enter the chore to be added:\n");
	getchar();
	scanf("%[^\n]",x.chore);
	printf("Print the status\nC for complete, I for incomplete\n");
	getchar();
	scanf("%c",&x.status);
	fwrite(&x,sizeof(x),1,fp);
	fclose(fp);
}
void status()
{
	FILE *fp;
	fpos_t pos;
	duty x;
	char search[1000],c;
	fp=fopen("Checklist.dat","r+");
	getchar();
	printf("Enter the chore to be updated:\n");
	scanf("%[^\n]",search);
	getchar();
	fread(&x,sizeof(x),1,fp);
	while(!feof(fp))
	{
		//fgetpos(fp,&pos);
		if(strcmp(search,x.chore)==0)
		{
			printf("Enter the current status:\n");
			printf("C for complete, I for incomplete\n");
	        scanf("%c",&c);
            x.status=c;
            fseek(fp,-sizeof(x),SEEK_CUR);//fsetpos(fp,&pos);
            fwrite(&x,sizeof(x),1,fp);

		}
		fread(&x,sizeof(x),1,fp);
	}
	fclose(fp);
}
void display()
{
	FILE *fp;
	duty x;
	fp=fopen("Checklist.dat","r");
	 	fread(&x,sizeof(x),1,fp);
	    while(!feof(fp))
	 	{

	 		printf("-----------------------\n");
	 		printf("Chore: %s\nStatus: %c\n",x.chore,x.status);
	 		printf("-----------------------\n");
	 		fread(&x,sizeof(x),1,fp);

	 	}
	fclose(fp);
}
/*void main()
{
	int choice=0;
	while(choice!=5)
	{
		printf("What do you want to do?\n1.Create a list\n2.Add Chore\n3.Update Chore status\n4.Check list\n5.Exit\n");
		scanf("%d",&choice);
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


	}

}*/
