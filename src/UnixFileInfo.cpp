#include "UnixFileInfo.h"
#include <format>
#include <grp.h>
#include <optional>
#include <pwd.h>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>


UnixFileInfo::UnixFileInfo(std::string_view filename)
{
  struct stat fileStat = {};
  if (stat(std::string(filename).c_str(), &fileStat) == -1) { throw std::runtime_error(std::format("File could not be found: {}", filename)); }

  numHardLinks = static_cast<long>(fileStat.st_nlink);
  fileOwner = fetchFileOwner(fileStat.st_uid);
  fileOwnerGroup = fetchFileOwnerGroup(fileStat.st_gid);
  permissionString = fetchPermissionString(fileStat.st_mode);
}

std::optional<std::string> UnixFileInfo::fetchPermissionString(mode_t mode) {

  std::string permissions{};

  // File type
  if (S_ISREG(mode)) { permissions += '-'; }
  else if (S_ISDIR(mode)) { permissions += 'd'; }
  else if (S_ISLNK(mode)) { permissions += 'l'; }
  else if (S_ISCHR(mode)) { permissions += 'c'; }
  else if (S_ISBLK(mode)) { permissions += 'b'; } 
  else if (S_ISFIFO(mode)) { permissions += 'p'; }
  else if (S_ISSOCK(mode)) { permissions += 's'; }
  else { permissions += '?'; }

  // Owner permissions
  permissions += ((mode & S_IRUSR) != 0U) ? 'r' : '-';
  permissions += ((mode & S_IWUSR) != 0U) ? 'w' : '-';
  permissions += ((mode & S_IXUSR) != 0U) ? 'x' : '-';

  // Group permissions
  permissions += ((mode & S_IRGRP) != 0U) ? 'r' : '-';
  permissions += ((mode & S_IWGRP) != 0U) ? 'w' : '-';
  permissions += ((mode & S_IXGRP) != 0U) ? 'x' : '-';

  // Others permissions
  permissions += ((mode & S_IROTH) != 0U) ? 'r' : '-';
  permissions += ((mode & S_IWOTH) != 0U) ? 'w' : '-';
  permissions += ((mode & S_IXOTH) != 0U) ? 'x' : '-';

  return permissions;
}

std::optional<std::string> UnixFileInfo::fetchFileOwner(uid_t uid)
{
  struct passwd pwd = {};
  struct passwd* result{ nullptr };
  long bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (bufsize == -1) { bufsize = DEFAULT_BUFFER_SIZE; }

  std::vector<char> buffer(bufsize);
  if (getpwuid_r(uid, &pwd, buffer.data(), buffer.size(), &result) != 0 || result == nullptr) { return std::nullopt; }
  return pwd.pw_name;
}

std::optional<std::string> UnixFileInfo::fetchFileOwnerGroup(gid_t gid)
{
  struct group grp = {};
  struct group* groupResult = nullptr;
  long bufsize = sysconf(_SC_GETGR_R_SIZE_MAX);
  if (bufsize == -1) { bufsize = DEFAULT_BUFFER_SIZE; }

  std::vector<char> buffer2(bufsize);
  if (getgrgid_r(gid, &grp, buffer2.data(), buffer2.size(), &groupResult) != 0 || groupResult == nullptr) { return std::nullopt; }
  return grp.gr_name;
}
