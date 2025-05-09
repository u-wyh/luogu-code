//https://acm.hdu.edu.cn/showproblem.php?pid=1560
//https://www.cnblogs.com/LuckyGlass-blog/p/9061081.html
//IDA*ʵ���Ͽ��Կ����� dfs��A*�㷨  ����ǿ��������
//�ؼ�����ô��Ԥ�⺯��  �Լ���ô����Ԥ�⺯�����
//D()Ϊ��ǰ��ȣ���A[i],C[i],G[i],T[i]�����ʾACGT�ڵ�i��������δƥ���������ĸ���������������
//G()=max(A[])+max(G[])+max(C[])+max(T[])
//������δƥ������Ϊ"ACA","GG","ACG",��max A[]=2,max G[]=2,max C[]=1,����G()=5��
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

int n,depth;
int len[10];
int chr[10][4];//ͳ�ƴ�Ƶ
int mat[10];//��ʾ��Щ�ַ���Ŀǰ������λ��
char DNA[10][10];

//������������ڹ����޶ȵ�
inline int GetPri(){
	int ret=0;
	for(int j=0;j<4;j++){
		int Max=0;
		for(int i=0;i<n;i++)
			Max=max(Max,chr[i][j]);
		ret+=Max;
	}
	return ret;
}

bool ID_A_Star(int dep)
{
	int pri=GetPri();
	if(dep+pri>depth)
        return false;
	if(!pri){
        //��ʾ�����������  ����true
		return true;
    }
	for(int i=0;i<4;i++){
		char ch=i+'0';
        bool chg[10]={};//���ǻ��ݱ�־
        bool flag=true;
		for(int j=0;j<n;j++){
			if(DNA[j][mat[j]]==ch){
				chr[j][DNA[j][mat[j]]-'0']--;//��ʾ����ַ����������ĸ����1
				mat[j]++;//����ַ���ָ������һλ
				chg[j]=true;//���ڱ�� ׼������
				flag=false;//��ʾ�����Ч��
			}
		}
		if(!flag){
            //�����Ч��  ��ô���λ�þ��ǵ�ǰi����ĸ  ����������
            //���û��Ч�� ˵�����λ�������еĻ�������û�����õ�  �ǲ�Ӧ�õ�
			if(ID_A_Star(dep+1)){
				return true;
			}
		}
		if(!flag){
			//��ԭ����  ֻ�в����˲��б�Ҫ��ԭ
			for(int j=0;j<n;j++){
				if(chg[j]){
					mat[j]--,chr[j][DNA[j][mat[j]]-'0']++;
				}
			}
		}
	}
	return false;
}

int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		memset(DNA,'\0',sizeof DNA);
		memset(chr,0,sizeof chr);
		memset(len,0,sizeof len);
		memset(mat,0,sizeof mat);
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%s",DNA[i]);
			len[i]=strlen(DNA[i]);
			for(int j=0;j<len[i];j++){
				switch(DNA[i][j]){
					//���ַ��ĳ�1 2 3 4  ��������Ӧ��Ƶ
					case 'A': DNA[i][j]='0';chr[i][0]++;break;
					case 'C': DNA[i][j]='1';chr[i][1]++;break;
					case 'G': DNA[i][j]='2';chr[i][2]++;break;
					case 'T': DNA[i][j]='3';chr[i][3]++;break;
				}
			}
		}
		depth=GetPri();//��Ϊ���������ж�
		while(!ID_A_Star(0)){
			memset(mat,0,sizeof mat);
			depth++;
			//��ǰ��Ȳ��� ��Ҫ��һ
		}
		printf("%d\n",depth);
	}
	return 0;
}
