#include<bits/stdc++.h>
#include"header.hpp"

using namespace std;

void storeSubstCiph(int noOfChars, char ciph2[], char ciphertext[], char key[]){
    ciph2[noOfChars+1];
        for(int ii=0;ii<=noOfChars;ii++){       //Storing ciphertext with substituted key values
                int t=0;
                for(t=0;t<26;t++){
                    if(ciphertext[ii]==key[t]){
                        ciph2[ii]=(char)(t+65);
                        break;
                    }
                }
                if(t==26)
                    ciph2[ii]=ciphertext[ii];
            }
}

void resetKey(char key[]){
    for(int i=0;i<26;i++)
        key[i]='\0';
}

int existInString(string s, char c){
    for(int i=0;i<s.length();i++)
        if(s[i]==c)
            return 1;
    return 0;
}

int permut(char key[], int noOfChars, char ciphertext[], char alph[]){
    //SWE
    int keylen=0;
    bool blank=false;
    do {
        int keyt=0;
        for(int i=0;i<26;i++)
            if(key[i]>='a'&&key[i]<='z')
                keyt++;
        if(keyt<=keylen)
            return -1;
        else
            keylen=keyt;

        if(key[0]!='\0'&&key[1]!='\0'&&key[2]!='\0'&&key[3]!='\0'&&key[4]!='\0'&&key[5]!='\0'){
            int t2=(int)(key[5]-97)+1;
            for(int ti=6;ti<26;ti++){
            while(alph[t2]==key[0]||alph[t2]==key[1]||alph[t2]==key[2]||alph[t2]==key[3]||alph[t2]==key[4]||alph[t2]==key[5]){
                        t2++;       //Skipping characters already in chosen 6 letter word
                        if(t2>=26)
                            t2=0;
                    }
                if(key[ti]=='\0'){
                    key[ti]=alph[t2];
                }
                t2++;
                if(t2>=26)
                    t2=0;
                }
                return 9;       //success
            }
        blank=false;
        char ciph2[noOfChars+1];
            for(int ii=0;ii<=noOfChars;ii++){       //Storing ciphertext with substituted key values
                int t=0;
                for(t=0;t<26;t++){
                    if(ciphertext[ii]==key[t]){
                        ciph2[ii]=(char)(t+65);
                        break;
                    }
                }
                if(t==26)
                    ciph2[ii]=ciphertext[ii];
            }

            string cipword="";
            bool flag=false;
            int uniqueCount=0;
            for(int counter=0;counter<=noOfChars;counter++){
                int cu=0;
                if(isalpha(ciph2[counter])!=0&&ciph2[counter-1]!='\\')      //Extracting word from ciphertext
                    cipword+=ciph2[counter];
                else{       //If special character
                    if(cipword=="")
                        continue;
                    ifstream dict("<file_path>");
                    if(!dict){
                        cout<<"Cannot open file";
                        return 1;
                    }
                    string word, uniqw="";
                    bool tb=false, tb2=false;
                        for(int t=0;t<cipword.length()&&!tb;t++){     //To skip words that have only capital letters
                            if(cipword[t]>='a'&&cipword[t]<='z')
                                tb=true;
                        }
                        for(int t=0;t<cipword.length()&&!tb2;t++){      //To skip words that have only lower case letters
                            if(cipword[t]>='A'&&cipword[t]<='Z')
                                tb2=true;
                        }
                    if(tb&&tb2){
                    cu=0;       //Counting unique dictionary words for each ciphertext word
                    int wt=0;
                    string matches[noOfChars];

                    while(dict>>word){
                        if(word.length()!=cipword.length()||isdigit(word[0])!=0)        //If picked up NULL word or digits
                            continue;
                        bool f=true;
                        for(wt=0; wt<word.length()&&f;wt++){        //Finding words with position of capital letters matching
                            if(cipword[wt]>=65&&cipword[wt]<=90&&cipword[wt]!=word[wt])
                            f=false;
                        }
                        if(f==true){
                            matches[cu++]=word;
                        }
                    }
                    if(cu==1){        //If unique word found
                        flag=true;
                        uniqueCount++;
                        for(int t=0;t<cipword.length();t++){
                            if(cipword[t]>='a'&&cipword[t]<='z'){
                                key[matches[0][t]-65]=cipword[t];
                            }
                        }
                    }
                    else if(cu==0)
                        return -1;
                    cipword="";
                    }
                else
                    cipword="";
                if(uniqueCount>1)
                    break;
                }
                if(flag==true)
                    break;
            }
            blank=false;
            for(int ii=0;ii<26;ii++)
                blank=(blank||(key[ii]=='\0'));
            if(blank==false)
                break;

   } while(true);
    return 9;       //9 => success
}



