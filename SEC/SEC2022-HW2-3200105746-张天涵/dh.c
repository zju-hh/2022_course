#include<stdio.h>
#include<string.h>
#define MAX 100
int x[MAX],y[MAX],z[MAX],m[MAX];
int digit;
int ADD(char num1[],char num2[],int sum[])
{
    int i, j, len;
    int n2[MAX] = {0};
    int n1[MAX] = {0};
    int len1 = strlen (num1); 
    int len2 = strlen (num2); 
 	len = len1>len2 ? len1 : len2; 
     
    for (i = len1-1, j = 0; i >= 0; i--, j++) n1[j] = num1[i] - '0';
    for (i = len2-1, j = 0; i >= 0; i--, j++) n2[j] = num2[i] - '0';
    for (i = 0; i <= len; i++)
    {
         sum[i] =n1[i]+n2[i];  
         if (sum[i] > 9)   
        {   
            sum[i]-= 10;
            sum[i+1]++;
        }
     }
    if(sum[len] != 0) 
    len++;
    return len;   
}

int SUB(char num1[],char num2[],int sum[])
{
    int i, j, flag;
    int len;
    char *temp;
    int n2[MAX] = {0};
    int len1 = strlen(num1); 
    int len2 = strlen(num2); 
    flag = 0; 
    if(len1 < len2) 
      {
        flag = 1; 
        temp = num1;
        num1 = num2;
        num2 = temp;
        int len1 = strlen(num1); 
        int len2 = strlen(num2);
      }

      else if(len1 ==len2) 
      {  
           
         for(i = 0; i < len1; i++)
          {
              if(num1[i] == num2[i])
                  continue;
             if(num1[i] > num2[i])
               {
                  flag = 0; 
                  break;
              } 
              else
              {
                 flag = 1; 
                   
                 temp = num1;
                 num1 = num2;
                 num2 = temp;
                  break;
            } 
          }  
      }
        len = len1>len2 ? len1 : len2; 
        for (i = len1-1, j = 0; i >= 0; i--, j++) 
        sum[j] = num1[i] - '0';
      
      for (i = len2-1, j = 0; i >= 0; i--, j++)
          n2[j] = num2[i] - '0';
     
      for (i = 0; i <= len; i++)
      {
          sum[i] = sum[i] - n2[i];  
          if (sum[i] < 0)   
         {    
           sum[i] += 10;
             sum[i+1]--;
          }
      }
     for (i = len1-1; i>=0 && sum[i] == 0; i--)
      len = i+1;
      if(flag==1)
      {
          sum[len] = -1; 
        len++;
     }
      return len;  
}

int MUL(char num1[],char num2[],int sum[])
 {
    int i, j, len, len1, len2;
    int a[MAX+10] = {0};
    int b[MAX+10] = {0};
    int c[MAX*2+10] = {0};

    len1 = strlen(num1);
    for(j = 0, i = len1-1; i >= 0; i--) a[j++] = num1[i]-'0';
    len2 = strlen(num2);
    for(j = 0, i = len2-1; i >= 0; i--)b[j++] = num2[i]-'0';
    for(i = 0; i < len2; i++)
    {
        for(j = 0; j < len1; j++)
        {
             c[i+j] += b[i] * a[j]; 
        }
     }
     
    for(i=0; i<MAX*2; i++) 
    {
         if(c[i]>=10)
         {
             c[i+1]+=c[i]/10;
             c[i]%=10;
         }
     }
 
     for(i = MAX*2; c[i]==0 && i>=0; i--); 
     len = i+1; 
     for(; i>=0; i--)
        sum[i]=c[i];
     return len; 
    }



void sub(int x[],int y[],int len1,int len2)
{
	int i;
	for(i=0;i<len1;i++)
	{
		if(x[i]<y[i])
		{
			x[i]=x[i]+10-y[i];
			x[i+1]--;
		}
		else
			x[i]=x[i]-y[i];
	}
	for(i=len1-1;i>=0;i--)
	{
		if(x[i])
		{ 
			digit=i+1;
			break;		   
		} 
	}
}
int judge(int x[],int y[],int len1,int len2)
{
	int i;
	if(len1<len2)
		return -1;
	if(len1==len2)
	{
		for(i=len1-1;i>=0;i--)
		{
			if(x[i]==y[i])
				continue;
			if(x[i]>y[i])
				return 1;
			if(x[i]<y[i])
				return -1;
		}
		return 0;
	}	
}

