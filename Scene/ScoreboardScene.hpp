#ifndef SCOREBOARDSCENE_HPP
#define SCOREBOARDSCENE_HPP
#include "PlayScene.hpp"
#include "Engine/IScene.hpp"

class ScoreboardScene final : public Engine::IScene {
private:
    std::ifstream ifs;
    std::string Name;
    int Page = 0;
    int MAXPAGES = 0;
    int List_per_Page = 8;
    std::vector<std::pair<std::string, int>> Data;
    std::vector<std::string> Time;
    void sortData(int sortType);

public:
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void OnKeyDown(int keyCode) override;
    void Draw() const override;
    void Terminate() override;
    void CloseOnClick(int stage);
    void PageButtonOnClick(int stage);
    void SortOnClick(int stage);
};

#endif   // SCOREBOARDSCENE_HPP
