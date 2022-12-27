//
// Created by Seun Suberu on 12/16/22.
//

#include "Index.h"
#include <dirent.h>
#include <fstream>
#include "../../rapidjson/include/rapidjson/document.h"
#include "../../rapidjson/include/rapidjson/writer.h"
#include <cctype>
#include <sstream>
#include "../../rapidjson/include/rapidjson/istreamwrapper.h"
#include "../../Util/HashSet/HashSet.h"
#include "../../Stemmer/porter2_stemmer.h"

using namespace std;
using namespace rapidjson;

int initializeStopWords(HashSet<string>& stops);
void parseBody(HashSet<string>& stopWords, AVLTree<Word>& words, istringstream& ss, string& documentID, string& documentTitle, string& firstAuthor);

int Index::build(const char* dir, HashMap<string, Author*>& authors, AVLTree<Word>& words, HashMap<string, Article*>& articles) {
    HashSet<string> stopWords;
    initializeStopWords(stopWords);
    DIR *pDIR;
    struct dirent *entry;
    int num = 0;
    pDIR = opendir(dir);
    if(pDIR) {
        cout << "Directory found!" << endl << endl;
        cout << "Loading. . ." << endl;
        entry = readdir(pDIR);
        while (entry) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                num++;
                // 1. Parse a JSON string into DOM.
                char str[100];
                strcpy(str, dir);
                strcat(str, "/");
                string fullname = str;
                fullname += entry->d_name; //change from char* to string because json / strcat didnt accept string?
                std::ifstream ifs{fullname};
                if (!ifs.is_open()) {
                    std::cerr << "Could not open file for reading!\n";
                    return EXIT_FAILURE;
                }
                if (strcmp(entry->d_name, "metadata-cs2341.csv") == 0)
                    return num;

                IStreamWrapper isw{ifs};

                Document d;
                d.ParseStream(isw);
                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                d.Accept(writer);

                //get Document ID
                string documentID = d["paper_id"].GetString();
                string title = d["metadata"]["title"].GetString();

                auto* article = new Article(title, documentID);
                // add new article
                articles.put(documentID, article);

                string firstAuthor;
                for (int i = 0; i < d["metadata"]["authors"].GetArray().Size(); i++) {
                    string first = d["metadata"]["authors"].GetArray()[i]["first"].GetString();
                    string last = d["metadata"]["authors"].GetArray()[i]["last"].GetString();
                    if(firstAuthor.empty())
                        firstAuthor = last;
                    //put first and last name in one word with no space
                    if(last.empty()){
                        continue;
                    }
                    transform(last.begin(), last.end(), last.begin(), ::tolower);
                    if (!authors.containsKey(last)) authors.put(last, new Author(last));
                    authors[last]->addArticles(documentID);
                    article->addAuthor(last);
                }
                for (int i = 0; i < d["abstract"].GetArray().Size(); i++) {
                    string temp = d["abstract"].GetArray()[i]["text"].GetString();
                    istringstream ss(temp);
                    //reads through all words
                    parseBody(stopWords, words, ss, documentID, title, firstAuthor);
                }
                for (int i = 0; i < d["body_text"].GetArray().Size(); i++) {
                    string temp = d["body_text"].GetArray()[i]["text"].GetString();
                    istringstream ss(temp);
                    //reads through all words
                    parseBody(stopWords, words, ss, documentID, title, firstAuthor);
                }
            }
            if (num == 100) {
                return num;
            }
            entry = readdir(pDIR);
        }
        closedir(pDIR);
    }
    else{
        cout << "Directory not found :(" << endl;
    }
    return num;
}

void parseBody(HashSet<string>& stopWords, AVLTree<Word>& words, istringstream& ss, string& documentID, string& documentTitle, string& firstAuthor){
    do {
        // Read a word
        string word;
        ss >> word;

        if(word.size() <= 2)
            continue;

        //if words consists only of alphabetical characters
        for(char c : word){
            if(!isalpha(c)){
                if (word.find(c) != std::string::npos) {
                    word.erase(word.find(c));
                }
            }
        }

        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (stopWords.contains(word)) {continue;}
        Porter2Stemmer::stem(word);
        if (stopWords.contains(word)) {continue;}
        if(word.size() <= 2) continue;
        Word* wordObj = new Word(word);
        if (words.contains(*wordObj)) {
            wordObj = words.getValue(*wordObj);
        }
        if (!wordObj->hasDocument(documentID)) {
            wordObj->insertDoc(documentID);
        } else {
            wordObj->increaseDocumentFrequency(documentID);
        }
        wordObj->increaseFreq();
        if (!words.contains(*wordObj)) words.insert(*wordObj);
    } while (ss);
}

int initializeStopWords(HashSet<string>& stops) {
    ifstream ifs("../stopWords.txt");
    if (!ifs.is_open()) {
        std::cerr << "Could not open file for reading!\n";
        return EXIT_FAILURE;
    }
    std::string str;
    while(ifs >> str) {
        stops.add(str);
    }
    return 0;
}