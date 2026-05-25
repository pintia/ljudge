#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
  const char* inf = argc > 1 ? argv[1] : "input.txt";
  ifstream fin(inf);
  const char* outf = argc > 2 ? argv[2] : "output.txt";
  ofstream fout(outf);

  if (!fin) {
    cerr << "Cannot open file: " << inf << endl;
    return 1;
  }

  if (!fout) {
    cerr << "Cannot open file: " << outf << endl;
    return 1;
  }

  int a, b;
  while (fin >> a >> b)
    fout << a+b << endl;

  return 0;
}