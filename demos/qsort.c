int a[1000];

void qsort(int l,int r,int n){
	int i=l,j=r;
	int key=a[l];
	for (int i=0;i<n;i++) printf(a[i],' ');
	printf("\n");
	printf(l," ",key," ",a[l],"\n");
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
	int n;
	scanf(n);
	for (int i=0;i<n;i++) scanf(a[i]);
	qsort(0,n-1,n);
	for (int i=0;i<n;i++) printf(a[i],' ');
	printf("\n");
	return 0;
}
