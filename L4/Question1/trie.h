#ifndef TRIE_H
#define TRIE_H



struct node {
    QString meaning;
    node * child[26];
};

node * initialize();

class Trie {
    public:
        Trie() { root = initialize(); }
        bool insert(QString word,QString meaning) {return insert(root,word,meaning); }
        QString getMeaning(QString str) { return getMeaning(root , str); }
        void loadDataInTrie();
    private:
        node * root;
        bool insert(node *root,QString word,QString meaning);
        QString getMeaning(node * curr, QString st);
};

#endif // TRIE_H
