typedef struct DoubleMatrix {
  int rows, cols, error;
  double* ptr;
} DoubleMatrix;

DoubleMatrix createMatrix(int rows, int cols);

void destroyMatrix(DoubleMatrix* matrix);

int inputMatrix(DoubleMatrix* matrix, char* prompt);

int outputMatrix(DoubleMatrix* matrix, char* message);

double matrixMean(DoubleMatrix* matrix);

double get(DoubleMatrix* matrix, int i, int j);

void set(DoubleMatrix* matrix, int i, int j, double val);