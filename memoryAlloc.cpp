//�ڴ����
//����2-6-2 memoryAlloc.cpp
#include <windows.h>
#include <stdio.h>

int main(int argc,  char* argv[])
{
	FILE* fp = fopen("result.txt","w+");//������ļ�
	MEMORYSTATUS Vmeminfo;//���Բ�ѯȫ���ڴ�״̬
	MEMORY_BASIC_INFORMATION inspectorinfo1;//���Բ�ѯ����ҳ���״̬
	int structsize = sizeof(MEMORY_BASIC_INFORMATION);
	LPVOID BASE_PTR = NULL;
	int stat = 0;
	GlobalMemoryStatus(&Vmeminfo);//��ѯû�з���֮ǰ������״̬
	//�����Ϣ
	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%ld(BYTES)\n",  Vmeminfo.dwTotalPhys);
	fprintf(fp,"���������ڴ棺%ld(BYTES)\n",  Vmeminfo.dwAvailPhys);
	fprintf(fp,"ҳ���ļ�������%ld(KBYTES)\n",  Vmeminfo.dwTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%ld(KBYTES)\n",  Vmeminfo.dwAvailPageFile/1024);
	fprintf(fp,"���ռ�������%ld(BYTES)\n",  Vmeminfo.dwTotalVirtual);
	fprintf(fp,"�������ռ�����%ld(BYTES)\n",  Vmeminfo.dwAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	BASE_PTR = VirtualAlloc(NULL, 1024*32, MEM_COMMIT, PAGE_READWRITE);/*�������ڴ�*/
	stat = VirtualQuery(BASE_PTR, &inspectorinfo1, structsize);/*��ѯVirtualAlloc֮��ĵ�ǰ����״̬״̬*/
	//�����Ϣ
	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n********************************\n");
	GlobalMemoryStatus(&Vmeminfo);//��ѯVirtualAlloc֮�������״̬
	//�����Ϣ
	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%ld(BYTES)\n",  Vmeminfo.dwTotalPhys);
	fprintf(fp,"���������ڴ棺%ld(BYTES)\n",  Vmeminfo.dwAvailPhys);
	fprintf(fp,"ҳ���ļ�������%ld(KBYTES)\n",  Vmeminfo.dwTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%ld(KBYTES)\n",  Vmeminfo.dwAvailPageFile/1024);
	fprintf(fp,"���ռ�������%ld(BYTES)\n",  Vmeminfo.dwTotalVirtual);
	fprintf(fp,"�������ռ�����%ld(BYTES)\n",  Vmeminfo.dwAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	stat = VirtualFree(BASE_PTR, 0, MEM_RELEASE);//�ͷ��ڴ�
	DWORD lerr = GetLastError();
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);//��ѯVirtualFree֮��ĵ�ǰ����״̬״̬
	//�����Ϣ
	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n********************************\n");
	GlobalMemoryStatus(&Vmeminfo);//��ѯVirtualFree֮�������״̬
	//�����Ϣ
	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%ld(BYTES)\n",  Vmeminfo.dwTotalPhys);
	fprintf(fp,"���������ڴ棺%ld(BYTES)\n",  Vmeminfo.dwAvailPhys);
	fprintf(fp,"ҳ���ļ�������%ld(KBYTES)\n",  Vmeminfo.dwTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%ld(KBYTES)\n",  Vmeminfo.dwAvailPageFile/1024);
	fprintf(fp,"���ռ�������%ld(BYTES)\n",  Vmeminfo.dwTotalVirtual);
	fprintf(fp,"�������ռ�����%ld(BYTES)\n",  Vmeminfo.dwAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	BASE_PTR = malloc(1024*32*sizeof(char));//������new
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);/*��ѯmalloc֮��ĵ�ǰ����״̬״̬*/
	//�����Ϣ
	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n********************************\n");
	GlobalMemoryStatus(&Vmeminfo);//��ѯmalloc֮�������״̬
	//�����Ϣ
	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%ld(BYTES)\n",  Vmeminfo.dwTotalPhys);
	fprintf(fp,"���������ڴ棺%ld(BYTES)\n",  Vmeminfo.dwAvailPhys);
	fprintf(fp,"ҳ���ļ�������%ld(KBYTES)\n",  Vmeminfo.dwTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%ld(KBYTES)\n",  Vmeminfo.dwAvailPageFile/1024);
	fprintf(fp,"���ռ�������%ld(BYTES)\n",  Vmeminfo.dwTotalVirtual);
	fprintf(fp,"�������ռ�����%ld(BYTES)\n",  Vmeminfo.dwAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	memset(&inspectorinfo1, 0, structsize);//�ṹ����0
	free(BASE_PTR );//�����new������delete
	VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);/*��ѯfree֮��ĵ�ǰ����״̬״̬*/
	//�����Ϣ
	fprintf(fp,"��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
	fprintf(fp,"�����С:0X%x\n", inspectorinfo1.RegionSize);
	fprintf(fp,"Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
	fprintf(fp,"����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
	fprintf(fp,"��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
	fprintf(fp,"(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
	fprintf(fp,"(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
	fprintf(fp,"��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n********************************\n");
	GlobalMemoryStatus(&Vmeminfo);//��ѯfree֮�������״̬
	//�����Ϣ
	fprintf(fp,"��ǰ����洢ͳ������\n");
	fprintf(fp,"�����ڴ�������%ld(BYTES)\n",  Vmeminfo.dwTotalPhys);
	fprintf(fp,"���������ڴ棺%ld(BYTES)\n",  Vmeminfo.dwAvailPhys);
	fprintf(fp,"ҳ���ļ�������%ld(KBYTES)\n",  Vmeminfo.dwTotalPageFile/1024);
	fprintf(fp,"����ҳ���ļ�����%ld(KBYTES)\n",  Vmeminfo.dwAvailPageFile/1024);
	fprintf(fp,"���ռ�������%ld(BYTES)\n",  Vmeminfo.dwTotalVirtual);
	fprintf(fp,"�������ռ�����%ld(BYTES)\n",  Vmeminfo.dwAvailVirtual);
	fprintf(fp,"����洢ʹ�ø��ɣ�%%%d\n\n\n\n",  Vmeminfo.dwMemoryLoad);
	fclose(fp);
	return 0;
}
