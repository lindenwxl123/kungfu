//
// Created by qlu on 2019/3/18.
//

#ifndef KUNGFU_JOURNAL_PRINTER_H
#define KUNGFU_JOURNAL_PRINTER_H

#include "YJJ_DECLARE.h"
#include "Timer.h"
#include "Hash.hpp"
#include "JournalReader.h"
#include "Frame.hpp"
#include "Page.h"
#include "PageUtil.h"
#include "PageHeader.h"
#include <iostream>
#include <algorithm>

#include "include/md_struct.h"
#include "include/serialize.h"
#include "include/msg.h"
#include "gateway/include/macro.h"

#include "nlohmann/json.hpp"

#define  TIME_FORMAT "%Y%m%d-%H:%M:%S"
#define PRINTER_NAME "JournalPrinter"

namespace kungfu
{
    
    class JournalPrinter
    {
    public:
        JournalPrinter(const std::string& folder, const std::string& name, int length = 20, bool only_page_header = false, bool to_verify = false, bool to_time_visual = true, bool need_detail = true):
                folder_(folder), name_(name), length_(20), only_page_header_(only_page_header), to_verify_(to_verify), to_time_visual_(to_time_visual), need_detail_(need_detail) {}

        void run(const std::string start_time = "20000101-13:30:00", const std::string end_time = "20200101-00:00:00", bool keep = false);

    private:
        std::string folder_;
        std::string name_;

        int length_;

        bool only_page_header_;
        bool to_verify_;

        bool to_time_visual_;
        bool need_detail_;

        void print_data(const void* data, kungfu::MsgType msg_type);
    };
}
#endif //KUNGFU_JOURNAL_PRINTER_H
