#include<bits/stdc++.h>
using namespace std;
double x[1005],y[1005],w[1005],in[1005],ou[1005],ser[1005];
char s[1005];
double sqr2(double x,double y){
    return sqrt(x*x+y*y);
}
int N = 100,Car = 25;
int Data_type = 0;
int main(){
    freopen("data_input.txt","r",stdin);
    int number;double capacity;
    if (Data_type)cin.getline(s,N);
    if (Data_type)cin.getline(s,N);
    if (Data_type)cin.getline(s,N);
    if (Data_type)cin.getline(s,N);
    scanf("%d %d %lf",&number,&Car, &capacity);
    N=number;
    // printf("%d %d %lf\n",number,Car,capacity);
    if (Data_type)cin.getline(s,N);
    if (Data_type)cin.getline(s,N);
    if (Data_type)cin.getline(s,N);
    if (Data_type)cin.getline(s,N);
    int id;
    for (int i = 0;i<=N;i++){
        if (!Data_type){
            scanf("%lf%lf%lf",&x[i],&y[i],&w[i]);
        }
        else scanf("%d%lf%lf%lf%lf%lf%lf",&id,&x[i],&y[i],&w[i],&in[i],&ou[i],&ser[i]);
        // printf("%d %lf %lf %lf\n",i,x[i],y[i],ser[i]);
        //printf("%d %lf %lf %lf %lf %lf %lf\n",id,x[i],y[i],w[i],in[i],ou[i],ser[i]);
    }
    /*
    printf("[");
    for (int i = 0;i<=N;i++){
        if (i)printf(",");
        printf("[");
        for (int j=0;j<=N;j++){
            if (j)printf(",");
            printf("%.2f",sqr2(x[i]-x[j],y[i]-y[j]));
        }
        printf("]\n");

    }
    printf("]\n");
    printf("[");
    for (int i=0;i<=N;i++){
        if (i)printf(",");
        printf("%d", (int)w[i]);
    }
    printf("]\n");*/
    freopen("data7","w",stdout);
    printf("%d %d %lf\n",N,Car,capacity);
    for (int i = 0;i<=N;i++){
        for (int j=0;j<=N;j++){
            printf("%.2f ",sqr2(x[i]-x[j],y[i]-y[j]));
        }
        printf("\n");

    }
    for (int i=0;i<=N;i++){
        printf("%d ", (int)w[i]);
    }
    puts("\n");
}
