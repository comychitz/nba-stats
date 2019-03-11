#ifndef __NBA_STAT_MAP_H__
#define __NBA_STAT_MAP_H__

#include <string>
#include <unordered_map>

namespace nba {

  class StatMap {
    public:
      StatMap() { }

      ~StatMap() { }

      void add(const std::string &key, const std::string &val) {
        map_[key] = val;
      }

      bool get(const std::string &key, int &val) const {
        auto mapIter = map_.find(key);
        if (mapIter != map_.end()) {
          val = std::stoi(mapIter->second);
          return true;
        }
        return false;
      }

      bool get(const std::string &key, float &val) const {
        auto mapIter = map_.find(key);
        if (mapIter != map_.end()) {
          val = std::stof(mapIter->second);
          return true;
        }
        return false;
      }

      bool get(const std::string &key, std::string &val) const {
        auto mapIter = map_.find(key);
        if (mapIter != map_.end()) {
          val = mapIter->second;
          return true;
        }
        return false;
      }

      bool get(const std::string &key, unsigned long long &val) const {
        auto mapIter = map_.find(key);
        if (mapIter != map_.end()) {
          val = stoull(mapIter->second);
          return true;
        }
        return false;
      }

    private:
      std::unordered_map<std::string, std::string> map_;
  };

}
#endif
