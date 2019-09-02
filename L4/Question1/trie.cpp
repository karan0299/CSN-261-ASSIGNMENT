#include <bits/stdc++.h>
#include "QString"
#include "trie.h"
#include "QDebug"
using namespace std;


node * initialize(){
    node * newNode = new (struct node);
    newNode->meaning = "";
    for (int i = 0; i < 26; i++)
        newNode->child[i] = NULL;
    return newNode;
}


bool Trie:: insert(node *root, QString word , QString meaning) {

        node * curr = root;

        for (int i = 0; i < word.length(); i++) {
            QChar c = word.at(i);
            int ascii = c.toLatin1();
            int alpha = ascii - 97;
            if (curr->child[alpha] == NULL){
                curr->child[alpha] = initialize();
            }
            curr = curr->child[alpha];
        }

        if(curr->meaning==meaning){
            qDebug()<<"This word's meaning already exists";
            return false;
        }

        curr->meaning=meaning;

        return true;
}


QString Trie:: getMeaning( node * root, QString word1 ){
        string str = word1.toStdString();
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        QString word = QString::fromStdString(str);
        node * curr = root;
        for (int i = 0; i < word.length(); i++) {
            QChar c = word.at(i);
            int ascii = c.toLatin1();
            int alpha =ascii - 97;
            curr = curr->child[alpha];
            if(curr== NULL){
                return "";
            }
        }
        return curr->meaning;
}

void Trie:: loadDataInTrie() {
    qCritical()<< "C++ Style Info Message";
    ifstream file ( "/home/kps/Desktop/csn-261/L4/Question1/input_file.csv" );
    qCritical()<< "C++ Style Info Message";
    string value;
     qCritical()<<file.good();
    while ( file.good() )
    {
         qCritical()<< "C++ Style Info Message";
         getline ( file, value, '\n' );
         int pos = value.find(",");
         transform(value.begin(), value.end(), value.begin(), ::tolower);
         qDebug()<<pos;
         string firstWord = value.substr(0,pos);
         string remain = value.substr(pos+1);
         QString word = QString::fromStdString(firstWord);
         QString meaning = QString::fromStdString(remain);
         insert(word,meaning);
    }
}

