#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Bullet/FireBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"

const int Shovel::Price = 0;
Shovel::Shovel(float x, float y)
    : Turret("play/shovel.png", "play/shovel.png", x, y, 200, Price, 0.5) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 0.0f / GetBitmapHeight();
}

void Shovel::CreateBullet()
{

}
