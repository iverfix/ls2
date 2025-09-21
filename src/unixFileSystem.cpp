#include "unixFileSystem.h"
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

std::string UnixFileSystem::getFileUser(const char* filename) const {
 
  struct stat fileStat;
  if (stat(filename, &fileStat) == -1) {
    throw std::runtime_error("File could not be found");
  }


  struct passwd* pw = getpwuid(fileStat.st_uid);

  return std::string(pw ? pw->pw_name : "unknown");
}

std::string UnixFileSystem::getFileGroup(const char* filename) const {


  struct stat fileStat;
  if (stat(filename, &fileStat) == -1) {
    throw std::runtime_error("File could not be found");
  }

  struct group* gr = getgrgid(fileStat.st_gid);

  return std::string(gr ? gr->gr_name : "unknown");
}

int UnixFileSystem::getFileSize(const char* filename) const {

  return 0;
}
