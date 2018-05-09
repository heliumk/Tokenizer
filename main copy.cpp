#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TokenFreq{        //stores a token 'word' and the number of occurences of this word as an integer FUNCTIONAL
    string token;
    int freq = 1;
};

string shortenSpace( string str );        //function declarations
string toLowerCase( string str );
void matrixInit(  vector< vector<int> >&, int numRows, int numCols );
void getTokenFreqVec( const string & istr , vector<TokenFreq> & tfVec );
void selectionSort( vector<TokenFreq> & tfVec );
void insertionSort( vector<TokenFreq> & tfVec );

int main(){
    string istr = "And no, I'm not   a walking C++ dictionary. I do not keep every technical detail in my head at all times. If I did that, I would be a much poorer programmer. I do keep the main   points straight in my head   most of the time, and I do know where to find the details when I need them. by Bjarne Stroustrup";       //*test for Tokenizer*
    vector<TokenFreq> tfVec(0);
    getTokenFreqVec(istr, tfVec);
    
    for (unsigned int i = 0; i < tfVec.size(); ++i){           //*test* prints contents of tfVec, 1d vector
        cout<<"["<<i<<"] (token = '"<<tfVec[i].token<<"', freq = "<<tfVec[i].freq<<")"<<endl;
    }
    //selectionSort( tfVec );         //*testfor selection
   // for (unsigned int i = 0; i < tfVec.size(); ++i){
        //cout<<"["<<i<<"] (token = '"<<tfVec[i].token<<"', freq = "<<tfVec[i].freq<<")"<<endl;       //prints
    //}
    //insertionSort( tfVec );
    //for (unsigned int i = 0; i < tfVec.size(); ++i){
       // cout<<"["<<i<<"] (token = '"<<tfVec[i].token<<"', freq = "<<tfVec[i].freq<<")"<<endl;       //prints
    //}
    
    return 0;
}

void matrixInit( vector< vector<int> >& matrix, int numRows, int numCols){ //initializes matrix with specified rows and columns, FUNCTIONAL
    for(int i = 0; i < numRows; i++){
        matrix.push_back(vector<int>(numCols, 0));      //each row gets numCols columns
    }
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
            matrix[i][j] = i*j;
        }
    }
}

void getTokenFreqVec(const string & istr, vector<TokenFreq> & tfVec){//tokenizer of istr, tfVec stores tokens, passed by reference
        string str = istr;
        str = shortenSpace(istr);                  //removes spaces and converts uppercase to lower
        str = toLowerCase(str);
        TokenFreq word;
        int curr_beg=0;                         //curr_beg and curr_end are identiers of start and end of token, where to use substring
        unsigned int curr_end=0;
        curr_end = str.find(' ');       //sets end to first space
        while(str.find(' ', curr_end+1) != -1){
            if(curr_end != -1){        //if space isnt outside string
                word.token = str.substr(curr_beg, curr_end-curr_beg);
                cout<<word.token<<endl;
                int found = 1;
                for(unsigned int i = 0; i < tfVec.size(); i++){ // If tfVec contains the frequency for token
                    if(!tfVec[i].token.compare(word.token) ){        //compares recently tokenized string to contents of tfVec
                        tfVec[i].freq += 1; // Increment frequency if found within tfVec
                        found = 0;
                    }
                }
                if(found){          //if found = 0(token was not already inside tfVec), token is added to tfVec
                    tfVec.push_back(word);
                }
                curr_end = str.find(' ', curr_end+1);
                cout<<curr_end<<endl;
            }
            //cout<<curr_beg<<endl;
    }
}

void selectionSort( vector<TokenFreq> & tokFreqVector ){        //selection ascending order
    int min;
    unsigned int i;
    unsigned int j;
    TokenFreq tok;
    for(i = 0; i < tokFreqVector.size() - 1; i++){
        min = i;
        for(j = i + 1; j < tokFreqVector.size(); j++){
            if(tokFreqVector[j].freq < tokFreqVector[min].freq){ // Swap values if new minimum element is found
                tok = tokFreqVector[min];
                tokFreqVector[min] = tokFreqVector[j];
                tokFreqVector[j] = tok;
            }
        }
    }
}

void insertionSort( vector<TokenFreq> & tfVec ){        //insertion descending order
    unsigned int i;
    int j;
    TokenFreq tok;
    for(i = 1; i < tfVec.size(); i++){
        tok = tfVec[i];
        for(j = i - 1; j >= 0 && tfVec[j].freq < tok.freq; j--)
            tfVec[j + 1] = tfVec[j];
        tfVec[j + 1] = tok;
    }
}

string shortenSpace( string str ){//removes excess spaces in string, called in getTokenFreqVec
    int found =0;
    while(isspace(str.at(0))){    //deletes any white spaces at the beginning of text
        str.erase(0,1);
    }
    while(isspace(str.back())){    //deletes any white spaces at the beginning of text
        str.pop_back();
    }
    found = str.find(' ');
    while(found != -1){
        while (str.at(found+1) == (' ')){
            str.erase(found,1);
        }
        found = str.find(' ', found+1);
    }
    return str;
}

string toLowerCase( string str ){               //all string uppercase to lowercase, called in getTokenFreqVec FUNCTIONAL
    for(unsigned int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

