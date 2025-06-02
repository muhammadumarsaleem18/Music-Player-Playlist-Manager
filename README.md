A console-based music playlist manager written in C++ that allows users to add, delete, search, sort, and play .mp3 songs. It also maintains a persistent playlist using file storage and tracks recently played songs.

🚀 Features
🎼 Add Songs: Add new songs to your playlist with validation.

❌ Delete Songs: Remove songs by name or by position.

🔍 Search Songs: Find a song by name quickly.

📃 Display Playlist: View all songs in the playlist.

🔢 Song Count: Display the total number of songs.

🔁 Sort Playlist: Alphabetically sort the playlist.

▶️ Play Songs: Play .mp3 files using Windows Media Player.

🕓 Recently Played: View recently played songs.

📁 Persistent Storage: Load and save the playlist using a text file.

📂 File Structure
playlist.txt: Stores the list of songs.

.mp3 files: Expected to be located in C:\Music\.

🛠️ Technologies Used
C++ Standard Library (iostream, fstream, cstring, string, etc.)

Windows system call to launch Windows Media Player (system("start wmplayer ..."))

📝 How to Use
Clone or download the repository.

Place your .mp3 songs in C:\Music\.

Build and run the program using a C++ compiler (e.g., g++, MSVC).

Use the menu to interact with your playlist.

⚠️ Note: Song names should not contain spaces — use _ instead (e.g., My_Song instead of My Song).

📌 Example
markdown
Copy
Edit
*WELCOME TO MUSIC PLAYLIST*
*Please use '_' for spaces in song names*
Enter your playlist name (use '_' instead of spaces): my_favs

1. Add Song
2. Delete Song
3. Display Playlist
...
Enter your choice: 6
Choose song to play: chill_beats
Now Playing: chill_beats
📎 Future Improvements
Cross-platform support (replace wmplayer call)

GUI version using Qt or SFML

Playlist export/import in various formats

Support for custom song metadata

📄 License
This project is for educational purposes and does not include actual music files. Ensure all songs used are legally owned.
