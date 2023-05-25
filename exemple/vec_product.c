
void vec_product(double left[], double right[], double alpha, double out[], int N){
  #pragma omp parallel for shared(left, right, out, alpha, N) schedule(static, 1000)
    for (int i=0; i<N; i++){
      out[i] = left[i] * right[i] * alpha;
    }
}


int main(){
  int N=100000;
  double a[N], b[N], c[N];
  for (int i=0; i<N; i++){
    a[i] = i;
    b[i] = N - i;
    c[i] = 0.;
  }

  for(int rep=0; rep<10000; rep++) vec_product(a, b, 2., c, N);

}
