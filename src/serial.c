




void putc(int data) {

	int *mu_io;
	mu_io = 0x3f215040;
	*mu_io = data;
}

