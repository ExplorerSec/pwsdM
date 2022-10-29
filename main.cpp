#include <bits/stdc++.h>
#include <Windows.h>
#include <fstream>
#include <random>
#define InfoFileD "info.dat"//在改为某些路径后会无法读取，原因未知：D:\\info.dat可以,D:\\xx\\pswdM\\info.dat不行
#define LengthMinOrder 5
#define LengthOrder 20
using namespace std;

/*更新记录*/
//0.0.2版本
//202210221454二级指令改为字符型，存在死循环bug，改回int
//202210221519弱权限模块
//202210221519兼容性路径
//0.0.3版本
//202210221618随机数产生器优化
//202210261640界面优化
//202210261649解决二级返回一级的吞字符bug
//202210261706本地密码文件报错功能

/*指令简写对照格式*/
struct order_struct {
	char MinOrder[LengthMinOrder];
	char Order[LengthOrder];
};
/*密码储存格式*/
struct mm_struct {
	char fileName[50] = "file404";
	char mm_account[16] = "account404";
	char mm_password[21] = "password404";
	char mm_web[50] = "web404";
	char mm_name[10] = "name404";
	char mm_phone[12] = "number404";
} str;

/*剪切板写入函数*/
int setClipbar(const char *data) {
	int contentSize = strlen(data) + 1;
	HGLOBAL hMemory;
	LPTSTR lpMemory;
	if (!OpenClipboard(NULL)) return 0; /* 打开剪切板 */
	if (!EmptyClipboard()) return 0; /* 清空剪切板 */
	if (!(hMemory = GlobalAlloc(GMEM_MOVEABLE, contentSize))) return 0; /* 对剪切板分配内存 */
	if (!(lpMemory = (LPTSTR)GlobalLock(hMemory))) return 0; /* 锁定内存区域 */
	memcpy_s(lpMemory, contentSize, data, contentSize);    /* 复制数据到内存区域 */
	GlobalUnlock(hMemory);                                 /* 解除内存锁定 */
	if (!SetClipboardData(CF_TEXT, hMemory)) return 0;     /* 设置剪切板数据 */
	//printf("成功复制【%s】到剪切板，字符串长度为%d。\n",data,contentSize);
	CloseClipboard();/* 关闭剪切板 */
	return 1;
}

/*密码信息文件读取函数*/ /*已弃用*/
int FileRead0(const char *filename, mm_struct str) {

	FILE *fp = NULL;
	fp = fopen(filename, "r");
	if (!fscanf(fp, "%s", str.fileName))return 0; //0
	if (!fscanf(fp, "%s", str.mm_account))return 0; //1
	if (!fscanf(fp, "%s", str.mm_password))return 0; //2
	if (!fscanf(fp, "%s", str.mm_web))return 0; //3
	if (!fscanf(fp, "%s", str.mm_name))return 0; //4
	if (!fscanf(fp, "%s", str.mm_phone))return 0; //5
	fclose(fp);
	fp = NULL;
	return 1;
}

/*密码信息文件读取函数*/ /*由于传值调用与传址调用问题，已移入主函数*/
/*int FileRead(const char *filename, mm_struct str) {
	
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	fscanf(fp, "%s", str.fileName); //0
	fscanf(fp, "%s", str.mm_account); //1
	fscanf(fp, "%s", str.mm_password); //2
	fscanf(fp, "%s", str.mm_web); //3
	fscanf(fp, "%s", str.mm_name); //4
	fscanf(fp, "%s", str.mm_phone); //5
	//fgets(str->mm_account);//函数原形错了
	//fprintf(fp,"%d",aa);
	fclose(fp);
	fp = NULL;
	return 1;
}*/

/*自动计数的记录密码文件的信息文件的读取函数*/ /*暂时未解决bug*/
int FileInfoReadPlus(const char *filename, bool See) {
	char MinOrder[LengthMinOrder];
	char fileName[20];
	int FileNum = 0;
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	while (fscanf(fp, "%s", MinOrder)) {
		fscanf(fp, "%s", fileName);
		if (See)printf("%s %s\n", MinOrder, fileName);
		FileNum++;
	}
	fclose(fp);
	fp = NULL;
	return FileNum;
}

/*记录密码文件的信息文件的读取函数*/ /*暂时需要下方补丁*/
int FileInfoRead(const char *filename, bool See, order_struct *Orders) {
	//char MinOrder[LengthMinOrder];
	//char fileName[20];
	int FileNum = 0;
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	fscanf(fp, "%d", &FileNum);
	for (int i = 0; i < FileNum; i++) {
		fscanf(fp, "%s", Orders[i].MinOrder);
		fscanf(fp, "%s", Orders[i].Order);
		if (See)printf("%s %s\n", Orders[i].MinOrder, Orders[i].Order);
	}
	fclose(fp);
	fp = NULL;
	return FileNum;
}

