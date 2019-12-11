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
//��Ʒ��Ϣ�ṹ�Ķ���
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
//������Ʒ����Ľ��
//--------------------------------------------------------------------
typedef struct node
{
	GoodsInfo data;
	struct node *next;
} GoodsList;

//ȫ�ֱ������洢��ǰ��Ʒ������
int CurrentCnt;

//--------------------------------------------------------------------
//�ο������������������ṩ�ļ������Ĳ���
//--------------------------------------------------------------------
void fileIOreferrence(void)
{
    char tempstring[30];

    //�����ļ�������ָ��
    FILE *fp;
    //fopen���ڴ��ļ�����������������һ�����ļ���·����һ�����ļ��򿪵ķ�ʽ
    //����xxxxxx.txt�͸���Ŀ�Ŀ�ִ���ļ���ͬһĿ¼�£���˴�ֻ��Ҫ����ȡ�����ļ���
    //����r������ֻ����ʽ���ļ�
    fp = fopen("xxxxxxx.txt", "r"); 
    //���w�����ֻд�ļ������ļ������򳤶���Ϊ0�������ļ�������ʧ�����������򴴽����ļ�
    //����򿪷�ʽ�����в����ĵ�
    fp = fopen("xxxxxxx.txt", "w");

    //fscanf���ڴ�txt�ļ��ж�ȡ���ݣ��������ַ�����ʽ����һ���ַ��������tempstring��
    fscanf(fp, "%s", tempstring);
    //�����Ը�ʽ���ķ�ʽ�����ַ���
    fscanf(fp, "\t%s\n", tempstring);

    //fprintf�Ը�ʽ���ķ�ʽ��txt�ļ���д������
    fprintf(fp, "%s\t", tempstring);

    //����ļ������Ƿ��Ѿ������ļ���������
    fgetc(fp);
    while ( !feof(fp))
    {
        rewind(fp);	 
		//��������
    }
       
    //�ļ�������ɺ���Ҫʹ��fclose�ر��ļ�ָ��
    fclose(fp);
    
    //ɾ���ļ�
	remove("xxxxxxx.txt"); 
}

