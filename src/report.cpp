#define CPPHTTPLIB_OPENSSL_SUPPORT

#include"login.h"
#include"httplib.h"
#include"nlohmann/json.hpp"
#include"fmt/format.h"
#include"config.h"
using namespace nlohmann;
using namespace std;
optional<string> report_now()
{
	try
	{
		auto cli = login("https://xmuxg.xmu.edu.cn/login/cas/xmu","/login/check");
		if (!cli)
			return "login failed! please check your username and password.";
		auto rsp = cli->Get("/api/app/214/business/now");
		if (!rsp)
			return "can't open the report url!";
		auto business_ID = json::parse(rsp->body).at("data").at(0).at("business").at("id");
		if (!business_ID.is_number_unsigned())
			return "failed to get businees_ID";
		rsp = cli->Get(fmt::format("/api/formEngine/business/{}/myFormInstance", business_ID.get<size_t>()).data());
		if (!rsp)
			return "can't open the report form!";
		auto form_ID = json::parse(rsp->body).at("data").at("id");
		if (!form_ID.is_string())
			return "failed to get form_ID";
		rsp = cli->Post(fmt::format("/api/formEngine/formInstance/{}", form_ID.get<string>()).data(), get_form_data(), "application/json");
		if (!rsp || rsp->status != 200)
			return "post form-data failed";
		if (json::parse(rsp->body).at("state") == false)
		{
			return "Today's report is over. You can't report now.";
		}
		return {};
	}
	catch(const exception& e)
	{
		return e.what();
	}
}