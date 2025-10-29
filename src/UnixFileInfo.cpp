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

  std::string permissions{};

  // File type
  if (entry.is_regular_file()) {
    permissions += '-';
  } else if (entry.is_directory()) {
    permissions += 'd';
  } else if (entry.is_symlink()) {
    permissions += 'l';
  } else if (entry.is_character_file()) {
    permissions += 'c';
  } else if (entry.is_block_file()) {
    permissions += 'b';
  } else if (entry.is_fifo()) {
    permissions += 'p';
  } else if (entry.is_socket()) {
    permissions += 's';
  } else {
    permissions += '?';
  }

  auto to_symbolic = [](std::filesystem::perms permission) {
    auto check = [&](std::filesystem::perms bit, char character) { return (permission & bit) != std::filesystem::perms::none ? character : '-'; };
    std::string str;
    str += check(std::filesystem::perms::owner_read, 'r');
    str += check(std::filesystem::perms::owner_write, 'w');
    str += check(std::filesystem::perms::owner_exec, 'x');
    str += check(std::filesystem::perms::group_read, 'r');
    str += check(std::filesystem::perms::group_write, 'w');
    str += check(std::filesystem::perms::group_exec, 'x');
    str += check(std::filesystem::perms::others_read, 'r');
    str += check(std::filesystem::perms::others_write, 'w');
    str += check(std::filesystem::perms::others_exec, 'x');
    return str;
  };

  return permissions + to_symbolic(entry.status().permissions());
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
