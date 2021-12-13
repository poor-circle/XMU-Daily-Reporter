#pragma once

#include <string_view>
#include <optional>

//send default null message means success
void send_daily_report_mail(std::string_view title, std::string_view context = "");