#include<bits/stdc++.h>
#include<random>
using namespace std;
const int MAXCLIENT = 1005;
const int MAXCAR = 105;
const int MAXPOPULATION = 3005;
const int INF = 1000000000;
random_device rd;
default_random_engine eng(rd());
int RandomInt(int l,int r){

    uniform_int_distribution<int> RI(l, r);
    return RI(eng);
}
double RandomDouble(){
    uniform_real_distribution<double> RD(0,1);
    return RD(eng);
}
void Error(int line){
    printf("error in line (%d)\n",line);
    exit(0);
    return;
}

class CarInformation{
    public:
    double MaxWeight,MaxLength;
    void Init(double _MaxWeight,double _MaxLength){
        MaxWeight = _MaxWeight;
        MaxLength = _MaxLength;
    }
    void PrintInformation(){
        printf("%lf %lf\n",MaxWeight,MaxLength);
    }
};
class ChromosomeInformation{
    public:
    int Chromosome[MAXCLIENT];
    int DividePoint[MAXCAR];
    double Fitness,Probability;
    // int GenerationNum;//出现代数
    void RandomGeneration(int test=0);
    void GreedGeneration(int test=0);
    void PrintInformation();
    void CalculatFitness();
    void Fitnesswork(double f[],double g[],int I[],double s[], double sw[], int l,int r,int fl,int fr);
};
class ParameterInformation{
    public:
    int PopulationScale,TotalTime;
    double CrossRate;
    double MutationRate;
    void Init(){
        PopulationScale = 500;
        TotalTime = 1000;
        CrossRate = 0.9;
        MutationRate = 0.05;
    }
};
            FILE * fp;
