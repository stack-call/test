#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define STR_MAX 101
#define MAXSIZE 10000

typedef struct
{
	char no[20];
	char name[50];
	float price;
}Book;

typedef struct
{
	Book *elem;
	int length;
}SqList;

SqList L;

void print_window();
int read_file();
void print_books();
void print_num();
void insert_book();
void delete_book();
void find_book();
void update_price();
void sort_price();
void reverse_book();
 
int main()
{
	L.elem = (Book*)malloc(sizeof(Book) * MAXSIZE);
	L.length = 0;
	int status;
	if((status = read_file())!= 1)
	{
		printf("error");
		return -1;
	}
	while(1)
	{
		int cmd;
		print_window();
		printf("���������:");
		scanf("%d", &cmd);
		switch(cmd)
		{
			case(1):
			{
				print_books();
				break; 
			}
			case(2):
			{
				print_num();
				break; 
			}
			case(3):
			{
				insert_book();
				break; 
			}
			case(4):
			{
				delete_book();
				break;
			}
			case(5):
			{
				find_book();
				break;
			}
			case(6):
			{
				update_price(); 
				break;
			}
			case(7):
			{
				sort_price();
				break;
			}
			case(8):
			{
				reverse_book();
				break;
			}
			case(0):
				exit(0);
			default:
				printf("error1"); 
				exit(0);
		}
	}
	
	return 0;
}

static void write_to_file(char* filename)
{
	FILE *fp;
	if((fp=fopen(filename,"w+")) == NULL ){
	    printf("Fail to open file!\n");
	    exit(0);
	}
	
	int i;
	fputs("������ҵ��ѧͼ��ݼ������ͼ��ɹ��б�\n",fp);
	fputs("ISBN  ����  ����\n",fp);
	for(i = 0; i < L.length-1; i++)
	{
		fprintf(fp, "%s %s %g\n", L.elem[i].no, L.elem[i].name, L.elem[i].price);
	}
	fprintf(fp, "%s %s %g", L.elem[L.length-1].no, L.elem[L.length-1].name, L.elem[L.length-1].price);
}
int read_file()
{
	FILE *fp;
	if((fp=fopen("book.txt","r")) == NULL ){
	    printf("Fail to open file!\n");
	    exit(0);
	}
	char str[STR_MAX];
	fgets(str, STR_MAX, fp);
	printf(str);
	fgets(str, STR_MAX, fp);
	printf(str);//lseek

	Book* temp = (Book*)malloc(sizeof(Book));//Book temp; 

	while(!feof(fp)){ 
	    fscanf(fp, "%s %s %f", temp->no, temp->name, &temp->price);
	    L.elem[L.length] = *temp;
	    L.length++;
	}
	free(temp);
}

void print_books()
{
	int i;
	for(i = 0; i < L.length; i++)
	{
		printf("%s %s %g\n", L.elem[i].no, L.elem[i].name, L.elem[i].price);
	}
}
void print_num()
{
	printf("%d\n", L.length);
}
void insert_book()
{
	Book booktemp;
	float tempf;
	char temp[STR_MAX];
	printf("�������鼮��Ϣ:\n");
	printf("ISBN:");
	scanf("%s", temp);
	strcpy(booktemp.no, temp); 
	printf("����:");
	scanf("%s", temp); 
	strcpy(booktemp.name, temp); 
	printf("�۸�:");
	scanf("%f", &tempf);
	booktemp.price = tempf;
	int i;
	printf("���������λ��:");
	scanf("%d",&i);
	i--;
	if(i>L.length || i<=0)
	{
		printf("error");
		return;
	}
	int j;
	for(j = L.length-1; j >=i; j--)
	{
		L.elem[j+1]=L.elem[j];
	}
	L.length++;
	L.elem[i] = booktemp;
	write_to_file("book.txt");
}

void print_window()
{
	printf("----------------\n"
			"1:ͼ�����\n"
			"2:ͼ��ͳ��\n"
			"3:ͼ�����\n"
			"4:ͼ��ɾ��\n"
			"5:ͼ�����\n"
			"6:�۸����\n"
			"7:�۸�����\n"
			"8:���򴢴�\n"
			"0:�˳�\n");
}

void delete_book()
{
	int i;
	printf("������ɾ�����:");
	scanf("%d", &i);
	int j;
	for(j = i-1; j < L.length; j++)
	{
		L.elem[j] = L.elem[j+1];
	}
	L.length--;
	write_to_file("book.txt");
}

void find_book()
{
	printf("0:��λ�ò��� 1:����������:");
	int i;
	scanf("%d", &i);
	if(i == 0)
	{
		printf("������λ��:");
		int j;
		scanf("%d", &j);
		--j;
		printf("%s %s %.2f\n", L.elem[j].no, L.elem[j].name, L.elem[j].price); 
	}
	else if(i==1)
	{
		printf("����������:");
		char target[STR_MAX];
		scanf("%s", target);
		int j;
		for(j = 0; j < L.length; j++)
		{
			if(!strcmp(target, L.elem[j].name))
			{
				printf("%s %s %.2f\n", L.elem[j].no, L.elem[j].name, L.elem[j].price); 
			}
		}
	}
}

void update_price()
{
	int i;
	for(i = 0; i < L.length; i++)
	{
		if(L.elem[i].price<45.0)
		{
			L.elem[i].price *= 1.2;
		}
		else if(L.elem[i].price >= 45.0)
		{
			L.elem[i].price *= 1.1;
		}
	}
	write_to_file("book-newprice.txt");
}

void sort_price()
{
	int i, j;
	for (i = 0; i < L.length-1; i++)
	{
		for (j = 0; j < L.length-1 - i; j++)
		{
			if (L.elem[j].price > L.elem[j+1].price)
			{
				Book temp = L.elem[j];
				L.elem[j] = L.elem[j+1];
				L.elem[j+1] = temp;
			}
		}
	}
	write_to_file("book-newsort.txt");
}


void reverse_book()
{
	int i;
	for(i = 0; i < L.length/2; i++)
	{
		Book temp;
		temp = L.elem[i];
		L.elem[i] = L.elem[L.length-1-i];
		L.elem[L.length-1-i] = temp;
	}
	write_to_file("book-newinverse.txt");
}
