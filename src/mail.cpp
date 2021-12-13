#include <string_view>
#include <optional>
#include <exception>

#include "mailio/message.hpp"
#include "mailio/smtp.hpp"
#include "spdlog/spdlog.h"

#include "config.h"

using namespace std;
using mailio::dialog_error;
using mailio::mail_address;
using mailio::message;
using mailio::smtp_error;
using mailio::smtps;
string get_smtp_address(string_view mail_address)
{
    auto iter = find(mail_address.begin(), mail_address.end(), '@');
    if (iter == mail_address.end())
    {
        throw invalid_argument("illegal mail-address");
    }
    return "smtp." + string(iter + 1, mail_address.end());
}

void send_daily_report_mail(string_view title, string_view context = "") // if fail_reason is empty means success
{
    try
    {
        if (!is_send_mail())
            return;
        auto [address, password] = get_mail_info();
        auto reporter_name = get_reporter_name();
        auto smtp_address = get_smtp_address(address);
        message msg;
        msg.from(mail_address(reporter_name, address.data())); // set the correct sender name and address
        msg.add_recipient(mail_address("Dear User", address.data()));
        msg.subject(title.data());
        if (context.size())
            msg.content(fmt::format("Info:{}\r\nReport by {}.\r\n", context, reporter_name));
        else
            msg.content(fmt::format("Report by {}.\r\n", reporter_name));
        smtps conn(smtp_address, 587);
        conn.authenticate(address.data(), password.data(), smtps::auth_method_t::START_TLS);
        conn.submit(msg);
        SPDLOG_INFO("An E-mail has sent from {0} to {0} by smtp_server:{1}.", address,smtp_address);
        SPDLOG_INFO("E-mail Reporter name:{}, content:{}",reporter_name,msg.content());
    }
    catch (const exception &err)
    {
        SPDLOG_ERROR("send email failed:{}", err.what());
    }
}