#include <thread>
#include <random>
#include <chrono>

#include "report.h"
#include "mail.h"
#include "config.h"


using namespace std;
bool is_in_report_time()
{
	auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto time = *localtime(&now);
	return (time.tm_hour < 20 && (time.tm_hour != 19 || time.tm_min <= 30)) && time.tm_hour >= 5;
}
optional<string> report(int count = get_report_retry_counts())
{
	if (count <= 0)
		return {};
	auto result = report_now();
	while (result.has_value() && --count > 0)
	{
		SPDLOG_ERROR("Report failed: {}. We will try again after {}s", result.value(), get_report_retry_duration());
		SPDLOG_INFO("Least retry count: {}",count);
		this_thread::sleep_for(get_report_retry_duration() * 1s);
		result = report_now();
	}
	return result;
}
int main()
{
	if (!check_config())
	{
		SPDLOG_ERROR("Please edit \"report_setting.json\", input your account info and re-run the program.");
		this_thread::sleep_for(5s);
		return 0;
	}
	auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto time = *localtime(&now);
	if (!is_in_report_time())
	{
		SPDLOG_WARN("It is not allowed to report at this time.");
	}
	auto result = report();
	if (result.has_value()) //failed
	{
		send_daily_report_mail(
			"Daily report is failed!!!!",
			fmt::format("\r\nfailed resson:{}\r\n", result.value()));
		SPDLOG_ERROR("Report failed: {}\nPlease report manually", result.value());
	}
	else //succeed
	{
		SPDLOG_INFO("report succeeed!");
		send_daily_report_mail(
			"Daily report is succeed.");
	}
	this_thread::sleep_for(5s);
	return 0;
}