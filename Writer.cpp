#include <windows.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;

# define sleep(n) Sleep(n*1000)
struct ThreadInfo{
    int ID;        //�߳�ID
    char type;      //���ݽ�ɫ���߻�д��
    double delay;   //�߳��ӳ�
    double persist; //��д����ʱ��
};

int ReadCount = 0;

HANDLE Rmutex;              //���߻�����
HANDLE Wmutex;              //д�߻�����
HANDLE RWmutex;             //��������

void ReaderThread(void *p){
    DWORD r_delay;
    DWORD r_persist;
    int r_id;
    r_delay = ((ThreadInfo *)(p))->delay;
    r_persist = ((ThreadInfo *)(p))->persist;
    r_id = ((ThreadInfo *)(p))->ID;
    sleep(r_delay);
    //������Դ
    printf("Reader thread %d sents the reading require !\n",r_id); 
    WaitForSingleObject(Wmutex, -1);
    WaitForSingleObject(Rmutex, -1);
    if(ReadCount == 0){
        WaitForSingleObject(RWmutex, -1);
    }
    ReadCount++;
    ReleaseMutex(Rmutex);
    ReleaseMutex(Wmutex);
    //���ж�����
    printf("Reader thread %d begins to read file !\n",r_id); 
    sleep(r_persist);
    //���н���������
    printf("Reader thread %d finished reading file !\n", r_id); 
    WaitForSingleObject(Rmutex, -1);
    ReadCount--;
    if(ReadCount == 0){
        ReleaseMutex(RWmutex);
    }
    ReleaseMutex(Rmutex);
}

void WriterThread(void *p){
    DWORD w_delay;
    DWORD w_persist;
    int w_id;
    w_delay = ((ThreadInfo *)(p))->delay;
    w_persist = ((ThreadInfo *)(p))->persist;
    w_id = ((ThreadInfo *)(p))->ID;
    sleep(w_delay);
    printf("writer thread %d sends the writing require !\n",w_id);
    //�����ٽ���Դ
    WaitForSingleObject(Wmutex, -1);
    WaitForSingleObject(RWmutex, -1);
    //ִ��д����
    printf("writer thread %d begins to write file !\n",w_id);
    sleep(w_persist);
    //����д����
    printf("writer thread %d finished writing file !\n",w_id);
    ReleaseMutex(RWmutex);
    ReleaseMutex(Wmutex);
}

int main(){
    DWORD thread_Num = 0;       //��ʼ���߳���Ŀ
    DWORD thread_ID;            //�߳�ID

    HANDLE h_thread[20];        //�̶߳�������
    ThreadInfo thread_info[20];

    Rmutex = CreateMutex(NULL, FALSE, LPCTSTR("mutex_for_readcount"));
    Wmutex = CreateMutex(NULL, FALSE, LPCTSTR("mutex_for_readcount"));
    RWmutex = CreateMutex(NULL, FALSE, LPCTSTR("mutex_for_readcount"));

    ifstream inFile;
    inFile.open("G:\\Programming\\c++ Workspace\\OS\\WR.txt", ios::in);

    if(inFile.fail()){
        cout << "Error in open file!" << endl;
        exit(1); 
    }

    while(inFile){
        inFile >> thread_info[thread_Num].ID;
        inFile >> thread_info[thread_Num].type;
        inFile >> thread_info[thread_Num].delay;
        inFile >> thread_info[thread_Num].persist;
        inFile.get();
        thread_Num++;
    }

    int i = 0;
    for (i = 0; i < thread_Num; i++){
        if(thread_info[i].type == 'R'){
            h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(ReaderThread), &thread_info[i], 0, &thread_ID);
        }
        else{
            h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(WriterThread), &thread_info[i], 0, &thread_ID);
        }
    }

    DWORD wait_for_all = WaitForMultipleObjects(thread_Num, h_thread, true, -1);
    cout << "All Finish!" << endl;
    _getch();
    return 0; 
}