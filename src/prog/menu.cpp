#include "menu.hpp"

using namespace glbasimac;

SimpleText *TextRenderer = nullptr;

void drawMenu()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    TextRenderer->Label("Press S to Start", GL_VIEW_SIZE / 2, GL_VIEW_SIZE / 2, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 20.f, SimpleText::CENTER);

    TextRenderer->SetTextSize(SimpleText::SIZE_32);

    TextRenderer->Label("Farmer vs Aliens", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) - 50.f, SimpleText::CENTER);
    TextRenderer->Render();
}

void drawWin(const int &score, const int &time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.5f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::BLACK);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    TextRenderer->Label("Press S to Start", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 80.f, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 100.f, SimpleText::CENTER);

    std::string scoreText = "Score: " + std::to_string(score);
    std::string timeText = "Time: " + std::to_string(time);

    TextRenderer->SetTextSize(SimpleText::SIZE_32);

    TextRenderer->Label(scoreText.c_str(), GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2), SimpleText::CENTER);
    TextRenderer->Label(timeText.c_str(), GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 30.f, SimpleText::CENTER);

    TextRenderer->SetTextSize(SimpleText::SIZE_48);

    TextRenderer->Label("YOU WIN !!!", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) - 60.f, SimpleText::CENTER);

    TextRenderer->Render();
};

void drawLose()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.5f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::BLACK);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    TextRenderer->Label("Press S to Start", GL_VIEW_SIZE / 2, GL_VIEW_SIZE / 2, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 20.f, SimpleText::CENTER);

    TextRenderer->SetTextSize(SimpleText::SIZE_32);

    TextRenderer->Label("YOU LOSE !!!", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) - 50.f, SimpleText::CENTER);
    TextRenderer->Render();
};

void drawPause()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    TextRenderer->Label("Press S to continue", GL_VIEW_SIZE / 2, GL_VIEW_SIZE / 2, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 20.f, SimpleText::CENTER);

    TextRenderer->SetTextSize(SimpleText::SIZE_32);

    TextRenderer->Label("PAUSE", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) - 50.f, SimpleText::CENTER);
    TextRenderer->Render();
};

void drawUI(const int &score, const int &time)
{
    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::BLACK);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    TextRenderer->Label("Press R to Restart", 50.f, 40.f, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", 50.f, 20.f, SimpleText::CENTER);

    std::string scoreText = "Score: " + std::to_string(score);
    std::string timeText = "Time: " + std::to_string(time);

    TextRenderer->Label(scoreText.c_str(), 50.f, 60.f, SimpleText::CENTER);
    TextRenderer->Label(timeText.c_str(), 50.f, 80.f, SimpleText::CENTER);

    TextRenderer->Render();
}