//--------------------------------------------------------------------
//�����Ʒ�ļ�goodsinfo.txt�����ڣ��򴴽����ļ��� 
//������ڣ�����Ʒ�ļ�goodsinfo.txt�Ѽ�¼����Ʒ���ݶ�������������Ʒ����
//�����Ʒ�����inventory�в��죬��һ����Ʒ��㲻����listָ��ָ�򣬶�����һ���ṹ*Lָ������ṹû��data
//p = (*L)->next; p���ǵ�һ����Ʒ���
//--------------------------------------------------------------------
void init_list(GoodsList **L) {
	FILE *fp;
	GoodsInfo goodsInfo;
	GoodsList *p, *r;
    /*
     * 1.�ж�goodsinfo.txt�Ƿ���ڣ����������½�һ��goodsinfo.txt
     * 2.������ڣ���δ�ﵽ�ļ�β������£�����feof���������Ӹ��ļ��ж�ȡ��Ʒ��Ϣ������fscanf������ ��������Ʒ���� 
     * �ļ���Ϣ�Ķ�д�ɲ��յ�22�¿μ���fileIOreferrence����
     */

	(*L) = (GoodsList *)malloc(sizeof(GoodsList));
	r = (*L);
	p=NULL;
	r->next = NULL;
	if ((fp = fopen(GOODS_FILE_NAME, "r")) == NULL)
	{
		if ((fp = fopen(GOODS_FILE_NAME, "w")) == NULL)
			printf("��ʾ�����ܴ�����Ʒ�ļ�\n");
	}
	else {
		fgetc(fp);  //�����ж��Ƿ��ǿ��ļ������ڿ��ļ�����feof֮ǰ���ȵ��øú�����feof�ŷ���Ϊ1 
		if (!feof(fp)) {     
		   while (!feof(fp))
		   {
		      fseek(fp,-1,SEEK_CUR);  //����һ���ַ���֮ǰfgetc����һ������������������˻�ȥ��
			  // TO DO YOUR WORK 
              fscanf(fp, "%s", goodsInfo.goods_id);
              fscanf(fp, "\t%s", goodsInfo.goods_name);  //�����fscanf���ÿɲο������ӣ��ر�ע��\t��ʹ�� 
			  fscanf(fp, "\t%d", &goodsInfo.goods_price);
			  fscanf(fp, "\t%s", goodsInfo.goods_discount);
			  fscanf(fp, "\t%d", &goodsInfo.goods_amount);
			  fscanf(fp, "\t%d\n", &goodsInfo.goods_remain);  //����������Ѿ���ȡ��һ����Ʒ��¼��˼����Ϊʲô�� 
              //����malloc������Ʒ����ڴ棬���ӵ���β��������Ʒ��CurrentCnt 
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
		      fgetc(fp);  //���ڲ����Ƿ�����ļ�������־EOF������while�е�feof�Ƿ񷵻�1��ԭ������ļ����ж����� 
		    }//while 
		}
    }//else
	fclose(fp);
	if(p!=NULL)
		p->next = NULL;
	printf("��Ʒ�������ļ��ѽ�������%d����Ʒ��¼\n", CurrentCnt);
}
//-------------------------------------------------------------
//���ж�ȡ�������Ϣ
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
// �Ӽ��̻�ȡ��Ʒ�Ļ�����Ϣ
//--------------------------------------------------------------------
GoodsInfo read_goods_info(){
	GoodsInfo goodsInfo;
	printf("������Ʒ��Ϣ��\n");
	printf("��ƷID��");
	read_line(goodsInfo.goods_id, MAX_ID_LEN);    //�ַ������͵ĳ�Ա�ô˺�����ȡ 
	read_line(goodsInfo.goods_name, MAX_NAME_LEN);
	scanf("%d", &goodsInfo.goods_price);
	read_line(goodsInfo.goods_discount, MAX_DISCOUNT_LEN);
	scanf("%d", &goodsInfo.goods_amount);
	scanf("%d", &goodsInfo.goods_remain);
	return goodsInfo;
}

//-------------------------------------------------------------
//���һ����Ʒ��¼
// goodsInfoΪ�ȴ���ӵ���Ʒ������Ϣ
// choiceΪ��ӵķ�����0Ϊ��β��������Ʒ��1Ϊ��ͷ��������Ʒ������1����δ������Χʱ����ֵ��ʾ���м�i��λ�ò�������Ʒ��
// ��������3��Ӧ���ڵڶ����ڵ������½ڵ㡣���������Χ����ʾ������Ϣ����
//��ѡ��������ID���ڲ����ʱ����в��أ�������и�ID�ţ���ʾ�ظ�
//-------------------------------------------------------------
bool insert_item(GoodsList *L, GoodsInfo goodsInfo, int choice) {
	GoodsList *temp;
	GoodsList *pre = L, *p = L->next;
	int i;
	if (CurrentCnt >= 100) {
		printf("��Ϣ��������Ҫ��������ɾ��һ��������Ʒ����!\n");
		return false;
	}
	switch (choice) {
		case 0:
			//β�巨��������Ʒ
			temp = malloc(sizeof(GoodsList));
			while (pre->next != NULL)
				pre = pre->next;
			temp->data = goodsInfo;
			pre->next = temp;
			temp->next = NULL;
			pre = L;
	        printf("Tips:�����Ʒ%s�ɹ�\n", goodsInfo.goods_name);	        
	  		return true;
		case 1:
			//ͷ�巨��������Ʒ
			temp = malloc(sizeof(GoodsList));
			temp->data = goodsInfo;
			temp->next = pre->next;
			pre->next = temp;
  	        printf("Tips:�����Ʒ%s�ɹ�\n", goodsInfo.goods_name);
			return true;
		default:
			//�м�i��λ�ò�������Ʒ�����磺����3��Ӧ���ڵڶ����ڵ������½ڵ�
			//CurrentCnt ��Ϊ CurrentCnt+1����Ϊ�� CurrentCnt Ϊ2ʱ����������������¼��
			//��ʱ����3���� choiseΪ 3����ʾ�ڵڶ�����¼��������ݣ��¼�¼��Ϊ��3������
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
				printf("Tips:�����Ʒ%s�ɹ�\n", goodsInfo.goods_name);  //i��Чʱ
			}		
			else
				printf("�����λ�ó�����ǰ��Ʒ�б�Χ\n");  //i��Чʱ
        	return true;
	}
}


