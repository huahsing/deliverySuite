#include <bits/stdc++.h>

using namespace std;

class DeliverySuite
{
private:
  struct Woman
  {
    string name;
    int dilation;
    int arrivalNumber;
    Woman(string name, int dilation, int arrivalNumber)
    {
      this->name = name;
      this->dilation = dilation;
      this->arrivalNumber = arrivalNumber;
    }
  };
 
  int arrivalCounter;
  
  unordered_map<string, Woman> WomanMap;
  map<int, Woman> DilationQueue[100 - 30 + 1];
  
  inline int queueIndex(int dilation)
  {
    return (dilation - 30);
  }
  
public:
  DeliverySuite() { arrivalCounter = 0; }
  void ArrivalAtHospital(string womanName, int dilation);
  void UpdateDilation(string womanName, int increaseDilation);
  void GiveBirth(string womanName);
  string Query();
};

// O(logN)
void DeliverySuite::ArrivalAtHospital(string womanName, int dilation)
{
  ++arrivalCounter;
  Woman w(womanName, dilation, arrivalCounter);
  WomanMap.insert(make_pair(womanName, w)); // O(1)
  DilationQueue[queueIndex(dilation)].insert(make_pair(arrivalCounter, w)); // O(logN)
}

// O(logN)
void DeliverySuite::UpdateDilation(string womanName, int increaseDilation)
{
  // get reference from WomanMap as we want to modify its dilation later
  Woman &w = WomanMap.find(womanName)->second; // O(1)
  
  // get a copy from DilationQueue as we want to erase it later (auto destroyed by map)
  Woman w2 = DilationQueue[queueIndex(w.dilation)].find(w.arrivalNumber)->second; // O(logN)
  // erase from old position/queue in dilation queue
  DilationQueue[queueIndex(w2.dilation)].erase(w2.arrivalNumber); // O(logN)
  
  // update dilation
  w.dilation += increaseDilation;
  w2.dilation += increaseDilation;
  
  // reinsert into dilation queue at new index
  DilationQueue[queueIndex(w2.dilation)].insert(make_pair(w2.arrivalNumber, w2)); // O(logN)
}

// O(logN)
void DeliverySuite::GiveBirth(string womanName)
{
  Woman &w = WomanMap.find(womanName)->second; // O(1)
  // erase from both map and dilation queue
  DilationQueue[queueIndex(w.dilation)].erase(w.arrivalNumber); // O(logN)
  WomanMap.erase(womanName); // O(1)
}

// O(1)
string DeliverySuite::Query()
{
  string strToReturn = "The delivery suite is empty";
  
  if(!WomanMap.empty())
  {
    // max 71 iterations, which is CONSTANT and very small compared to number of women, thus O(1) for loop
    for(int i = queueIndex(100); i >= queueIndex(30); i--)
    {
      if(!DilationQueue[i].empty())
      {
        strToReturn = DilationQueue[i].begin()->second.name; // O(1)
        break;
      }
    }
  }
  
  return strToReturn;
}

int main()
{
  DeliverySuite ds;
  int CMD, cmdCnt=0, cmdInput, dilationVal;
  string name;
  
  cin >> CMD;
  while(cmdCnt++ < CMD)
  {
    cin >> cmdInput;
    switch(cmdInput)
    {
      case 0:
        cin >> name >> dilationVal;
        ds.ArrivalAtHospital(name, dilationVal);
        break;
        
      case 1:
        cin >> name >> dilationVal;
        ds.UpdateDilation(name, dilationVal);
        break;
      
      case 2:
        cin >> name;
        ds.GiveBirth(name);
        break;
        
      case 3:
        cout << ds.Query() << endl;;
        break;
    }
  }
  
  return 0;
}