#pragma once

#include <optional>
#include <string_view>
#include <memory>

#include <httplib.h>
std::unique_ptr<httplib::Client> login(const std::string_view src_url, std::optional<std::string_view> login_check_path = {});