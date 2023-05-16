#pragma once

#include "Plugin.h"
using namespace yazi::engine;

namespace yazi {
namespace plugin {

class TestPlugin : public Plugin {
public:
  TestPlugin();
  virtual ~TestPlugin();

  virtual bool run(Context &ctx);
};
// 最好在.cc文件中注册，否则谁include整个文件，就会再次new
DEFINE_PLUGIN(TestPlugin)

} // namespace plugin
} // namespace yazi
