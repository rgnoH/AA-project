#include<bits/stdc++.h>
using namespace std;
char s[255];
int route[1000][1000];
int main(){
    // freopen("out/ortool_out1","r",stdin);
    // freopen("out/out1","w",stdout);
    double ans = 0.;
    scanf("%s",s);
    scanf("%lf",&ans);
    // printf("%lf\n",ans);
    int index = 0;
    while (true){
        scanf("%s",s);
        if (strcmp(s,"Route") == 0){
            scanf("%s",s);scanf("%s",s);scanf("%s",s);
            int x;
            while (true){
                scanf("%d",&x);
                route[index][++route[index][0]] = x;
                scanf("%s",s);
                scanf("%s",s);
                if (x==0&&route[index][0]!=1)break;
            }
            scanf("%s",s);
            scanf("%s",s);
            scanf("%s",s);
            scanf("%s",s);
            scanf("%s",s);
            scanf("%s",s);
            scanf("%s",s);
            scanf("%s",s);
            scanf("%s",s);
        }else break;

        index++;
    }
    printf("%d\n",index);
    for (int i=0;i<index;i++){
        printf("%d ",route[i][0]-2);
        for (int j = 2;j<route[i][0];j++)
            printf("%d ",route[i][j]);puts("");
    }
}