#pragma once
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <locale>
#include <codecvt>
#define WIN32_LEAN_AND_MEAN // Prevent windows.h from including winsock.h
#include <winsock2.h>       // Must come first
#include <windows.h>        // After winsock2.h
#include <ws2tcpip.h>       // For getaddrinfo and inet_ntop
#include <iostream>
#include <iphlpapi.h>       // For GetAdaptersAddresses
#include <shellapi.h>
#include <urlmon.h>
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
using namespace std;
extern bool brute_force_password(string current_guess, const string& correct_password);
extern int random(int lower_bound, int upper_bound);
extern std::string getLineFromFile(const std::string& filePath, int lineNumber);
extern int countLinesInFile(const std::string& filePath);
extern bool copy_file(const std::string& source, const std::string& destinationDir);
extern string read_file_to_string(string file_path);
extern void overwrite_line_in_file(const std::string& filePath, int lineNumber, const std::string& newContent);
extern std::vector<std::string> splitString(const std::string& str, char delimiter);
extern std::string convertSecondsToTime(int totalSeconds);
extern bool yes_or_no_random();
extern void Log(const std::string& message);
extern void TerminalError(string message, HWND consoleWindow);
extern std::wstring getExecutablePath();
extern std::string Wstring2String(const std::wstring& wstr);
extern std::wstring getExecutableDir();
extern bool RelaunchAsAdmin();
extern bool writeToFile(const std::string& filename, const std::string& content);
extern bool fileExists(const std::string& filename);
extern std::string pad16(const std::string& input);
extern std::string unpad(const std::string& padded);
extern SDL_Texture* randomTexture(SDL_Texture* T0, SDL_Texture* T1, SDL_Texture* T2, SDL_Texture* T3, SDL_Texture* T4, SDL_Texture* T5, SDL_Texture* T6, SDL_Texture* T7, SDL_Texture* T8, SDL_Texture* T9);