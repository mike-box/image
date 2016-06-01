#include <stdio.h>

// 函数名称：求解多元一次方程组
// data：方程组系数矩阵
// answer：求得的未知数的结果
// num：未知数的个数
int imgLinearEquation(float *data,float *answer,int num)
{
	int i,j,k;
	
	float buff;
	
	#define DATA(y,x) (*(data+(y)*(num+1)+(x)))	
	
	// 高斯消元
	for(k=0;k<num;k++)
	{
		if(DATA(k,k)==0)
		{
			for(j=k+1;j<num;j++)
				if(DATA(j,k)!=0)
				{
					for(i=k;i<num+1;i++)
					{
						buff = DATA(k,i);
						DATA(k,i) = DATA(j,i);
						DATA(j,i) = buff;
					}
						
					break;
				}
				
			// 如果无解则返回0
			if(j==num)
				return 0;
		}
		
		for(i=k+1;i<num+1;i++)		
			DATA(k,i) = DATA(k,i)/DATA(k,k);
			
		DATA(k,k) = 1;
				
		for(j=k+1;j<num;j++)
			if(DATA(j,k)!=0)
			{
				for(i=k+1;i<num+1;i++)
					DATA(j,i) = DATA(j,i)/DATA(j,k)-DATA(k,i);
				
				DATA(j,k)=0;
			}
	}
	
	// 答案求解
	for(j=num-1;j>=0;j--)
	{
		answer[j] = 0-DATA(j,num);
		for(i=num-1;i>j;i--)
			answer[j] = answer[j] - DATA(j,i)*answer[i];
	}
	
	return 1;		
}

#define ABS(x) (((x)>0)?(x):(0-x))

float imgSqrt(float x)
{
	float y=(x+1.0)/2.0;
	
	float error = ABS(y*y-x);
	
	while(error>0.01)
	{
		y = (y+x/y)/2.0;
		
		error = ABS(y*y-x);
	}
	
	return y;
}

float mysin[91]={0.00000000000000,
				0.01745240643728,
				0.03489949670250, 
				0.05233595624294, 
				0.06975647374413, 
				0.08715574274766, 
				0.10452846326765, 
				0.12186934340515, 
				0.13917310096007, 
				0.15643446504023, 
				0.17364817766693, 
				0.19080899537655, 
				0.20791169081776, 
				0.22495105434387, 
				0.24192189559967, 
				0.25881904510252, 
				0.27563735581700, 
				0.29237170472274, 
				0.30901699437495, 
				0.32556815445716, 
				0.34202014332567, 
				0.35836794954530, 
				0.37460659341591, 
				0.39073112848927, 
				0.40673664307580, 
				0.42261826174070, 
				0.43837114678908, 
				0.45399049973955, 
				0.46947156278589, 
				0.48480962024634, 
				0.50000000000000, 
				0.51503807491005, 
				0.52991926423321, 
				0.54463903501503, 
				0.55919290347075, 
				0.57357643635105, 
				0.58778525229247, 
				0.60181502315205, 
				0.61566147532566, 
				0.62932039104984, 
				0.64278760968654, 
				0.65605902899051, 
				0.66913060635886, 
				0.68199836006250, 
				0.69465837045900, 
				0.70710678118655, 
				0.71933980033865, 
				0.73135370161917,
				0.74314482547739, 
				0.75470958022277, 
				0.76604444311898, 
				0.77714596145697, 
				0.78801075360672, 
				0.79863551004729, 
				0.80901699437495, 
				0.81915204428899, 
				0.82903757255504, 
				0.83867056794542, 
				0.84804809615643, 
				0.85716730070211, 
				0.86602540378444, 
				0.87461970713940, 
				0.88294759285893, 
				0.89100652418837, 
				0.89879404629917, 
				0.90630778703665, 
				0.91354545764260, 
				0.92050485345244, 
				0.92718385456679, 
				0.93358042649720, 
				0.93969262078591, 
				0.94551857559932, 
				0.95105651629515, 
				0.95630475596304, 
				0.96126169593832, 
				0.96592582628907, 
				0.97029572627600, 
				0.97437006478524, 
				0.97814760073381, 
				0.98162718344766, 
				0.98480775301221, 
				0.98768834059514, 
				0.99026806874157,
				0.99254615164132, 
				0.99452189536827, 
				0.99619469809175, 
				0.99756405025982, 
				0.99862953475457, 
				0.99939082701910, 
				0.99984769515639,
				1.0};	

