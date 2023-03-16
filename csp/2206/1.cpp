/*
 * @Author: zanilia
 * @Date: 2022-08-29 10:46:38
 * @LastEditTime: 2022-08-29 10:52:16
 * @Descripttion: 
 */
#include <math.h>
#include <stdio.h>
double nums[1000];
int n;
int main(){
	scanf("%d",&n);
	double avg = 0;
	for(int i=0;i<n;++i){
		scanf("%lf",&nums[i]);
		avg += nums[i];
	}
	avg /= n;
	double d = 0;
	for(int i=0;i<n;++i){
		d += (nums[i]-avg)*(nums[i]-avg);
	}
	d /= n;
	d = sqrt(d);
	for(int i=0;i<n;++i){
		printf("%lf\n",(nums[i]-avg)/d);
	}
	return 0;
}