int fib(int n)
{
	if (n == 0) {
		return(1);
	} else if (n == 1) {
		return(1);
	} else {
		return(fib(n - 1) + fib(n - 2));
	}
}

void main()
{
	int n;
	printf("Please input: ");
	scanf(n);
	for (int i=0;i<n;i++){
		printf(fib(i)," ");
	}
	printf("\n");
}
