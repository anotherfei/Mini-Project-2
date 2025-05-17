#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>

#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

#include <allegro5/allegro_primitives.h>

#include "ScoreboardScene.hpp"

void ScoreboardScene::Initialize() {
    ifs.open("../Resource/scoreboard.txt", std::ios_base::in);
    if (ifs.is_open()) {
        std::string name, score, date_time;
        while (getline(ifs, name, '~') && getline(ifs, score, '~') && getline(ifs, date_time, '~')) {
            if (name != " ") {
                Data.push_back( {name.substr(0,name.length()-1), std::stoi(score.substr(1, score.length()-1))} );
                Time.push_back(date_time.substr(1, date_time.length()-1));
            }

            name.clear();
            score.clear();
            date_time.clear();
        }

        ifs.close();
    } else {
        std::cerr << "[ERROR] Could not open scoreboard.txt for writing!" << std::endl;
    }
    // Count pages needed to display data
    MAXPAGES = (static_cast<int>(Data.size()) + List_per_Page-1) / List_per_Page;
    sortData(0);

    int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    int halfH = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;

    AddNewObject(new Engine::Label("SCOREBOARD", "pirulen.ttf", 60, halfW, halfH / 4 - 20, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Name", "pirulen.ttf", 25, halfW - 500 - 10, halfH / 4 + 70, 215, 215, 215, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Score", "pirulen.ttf", 25, halfW - 30, halfH / 4 + 70, 215, 215, 215, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Date & Time", "pirulen.ttf", 25, halfW + 500 - 30, halfH / 4 + 70, 215, 215, 215, 255, 0.5, 0.5));

    Engine::ImageButton *btn;

    // Sort By
    // btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 80, 80, 200, 100);
    // btn->SetOnClickCallback(std::bind(&ScoreboardScene::SortOnClick, this, 0));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("Close", "pirulen.ttf", 48, halfW - 8, halfH * 3 / 2 + 80, 0, 0, 0, 255, 0.5, 0.5));

    // Close Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 - 5, halfH * 3 / 2 + 30, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::CloseOnClick, this, 0));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Close", "pirulen.ttf", 48, halfW - 8, halfH * 3 / 2 + 80, 0, 0, 0, 255, 0.5, 0.5));

    // > Next Page
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 - 5 + 500, halfH * 3 / 2 + 30, 100, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PageButtonOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label(">", "pirulen.ttf", 88, halfW - 8 + 355, halfH * 3 / 2 + 78, 0, 0, 0, 255, 0.5, 0.5));

    // < Prev Page
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200 - 5 - 200, halfH * 3 / 2 + 30, 100, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PageButtonOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("<", "pirulen.ttf", 88, halfW - 8 - 350, halfH * 3 / 2 + 78, 0, 0, 0, 255, 0.5, 0.5));
}

void ScoreboardScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_RIGHT) {
        if (Page < MAXPAGES-1) Page += 1;
    } else if (keyCode == ALLEGRO_KEY_LEFT){
        if (Page > 0) Page -= 1;
    }
}

void ScoreboardScene::Draw() const {
    IScene::Draw();
    int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
    int halfH = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;

    ALLEGRO_FONT* font = Engine::Resources::GetInstance().GetFont("pirulen.ttf", 20).get();
    ALLEGRO_FONT* Numfont = Engine::Resources::GetInstance().GetFont("pirulen.ttf", 25).get();
    int point = List_per_Page * Page;
    for (int i = 0; i < List_per_Page; i++) {

        if (i + point < static_cast<int>(Data.size())) {
            al_draw_textf(
                Numfont, al_map_rgb(215, 215, 215),
                halfW - 660, halfH / 4 + 105 + i * 55,
                ALLEGRO_ALIGN_CENTER,
                "%d.", i + point + 1
            );

            al_draw_textf(
                font, al_map_rgb(150, 150, 150),
                halfW - 560, halfH / 4 + 105 + i * 55,
                ALLEGRO_ALIGN_LEFT,
                "%s", (Data[i + point].first).c_str()
            );

            al_draw_textf(
                font, al_map_rgb(150, 150, 150),
                halfW - 85, halfH / 4 + 105 + i * 55,
                ALLEGRO_ALIGN_LEFT,
                "%d", Data[i + point].second
            );

            al_draw_textf(
                font, al_map_rgb(150, 150, 150),
                halfW + 365, halfH / 4 + 105 + i * 55,
                ALLEGRO_ALIGN_LEFT,
                "%s", (Time[i + point]).c_str()
            );
        }
    }
}

void ScoreboardScene::sortData(int sortType){
    switch (sortType) {
        case 1: break;
        case 2: break;

        default:
            for (int i = 0; i < static_cast<int>(Data.size()); i++) {
                for (int n = i; n < static_cast<int>(Data.size()); n++) {
                    if (Data[i].second < Data[n].second) {
                        swap(Data[i], Data[n]);
                        swap(Time[i], Time[n]);
                    }
                }
            }
        break;
    }
}

void ScoreboardScene::Terminate() {
    IScene::Terminate();
}

void ScoreboardScene::CloseOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("start");
}

void ScoreboardScene::PageButtonOnClick(int stage) {
    // Change to select scene.
    if (stage == 1) {
        if (Page < MAXPAGES-1) Page += 1;
    }
    else if (stage == 2) {
        if (Page > 0) Page -= 1;
    }
}

// void ScoreboardScene::SortOnClick(int stage) {
//     // sort the leaderboard
//     sort(stage);
// }