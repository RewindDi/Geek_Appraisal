#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//gcc src.c -std=c99 -o src
//���ҽ��i�ĸ����,ͨ���ݹ�õ���㵽���ĳ���
int findParent(int i,int huffman[][5],int n);
//���ݳ�ʼȨ�ع�����������
void huffmanTree(int w[],int huffman[][5],int n,int arr_big[]);
//Ѱ��Ȩ����С�������ڵ�
void findMin(int ii[],int huffman[][5],int n);
//��ÿ��Ҷ�ڵ���й���������
void HuffmanCode(int i,int huffman[][5],int n);
//��������char������
void inplace_swap(char *x,char *y);

int main()
{
    //��������ַ������м�¼�����ַ����ܸ���count�Լ������ַ��ĳ��ִ���arr_small[]����ͳ��
    char str[100];
    printf("Please Enter the string\n");
    scanf("%s", str);
    int arr_big[27] = {0};  //�����ַ��ĳ��ִ���
    int count = 0;  //�ַ����ܸ���
    for(int i = 0; i < strlen(str); i++)    //���������ַ����е������ַ�
    {
        for(int j = 0; j < 27; j++) //����26����д��ĸ
        {
            if(str[i] == (char)(0x41 + j))
            {
                arr_big[j] += 1;
                if(arr_big[j] == 1)
                {
                    /*����������*/		//��¼һ�������˼�����ĸ
                    count++;
                }
                break;
            }
        }
    }
    printf("the letter count is %d\n",count);   //��ӡ�����ַ��������˼�����ĸ

    //ͨ��arr_big�������ַ����г��ֵ���ĸ��������ͳ�ƣ���������arr_small��
    int count2 = 0;     //�ַ����г��ֵ��ַ��ܸ���
    int arr_small[count] ;  //ͳ�������ַ�������ĸ�ĳ��ִ���
    for(int i = 0; i < 27; i++)
    {
        if(/*����������*/arr_big[i]!=0)
        {
            arr_small[count2++] = arr_big[i];
			//printf("%d\n",arr_small[count]);	/*����ע�ͣ�˵�����ã�*///��û�õ�ȥ��
        }
    }
	
    //����int�Ͷ�ά���飬���鳤��[*]Ϊ���������Ľڵ����
    //c[*][0]��ŵ��Ǹýڵ��[���ڵ��λ��]��c[*][1]Ϊ�ýڵ��[�������ڵ��λ��]
    //c[*][2]��Ÿýڵ��[�������ڵ��λ��]��c[*][3]Ϊ�ýڵ��Ȩֵ
    int huffman[2 * count - 1][5];  //ǰn��ΪҶ��㣬��n-1��Ϊ�м���
	

    //���ݳ�ʼȨ������arr_small���ַ���������huffman��
    huffmanTree(arr_small,huffman,count,arr_big);

    //����Huffman���������ܳ���WPL
    int sum = 0;
    for(int i = 0;i < count;i++)
    {
        int length = 0;
        if(huffman[i][1] == -1 && huffman[i][2] == -1)  /*�����ж�ģ��ע��*///Ҷ��
        {
            length = findParent(i,huffman,count);   //�õ�����Ҷ���Ĵ�Ȩ·������
            /*����������*/  	//����Ҷ����Ȩ·�������ۼӵõ��ܳ���WPL
            sum = sum + length;
        }
    }
    printf("the tree's WPL  is  %d\n",sum);

    //Huffman����
    for(int i = 0;i < count;i++)
    {
        HuffmanCode(i,huffman,count);
    }

    return 0;
}

