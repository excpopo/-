#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
struct item{
	int code; //编码
	char object[20];//物品名称
	double price;//价格
	int num;//数量
	char name[20];//购买人
	};	//定义物品信息结构体
struct information{
	int code_;
	int day; //日期
	char object_[20];//物品名称
	int num_;//领取数量
	char name_[20];//领取人姓名
	char way_[4];//传入方法是领取为out是添加已有则为in
	};	
FILE *fp;
	void reserve();//项目保存
	void search_all();//项目浏览
	void search_item_code();//项目编码检索
	void search_item_name();//项目名称检索
	void get_item_code();//项目编码领取
	void get_item_name();//项目名称领取
	int count(int a);//辅助功能，用于计算当前库房所存项目数
	void get_chage(int a,int b, struct item c);//辅助功能，用于领取后项目修改后重输入,a项目个数，b项目位置，c变化后数字
	int get_information(char a[],char way[],char name1[],int code1);//辅助功能，用来存储领取信息
	struct item object_search(char a[]);//辅助功能，用于物品名字查询
	struct item code_search(int cod);//辅助功能，用于物品代码查询
	void item_change_code();//修改功能，用于入库物品信息修改（编码）
	void item_change_object();//修改功能，用于入库物品信息修改
	void scan_information();//用于对库房物品添加与领取记录浏览								//定义领取信息结构体
