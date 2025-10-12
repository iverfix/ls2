#include "unixOperatingSystem.h"
#include <grp.h>
#include <pwd.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>


constexpr int DEFAULT_BUFFER_SIZE = 16384;

long UnixOperatingSystem::getNumHardLinks(const char* filename) const {
  struct stat fileStat
  {
  };

  if (stat(filename, &fileStat) == -1) throw std::runtime_error("File coluld not be found");

  struct passwd pwd
  {
  };
  struct passwd* result{ nullptr };
  long bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);

  if (bufsize == -1) bufsize = DEFAULT_BUFFER_SIZE;

  std::vector<char> buffer(bufsize);


  if (getpwuid_r(fileStat.st_uid, &pwd, buffer.data(), buffer.size(), &result) != 0 || result == nullptr) { return 0; }
  return static_cast<long>(fileStat.st_nlink);
}

std::string UnixOperatingSystem::getFileUser(const char* filename) const {
  struct stat fileStat
  {
  };
  if (stat(filename, &fileStat) == -1) { throw std::runtime_error("File could not be found"); }

  struct passwd pwd
  {
  };
  struct passwd* result = nullptr;
  long bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (bufsize == -1) {
    bufsize = DEFAULT_BUFFER_SIZE;// Fallback value
  }

  std::vector<char> buffer(bufsize);

  if (getpwuid_r(fileStat.st_uid, &pwd, buffer.data(), buffer.size(), &result) != 0 || result == nullptr) { return "unknown"; }

  return { pwd.pw_name };
}

std::string UnixOperatingSystem::getFileGroup(const char* filename) const {
  struct stat fileStat
  {
  };
  if (stat(filename, &fileStat) == -1) { throw std::runtime_error("File could not be found"); }

  struct group grp
  {
  };
  struct group* result = nullptr;
  long bufsize = sysconf(_SC_GETGR_R_SIZE_MAX);
  if (bufsize == -1) {
    bufsize = DEFAULT_BUFFER_SIZE;// Fallback value
  }

  std::vector<char> buffer(bufsize);

  if (getgrgid_r(fileStat.st_gid, &grp, buffer.data(), buffer.size(), &result) != 0 || result == nullptr) { return "unknown"; }

  return { grp.gr_name };
}
