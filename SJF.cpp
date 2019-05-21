#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct PCB_type
{
    int ID;              //进程ID
    int Arrive_Time;     //到达时间
    int Finish_Time;     //完成时间
    int Need_Time;       //剩余所需时间
    int Run_Time;        //需要运行的时间
    int Over_Time = 0;   //轮转时间
    int Wait_Time;       //等待时间
    float Equ_over_time; //带权周转时间
    int Pri;             //优先级
};

class PCB
{
private:
    int Time = 0;                 //系统当前时间
    queue<struct PCB_type> Ready; //就绪队列
    stack<struct PCB_type> Wait;  //等待队列
    queue<struct PCB_type> End;   //结束队列
    PCB_type Node[10];            //保存刚输入进程的缓冲空间

public:
    void Read_File(); //将文件中内容读入程序
    void Run_PCB();   //按时间片算法运行进程并记录完成及周转时间
    void End_PCB();   //结束进程并输出时间信息
};

void PCB::Read_File()
{
    int Mark;
    int n;
    string Str;
    ifstream File;
    int i = 0;
    File.open("F:\\Programming\\c++ Workspace\\OS\\job.txt", ios::in);
    if (File.fail())
    {
        cout << "打开文件失败" << endl;
        exit(1);
    }

    getline(File, Str);
    while (!File.eof())
    {
        File >> Mark;
        Node[i].ID = Mark;
        File >> Mark;
        Node[i].Arrive_Time = Mark;
        File >> Mark;
        Node[i].Run_Time = Mark;
        Node[i].Need_Time = Mark;
        File >> Mark;
        Node[i].Pri = Mark;
        i += 1;
    }
    File.close();
    n = i + 1;
    //通过冒泡排序将进程按到达时间顺序排列
    PCB_type middle;
    for (i = 0; i < n; i++)
    {
        for (int i1 = i; i1 < n; i1++)
        {
            if (Node[i].Arrive_Time > Node[i1].Arrive_Time)
            {
                middle = Node[i];
                Node[i] = Node[i1];
                Node[i1] = middle;
            }
        }
    }
    for (i = n - 2; i >= 0; i--)
    {
        Wait.push(Node[i]);     //将进程输入等待队列
    }
}

void PCB::Run_PCB()
{
    PCB_type pcb;
    cout << "SJF:" << endl;
    Time = Wait.top().Arrive_Time; //当前时间作为第一个到达时间
    while (!Ready.empty() || !Wait.empty())
    { //当到达，依次进入就绪队列
        while (!Wait.empty() && Time >= Wait.top().Arrive_Time)
        {
            Ready.push(Wait.top());
            Wait.pop();
        }

        //当没有进程到达且排队队伍非空时，时间直接跳转到排队队伍第一个进程的到达时间

        if (Ready.empty())
        {
            Time = Wait.top().Arrive_Time;
            pcb = Wait.top();
            Wait.pop();
        }
        else
        {
            pcb = Ready.front();
            Ready.pop();
        }
            
        while(!Ready.empty()){
            if(pcb.Run_Time > Ready.front().Run_Time)
                {
                    Wait.push(pcb);
                    pcb = Ready.front();
                    Ready.pop();
                }
                else{
                    Wait.push(Ready.front());
                    Ready.pop();
                }
        }
        
        Time += pcb.Run_Time;
        pcb.Finish_Time = Time;
        pcb.Over_Time = Time - pcb.Arrive_Time;
        pcb.Wait_Time = pcb.Over_Time - pcb.Run_Time;
        pcb.Equ_over_time = float(pcb.Over_Time) / float(pcb.Run_Time);
        cout << "执行完的作业是：" << pcb.ID
             << "号作业，等待时间为" << pcb.Wait_Time
             << " 周转时间为" << pcb.Over_Time
             << " 带权周转时间为 " << pcb.Equ_over_time << endl;
        End.push(pcb);
    }
}

void PCB::End_PCB()
{
    float wait_time = 0, over_time = 0, equ_over = 0;
    int n = End.size();
    int i;
    for (i = 0; i < n; i++){ 
        //计算等待时间，周转时间，平均周转时间
        wait_time += End.front().Wait_Time;
        over_time += End.front().Over_Time;
        equ_over += End.front().Equ_over_time;
        End.pop();
    }
    wait_time /= n;
    over_time /= n;
    equ_over /= n;
    cout << "平均等待时间为：" << wait_time << endl
         << "平均周转时间为：" << over_time << endl
         << "平均带权周转时间为：" << equ_over << endl;
}

int main()
{
    PCB pcb;
    pcb.Read_File();
    pcb.Run_PCB();
    pcb.End_PCB();
    return 0;
}
