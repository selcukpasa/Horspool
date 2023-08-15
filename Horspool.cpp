#include "Horspool.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstdint>

using namespace std;

class HorspoolImpl : public Horspool
{
public:
    void setPattern(const std::string& pat)
    {
        pattern_ = pat;
        patternLength_ = pat.length();
        //shifTable_.clear() um die Liste jedes mal bei der neukompilierung zu leeren
        shiftTable_.clear();
        //jedem Buchstaben(key) wird ein Wert zugewissen. Hier Patternlaenge - Index - 1 
        for (size_t i = 0; i <= patternLength_ - 1; ++i)
        {
            shiftTable_[pattern_[i]] = patternLength_ - i - 1;
        }
    }

    const std::string& getPattern() const
    {   
        //Hier soll nur der Pattern ausgegeben werden
        return pattern_;
    }

    std::vector<size_t> getHits(const std::string& text) const
    {
        std::vector<size_t> hits;
        //Zeiger auf welchem Index im Text wir uns befinden
        size_t textPos = 0;
        //Solange die Position nicht kleiner/gleich Textlaenge - Patternlaenge ist
        while (textPos <= text.length() - patternLength_)
        {
            //Zeiger fuer die Position im Pattern
            size_t patternPos = patternLength_ - 1;
            //Solange Position kleiner als 0 und der letzte Char von Pattern mit dem Char im Index vom Text übereinstimmt wird patternPos dekrementiert
            while (patternPos > 0 && pattern_[patternPos] == text[textPos + patternPos])
            {
                --patternPos;
            }
            //Wenn patternPos 0 ist wurde ein Treffer festgestellt und wird hinten an hits eingefuegt. Danach wird um eine Patternlaenge geshiftet
            if (patternPos == 0)
            {
                hits.push_back(textPos);
                textPos += patternLength_;
                //cout << textPos << endl;
            }
            //Falls kein Treffer, dann soll geshiftet werden
            else
            {
                textPos += getShift_(text[textPos + patternLength_ - 1]);
                //cout << textPos << endl;
            }
        }
        //Ausgegeben wird die Liste mit Treffern
        return hits;
    }

protected:
    //Falls Char nicht mit dem letzten Key aus der Shifttabelle uebereinstimmt, wird der Wert des jeweiligen Keys zuruekgegeben 
    uint32_t getShift_(const char last_char) const
    {
        auto it = shiftTable_.find(last_char);
        if (it != shiftTable_.end())
        {

            return it->second;
        }
        else
        {
            //Sonst wird die Patternlaenge uebergeben
            return patternLength_;
        }
    }

private:
    std::string pattern_;
    size_t patternLength_;
    std::unordered_map<char, uint32_t> shiftTable_;
};

/* int main()
{
    HorspoolImpl horspool;

    horspool.setPattern("TOOTH");
    const std::string text = "TRUSTHARDTOOTHBRUSHES";
    std::vector<size_t> hits = horspool.getHits(text);

    cout << "Pattern: " << horspool.getPattern() << std::endl;
    std::cout << "Text: " << text << endl;
    std::cout << "Hits: ";
    for (size_t hit : hits)
    {
        std::cout << hit << " ";
    }
    std::cout << std::endl;

    return 0;
}*/
