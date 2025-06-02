C++ Music Playlist Manager
--------------------------

This is a console-based C++ program that manages a music playlist using a doubly linked list. It allows users to add, delete, search, sort, and play songs stored in the `C:\Music\` directory. Songs are stored as `.mp3` files, and the playlist is persisted using a text file (`playlist.txt`).

Main Features:
- Add songs to the playlist (use underscores instead of spaces)
- Delete songs by name or by position
- Search for a song in the playlist
- Sort the playlist alphabetically
- Count total number of songs
- Play songs using Windows Media Player (via system call)
- Display recently played songs using a stack
- Save playlist to file and load from file

Implementation Highlights:
- Songs are managed in a doubly linked list for efficient insertion and deletion.
- Recently played songs are tracked using a stack structure.
- Songs are validated to ensure proper formatting and file compatibility.
- File I/O is used to maintain a persistent playlist between sessions.

Usage:
- Make sure your `.mp3` files are placed in `C:\Music\`.
- Compile the code with a C++ compiler (e.g., g++).
- Run the program and follow the menu options.
- Use `_` instead of spaces when entering song names.

This project demonstrates the use of file handling, linked lists, basic data structures (stack), and system-level commands in C++.
