void hanio(int n, char from, char buffer, char to)
{
	if (n == 0) return;
	hanio(n - 1, from, to, buffer);
	printf("Move disk from ", from);
	printf(" to ", to);
	printf("\n");
	hanio(n - 1, buffer, from, to);
}

void main()
{
	int n;
	printf("Please input: ");
	scanf(n);
	hanio(n, 'A', 'B', 'C');
}