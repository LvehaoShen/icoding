#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX 100
#define GOODS_FILE_NAME "goodsinfo.txt"
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_PRICE_LEN 30
#define MAX_DISCOUNT_LEN 30

//--------------------------------------------------------------------
//商品信息结构的定义
//--------------------------------------------------------------------
typedef struct {
	char    goods_id[MAX_ID_LEN+1];
	char    goods_name[MAX_NAME_LEN+1];
	int     goods_price;
	char    goods_discount[MAX_DISCOUNT_LEN+1];
	int     goods_amount;
	int     goods_remain;
} GoodsInfo;
//--------------------------------------------------------------------
//定义商品链表的结点
//--------------------------------------------------------------------
typedef struct node
{
	GoodsInfo data;
	struct node *next;
} GoodsList;

//全局变量，存储当前商品的数量
int CurrentCnt;

//--------------------------------------------------------------------
//参考函数：本函数用于提供文件操作的参照
//--------------------------------------------------------------------
void fileIOreferrence(void)
{
    char tempstring[30];

    //定义文件操作的指针
    FILE *fp;
    //fopen用于打开文件，接收两个参数，一个是文件的路径，一个是文件打开的方式
    //例如xxxxxx.txt和该项目的可执行文件在同一目录下，则此处只需要所读取内容文件名
    //例如r代表以只读方式打开文件
    fp = fopen("xxxxxxx.txt", "r"); 
    //如果w代表打开只写文件，若文件存在则长度清为0，即该文件内容消失，若不存在则创建该文件
    //其余打开方式请自行查阅文档
    fp = fopen("xxxxxxx.txt", "w");

    //fscanf用于从txt文件中读取内容，下例以字符串形式读入一段字符并存放在tempstring中
    fscanf(fp, "%s", tempstring);
    //或者以格式化的方式读入字符串
    fscanf(fp, "\t%s\n", tempstring);

    //fprintf以格式化的方式向txt文件中写入内容
    fprintf(fp, "%s\t", tempstring);

    //检查文件内容是否已经读到文件结束符了
    fgetc(fp);
    while ( !feof(fp))
    {
        rewind(fp);	 
		//…………
    }
       
    //文件操作完成后需要使用fclose关闭文件指针
    fclose(fp);
    
    //删除文件
	remove("xxxxxxx.txt"); 
}

