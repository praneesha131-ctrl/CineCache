#include "common/headers.h"
#include "../engine/cinecache_system.h"
#include "../engine/ui.h"
#include "../engine/utils.h"

using namespace std;

int main() {
    printBanner();

    // Create the main system
    CineCacheSystem app;

    cout << GRN << "  + 3 cache nodes ready: Node-A  Node-B  Node-C\n" << RST;
    cout << DIM << "  Tip: load the database first [4], then try [2].\n\n" << RST;

    string input;

    // Main menu loop
    while (true) {
        printMenu(app.is_database_loaded());
        getline(cin, input);

        if (input.empty()) {
            continue;
        }

        char choice = input[0];

        // Option 1: Show cache state
        if (choice == '1') {
            app.show_cache_state();
        }
        // Option 2: Lookup and show a movie
        else if (choice == '2') {
            cout << "\n  Enter User ID  (e.g. alice)     : ";
            string user_id;
            getline(cin, user_id);

            if (user_id.empty()) {
                cout << RED << "  Empty.\n" << RST;
                continue;
            }

            cout << "  Enter Movie ID (1 to " << app.get_database_size() << ") : ";
            string movie_id;
            getline(cin, movie_id);

            if (movie_id.empty()) {
                cout << RED << "  Empty.\n" << RST;
                continue;
            }

            app.lookup_and_show_movie(user_id, movie_id);
        }
        // Option 3: Show hash ring stats
        else if (choice == '3') {
            app.show_ring_stats();
        }
        // Option 4: Load database
        else if (choice == '4') {
            app.load_database_from_menu();
        }
        // Option 5: Remove a node
        else if (choice == '5') {
            app.remove_node_from_menu();
        }
        // Option 0: Quit
        else if (choice == '0') {
            cout << "\n" << CYN << "  Goodbye from CineCache!\n\n" << RST;
            break;
        }
        // Invalid option
        else {
            cout << RED << "  x Unknown option (0-5).\n" << RST;
        }
    }

    return 0;
}
