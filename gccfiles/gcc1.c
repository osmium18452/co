int add(int a,int b){
	return a+b;
}
int add_many_times(int a,int b,int c){
	return a+b*c;
}
int caller(int a,int b){
	int c,d;
	add(c,d);
	{
		int e,f;
		add (e,f);
	}
	add(c,d);
	int e,f;
	add(e,f);
}