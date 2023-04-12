#pragma once

#include <string_view>

#include <userver/components/tcp_acceptor_base.hpp>
#include <userver/engine/io/socket.hpp>

#include <array>

#include "stats.hpp"

namespace c10kuserv {

class Srv final : public userver::components::TcpAcceptorBase {
  public:
    //kName is required by ...
    static constexpr std::string_view kName = "c10kuserv";

    Srv(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
      : userver::components::TcpAcceptorBase(config, context)
      {};

    void ProcessSocket(userver::engine::io::Socket&& sock) 
    {
      stats.add_request();
      std::array<char, 16> buffer;

      while(!userver::engine::current_task::ShouldCancel()) {
        const auto readBytes = sock.ReadAll(buffer.data(), buffer.size(), {});
        if(readBytes == 0) {
          sock.Close();
          return;
        }
        const auto sentBytes = sock.SendAll(buffer.data(), readBytes, {});
        if(sentBytes != readBytes) {
          sock.Close();
          return;
        }
      }
    }
};


} // namespace service_template
