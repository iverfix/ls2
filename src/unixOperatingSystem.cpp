#include "unixOperatingSystem.h"
#include <grp.h>
#include <optional>
#include <pwd.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>


UnixOperatingSystem::UnixOperatingSystem(const char* filename)
{
  struct stat fileStat = {};
  if (stat(filename, &fileStat) == -1) throw std::runtime_error("File could not be found:" + std::string(filename));

  numHardLinks = static_cast<long>(fileStat.st_nlink);
  fileOwner = fetchFileOwner(fileStat.st_uid);
  fileOwnerGroup = fetchFileOwner(fileStat.st_gid);
}

std::optional<std::string> UnixOperatingSystem::fetchFileOwner(uid_t uid)
{
  struct passwd pwd = {};
  struct passwd* result{ nullptr };
  long bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (bufsize == -1) bufsize = DEFAULT_BUFFER_SIZE;

  std::vector<char> buffer(bufsize);
  if (getpwuid_r(uid, &pwd, buffer.data(), buffer.size(), &result) != 0 || result == nullptr) return std::nullopt;
  return pwd.pw_name;
}

std::optional<std::string> UnixOperatingSystem::fetchFileOwnerGroup(gid_t gid)
{
  struct group grp = {};
  struct group* groupResult = nullptr;
  long bufsize = sysconf(_SC_GETGR_R_SIZE_MAX);
  if (bufsize == -1) bufsize = DEFAULT_BUFFER_SIZE;

  std::vector<char> buffer2(bufsize);
  if (getgrgid_r(gid, &grp, buffer2.data(), buffer2.size(), &groupResult) != 0 || groupResult == nullptr) return std::nullopt;
  return grp.gr_name;
}