//�Ӻ�������������������
void huffmanTree(int w[],int huffman[][5],int count,int arr_big[])
{
    //����ʼ��
    for(int i = 0; i < 2 * count - 1; i++)
    {
        huffman[i][0] = -1;
        huffman[i][1] = -1;
        huffman[i][2] = -1;
        huffman[i][3] = -1;
        huffman[i][4] = -1;
    }
    int count3 = 0;
    for(int i = 0; i < 27; i++)
    {
        if(arr_big[i]!=0)
        {
            huffman[count3++][4] = 'A'+i;
        }
    }
    /*����ע�ͣ�˵�����ã�*///��ʼ��
    for(int i = 0; i < count; i++)
    {
        huffman[i][3] = w[i];//w[i]Ȩֵ
    }
    //ÿ�γ������Ȩ����С�Ľ����кϲ���ֱ�����ղ��������
    for(int i = count; i < 2 * count - 1; i++)
    {
        int i1,i2;  //Ȩ����С���������
        int ii[2];
        //�ҳ�����Ȩ����С�Ľ��
        findMin(ii,huffman,count);
        i1=ii[0];
        i2=ii[1];
        //�ϲ�i1��i2���,���½����Ϣ�������ɽ��������ӽ�㣬�ӽڵ��Ӧ�ĸ���㣬�����ɽ���Ȩ�أ�
		huffman[i][3] = huffman[i1][3] + huffman[i2][3];
		huffman[i1][0]=i;
		huffman[i2][0]=i;
		huffman[i][1]=i1;
		huffman[i][2]=i2;
        /*����������*/
        

    }
}
void findMin(int ii[], int huffman[][5], int n)
{
    //�ҳ���һ��Ȩ����С�Ľ��
    int min = 9999999;
    for (int i = 0; i < 2 * n - 1; i++)
    {
        if (huffman[i][3] == -1 && huffman[i][0] == -1)  /*�����ж�ģ��ע�ͣ�˵�����ã�*/
        {
            break;
        }
        if (huffman[i][3] < min && huffman[i][0] == -1)  /*�����ж�ģ��ע�ͣ�˵�����ã�*/
        {
            min = huffman[i][3];
            ii[0] = i;
        }
    }

    //�ҳ��ڶ���Ȩ����С�Ľ�㣨ģ���ϲ������б�д��
	int min2=999999;
    /*����������*/
	for (int j = 0; j<2*n-1;j++)
	{
		if(huffman[j][3]==-1 && huffman[j][0] ==-1)
		{
			break;
		}
		if(huffman[j][3] < min2 && huffman[j][0] ==-1 && j!=ii[0])
		{
			min2 =huffman[j][3];
			ii[1] =j;
		}
	}

}


//�Ӻ����������ҽ��i�ĸ����,�õ���㵽���ĳ���
int findParent(int i,int huffman[][5],int n)
{
    int length = 0;
    if(huffman[i][0] == -1)     /*�����ж�ģ��ע��*///��
    {
        return 0;
    }
    length += (findParent(huffman[i][0],huffman,n) + 1);    //ͨ���ݹ�õ���㵽����·������
    return length;
}

//�Ӻ���������ÿ��Ҷ�ڵ���й��������벢���д�ӡ
void HuffmanCode(int i,int huffman[][5],int n)
{
    char code[30];  //char����������
    int current=i;  //���嵱ǰ���ʵĽ��
    int father = huffman[i][0]; //���嵱ǰ���ĸ��ڵ�
    int start=0;    //ÿ�α����λ�ã���ʼΪ���뵹��λ��
    int first,last;     //char�����ͷ����β��

    while(father != -1)
    {
        /*����������*/		//�жϵ�ǰ���ĸ�����������Ƿ�Ϊ��ǰ���
        if(huffman[father][1]==current)
        {
        	code[start] = '0';
		}       /*����������*/		//�ӽ���Ǹ�����������������Ϊ0
        else
		{
			code[start] = '1';
		}        /*����������*/		//�ӽ���Ǹ�����������������Ϊ0

        current = father;               /*����������*/		//����˷Դ�����µ�ǰ���
        father = huffman[father][0];    /*����������*/		//ͬ����ǰ�����º󣩣����µ�ǰ���ĸ��׽��
        start += 1;                     /*����������*/		//���±���λ��
    }
    code[start]='\0';   //���������

    //��char�����е�Ԫ��ͷβ���˽��жԵ�
    for(first = 0, last = start-1; first < last; first++,last--)
    {
        //�Ե������ڲ�Ԫ��
        inplace_swap(&code[first], &code[last]);	/*�ú������Լ���д*/
    }
	printf("%c Huffman code:  %s\n",huffman[i][4],code);
}

//�Ӻ���������������char�����ݣ�ʹ���˲������㣩�����Լ������ÿɶ��ԽϺõķ�������ʵ�ָĺ���
void inplace_swap(char *x,char *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}
