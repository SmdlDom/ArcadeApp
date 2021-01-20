#include "BreakOut.h"
#include "GameController.h"
#include "App.h"
#include "AARectangle.h"
#include <iostream>

/*
Paddle
-Can move side to side (by user)
-Stops at the edges of the screen
-Width and Height
_Bounces the ball based on the position that was hit

Ball
-Bounces off of the walls, the paddle and the block
-Width and Height
-Velocity, position

Block
-part of the level
-Has HP - One hit by the ball is -1 HP
-Color, position, Width and Height
-Bounces the ball

Level
-Container that holds all of the blocks
-Should be able to load a level from the levels.txt file
-Handle collision of the block 
-Contain the walls/Edges of the screens
-Reset the level

Game
-Contains all of the object
-Player which has 3 lives
-States -Serve the ball, In Game, Reset Game
*/

void BreakOut::ResetGame() {
    AARectangle paddleRect = {Vec2D(App::Singleton().Width() / 2 - Paddle::PADDLE_WIDTH / 2, App::Singleton().Height() -  3 * Paddle::PADDLE_HEIGHT),
                              Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
    AARectangle levelBoundary = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height() };

    _levelBoundary = { levelBoundary };
    _paddle.Init(paddleRect, levelBoundary);
    _ball.MoveTo(Vec2D(App::Singleton().Width() / 2, App::Singleton().Height() / 2));

    _ball.SetVelocity(INITIAL_BALL_VEL);

}

void BreakOut::Init(GameController& controller) {
    controller.ClearAll();

    ResetGame();

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::IsPressed(state)) _paddle.SetMovementDirection(PaddleDirection::LEFT);
        else _paddle.UnsetMovementDirection(PaddleDirection::LEFT);
    };
    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::IsPressed(state)) _paddle.SetMovementDirection(PaddleDirection::RIGHT);
        else _paddle.UnsetMovementDirection(PaddleDirection::RIGHT);
    };
    controller.AddInputActionForKey(rightKeyAction);


}

void BreakOut::Update(uint32_t dt) {
    _ball.Update(dt);
    _paddle.Update(dt, _ball);

    BoundaryEdge edge;

    if (_paddle.Bounce(_ball)) return;

    if (_levelBoundary.HasCollided(_ball, edge)) {
        _ball.Bounce(edge);
        return;
    }
}

void BreakOut::Draw(Screen& screen) {
    _ball.Draw(screen);
    _paddle.Draw(screen);
    screen.Draw(_levelBoundary.GetAARectangle(), Color::White());
}

const std::string& BreakOut::GetName() const {
    static std::string name = "Break Out!";
    return name;
}