//--------------------------------------------------------------------
//如果商品文件goodsinfo.txt不存在，则创建该文件； 
//如果存在，则将商品文件goodsinfo.txt已记录的商品数据读出，并建立商品链表
//这个商品链表跟inventory有差异，第一个商品结点不是由list指针指向，而是由一个结构*L指向，这个结构没有data
//p = (*L)->next; p才是第一个商品结点
//--------------------------------------------------------------------
void init_list(GoodsList **L) {
	FILE *fp;
	GoodsInfo goodsInfo;
	GoodsList *p, *r;
    /*
     * 1.判断goodsinfo.txt是否存在，不存在则新建一个goodsinfo.txt
     * 2.如果存在，在未达到文件尾的情况下（利用feof函数），从该文件中读取商品信息（调用fscanf函数） ，建立商品链表 
     * 文件信息的读写可参照第22章课件或fileIOreferrence函数
     */

	(*L) = (GoodsList *)malloc(sizeof(GoodsList));
	r = (*L);
	p=NULL;
	r->next = NULL;
	if ((fp = fopen(GOODS_FILE_NAME, "r")) == NULL)
	{
		if ((fp = fopen(GOODS_FILE_NAME, "w")) == NULL)
			printf("提示：不能创建商品文件\n");
	}
	else {
		fgetc(fp);  //用于判断是否是空文件。对于空文件，在feof之前，先调用该函数，feof才返回为1 
		if (!feof(fp)) {     
		   while (!feof(fp))
		   {
		      fseek(fp,-1,SEEK_CUR);  //回退一个字符。之前fgetc读了一个，这个函数将光标回退回去。
			  // TO DO YOUR WORK 
              fscanf(fp, "%s", goodsInfo.goods_id);
              fscanf(fp, "\t%s", goodsInfo.goods_name);  //下面的fscanf调用可参考本例子，特别注意\t的使用 
			  fscanf(fp, "\t%d", &goodsInfo.goods_price);
			  fscanf(fp, "\t%s", goodsInfo.goods_discount);
			  fscanf(fp, "\t%d", &goodsInfo.goods_amount);
			  fscanf(fp, "\t%d\n", &goodsInfo.goods_remain);  //读到这里就已经获取完一条商品记录，思考下为什么？ 
              //调用malloc分配商品结点内存，链接到链尾，增加商品数CurrentCnt 
			  p = malloc(sizeof(GoodsList));
			  p->data = goodsInfo;
			  if (r->next == NULL)
			  {
				r->next = p;
				p->next = NULL;
				++CurrentCnt;
			  }
			  else
			  {
				  GoodsList* temp = r;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = p;
				p->next = NULL;
				++CurrentCnt;
			  }			  
		      fgetc(fp);  //用于测试是否读到文件结束标志EOF，决定while中的feof是否返回1。原因与空文件的判断类似 
		    }//while 
		}
    }//else
	fclose(fp);
	if(p!=NULL)
		p->next = NULL;
	printf("商品的链表文件已建立，有%d个商品记录\n", CurrentCnt);
}
//-------------------------------------------------------------
//以行读取输入的信息
//-------------------------------------------------------------
int read_line(char str[], int n)
{
	int ch, i = 0;

	while (isspace(ch = getchar()))
		;
	while (ch != '\n' && ch != EOF) {
		if (i < n)
			str[i++] = ch;
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}

//--------------------------------------------------------------------
// 从键盘获取商品的基本信息
//--------------------------------------------------------------------
GoodsInfo read_goods_info(){
	GoodsInfo goodsInfo;
	printf("输入商品信息：\n");
	printf("商品ID：");
	read_line(goodsInfo.goods_id, MAX_ID_LEN);    //字符串类型的成员用此函数读取 
	read_line(goodsInfo.goods_name, MAX_NAME_LEN);
	scanf("%d", &goodsInfo.goods_price);
	read_line(goodsInfo.goods_discount, MAX_DISCOUNT_LEN);
	scanf("%d", &goodsInfo.goods_amount);
	scanf("%d", &goodsInfo.goods_remain);
	return goodsInfo;
}

//-------------------------------------------------------------
//添加一条商品记录
// goodsInfo为等待添加的商品基本信息
// choice为添加的方法（0为链尾插入新商品；1为链头插入新商品；大于1但是未超出范围时，数值表示在中间i号位置插入新商品，
// 例如输入3，应该在第二个节点后插入新节点。如果超出范围，提示出错信息。）
//【选作】根据ID号在插入的时候进行查重，如果已有该ID号，提示重复
//-------------------------------------------------------------
bool insert_item(GoodsList *L, GoodsInfo goodsInfo, int choice) {
	GoodsList *temp;
	GoodsList *pre = L, *p = L->next;
	int i;
	if (CurrentCnt >= 100) {
		printf("信息库已满，要插入请先删除一定量的商品数据!\n");
		return false;
	}
	switch (choice) {
		case 0:
			//尾插法插入新商品
			temp = malloc(sizeof(GoodsList));
			while (pre->next != NULL)
				pre = pre->next;
			temp->data = goodsInfo;
			pre->next = temp;
			temp->next = NULL;
			pre = L;
	        printf("Tips:添加商品%s成功\n", goodsInfo.goods_name);	        
	  		return true;
		case 1:
			//头插法插入新商品
			temp = malloc(sizeof(GoodsList));
			temp->data = goodsInfo;
			temp->next = pre->next;
			pre->next = temp;
  	        printf("Tips:添加商品%s成功\n", goodsInfo.goods_name);
			return true;
		default:
			//中间i号位置插入新商品，例如：输入3，应该在第二个节点后插入新节点
			//CurrentCnt 改为 CurrentCnt+1，因为当 CurrentCnt 为2时，链表中有两个记录，
			//此时输入3，即 choise为 3，表示在第二条记录后插入数据，新记录成为第3条数据
			if (choice <= CurrentCnt + 1)
			{	
				while (choice > 1)
				{
					pre = pre->next;
					choice--;
				}
				CurrentCnt++;
				temp = malloc(sizeof(GoodsList));
				if (
					pre->next == NULL) {
					temp->data = goodsInfo;
					pre->next = temp;
					temp->next = NULL;
					pre = L;
				}
				else {
					temp->data = goodsInfo;
					temp->next = pre->next;
					pre->next = temp;
					pre = L;
				}
				printf("Tips:添加商品%s成功\n", goodsInfo.goods_name);  //i有效时
			}		
			else
				printf("输入的位置超出当前商品列表范围\n");  //i无效时
        	return true;
	}
}


//-------------------------------------------------------------
//删除一条商品记录
//将goods_id指向的商品结点从商品链表中取下，调用free释放内存空间
//-------------------------------------------------------------
bool delete_item(GoodsList *L, char* goods_id) {
	GoodsList *pre = L, *p = L->next;
	while (p != NULL && (strcmp(p->data.goods_id, goods_id))) {
		p = p->next;
		pre = pre->next;
    }
	if(p==NULL)
		printf("商品%s对应的商品不存在", goods_id);
	else
	{
		pre->next = p->next;
		free(p);
		p = NULL;
		printf("商品%s对应的商品已被删除", goods_id);
	}
    // 如果商品ID存在，则删除后打印   
    // 如果商品ID不存在，则打印错误提示，   
}


//-------------------------------------------------------------
//查找一条商品记录
// goods_id为待查找的商品编号
// 返回指向该商品结点的指针
//-------------------------------------------------------------

GoodsList* search_item(GoodsList *L, char* goods_id) {
	GoodsList *p = L->next;
	while (p != NULL && (strcmp(p->data.goods_id, goods_id))) {
		p = p->next;
	}	
	return p;
}

//-------------------------------------------------------------
//修改一条商品记录
// new_info为商品的新信息，用这些新信息替换该商品的原有信息
//调用函数search_item，找到goods_id对应的商品结点
//-------------------------------------------------------------
bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info) {
	GoodsList *p = L->next;
	GoodsList *ptarget = search_item(L, goods_id);
	if (ptarget == NULL) {
		printf("商品%s对应的商品不存在",goods_id);   
		return false;
	}
	else {		
		ptarget->data = new_info;
		return true;
	}
}


