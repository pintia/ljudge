#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
  const char* filename = argc > 1 ? argv[1] : "output.txt";
  ofstream fout(filename);
  
  if (!fout) {
    cerr << "Cannot open file: " << filename << endl;
    return 1;
  }

  int a, b;
  while (cin >> a >> b)
    fout << a+b << endl;

  return 0;
}
