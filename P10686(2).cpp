#include<bits/stdc++.h>//����ͷ
using namespace std;
const int N=5e6+10;

struct T{
	int a,b,c;
}t[N];

int n,m,fa[N],ans1,ans2,ansnum;//ans1�ǲ��У�ans2��������ansnum��ͳ�Ʋ��еĸ���

inline void init(){//��ʼ�����鼯
	for(int i=1;i<=3*n;i++)	fa[i]=i;
}

inline int find(int x){//��ѯ
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void noin(int x,int y){//�ϲ�
	fa[find(x)]=find(y);
}

int main(){
	while(cin>>n){
		cin>>m;
		ans1=0,ans2=0,ansnum=0;
		init();
		if(m==0){	printf("Player 0 can be determined to be the judge after 0 lines\n");continue;}//����һ��
		for(int i=1;i<=m;i++){
			char s;
			cin>>t[i].a>>s>>t[i].b;
			t[i].a++,t[i].b++;//ȥ��С����Ϊ0�����
			if(s=='>') t[i].c=1;
			if(s=='=') t[i].c=2;
			if(s=='<'){//ͳһ ��'>'
				t[i].c=1;
				swap(t[i].a,t[i].b);
			}
		}
		for(int i=1;i<=n;i++){//ö�ٲ���
			int flag=1;//��¼�Ƿ���ڲ���
			init();//��ʼ��
			for(int j=1;j<=m;j++){
				if(t[j].a==i||t[j].b==i)	continue;
				if(t[j].c==2){//ƽ��
//					if(t[j].a==t[j].b)	continue;//Ҫ��Ҫ��һ����(*/�أ�*)
					if((find(t[j].a)==find(t[j].b+n))||(find(t[j].a+n)==find(t[j].b))){
						flag=0;//û�в���
						ans2=max(ans2,j);break;//��¼����
					}
					noin(t[j].a,t[j].b);
					noin(t[j].a+n,t[j].b+n);
					noin(t[j].a+2*n,t[j].b+2*n);
				}
				if(t[j].c==1){//'>'�����(�Ѵ����'<'�������)
					if((find(t[j].a)==find(t[j].b))||(find(t[j].a)==find(t[j].b+n))){
						flag=0;//û�в���
						ans2=max(ans2,j);break;//��¼����
					}
					noin(t[j].a,t[j].b+2*n);
					noin(t[j].a+n,t[j].b);
					noin(t[j].a+2*n,t[j].b+n);
				}
			}
			if(flag==1) ansnum++,ans1=i;//���ڲ��У��ͼ�¼��
		//	cout<<ansnum<<'\n';
		}
		if(ansnum==1)	printf("Player %d can be determined to be the judge after %d lines\n",ans1-1,ans2);//��Ϊ�����ʼ��С���Ѷ���� 1�����Դ�ʱ��ԭ�� 1
		else if(ansnum>1)	printf("Can not determine\n");//���ڶ������
		else	printf("Impossible\n");//�Ҳ�������
	}
	return 0;
}
