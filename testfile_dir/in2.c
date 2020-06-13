int a[1000];

void qsort(int l,int r,int n){
	int i=l,j=r;
	int key=a[l];
	while (i<j){
		while (i<j&&a[j]>=key){
			j--;
		}
		if (i<j){
			a[i]=a[j];
			i++;
		}
		while (i<j&&a[i]<key){
			i++;
		}
		if (i<j){
			a[j]=a[i];
			j--;
		}
		a[i]=key;
		qsort(l,i-1,n);
		qsort(i+1,r,n);
	}
}

int main() {
	int testa;
	char testc;
	int testb;
	testb=testa+testc;
	testb=testa-testc;
	testb=testa*testc;
	testb=testa/testc;
	int n;
	scanf(n);
	for (int i=0;i<n;i++) scanf(a[i]);
	qsort(0,n-1,n);
	for (int i=0;i<n;i++) printf(a[i],' ');
	printf("\n");
	int c=qsort(0,n-1,n);
	do{
		c++;
	} while (c<5);
	int a;
	a=1;
	printf(a);
	for (int i=0;i<13;i++){
		printf("case ",i,": ");
		switch (i) {
			case 1:
				printf("2\n");
				break;
			case 2:
				printf("3\n");
				break;
			case 3:
				printf("hello ");
			case 4:
				printf("world\n");
				break;
			case 10:
				printf("NO. 10\n");
				break;
			default:
				printf("default\n");
				break;
		}
	}
	return 0;
}
