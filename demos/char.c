int a[1000];
int cnt;

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
	}
	if (i-1>l) qsort(l,i-1,n);
	if (i+1<r) qsort(i+1,r,n);
}

int main() {
	cnt=0;
	int n;
	scanf(n);
	for (int i=0;i<n;i++) scanf(a[i]);
	for (int i=0;i<n;i++) printf(a[i]," ");
	printf("\n");
	qsort(0,n-1,n);
	for (int i=0;i<n;i++) printf(a[i],' ');
	printf("\n");
	return 0;
}