int main()
{
	int xz;//通过xz选择各种函数
	int sc;//通过sc选择检索方法
	int gi;//通过gi选择领取方法
	int ic;//通过ic选择添加方法
	printf("--------------欢迎使用物资信息管理系统----------------\n");
	printf("  Ｏ(≧▽≦)ＯＯ(≧▽≦)ＯＯ(≧▽≦)ＯＯ(≧▽≦)Ｏ\n");
	printf("||                      目录                      ||  \n");
    printf("||-------------------物品入库---------------------||（1）\n");
	printf("||-------------------库房浏览---------------------||（2）\n");
	printf("||-------------------物品检索---------------------||（3）\n");
	printf("||-------------------物品领取---------------------||（4）\n");
	printf("||-------------------物品添加---------------------||（5）\n");
	printf("||-------------------出入记录---------------------||（6）\n");
	printf("  Ｏ(≧▽≦)ＯＯ(≧▽≦)ＯＯ(≧▽≦)ＯＯ(≧▽≦)Ｏ\n");
	for(;;){
	printf("\n\n\n请输入需要执行的操作编码：");
	scanf("%d",&xz);
	switch(xz){
	case 1:reserve();break;//入库
	case 2:search_all();break;//对已存项目浏览
	case 3:printf("请选择方法进行检索（0通过编码检索/1通过物品名称检索）:");//单条搜索
		scanf("%d",&sc);
		if(sc==0)
			search_item_code();
		if(sc==1)
			search_item_name();
		if(sc!=0&&sc!=1)
			printf("\n****错误操作！****\n");
		break;
	case 4:printf("请选择方法进行领取（0通过编码领取/1通过物品名称领取）:");//单条领取
		scanf("%d",&gi);
		if(gi==0)
			get_item_code();
		if(gi==1)
			get_item_name();
		if(gi!=0&&gi!=1)
			printf("\n****错误操作！****\n");
		break;
	case 5:printf("请选择方法进行添加（0通过编码添加/1通过物品名称添加）:");//单条添加
		scanf("%d",&ic);
		if(ic==0)
			item_change_code();
		if(ic==1)
			item_change_object();	
		if(ic!=0&&ic!=1)
			printf("\n****错误操作！****\n");		
		 break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	case 6:printf("查看记录\n");
		scan_information();break;
	default:printf("\n****输入选项异常，是否重新运行?(是输入'y'否输入'n')****");
		getchar();
		if(getchar()!='n')
		continue;}//此处循环结束
	printf("\n本次操作结束，是否继续进行操作（是输入'y'否输入'n'）:");	
	getchar();
	if(getchar()!='y')
		break;}//此处外层循环结束
return 0;}
/*************************************************************************************************/
void reserve ()					//入库保存模块（1）
{	
	struct item *list,*li;
	int size=10,i,t;
		if((fp=fopen("notebook.txt","ab+"))==NULL)//为方便检索功能采用二进制的形式添加读写
		{
			printf("文件不存在");  
			exit(0);
		}	
		li=list=(struct item*)calloc(size,sizeof(struct item));//动态数组输入（注意释放空间）
		printf("本次为入库信息输入（输入完毕后，换行输入'.'，输入结束）\n");
		printf("物资编号    物资名称    物资购入价格    物资数量    采购人\n");
	for(i=0;;i++)							//无条件执行循环
		{		
			if(i==size)											//初始定义十个，后期不够再添加四个
			{
				size+=4;
				list=(struct item*)realloc(list,size*sizeof(struct item));
			}
			scanf("%d %s %lf %d %s",&list[i].code,&list[i].object,&list[i].price,
				&list[i].num,&list[i].name);			//输入条款
			if(list[i].code==0)
				break;						//输入完毕后，换行输入'.'回车结束,总录入i个
		}
		for(t=0;t<i;t++)									//循环输入文件
		{
			fwrite(&list[t],sizeof(struct item),1,fp);//写入文件
		}
		printf("入库成功！");
		fclose(fp);
		free(li);
}
/*********************************************************************************************/
void search_all()//  检索功能——对全体输出(2.1)
{
	struct item *list,*li;
	int size=10,i;
		if((fp=fopen("notebook.txt","rb"))==NULL)//打开文件，记得关闭
		{
			printf("文件不存在");  
			exit(0);
		}			
		li=list=(struct item*)calloc(size,sizeof(struct item));//动态数组输入（注意释放空间）
		printf("物资编号    物资名称        物资购入价格    物资数量   采购人\n");
		for(i=0;i<count(1);i++)
		{		
			if(i==size)											//初始定义十个，后期不够再添加四个
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
void search_item_code()///搜索功能（编码的方式）
{
	struct item n;
	int cod;
	printf("请输入需要查询的编号：");
	scanf("%d",&cod);
	n=code_search(cod);
	printf("您所查询物品信息如下\n");
	printf("物资编号    物资名称        物资购入价格    物资数量   采购人\n");
	printf("\n%03d	    %-6s	    %-5.2lf	    %-5d      %-4s\n",n.code,n.object,n.price,n.num,n.name);	
}
/****************************************************************************************************/	
struct item code_search(int cod)//辅助功能，用于物品代码查询,cod为传入编码
{
		struct item n;
		if((fp=fopen("notebook.txt","rb"))==NULL)
		{
			printf("文件不存在");  
			exit(0);
		}
		if(cod>count(1))
		{
			printf("您所输入的编码不存在!\n");
			exit(0);
		}
		cod--;
		fseek(fp,cod*sizeof(struct item),0);
		fread(&n,sizeof(struct item),1,fp);
		return n;		
		fclose(fp);
}
/*************************************************************************************************/
void search_item_name()//通过对象名称查询
{
	struct item n;
	char object_[20];	
	printf("请输入要查找的物品名称:");
	scanf("%s",object_);
    n=object_search(object_);//调用物品名称搜索，返回目标物品对象
	printf("您所查询物品信息如下：\n");
	printf("\n物资编号    物资名称        物资购入价格    物资数量   采购人\n");
	printf("%03d	    %-6s	    %-5.2lf	    %-5d      %-4s\n",n.code,n.object,n.price,n.num,n.name);
}
/*************************************************************************************************/
struct item object_search(char a[])//辅助功能，用于物品名字查询
{
	struct item *list,*li;
	int size=10,i,all;
	all=count(1);
		if((fp=fopen("notebook.txt","rb"))==NULL)//打开文件，记得关闭
		{
			printf("文件不存在");  
			exit(0);
		}	
		li=list=(struct item*)calloc(size,sizeof(struct item));//动态数组输入（注意释放空间）
		for(i=0;i<all;i++)
		{
			if(i==size)											//初始定义十个，后期不够再添加四个
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
				printf("您所输入的物品尚未入库！（或该物资已耗尽）");
				exit(0);
			}
		}
		free(li);
		fclose(fp);
}
/***************************************************************************************************/	
int count(int a)//辅助功能，用于每次入库后计算有多少项物品,a用于判断打开文件
{
	struct item *list,*li;
	int size=10,i;
	FILE *fp;
	if(a==1)
	{	if((fp=fopen("notebook.txt","rb"))==NULL)//打开文件，记得关闭
		{
			printf("文件不存在");  
			exit(0);
		}
	}
	else
	{	if((fp=fopen("record.txt","rb"))==NULL)//打开文件，记得关闭
		{
			printf("文件不存在");  
			exit(0);
		}
	}
		li=list=(struct item*)calloc(size,sizeof(struct item));//动态数组输入（注意释放空间）
		fread(&list[0],sizeof(struct item),1,fp);
		for(i=1;(!feof(fp));i++)
		{	
			if(i==size)											//初始定义十个，后期不够再添加四个
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
void get_item_code()//领取模块（通过编码）,注意设计领取记录查询模块
{
		int cod,numb,a,c;struct item n;char way[4]="out";//a 为库房所有物品数量
		a=count(1);
		if((fp=fopen("notebook.txt","rb"))==NULL)
		{
			printf("文件不存在");  
			exit(0);
		}
		printf("\n请输入需要领取物品的编号：");
		scanf("%d",&cod);
		n=code_search(cod);
		cod--;
		printf("该物品剩余量（%d）\n",n.num);
		numb=get_information(n.object,way,NULL,n.code);//调用领取信息存储功能返回领取数量			
		if(numb<=n.num)//数量足够时
		{			
			n.num-=numb;
			get_chage(a,cod,n);
			printf("领取成功！");
		}
		else
		{
			printf("****领取出错！您所领取数量大于库房数量****");
		}
		printf("是否继续领取？（是则输入1，否则输入0）：");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------分割线\n");
			get_item_code();
		}
		putchar('\n');
		printf("本次领取结束");
}
/***********************************************************************************************/
void get_chage(int a,int b,struct item c)//用于领取后项目修改后重输入(包含项目删除部分)
//a物品剩余个数，b项目位置，c变化后数字
{
	struct item	*count1,*co;int i;
		if((fp=fopen("notebook.txt","rb+"))==NULL)
		{
			printf("文件不存在");  
			exit(0);
		}
		fseek(fp,0,0);//指针调至文件头
		co=count1=(struct item*)calloc(a,sizeof(struct item));//动态数组输入（注意释放空间）)
		for(i=0;i<a;i++)
		{
			fread(&count1[i],sizeof(struct item),1,fp);//先将文件信息录取
		}
		count1[b]=c;//将有领取的物品变化后信息输入数组
		fseek(fp,0,0);//因为需要从文件头打印，则将指针再次调至头部
		if(c.num>0)//若传入数量剩余>0
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
			fwrite(&count1[i],sizeof(struct item),1,fp);//清除物品信息后文件保存
			}	
			fclose(fp);
			free(co);
		}
}
/******************************************************************************************/
void get_item_name()//通过物品名称搜索领取
{
	struct item n;
	char object_[20],way[4]="out";//way 用于信息存取判断是存储还是领取
	int numb,a,c,cod;//a 为库房所有物品数量
	if((fp=fopen("notebook.txt","rb"))==NULL)
	{
		printf("文件不存在");  
		exit(0);
	}
	printf("请输入要领取的物品名称:");
	scanf("%s",object_);
	a=count(1);
    n=object_search(object_);//调用物品名称搜索，返回目标物品对象
	cod=n.code;
	cod--;
	printf("该物品剩余量（%d）\n",n.num);
	numb=get_information(n.object,way,NULL,n.code);//调用领取信息存储功能返回领取数量			
	if(numb<=n.num)//数量足够时
	{			
		n.num-=numb;
		get_chage(a,cod,n);
		printf("领取成功！");
	}
		else
		{
			printf("***领取出错！您所领取数量大于库房剩余数量****");
		}
		printf("是否继续领取？（是则输入1，否则输入0）：");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------分割线\n");
			get_item_name();
		}
		putchar('\n');
		printf("本次领取结束");
}
/*************************************************************************************************/
void item_change_code()//添加功能（通过编码查找--添加）
{
	struct item n;int cod,a,c;char way[4]="in";
	char name1[20];
	printf("请输入需要添加的物品的编码:");
	scanf("%d",&cod);
	n=code_search(cod);
	a=count(1);
	printf("请输入姓名：");
	scanf("%s",name1);
	n.num+=get_information(n.object,way,name1,n.code);
	cod--;
	strcpy(n.name,name1);
	get_chage(a,cod,n);
	printf("物品添加成功\n");
	printf("是否继续添加？（是则输入1，否则输入0）：");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------分割线\n");
			item_change_code();
		}
		putchar('\n');
		printf("本次添加结束");

}
/*************************************************************************************************/
void item_change_object()//添加功能（通过物品名称查找--添加）
{
	struct item n;int a,c;char way[4]="in",object1[20];//a 为总数，c 用于判断
	char name1[20];
	printf("请输入需要添加的物品的名称：");
	scanf("%s",&object1);
	n=object_search(object1);
	a=count(1);
	printf("请输入姓名：");
	scanf("%s",name1);
	n.num+=get_information(n.object,way,name1,n.code);
	n.code--;
	strcpy(n.name,name1);
	get_chage(a,n.code,n);
	printf("物品添加成功\n");
	printf("是否继续添加？（是则输入1，否则输入0）：");
		scanf("%d",&c);
		if(c!=0)
		{
			printf("-----------------------------------------------分割线\n");
			item_change_object();
		}
		putchar('\n');
		printf("本次添加结束");
}
/*************************************************************************************************/
int get_information(char a[],char way[],char name1[],int code1)//a 为物品名称,name1为操作人姓名
{
	struct information b;char way1[]="out";
	FILE *re;
	if((re=fopen("record.txt","ab+"))==NULL)
	{
		printf("文件不存在");  
		exit(0);
	}
	printf("请输入所需领取(或添加)物品的数量：");
	scanf("%d",&b.num_);
	if(strcmp(way,way1)==0)
	{printf("请输入姓名：");
	scanf("%s",&b.name_);}
	else
	{strcpy(b.name_,name1);}
	b.code_=code1;//编码输入
	printf("请输入领取（或添加）时间如（20180101）：");//录入时间
	scanf("%d",&b.day);
	strcpy(b.way_,way);
	strcpy(b.object_,a);//将物品名称代入领取information
	fwrite(&b,sizeof(struct item),1,re);
	fclose(re);
	return (b.num_);
}
/*************************************************************************************************/
void scan_information()//浏览库房添加领取记录
{
	struct information *list,*li;
	int size=10,i; 
		if((fp=fopen("record.txt","rb"))==NULL)//打开文件，记得关闭
		{
			printf("文件不存在");  
			exit(0);
		}			
		li=list=(struct information*)calloc(size,sizeof(struct information));//动态数组输入（注意释放空间）
		printf("物资编号  物资名称  物资数量  采购人  日期  方法\n");
		for(i=0;i<count(2);i++)
		{
			if(i==size)											//初始定义十个，后期不够再添加四个
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
/*void arrangement()//气泡排序 功能不起作用不知道中文如何排序
{    int count(int a);
		struct item	*count1,*co;int i,j,a;char t[20];
	FILE *fp; 
		if((fp=fopen("notebook.txt","rb"))==NULL)
		{
			printf("文件不存在");  
			exit(0);
		}a=count(1);
		co=count1=(struct item*)calloc(a,sizeof(struct item));//动态数组输入（注意释放空间）)
		for(i=0;i<a;i++)
		{
			fread(&count1[i],sizeof(struct item),1,fp);//先将文件信息录取
		}
		
		a--;
		for(i=0;i<a;i++){
			for(j=0;i<a-i;j++){
				if(strcmp(count1[i].object,count1[i+1].object)>0)//若比后一项的阿斯克码值大，“下沉
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