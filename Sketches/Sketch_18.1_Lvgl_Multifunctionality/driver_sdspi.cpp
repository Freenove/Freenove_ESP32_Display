#include "driver_sdspi.h"

SPIClass vspi(VSPI);

void sdspi_init(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs) {
  vspi.begin(sck, miso, mosi, cs);
  if (!SD.begin(cs, vspi, 10000000, "/sd", 5, false)) {
    Serial.println(F("SD.begin failed!"));
    //while (1) delay(1);
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\r\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\r\n", SD.usedBytes() / (1024 * 1024));
}

std::list<File_Entry> list_dir(const char *dirname, uint8_t levels) {
  std::list<File_Entry> fileList;

  File root = SD.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return fileList;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return fileList;
  }

  File file = root.openNextFile();
  while (file) {
    File_Entry entry;
    entry.name = file.name();
    entry.isDirectory = file.isDirectory();
    if (!entry.isDirectory) {
      entry.size = file.size();
    }
    fileList.push_back(entry);
    if (entry.isDirectory && levels) {
      std::list<File_Entry> subDirList = list_dir(file.path(), levels - 1);
      fileList.insert(fileList.end(), subDirList.begin(), subDirList.end());
    }
    file = root.openNextFile();
  }
  return fileList;
}

void create_dir(const char *path) {
  if (SD.exists(path)) {
    return;
  } else {
    if (!SD.mkdir(path)) {
      Serial.println("mkdir failed");
    }
  }
}

void remove_dir(const char *path) {
  if (SD.exists(path)) {
    std::list<File_Entry> fileList = list_dir(path, 1);

    for (const auto &entry : fileList) {
      if (entry.isDirectory) {
        char subPath[256];
        snprintf(subPath, sizeof(subPath), "%s/%s", path, entry.name.c_str());
        remove_dir(subPath);
      } else {
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%s", path, entry.name.c_str());
        delete_file(filePath);
      }
    }

    if (!SD.rmdir(path)) {
      Serial.println("rmdir failed");
    }
  }
}

void read_file(const char *path, uint8_t *buffer, size_t length) {
  File file = SD.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  size_t fileSize = file.size();
  if (length == 0 || length > fileSize) {
    length = fileSize;
  }

  size_t bytesRead = file.read(buffer, length);
  if (bytesRead != length) {
    Serial.printf("Failed to read %u bytes, only read %u bytes\n", length, bytesRead);
  }
  buffer[bytesRead] = '\0';
  file.close();
}

void write_file(const char *path, const uint8_t *buffer, size_t size) {
  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t bytesWritten = file.write(buffer, size);
  if (bytesWritten != size) {
    Serial.printf("Failed to write %u bytes, only wrote %u bytes\n", size, bytesWritten);
  }

  file.close();
}

void append_file(const char *path, const uint8_t *buffer, size_t size) {
  File file = SD.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }

  size_t bytesWritten = file.write(buffer, size);
  if (bytesWritten != size) {
    Serial.printf("Failed to append %u bytes, only appended %u bytes\n", size, bytesWritten);
  }

  file.close();
}

void rename_file(const char *path1, const char *path2) {
  if (SD.exists(path2)) {
    if (!SD.remove(path2)) {
      Serial.println("Failed to delete target file");
      return;
    }
  }

  if (!SD.rename(path1, path2)) {
    Serial.println("Rename failed");
  }
}

void delete_file(const char *path) {
  if (!SD.remove(path)) {
    Serial.println("Delete failed");
  }
}

void test_file_io(const char *path) {
  File file = SD.open(path);
  static uint8_t buf[512];
  size_t len = 0;

  if (file) {
    len = file.size();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
    return;
  }

  file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  for (size_t i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }

  file.close();
}

void create_folder(char *path) {
  File root = SD.open(path);
  if (!root) {
    if (!SD.mkdir(path)) {
      Serial.println("mkdir failed");
    }
  }
  root.close();
}

int read_file_num(const char *dirname) {
  std::list<File_Entry> fileList = list_dir(dirname, 0);
  if (fileList.empty()) {
    return 0;
  }

  int num = 0;
  for (const auto &entry : fileList) {
    if (!entry.isDirectory) {
      num++;
    }
  }

  return num;
}

void print_file_list(const std::list<File_Entry> &fileList) {
  for (const auto &entry : fileList) {
    if (entry.isDirectory) {
      Serial.print("DIR: ");
    } else {
      Serial.print("FILE: ");
    }
    Serial.print(entry.name);
    if (!entry.isDirectory) {
      Serial.printf("  SIZE: %u\n", entry.size);
    } else {
      Serial.println();
    }
  }
}

