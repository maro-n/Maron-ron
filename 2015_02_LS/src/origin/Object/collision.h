
#pragma once
#include "../System/window_create.h"

//
// �����蔻��
//

namespace Collision {
  bool box_to_cursor(const Vec2f&, const Vec2f&);
  bool box_to_box();
}

using namespace Collision;
