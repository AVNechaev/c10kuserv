#ifndef STATS
#define STATS

#include <atomic>
#include <iostream>


struct stats_t {
  friend std::ostream& operator << (std::ostream& os, const stats_t& me);

  void add_request() { ++requests; }
  void open_conn() { ++connections; add_request(); }
  void close_conn() { --connections; }

private:
  std::atomic_int connections;
  std::atomic_int requests;
} stats;

std::ostream& operator << (std::ostream& os, const stats_t& me) {
  os << "conns: " << me.connections << "; requests: " << me.requests;
  return os;
}

#endif