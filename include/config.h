#pragma once
#include<utility>
#include<string>
#include<fstream>
#include<iostream>
#include"nlohmann/json.hpp"
inline nlohmann::json& default_json()
{
	static nlohmann::json default_json =
	{
		{"user_agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.159 Safari/537.36 Edg/92.0.902.84"},
		{"form_data","{\"formData\":[{\"name\":\"select_1582538796361\",\"title\":\"\\u4ECA\\u65E5\\u4F53\\u6E29 Body temperature today \\uFF08\\u2103\\uFF09\",\"value\":{\"stringValue\":\"37.3\\u4EE5\\u4E0B Below 37.3 degree celsius\"},\"hide\":false},{\"name\":\"select_1582538846920\",\"title\":\"\\u662F\\u5426\\u51FA\\u73B0\\u53D1\\u70ED\\u6216\\u54B3\\u55FD\\u6216\\u80F8\\u95F7\\u6216\\u547C\\u5438\\u56F0\\u96BE\\u7B49\\u75C7\\u72B6\\uFF1FDo you have sypmtoms such as fever, coughing, chest tightness or breath difficulties?\",\"value\":{\"stringValue\":\"\\u5426 No\"},\"hide\":false},{\"name\":\"select_1584240106785\",\"title\":\"\\u5B66\\u751F\\u672C\\u4EBA\\u662F\\u5426\\u586B\\u5199\",\"value\":{\"stringValue\":\"\\u662F\"},\"hide\":false},{\"name\":\"select_1582538939790\",\"title\":\"Can you hereby declare that all the information provided is all true and accurate and there is no concealment, false information or omission. \\u672C\\u4EBA\\u662F\\u5426\\u627F\\u8BFA\\u6240\\u586B\\u62A5\\u7684\\u5168\\u90E8\\u5185\\u5BB9\\u5747\\u5C5E\\u5B9E\\u3001\\u51C6\\u786E\\uFF0C\\u4E0D\\u5B58\\u5728\\u4EFB\\u4F55\\u9690\\u7792\\u548C\\u4E0D\\u5B9E\\u7684\\u60C5\\u51B5\\uFF0C\\u66F4\\u65E0\\u9057\\u6F0F\\u4E4B\\u5904\\u3002\",\"value\":{\"stringValue\":\"\\u662F Yes\"},\"hide\":false},{\"name\":\"input_1582538924486\",\"title\":\"\\u5907\\u6CE8 Notes\",\"value\":{\"stringValue\":\"\"},\"hide\":false},{\"name\":\"datetime_1611146487222\",\"title\":\"\\u6253\\u5361\\u65F6\\u95F4\\uFF08\\u65E0\\u9700\\u586B\\u5199\\uFF0C\\u4FDD\\u5B58\\u540E\\u4F1A\\u81EA\\u52A8\\u66F4\\u65B0\\uFF09\",\"value\":{\"dateValue\":\"\"},\"hide\":false}],\"playerId\":\"owner\"}" },
		{"report_retry",{
			{"duration",10},
			{"counts",3}
		}},
		{"mail",{
			{"address",""},
			{"smtp_password",""},
			{"reporter_name","HAL-9000"}
		}},
		{"xmu",{
			{"ID",""},
			{"password",""}
		}}
	};
	return default_json;
}
inline nlohmann::json& init_json()
{
	static auto j = default_json();
	std::ifstream file("report_setting.json");
	if (!file.is_open())
		throw std::exception{};
	nlohmann::json user_json;
	file >> user_json;
	j.update(user_json);
	return j;
}
inline nlohmann::json& get_json()
{
	static nlohmann::json j = init_json();
	return j;
}
inline std::string get_user_agent()
{
	return get_json().at("user_agent").get<std::string>();
}
inline  std::string get_form_data()
{
	return get_json().at("form_data").get<std::string>();
}
inline int get_report_retry_duration()
{
	return get_json().at("report_retry").at("duration").get<int>();
}
inline int get_report_retry_counts()
{
	return get_json().at("report_retry").at("counts").get<int>();
}
inline std::pair<std::string, std::string> get_user_info()
{
	auto& j = get_json().at("xmu");
	return { j.at("ID").get<std::string>(),j.at("password").get<std::string>() };
}
inline bool is_send_mail()
{
	return get_json().at("mail").at("address").get<std::string>() != "";
}
inline std::pair<std::string, std::string> get_mail_info()
{
	auto& j = get_json().at("mail");
	return { j.at("address").get<std::string>(), j.at("smtp_password").get<std::string>() };
}
inline std::string get_reporter_name()
{
	return  get_json().at("mail").at("reporter_name").get<std::string>();
}
inline bool check_config()
{
	try
	{
		if (get_json().at("user_agent").is_string() &&
			get_json().at("form_data").is_string() &&
			get_json().at("report_retry").at("duration").is_number_integer() &&
			get_json().at("report_retry").at("counts").is_number_integer() &&
			get_json().at("xmu").at("ID").is_string() &&
			get_json().at("xmu").at("password").is_string() &&
			get_json().at("mail").at("address").is_string() &&
			get_json().at("mail").at("smtp_password").is_string() &&
			get_json().at("mail").at("reporter_name").is_string())
		{
			auto [id, pass] = get_user_info();
			if (id.size() && pass.size())
			{
				return true;
			}
		}
	}
	catch (const std::exception& e){}
	std::ofstream s("report_setting.json");
	s << default_json().dump(4);
	return false;
}