float imgSin(int x)
{
	if(x>=360)
		x = x%360;
	
	if((x>=0)&&(x<90))
		return mysin[x];
	else if(x<180)
		return mysin[180-x];
	else if(x<270)
		return (0-mysin[x-180]);
	else
		return (0-mysin[360-x]);
}



float imgCos(int x)
{
	if(x>=360)
		x = x%360;
	
	if((x>=0)&&(x<90))
		return mysin[90-x];
	else if(x<180)
		return (0-mysin[x-90]);
	else if(x<270)
		return (0-mysin[270-x]);
	else
		return mysin[x-270];
}




// 函数名称：抛物线拟合
// x：输入的自变量序列
// y：输入的因变量序列
// n：自变量因变量的个数
// answer：输出的抛物线系数
void imgPolyFit2(float *x,float *y,int n,float *answer)
{
	int i,j;
	
	float k[3][4];
	// 方程组的系数矩阵
	for(j=0;j<3;j++)
		for(i=0;i<4;i++)
			k[j][i] = 0.0;
		
	float x1,x2,y1;
		
	// 构造三元一次方程组
	for(i=0;i<n;i++)
	{
		x2 = x[i]*x[i];
		x1 = x[i];
		y1 = y[i];
		
		k[0][0] = k[0][0]+x2;
		k[0][1] = k[0][1]+x1;		
		k[1][0] = k[1][0]+x2*x1;
		k[2][0] = k[2][0]+x2*x2;
		
		k[0][3] = k[0][3]-y1;
		k[1][3] = k[1][3]-x1*y1;
		k[2][3] = k[2][3]-x2*y1;	
	}
	
	k[0][2] = n;
	k[1][1] = k[0][0];
	k[1][2] = k[0][1];
	k[2][1] = k[1][0];
	k[2][2] = k[0][0];
	
	// 求解三元一次方程组矩阵	
	imgLinearEquation(k[0],answer,3);	
}

void imgPolyFit3(float *x,float *y,int n,float *answer)
{
	int i,j;
	
	float k[4][5];
	// 方程组的系数矩阵
	for(j=0;j<4;j++)
		for(i=0;i<5;i++)
			k[j][i] = 0.0;
		
	float x1,x2,x3,y1;
	
	for(i=0;i<n;i++)
	{
		x1 = x[i];
		x2 = x1*x1;
		x3 = x2*x1;
		y1 = y[i];
	
		k[0][0] = k[0][0]+x3;
		k[0][1] = k[0][1]+x2;
		k[0][2] = k[0][2]+x1;
		k[1][0] = k[1][0]+x3*x1;
		k[2][0] = k[2][0]+x3*x2;
		k[3][0] = k[3][0]+x3*x3;
		
		k[0][4] = k[0][4]-y1;
		k[1][4] = k[1][4]-x1*y1;
		k[2][4] = k[2][4]-x2*y1;
		k[3][4] = k[3][4]-x3*y1;
	}

	k[0][3] = n;
	k[1][1] = k[0][0];
	k[1][2] = k[0][1];
	k[1][3] = k[0][2];
	k[2][1] = k[1][0];
	k[2][2] = k[1][1];
	k[2][3] = k[1][2];
	k[3][1] = k[2][0];
	k[3][2] = k[2][1];
	k[3][3] = k[2][2];
	
	imgLinearEquation(k[0],answer,4);
}
		
	
	
	
