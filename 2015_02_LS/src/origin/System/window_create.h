
#pragma once
#include "../common.h"
#include <memory>

//
// �E�B���h�E�����N���X
//

class WindowCreate {
  WindowCreate() = default;

  static bool isCreate;

public:
  static std::unique_ptr<AppEnv> app;
  static Vec2f mouse;

  static void create();
  static void mouse_translate();
};

typedef WindowCreate  win;
