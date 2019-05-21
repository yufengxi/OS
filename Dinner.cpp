#include <conio.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;
#define sleep(n) Sleep(n * 1000)

HANDLE hMutex[5];     //��ֻ�;�
HANDLE Sem;           //���������������ź��������4����ѧ���ܹ�����;�

struct ThreadInfo{
    int ID;             //�߳�ID
    char role;          //�߳̽�ɫ
    int delay;          //�߳�����ʱ��
    int persist;        //�߳���Ҫ���е�ʱ��
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
    //�����ж��ź����Ƿ�����
    WaitForSingleObject(Sem, -1);
    //�������ҵĲ;�
    WaitForSingleObject(hMutex[m_id], -1);
    WaitForSingleObject(hMutex[(m_id + 1) % 5], -1);
    //��ʼ����
    printf("Philosophist %d is easting !!! \n", m_id);
    sleep(m_persist);
    printf("Philosophist %d finished eating !!! \n", m_id);
    //�����ò�
    ReleaseMutex(hMutex[m_id]);
    ReleaseMutex(hMutex[(m_id + 1) % 5]);
    ReleaseSemaphore(Sem, 1, NULL);
}

int main(){
    DWORD n_thread = 0;             //�߳���Ŀ
    DWORD thread_ID;                //�߳�ID
    HANDLE h_thread[10];            //�̶߳�������
    ThreadInfo thread_info[10];     //�߳���Ϣ
    
    int i = 0;
    for (i = 0; i < 5; i++)
        hMutex[i] = CreateMutex(NULL, FALSE, LPCTSTR("mutex_for_readcount"));
    //���ļ�
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
    // �����߳�
    for (i = 0; i < n_thread; i++){
        h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Phio), &thread_info[i], 0, &thread_ID);
    }
    //��ʼ���ź���
    Sem = CreateSemaphore(NULL, n_thread - 1, n_thread - 1, NULL);
    DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, true, -1);
    cout << "All Finished !!!" << endl;
    _getch();
    return 0;
}
