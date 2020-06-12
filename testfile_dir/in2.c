int main(){
	int a[100];
	a[0]=1;
	a[1]=1;
	int n;
	scanf(n);
	for (int i=0;i<n;i++){
		if (i>1) a[i]=a[i-1]+a[i-2];
		printf(i+1,":",a[i],"\n");
	}
	return 0;
}