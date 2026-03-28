#ifndef DLL_NODE_H
#define DLL_NODE_H

#include <string>
#include <iostream>
using namespace std;

// ─────────────────────────────────────────────
//  Movie Class — matches IMDb Kaggle CSV columns
// ─────────────────────────────────────────────
class Movie {
private:
    string series_title;
    int released_year;
    string certificate;
    string runtime;
    string genre;
    float imdb_rating;
    string overview;
    int meta_score;
    string director;
    string star1, star2, star3, star4;
    long no_of_votes;
    string gross;

public:
    // 🔹 Default Constructor
    Movie() {
        series_title = "";
        released_year = 0;
        certificate = "";
        runtime = "";
        genre = "";
        imdb_rating = 0.0;
        overview = "";
        meta_score = 0;
        director = "";
        star1 = star2 = star3 = star4 = "";
        no_of_votes = 0;
        gross = "";
    }

    // 🔹 Parameterized Constructor (simpler)
    Movie(string title, int year, string cert,
          string rt, string gen, float rating,
          string ovr, int meta, string dir,
          string s1, string s2, string s3,
          string s4, long votes, string gr) {

        series_title = title;
        released_year = year;
        certificate = cert;
        runtime = rt;
        genre = gen;
        imdb_rating = rating;
        overview = ovr;
        meta_score = meta;
        director = dir;
        star1 = s1;
        star2 = s2;
        star3 = s3;
        star4 = s4;
        no_of_votes = votes;
        gross = gr;
    }
// end of parameterized ctor — keep class open for member methods

    // ── Getters ───────────────────────────────
    string getTitle()       const { return series_title;  }
    int    getYear()        const { return released_year; }
    string getCertificate() const { return certificate;   }
    string getRuntime()     const { return runtime;       }
    string getGenre()       const { return genre;         }
    float  getRating()      const { return imdb_rating;   }
    string getOverview()    const { return overview;      }
    int    getMetaScore()   const { return meta_score;    }
    string getDirector()    const { return director;      }
    string getStar1()       const { return star1;         }
    string getStar2()       const { return star2;         }
    string getStar3()       const { return star3;         }
    string getStar4()       const { return star4;         }
    long   getVotes()       const { return no_of_votes;   }
    string getGross()       const { return gross;         }

    // ── Setters ───────────────────────────────
    void setTitle(const string& t)       { series_title  = t; }
    void setYear(int y)                  { released_year = y; }
    void setCertificate(const string& c) { certificate   = c; }
    void setRuntime(const string& r)     { runtime       = r; }
    void setGenre(const string& g)       { genre         = g; }
    void setRating(float r)              { imdb_rating   = r; }
    void setOverview(const string& o)    { overview      = o; }
    void setMetaScore(int m)             { meta_score    = m; }
    void setDirector(const string& d)    { director      = d; }
    void setStar1(const string& s)       { star1         = s; }
    void setStar2(const string& s)       { star2         = s; }
    void setStar3(const string& s)       { star3         = s; }
    void setStar4(const string& s)       { star4         = s; }
    void setVotes(long v)                { no_of_votes   = v; }
    void setGross(const string& g)       { gross         = g; }

    // ── Display full details ───────────────────
    void display() const {
        cout << "------------------------------\n";
        cout << "Title    : " << series_title  << "\n";
        cout << "Year     : " << released_year << "\n";
        cout << "Cert     : " << certificate   << "\n";
        cout << "Runtime  : " << runtime       << "\n";
        cout << "Genre    : " << genre         << "\n";
        cout << "Rating   : " << imdb_rating   << "\n";
        cout << "Metascore: " << meta_score    << "\n";
        cout << "Director : " << director      << "\n";
        cout << "Cast     : " << star1 << ", " << star2
                               << ", " << star3 << ", " << star4 << "\n";
        cout << "Votes    : " << no_of_votes   << "\n";
        cout << "Gross    : $" << gross        << "\n";
        cout << "Overview : " << overview      << "\n";
        cout << "------------------------------\n";
    }

    // ── Display short summary ──────────────────
    void displayShort() const {
        cout << "\"" << series_title << "\""
             << " (" << released_year << ")"
             << " | Genre: "  << genre
             << " | Rating: " << imdb_rating
             << " | Dir: "    << director << "\n";
    }

    // ── Overload == for title comparison ───────
    bool operator==(const string& title) const {
        return series_title == title;
    }
};

// ─────────────────────────────────────────────
//  Node Class — wraps Movie with prev/next links
// ─────────────────────────────────────────────
class Node {
private:
    Movie data;
    Node* prev;
    Node* next;

public:
    // ── Constructor ───────────────────────────
    Node(const Movie& m)
        : data(m), prev(nullptr), next(nullptr) {}

    // ── Getters ───────────────────────────────
    Movie&       getData()       { return data; }
    const Movie& getData() const { return data; }
    Node*        getPrev() const { return prev; }
    Node*        getNext() const { return next; }

    // ── Setters ───────────────────────────────
    void setPrev(Node* p)        { prev = p; }
    void setNext(Node* n)        { next = n; }
    void setData(const Movie& m) { data = m; }

    // ── Give DoublyLinkedList direct access ────
    friend class DoublyLinkedList;
};

#endif // DLL_NODE_H