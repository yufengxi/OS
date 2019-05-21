#include <conio.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <windows.h>
using namespace std;

#define sleep(n) Sleep(n * 1000)
struct ThreadInfo
{
    int ID;         //线程ID
    char type;      //扮演角色读者或写者
    double delay;   //线程延迟
    double persist; //读写持续时间
};

int ReadCount = 0;

HANDLE Mutex;  //读者互斥量
HANDLE Full;  //饱和信号量
HANDLE Empty; //空信号量

void ProducerThread(void *p)
{
    DWORD r_delay;
    DWORD r_persist;
    int r_id;
    r_delay = ((ThreadInfo *)(p))->delay;
    r_persist = ((ThreadInfo *)(p))->persist;
    r_id = ((ThreadInfo *)(p))->ID;
    sleep(r_delay);
    //申请资源
    printf("Producer thread %d sends the producing require !\n", r_id);
    //申请资源
    WaitForSingleObject(Empty, -1);
    WaitForSingleObject(Mutex, -1);
    //执行生产操作
    printf("Producer thread %d begins to produce !\n", r_id);
    sleep(r_persist);
    //结束生产操作
    printf("Producer thread %d finished producing !\n", r_id);
    ReleaseMutex(Mutex);
    ReleaseSemaphore(Full, 1, NULL);
}

void ConsumerThread(void *p)
{
    DWORD w_delay;
    DWORD w_persist;
    int w_id;
    w_delay = ((ThreadInfo *)(p))->delay;
    w_persist = ((ThreadInfo *)(p))->persist;
    w_id = ((ThreadInfo *)(p))->ID;
    sleep(w_delay);
    printf("Consumer thread %d sends the consuming require !\n", w_id);
    //申请临界资源
    WaitForSingleObject(Full, -1);
    WaitForSingleObject(Mutex, -1);
    //执行写操作
    printf("Consumer thread %d begins to consume !\n", w_id);
    sleep(w_persist);
    //结束写操作
    printf("Consumer thread %d finished consuming !\n", w_id);
    ReleaseMutex(Mutex);
    ReleaseSemaphore(Empty, 1, NULL);
}

int main()
{
    DWORD thread_Num = 0; //初始化线程数目
    DWORD thread_ID;      //线程ID

    HANDLE h_thread[20]; //线程对象数组
    ThreadInfo thread_info[20];

    Mutex = CreateMutex(NULL, FALSE, LPCTSTR("mutex_for_readcount"));
    Empty = CreateSemaphore(NULL, 5, 5, NULL);
    Full = CreateSemaphore(NULL, 0, 5, NULL);
    ifstream inFile;
    inFile.open("F:\\Programming\\c++ Workspace\\OS\\test2.txt", ios::in);

    if (inFile.fail())
    {
        cout << "Error in open file!" << endl;
        exit(1);
    }

    while (inFile)
    {
        inFile >> thread_info[thread_Num].ID;
        inFile >> thread_info[thread_Num].type;
        inFile >> thread_info[thread_Num].delay;
        inFile >> thread_info[thread_Num].persist;
        inFile.get();
        thread_Num++;
    }

    int i = 0;
    for (i = 0; i < thread_Num; i++)
    {
        if (thread_info[i].type == 'P')
        {
            h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ProducerThread), &thread_info[i], 0, &thread_ID);
        }
        else
        {
            h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ConsumerThread), &thread_info[i], 0, &thread_ID);
        }
    }

    DWORD wait_for_all = WaitForMultipleObjects(thread_Num, h_thread, true, -1);
    cout << "All Finish!" << endl;
    _getch();
    return 0;
}