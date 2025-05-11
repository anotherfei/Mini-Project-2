#ifndef LEADERBOARDSCENE_HPP
#define LEADERBOARDSCENE_HPP
#include "PlayScene.hpp"
#include "Engine/IScene.hpp"

class LeaderboardScene final : public Engine::IScene {
private:
    std::ofstream ofs;
    std::string Name;
    int tick;
    int money;

public:
    explicit LeaderboardScene() = default;
    void Initialize() override;
    void OnKeyDown(int keyCode) override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void Terminate() override;
    void ReturnOnClick(int stage);
};

#endif   // LEADERBOARDSCENE_HPP
