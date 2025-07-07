#ifndef __DRIVER_SDMMC_H
#define __DRIVER_SDMMC_H

#include "Arduino.h"
// Include SD
#define FS_NO_GLOBALS
#include <FS.h>
#include <SD.h>
#ifdef ESP32
  #include "SPIFFS.h" // ESP32 only
#endif
#include "SPI.h"
#include <list>  // Include list header file

// Define a structure to store file and directory information
struct File_Entry {
    String name;
    bool isDirectory;
    size_t size;  // Valid only for files
};

void sdspi_init(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs);
std::list<File_Entry> list_dir(const char * dirname, uint8_t levels);
void create_dir(const char * path);
void remove_dir(const char * path);
void read_file(const char * path, uint8_t * buffer, size_t length);
void write_file(const char * path, const uint8_t * buffer, size_t size);
void append_file(const char * path, const uint8_t * buffer, size_t size);
void rename_file(const char * path1, const char * path2);
void delete_file(const char * path);
void test_file_io(const char * path);

int read_file_num(const char * dirname);
void print_file_list(const std::list<File_Entry>& fileList);
String get_file_name_by_index(const char * dirname, int index);
void write_jpg(const char * path, const uint8_t *buf, size_t size);
void write_bmp(char *path, uint8_t *buf, long size, long height, long width);

#endif