#include <conio.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;
#define sleep(n) Sleep(n * 1000)

HANDLE hMutex[5];     //五只餐具
HANDLE Sem;           //避免死锁，定义信号量令最多4个哲学家能够申请餐具

struct ThreadInfo{
    int ID;             //线程ID
    char role;          //线程角色
    int delay;          //线程延误时间
    int persist;        //线程需要运行的时间
};

void Phio(void *p)
{
    DWORD m_delay;
    DWORD m_persist;
    int m_id;

    m_delay = ((ThreadInfo *)(p))->delay;
    m_persist = ((ThreadInfo *)(p))->persist;
    m_id = ((ThreadInfo *)(p))->ID;
    sleep(m_delay);
    printf("Philosophist %d wants to eat !!! \n", m_id);
    //首先判断信号量是否阻塞
    WaitForSingleObject(Sem, -1);
    //申请左右的餐具
    WaitForSingleObject(hMutex[m_id], -1);
    WaitForSingleObject(hMutex[(m_id + 1) % 5], -1);
    //开始进餐
    printf("Philosophist %d is easting !!! \n", m_id);
    sleep(m_persist);
    printf("Philosophist %d finished eating !!! \n", m_id);
    //结束用餐
    ReleaseMutex(hMutex[m_id]);
    ReleaseMutex(hMutex[(m_id + 1) % 5]);
    ReleaseSemaphore(Sem, 1, NULL);
}

int main(){
    DWORD n_thread = 0;             //线程数目
    DWORD thread_ID;                //线程ID
    HANDLE h_thread[10];            //线程对象数组
    ThreadInfo thread_info[10];     //线程信息
    
    int i = 0;
    for (i = 0; i < 5; i++)
        hMutex[i] = CreateMutex(NULL, FALSE, LPCTSTR("mutex_for_readcount"));
    //读文件
    ifstream inFile;
    inFile.open("F:\\Programming\\c++ Workspace\\OS\\test3.txt", ios::in);
    if(!inFile){
        cout << "Error in open file" << endl;
        exit(1);
    }
    while (inFile){
        inFile >> thread_info[n_thread].ID;
        inFile >> thread_info[n_thread].role;
        inFile >> thread_info[n_thread].delay;
        inFile >> thread_info[n_thread].persist;
        n_thread++;
    }
    // 创建线程
    for (i = 0; i < n_thread; i++){
        h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Phio), &thread_info[i], 0, &thread_ID);
    }
    //初始化信号量
    Sem = CreateSemaphore(NULL, n_thread - 1, n_thread - 1, NULL);
    DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, true, -1);
    cout << "All Finished !!!" << endl;
    _getch();
    return 0;
}
