#include "unixOperatingSystem.h"
#include <grp.h>
#include <pwd.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>

std::string UnixOperatingSystem::getFileUser(const char* filename) const
{

  struct stat fileStat
  {
  };
  if (stat(filename, &fileStat) == -1) { throw std::runtime_error("File could not be found"); }


  struct passwd* fileUser = getpwuid(fileStat.st_uid);

  return { fileUser != nullptr ? fileUser->pw_name : "unknown" };
}

std::string UnixOperatingSystem::getFileGroup(const char* filename) const
{


  struct stat fileStat
  {
  };
  if (stat(filename, &fileStat) == -1) { throw std::runtime_error("File could not be found"); }

  struct group* groupStats = getgrgid(fileStat.st_gid);

  return { groupStats != nullptr ? groupStats->gr_name : "unknown" };
}