namespace VehicleRoutingProblem{
    int CarNumber,ClientNumber,CurrentTime;
    ChromosomeInformation BestChromosome;
    double DistanceClient[MAXCLIENT][MAXCLIENT];
    double WeightClient[MAXCLIENT];
    ChromosomeInformation OldGeneration[MAXPOPULATION],NewGeneration[MAXPOPULATION];
    ParameterInformation MyParameter;
    CarInformation Car;
    void InitData(){

        // freopen("data3","r",stdin);
        // fp = fopen ("file.txt", "w");
        int N,C;double W;
        scanf("%d%d%lf",&N,&C,&W);
        ClientNumber = N;
        CarNumber = C;
        MyParameter.Init();
        double x[30],y[30];
        Car.Init(W,10000.);
        /*
        double x0=0.,y0=0.;
        for (int i = 0 ; i<= ClientNumber; i++)
            for (int j = 0; j <= ClientNumber; j++){
                x0 = x[i]-x[j],y0 = y[i] - y[j];
                DistanceClient[i][j] = sqrt(x0*x0+y0*y0);
            }
        */
       
        for (int i = 0 ; i<= ClientNumber; i++)
            for (int j = 0; j <= ClientNumber; j++)
                scanf("%lf",&DistanceClient[i][j]);
        for (int i=0;i<=ClientNumber;i++)
            scanf("%lf",&WeightClient[i]);
        /*
        printf("Code in InitData\n");
        for (int i = 0; i<= ClientNumber; i++){
            for (int j = 0;j<=ClientNumber;j++)
                printf("%lf ",DistanceClient[i][j]);
            puts("");
        }
        puts("");
        printf("CarInformation: %lf %lf\n",Car.MaxLength,Car.MaxWeight);
        printf("End InitData\n");
        */
    }
    void CountRate(){
        double SumFitness = 0.;
        double MinFitness = 0.;
        /*for (int k =0;k<MyParameter.PopulationScale;k++)
            MinFitness = min(MinFitness,OldGeneration[k].Fitness);
        MinFitness -= 1.0 / INF;
        */
        for (int k=0;k<MyParameter.PopulationScale;k++)
            SumFitness += (OldGeneration[k].Fitness - MinFitness);
        OldGeneration[0].Probability = (OldGeneration[0].Fitness - MinFitness) / SumFitness;
        for (int k=0;k<MyParameter.PopulationScale;k++)
            OldGeneration[k].Probability = OldGeneration[k-1].Probability + (OldGeneration[k].Fitness - MinFitness) / SumFitness;
        /*
        printf("(%lf,%lf) ",OldGeneration[0].Probability,OldGeneration[0].Fitness);
        for (int k=1;k<MyParameter.PopulationScale;k++)
            printf("(%lf,%lf) ",OldGeneration[k].Probability-OldGeneration[k-1].Probability,OldGeneration[k].Fitness);
        puts("");*/
    }
    void swap(int&x,int&y){
        int tmp = x; x=y; y=tmp;
    }
    void ClimbMountain(ChromosomeInformation&Best){
        static const double Rate = 0.1;
        int&CN = VehicleRoutingProblem::ClientNumber;
        int l = RandomInt(1,CN), r = RandomInt(1,CN);
        while (l==r) r = RandomInt(1,CN);
        double OldFitness = Best.Fitness;
        swap(Best.Chromosome[l],Best.Chromosome[r]);
        Best.CalculatFitness();
        double NewFitness = Best.Fitness;
        if (OldFitness<=NewFitness){
            // cerr<<"find"<<endl;
            ClimbMountain(Best);
        }
        else{
            swap(Best.Chromosome[l],Best.Chromosome[r]);
            Best.CalculatFitness();
            if (RandomDouble() > Rate)
                ClimbMountain(Best);
        }
    }
    void InitPopulation(){
        for (int k = 0; k < MyParameter.PopulationScale; k++){
            OldGeneration[k].GreedGeneration();
            while (OldGeneration[k].Fitness <= 1. / INF)
                OldGeneration[k].GreedGeneration();
            ClimbMountain(OldGeneration[k]);
        }
        CountRate();
    }
    void UpdateBestChromosome(){
        for (int k = 0; k < MyParameter.PopulationScale; k++){
            if (BestChromosome.Fitness < OldGeneration[k].Fitness)
                BestChromosome = OldGeneration[k];
        }
        ClimbMountain(BestChromosome);
        NewGeneration[0] = BestChromosome;
    }
    void Mutation(int Index){
        int ran1,ran2;
        ran1 = RandomInt(1,ClientNumber);
        ran2 = RandomInt(1,ClientNumber);
        while (ran1 == ran2)
            ran2 = RandomInt(1,ClientNumber);
        swap(NewGeneration[Index].Chromosome[ran1],
             NewGeneration[Index].Chromosome[ran2]);
    }
    int Select(){
        // for (int k=0;k<MyParameter.PopulationScale;k++)
        //     printf("%lf ",OldGeneration[k].Probability);puts("");
        double RD = RandomDouble();
        for (int k=0; k < MyParameter.PopulationScale; k++){
            if (RD <= OldGeneration[k].Probability){
                return k;
            }
        }
        Error(__LINE__);exit(0);
    }
    bool VisitCrossor[MAXCLIENT];
    ChromosomeInformation Crossover(){
        int ran1 = Select();
        int ran2 = Select();
        while (ran1 == ran2)
            ran2 = Select();
        // OldGeneration[ran1].PrintInformation();
        // OldGeneration[ran2].PrintInformation();
        int x = RandomInt(1,ClientNumber),y = RandomInt(1,ClientNumber);
        if (x>y)swap(x,y);
        ChromosomeInformation Result1,Result2;
        memset(VisitCrossor,0,sizeof(VisitCrossor));
        for (int i=x;i<=y;i++){
            Result1.Chromosome[i] = OldGeneration[ran1].Chromosome[i];
            VisitCrossor[Result1.Chromosome[i]]=true;
        }
        int _ = y;
        for (int i=y+1;i<=ClientNumber;i++){
            int temp = OldGeneration[ran2].Chromosome[i];
            if (!VisitCrossor[temp]){
                Result1.Chromosome[_=_%ClientNumber+1]=temp;
                VisitCrossor[temp]=true;
            }
        }
        for (int i=1;i<=y;i++){
            int temp = OldGeneration[ran2].Chromosome[i];
            if (!VisitCrossor[temp]){
                Result1.Chromosome[_=_%ClientNumber+1]=temp;
                VisitCrossor[temp]=true;
            }
        }
        Result1.CalculatFitness();

        memset(VisitCrossor,0,sizeof(VisitCrossor));
        for (int i=x;i<=y;i++){
            Result2.Chromosome[i] = OldGeneration[ran2].Chromosome[i];
            VisitCrossor[Result2.Chromosome[i]]=true;
        }
        _ = y;
        for (int i=y+1;i<=ClientNumber;i++){
            int temp = OldGeneration[ran1].Chromosome[i];
            if (!VisitCrossor[temp]){
                Result2.Chromosome[_=_%ClientNumber+1]=temp;
                VisitCrossor[temp]=true;
            }
        }
        for (int i=1;i<=y;i++){
            int temp = OldGeneration[ran1].Chromosome[i];
            if (!VisitCrossor[temp]){
                Result2.Chromosome[_=_%ClientNumber+1]=temp;
                VisitCrossor[temp]=true;
            }
        }
        Result2.CalculatFitness();
        // Result.PrintInformation();
        // return Result;
        // cerr<<Result1.Fitness <<" "<< Result2.Fitness<<endl;
        // ClimbMountain(Result1);
        // ClimbMountain(Result2);
        if (Result1.Fitness < Result2.Fitness)return Result2;
        else return Result1;
        // return Result1;
    }
    int CompeteSelete(){
        int k1 = Select(),k2 = Select();
        if (OldGeneration[k1].Fitness > OldGeneration[k2].Fitness)
            return k1;else return k2;
    }
    int Restart = 0;
    void Evolution(int CurrentTime,int TotalTime){
        static bool Vis[MAXPOPULATION];
        for (int k=1;k<MyParameter.PopulationScale;k++){
            NewGeneration[k] = Crossover();
        }
        int count = 0;
        for (int k = 0;k<MyParameter.PopulationScale;k++)
            Vis[k] = false;
        for (int k=1 ; k<MyParameter.PopulationScale; k++) if (RandomDouble() > (0.8 + 0.1 * CurrentTime / TotalTime) * NewGeneration[k].Fitness / BestChromosome.Fitness){
            count++;
            int k_ = CompeteSelete();
            while (Vis[k_])k_ = CompeteSelete();
            Vis[k_] = true;
            if (NewGeneration[k].Fitness < OldGeneration[k_].Fitness)
                NewGeneration[k] = OldGeneration[k_];//,ClimbMountain(NewGeneration[k]);
        }
        //cerr<< (double)count/MyParameter.PopulationScale<<endl;
        // for (int k= 0;k<MyParameter.PopulationScale;k++)
        //    printf("%lf ",NewGeneration[k].Fitness);puts("");
        //if (CurrentTime+1 == TotalTime)

        for (int k=1 ; k<MyParameter.PopulationScale; k++){
            if (RandomDouble()<0.1){
                // Mutation(k);
                ClimbMountain(NewGeneration[k]);
            }
        }
        double T = INF; int c = 0;
        for (int k = 1;k < MyParameter.PopulationScale;k++)
            if (T == NewGeneration[k].Fitness)c++;else{
                if (c == 0) T = NewGeneration[k].Fitness,c++;
                else c--;
            }
        c = 0;
        for (int k = 1;k<MyParameter.PopulationScale;k++)
            if (NewGeneration[k].Fitness == T) c++;
        //printf("Same Fitness : %lf\n",(double)c / MyParameter.PopulationScale);
        
        if ((double)c / MyParameter.PopulationScale > 0.01){
            Restart++;
            for (int k = 1; k < MyParameter.PopulationScale; k++){
            NewGeneration[k].GreedGeneration();
            while (NewGeneration[k].Fitness <= 1. / INF)
                NewGeneration[k].GreedGeneration();
        }
            /*{
                for (int k = 0 ;k<MyParameter.PopulationScale;k++)
                NewGeneration[k].PrintInformation();
            }*/
        }
       for (int k = 0; k<MyParameter.PopulationScale;k++)
            OldGeneration[k] = NewGeneration[k];
        CountRate();
        UpdateBestChromosome();
        // exit(0);
        /*
        puts("----------------------------------------------");
        for (int k = 0; k<MyParameter.PopulationScale;k++)
            OldGeneration[k].PrintInformation();
        puts("----------------------------------------------");

        for (int k = 0; k<MyParameter.PopulationScale;k++)
            printf("%.2f ",OldGeneration[k].Probability);
        puts("");
        for (int k = 0; k<MyParameter.PopulationScale;k++)
            printf("%.6f ",OldGeneration[k].Fitness);
        puts("");
        */
    }
    void BestResult(){
        InitData();
        InitPopulation();
        UpdateBestChromosome();
        for (CurrentTime = 0;CurrentTime<MyParameter.TotalTime;CurrentTime++){
            Evolution(CurrentTime,MyParameter.TotalTime);
            // cerr<<1./BestChromosome.Fitness<<endl;
            // BestChromosome.PrintInformation();puts("");
            // fprintf(fp, "%lf\n", BestChromosome.Fitness);
        }
        // printf("\nBestChromosome:\n");
        BestChromosome.PrintInformation();
       //printf("Restart: %d\n",Restart);
        /*
        ChromosomeInformation Temp;
        Temp.RandomGeneration(); for (int i = 0;i<100;i++)Temp.RandomGeneration(1);
        Temp.GreedGeneration(); for (int i = 0;i<100;i++)Temp.GreedGeneration(1);
        */
    }
}

