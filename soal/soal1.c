#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t t1, t2;

FILE *fptr1, *fptr2, *fptr3;
int status;

void *copy1()
{
	fptr1=fopen("baca.txt", "rb");
	fptr2=fopen("salin1.txt", "wb");
	status =0;
	char c = fgetc(fptr1);
	while(c != EOF){
		fputc(c, fptr2);
		c = fgetc(fptr1);
	}
	status =1;
	fclose(fptr1); fclose(fptr2);
	return 0;
}

void *copy2()
{
	while(!status){}
	fptr2=fopen("salin1.txt", "rb");
	fptr3=fopen("salin2.txt", "wb");
	char c= fgetc(fptr2);
	while (c != EOF){
		fputc(c, fptr3);
		c = fgetc(fptr2);
	}
	fclose(fptr2);
	fclose(fptr3);
	return 0;
}

int main (void)
{
	pthread_create(&(t1), NULL, &copy1, NULL);
	pthread_create(&(t2), NULL, &copy2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
