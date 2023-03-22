#include <userver/utils/daemon_run.hpp>

#include <userver/components/component_list.hpp>
#include <userver/logging/component.hpp>
#include <userver/os_signals/component.hpp>
#include <userver/components/tracer.hpp>
#include <userver/components/manager_controller_component.hpp>

#include "tcp_srv.hpp"

int main(int argc, char* argv[]) {
  auto component_list = userver::components::ComponentList()
                            .Append<userver::os_signals::ProcessorComponent>()
                            .Append<userver::components::Logging>()       
                            .Append<userver::components::Tracer>()                   
                            // .Append<userver::components::ManagerControllerComponent>()
                            .Append<c10kuserv::Srv>();

  return userver::utils::DaemonMain(argc, argv, component_list);
}