//-------------------------------------------------------------
//打印单个商品链表节点的信息
//该函数用于实现打印指定结点的信息（结构中的所有成员的信息），如果结点为空，则直接返回。 
//-------------------------------------------------------------
void output_one_item(GoodsList *p){
	if(p == NULL)
		return;
	else {
		printf("%s", p->data.goods_id);
		printf("\t%s", p->data.goods_name);
		printf("\t%d", p->data.goods_price);
		printf("\t%s", p->data.goods_discount);
		printf("\t%d", p->data.goods_amount);
		printf("\t%d\n", p->data.goods_remain);
		return;
	}
}


//-------------------------------------------------------------
//在屏幕上输出所有商品信息
//这个商品链表跟inventory有差异，第一个商品结点不是由list指针指向，而是由一个结构指向，这个结构没有data
//p = L->next; p才是第一个商品结点
//-------------------------------------------------------------
void output_all_items(GoodsList *L)
{
	GoodsList *p = L->next;
	while (p != NULL)
	{
		output_one_item(p);
		p = p->next;
	}
}

//-------------------------------------------------------------
//释放商品链表
//destory_list_and_file的子函数
//调用free函数释放所有结点（释放之前通过malloc获得的内存），将CurrnetCnt清0，链头指针*L设置为NULL
//-------------------------------------------------------------
void destory_list(GoodsList **L) {
	if (L == NULL || *L == NULL)
		return;
	GoodsList *pre = *L, *p = (*L)->next;
	while (p != NULL) {
		delete_item(p, p->data.goods_id);
		p = p->next;
	}	
	CurrentCnt = 0;
	*L = NULL;
}

//-------------------------------------------------------------
//删除商品文件以及商品链表中的所有信息
//先删除商品链表中的所有信息
//再删除商品文件 
//-------------------------------------------------------------
void destory_list_and_file(GoodsList **L) {
	//调用destory_list函数和remove函数，remove的用法remove(GOODS_FILE_NAME); 
	destory_list(L);
	remove(GOODS_FILE_NAME);
}

