#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "login.h"
#include "httplib.h"

#include "config.h"

using namespace nlohmann;
using namespace std;
bool report_now()
{
	try
	{
	    SPDLOG_INFO("try login");
		auto cli = login("https://xmuxg.xmu.edu.cn/login/cas/xmu", "/platform");
		if (!cli)
		{
			SPDLOG_ERROR("login failed! please check your username and password.");
			return false;
		}
		this_thread::sleep_for(2s);
		auto res = cli->Get("/api/app/214/business/now");
		if (!res)
		{
			SPDLOG_ERROR("can't open the report url:{}!",to_string(res.error()));
			return false;
		}
		//SPDLOG_DEBUG("Headers:{}",res.value().headers);
		SPDLOG_DEBUG("Body:{}",res.value().body);
		SPDLOG_DEBUG("Status:{}",res.value().status);
		auto business_ID = json::parse(res->body).at("data").at(0).at("business").at("id");
		if (!business_ID.is_number_unsigned())
		{
			SPDLOG_ERROR("failed to get businees_ID");
			return false;
		}
		this_thread::sleep_for(2s);
		res = cli->Get(fmt::format("/api/formEngine/business/{}/myFormInstance", business_ID.get<size_t>()).data());
		if (!res)
		{
			SPDLOG_ERROR("can't open the report form: {}!",to_string(res.error()));
			return false;
		}
		//SPDLOG_DEBUG("Headers:{}",res.value().headers);
		//SPDLOG_DEBUG("Body:{}",res.value().body);
		SPDLOG_DEBUG("Status:{}",res.value().status);
		auto form_ID = json::parse(res->body).at("data").at("id");
		if (!form_ID.is_string())
		{
			SPDLOG_ERROR("failed to get form_ID");
			return false;
		}
		this_thread::sleep_for(2s);
		res = cli->Post(fmt::format("/api/formEngine/formInstance/{}", form_ID.get<string>()).data(), get_form_data(), "application/json");
		if (!res)
		{
			SPDLOG_ERROR("post form-data failed:{}!",to_string(res.error()));
			return false;
		}
		if (res->status != 200)
		{
			SPDLOG_ERROR("post form-data error status code={}!",res->status);
			return false;
		}
		//SPDLOG_DEBUG("Headers:{}",res.value().headers);
		SPDLOG_DEBUG("Body:{}",res.value().body);
		SPDLOG_DEBUG("Status:{}",res.value().status);
		if (json::parse(res->body).at("state") == false)
		{
			SPDLOG_ERROR("Today's report is over. You can't report now.");
			return false;
		}
		return true;
	}
	catch (const exception &e)
	{
		SPDLOG_ERROR("unknown exception occur: exception type:{} exception message:{}",typeid(e).name(),e.what());
		return false;
	}
}