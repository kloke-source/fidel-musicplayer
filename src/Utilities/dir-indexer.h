#ifndef DIR_INDEXER_HH
#define DIR_INDEXER_HH
#include "dir-data-struct.h"
#include "threadpool.h"
#include <dirent.h>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace DirIndexerTypes {
/* Type definitions */
typedef std::function<void(std::string, struct dirent *)> ForContCbFunc;
typedef std::vector<std::string> Files;
// typedef std::vector<std::string> Contents;

struct Contents {
  std::vector<std::string> dirs;
  std::vector<std::string> files;
};
};

class DirIndexer {
private:
  std::mutex indexer_mutex;

public:
  DirIndexer();
  ~DirIndexer();

  DirIndexerTypes::Contents
  get_contents_in(std::string dir_name, bool ignore_hidden = true,
                  bool only_files = false,
                  DirIndexerTypes::ForContCbFunc cb_func =
                      [](std::string top_dir, struct dirent *ent) {});

  void get_all_contents_in(std::string dir_name, bool ignore_hidden = true,
                      bool only_files = false,
                      DirIndexerTypes::ForContCbFunc cb_func =
                          [](std::string top_dir, struct dirent *ent) {});

  DirIndexerTypes::Contents get_all_contents_in_backend(
      DirIndexerTypes::Contents contents, std::string dir_name,
      bool ignore_hidden = true, bool only_files = false,
      DirIndexerTypes::ForContCbFunc cb_func = [](std::string top_dir,
                                                  struct dirent *ent) {});

protected:
  ThreadPool *threadpool;
  DirDataStruct *dir_data_struct_tree;
};
#endif
