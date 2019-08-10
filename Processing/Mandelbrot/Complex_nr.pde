class Complex_nr {
  Complex_nr(double a, double b) {
    this.real = a;
    this.imaginary = b;
  }

  double real;
  double imaginary;

  void add (Complex_nr x) {
    this.real += x.real;
    this.imaginary += x.imaginary;
  }

  void sq() {
    double x = this.real * this.real - this.imaginary * this.imaginary;
    double y = this.real * this.imaginary * 2;
    
    this.real = x;
    this.imaginary = y;
  }

  double modulo() {
    double m = (this.real * this.real) + (this.imaginary * this.imaginary);
    return java.lang.Math.sqrt(m);
  }

  void print() {
    println(this.real, this.imaginary);
  }
}