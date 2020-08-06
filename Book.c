#include<stdio.h>
#include<string.h>
typedef struct
{
	char name[100];
	char author[100];
	int copies;
	int edition;
	int bookID;
	int price;
	double rating;
	int borrowed;
}Book;

void TestBook(Book *b){
    (*b).name[0]='\0';
    (*b).author[0]='\0';
    (*b).copies=(*b).edition=(*b).bookID=0;
    (*b).price=0;(*b).rating=0;
    (*b).borrowed=0;
}

void ReadBook(Book *x){
	printf("Enter the name of the book:\n");
	getchar();
	scanf("%[^\n]",&(x->name));
	getchar();
	printf("Enter the name of the author:\n");
	scanf("%[^\n]",&(x->author));
	printf("Enter the number of copies:\n");
	scanf("%d",&(x->copies));
	printf("Enter the price:\n");
	scanf("%d",&(x->price));
	printf("Enter the book ID:\n");
	scanf("%d",&(x->bookID));
	printf("Enter the edition:\n");
	scanf("%d",&(x->edition));
	(*x).rating=0;
	(*x).borrowed=0;
}
void create()
{
	FILE *fp;
	Book x;
	fp=fopen("Books.dat","a");
	ReadBook(&x);
	if(!fp)
        printf("No Access to file\n");
	else
        fwrite(&x,sizeof(x),1,fp);
	fclose(fp);

}
/*
void search()
{
	int flag=0;
	book x,x1;
	FILE *fp;
	char search[1000];
    fp=fopen("Books.dat","r");
 	printf("Enter the name of the book to be searched for:\n");
 	getchar();
 	scanf("%[^\n]",search);
 	while(!feof(fp))
 	{
 		fread(&x,sizeof(x),1,fp);
 		if(strcmp(search,x.name)==0)
 		{
 			x1=x;
 			flag+=1;
 			break;
 		}
 	}
 	if(flag==1)
  	{
    	printf("-----------------------\n");
 		printf("Title: %s\nAuthor: %s\nNumber of copies: %d\nPrice: %d\nBook ID: %d\nEdition: %d\n",x1.name,x1.author,x1.copies,x1.price,x1.bookID,x1.edition);
 		printf("-----------------------\n");
 	}
	else
 	{
		printf("THIS BOOK IS NOT IN THE DATABASE\n");
 	}
 	fclose(fp);
}*/

void update()
{
	Book x;
	FILE *fp;
	fp=fopen("Books.dat","a+");
	ReadBook(&x);
	fwrite(&x,sizeof(x),1,fp);
	fclose(fp);

}

void DisplayBook(Book x){
	printf("-----------------------\n");
	printf("Title: %s\nAuthor: %s\nNumber of copies: %d\nPrice: %d\nBook ID: %d\nEdition: %d\nRating: %d\n",x.name,x.author,x.copies,x.price,x.bookID,x.edition,x.rating);
	printf("-----------------------\n");
}

void DisplayAll()
{
	FILE *fp;
	Book x;
	fp=fopen("Books.dat","r");
    fread(&x,sizeof(x),1,fp);
    if(!fp)
        printf("Unable to access file");
	while(!feof(fp))
    {

        printf("-----------------------\n");
        printf("Title: %s\nAuthor: %s\nNumber of copies: %d\nPrice: %d\nBook ID: %d\nEdition: %d\nRating: %d\n",x.name,x.author,x.copies,x.price,x.bookID,x.edition,x.rating);
        printf("-----------------------\n");
        fread(&x,sizeof(x),1,fp);
    }
	fclose(fp);
}
/*void addrate()
{
    book x;
    fpos_t pos;
	FILE *fp;
	char search[1000];
    fp=fopen("Books.dat","r");
 	printf("Enter the name of the book to be searched for:\n");
 	getchar();
 	scanf("%[^\n]",search);
 	while(!feof(fp))
 	{
 		fgetpos(fp,&pos);
 		fread(&x,sizeof(x),1,fp);
 		if(strcmp(search,x.name)==0)
 		{
 			printf("Enter the rating out of 10:\n");

 			scanf("%d",&x.rating);
 			break;
 		}
 	}
 	fsetpos(fp,&pos);
 	fwrite(&x,sizeof(x),1,fp);
 	fclose(fp);

}*/
void sortByRating()
{
	Book x,x1[100],temp;
	FILE *fp;
	int i=0,n,j;
	fp=fopen("Books.dat","r+");
	fread(&x,sizeof(x),1,fp);
	while(!feof(fp))
	{
		fread(&x,sizeof(x),1,fp);
		x1[i++]=x;
	}
	n=i;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(x1[j].rating<x1[j+1].rating)
			{
				temp=x1[j];
				x1[j]=x1[j+1];
				x1[j+1]=temp;
			}
		}
	}
	rewind(fp);
	for(i=0;i<n;i++)
	{
		temp=x1[i];
		fwrite(&temp,sizeof(temp),1,fp);
	}
	fclose(fp);




}
void DeleteEdition(Book x)//change name in driver
{
	Book x1[100],c;
	fpos_t pos;
	FILE *fp;
	int flag=0,i=0;
	fp=fopen("Books.dat","w+");
	fread(&c,sizeof(c),1,fp);
	while(!feof(fp))
	{
		fgetpos(fp,&pos);
		fread(&c,sizeof(c),1,fp);
		if(strcmp(c.name,x.name)==0&&c.edition==x.edition)
		{
			break;
		}
	}
	fread(&c,sizeof(c),1,fp);
	while(!feof(fp))
	{
		fread(&c,sizeof(c),1,fp);
		x1[i++]=c;

	}
	fsetpos(fp,&pos);
	i=0;
	while(!feof(fp))
	{
		c=x1[i++];
		fwrite(&c,sizeof(c),1,fp);

	}
	fclose(fp);
}

