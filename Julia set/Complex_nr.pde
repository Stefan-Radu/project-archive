class Complex_nr {
  Complex_nr(float a, float b) {
    this.real = a;
    this.imaginary = b;
  }

  float real;
  float imaginary;

  void add (Complex_nr x) {
    this.real += x.real;
    this.imaginary += x.imaginary;
  }

  void sq() {
    float x = this.real * this.real - this.imaginary * this.imaginary;
    float y = this.real * this.imaginary * 2;
    
    this.real = x;
    this.imaginary = y;
  }

  float modulo() {
    float m = (this.real * this.real) + (this.imaginary * this.imaginary);
    return sqrt(m);
  }

  void print() {
    println(this.real, this.imaginary);
  }
}