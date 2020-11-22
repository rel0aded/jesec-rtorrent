// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright (C) 2005-2011, Jari Sundell <jaris@ifi.uio.no>

#ifndef RTORRENT_CORE_DHT_MANAGER_H
#define RTORRENT_CORE_DHT_MANAGER_H

#include <torrent/utils/priority_queue_default.h>

#include <torrent/object.h>

namespace core {

class DhtManager {
public:
  DhtManager()
    : m_warned(false)
    , m_start(dht_off) {}
  ~DhtManager();

  void            load_dht_cache();
  void            save_dht_cache();
  torrent::Object dht_statistics();

  void start_dht();
  void stop_dht();
  void auto_start() {
    if (m_start == dht_auto)
      start_dht();
  }

  void set_mode(const std::string& arg);

  void               set_throttle_name(const std::string& throttleName);
  const std::string& throttle_name() const {
    return m_throttleName;
  }

private:
  static const int dht_disable = 0;
  static const int dht_off     = 1;
  static const int dht_auto    = 2;
  static const int dht_on      = 3;

  static const int   dht_settings_num = 4;
  static const char* dht_settings[dht_settings_num];

  void update();
  bool log_statistics(bool force);

  unsigned int m_dhtPrevCycle;
  unsigned int m_dhtPrevQueriesSent;
  unsigned int m_dhtPrevRepliesReceived;
  unsigned int m_dhtPrevQueriesReceived;
  uint64_t     m_dhtPrevBytesUp;
  uint64_t     m_dhtPrevBytesDown;

  torrent::utils::priority_item m_updateTimeout;
  torrent::utils::priority_item m_stopTimeout;
  bool                          m_warned;

  int         m_start;
  std::string m_throttleName;
};

}

#endif
