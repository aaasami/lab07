#include "WordCount.h"
#include <iostream>
#include <sstream>
#include "tddFuncs.h"
using namespace std;

int main() {
    cout << "Testing..." << endl;

    WordCount wc1;

    ASSERT_EQUALS(0, wc1.getWordCount("hello"));

    wc1.incrWordCount("hello");
    ASSERT_EQUALS(1, wc1.getWordCount("hello"));
    wc1.incrWordCount("hello");
    ASSERT_EQUALS(2, wc1.getWordCount("hello"));
    wc1.incrWordCount("homework");
    ASSERT_EQUALS(1, wc1.getWordCount("homework"));

    std::string text = "This is a WordCount test. Test is good.";
    std::istringstream iss(text);
    WordCount wc2;
    wc2.addAllWords(text);

    ASSERT_EQUALS(1, wc2.getWordCount("this"));
    ASSERT_EQUALS(2, wc2.getWordCount("is"));
    ASSERT_EQUALS(1, wc2.getWordCount("a"));
    ASSERT_EQUALS(1, wc2.getWordCount("WordCount"));
    ASSERT_EQUALS(2, wc2.getWordCount("test"));
    ASSERT_EQUALS(1, wc2.getWordCount("good"));

    //dumpWordsSortedByWord
    std::ostringstream ws;
    wc2.dumpWordsSortedByWord(ws);
    std::string resultWS = "wordcount,1\nthis,1\ntest,2\nis,2\ngood,1\na,1\n";
    ASSERT_EQUALS(resultWS, ws.str());

    // dumpWordsSortedByOccurence
    std::ostringstream os;
    wc2.dumpWordsSortedByOccurence(os);
    std::string resultOS = "a,1\ngood,1\nthis,1\nwordcount,1\nis,2\ntest,2\n";
    ASSERT_EQUALS(resultOS, os.str());

    cout << "All tests passed." << endl;
    return 0;
}
