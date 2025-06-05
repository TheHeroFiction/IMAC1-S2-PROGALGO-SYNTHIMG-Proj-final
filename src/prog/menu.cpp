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

    // Configure TextRenderer
    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    // Draw "Play" at center of button (0,0)
    TextRenderer->Label("Press S to Start", GL_VIEW_SIZE / 2, GL_VIEW_SIZE / 2, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 20.f, SimpleText::CENTER);

    TextRenderer->SetTextSize(SimpleText::SIZE_32);

    TextRenderer->Label("Farmer vs Aliens", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) - 50.f, SimpleText::CENTER);
    TextRenderer->Render();
}

void drawWin()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.5f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Configure TextRenderer
    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::BLACK);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    // Draw "Play" at center of button (0,0)
    TextRenderer->Label("Press S to Start", GL_VIEW_SIZE / 2, GL_VIEW_SIZE / 2, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 20.f, SimpleText::CENTER);

    TextRenderer->SetTextSize(SimpleText::SIZE_32);

    TextRenderer->Label("YOU WIN !!!", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) - 50.f, SimpleText::CENTER);
    TextRenderer->Render();
};

void drawLose()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.5f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Configure TextRenderer
    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::BLACK);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    // Draw "Play" at center of button (0,0)
    TextRenderer->Label("Press S to Start", GL_VIEW_SIZE / 2, GL_VIEW_SIZE / 2, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) + 20.f, SimpleText::CENTER);

    TextRenderer->SetTextSize(SimpleText::SIZE_32);

    TextRenderer->Label("YOU LOSE !!!", GL_VIEW_SIZE / 2, (GL_VIEW_SIZE / 2) - 50.f, SimpleText::CENTER);
    TextRenderer->Render();
};

void drawUI()
{
    // Configure TextRenderer
    TextRenderer->ResetFont();
    TextRenderer->SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer->SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer->EnableBlending(true);

    // Draw "Play" at center of button (0,0)
    TextRenderer->Label("Press R to Restart", 20.f, 40.f, SimpleText::CENTER);
    TextRenderer->Label("Press O to quit", 20.f, 20.f, SimpleText::CENTER);

    TextRenderer->Render();
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && currentState == GameState::MENU)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int winW, winH;
        glfwGetWindowSize(window, &winW, &winH);

        float glX = (xpos / winW) * GL_VIEW_SIZE * aspectRatio - (GL_VIEW_SIZE * aspectRatio) / 2.0f;
        float glY = ((winH - ypos) / winH) * GL_VIEW_SIZE - GL_VIEW_SIZE / 2.0f;

        // Check Play button click
        if (glX >= -50 && glX <= 50 && glY >= -25 && glY <= 25)
        {
            currentState = GameState::PLAYING;
        }
    }
}