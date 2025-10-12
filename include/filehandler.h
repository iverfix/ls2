#pragma once
#include "IFileHandler.h"
#include "entry.h"
#include <algorithm>
#include <argumentParser.h>
#include <array>
#include <filesystem>
#include <system_error>
#include <utility>
#include <vector>

class FileHandler : public IFileHandler
{

public:
  explicit FileHandler(UserOptions options) : options(std::move(options)) {}
  [[nodiscard]] std::vector<Entry> getFolderContent() const override;

private:
  static constexpr int columnPadding{ 2 };
  UserOptions options{};

  [[nodiscard]] static EntryType getFileType(const std::filesystem::directory_entry& dirEntry) noexcept
  {
    std::error_code errorCode;
    const auto status = dirEntry.symlink_status(errorCode);
    if (errorCode) { return EntryType::RegularFile; }

    if (std::filesystem::is_directory(status)) { return EntryType::Directory; }
    if (std::filesystem::is_symlink(status)) { return EntryType::Symlink; }

    const auto permissions = status.permissions();
    constexpr std::array exec_bits = { std::filesystem::perms::owner_exec, std::filesystem::perms::group_exec, std::filesystem::perms::others_exec };

    if (std::ranges::any_of(exec_bits, [permissions](auto bit) { return (permissions & bit) != std::filesystem::perms::none; })) { return EntryType::Executable; }

    return EntryType::RegularFile;
  }
};