//-------------------------------------------------------------
//将当前商品链表中的所有商品信息存入文件goodsinfo.txt，返回存入商品的个数
//提示：调用fprintf将所有商品链上的商品信息写入指定文件goodsinfo.txt，
// 并调用fclose释放已分配的文件空间，返回文件中保存的商品条数。
// 如果不能正常打开goodsinfo.txt，则提示错误信息。
//-------------------------------------------------------------
int save_to_file(GoodsList *L) {
	if(L == NULL)
		return 0;
	GoodsList *p = L->next;
	FILE *fp;
    int save_count = 0;  
  	if ((fp = fopen("goodsinfo.txt", "w")) == NULL)
	{
		printf("提示：不能打开商品文件\n");
		return 0;
	}
	while (p != NULL) {
		fprintf(fp, "%s", p->data.goods_id);
		fprintf(fp, "\t%s", p->data.goods_name);
		fprintf(fp, "\t%d", p->data.goods_price);
		fprintf(fp, "\t%s", p->data.goods_discount);
		fprintf(fp, "\t%d", p->data.goods_amount);
		fprintf(fp, "\t%d\n", p->data.goods_remain);
		p = p->next;
	}
	fclose(fp);
	return save_count;
}

//--------------------------------------------------------------------
//采用冒泡排序算法实现对商品链上的商品信息按照价格从低到高排序
//--------------------------------------------------------------------
void bubble_sort(GoodsList *L) {
	GoodsList *p=L->next;
	GoodsList* guide = L->next;
	GoodsInfo temp;
	int n = CurrentCnt;
	int i, j;
	if (L == NULL || L->next == NULL)
		printf("当前链表中没有商品\n");
	else {
		for (i = 0; i < n - 1; i++) {
			p = guide;
			for (j = 1; j <= n - i - 1; j++) {
				if (p->data.goods_price > p->next->data.goods_price) {
					temp = p->data;
					p->data = p->next->data;
					p->next->data = temp;
				}
				p = p->next;
			}
			guide = guide->next;
		}
	}
}

//--------------------------------------------------------------------
//主函数
//
//1.初始化一个链表
//2.循环显示商品管理系统的操作选择列表
//3.用户选择后调用相应的函数进行处理，处理完成后再度显示操作选择列表
//4.如果选择超出列表范围，则默认退出系统。
// 
//--------------------------------------------------------------------
int main(void)
{
	GoodsList *goodsList;
	init_list(&goodsList);
	GoodsInfo item;
	char temp_id[MAX_ID_LEN];
	while (1) {
		int choice;
		printf("超市商品管理系统\n");
		printf("********************************************\n");
		printf("1.显示所有商品的信息:\n");
		printf("2.修改某个商品的信息:\n");
		printf("3.插入某个商品的信息:\n");
		printf("4.删除某个商品的信息:\n");
		printf("5.查找某个商品的信息:\n");
		printf("6.商品存盘并退出系统:\n");
		printf("7.对商品价格进行排序:\n");
		printf("8.(慎用)删除所有内容:\n");
		printf("其他.不存盘并退出系统:\n");
		printf("********************************************\n");
		printf("输入您的选择: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				output_all_items(goodsList);
				break;
			case 2:      
                printf("输入要修改记录的 ID：");
				scanf("%s", temp_id);
				change_item(goodsList, temp_id, item);
				break;
			case 3:
				 
				printf("输入数字表明你要插入的商品位置：0.商品列表尾部 1.商品列表头部 i.商品列表中间第i号位置\n");
				scanf("%d", &choice);
				insert_item(goodsList, item, choice);
				break;
			case 4:
				
				printf("输入要删除记录的 ID：");
				scanf("%s", temp_id);
				delete_item(goodsList, temp_id);
				break;
			case 5:
				
				printf("输入要查找记录的 ID：");
				scanf("%s", temp_id);
				if(search_item(goodsList,temp_id))
					output_one_item(search_item(goodsList, temp_id));
				else 
					printf("您查询的商品%s不存在!\n",temp_id);   
				break;
			case 6:
				save_to_file(goodsList);
				printf("您已经存盘并退出超市商品管理系统!\n");
				return 0;
			case 7:
				bubble_sort(goodsList);
				break;
			case 8:
				destory_list_and_file(&goodsList);
				printf("您已经删除商品文件内容以及链表内容!\n");
				break;
			default:
				destory_list(&goodsList);
				printf("您已经退出超市商品管理系统!\n");
			    return 0;
		}
	}
}