/*记录密码文件的信息文件的读取函数-补丁-读取数目*/
int FileSumFromInfoRead(const char *filename) {
	int FileNum = 0;
	FILE *fp = NULL;
	fp = fopen(filename, "r");
	fscanf(fp, "%d", &FileNum);
	fclose(fp);
	fp = NULL;
	return FileNum;
}

/*多文件扫描函数*/
int FileScan(const char *filename);
/*本想自动扫描指定目录下的所有文件名，
  但是据在网上收集的资料，
  都用到了io.h库和一些其他句柄，
  暂时放下这个思路，
  改为在一个文件中预先记录简略信息。
 */

/*随机数产生函数*/
int RandomNumber(int min, int max)
{
	random_device seed;//硬件生成随机数种子
	ranlux48 engine(seed());//利用种子生成随机数引擎
	uniform_int_distribution<> distrib(min, max);//设置随机数范围，并为均匀分布
	int random = distrib(engine);//随机数
	return random;
}

int main() { //int argc,char** argv)
	/*掩盖真实路径，优化视图*/
	system("@title Password Manager 0.0.3 -10261648");
	system("@color 0a");
	
	/*弱权限模块*/ /*后期再加强*/
	int randnumber=RandomNumber(111112,999998);int ifuser;
	printf("##Login## \n#Account: %d\n#Passwrd: ",randnumber);
	ifuser=(99-randnumber%100)*100+(randnumber/100000*9);
	scanf("%d",&randnumber);
	if(randnumber!=ifuser)
	{
		printf("您没有访问权限!\n");
		return 0;
	}
	else
	{
		system("cls");
		system("@title Password Manager 0.0.3");
	}
	
	/*记录命令数目与命令对照关系*/
	char TerminalOrder[20];
	int FileNum = FileSumFromInfoRead(InfoFileD);
	if(!FileNum)
	{
		printf("# Error 404-0\n\n##Local Files for Password NOT Found!##");
		return 0;
	}
	order_struct Orders[FileNum];
	FileInfoRead(InfoFileD, 0, Orders);
	/*指令读取循环*/
	bool whileflag1 = 1;
	while (whileflag1) {
		printf("\n$$");
		scanf("%s", TerminalOrder);
		if (!strcmp(TerminalOrder, "ls")) {
			printf("\n");
			FileInfoRead(InfoFileD, 1 , Orders);
			continue;
		}else if (!strcmp(TerminalOrder, "cls")) {
			system("cls");
			continue;}
		else {
			/*进入一级指令文件匹配循环*/
			bool FirstOrderMatch=1;//进入匹配的标志,修复离开二级指令循环时弹出一级指令不存在的bug
			int i = 0;
			for (i = 0; i < FileNum; i++){
				if (!strcmp(TerminalOrder, Orders[i].MinOrder)) {
					//printf("%s %s\n",TerminalOrder, Orders[i].MinOrder);
					//printf("%s %s\n",Orders[i].MinOrder,Orders[i].Order);
					//FileRead(Orders[i].Order, str);//printf("%s\n",Orders[i].Order);
					
					/*密码文件的读取函数-移入主函数*/
					FILE *fp = NULL;
					fp = fopen(Orders[i].Order, "r");
					char kk[20];
					fscanf(fp, "%s", str.fileName); //0
					fscanf(fp, "%s", str.mm_account); //1
					fscanf(fp, "%s", str.mm_password); //2
					fscanf(fp, "%s", str.mm_web); //3
					fscanf(fp, "%s", str.mm_name); //4
					fscanf(fp, "%s", str.mm_phone); //5
					fclose(fp);
					fp = NULL;
					
					/*二级指令读取循环*//*代码过于冗杂，暂时无解决方案*/
					bool whileflag2 = 1;
					while (whileflag2) {
						int x;
						printf("\n>>");
						scanf("%d", &x);
						switch (x) {
						case 0:
							setClipbar(str.fileName);
							printf("<< Filename copied!\n");
							break;
						case 1:
							setClipbar(str.mm_account);
							printf("<< Account copied!\n");
							break;
						case 2:
							setClipbar(str.mm_password);
							printf("<< Password copied!\n");
							break;
						case 3:
							setClipbar(str.mm_web);
							printf("<< Website copied!\n");
							break;
						case 4:
							setClipbar(str.mm_name);
							printf("<< Name copied!\n");
							break;
						case 5:
							setClipbar(str.mm_phone);
							printf("<< Phone copied!\n");
							break;
						case 6:
							whileflag2 = 0;
							FirstOrderMatch=0;
							break;
						case 7:
							return 0;
							break;
						default:
							printf("<< Error 404-2\n");
							break;
						}
					}
				}		
			}
			if(FirstOrderMatch)printf("<< Error 404-1\n");	
		}
	}
	return 0;
}
