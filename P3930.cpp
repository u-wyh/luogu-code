#include<bits/stdc++.h>
using namespace std;

char mp[60][60];
int vis[60][60],vit[60][60];
int nx[]={2,1,-1,-2,2,1,-1,-2};
int ny[]={-1,-2,-2,-1,1,2,2,1};
int bx[]={1,1,-1,-1};
int by[]={-1,1,-1,1};
int rx[]={1,0,-1,0};
int ry[]={0,1,0,-1};
struct node{
	int x,y,dis;
};

int main()
{
	int n;
	while(cin>>n){//������������
		int sx,sy,tx,ty;//����x����y������յ��x����y����
		for(register int i=1;i<=n;i++){
			scanf("%s",mp[i]+1);
			for(register int j=1;j<=n;j++){
				if(mp[i][j]=='O'){//��¼���
					sx=i;
					sy=j;
				}
				if(mp[i][j]=='X'){//��¼�յ�
					tx=i;
					ty=j;
				}
			}
		}
		memset(vis,0,sizeof(vis));
		for(register int x=1;x<=n;x++){
			for(register int y=1;y<=n;y++){
				if(mp[x][y]=='P'){//ʿ��ֻ�ܹ�����������
					if(x==8)
                        continue;
					if(y>1)
                        vis[x][y-1]++;
					if(y<8)
                        vis[x][y+1]++;
				}else if(mp[x][y]=='K'){
					for(register int i=0;i<8;i++){
						int ax=x+nx[i],ay=y+ny[i];
						if(ax<1 || ax>n || ay<1 || ay>n)
                            continue;
						vis[ax][ay]+=2;
					}
				}else if(mp[x][y]=='B'){//���̹�����Χ
					for(register int i=0;i<4;i++){
						int ax=x+bx[i],ay=y+by[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=4;
							ax+=bx[i];
							ay+=by[i];
						}
					}
				}else if(mp[x][y]=='C'){//�Ǳ�������Χ
					for(register int i=0;i<4;i++){
						int ax=x+rx[i],ay=y+ry[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=8;
							ax+=rx[i];
							ay+=ry[i];
						}
					}
				}else if(mp[x][y]=='Q'){//�ʺ󹥻���Χ�ڵ�
					for(register int i=0;i<4;i++){
						int ax=x+rx[i],ay=y+ry[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=16;
							ax+=rx[i];
							ay+=ry[i];
						}
					}
					for(register int i=0;i<4;i++){
						int ax=x+bx[i],ay=y+by[i];
						while(!(ax<1 || ax>n || ay<1 || ay>n)){
							vis[ax][ay]+=16;
							ax+=bx[i];
							ay+=by[i];
						}
					}
				}else if(mp[x][y]=='X'){
					for(register int i=0;i<4;i++){//������//�ʺ󹥻���Χ�ڵ�
						int ax=x+rx[i],ay=y+ry[i];
						if(!(ax<1 || ax>n || ay<1 || ay>n))vis[ax][ay]+=32;
					}
					for(register int i=0;i<4;i++){
						int ax=x+bx[i],ay=y+by[i];
						if(!(ax<1 || ax>n || ay<1 || ay>n))vis[ax][ay]+=32;
					}
				}
			}
		}
		if(vis[sx][sy]){
			puts("-1");
			continue;
		}
		memset(vit,0,sizeof(vit));//��ʼ��
		queue<node> q;
		q.push(node{sx,sy,0});
		vit[sx][sy]=1;
		while(!q.empty()){//��ʼ���й����������
			node f=q.front();
			q.pop();
			int x=f.x,y=f.y,dis=f.dis;
			if(x==tx && y==ty){
				cout<<dis<<endl;
				break;
			}
			for(register int i=0;i<8;i++){
				int ax=x+nx[i],ay=y+ny[i];
				if(ax<1 || ax>n || ay<1 || ay>n)continue;
				if(vit[ax][ay])continue;
				vit[ax][ay]=1;
				if(ax==tx && ay==ty){
					q.push(node{ax,ay,dis+1});
					break;
				}
				if(vis[ax][ay])continue;
				if(mp[ax][ay]=='P'){//�����һ����ʿ��
					mp[ax][ay]='.';
					if(ax<8){
						if(ay>1)mp[ax][ay-1]--;
						if(ay<8)mp[ax][ay+1]--;
					}
				}else if(mp[ax][ay]=='K'){//�����һ������ʿ
					mp[ax][ay]='.';
					for(register int i=0;i<8;i++){
						int cxk=ax+nx[i],cy=ay+ny[i];
						if(cxk<1 || cxk>n || cy<1 || cy>n)continue;
						vis[cxk][cy]-=2;
					}
				}else if(mp[ax][ay]=='B'){//�����һ��������
					mp[ax][ay]='.';
					for(register int i=0;i<4;i++){
						int cx=ax+bx[i],cy=ay+by[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n)){
							vis[cx][cy]-=4;
							cx+=bx[i];
							cy+=by[i];
						}
					}
				}else if(mp[ax][ay]=='C'){//�����һ���ǳǱ�
					mp[ax][ay]='.';
					for(register int i=0;i<4;i++){
						int cx=ax+rx[i],cy=ay+ry[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n)){
							vis[cx][cy]-=8;
							cx+=rx[i];
							cy+=ry[i];
						}
					}
				}else if(mp[ax][ay]=='Q'){//�����һ���ǻʺ�
					mp[ax][ay]='.';
					for(register int i=0;i<4;i++){
						int cx=ax+bx[i],cy=ay+by[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n)){
							vis[cx][cy]-=16;
							cx+=bx[i];
							cy+=by[i];
						}
					}
					for(register int i=0;i<4;i++){
						int cx=ax+rx[i],cy=ay+ry[i];
						while(!(cx<1 || cx>n || cy<1 || cy>n)){
							vis[cx][cy]-=16;
							cx+=rx[i];
							cy+=ry[i];
						}
					}
				}
				q.push(node{ax,ay,dis+1});
			}
		}
	}
	return 0;//���п���
}
