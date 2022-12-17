//
// Created by Seun Suberu on 12/16/22.
//

#include "UserInterface.h"

void UserInterface::start() {
    cout << "Seun's Search Engine" << endl;
    cout << "||========================================||" << endl;
}

void UserInterface::clearConsole() {
    for(int i = 0; i < 50; i++){
        cout << endl;
    }
}

void UserInterface::runQuery(AVLTree<Word>& words, HashMap<string, Author*>& authors, HashMap<string, Article*>& articles) {
    bool search = true;
    while (search) {
        cout << "Number of accessible authors : " << authors.getSize() << endl;
        //    cout << "number of words that are stops : " << stopWords.getSize() << endl;
        cout << "Available keywords: AND, OR, NOT, AUTHOR" << endl;
        cout << "Please enter your search query:" << endl;

        string line;
        getline(cin, line);
        QueryProcessor qp;
        vector<string> res = qp.processQuery(words, authors, line);
        outputQueryResult(res, articles);

        cout << "\nWould you like to search again?" << endl;
        cout << "Y / N, clear, or print persistant file (PRINT): " << endl;
        string decision;
        cin.ignore();
        while (true) { //loop that waits for a Y/N/clear command. anything else returns invalid.
            getline(cin, decision);
            if (decision == "PRINT" || decision == "print" || decision == "Print") {
                cout << "\nWould you like to search again?" << endl;
                cout << "Y / N:" << endl;
            } else if (decision == "clear") {
                clearConsole();
                cout << "\nWould you like to search again?" << endl;
                cout << "Y / N:" << endl;
            } else if (decision == "Yes" || decision == "y" || decision == "yes" || decision == "YES" || decision == "Y"){
                break;
            }
            else if (decision == "N" || decision == "no" || decision == "No" || decision == "n") {
                search = false;
                break;
            } else {
                cout << "\nInvalid command. Please enter Y / N : \n";
            }
        }
    }
}

void UserInterface::outputQueryResult(vector<string> &res, HashMap<string, Article*>& articles) {
    for (int i = 0; i < 5 && i < res.size(); i++) {
        cout << res.at(i) << endl;
        Article* article = articles[res.at(i)];
        cout << article->getTitle() << " " << endl;
        vector<string>* authors = article->getAuthors();
        if (authors != nullptr) {
            for (string author : *authors) cout << author << " ";
        }
        cout << endl;
    }
}

void UserInterface::endQuery() {
    cout << "||========================================||" << endl;
}