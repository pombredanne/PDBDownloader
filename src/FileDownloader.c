#include "PDBDownload.h"

void FileDownloader(char* pdbName, char* url) {

    DWORD BytesRead, FileSize, Download, i = 0, BuffLen = sizeof(int);
    DWORD Flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_UI | INTERNET_FLAG_PRAGMA_NOCACHE;

    HANDLE hOpen = InternetOpen("", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
    HANDLE hUrl = InternetOpenUrl(hOpen, url, 0, 0, Flags, 0);

    BOOL IsValidUrl = HttpQueryInfo(hUrl, HTTP_QUERY_FLAG_NUMBER | HTTP_QUERY_CONTENT_LENGTH, &FileSize, &BuffLen, 0);

    if (IsValidUrl && FileSize) {
        printf("Total file size: %d KB\n", FileSize / 1024);
    }
    else {
        printf("HttpQueryInfo Error: %d\n", (GetLastError() & 0xFFFF));
        exit(1);
    }

    FILE* File = fopen(pdbName, "wb");
    
    char Buffer[USHRT_MAX];

    while (InternetReadFile(hUrl, Buffer, USHRT_MAX, &BytesRead)) {

        if (BytesRead) {
            Download = BytesRead + i;
            printf("Downloading: %d%%\r", (100 * Download / FileSize));
            fwrite(Buffer, 1, BytesRead, File);
            i = Download;
        }
        else {
            printf("\n");
            break;
        }
    }

    fclose(File);
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hOpen);
}
