// By Stefan Radu

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll MOD = 5e9;
const int EPS = 1000;
const int DISPLAY_START = 7;

void print(vector < ll > howMany) {

  for (int i = DISPLAY_START; i < 10; ++ i) {
    cerr << i * 10 + 1 << " - " << (i + 1) * 10 << ": " << howMany[i] << '\n';
  }

  cerr << '\n';
}

void run(int &cnt, ll &steps, vector < ll > &howMany, vector < bool > &state) {
  int cur = rand() % 100;
  if (state[cur] == 0) {
    state[cur] = 1;
    -- cnt;
  }
  else {
    state[cur] = 0;
    ++ cnt;
  }

  if (cnt == 100) {
    cerr << "Back to the beginning" << endl;
    exit(0);
  }

  ++ steps;

  for (int i = DISPLAY_START; i < 10; ++ i) {
    if (cnt > i * 10 and cnt <= (i + 1) * 10) {
      ++ howMany[i];
    }
  }

  if (steps % MOD == 0) print(howMany);
}

int main() {

  srand(time(0));

  int cnt = 100;
  ll steps = 0;

  vector < bool > state(100);
  vector < ll > howMany(10), aux(10);

  for (int i = 1; i <= EPS; ++ i) run(cnt, steps, aux, state); 
  while (true) run(cnt, steps, howMany, state); 
}
