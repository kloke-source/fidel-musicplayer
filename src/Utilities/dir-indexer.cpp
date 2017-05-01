#include "dir-indexer.h"
#include "dir-data-struct.h"
#include <Utilities/util.h>
#include <functional>

using namespace DirIndexerTypes;

DirIndexer::DirIndexer() {
  this->threadpool = new ThreadPool();
  this->dir_data_struct_tree = new DirDataStruct();
}

DirIndexer::~DirIndexer() {
  if (this->threadpool != NULL)
    delete this->threadpool;
}

Contents DirIndexer::get_contents_in(std::string dir_name, bool ignore_hidden,
                                     bool only_files, ForContCbFunc cb_func) {
  Contents contents;
  if (dir_name.substr(dir_name.length() - 1) != "/")
    dir_name += "/";

  DIR *dir;
  struct dirent *ent;

  std::future<void> results;
  if ((dir = opendir(dir_name.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      // std::unique_lock<std::mutex> lock(indexer_mutex);
      // Ignore '.' and '..' directories //
      if (ent->d_name[0] != '.') {
        if (ent->d_type == DT_REG) {
          cb_func(dir_name + ent->d_name, ent);
        }
        contents.dirs.push_back(ent->d_name);
        /*        if (only_files == true) {
                  // Only if the content in the directory is a file //
                  if (ent->d_type == DT_REG) {
                    threadpool::Instance()->enqueue(
                        [&]() { cb_func(dir_name + ent->d_name, ent); });
                    contents.files.push_back(ent->d_name);
                  }
                } else {

                }*/
      }
    }
    closedir(dir);
  }

  return contents;
}

void DirIndexer::get_all_contents_in(std::string dir_name, bool ignore_hidden,
                                     bool only_files, ForContCbFunc cb_func) {
  this->dir_data_struct_tree->get_root_node()->set_data(dir_name);
  this->dir_data_struct_tree->get_root_node()->set_path(dir_name);
  this->dir_data_struct_tree->get_root_node()->set_is_dir(true);

  std::function<std::vector<DirDataStruct::Node *>(DirDataStruct::Node *)>
      index_contents_in_dir = [&](DirDataStruct::Node *parent_node) {
        Contents contents_in_dir = get_contents_in(
            parent_node->get_path(), ignore_hidden, only_files, cb_func);
        std::vector<DirDataStruct::Node *> children;

        for (size_t iter = 0; iter < contents_in_dir.files.size(); iter++) {
          threadpool::Instance()->enqueue(
              [iter, contents_in_dir, parent_node]() {
                parent_node->add_child(contents_in_dir.files[iter]);
              });
        }

        for (size_t iter = 0; iter < contents_in_dir.dirs.size(); iter++) {
          children.push_back(
              parent_node->add_child(contents_in_dir.dirs[iter], true));
        }

        return children;
      };

  DirDataStruct::Node *root_node = this->dir_data_struct_tree->get_root_node();

  std::function<void(DirDataStruct::Node *)> index_all_contents_func =
      [&](DirDataStruct::Node *parent_node) {
        if (parent_node != NULL) {
          // std::unique_lock<std::mutex> lock(this->indexer_mutex);
          std::vector<DirDataStruct::Node *> contents_in_par_dir =
              index_contents_in_dir(parent_node);

          for (size_t iter = 0; iter < contents_in_par_dir.size(); iter++) {
            // std::cout << "Path -> " << contents_in_par_dir[iter]->get_path()
            // << std::endl;
            index_all_contents_func(contents_in_par_dir[iter]);
          }
        } else
          return;
      };

  index_all_contents_func(root_node);
  // split_dir_index_results.get();
  // std::this_thread::sleep_for(std::chrono::seconds(1));
  // this->dir_data_struct_tree->traverse_all_nodes();
}