int main(){
    VehicleRoutingProblem::BestResult();
}


void ChromosomeInformation::RandomGeneration(int test){
    static int temp[MAXCLIENT];
    int&CN = VehicleRoutingProblem::ClientNumber;
    if (test){
        for (int i=1;i<=CN;i++)temp[i]=Chromosome[i];
    }
    for (int i = 1; i<=CN; i++){
        Chromosome[i] = i;
    }
    random_shuffle(Chromosome + 1 ,Chromosome + CN + 1);
    CalculatFitness();
    if (test){
        int *b = VehicleRoutingProblem::BestChromosome.Chromosome;
        static int count2 = 0;
        static int count = 0;
        for (int i = 1;i<CN;i++)
            for (int j = 1;j<CN;j++)
                if (Chromosome[i] == b[j]&&Chromosome[i+1]==b[j+1])count++;
        for (int i = 1;i<CN;i++)
            for (int j = 1;j<CN;j++)
                if (Chromosome[i] == temp[j]&&Chromosome[i+1]==temp[j+1])count2++;
        printf("Random:%d %d\n",count,count2);
    }
}
void ChromosomeInformation::GreedGeneration(int test){
    static int temp[MAXCLIENT];
    int&CN = VehicleRoutingProblem::ClientNumber;
    if (test){
        for (int i=1;i<=CN;i++)temp[i]=Chromosome[i];
    }
    int&CR = VehicleRoutingProblem::CarNumber;
    static int Pre[MAXCLIENT];
    static int CarLast[MAXCAR];
    static bool VisitClient[MAXCLIENT];
    static double MinDist[MAXCLIENT];
    for (int i = 1; i<=CN; i++) Pre[i]=0,VisitClient[i]=0,MinDist[i] = INF;
    for (int i = 0; i<CR; i++){
        int x = RandomInt(1,CN);
        while (VisitClient[x])x = RandomInt(1,CN);
        VisitClient[x] = true;
        CarLast[i] = x;
        for (int k = 1;k<=CN;k++)
            if (!VisitClient[k])
                MinDist[k] = min(MinDist[k], VehicleRoutingProblem::DistanceClient[x][k]);
    }
    for (int i = 0; i < CN-CR; i++){
        int now = 0;double dis = INF;
        for (int k = 1;k<=CN;k++)
            if (!VisitClient[k]&&MinDist[k]< dis)
                dis = MinDist[k],now = k;
        VisitClient[now]=true;
        for (int k = 0;k<CR;k++)
            if (MinDist[now] == VehicleRoutingProblem::DistanceClient[CarLast[k]][now]){
                Pre[now] = CarLast[k],CarLast[k]=now;
                break;
            }
        for (int k = 1;k<=CN;k++)
            if (!VisitClient[k]&&VehicleRoutingProblem::DistanceClient[Pre[now]][k] == MinDist[k]){
                MinDist[k] = INF;
                for (int j = 0; j< CR; j++)
                    MinDist[k] = min(MinDist[k],VehicleRoutingProblem::DistanceClient[CarLast[j]][k]);
            }
        for (int k = 1;k<=CN;k++)
            if (!VisitClient[k]&&VehicleRoutingProblem::DistanceClient[now][k]<MinDist[k])
                MinDist[k]=VehicleRoutingProblem::DistanceClient[now][k];
        
    }
    int End = CN;
    for (int i = 0; i<CR;i++)
        for (int k = CarLast[i] ; k; k =Pre[k])
            Chromosome[End--] = k;
    CalculatFitness();

    if (test){
        int *b = VehicleRoutingProblem::BestChromosome.Chromosome;
        static int count = 0,count2=0;
        for (int i = 1;i<CN;i++)
            for (int j = 1;j<CN;j++)
                if (Chromosome[i] == b[j]&&Chromosome[i+1]==b[j+1])count++;
        for (int i = 1;i<CN;i++)
            for (int j = 1;j<CN;j++)
                if (Chromosome[i] == temp[j]&&Chromosome[i+1]==temp[j+1])count2++;
        printf("Greed:%d %d\n",count,count2);
    }
    // PrintInformation();
    // exit(0);
}
void ChromosomeInformation::PrintInformation(){
    int&CN = VehicleRoutingProblem::ClientNumber;
    // printf("Chromosome:");
    // for (int i=1;i<=CN;i++)
    //     printf("%d ",Chromosome[i]);puts("");
    // printf("DividePoint:");
    // for (int i=1;i<=CN;i++)
    //    printf("%d ",DividePoint[i]);puts("");
    //printf("Car:\n");
    int ans = 0;
    for (int i = 1;i<=CN;i++)if (DividePoint[i])ans++;else break;
    printf("%d\n",ans);
    for (int i=1;i<=CN;i++){
        int L = DividePoint[i], R = DividePoint[i+1];
        if (R==0){
            printf("%d ",CN-L+1);
            for (int j=L;j<=CN;j++)printf("%d ",Chromosome[j]);
            puts("");break;
        }
        printf("%d ",R-L);
        for (int j = L;j< R;j++)printf("%d ",Chromosome[j]);
        puts("");
    }
    // printf("Fitness : %.10f\n",Fitness);
    
    // printf("Probability : %lf\n",Probability);
    // printf("GenerationNum : %d\n",GenerationNum);
}

