#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
struct item{
	int code; //����
	char object[20];//��Ʒ����
	double price;//�۸�
	int num;//����
	char name[20];//������
	};	//������Ʒ��Ϣ�ṹ��
struct information{
	int code_;
	int day; //����
	char object_[20];//��Ʒ����
	int num_;//��ȡ����
	char name_[20];//��ȡ������
	char way_[4];//���뷽������ȡΪout�����������Ϊin
	};	
FILE *fp;
	void reserve();//��Ŀ����
	void search_all();//��Ŀ���
	void search_item_code();//��Ŀ�������
	void search_item_name();//��Ŀ���Ƽ���
	void get_item_code();//��Ŀ������ȡ
	void get_item_name();//��Ŀ������ȡ
	int count(int a);//�������ܣ����ڼ��㵱ǰ�ⷿ������Ŀ��
	void get_chage(int a,int b, struct item c);//�������ܣ�������ȡ����Ŀ�޸ĺ�������,a��Ŀ������b��Ŀλ�ã�c�仯������
	int get_information(char a[],char way[],char name1[],int code1);//�������ܣ������洢��ȡ��Ϣ
	struct item object_search(char a[]);//�������ܣ�������Ʒ���ֲ�ѯ
	struct item code_search(int cod);//�������ܣ�������Ʒ�����ѯ
	void item_change_code();//�޸Ĺ��ܣ����������Ʒ��Ϣ�޸ģ����룩
	void item_change_object();//�޸Ĺ��ܣ����������Ʒ��Ϣ�޸�
	void scan_information();//���ڶԿⷿ��Ʒ�������ȡ��¼���								//������ȡ��Ϣ�ṹ��
