#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <winnt.h> /*All the structs and definitions*/
#include <stdio.h>
#include <stdint.h>
#include <WinInet.h>
#pragma comment (lib, "Wininet.lib")

void PEHeaderReader(char* PdbName, char* url);
void FileDownloader(char* PdbName, char* url);
