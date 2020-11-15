 

 int main() {
 	int **a;
	a = new int*[4];
	a[1] = new int[3];
	a[2] = new int;
	int b = 25;
	int c[3] = {1,10,100};
	*(a[2]) = 15;
	a[0][0] = 8;
	a[2] = &b;
	a[2][0] = 1986;
	a[2] = &(c[1]);
 }