#!/usr/bin/env python3
"""
Extract top 200 movies from IMDb CSV and save as pipe-delimited text file
Format: ranking|name|year|rating|genre|director|description
"""

import csv
import sys

def extract_movies(csv_path, output_path, limit=200):
    """Extract movies from IMDb CSV"""
    
    movies = []
    
    try:
        with open(csv_path, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            header = next(reader)  # Skip header
            
            # Header columns: ranking, name, year, certificate, runtime, genre, rating, metascore, description, director, actor1, actor2, actor3, actor4, votes, gross
            # Indices:        0         1      2     3            4        5      6       7          8            9         10      11     12     13     14    15
            
            for row in reader:
                if len(movies) >= limit:
                    break
                
                if len(row) < 10:  # Need at least columns 0-9
                    continue
                
                try:
                    ranking = int(row[0])
                    name = row[1]
                    year_str = row[2]
                    
                    # Handle year format (might have dash: "-1994")
                    if year_str.startswith('-'):
                        year = year_str[1:]
                    else:
                        year = year_str
                    
                    rating = float(row[6])
                    genre = row[5]
                    director = row[9]
                    description = row[8][:100]  # Limit description length
                    
                    # Create pipe-delimited string
                    movie_str = f"{ranking}|{name}|{year}|{rating}|{genre}|{director}|{description}"
                    movies.append(movie_str)
                    
                except (ValueError, IndexError):
                    # Skip malformed rows
                    continue
        
        # Write to output file
        with open(output_path, 'w', encoding='utf-8') as f:
            for movie in movies:
                f.write(movie + '\n')
        
        print(f"✓ Extracted {len(movies)} movies to {output_path}")
        return True
        
    except FileNotFoundError:
        print(f"✗ File not found: {csv_path}")
        return False
    except Exception as e:
        print(f"✗ Error: {e}")
        return False

if __name__ == "__main__":
    csv_file = "./data/imdb_movies.csv"
    output_file = "./data/movies_db.txt"
    
    print("Extracting IMDb movies...")
    if extract_movies(csv_file, output_file, limit=200):
        print("\nFirst 5 movies:")
        with open(output_file, 'r') as f:
            for i, line in enumerate(f):
                if i >= 5:
                    break
                parts = line.strip().split('|')
                print(f"  [{parts[0]}] {parts[1]} ({parts[2]}) - Rating: {parts[3]}")
    else:
        sys.exit(1)
