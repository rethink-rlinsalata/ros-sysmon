/*
 * Copyright (c) 2012, Justin Bronder
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the organization nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <string>
#include <iostream>

#include <boost/shared_ptr.hpp>

#include <diagnostic_updater/diagnostic_updater.h>

namespace sysmon {

#define err(fmt...) fprintf(stderr, fmt);

class CpuInfo {
    /*
     * Parser for /proc/cpuinfo
     */
    public:
        typedef std::map<std::string, std::string> cpuinfo;
        typedef std::map<std::string, std::string>::const_iterator cpuinfoIter;

        /*
         * Constructor
         */
        CpuInfo();

        /*
         * Get the number of available processors.
         *
         * @return  - number of processors on the system.
         */
        unsigned int nproc();

        /*
         * Update the ROS diagnostics.
         */
        void ros_update(unsigned int proc, diagnostic_updater::DiagnosticStatusWrapper &dsw);

    private:
        /*
         * Read the latest value from /proc/cpuinfo.
         *
         * @return  - 0 on success, appropriate errno otherwise.
         */
        int update();

        std::vector<cpuinfo> m_values;

        friend std::ostream &operator<<(std::ostream &stream, const CpuInfo &ci);
};

} // namespace sysmon
