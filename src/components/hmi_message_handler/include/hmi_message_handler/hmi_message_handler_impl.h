/**
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_COMPONENTS_HMI_MESSAGE_HANDLER_INCLUDE_HMI_MESSAGE_HANDLER_HMI_MESSAGE_HANDLER_IMPL
#define SRC_COMPONENTS_HMI_MESSAGE_HANDLER_INCLUDE_HMI_MESSAGE_HANDLER_HMI_MESSAGE_HANDLER_IMPL

#include <set>
#include "hmi_message_handler/hmi_message_adapter.h"
#include "hmi_message_handler/hmi_message_handler.h"
#include "Utils/macro.h"
#include "Utils/MessageQueue.h"
#include "Utils/threads/thread.h"

namespace hmi_message_handler {

class ToHMIThreadImpl;
class FromHMIThreadImpl;

class HMIMessageHandlerImpl : public HMIMessageHandler {
  public:
    HMIMessageHandlerImpl();
    ~HMIMessageHandlerImpl();
    void onMessageReceived(application_manager::Message* message);
    void sendMessageToHMI(application_manager::Message* message);
    void setMessageObserver(HMIMessageObserver* observer);
    void onErrorSending(application_manager::Message* message);
    void addHMIMessageAdapter(HMIMessageAdapter* adapter) = 0;
    void removeHMIMessageAdapter(HMIMessageAdapter* adapter);

  private:
    HMIMessageObserver* observer_;
    std::set<HMIMessageAdapter* > message_adapters_;

    threads::Thread* to_hmi_thread_;
    friend class ToHMIThreadImpl;

    threads::Thread* from_hmi_thread_;
    friend class FromHMIThreadImpl;

    MessageQueue<application_manager::Message*> message_to_hmi_;
    MessageQueue<application_manager::Message*> message_from_hmi_;

    DISALLOW_COPY_AND_ASSIGN(HMIMessageHandlerImpl);
};
}  // namespace hmi_message_handler

#endif // SRC_COMPONENTS_HMI_MESSAGE_HANDLER_INCLUDE_HMI_MESSAGE_HANDLER_HMI_MESSAGE_HANDLER_IMPL