int main()
{
	int xz;//ͨ��xzѡ����ֺ���
	int sc;//ͨ��scѡ���������
	int gi;//ͨ��giѡ����ȡ����
	int ic;//ͨ��icѡ����ӷ���
	printf("--------------��ӭʹ��������Ϣ����ϵͳ----------------\n");
	printf("  ��(�R���Q)�ϣ�(�R���Q)�ϣ�(�R���Q)�ϣ�(�R���Q)��\n");
	printf("||                      Ŀ¼                      ||  \n");
    printf("||-------------------��Ʒ���---------------------||��1��\n");
	printf("||-------------------�ⷿ���---------------------||��2��\n");
	printf("||-------------------��Ʒ����---------------------||��3��\n");
	printf("||-------------------��Ʒ��ȡ---------------------||��4��\n");
	printf("||-------------------��Ʒ���---------------------||��5��\n");
	printf("||-------------------�����¼---------------------||��6��\n");
	printf("  ��(�R���Q)�ϣ�(�R���Q)�ϣ�(�R���Q)�ϣ�(�R���Q)��\n");
	for(;;){
	printf("\n\n\n��������Ҫִ�еĲ������룺");
	scanf("%d",&xz);
	switch(xz){
	case 1:reserve();break;//���
	case 2:search_all();break;//���Ѵ���Ŀ���
	case 3:printf("��ѡ�񷽷����м�����0ͨ���������/1ͨ����Ʒ���Ƽ�����:");//��������
		scanf("%d",&sc);
		if(sc==0)
			search_item_code();
		if(sc==1)
			search_item_name();
		if(sc!=0&&sc!=1)
			printf("\n****���������****\n");
		break;
	case 4:printf("��ѡ�񷽷�������ȡ��0ͨ��������ȡ/1ͨ����Ʒ������ȡ��:");//������ȡ
		scanf("%d",&gi);
		if(gi==0)
			get_item_code();
		if(gi==1)
			get_item_name();
		if(gi!=0&&gi!=1)
			printf("\n****���������****\n");
		break;
	case 5:printf("��ѡ�񷽷�������ӣ�0ͨ���������/1ͨ����Ʒ������ӣ�:");//�������
		scanf("%d",&ic);
		if(ic==0)
			item_change_code();
		if(ic==1)
			item_change_object();	
		if(ic!=0&&ic!=1)
			printf("\n****���������****\n");		
		 break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	case 6:printf("�鿴��¼\n");
		scan_information();break;
	default:printf("\n****����ѡ���쳣���Ƿ���������?(������'y'������'n')****");
		getchar();
		if(getchar()!='n')
		continue;}//�˴�ѭ������
	printf("\n���β����������Ƿ�������в�����������'y'������'n'��:");	
	getchar();
	if(getchar()!='y')
		break;}//�˴����ѭ������
return 0;}
/*************************************************************************************************/
void reserve ()					//��Ᵽ��ģ�飨1��
{	
	struct item *list,*li;
	int size=10,i,t;
		if((fp=fopen("notebook.txt","ab+"))==NULL)//Ϊ����������ܲ��ö����Ƶ���ʽ��Ӷ�д
		{
			printf("�ļ�������");  
			exit(0);
		}	
		li=list=(struct item*)calloc(size,sizeof(struct item));//��̬�������루ע���ͷſռ䣩
		printf("����Ϊ�����Ϣ���루������Ϻ󣬻�������'.'�����������\n");
		printf("���ʱ��    ��������    ���ʹ���۸�    ��������    �ɹ���\n");
	for(i=0;;i++)							//������ִ��ѭ��
		{		
			if(i==size)											//��ʼ����ʮ�������ڲ���������ĸ�
			{
				size+=4;
				list=(struct item*)realloc(list,size*sizeof(struct item));
			}
			scanf("%d %s %lf %d %s",&list[i].code,&list[i].object,&list[i].price,
				&list[i].num,&list[i].name);			//��������
			if(list[i].code==0)
				break;						//������Ϻ󣬻�������'.'�س�����,��¼��i��
		}
		for(t=0;t<i;t++)									//ѭ�������ļ�
		{
			fwrite(&list[t],sizeof(struct item),1,fp);//д���ļ�
		}
		printf("���ɹ���");
		fclose(fp);
		free(li);
}
/*********************************************************************************************/
void search_all()//  �������ܡ�����ȫ�����(2.1)
{
	struct item *list,*li;
	int size=10,i;
		if((fp=fopen("notebook.txt","rb"))==NULL)//���ļ����ǵùر�
		{
			printf("�ļ�������");  
			exit(0);
		}			
		li=list=(struct item*)calloc(size,sizeof(struct item));//��̬�������루ע���ͷſռ䣩
		printf("���ʱ��    ��������        ���ʹ���۸�    ��������   �ɹ���\n");
		for(i=0;i<count(1);i++)
		{		
			if(i==size)											//��ʼ����ʮ�������ڲ���������ĸ�
			{
				size+=4;
				list=(struct item*)realloc(list,size*sizeof(struct item));
			}
			fread(&list[i],sizeof(struct item),1,fp);
			printf("%03d	    %-6s	    %-5.2lf	    %-5d      %-4s\n",list[i].code,list[i].object,list[i].price,list[i].num,list[i].name);
		}
		fclose(fp);
		free(li);
}
/****************************************************************************************************/
void search_item_code()///�������ܣ�����ķ�ʽ��
{
	struct item n;
	int cod;
	printf("��������Ҫ��ѯ�ı�ţ�");
	scanf("%d",&cod);
	n=code_search(cod);
	printf("������ѯ��Ʒ��Ϣ����\n");
	printf("���ʱ��    ��������        ���ʹ���۸�    ��������   �ɹ���\n");
	printf("\n%03d	    %-6s	    %-5.2lf	    %-5d      %-4s\n",n.code,n.object,n.price,n.num,n.name);	
}
/****************************************************************************************************/	
struct item code_search(int cod)//�������ܣ�������Ʒ�����ѯ,codΪ�������
{
		struct item n;
		if((fp=fopen("notebook.txt","rb"))==NULL)
		{
			printf("�ļ�������");  
			exit(0);
		}
		if(cod>count(1))
		{
			printf("��������ı��벻����!\n");
			exit(0);
		}
		cod--;
		fseek(fp,cod*sizeof(struct item),0);
		fread(&n,sizeof(struct item),1,fp);
		return n;		
		fclose(fp);
}
/*************************************************************************************************/
void search_item_name()//ͨ���������Ʋ�ѯ
{
	struct item n;
	char object_[20];	
	printf("������Ҫ���ҵ���Ʒ����:");
	scanf("%s",object_);
    n=object_search(object_);//������Ʒ��������������Ŀ����Ʒ����
	printf("������ѯ��Ʒ��Ϣ���£�\n");
	printf("\n���ʱ��    ��������        ���ʹ���۸�    ��������   �ɹ���\n");
	printf("%03d	    %-6s	    %-5.2lf	    %-5d      %-4s\n",n.code,n.object,n.price,n.num,n.name);
}
/*************************************************************************************************/
struct item object_search(char a[])//�������ܣ�������Ʒ���ֲ�ѯ
{
	struct item *list,*li;
	int size=10,i,all;
	all=count(1);
		if((fp=fopen("notebook.txt","rb"))==NULL)//���ļ����ǵùر�
		{
			printf("�ļ�������");  
			exit(0);
		}	
		li=list=(struct item*)calloc(size,sizeof(struct item));//��̬�������루ע���ͷſռ䣩
		for(i=0;i<all;i++)
		{
			if(i==size)											//��ʼ����ʮ�������ڲ���������ĸ�
			{
				size+=4;
				list=(struct item*)realloc(list,size*sizeof(struct item));
			}
			fread(&list[i],sizeof(struct item),1,fp);
			if(strcmp(a,list[i].object)==0)
			{
				return list[i];
			}				
		}
		for(i=0;i<all;i++)
		{
			if(strcmp(a,list[i].object)!=0)
			{	
				printf("�����������Ʒ��δ��⣡����������Ѻľ���");
				exit(0);
			}
		}
		free(li);
		fclose(fp);
}
/***************************************************************************************************/	
int count(int a)//�������ܣ�����ÿ����������ж�������Ʒ,a�����жϴ��ļ�
{
	struct item *list,*li;
	int size=10,i;
	FILE *fp;
	if(a==1)
	{	if((fp=fopen("notebook.txt","rb"))==NULL)//���ļ����ǵùر�
		{
			printf("�ļ�������");  
			exit(0);
		}
	}
	else
	{	if((fp=fopen("record.txt","rb"))==NULL)//���ļ����ǵùر�
		{
			printf("�ļ�������");  
			exit(0);
		}
	}
		li=list=(struct item*)calloc(size,sizeof(struct item));//��̬�������루ע���ͷſռ䣩
		fread(&list[0],sizeof(struct item),1,fp);
		for(i=1;(!feof(fp));i++)
		{	
			if(i==size)											//��ʼ����ʮ�������ڲ���������ĸ�
			{
				size+=4;
				list=(struct item*)realloc(list,size*sizeof(struct item));
			}
			fread(&list[i],sizeof(struct item),1,fp);		
		}i--;
		return(i);
		fclose(fp);
		free(li);
}
/***************************************************************************************************/
void get_item_code()//��ȡģ�飨ͨ�����룩,ע�������ȡ��¼��ѯģ��
{
		int cod,numb,a,c;struct item n;char way[4]="out";//a Ϊ�ⷿ������Ʒ����
		a=count(1);
		if((fp=fopen("notebook.txt","rb"))==NULL)
		{
			printf("�ļ�������");  
			exit(0);
		}
		printf("\n��������Ҫ��ȡ��Ʒ�ı�ţ�");
		scanf("%d",&cod);
		n=code_search(cod);
		cod--;
		printf("����Ʒʣ������%d��\n",n.num);
		numb=get_information(n.object,way,NULL,n.code);//������ȡ��Ϣ�洢���ܷ�����ȡ����			
		if(numb<=n.num)//�����㹻ʱ
		{			
			n.num-=numb;
			get_chage(a,cod,n);
			printf("��ȡ�ɹ���");
		}
		else
		{
			printf("****��ȡ����������ȡ�������ڿⷿ����****");
		}
		printf("�Ƿ������ȡ������������1����������0����");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------�ָ���\n");
			get_item_code();
		}
		putchar('\n');
		printf("������ȡ����");
}
/***********************************************************************************************/
void get_chage(int a,int b,struct item c)//������ȡ����Ŀ�޸ĺ�������(������Ŀɾ������)
//a��Ʒʣ�������b��Ŀλ�ã�c�仯������
{
	struct item	*count1,*co;int i;
		if((fp=fopen("notebook.txt","rb+"))==NULL)
		{
			printf("�ļ�������");  
			exit(0);
		}
		fseek(fp,0,0);//ָ������ļ�ͷ
		co=count1=(struct item*)calloc(a,sizeof(struct item));//��̬�������루ע���ͷſռ䣩)
		for(i=0;i<a;i++)
		{
			fread(&count1[i],sizeof(struct item),1,fp);//�Ƚ��ļ���Ϣ¼ȡ
		}
		count1[b]=c;//������ȡ����Ʒ�仯����Ϣ��������
		fseek(fp,0,0);//��Ϊ��Ҫ���ļ�ͷ��ӡ����ָ���ٴε���ͷ��
		if(c.num>0)//����������ʣ��>0
		{	
			for(i=0;i<a;i++)
			{
			fwrite(&count1[i],sizeof(struct item),1,fp);
			}
			fclose(fp);
			free(co);	
		}
		if(c.num==0)
		{
			memset(&count1[b],NULL,sizeof(struct item));
			for(i=0;i<a;i++)
			{
			fwrite(&count1[i],sizeof(struct item),1,fp);//�����Ʒ��Ϣ���ļ�����
			}	
			fclose(fp);
			free(co);
		}
}
/******************************************************************************************/
void get_item_name()//ͨ����Ʒ����������ȡ
{
	struct item n;
	char object_[20],way[4]="out";//way ������Ϣ��ȡ�ж��Ǵ洢������ȡ
	int numb,a,c,cod;//a Ϊ�ⷿ������Ʒ����
	if((fp=fopen("notebook.txt","rb"))==NULL)
	{
		printf("�ļ�������");  
		exit(0);
	}
	printf("������Ҫ��ȡ����Ʒ����:");
	scanf("%s",object_);
	a=count(1);
    n=object_search(object_);//������Ʒ��������������Ŀ����Ʒ����
	cod=n.code;
	cod--;
	printf("����Ʒʣ������%d��\n",n.num);
	numb=get_information(n.object,way,NULL,n.code);//������ȡ��Ϣ�洢���ܷ�����ȡ����			
	if(numb<=n.num)//�����㹻ʱ
	{			
		n.num-=numb;
		get_chage(a,cod,n);
		printf("��ȡ�ɹ���");
	}
		else
		{
			printf("***��ȡ����������ȡ�������ڿⷿʣ������****");
		}
		printf("�Ƿ������ȡ������������1����������0����");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------�ָ���\n");
			get_item_name();
		}
		putchar('\n');
		printf("������ȡ����");
}
/*************************************************************************************************/
void item_change_code()//��ӹ��ܣ�ͨ���������--��ӣ�
{
	struct item n;int cod,a,c;char way[4]="in";
	char name1[20];
	printf("��������Ҫ��ӵ���Ʒ�ı���:");
	scanf("%d",&cod);
	n=code_search(cod);
	a=count(1);
	printf("������������");
	scanf("%s",name1);
	n.num+=get_information(n.object,way,name1,n.code);
	cod--;
	strcpy(n.name,name1);
	get_chage(a,cod,n);
	printf("��Ʒ��ӳɹ�\n");
	printf("�Ƿ������ӣ�����������1����������0����");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------�ָ���\n");
			item_change_code();
		}
		putchar('\n');
		printf("������ӽ���");

}
/*************************************************************************************************/
void item_change_object()//��ӹ��ܣ�ͨ����Ʒ���Ʋ���--��ӣ�
{
	struct item n;int a,c;char way[4]="in",object1[20];//a Ϊ������c �����ж�
	char name1[20];
	printf("��������Ҫ��ӵ���Ʒ�����ƣ�");
	scanf("%s",&object1);
	n=object_search(object1);
	a=count(1);
	printf("������������");
	scanf("%s",name1);
	n.num+=get_information(n.object,way,name1,n.code);
	n.code--;
	strcpy(n.name,name1);
	get_chage(a,n.code,n);
	printf("��Ʒ��ӳɹ�\n");
	printf("�Ƿ������ӣ�����������1����������0����");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------�ָ���\n");
			item_change_object();
		}
		putchar('\n');
		printf("������ӽ���");
}
/*************************************************************************************************/
int get_information(char a[],char way[],char name1[],int code1)//a Ϊ��Ʒ����,name1Ϊ����������
{
	struct information b;char way1[]="out";
	FILE *re;
	if((re=fopen("record.txt","ab+"))==NULL)
	{
		printf("�ļ�������");  
		exit(0);
	}
	printf("������������ȡ(�����)��Ʒ��������");
	scanf("%d",&b.num_);
	if(strcmp(way,way1)==0)
	{printf("������������");
	scanf("%s",&b.name_);}
	else
	{strcpy(b.name_,name1);}
	b.code_=code1;//��������
	printf("��������ȡ������ӣ�ʱ���磨20180101����");//¼��ʱ��
	scanf("%d",&b.day);
	strcpy(b.way_,way);
	strcpy(b.object_,a);//����Ʒ���ƴ�����ȡinformation
	fwrite(&b,sizeof(struct item),1,re);
	fclose(re);
	return (b.num_);
}
/*************************************************************************************************/
void scan_information()//����ⷿ�����ȡ��¼
{
	struct information *list,*li;
	int size=10,i; 
		if((fp=fopen("record.txt","rb"))==NULL)//���ļ����ǵùر�
		{
			printf("�ļ�������");  
			exit(0);
		}			
		li=list=(struct information*)calloc(size,sizeof(struct information));//��̬�������루ע���ͷſռ䣩
		printf("���ʱ��  ��������  ��������  �ɹ���  ����  ����\n");
		for(i=0;i<count(2);i++)
		{
			if(i==size)											//��ʼ����ʮ�������ڲ���������ĸ�
			{
				size+=4;
				list=(struct information*)calloc(size,sizeof(struct information));
			}
			fread(&list[i],sizeof(struct information),1,fp);
			printf("%03d	  %s	    %d	  %s	    %d  (%s)\n",list[i].code_ ,list[i].object_,list[i].num_,list[i].name_,list[i].day,list[i].way_);
		}
		fclose(fp);
		free(li);
}
/*************************************************************************************************/
/*void arrangement()//�������� ���ܲ������ò�֪�������������
{    int count(int a);
		struct item	*count1,*co;int i,j,a;char t[20];
	FILE *fp; 
		if((fp=fopen("notebook.txt","rb"))==NULL)
		{
			printf("�ļ�������");  
			exit(0);
		}a=count(1);
		co=count1=(struct item*)calloc(a,sizeof(struct item));//��̬�������루ע���ͷſռ䣩)
		for(i=0;i<a;i++)
		{
			fread(&count1[i],sizeof(struct item),1,fp);//�Ƚ��ļ���Ϣ¼ȡ
		}
		
		a--;
		for(i=0;i<a;i++){
			for(j=0;i<a-i;j++){
				if(strcmp(count1[i].object,count1[i+1].object)>0)//���Ⱥ�һ��İ�˹����ֵ�󣬡��³�
				{
					strcpy(t,count1[i].object);
					strcpy(count1[i].object,count1[i+1].object);
					strcpy(count1[i+1].object,t);
		}}}
		for(i=0;i<a;i++){
		printf("%03d	  %s	    %.2lf	  %d	    %s\n",count1[i].code,count1[i].object,count1[i].price,count1[i].num,count1[i].name);
		}
		fclose(fp);
		free(co);
}*/