//-------------------------------------------------------------
//ɾ��һ����Ʒ��¼
//��goods_idָ�����Ʒ������Ʒ������ȡ�£�����free�ͷ��ڴ�ռ�
//-------------------------------------------------------------
bool delete_item(GoodsList *L, char* goods_id) {
	GoodsList *pre = L, *p = L->next;
	while (p != NULL && (strcmp(p->data.goods_id, goods_id))) {
		p = p->next;
		pre = pre->next;
    }
	if(p==NULL)
		printf("��Ʒ%s��Ӧ����Ʒ������", goods_id);
	else
	{
		pre->next = p->next;
		free(p);
		p = NULL;
		printf("��Ʒ%s��Ӧ����Ʒ�ѱ�ɾ��", goods_id);
	}
    // �����ƷID���ڣ���ɾ�����ӡ   
    // �����ƷID�����ڣ����ӡ������ʾ��   
}


//-------------------------------------------------------------
//����һ����Ʒ��¼
// goods_idΪ�����ҵ���Ʒ���
// ����ָ�����Ʒ����ָ��
//-------------------------------------------------------------

GoodsList* search_item(GoodsList *L, char* goods_id) {
	GoodsList *p = L->next;
	while (p != NULL && (strcmp(p->data.goods_id, goods_id))) {
		p = p->next;
	}	
	return p;
}

//-------------------------------------------------------------
//�޸�һ����Ʒ��¼
// new_infoΪ��Ʒ������Ϣ������Щ����Ϣ�滻����Ʒ��ԭ����Ϣ
//���ú���search_item���ҵ�goods_id��Ӧ����Ʒ���
//-------------------------------------------------------------
bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info) {
	GoodsList *p = L->next;
	GoodsList *ptarget = search_item(L, goods_id);
	if (ptarget == NULL) {
		printf("��Ʒ%s��Ӧ����Ʒ������",goods_id);   
		return false;
	}
	else {		
		ptarget->data = new_info;
		return true;
	}
}


//-------------------------------------------------------------
//��ӡ������Ʒ����ڵ����Ϣ
//�ú�������ʵ�ִ�ӡָ��������Ϣ���ṹ�е����г�Ա����Ϣ����������Ϊ�գ���ֱ�ӷ��ء� 
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
//����Ļ�����������Ʒ��Ϣ
//�����Ʒ�����inventory�в��죬��һ����Ʒ��㲻����listָ��ָ�򣬶�����һ���ṹָ������ṹû��data
//p = L->next; p���ǵ�һ����Ʒ���
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
//�ͷ���Ʒ����
//destory_list_and_file���Ӻ���
//����free�����ͷ����н�㣨�ͷ�֮ǰͨ��malloc��õ��ڴ棩����CurrnetCnt��0����ͷָ��*L����ΪNULL
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
//ɾ����Ʒ�ļ��Լ���Ʒ�����е�������Ϣ
//��ɾ����Ʒ�����е�������Ϣ
//��ɾ����Ʒ�ļ� 
//-------------------------------------------------------------
void destory_list_and_file(GoodsList **L) {
	//����destory_list������remove������remove���÷�remove(GOODS_FILE_NAME); 
	destory_list(L);
	remove(GOODS_FILE_NAME);
}

