#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
double d[maxn][maxn],p[maxn];
int main(){
    freopen("data7","r",stdin);
    freopen("new_data","w",stdout);
    int n,c;double w;
    scanf("%d%d%lf",&n,&c,&w);
    for (int i=0;i<=n;i++){
        for (int j=0;j<=n;j++)
            scanf("%lf",&d[i][j]);
    }
    for (int i=0;i<=n;i++)scanf("%lf",&p[i]);
    printf("[\n");
    for (int i=0;i<=n;i++){
        printf("[%.2f",d[i][0]);
        for (int j=1;j<=n;j++)
            printf(",%.2f",d[i][j]);
        printf("],\n");
    }
    printf("]\n");
    printf("[%.2f",p[0]);
    for (int j=1;j<=n;j++)printf(",%.2f",p[j]);
    printf("]\n");
}