int main(){

    //counting number of characters in text file for array initialisation
    ifstream txtFile("<file_path>");
    int noOfChars=0;
    while(1)
    {
        if(txtFile.peek() == -1)
            break;
        if(txtFile.get() != txtFile.eof())
                    noOfChars++;
    }

    char ciphertext[noOfChars+1];

    //Reading ciphertext from file and storing it in array
    ifstream in("<file_path>");
    if(! in)
    {
        cout<<"Cannot open input file\n";
        return 1;
    }
    in.read((char *)& ciphertext,sizeof(ciphertext));


    //Counting frequency of each letter in ciphertext
    char alph[26];
    for(int j=0;j<26;j++)
        alph[j]=(char)(j+97);
    int countalp[26];
    for(int j=0;j<26;j++)
        countalp[j]=0;
    for(int j=0;j<26;j++){
        for(int k=0;ciphertext[k]!='\0';k++){
            if(ciphertext[k]==alph[j])
                countalp[j]++;
        }
    }

    //finding 5 most frequently occurring letters in ciphertext
    char freq5[5];
    int maxa=0;
    for(int j=0;j<5;j++){
        maxa=0;
        for(int k=0;k<26;k++){
            if(countalp[k]>countalp[maxa])
                maxa=k;
        }
        countalp[maxa]=-1;
        freq5[j]=alph[maxa];
    }

    //creating key array and initialising to \0
    char key[26];
    for(int i=0;i<26;i++)
        key[i]='\0';


    //using permutations in dictionary closure
    int asize = sizeof(freq5)/sizeof(freq5[0]);
    do {
        key[0]=freq5[0];        //A
        key[4]=freq5[1];        //E
        key[8]=freq5[2];        //I
        key[19]=freq5[3];       //T

        //dictionary closure
        char ciph2[noOfChars+1];
        storeSubstCiph(noOfChars, ciph2, ciphertext, key);
            string cipword="";
            bool flag=false;
            for(int counter=0;counter<=noOfChars;counter++){
                int cu=0;
                if(isalpha(ciph2[counter])!=0&&ciph2[counter-1]!='\\')      //Extracting word from ciphertext
                    cipword+=ciph2[counter];
                else{       //If special character
                    if(cipword=="")
                        continue;
                    ifstream dict("<dictionary_path>");
                    if(!dict){
                        cout<<"Cannot open file";
                        return 1;
                    }
                    string word, uniqw="";
                    bool tb=false, tb2=false;
                        for(int t=0;t<cipword.length()&&!tb;t++){     //To skip words that have only capital letters
                            if(cipword[t]>='a'&&cipword[t]<='z')
                                tb=true;
                        }
                        for(int t=0;t<cipword.length()&&!tb2;t++){      //To skip words that have only lower case letters
                            if(cipword[t]>='A'&&cipword[t]<='Z')
                                tb2=true;
                        }
                    if(tb&&tb2){
                    cu=0;       //Counting unique dictionary words for each ciphertext word
                    int wt=0;
                    while(dict>>word){
                        if(word.length()!=cipword.length()||isdigit(word[0])!=0)        //If picked up NULL word or digits
                            continue;
                        bool f=true;
                        for(wt=0; wt<word.length()&&f;wt++){        //Finding words with position of capital letters matching
                            if(cipword[wt]>=65&&cipword[wt]<=90&&cipword[wt]!=word[wt])
                            f=false;
                        }
                        if(f==true){
                            cu++;
                            uniqw=word;
                        }
                    }
                    if(cu==1){        //If unique word found
                        flag=true;
                        for(int t=0;t<cipword.length();t++){        //Modifying key
                            if(cipword[t]>='a'&&cipword[t]<='z'){
                                key[uniqw[t]-65]=cipword[t];
                            }
                        }
                        break;
                    }
                    else if(cu==0)
                        break;
                    cipword="";
                    }
                else
                    cipword="";
                }
                if(flag==true)
                    break;
            }
            if(flag==true){
                if(permut(key,noOfChars,ciphertext, alph)==9)
                    break;
                else if(permut(key,noOfChars,ciphertext,alph)==-1)
                    resetKey(key);
            }
   } while(next_permutation(freq5, freq5+asize));



    //SWE
    bool blank=false;
    do {
        if(key[0]!='\0'&&key[1]!='\0'&&key[2]!='\0'&&key[3]!='\0'&&key[4]!='\0'&&key[5]!='\0'){
            int t2=(int)(key[5]-97)+1;
            for(int ti=6;ti<26;ti++){
            while(alph[t2]==key[0]||alph[t2]==key[1]||alph[t2]==key[2]||alph[t2]==key[3]||alph[t2]==key[4]||alph[t2]==key[5]){
                        t2++;       //Skipping characters already in chosen 6 letter word
                        if(t2>=26)
                            t2=0;
                    }
                if(key[ti]=='\0'){
                    key[ti]=alph[t2];
                }
                t2++;
                if(t2>=26)
                    t2=0;
                }
                break;
            }
        blank=false;
        char ciph2[noOfChars+1];
            for(int ii=0;ii<=noOfChars;ii++){       //Storing ciphertext with substituted key values
                int t=0;
                for(t=0;t<26;t++){
                    if(ciphertext[ii]==key[t]){
                        ciph2[ii]=(char)(t+65);
                        break;
                    }
                }
                if(t==26)
                    ciph2[ii]=ciphertext[ii];
            }

            string cipword="";
            bool flag=false;
            for(int counter=0;counter<=noOfChars;counter++){
                int cu=0;
                if(isalpha(ciph2[counter])!=0&&ciph2[counter-1]!='\\')      //Extracting word from ciphertext
                    cipword+=ciph2[counter];
                else{       //If special character
                    if(cipword=="")
                        continue;
                    ifstream dict("<dictionary_path>");
                    if(!dict){
                        cout<<"Cannot open file";
                        return 1;
                    }
                    string word, uniqw="";
                    bool tb=false, tb2=false;
                        for(int t=0;t<cipword.length()&&!tb;t++){     //To skip words that have only capital letters
                            if(cipword[t]>='a'&&cipword[t]<='z')
                                tb=true;
                        }
                        for(int t=0;t<cipword.length()&&!tb2;t++){      //To skip words that have only lower case letters
                            if(cipword[t]>='A'&&cipword[t]<='Z')
                                tb2=true;
                        }
                    if(tb&&tb2){
                    cu=0;       //Counting unique dictionary words for each ciphertext word
                    int wt=0;
                    while(dict>>word){
                        if(word.length()!=cipword.length()||isdigit(word[0])!=0)        //If picked up NULL word or digits
                            continue;
                        bool f=true;
                        for(wt=0; wt<word.length()&&f;wt++){        //Finding words with position of capital letters matching
                            if(cipword[wt]>=65&&cipword[wt]<=90&&cipword[wt]!=word[wt])
                            f=false;
                        }
                        if(f==true){
                            cu++;
                            uniqw=word;
                        }
                    }
                    if(cu==1){        //If unique word found
                        flag=true;
                        for(int t=0;t<cipword.length();t++){
                            if(cipword[t]>='a'&&cipword[t]<='z'){
                                key[uniqw[t]-65]=cipword[t];
                            }
                        }
                    }
                    else if(cu==0)
                        break;
                    cipword="";
                    }
                else
                    cipword="";
                }
                if(flag==true)
                    break;
            }
            blank=false;
            for(int ii=0;ii<26;ii++)
                blank=(blank||(key[ii]=='\0'));
            if(blank==false)
                break;

   } while(true);

    //Printing
    cout<<"-----------------------------------------------------\n|";
    for(char i='A';i<='Z';i++)
        cout<<i<<"|";
    cout<<"\n-----------------------------------------------------\n|";
    for(int i=0;i<26;i++)
        cout<<key[i]<<"|";
    cout<<"\n-----------------------------------------------------";


    return 0;
}


