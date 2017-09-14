inline int Bignum::Carry::operator()(int n){
	n += carr_;
	carr_ = n / 10;
	return n % 10;
}
