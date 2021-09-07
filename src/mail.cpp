#include <string_view>
#include <optional>
#include <exception>

#include "mailio/message.hpp"
#include "mailio/smtp.hpp"
#include "fmt/format.h"

#include "config.h"

using namespace std;
using mailio::message;
using mailio::mail_address;
using mailio::smtps;
using mailio::smtp_error;
using mailio::dialog_error;
string get_smtp_address(string_view mail_address)
{
   auto iter = find(mail_address.begin(), mail_address.end(), '@');
   if (iter == mail_address.end())
   {
       throw invalid_argument("illegal mail-address");
   }
   return "smtp."+string(iter+1, mail_address.end());
}

void send_daily_report_mail(string_view title,string_view context="") // if fail_reason is empty means success
{
    try
    {
        if (!is_send_mail())
            return;
        auto [address, password] = get_mail_info();
        auto reporter_name = get_reporter_name();
        auto smtp_address = get_smtp_address(address);
        message msg;
        msg.from(mail_address(reporter_name, address.data()));// set the correct sender name and address
        msg.add_recipient(mail_address("Dear User", address.data()));
        msg.subject(title.data());
        if (context.size())
            msg.content(fmt::format("Info:{}\r\nReport by {}.\r\n", context, reporter_name));
        else
            msg.content(fmt::format("Report by {}.\r\n", reporter_name));
        smtps conn(smtp_address, 587);
        conn.authenticate(address.data(), password.data(), smtps::auth_method_t::START_TLS);
        conn.submit(msg);
        fmt::print("an e-mail has sent to {}.\n", address);
    }
    catch (const exception& err)
    {
        fmt::print("send email failed:{}\n", err.what());
    }
}