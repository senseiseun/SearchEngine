//
// Created by Seun Suberu on 12/16/22.
//

#include "UserInterface.h"
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/istreamwrapper.h"
#include <fstream>

void UserInterface::start() {
    cout << "||=================Seun's Search Engine====================||" << endl;
}

void UserInterface::clearConsole() {
    for(int i = 0; i < 50; i++){
        cout << endl;
    }
}

void UserInterface::runQuery(AVLTree<Word>& words, HashMap<string, Author*>& authors, HashMap<string, Article*>& articles, char* directory) {
    bool search = true;
    while (search) {
        cout << "Number of accessible authors : " << authors.getSize() << endl;
        //    cout << "number of words that are stops : " << stopWords.getSize() << endl;
        cout << "Available keywords: AND, OR, NOT, AUTHOR" << endl;
        cout << "Please enter your search query:" << endl;

        string line;
        getline(cin, line);
        vector<string> res = QueryProcessor::processQuery(words, authors, articles, line);
        string dir(directory);
        outputQueryResult(res, articles, dir);

        cout << "\nWould you like to search again?" << endl;
        cout << "Y / N, clear, or print persistant file (PRINT): " << endl;
        string decision;
        cin.clear();
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

void UserInterface::outputQueryResult(vector<string> &res, HashMap<string, Article*>& articles, string& directory) {
    for (int i = 0; i < 5 && i < res.size(); i++) {
        Article* article = articles[res.at(i)];
        cout << "\n" << (i+1) << ". " << article->getTitle() << " " << endl;
        vector<string>* authors = article->getAuthors();
        cout << "\tWritten by: ";
        if (authors != nullptr) {
            for (string& author : *authors) cout << author << " ";
        }
        cout << endl;
        string empty;
        string preview = retrivePreview(res.at(i), directory);
        for (int count = 0; count < 300; count += 75) {
            empty.append("\t" + preview.substr(count, count+75) + (count == 225 ? "..." : "\n"));
        }
        cout << empty << endl;
    }
}

void UserInterface::endQuery() {
    cout << "||=================Seun's Search Engine====================||" << endl;
}

using namespace rapidjson;
string UserInterface::retrivePreview(string& doc, string& directory) {
    std::ifstream ifs{directory + "/" + doc + ".json"};
    if (!ifs.is_open()) {
        std::cerr << "Could not open file for reading!\n";
        return "";
    }
    IStreamWrapper isw{ifs};
    Document d;
    d.ParseStream(isw);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    string output;
    for (int i = 0; i < d["abstract"].GetArray().Size(); i++) {
        string res = d["abstract"].GetArray()[i]["text"].GetString();
        output.append(res.substr(0, 300));
        if (output.length() >= 300) return output;
    }
    for (int i = 0; i < d["body_text"].GetArray().Size(); i++) {
        string res = d["body_text"].GetArray()[i]["text"].GetString();
        output.append(res.substr(0, 300));
        if (output.length() >= 300) break;
    }
    return output;
}