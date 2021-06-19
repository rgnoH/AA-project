#include<bits/stdc++.h>
#include<random>
#include <unistd.h>
#include<time.h>

 #include <chrono>
 #include <thread>

 using namespace std;
 using namespace std::chrono;
using namespace std;
random_device rd;
default_random_engine eng(rd());
void work(int x=1);
int main(int argc,char**argv){
    char run_code_1[] = "./ga_vrp < data/data1 > out/out1";
    char run_code_2[] = "./ga_vrp < data/data2 > out/out2";
    char run_code_3[] = "./ga_vrp < data/data3 > out/out3";
    char run_code_4[] = "./ga_vrp < data/data4 > out/out4";
    char run_code_5[] = "./ga_vrp < data/data5 > out/out5";
    char run_code_6[] = "./ga_vrp < data/data6 > out/out6";
    char run_code_7[] = "./ga_vrp < data/data7 > out/out7";
    char run_python_code_1[] = "python ortool.py < data/data1 > out/ortool_out1";
    char run_python_code_2[] = "python ortool.py < data/data2 > out/ortool_out2";
    char run_python_code_3[] = "python ortool.py < data/data3 > out/ortool_out3";
    char run_python_code_4[] = "python ortool.py < data/data4 > out/ortool_out4";
    char run_python_code_5[] = "python ortool.py < data/data5 > out/ortool_out5";
    char run_python_code_6[] = "python ortool.py < data/data6 > out/ortool_out6";
    char run_python_code_7[] = "python ortool.py < data/data7 > out/ortool_out7";
    char run_change_code_1[] = "./changeout < out/ortool_out1 > out/out1";
    char run_change_code_2[] = "./changeout < out/ortool_out2 > out/out2";
    char run_change_code_3[] = "./changeout < out/ortool_out3 > out/out3";
    char run_change_code_4[] = "./changeout < out/ortool_out4 > out/out4";
    char run_change_code_5[] = "./changeout < out/ortool_out5 > out/out5";
    char run_change_code_6[] = "./changeout < out/ortool_out6 > out/out6";
    char run_change_code_7[] = "./changeout < out/ortool_out7 > out/out7";
    char test_code_1[] = "./CheckAnswer data/data1 out/out1";
    char test_code_2[] = "./CheckAnswer data/data2 out/out2";
    char test_code_3[] = "./CheckAnswer data/data3 out/out3";
    char test_code_4[] = "./CheckAnswer data/data4 out/out4";
    char test_code_5[] = "./CheckAnswer data/data5 out/out5";
    char test_code_6[] = "./CheckAnswer data/data6 out/out6";
    char test_code_7[] = "./CheckAnswer data/data7 out/out7";

     auto start = high_resolution_clock::now();

    if (strcmp(argv[1],"Run") == 0){
        switch (argv[2][0]){
            case '0':
                system(run_code_1);
                system(run_code_2);
                system(run_code_3);
                system(run_code_4);
                system(run_code_5);
                system(run_code_6);
                system(run_code_7);
                break;
            case '1':
                system(run_code_1);
                break;
            case '2':
                system(run_code_2);
                break;
            case '3':
                system(run_code_3);
                break;
            case '4':
                system(run_code_4);
                break;
            case '5':
                system(run_code_5);
                break;
            case '6':
                system(run_code_6);
                break;
            case '7':
                system(run_code_7);
                break;
        }
    }
    else if (strcmp(argv[1],"Test") == 0){
        switch (argv[2][0]){
            case '0':
                system(test_code_1);
                system(test_code_2);
                system(test_code_3);
                system(test_code_4);
                system(test_code_5);
                system(test_code_6);
                system(test_code_7);
                break;
            case '1':
                system(test_code_1);
                break;
            case '2':
                system(test_code_2);
                break;
            case '3':
                system(test_code_3);
                break;
            case '4':
                system(test_code_4);
                break;
            case '5':
                system(test_code_5);
                break;
            case '6':
                system(test_code_6);
                break;
            case '7':
                system(test_code_7);
                break;
        }

    }
    else if (strcmp(argv[1],"Ortool")==0){
        switch (argv[2][0]){
            case '0':
                system(run_python_code_1);
                system(run_python_code_2);
                system(run_python_code_3);
                system(run_python_code_4);
                system(run_python_code_5);
                system(run_python_code_6);
                system(run_python_code_7);
                system(run_change_code_1);
                system(run_change_code_2);
                system(run_change_code_3);
                system(run_change_code_4);
                system(run_change_code_5);
                system(run_change_code_6);
                system(run_change_code_7);
                break;
            case '1':
                system(run_python_code_1);
                system(run_change_code_1);
                break;
            case '2':
                system(run_python_code_2);
                system(run_change_code_2);
                break;
            case '3':
                system(run_python_code_3);
                system(run_change_code_3);
                break;
            case '4':
                system(run_python_code_4);
                system(run_change_code_4);
                break;
            case '5':
                system(run_python_code_5);
                system(run_change_code_5);
                break;
            case '6':
                system(run_python_code_6);
                system(run_change_code_6);
                break;
            case '7':
                system(run_python_code_7);
                system(run_change_code_7);
                break;
        }

    }
    cout << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << "ms\n";

     return 0;
}