//-------------------------------------------------------------
//����ǰ��Ʒ�����е�������Ʒ��Ϣ�����ļ�goodsinfo.txt�����ش�����Ʒ�ĸ���
//��ʾ������fprintf��������Ʒ���ϵ���Ʒ��Ϣд��ָ���ļ�goodsinfo.txt��
// ������fclose�ͷ��ѷ�����ļ��ռ䣬�����ļ��б������Ʒ������
// �������������goodsinfo.txt������ʾ������Ϣ��
//-------------------------------------------------------------
int save_to_file(GoodsList *L) {
	if(L == NULL)
		return 0;
	GoodsList *p = L->next;
	FILE *fp;
    int save_count = 0;  
  	if ((fp = fopen("goodsinfo.txt", "w")) == NULL)
	{
		printf("��ʾ�����ܴ���Ʒ�ļ�\n");
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
//����ð�������㷨ʵ�ֶ���Ʒ���ϵ���Ʒ��Ϣ���ռ۸�ӵ͵�������
//--------------------------------------------------------------------
void bubble_sort(GoodsList *L) {
	GoodsList *p=L->next;
	GoodsList* guide = L->next;
	GoodsInfo temp;
	int n = CurrentCnt;
	int i, j;
	if (L == NULL || L->next == NULL)
		printf("��ǰ������û����Ʒ\n");
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
//������
//
//1.��ʼ��һ������
//2.ѭ����ʾ��Ʒ����ϵͳ�Ĳ���ѡ���б�
//3.�û�ѡ��������Ӧ�ĺ������д���������ɺ��ٶ���ʾ����ѡ���б�
//4.���ѡ�񳬳��б�Χ����Ĭ���˳�ϵͳ��
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
		printf("������Ʒ����ϵͳ\n");
		printf("********************************************\n");
		printf("1.��ʾ������Ʒ����Ϣ:\n");
		printf("2.�޸�ĳ����Ʒ����Ϣ:\n");
		printf("3.����ĳ����Ʒ����Ϣ:\n");
		printf("4.ɾ��ĳ����Ʒ����Ϣ:\n");
		printf("5.����ĳ����Ʒ����Ϣ:\n");
		printf("6.��Ʒ���̲��˳�ϵͳ:\n");
		printf("7.����Ʒ�۸��������:\n");
		printf("8.(����)ɾ����������:\n");
		printf("����.�����̲��˳�ϵͳ:\n");
		printf("********************************************\n");
		printf("��������ѡ��: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				output_all_items(goodsList);
				break;
			case 2:      
                printf("����Ҫ�޸ļ�¼�� ID��");
				scanf("%s", temp_id);
				change_item(goodsList, temp_id, item);
				break;
			case 3:
				 
				printf("�������ֱ�����Ҫ�������Ʒλ�ã�0.��Ʒ�б�β�� 1.��Ʒ�б�ͷ�� i.��Ʒ�б��м��i��λ��\n");
				scanf("%d", &choice);
				insert_item(goodsList, item, choice);
				break;
			case 4:
				
				printf("����Ҫɾ����¼�� ID��");
				scanf("%s", temp_id);
				delete_item(goodsList, temp_id);
				break;
			case 5:
				
				printf("����Ҫ���Ҽ�¼�� ID��");
				scanf("%s", temp_id);
				if(search_item(goodsList,temp_id))
					output_one_item(search_item(goodsList, temp_id));
				else 
					printf("����ѯ����Ʒ%s������!\n",temp_id);   
				break;
			case 6:
				save_to_file(goodsList);
				printf("���Ѿ����̲��˳�������Ʒ����ϵͳ!\n");
				return 0;
			case 7:
				bubble_sort(goodsList);
				break;
			case 8:
				destory_list_and_file(&goodsList);
				printf("���Ѿ�ɾ����Ʒ�ļ������Լ���������!\n");
				break;
			default:
				destory_list(&goodsList);
				printf("���Ѿ��˳�������Ʒ����ϵͳ!\n");
			    return 0;
		}
	}
}