int main()
{
    int i;
    char num1[MAX] = {0};
    char num2[MAX] = {0};
    int addout[MAX] = {0};
    int subout[MAX] = {0};
    
    char divout[MAX] = {0};

	
    
	scanf("%s", num1);     
    scanf("%s", num2);
	int p;
	scanf("%d",&p);
	int g;
	scanf("%d",&g);
	
	char a1[500]={0};
	a1[0]='1';
	int k;
    int mullen = 0;
	for(k=0;k<p;k++)
	{
	int mulout[2 * MAX] = {0};
	int j=0;
    mullen = MUL(num2, a1, mulout);
    char tmp[500]={0};
    for(i = mullen-1,j=0; i>=0; i--)
    {
    	a1[j++]=mulout[i]+'0';
	}
	}
   
    
    char a2[500]={0};
	a2[0]='1';

    mullen = 0;
	for(k=0;k<g;k++)
	{
	int mulout[2 * MAX] = {0};
	int j=0;
    mullen = MUL(num2, a2, mulout);
    char tmp[500]={0};
    for(i = mullen-1,j=0; i>=0; i--)
    {
    	a2[j++]=mulout[i]+'0';
	}
	}
    
    
	
	
	
	int len1,len2;
	len1=strlen(a1);
	len2=strlen(num1);
	int k1=0;
	int j=0,temp;
	for(i=len1-1,j=0;i>=0;i--)
			x[j++]=a1[i]-'0';
	for(i=len2-1,k1=0;i>=0;i--)
			y[k1++]=num1[i]-'0';		    
	if(len1<len2)
		{
			printf("0\n");
			puts(num1); 
		}
	else 
		{
			int len=len1-len2;
			for(i=len1-1;i>=0;i--)
			{
				if(i>=len)
					y[i]=y[i-len];
				else
					y[i]=0;
			}
			len2=len1;	
			digit=len1;	
			for(j=0;j<=len;j++)
            {
				z[len-j]=0;
				while(((temp=judge(x,y,len1,len2))>=0)&&digit>=k1)
				{	
					sub(x,y,len1,len2);				    
					z[len-j]++;
					len1=digit;
					if(len1<len2&&y[len2-1]==0)		
						len2=len1;				
				}
				if(temp<0)
				{
					for(i=1;i<len2;i++)
						y[i-1]=y[i];
					y[i-1]=0;
					if(len1<len2) 
						len2--;			        				        
				}
			}
			for(i=len;i>0;i--)
			{
				if(z[i])
					break;
			}
			
			for(i=len1;i>0;i--)
			{
				if(x[i])
					break;
			}
			for(;i>=0;i--)printf("%d",x[i]);
			printf("\n");
		}
		
		
		
	
	len1=strlen(a2);
	len2=strlen(num1);
	k1=0;
	j=0,temp;
	for(i=len1-1,j=0;i>=0;i--)
			x[j++]=a2[i]-'0';
	for(i=len2-1,k1=0;i>=0;i--)
			y[k1++]=num1[i]-'0';		    
	if(len1<len2)
		{
			printf("0\n");
			puts(num1); 
		}
	else 
		{
			int len=len1-len2;
			for(i=len1-1;i>=0;i--)
			{
				if(i>=len)
					y[i]=y[i-len];
				else
					y[i]=0;
			}
			len2=len1;	
			digit=len1;	
			for(j=0;j<=len;j++)
            {
				z[len-j]=0;
				while(((temp=judge(x,y,len1,len2))>=0)&&digit>=k1)
				{	
					sub(x,y,len1,len2);				    
					z[len-j]++;
					len1=digit;
					if(len1<len2&&y[len2-1]==0)		
						len2=len1;				
				}
				if(temp<0)
				{
					for(i=1;i<len2;i++)
						y[i-1]=y[i];
					y[i-1]=0;
					if(len1<len2) 
						len2--;			        				        
				}
			}
			for(i=len;i>0;i--)
			{
				if(z[i])
					break;
			}
			
			for(i=len1;i>0;i--)
			{
				if(x[i])
					break;
			}
			for(;i>=0;i--)printf("%d",x[i]);
			printf("\n");
		}
    return 0;
}
