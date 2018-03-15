#include <bits/stdc++.h>

using namespace std;

// this version uses half the memory of the original version in deliverySuite3.cpp

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
  
  unordered_map<string, Woman*> WomanMap;
  map<int, Woman*> DilationQueue[100 - 30 + 1];
  
  inline int queueIndex(int dilation)
  {
    return (dilation - 30);
  }
  
public:
  DeliverySuite() { arrivalCounter = 0; }
  virtual ~DeliverySuite();
  void ArrivalAtHospital(string womanName, int dilation);
  void UpdateDilation(string womanName, int increaseDilation);
  void GiveBirth(string womanName);
  string Query();
};

DeliverySuite::~DeliverySuite()
{
  for (auto it = WomanMap.begin(); it != WomanMap.end(); ++it )
    delete it->second;
}

// O(logN)
void DeliverySuite::ArrivalAtHospital(string womanName, int dilation)
{
  ++arrivalCounter;
  Woman *w = new Woman(womanName, dilation, arrivalCounter);
  WomanMap.insert(make_pair(womanName, w)); // O(1)
  DilationQueue[queueIndex(dilation)].insert(make_pair(arrivalCounter, w)); // O(logN)
}

// O(logN)
void DeliverySuite::UpdateDilation(string womanName, int increaseDilation)
{
  Woman *w = WomanMap.find(womanName)->second; // O(1)
  DilationQueue[queueIndex(w->dilation)].erase(w->arrivalNumber); // O(logN)
  
  // update dilation
  w->dilation += increaseDilation;
  
  // reinsert into dilation queue at new index
  DilationQueue[queueIndex(w->dilation)].insert(make_pair(w->arrivalNumber, w)); // O(logN)
}

// O(logN)
void DeliverySuite::GiveBirth(string womanName)
{
  Woman *w = WomanMap.find(womanName)->second; // O(1)
  // erase from both map and dilation queue
  DilationQueue[queueIndex(w->dilation)].erase(w->arrivalNumber); // O(logN)
  WomanMap.erase(womanName); // O(1)
  delete w;
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
        strToReturn = DilationQueue[i].begin()->second->name; // O(1)
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