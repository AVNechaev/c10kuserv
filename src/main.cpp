#include <userver/utils/daemon_run.hpp>

#include <userver/components/component_list.hpp>
#include <userver/logging/component.hpp>
#include <userver/os_signals/component.hpp>
#include <userver/components/tracer.hpp>
#include <userver/components/manager_controller_component.hpp>

#include "tcp_srv.hpp"
#include "stats.hpp"

#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
  auto component_list = userver::components::ComponentList()
                            .Append<userver::os_signals::ProcessorComponent>()
                            .Append<userver::components::Logging>()       
                            .Append<userver::components::Tracer>()                   
                            // .Append<userver::components::ManagerControllerComponent>()
                            .Append<c10kuserv::Srv>();

  auto stat_fun = []() {
    while(true) {
      std::cout << stats << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  };

  std::thread stat_t(stat_fun);
  stat_t.detach();
  return userver::utils::DaemonMain(argc, argv, component_list);
}
