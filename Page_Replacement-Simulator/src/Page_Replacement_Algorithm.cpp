#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void LRU(int pages[], int refStringNum, int frameNum) {
  unordered_set<int> frame;
  unordered_map<int, int> index;
  int pageFaultsNum = 0;

  for (int i = 0; i < refStringNum; i++) {
    if (frame.size() < frameNum) {
      if (frame.find(pages[i]) == frame.end()) {
        frame.insert(pages[i]);
        pageFaultsNum++;
      }

      index[pages[i]] = i;
    }

    else {
      if (frame.find(pages[i]) == frame.end()) {
        int lru = INT_MAX, temp;
        
        for (auto it = frame.begin(); it != frame.end(); it++) {
          if (index[*it] < lru) {
            lru = index[*it];
            temp = *it;
          }
        }

        frame.erase(temp);
        frame.insert(pages[i]);
        pageFaultsNum++;
      }

      index[pages[i]] = i;
    }
  }
  cout << "The Number of Page faults LRU algorithm: " << pageFaultsNum << endl;
}

int foretellOptimal(int page[], vector<int> &frame, int refStringNum, int index) {
  int result = -1, farthest = index;
  for (int i = 0; i < frame.size(); i++) {
    int j;
    for (j = index; j < refStringNum; j++) {
      if (frame[i] == page[j]) {
        if (j > farthest) {
          farthest = j;
          result = i;
        }
        break;
      }
    }

    if (j == refStringNum)
      return i;
  }

  if (result == -1)
    return 0;
  else
    return result;
}

bool searchOptimal(int key, vector<int> &frame) {
  for (int i = 0; i < frame.size(); i++)
    if (frame[i] == key)
      return true;
  return false;
}

void Optimal(int page[], int refStringNum, int frameNum) {
  vector<int> frame;
  int pageFaultsNum = 0;

  for (int i = 0; i < refStringNum; i++) {

    if (searchOptimal(page[i], frame)) {
      continue;
    }

    if (frame.size() < frameNum) {
      frame.push_back(page[i]);
      pageFaultsNum++;
    }

    else {
      int j = foretellOptimal(page, frame, refStringNum, i + 1);
      frame[j] = page[i];
      pageFaultsNum++;
    }
  }
  
  cout << "The Number of Page faults Optimal algorithm: " << pageFaultsNum << endl;
}

int main() {

  int page[24] = {1, 2, 3, 2, 5, 6, 3, 4, 6, 3, 7, 3, 1, 5, 3, 6, 3, 4, 2, 4, 3, 4, 5, 1};
  int refStringNum = sizeof(page)/sizeof(page[0]); 
  int frameNum = 4;

  for (int i = 0; i < refStringNum; i++)
    cout << page[i] << " ";
  cout << endl << endl;

  LRU(page, refStringNum, frameNum);
  Optimal(page, refStringNum, frameNum);

  return 0;
}