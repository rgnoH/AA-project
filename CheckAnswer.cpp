#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
double weight[maxn];
double dist[maxn][maxn];
int n,c;double w;
int myc[maxn][maxn];
void Error(int x){
    printf("error : %d\n",x);
    exit(0);
}
int vis[maxn];
int main(int argc,char*argv[]){
    FILE *fp;
    // cerr<<argv[1]<<endl;
    fp = fopen(argv[1],"r");
    fscanf(fp,"%d%d%lf",&n,&c,&w);
    for (int i=0;i<=n;i++)
        for (int j= 0;j<=n;j++)
            fscanf(fp,"%lf",&dist[i][j]);
    for (int i=0;i<=n;i++)fscanf(fp,"%lf",&weight[i]);
    fclose(fp);
    fp = fopen(argv[2],"r");
    // freopen("ans","r",stdin);
    int tc=0;
    fscanf(fp,"%d",&tc);
    if (tc>c)Error(__LINE__);
    double ansl = 0;
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=tc;i++){
        fscanf(fp,"%d",&myc[i][0]);
        double myw = 0.;
        for (int j=1;j<=myc[i][0];j++){
            fscanf(fp,"%d",&myc[i][j]);
            vis[myc[i][j]]++;
            myw+=weight[myc[i][j]];
            if (j==1)ansl += dist[0][myc[i][j]];
            else ansl += dist[myc[i][j-1]][myc[i][j]];
            if (j==myc[i][0])ansl+=dist[myc[i][j]][0];
        }
        if (myw>w)Error(__LINE__);
    }
    for (int i = 1;i<=n;i++)if (vis[i]!=1)Error(i);
    printf("%lf\n",ansl);
}