String get_file_name_by_index(const char *dirname, int index) {
  std::list<File_Entry> fileList = list_dir(dirname, 0);
  if (fileList.empty()) {
    return "";
  }

  int count = 0;
  for (const auto &entry : fileList) {
    if (!entry.isDirectory) {
      if (count == index) {
        return entry.name;
      }
      count++;
    }
  }

  return "";
}

void write_jpg(const char *path, const uint8_t *buf, size_t size) {
  write_file(path, buf, size);
}

void write_bmp(char *path, uint8_t *buf, long size, long height, long width) {
  File file = SD.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  uint8_t bmp_info[] = {
    0x42, 0x4d,                                                                 // BM: BMP signature
    size & 0xFF, (size >> 8) & 0xFF, (size >> 16) & 0xFF, (size >> 24) & 0xFF,  // File size
    0x00, 0x00, 0x00, 0x00,                                                     // Reserved: 0
    0x46, 0x00, 0x00, 0x00,                                                     // Offset to pixel data: 70 bytes

    0x38, 0x00, 0x00, 0x00,                                                             // Header size: 56 bytes
    width & 0xFF, (width >> 8) & 0xFF, (width >> 16) & 0xFF, (width >> 24) & 0xFF,      // Image width
    height & 0xFF, (height >> 8) & 0xFF, (height >> 16) & 0xFF, (height >> 24) & 0xFF,  // Image height
    0x01, 0x00,                                                                         // Planes: 1
    0x10, 0x00,                                                                         // Bits per pixel: 16-bit (RGB565)
    0x03, 0x00, 0x00, 0x00,                                                             // Compression: 0 (none)
    0x02, 0xc2, 0x01, 0x00,                                                             // Image size: 0 (no compression)
    0x12, 0x0b, 0x00, 0x00,                                                             // X pixels per meter: 2834 pixels/meter
    0x12, 0x0b, 0x00, 0x00,                                                             // Y pixels per meter: 2834 pixels/meter
    0x00, 0x00, 0x00, 0x00,                                                             // Colors used: 0 (default)
    0x00, 0x00, 0x00, 0x00,                                                             // Important colors: 0 (default)
    0x00, 0xf8, 0x00, 0x00,
    0xe0, 0x07, 0x00, 0x00,
    0x1f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  uint8_t bmp_efo[] = { 0x00, 0x00 };
  file.write(bmp_info, 70);
  for (int i = height - 1; i >= 0; i--) {
    file.write(&buf[i * width * 2], width * 2);
  }
  file.write(bmp_efo, 2);
  file.close();
}

bool write_wav_header(const char *path, uint32_t data_size) {
  File file = SD.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return false;
  }
  uint8_t header[] = {
    0x52, 0x49, 0x46, 0x46,                                                             // RIFF
    0x00, 0x00, 0x00, 0x00,                                                             // File size
    0x57, 0x41, 0x56, 0x45,                                                             // WAVE
    0x66, 0x6d, 0x74, 0x20,                                                             // fmt
    0x10, 0x00, 0x00, 0x00,                                                             // Subchunk1Size: 16
    0x01, 0x00,                                                                         // AudioFormat: 1 (PCM)
    0x01, 0x00,                                                                         // NumChannels: 1
    0x80, 0x3e, 0x00, 0x00,                                                             // SampleRate: 16000
    0x80, 0x3e, 0x00, 0x00,                                                             // ByteRate: 16000
    0x02, 0x00,                                                                         // BlockAlign: 2
    0x10, 0x00,                                                                         // BitsPerSample: 16
    0x64, 0x61, 0x74, 0x61,                                                             // data
    0x00, 0x00, 0x00, 0x00                                                              // DataSize
  };
  header[4] = (data_size + 36) & 0xFF;
  header[5] = ((data_size + 36) >> 8) & 0xFF;
  header[6] = ((data_size + 36) >> 16) & 0xFF;
  header[7] = ((data_size + 36) >> 24) & 0xFF;
  header[40] = (data_size) & 0xFF;
  header[41] = (data_size >> 8) & 0xFF;
  header[42] = (data_size >> 16) & 0xFF;
  header[43] = (data_size >> 24) & 0xFF;
  file.seek(0, SeekSet);
  if (file.write(header, 44) != 44) {
    Serial.println("Failed to write WAV header");
    file.close();
    return false;
  }
  file.seek(0, SeekEnd);
  file.close();
  return true;
}