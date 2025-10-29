#include "UnixFileInfo.h"
#include <format>
#include <grp.h>
#include <optional>
#include <pwd.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <sys/types.h>
#include <unistd.h>
#include <vector>


UnixFileInfo::UnixFileInfo(const std::filesystem::directory_entry& entry)
{
  struct stat fileStat = {};
  std::string filename = entry.path().filename();
  if (stat(filename.c_str(), &fileStat) == -1) { throw std::runtime_error(std::format("File could not be found: {}", filename)); }

  numHardLinks = static_cast<long>(fileStat.st_nlink);
  fileOwner = fetchFileOwner(fileStat.st_uid);
  fileOwnerGroup = fetchFileOwnerGroup(fileStat.st_gid);
  permissionString = fetchPermissionString(entry);
}

std::optional<std::string> UnixFileInfo::fetchPermissionString(const std::filesystem::directory_entry& entry)
{

  std::string permissionString{};
  const auto fileStatus = entry.status();
  const auto permissions = fileStatus.permissions();

  switch (fileStatus.type()){
    case std::filesystem::file_type::regular:
      permissionString += '-';
      break;
    case std::filesystem::file_type::directory:
      permissionString += 'd';
      break;
    case std::filesystem::file_type::symlink:
      permissionString += 'l';
      break;
    case std::filesystem::file_type::character:
      permissionString += 'c';
      break;
    case std::filesystem::file_type::block:
      permissionString += 'b';
      break;
    case std::filesystem::file_type::fifo:
      permissionString += 'p';
      break;
    case std::filesystem::file_type::socket:
      permissionString += 's';
      break;
    case std::filesystem::file_type::not_found:
    case std::filesystem::file_type::none:
    case std::filesystem::file_type::unknown:
      permissionString += '?';
      break;
  }

  auto check = [&permissions](std::filesystem::perms bit, char character) { return (permissions & bit) != std::filesystem::perms::none ? character : '-'; };
  permissionString += check(std::filesystem::perms::owner_read, 'r');
  permissionString += check(std::filesystem::perms::owner_write, 'w');
  permissionString += check(std::filesystem::perms::owner_exec, 'x');
  permissionString += check(std::filesystem::perms::group_read, 'r');
  permissionString += check(std::filesystem::perms::group_write, 'w');
  permissionString += check(std::filesystem::perms::group_exec, 'x');
  permissionString += check(std::filesystem::perms::others_read, 'r');
  permissionString += check(std::filesystem::perms::others_write, 'w');
  permissionString += check(std::filesystem::perms::others_exec, 'x');

  return permissionString;
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
