#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<cctype>

using namespace std;

const string SONG_DIRECTORY = "C:\\Music\\";
const string FILE_EXTENSION = ".mp3";

struct node {
    char song[100];
    struct node* next;
    struct node* prev;
};

struct node* top = NULL, * temp = NULL;

void tofile(const char a[]) {
    ofstream f1("playlist.txt", ios::app);
    if (!f1) {
        cerr << "Error opening file to write song.\n";
        return;
    }
    f1 << a << endl;
}

bool validateSongName(const char* name) {
    if (strlen(name) == 0) {
        cout << "Error: Song name cannot be empty.\n";
        return false;
    }

    for (int i = 0; name[i] != '\0'; i++) {
        if (isspace(name[i])) {
            cout << "Error: Song name contains spaces. Please use '_' instead of spaces.\n";
            return false;
        }
    }
    return true;
}

void add_node(struct node* head) {
    char a[100];
    bool validInput = false;

    while (!validInput) {
        cout << "\nEnter Song name (use '_' instead of spaces, no extension): ";
        cin >> ws;
        cin.getline(a, sizeof(a));

        validInput = validateSongName(a);
    }

    string fullName = string(a) + FILE_EXTENSION;
    struct node* newNode = new(nothrow) node;
    if (!newNode) {
        cerr << "Memory allocation failed.\n";
        return;
    }
    strcpy_s(newNode->song, sizeof(newNode->song), fullName.c_str());
    tofile(fullName.c_str());
    newNode->next = NULL;
    newNode->prev = NULL;

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = newNode;
    newNode->prev = head;
}

void add_node_file(struct node* head, string a) {
    struct node* newNode = new(nothrow) node;
    if (!newNode) {
        cerr << "Memory allocation failed.\n";
        return;
    }
    strcpy_s(newNode->song, sizeof(newNode->song), a.c_str());
    newNode->next = NULL;
    newNode->prev = NULL;

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = newNode;
    newNode->prev = head;
}

void delete_file(const char a[]) {
    ifstream f1("playlist.txt");
    if (!f1) {
        cerr << "Error opening playlist file for reading.\n";
        return;
    }
    ofstream f2("temp.txt");
    if (!f2) {
        cerr << "Error opening temp file for writing.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(f1, line)) {
        if (strcmp(a, line.c_str()) != 0)
            f2 << line << endl;
        else
            found = true;
    }

    f1.close();
    f2.close();

    if (remove("playlist.txt") != 0) {
        perror("Error deleting original file");
        return;
    }
    if (rename("temp.txt", "playlist.txt") != 0) {
        perror("Error renaming temp file");
        return;
    }

    cout << (found ? "Song has been deleted." : "No song found with the given name.") << endl;
}

void del_node(struct node* head) {
    while (head->next && head->next->next != NULL) {
        head = head->next;
    }
    if (head->next) {
        delete_file(head->next->song);
        delete head->next;
        head->next = NULL;
        cout << "Deleted" << endl;
    }
    else {
        cout << "No song to delete." << endl;
    }
}

void printlist(struct node* head) {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }
    cout << "\nPlaylist:\n";
    while (head != NULL) {
        string name = head->song;
        size_t pos = name.find(FILE_EXTENSION);
        if (pos != string::npos)
            name = name.substr(0, pos);
        cout << name << endl;
        head = head->next;
    }
}

void count_nodes(struct node* head) {
    if (!head) {
        cout << "\nTotal songs: 0" << endl;
        return;
    }
    int count = 0;
    head = head->next;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    cout << "\nTotal songs: " << count << endl;
}

node* del_pos(node* head, int pos) {
    if (pos < 0) {
        cerr << "Invalid position.\n";
        return head;
    }

    node* current = head;
    int index = 0;

    while (current && index < pos) {
        current = current->next;
        index++;
    }

    if (!current) {
        cout << "Invalid position!" << endl;
        return head;
    }

    delete_file(current->song);

    if (current->prev)
        current->prev->next = current->next;
    if (current->next)
        current->next->prev = current->prev;

    if (current == head)
        head = current->next;

    delete current;
    cout << "Song deleted at position " << pos + 1 << endl;
    return head;
}

void search1(node* head) {
    char song[100];
    bool validInput = false;

    while (!validInput) {
        cout << "Enter song to search (use '_' instead of spaces): ";
        cin >> ws;
        cin.getline(song, sizeof(song));
        validInput = validateSongName(song);
    }

    string fullName = string(song) + FILE_EXTENSION;
    bool found = false;
    while (head) {
        if (strcmp(head->song, fullName.c_str()) == 0) {
            cout << "#Song Found" << endl;
            found = true;
            break;
        }
        head = head->next;
    }

    if (!found)
        cout << "#Song Not Found" << endl;
}

void create() {
    top = NULL;
}

void push(char data[]) {
    if (!top || strcmp(top->song, data) != 0) {
        node* newNode = new(nothrow) node;
        if (!newNode) {
            cerr << "Memory allocation failed.\n";
            return;
        }
        strcpy_s(newNode->song, sizeof(newNode->song), data);
        newNode->next = top;
        newNode->prev = NULL;
        top = newNode;
    }
}

