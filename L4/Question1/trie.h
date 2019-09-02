/** 
*@file trie.h
*@brief this  file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 04/08/19
*/


#ifndef TRIE_H
#define TRIE_H


/// structure representing the node of the tree
struct node {
    QString meaning;
    node * child[26];
};

/**
*This method will be used initialize the node s
*@author Karanpreet Singh
*@date 02/09/19
*/
node * initialize();


//!  class for Trie Structure 
/*!
  A more elaborate class description.
*/
class Trie {
    public:
        //! A class construction to initialize the root of trie
        /*!
        */
        Trie() { root = initialize(); }
        //! A public membr function to insert the node/ new data into the trie
        /*!
        \param word word whose meaning is to be stored
        \param meaning meaning of the given word
        \return bool whether inserted successfully or not
        */
        bool insert(QString word,QString meaning) {return insert(root,word,meaning); }
        //! A membr function to get value stored in trie
        /*!
        \param str string whose meaning to find
        \return QString GUI supported String
        */
        QString getMeaning(QString str) { return getMeaning(root , str); }
        //! A membr function to store the data from file into the trie
        /*!
        */
        void loadDataInTrie();
    private:
        /// pointer to root node of trie
        node * root;
        //! A private member function to insert the node/ new data into the trie
        /*!
        \param root pointer to the root node of the trie
        \param word word whose meaning is to be stored
        \param meaning meaning of the given word
        \return bool whether inserted successfully or not
        */
        bool insert(node *root,QString word,QString meaning);
        //! A private membr function to get value stored in trie
        /*!
        \param str string whose meaning to find
        \return QString GUI supported String
         \param curr pointer to the node of the trie
        */
        QString getMeaning(node * curr, QString st);
};

#endif // TRIE_H
