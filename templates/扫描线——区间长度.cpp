// ����ÿ����ѯ����С����
// ����һ����ά��������intervals������intervals[i] = [l, r]
// ��ʾ��i�����俪ʼ��l��������r������ĳ�����r-l+1
// ����һ����������queries��queries[i]��ʾҪ��ѯ��λ��
// �������а���queries[i]�������У���С���ȵ������Ƕ೤
// ���������Ӧ��ѯ�����д𰸣����������������������ô����-1
// �������� : https://leetcode.cn/problems/minimum-interval-to-include-each-query/
#include<bits/stdc++.h>
using namespace std;

struct Range {
    int l, r ,len;
    /*
    friend std::ostream& operator<<(std::ostream& os, const Range& range) {
        os << "(" << range.len<<", "<<range.l << ", " << range.r << ")";
        return os;
    }
    */
    //��δ�����Ϊ�����   ��Ȼ����û�б�Ҫ��
};

struct Dot{
    int subscript,value;
};

bool compare(Range& a,Range& b) {
    return a.len > b.len;
}
//Ϊ������С����

bool cmp1(Range a,Range b){
    return a.l<b.l;
}

bool cmp2(Dot a,Dot b){
    return a.value<b.value;
}
//���������ȽϺ�������Ϊ�˴�С��������

int main()
{
    int n,m;
    cin>>n>>m;
    int ans[m];
    std::priority_queue<Range, std::vector<Range>, decltype(&compare)> pq(compare);
    //����С����
    Range range[n+1];
    Dot dot[m+1];
    for(int i=1;i<=n;i++){
        cin>>range[i].l>>range[i].r;
        range[i].len=range[i].r-range[i].l+1;
    }
    sort(range+1,range+n+1,cmp1);
    /*
    for(int i=1;i<=n;i++){
        printf("%3d %3d %3d\n",range[i].l,range[i].r,range[i].len);
    }
    */
    for(int i=1;i<=m;i++){
        cin>>dot[i].value;
        dot[i].subscript=i;
    }
    sort(dot+1,dot+m+1,cmp2);
    /*
    for(int i=1;i<=m;i++){
        printf("%3d %3d\n",dot[i].value,dot[i].subscript);
    }
    */
    for(int i=1,j=1;i<=m;i++){
        //��С�����������ɨ����
        while(dot[i].value>=range[j].l&&j<=n){
            pq.push(range[j]);
            j++;
        }
        //������Ҫ���������뵽С������
        //cout<<pq.top()<<endl;
        while(!pq.empty()&&pq.top().r<dot[i].value){
            pq.pop();
        }
        //ֻ��Ҫ�ж�С���ѵĶ��˵������ǲ��Ƿ���Ҫ���  ���Ǿ͵���
        if(!pq.empty()){
            ans[dot[i].subscript]=pq.top().len;
        }else{
            ans[dot[i].subscript]=-1;
        }
    }
    for(int i=1;i<=m;i++){
        printf("%3d",ans[i]);
    }
    return 0;
}