void display() {
    node* current = top;
    if (!current) {
        cout << "No recently played tracks.\n";
        return;
    }
    cout << "Recently played tracks:\n";
    while (current) {
        string name = current->song;
        size_t pos = name.find(FILE_EXTENSION);
        if (pos != string::npos)
            name = name.substr(0, pos);
        cout << name << endl;
        current = current->next;
    }
}

void play(node* head) {
    if (!head) {
        cout << "Playlist is empty." << endl;
        return;
    }

    char song[100];
    bool validInput = false;

    while (!validInput) {
        printlist(head);
        cout << "Choose song to play (use '_' instead of spaces): ";
        cin >> ws;
        cin.getline(song, sizeof(song));
        validInput = validateSongName(song);
    }

    string fullName = string(song) + FILE_EXTENSION;
    bool found = false;
    while (head) {
        if (strcmp(head->song, fullName.c_str()) == 0) {
            cout << "Now Playing: " << song << endl;
            string filepath = SONG_DIRECTORY + fullName;
            string command = "start wmplayer \"" + filepath + "\"";
            system(command.c_str());
            push(song);
            found = true;
            break;
        }
        head = head->next;
    }

    if (!found)
        cout << "#Song Not Found" << endl;
}

void recent() {
    display();
}

void topelement() {
    if (top)
        cout << "Last Played Song: " << top->song << endl;
    else
        cout << "No last played tracks.\n";
}

void sort(node*& head) {
    if (!head || !head->next)
        return;

    for (node* i = head; i->next; i = i->next) {
        for (node* j = i->next; j; j = j->next) {
            if (strcmp(i->song, j->song) > 0) {
                char temp[100];
                strcpy_s(temp, sizeof(temp), i->song);
                strcpy_s(i->song, sizeof(i->song), j->song);
                strcpy_s(j->song, sizeof(j->song), temp);
            }
        }
    }
}

void addplaylist(node* head) {
    ifstream f1("playlist.txt");
    if (!f1) {
        cerr << "Error opening playlist file.\n";
        return;
    }

    string line;
    while (getline(f1, line)) {
        add_node_file(head, line);
    }
    cout << "Playlist loaded from file.\n";
}

void del_search(node* head) {
    if (!head) {
        cout << "Playlist is empty.\n";
        return;
    }

    char song[100];
    bool validInput = false;

    while (!validInput) {
        printlist(head);
        cout << "Enter song to delete (use '_' instead of spaces): ";
        cin >> ws;
        cin.getline(song, sizeof(song));
        validInput = validateSongName(song);
    }

    string fullName = string(song) + FILE_EXTENSION;
    node* current = head;
    while (current) {
        if (strcmp(current->song, fullName.c_str()) == 0) {
            delete_file(fullName.c_str());

            if (current->prev)
                current->prev->next = current->next;
            if (current->next)
                current->next->prev = current->prev;

            delete current;
            cout << "Song deleted.\n";
            return;
        }
        current = current->next;
    }
    cout << "Song not found.\n";
}

void deletemenu(node*& head) {
    int c;
    cout << "Delete method?\n1. By Search\n2. By Position\nEnter choice: ";
    if (!(cin >> c)) {
        cerr << "Invalid input. Exiting delete menu.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    switch (c) {
    case 1: del_search(head); break;
    case 2:
        int pos;
        cout << "Enter position: ";
        if (!(cin >> pos)) {
            cerr << "Invalid input for position.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        head = del_pos(head, pos - 1);
        break;
    default:
        cout << "Invalid option.\n";
    }
}

int main() {
    int choice;
    node* start = new(nothrow) node;

    if (!start) {
        cerr << "Failed to initialize playlist.\n";
        return 1;
    }

    cout << "\n*WELCOME TO MUSIC PLAYLIST*" << endl;
    cout << "*Please use '_' for spaces in song names*\n";

    bool validName = false;
    while (!validName) {
        cout << "Enter your playlist name (use '_' instead of spaces): ";
        cin >> ws;
        cin.getline(start->song, 100);
        validName = validateSongName(start->song);
    }

    start->next = NULL;
    start->prev = NULL;
    node* head = start;
    create();

    do {
        cout << "\n1. Add Song\n2. Delete Song\n3. Display Playlist\n4. Total Songs\n5. Search Song";
        cout << "\n6. Play Song\n7. Recently Played\n8. Last Played\n9. Sort Playlist\n10. Load Playlist from File\n11. Exit";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cerr << "Invalid input.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1: add_node(head); break;
        case 2: deletemenu(head); break;
        case 3: printlist(head); break;
        case 4: count_nodes(head); break;
        case 5: search1(head); break;
        case 6: play(head); break;
        case 7: recent(); break;
        case 8: topelement(); break;
        case 9: sort(head->next); printlist(head); break;
        case 10: addplaylist(head); break;
        case 11: cout << "Exiting program.\n"; exit(0);
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 11);

    return 0;
}