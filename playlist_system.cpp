#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Define the structure for Song
struct Song {
    std::string title;
    std::string artist;
    std::string genre;
    int duration;  // in seconds
};

// Define the structure for Playlist
struct Playlist {
    std::string name;
    std::vector<Song> songs;
};

// Function to create a new playlist
void createPlaylist(std::vector<Playlist>& playlists, const std::string& name) {
    Playlist newPlaylist = {name, {}};
    playlists.push_back(newPlaylist);
    std::cout << "Playlist '" << name << "' created.\n";
}

// Function to add a song to an existing playlist
void addSongToPlaylist(Playlist& playlist, const Song& song) {
    playlist.songs.push_back(song);
    std::cout << "Song '" << song.title << "' added to playlist '" << playlist.name << "'.\n";
}

// Function to display all playlists and their songs
void displayPlaylists(const std::vector<Playlist>& playlists) {
    if (playlists.empty()) {
        std::cout << "No playlists available.\n";
        return;
    }

    for (const auto& playlist : playlists) {
        std::cout << "Playlist: " << playlist.name << std::endl;
        if (playlist.songs.empty()) {
            std::cout << " - (Empty Playlist)\n";
        } else {
            for (const auto& song : playlist.songs) {
                std::cout << " - " << song.title << " by " << song.artist
                          << " [" << song.genre << "] (" << song.duration << "s)\n";
            }
        }
        std::cout << std::endl;
    }
}

// Function to rename an existing playlist
void renamePlaylist(Playlist& playlist, const std::string& newName) {
    playlist.name = newName;
    std::cout << "Playlist renamed to '" << newName << "'.\n";
}

// Function to edit song details within a playlist
void editSongDetails(Song& song, const std::string& newTitle, const std::string& newArtist,
                     const std::string& newGenre, int newDuration) {
    song.title = newTitle;
    song.artist = newArtist;
    song.genre = newGenre;
    song.duration = newDuration;
    std::cout << "Song details updated.\n";
}

// Function to delete a playlist
void deletePlaylist(std::vector<Playlist>& playlists, const std::string& name) {
    auto it = std::remove_if(playlists.begin(), playlists.end(),
                             [&name](const Playlist& playlist) { return playlist.name == name; });
    if (it != playlists.end()) {
        playlists.erase(it, playlists.end());
        std::cout << "Playlist '" << name << "' deleted.\n";
    } else {
        std::cout << "Playlist not found!\n";
    }
}

// Function to remove a specific song from a playlist
void deleteSongFromPlaylist(Playlist& playlist, const std::string& songTitle) {
    auto it = std::remove_if(playlist.songs.begin(), playlist.songs.end(),
                             [&songTitle](const Song& song) { return song.title == songTitle; });
    if (it != playlist.songs.end()) {
        playlist.songs.erase(it, playlist.songs.end());
        std::cout << "Song '" << songTitle << "' deleted from playlist '" << playlist.name << "'.\n";
    } else {
        std::cout << "Song not found in playlist!\n";
    }
}

// Function to display the menu options
void showMenu() {
    std::cout << "1. Create Playlist\n";
    std::cout << "2. Add Song to Playlist\n";
    std::cout << "3. Display Playlists\n";
    std::cout << "4. Rename Playlist\n";
    std::cout << "5. Edit Song in Playlist\n";
    std::cout << "6. Delete Playlist\n";
    std::cout << "7. Delete Song from Playlist\n";
    std::cout << "0. Exit\n";
}

// Main function to manage the CRUD system
int main() {
    std::vector<Playlist> playlists;
    int choice;

    do {
        showMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string playlistName;
                std::cout << "Enter playlist name: ";
                std::cin >> playlistName;
                createPlaylist(playlists, playlistName);
                break;
            }
            case 2: {
                std::string playlistName, songTitle, artist, genre;
                int duration;
                std::cout << "Enter playlist name: ";
                std::cin >> playlistName;

                // Find the playlist
                auto it = std::find_if(playlists.begin(), playlists.end(),
                                       [&playlistName](const Playlist& playlist) {
                                           return playlist.name == playlistName;
                                       });

                if (it != playlists.end()) {
                    std::cout << "Enter song title: ";
                    std::cin >> songTitle;
                    std::cout << "Enter artist: ";
                    std::cin >> artist;
                    std::cout << "Enter genre: ";
                    std::cin >> genre;
                    std::cout << "Enter duration (in seconds): ";
                    std::cin >> duration;

                    Song newSong = {songTitle, artist, genre, duration};
                    addSongToPlaylist(*it, newSong);
                } else {
                    std::cout << "Playlist not found!\n";
                }
                break;
            }
            case 3:
                displayPlaylists(playlists);
                break;
            case 4: {
                std::string playlistName, newName;
                std::cout << "Enter current playlist name: ";
                std::cin >> playlistName;

                // Find the playlist
                auto it = std::find_if(playlists.begin(), playlists.end(),
                                       [&playlistName](const Playlist& playlist) {
                                           return playlist.name == playlistName;
                                       });

                if (it != playlists.end()) {
                    std::cout << "Enter new playlist name: ";
                    std::cin >> newName;
                    renamePlaylist(*it, newName);
                } else {
                    std::cout << "Playlist not found!\n";
                }
                break;
            }
            case 5: {
                std::string playlistName, songTitle, newTitle, newArtist, newGenre;
                int newDuration;
                std::cout << "Enter playlist name: ";
                std::cin >> playlistName;

                // Find the playlist
                auto it = std::find_if(playlists.begin(), playlists.end(),
                                       [&playlistName](const Playlist& playlist) {
                                           return playlist.name == playlistName;
                                       });

                if (it != playlists.end()) {
                    std::cout << "Enter song title to edit: ";
                    std::cin >> songTitle;

                    // Find the song
                    auto songIt = std::find_if(it->songs.begin(), it->songs.end(),
                                               [&songTitle](const Song& song) {
                                                   return song.title == songTitle;
                                               });

                    if (songIt != it->songs.end()) {
                        std::cout << "Enter new song title: ";
                        std::cin >> newTitle;
                        std::cout << "Enter new artist: ";
                        std::cin >> newArtist;
                        std::cout << "Enter new genre: ";
                        std::cin >> newGenre;
                        std::cout << "Enter new duration (in seconds): ";
                        std::cin >> newDuration;

                        editSongDetails(*songIt, newTitle, newArtist, newGenre, newDuration);
                    } else {
                        std::cout << "Song not found!\n";
                    }
                } else {
                    std::cout << "Playlist not found!\n";
                }
                break;
            }
            case 6: {
                std::string playlistName;
                std::cout << "Enter playlist name to delete: ";
                std::cin >> playlistName;
                deletePlaylist(playlists, playlistName);
                break;
            }
            case 7: {
                std::string playlistName, songTitle;
                std::cout << "Enter playlist name: ";
                std::cin >> playlistName;

                // Find the playlist
                auto it = std::find_if(playlists.begin(), playlists.end(),
                                       [&playlistName](const Playlist& playlist) {
                                           return playlist.name == playlistName;
                                       });

                if (it != playlists.end()) {
                    std::cout << "Enter song title to delete: ";
                    std::cin >> songTitle;
                    deleteSongFromPlaylist(*it, songTitle);
                } else {
                    std::cout << "Playlist not found!\n";
                }
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