double min(double x,double y){
    return (x<y)?x:y;
}
void ChromosomeInformation::Fitnesswork(double f[],double g[],int I[],double s[], double sw[],int l,int r,int fl,int fr){

    if (l>r)return;
    // printf("%d %d %d %d\n",l,r,fl,fr);
    int mid = (l+r)>>1;
    double (*Dist)[MAXCLIENT] = VehicleRoutingProblem::DistanceClient;
    CarInformation& CarI = VehicleRoutingProblem::Car;
    for (int i = fl; i<=fr; i++)
        if (i<mid){
            //printf("%lf %lf %lf\n",sw[mid],sw[i],CarI.MaxWeight);
            if (sw[mid] - sw[i] <=CarI.MaxWeight){
                double v = g[i] + (s[mid] - s[i+1]) + Dist[0][Chromosome[i+1]] + Dist[Chromosome[mid]][0];
                //printf("%lf %lf\n",v,f[mid]);
                if (v<f[mid])f[mid]=v,I[mid]=i+1;
            }
        }else break;
    //exit(0);
    if (I[mid]==-1){
        Fitnesswork(f,g,I,s,sw,l,mid-1,fl,min(fr,mid-2));
        Fitnesswork(f,g,I,s,sw,mid+1,r,max(fl,mid),fr);
    }
    else{
        Fitnesswork(f,g,I,s,sw,l,mid-1,fl,I[mid]);
        Fitnesswork(f,g,I,s,sw,mid+1,r,I[mid],fr);
    }
}
void ChromosomeInformation::CalculatFitness(){
    static double fCF[MAXCLIENT][MAXCAR];
    static int fPR[MAXCLIENT][MAXCAR];
    static double sum[MAXCLIENT];
    static double wsum[MAXCLIENT];
    int&CliN = VehicleRoutingProblem::ClientNumber;
    int&CarN = VehicleRoutingProblem::CarNumber;
    double (*Dist)[MAXCLIENT] = VehicleRoutingProblem::DistanceClient;
    CarInformation& CarI = VehicleRoutingProblem::Car;
    double* W = VehicleRoutingProblem::WeightClient;
    
    // for (int i = 1;i<=CliN;i++)printf("%d ",Chromosome[i]);puts("");

    for (int i=0;i<=CliN;i++)
        for (int j=0;j<=CarN;j++)
            fCF[i][j] = INF,fPR[i][j] = -1;
    fCF[0][0] = 0;
    /*
    sum[1]=0;
    for (int i=2;i<=CliN;i++)
        sum[i]=sum[i-1]+Dist[Chromosome[i-1]][Chromosome[i]];
    wsum[0]=0;
    for (int i=1;i<=CliN;i++)
        wsum[i] = wsum[i-1] + W[i];
    */
    
    for (int i= 1; i<= CliN; i++){
        int x = Chromosome[i];
        if (Dist[x][0]+Dist[0][x] <= CarI.MaxLength && W[x] <= CarI.MaxWeight)
            for (int j = 1;j<=CarN;j++) fCF[i][j] = fCF[i-1][j-1] + Dist[x][0] + Dist[0][x] , fPR[i][j] = i;
        double SL = Dist[x][0],SW = W[x];
        for (int k = i-1; k >0; k--){
            int y = Chromosome[k];
            SL += Dist[y][x];
            SW += W[y];
            x = y;
            if (SW <= CarI.MaxWeight){
                if (SL + Dist[0][y] <= CarI.MaxLength) 
                    for (int j = 1;j<=CarN; j++){
                        if (fCF[i][j] > fCF[k-1][j-1] + SL + Dist[0][y])
                            fCF[i][j] = fCF[k-1][j-1] + SL + Dist[0][y],
                            fPR[i][j] = k;
                        // fCF[i][j] = min(fCF[i][j], fCF[k-1][j-1] + SL + Dist[0][y]);
                    }
            }
            else break;
        }
        // for (int j = 1;j<=CarN;j++)printf("%lf ",fCF[i][j]);puts("");
    }
    /*
    for (int i = 1;i<=CarN; i++){
        // printf("%d\n",i);
        Fitnesswork(fCF[i],fCF[i-1], fPR[i],sum, wsum,1,CliN,0,CliN-1);
    }*/
    double Res = INF; int CarIndex = 0, ChromosomeIndex = CliN;
    for (int j = 1;j<=CarN;j++)
        if (fCF[CliN][j] < Res)Res = fCF[CliN][CarIndex = j];
    memset(DividePoint,0,sizeof(DividePoint));
    // printf("%d %d\n",CarIndex,Res);
    while (CarIndex >= 0){
        // printf("%d %d\n",ChromosomeIndex,CarIndex);
        DividePoint[CarIndex] = fPR[ChromosomeIndex][CarIndex];
        ChromosomeIndex = fPR[ChromosomeIndex][CarIndex] - 1;
        CarIndex--;
    }
    Fitness = 1./ Res;
    // exit(0);
    // printf("Fitness %lf\n",Fitness);
}