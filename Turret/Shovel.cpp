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
    : Turret("play/shovel.png", "play/shovel.png", x, y, 0, Price, 0.5) {
    Anchor.y += 0.0f;
}

void Shovel::CreateBullet() {

}
