#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
struct range {
   int high;
   int low;
};

void *prime(void *args)
{
   struct range *range = args;
   printf("\nlow : %d -> high : %d\n",range->low,range->high);
   while (range->low < range->high)
   {
       int flag = 0;
       for(int i = 2; i <= range->low/2; ++i)
       {
           if(range->low % i == 0)
           {
               flag = 1;
		//printf("%d", range->low);
               break;
           }
       }
       if (flag == 0)
           printf("%d ", range->low);
       ++range->low;
   }
}
int main(void)
{
   int N, T;
   scanf("%d %d", &N, &T);
   //printf("%d%d",N,T);
   int interval = N/T;
   pthread_t tid[T];
   struct range *range = malloc(sizeof(struct range));
   range->low = 1;
   for (int i=0;i<T;i++){
       range->high = range->low + (interval-1);
       //printf("%d -> %d",range->low,range->high);
       if(pthread_create(&tid[i], NULL, prime, range)){
           fprintf(stderr, "No threads for you.\n");
       }
       sleep(1);
       range->low = range->high + 1;
   }
  
   for (int i;i<T;i++){
       pthread_join(tid[i], NULL);
   }
  return 0;
}

