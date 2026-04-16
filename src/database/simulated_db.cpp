#pragma once
#ifndef SIMULATED_DB_CPP
#define SIMULATED_DB_CPP

#include "common/headers.h"
#include "data_structures/hash_table.cpp"
#include "common/types.cpp"
using namespace std;

// A fake database that loads movie data from a text file.
class SimulatedDB {
private:
    HashTable<Movie> db;
    int query_count = 0;

public:
    SimulatedDB() : db(256) {}

    bool loadFromFile(const string& filepath, int limit = 200) {
        ifstream file(filepath);

        if (!file.is_open()) {
            cerr << "Could not open: " << filepath << "\n";
            return false;
        }

        string line;
        int count = 0;

        while (getline(file, line) && count < limit) {
            if (line.empty()) {
                continue;
            }

            vector<string> fields;
            stringstream ss(line);
            string field;

            while (getline(ss, field, '|')) {
                fields.push_back(field);
            }

            if (fields.size() < 7) {
                continue;
            }

            try {
                int id = stoi(fields[0]);
                string title = fields[1];
                int year = stoi(fields[2]);
                double rating = stod(fields[3]);
                string genre = fields[4];
                string director = fields[5];
                string description = fields[6];

                Movie movie(id, title, year, rating, genre, director, description);
                string key = "movie:" + to_string(id);

                db.insert(key, movie);
                count++;
            } catch (...) {
                continue;
            }
        }

        file.close();
        cout << "Loaded " << count << " movies into database\n";
        return count > 0;
    }

    Movie* fetch(const string& movie_key) {
        query_count++;

        Movie movie;

        if (db.search(movie_key, movie)) {
            return new Movie(movie);
        }

        return nullptr;
    }

    int get_query_count() const { return query_count; }
    int size() const { return db.get_size(); }
};

#endif
