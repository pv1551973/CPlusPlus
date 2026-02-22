#include <string>
#include <vector>
#include <utility>
#include <random>
#include <iterator>
#include <functional>
#include <algorithm>
#include <ios>
#include <type_traits>
#include <cmath>
#include <iostream>

using std::string;
using std::vector;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::distance;
using std::next;
using std::advance;
using std::find;
using std::function;
using std::boolalpha;
using std::for_each;
using std::cout;
using std::endl;

size_t findMaxSubSq(string& s, const string& sRef1, const string& sRef2)
{
  struct pos_data
  {
    char c;
    int froPos;
    int toPos;
  };
  using sequence = vector<pos_data>;
  using VS = vector<sequence>;
  VS vecSeq;

  //lambda to check if the characters are the same
  //in both the strings
  auto checkForAllSameCharsInFroTo = [&]()->bool
  {
    auto c = sRef1.at(0);
    auto chk1 = (sRef1.find_first_not_of(c) == std::string::npos);
    auto chk2 = (sRef2.find_first_not_of(c) == std::string::npos);

    return(chk1 && chk2);
  };

  auto flag = sRef1.length() == sRef2.length();

  //lambda to the find the longest sequence common
  //to both the strings
  auto fndLngstSeq = [&]()->void
  {
    //vector that stores all the matches encountered during a single
    //iteration of the inner loop while(iterSRef2 != sRef2.end())
    vector<pos_data>vMtchs;
    //so that we could store new sequences
    //discovered during an iteration of the 
    //inner loop while(iterSRef2 != sRef2.end()),
    //which could be pushed back to vecSeq
    //this is so as not to invalidate
    //iterators of vecSeq during the 
   //iteration
   VS tmpVecSeq;

   //a flag to check whether a particular
   //sequence was amended
   bool wasSeqChanged = false;

   //a flag to check whether a new
   //sequence was found
   bool wasNuSeqFnd = false;

   //a temporary store for the
   //changed sequence
   sequence changedS;

    //lambda to compare an element of vMtchs to a given
    //sequence within vecSeq for a given iteration of the  
   //inner loop while(iterSRef2 != sRef2.end())
    auto cmpMtchstoASeq = [&](VS::iterator& refToIterForASeq, const pos_data& crPD)->void
    {
      //data for inserting into the existing sequence
      int idxInS;

      //where does a new sequence diverge from existing sequence?
      int idxNuS;

      //for the sake of debugging
      //auto const& crVMtchs = vMtchs;

      //a debug aid
      //string currASeq;

     auto cmp = [&]()->unsigned short
     {
       auto aSeq = *refToIterForASeq;
       auto sqSz = aSeq.size();
       auto iterB = aSeq.begin();
       auto iterE = aSeq.end();

       //to keep track of which character in the sequence
       //we are looking at
       auto innerLoop = 0;
       //checks
       auto check1 = false;
       auto check2 = false;
       //a peculiar condition exists
       //wherein sqSz is 1
       //in such case we need check3
       //to be set to true by default
       //so that the processing logic
       //works as expected 
       auto check3 = true;
       auto check4 = false;
       auto check5 = false;

       while((size_t)innerLoop != sqSz)
       {
        auto iterC = iterB;
        auto nextPos = innerLoop + 1;
        //next position
        auto iterN = iterC;

        iterC += innerLoop;

        //does this match a previously matched toPos?
        check1 = (crPD.froPos > iterC->froPos && crPD.toPos == iterC->toPos);
        //it makes no logical sense to continue with
        //the loop if check1 turns out to be true
        if(check1){break;}

        //does this match come after the current iterator position?
        check2 = (crPD.froPos > iterC->froPos && crPD.toPos > iterC->toPos);

        //if check2 is valid, then we need to check if the match can be 
        //inserted into the sequence
        if(check2)
        {
          iterN += nextPos;
          while(iterN != iterE && (size_t)nextPos != sqSz)
          {
            check3 = (crPD.froPos > iterN->froPos && crPD.toPos > iterN->toPos);
            if(!check3)
            {
              //check3 is false
              break;
            }
            ++nextPos; 
            iterN = iterC;
            iterN += nextPos;
          }
          if(iterN != iterE && !check3)
          {
            //check3 is false
            //either this is a potential insert
            //or a potential new sequence
            check4 = (crPD.froPos < iterN->froPos && crPD.toPos < iterN->toPos);
            check5 = (crPD.froPos > iterN->froPos && crPD.toPos <= iterN->toPos) || (crPD.froPos == iterN->froPos && crPD.toPos > iterN->toPos);
            if(check4)
            {
              idxInS = distance(iterB,iterN);
            }
            if(check5)
            {
              idxNuS = distance(iterB,iterN);
            }

          }
        }
        else
        {
          //check2 is false
          //this would invariably imply that check3
          //is true
          //in fact check4 would invariably be false here
          //as check2 itself is false
          //that should leave us with the only possibility of
          //check5
         check5 = (crPD.froPos > iterC->froPos && crPD.toPos <= iterC->toPos) || (crPD.froPos == iterC->froPos && crPD.toPos > iterC->toPos);
            if(check5)
            {
              idxNuS = distance(iterB,iterC);
            }
        }
        //we don't need to continue with the 
        //loop if either check3 or check4 or check5
        //is true
        if(check3 || check4 || check5){break;}
        ++innerLoop;
      }
        if(check1){return 0;}//no effect
        if(check2 && check3){return 1;}//push back
        if(check2 && !check3 && check4){return 2;}//insert
        if((check2 && !check3 && check5) || (!check2 && check3 && check5)){return 3;}//new sequence

       return 0;
     };

     auto result = cmp();
     switch(result)
     {
       case 0:
       {
         //no impact
       }
       break;
       case 1:
       {
         //push_back
         auto aSeq = *refToIterForASeq;
         aSeq.push_back(crPD);
         wasSeqChanged = true;
         changedS = aSeq;
       }
         break;
         case 2:
         {
           //insert
           auto aSeq = *refToIterForASeq;
           auto iter = aSeq.begin();
           advance(iter,idxInS);
           aSeq.insert(iter,crPD);
           wasSeqChanged = true;
           changedS = aSeq;
         }
         break;
         case 3:
         {
           //based on debugging, there exists the 
           //probability that a given crPD might 
           //result in the same new sequence being
           //pushed on to the tmpVecSeq, for multiple
           //sequences from within vecSeq
           //the below lambda averts this erroneous probablity
           auto chkDupNuSeq = [&](const sequence& crSeq)->bool
           {
             auto isDuplicateSeq = false;

             auto cmpPdEq = [&] (const pos_data& crPD1, const pos_data& crPD2)->bool
             {
               if(crPD1.froPos == crPD2.froPos && crPD1.toPos == crPD2.toPos && crPD1.c == crPD2.c)
               {
                 return true;
               }
               return false;
             };

             auto cmpSeq4Eq = [&](const sequence& crSeq1, const sequence& crSeq2)->void
             {
               if(crSeq1.size() != crSeq2.size()){return;}

               auto iter1B = crSeq1.begin();
               auto iter1E = crSeq1.end();
               auto iter2B = crSeq2.begin();
               auto iter2E = crSeq2.end();

               while(iter1B != iter1E && iter2B != iter2E)
               {
                 if(cmpPdEq(*iter1B,*iter2B))
                 {
                   ++iter1B;
                   ++iter2B;
                   continue;
                 }
                 break;
               }

               if(iter1B == iter1E && iter2B == iter2E){isDuplicateSeq = true;}

               return;
             };

             for(auto aSeq : tmpVecSeq)
             {
               cmpSeq4Eq(aSeq,crSeq);
               if(isDuplicateSeq){break;} 
             }
             return isDuplicateSeq;
           }; 
           //new sequence
           auto origSeq = *refToIterForASeq;
           auto iterOrigB = origSeq.begin();
           auto iterOrigC = iterOrigB;
           advance(iterOrigC,idxNuS);
           sequence seqNu;
           auto iterNu = iterOrigB;
           while(iterNu != iterOrigC)
           {
             seqNu.push_back(*iterNu);
             ++iterNu;
           }
           seqNu.push_back(crPD);
           if(!tmpVecSeq.empty())
           {
            if(false == chkDupNuSeq(seqNu))  
            {
              tmpVecSeq.push_back(seqNu);
              wasNuSeqFnd = true;
            }
           }
           else
           {
             //tmpVecSeq is empty
             tmpVecSeq.push_back(seqNu);
             wasNuSeqFnd = true;
           }
         }
         break;
         default:
         {
         }
         break;
       }
    };

    //lambda to update vecSeq with any possible new
    //sequences
    auto amendVecSeq = [&]()->void
    {
      for(auto seq: tmpVecSeq)
      {
        vecSeq.push_back(seq);
      }
      tmpVecSeq.clear();
      wasNuSeqFnd = false;
    };

    //lambda that generalizes the processing logic
    //irrespective of sRef1 > sRef2 or vice versa
    auto procLg = [&](string& rStrOut, const string& crStrLesser, const string& crStrLarger)->void
    {
      auto iterStrLesserB = crStrLesser.begin();
      auto iterStrLesserE = crStrLesser.end();
      auto iterStrLargerB = crStrLarger.begin();
      auto iterStrLargerE = crStrLarger.end();

      auto iterStrLssr = iterStrLesserB;
      //we use this local variable to remember
      //the last true state of wasNuSeqFnd
      //since it may get overwritten during succesive
      //iterations of the do-while loop below
      auto cloneWasNuSeqFnd = false;

      while(iterStrLssr != iterStrLesserE)
      {

        auto iterStrLrgr = iterStrLargerB;

        while(iterStrLrgr != iterStrLargerE)
        {
          if(*iterStrLrgr == *iterStrLssr)
          {
            //for succesive matches to the same
            //character in the compared to string,
            //we only take only the latest into
            //consideration, and remove the previous
            pos_data pd;
            pd.froPos = distance(iterStrLesserB,iterStrLssr);
            pd.toPos = distance(iterStrLargerB,iterStrLrgr);
            pd.c = *iterStrLssr;
            vMtchs.push_back(pd);
          }
          ++iterStrLrgr;
        }
        if(!vMtchs.empty())
        {
          if(!vecSeq.empty())
          {
            //Algorithm
            //a) fetch each existing sequence from
            //vecSeq
            //b) compare vMtches against the sequence
            //and amend if necessary
            //c) create a new sequence if necessary and 
            //push it back on to vSeq 

           for(auto pd: vMtchs)
           {
            auto iterVecSeqE = vecSeq.end();
            auto iterVecSeqC = vecSeq.begin();
            do
            {
                cmpMtchstoASeq(iterVecSeqC,pd);
                if(wasSeqChanged)
                {
                  *iterVecSeqC = changedS;
                  wasSeqChanged = false;
                  changedS.clear();
                }
                if(wasNuSeqFnd)
                {
                  //if a new sequence was found
                  //remember the state
                  cloneWasNuSeqFnd = wasNuSeqFnd;
                }
            }while(++iterVecSeqC != iterVecSeqE);
           }
          }
          else
          {
            //the match is guranteed to be a single character
            //so can confidently push back
            sequence s;
            auto pd = vMtchs.at(0);
            s.push_back(pd);
            vecSeq.push_back(s);
          }
          //amend vecSeq if needed
          //based on the remembered
          //state
          if(cloneWasNuSeqFnd)
          {
            amendVecSeq();
            //align the cloned state with 
            //the original state
            cloneWasNuSeqFnd = false;
          }
        }
        if(!vMtchs.empty()){vMtchs.clear();} 
        ++iterStrLssr;
      }
      //locate the longest sequence within vecSeq
      auto idx = 0;
      size_t sz = 0;
    
      auto iterB = vecSeq.begin();
      auto iterCurr = iterB;
      sz = iterCurr->size();
      while(++iterCurr != vecSeq.end())
      {
        if(iterCurr->size() > sz)
        {
          sz = iterCurr->size();
          idx = distance(iterB,iterCurr);
        }
      }

      auto seqV = vecSeq[idx];

      for(auto pd : seqV)
      {
        rStrOut += pd.c;
      }
      
      return;
    };

    flag = sRef1.length() > sRef2.length();

    if(flag)
    {
      procLg(s,sRef2,sRef1);
    }
    else
    {
      procLg(s,sRef1,sRef2);
    }
    return;
  };

  if(flag)
  {
    auto iter1 = sRef1.begin();
    auto iter2 = sRef2.begin();
    s.clear();

    do
    {
      if(*iter1 == *iter2)
      {
        s.push_back(*iter1);
      }
      ++iter1;
      ++iter2;
    }while(iter1 != sRef1.end());

    return(s.size());
  }
  else if(checkForAllSameCharsInFroTo())
  {
    flag = sRef1.length() > sRef2.length();
    if(flag)
    {
      s.clear();
      s.assign(sRef2);
    }
    else
    {
      s.clear();
      s.assign(sRef1);
    }

    return(s.size());
  }
  else
  {
    fndLngstSeq(); 
  }

  return (s.size());
}

