#include<stdio.h>
#include<string.h>
#include<conio.h>
FILE *fp;
char filename[100][256],output[100000],str[1000],ch[100],rom[10]="#include \"";
int proc[100],local[10];
int initall(){
	for(local[0]=0;local[0]<100;local[0]++)
		for(local[1]=0;local[1]<100000;local[1]++)
			filename[local[0]][local[1]]=0;
	for(local[0]=0;local[0]<100000;local[0]++)
		output[local[0]]=0;
	for(local[0]=0;local[0]<1000;local[0]++)
		str[local[0]]=0;
	for(local[0]=0;local[0]<100;local[0]++)
		ch[local[0]]=0;
	for(local[0]=0;local[0]<100;local[0]++)
		proc[local[0]]=0;
	for(local[0]=1;local[0]<10;local[0]++)
		local[local[0]]=0;local[0]=0;
}
int namecheck(){
	for(local[1]=local[0];local[1]>=0;local[1]--)
		if(strcmp(str,filename[local[1]])==0)return 0;
	return 1;
}
int opensubfile(int limit){
	//printf("open:%s\n",str);
	for(local[1]=0;local[1]<=local[0];local[1]++)printf(" |");
	local[1]=0;
	printf("%s\n",str);
	if(namecheck()==1){
		local[1]=0;
		if((fopen(str,"r"))==0||(local[0]+1)>limit)return -1;
		proc[local[0]]=ftell(fp)-1;
		strcpy(filename[++local[0]],str);
		fclose(fp);
		fp=fopen(filename[local[0]],"r");
	}else{
		//printf("illegal file open\n");
	}
	local[1]=1;
}
int backfile(){
	//for(int i=0;i<100;i++)printf("%d,",filename[local[0]-1][i]);
	//printf("back:%s\n",filename[local[0]-1],fopen(filename[local[0]-1],"r"),local[0]-1);
	if((fopen(filename[--local[0]],"r"))==0||local[0]<0)return -1;
	fclose(fp);
	fp=fopen(filename[local[0]],"r");
	fseek(fp,proc[local[0]],0);
	local[1]=1;
	//puts("end");
}
int scanincfile(int limit){
	local[0]=0;local[1]=0;local[2]=0;local[3]=0;
	fseek(fp,0,0);
	while(local[0]>=0){
		if(fgets(str,1000,fp)==0||local[0]>5)backfile();
		if(strstr(str,"#include")!=0&&strstr(str,"<")==0&&str[0]==rom[0]){
			while(str[local[1]++]!=rom[9])if(local[1]>10)break;
			local[2]=local[1]+1;
			while(str[local[1]-local[2]]=str[local[1]++])if(local[1]>1000)break;
			str[strlen(str)-3]=99;str[strlen(str)-2]=0;local[1]=0;local[2]=0;
			if(fopen(str,"r")&&local[1]==0)
				opensubfile(limit);
			str[strlen(str)-1]=104;
			if(fopen(str,"r")&&local[1]==0)
				opensubfile(limit);
			if(local[1]==0){
				//printf("File open failed\n");
			}
			local[1]=0;
			//printf("local[0]=%d\n",local[0]);
			//getch();
		}
		local[1]=0;
	}
	local[0]=0;
}
int starttask(char limit[100]){
	while(local[0]!=1){
		//for(int i=0;i<100;i++)printf("%d,",filename[0][i]);
		fp=fopen(filename[0],"r");
		if(fp==0)return -1;
		printf("press any key start task\n");
		//for(int i=0;i<100;i++)printf("%d,",local[i]);
		//getch();
		scanincfile(limit);
		break;
		//for(int i=0;i<100;i++)printf("%d,",proc[i]);
	}
}
int main(int argc,char **argv){
	initall();
	if(argv[1]==0)strcpy(filename[0],"main.c");
	else if(strcmp(argv[1],".")==0)strcpy(filename[0],"main.c");
	else if(atoi(argv[1])!=0){
		strcpy(filename[0],"main.c");
		local[0]=atoi(argv[1]);
	}
	else strcpy(filename[0],argv[1]);
	if(argv[2]==0)starttask(local[0]);
	else starttask(atoi(argv[2]));
}
//DIRTY CODE
/*
int scanincfile(){
	local[0]=0;local[1]=0;local[2]=0;local[3]=0;
	fseek(fp,0,0);
	while(local[0]>=0){
		if(fgets(str,1000,fp)==0||local[0]>5)backfile();
		//printf("%s\n",str);
		if(strstr(str,"#include \"")!=0||strstr(str,"#include\"")!=0){
			while(str[local[1]++]!=rom[9])
				if(local[1]>10)break;
			local[2]=local[1]+1;
			while(str[local[1]]!=rom[9]||local[1]>266)str[local[1]-local[2]]=str[local[1]++];
			str[local[1]-local[2]]=99;str[local[1]-(local[2]-1)]=0;local[1]=0;local[2]=0;
			if(fopen(str,"r")&&local[1]==0){
				printf("fopen pass\n");
				opensubfile();
			}
			str[strlen(str)-1]=104;
			if(fopen(str,"r")&&local[1]==0){
				printf(".h file only\n");
				opensubfile();
			}
			if(local[1]==0){
				//printf("File open failed\n");
			}
			local[1]=0;
			//printf("local[0]=%d\n",local[0]);
			//getch();
		}
	}
	local[0]=0;
}*/
//END