# include<iostream>
# include<fstream>
# include <queue>
# include <iomanip>
using namespace std;

struct PCB_type{
	int ID;        		//����ID
	int Arrive_Time;    //����ʱ��
	int Finish_Time;    //���ʱ��
	int Need_Time;		//ʣ������ʱ��
	int Run_Time;		//��Ҫ���е�ʱ��
	int Over_Time = 0;  //��תʱ��
	int Wait_Time;		//�ȴ�ʱ��
	float Equ_over_time;//��Ȩ��תʱ��
	int Pri;			//���ȼ�
};

class PCB{
private:
	int RR = 10;                         //ʱ��Ƭ����
	int Time = 0;             		//ϵͳ��ǰʱ��
	queue<struct PCB_type> Ready;   //��������
	queue<struct PCB_type> Wait;	//�ȴ�����
	queue<struct PCB_type> End;		//�����Ľ��̶���
	PCB_type Node[10];				//�����������̵Ļ���ռ�

  public:		
	void Read_File();				//���ļ������ݶ������
	void Run_PCB();					//��ʱ��Ƭ�㷨���н��̲���¼��ɼ���תʱ��
	void End_PCB();					//�������̲����ʱ����Ϣ
};

void PCB::Read_File(){
	int Mark;
	int n;
	string Str;
	ifstream File;
	int i = 0;
	File.open("F:\\Programming\\c++ Workspace\\OS\\job.txt", ios::in);
	if(File.fail()){
		cout << "���ļ�ʧ��" << endl;
		exit(1);
	}
		
	getline(File, Str);
	while(!File.eof()){
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
	//ͨ��ð�����򽫽��̰�����ʱ��˳������
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
	for (i = 0; i < n -1; i++)
	{
		Wait.push(Node[i]); //����������ȴ�����
	}
}

void PCB::Run_PCB(){
	PCB_type pcb;
	

	while(! Ready.empty() || ! Wait.empty()){
		
		//��������ν����������
		while (!Wait.empty() && Time >= Wait.front().Arrive_Time)
		{
			Ready.push(Wait.front());
			Wait.pop();
		}

		//��û�н��̵������ŶӶ���ǿ�ʱ��ʱ��ֱ����ת���ŶӶ����һ�����̵ĵ���ʱ��

		if(Ready.empty()){
			Time = Wait.front().Arrive_Time;
			Ready.push(Wait.front());
			Wait.pop();
		}

		pcb = Ready.front();
		Ready.pop();

		//���ݱȽ�ʱ��Ƭ�������������ʣ��ʱ�䣬�жϽ�������ʱ��
		if (pcb.Need_Time > RR)
		{
			pcb.Need_Time -= RR;
			Time += RR;
			cout << pcb.ID << " ����ҵִ���� " << RR <<endl;
			while (!Wait.empty() && Time >= Wait.front().Arrive_Time)
			{
				Ready.push(Wait.front());
				Wait.pop();
			}
			Ready.push(pcb);
		}
		else
		{
			Time += pcb.Need_Time;
			pcb.Finish_Time = Time;
			pcb.Over_Time = pcb.Finish_Time - pcb.Arrive_Time;
			pcb.Wait_Time = pcb.Over_Time - pcb.Run_Time;
			pcb.Equ_over_time = float(pcb.Over_Time) / float(pcb.Run_Time);
			cout << pcb.ID << " ����ҵִ���� " << pcb.Need_Time << endl;
			cout << "ִ�����������" << pcb.ID << " �ţ��ȴ�ʱ��Ϊ "
				 << pcb.Wait_Time << " ����תʱ��Ϊ " << pcb.Over_Time << " ��Ȩ��תʱ��Ϊ " << pcb.Equ_over_time << endl;
			End.push(pcb);
		}
	}
}

void PCB::End_PCB(){
	float wait_time = 0, over_time = 0, equ_over = 0;
	cout << "��ҵ��ִ���꣡" << endl;
	int n = End.size();
	int i;
	for (i = 0; i < n; i++){			
		//����ȴ�ʱ�䣬��תʱ�䣬ƽ����תʱ��
		wait_time += End.front().Wait_Time;
		over_time += End.front().Over_Time;
		equ_over += End.front().Equ_over_time;
		End.pop();
	}
	wait_time /= n;
	over_time /= n;
	equ_over /= n;
	cout << "ƽ���ȴ�ʱ��Ϊ��" << wait_time << endl
		 << "ƽ����תʱ��Ϊ��" << over_time << endl
		 << "ƽ����Ȩ��תʱ��Ϊ��" << equ_over << endl;
}


int main()
{
	PCB pcb;
	pcb.Read_File();
	pcb.Run_PCB();
	pcb.End_PCB();
	return 0;
}