void makeStr(string& s, int numChars)
{
  char alphabets[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

  auto const distRng = sizeof(alphabets)/sizeof(alphabets[0]);
  s.clear();

  random_device rd;
  mt19937 gen(rd());
  //uniform_int_distribution<> distrib(0,numChars);
  uniform_int_distribution<> distrib(0, distRng - 1);

  for(auto count = 0; count < numChars; ++count)
  {
    auto idx = distrib(gen);
    s.push_back(alphabets[idx]);
  }

  return;
}

int func() 
{
  string s1;
  string s2;
  string sCmn;

  //constexpr unsigned sz1 = 10;
  //constexpr unsigned sz2 = 7;
  //constexpr unsigned sz1 = 20;
  //constexpr unsigned sz2 = 15;
  //constexpr unsigned sz1 = 40;
  //constexpr unsigned sz2 = 35;

  //makeStr(s1,sz1);
  //makeStr(s2,sz2);
  //s1 = "abcjklp";
  //s2 = "acjkp";
  //s1 = "papmretkborsrurgtina";
  //s2 = "nsnupotstmnkfcfavaxgl";
  //s1 = "hofubmnylkra";
  //s2 = "pqhgxgdofcvmr";
  //s1 = "ezupkr";
  //s2 = "ubmrapg";
  //s1 = "abcde";
  //s2 = "efcdgh";
  //s1 = "aecefurmkk";
  //s2 = "uvtyqlbkjeko";
  //s1 = "ogppozgixxiqyzjtdzamhcgsltuulx";
  //s2 = "pvgbykfqoxvevrdykahwdfmmw";
  //s1 = "almccekzip";
  //s2 = "zvtayfm";
  //s1 = "mevwemabuz";
  //s2 = "kkqwsgd";
  //s1 = "qvoqrtotlo";
  //s2 = "zqoeygh";
  //s1 = "uqkijdshph";
  //s2 = "uvofqnn";
  //s1 = "klfujgcuscklqqtksxyglcqqvwqhtl";
  //s2 = "vwtlhdnqsnrblkdmgjqcwqc";
  //s1 = "oxcpqrsvwf";
  //s2 = "shmtulqrypy";
  //s1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  //s2 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  //s1 = "pmjghexybyrgzczy";
  //s2 = "hafcdqbgncrcbihkd";
  //s1 = "abcde";
  //s2 = "ace";
  //s1 = "ylqpejqbalahwr";
  //s2 = "yrkzavgdmdgtqpg"; 
  //s1 = "mhunuzqrkzsnidwbun";
  //s2 = "szulspmhwpazoxijwbq";
  //s1 = "papmretkborsrurgtina";
  //s2 = "nsnupotstmnkfcfavaxgl";
  //s1 = "jgtargjctqvijshexyjcjcre";
  //s2 = "pyzazexujqtsjebcnadahobwf";
  s1 = "yfobudkbgpqtadspgvinafefktctinyvgf";
  s2 = "kpurgrihwbkjsrybmnqrgnubufebatwberi";

  cout << "s1 = " << s1 << endl;
  cout << "s2 = " << s2 << endl;

  auto sCmnSz = findMaxSubSq(sCmn,s1,s2);

  if(sCmnSz)
  {
    cout << "longest common sub-sequence = " << sCmn << endl;
    cout << "length of longest common sub-sequence = " << sCmnSz << endl;
  }
  else
  {
    cout << "No common substring" << endl;
  }

	return 0;	
}

int main() {
    auto exit = (int (*)()) &func;
    
    std::cout << exit() << std::endl;
}
