#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
  const char* filename = argc > 1 ? argv[1] : "input.txt";
  ifstream fin(filename);

  if (!fin) {
    cerr << "Cannot open file: " << filename << endl;
    return 1;
  }

  int a, b;
  while (fin >> a >> b)
    cout << a+b << endl;

  return 0;
}
