#include<thread>
#include<random>
#include<chrono>

#include"fmt/format.h"
#include"fmt/chrono.h"

#include"report.h"
#include"mail.h"
#include "config.h"
using namespace std;
bool is_in_report_time()
{
	auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto time = *localtime(&now);
	return (time.tm_hour < 20 && (time.tm_hour != 19 || time.tm_min <= 30)) && time.tm_hour >= 5;
}
optional<string> report(int count= get_report_retry_counts())
{
	if (count <= 0) return{};
	auto result = report_now();
	while (result.has_value() && --count > 0)
	{
		fmt::print("Error, report failed: {}\nWe will try again after {}s\n", result.value(),get_report_retry_duration());
		this_thread::sleep_for(get_report_retry_duration()*1s);
		result = report_now();
	}
	return result;
}
int main()
{
	if (!check_config())
	{
		fmt::print("Please edit \"report_setting.json\", input your account info and re-run the program.\n");
		this_thread::sleep_for(5s);
		return 0;
	}
	auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
	auto time = *localtime(&now);
	if (!is_in_report_time())
	{
		fmt::print("Warning: It is not allowed to report at this time.\n");
	}
	auto result = report();
	if (result.has_value()) //failed
	{
		send_daily_report_mail
		(
			"Daily report is failed!!!!",
			fmt::format("\r\nfailed resson:{}\r\n", result.value())
		);
		fmt::print("Error, report failed: {}\nPlease report manually\n", result.value());
	}
	else //succeed
	{
		send_daily_report_mail
		(
			"Daily report is succeed."
		);
		fmt::print("report succeeed!\n");
	}
	this_thread::sleep_for(5s);
	return 0;
}