#include "BreakOut.h"
#include "GameController.h"
#include "App.h"
#include "AARectangle.h"
#include "Circle.h"
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

void BreakOut::ResetGame(size_t toLevel, int lives) {
    _levels = BreakoutGameLevel::LoadLevelsFromFile(App::GetBasePath() + "Assets/BreakoutLevels.txt");
    _yCutoff = App::Singleton().Height() - 2 * Paddle::PADDLE_HEIGHT;
    _lives = lives;
    _currentLevel = toLevel;
    AARectangle paddleRect = {Vec2D(App::Singleton().Width() / 2 - Paddle::PADDLE_WIDTH / 2, App::Singleton().Height() -  3 * Paddle::PADDLE_HEIGHT),
                              Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
    AARectangle levelBoundary = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height() };

    _levelBoundary = { levelBoundary };
    _paddle.Init(paddleRect, levelBoundary);
    _ball.MoveTo(Vec2D(App::Singleton().Width() / 2, App::Singleton().Height()*0.75));

    SetToServeState();

}

void BreakOut::SetToServeState() {
    _gameState = IN_SERVE;
    _ball.Stop();

    _ball.MoveTo(Vec2D(_paddle.GetAARectangle().GetCenterPoint().GetX(),
                       _paddle.GetAARectangle().GetCenterPoint().GetY() - _ball.GetRadius() - _paddle.PADDLE_HEIGHT));
}

bool BreakOut::IsBallPassedCutOffY() const {
    return _ball.GetPosition().GetY() > _yCutoff;
}

void BreakOut::ReduceLifeByOne() {
    if (_lives >= 0) --_lives;
}

void BreakOut::Init(GameController& controller) {
    controller.ClearAll();
	ResetGame();

    ButtonAction serveAction;
    serveAction.key = GameController::ActionKey();
    serveAction.action = [this](uint32_t dt, InputState state) {
        if (_gameState == IN_SERVE) {
            if (GameController::IsPressed(state)) {
                _gameState = IN_PLAY;
                if (_paddle.IsMovingLeft()) _ball.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                else _ball.SetVelocity(Vec2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
            }
        } else if (_gameState == IN_GAME_OVER) {
            if (GameController::IsPressed(state)) ResetGame();
        }
    };

    controller.AddInputActionForKey(serveAction);

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state) {
        if (_gameState == IN_PLAY || _gameState == IN_SERVE) {
            if (GameController::IsPressed(state)) _paddle.SetMovementDirection(PaddleDirection::LEFT);
            else _paddle.UnsetMovementDirection(PaddleDirection::LEFT);
        }
    };
    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t dt, InputState state) {
        if (_gameState == IN_PLAY || _gameState == IN_SERVE) {
            if (GameController::IsPressed(state)) _paddle.SetMovementDirection(PaddleDirection::RIGHT);
            else _paddle.UnsetMovementDirection(PaddleDirection::RIGHT);
        }
    };
    controller.AddInputActionForKey(rightKeyAction);


}

void BreakOut::Update(uint32_t dt) {

    if (_gameState == IN_SERVE) {
        _paddle.Update(dt, _ball);
        SetToServeState();
    } else if (_gameState == IN_PLAY) {
        _ball.Update(dt);
        _paddle.Update(dt, _ball);

        BoundaryEdge edge;

        if (_paddle.Bounce(_ball)) return;

        if (_levelBoundary.HasCollided(_ball, edge)) {
            _ball.Bounce(edge);
            return;
        }

        GetCurrentLevel().Update(dt, _ball);

        if (IsBallPassedCutOffY()) {
            ReduceLifeByOne();
            if (!IsGameOver()) SetToServeState();
            else _gameState = IN_GAME_OVER;
        } else if (GetCurrentLevel().IsLevelComplet()) {
            _currentLevel = (_currentLevel + 1) % _levels.size();
            ResetGame(_currentLevel);
        }
    }
}

void BreakOut::Draw(Screen& screen) {
    _ball.Draw(screen);
    _paddle.Draw(screen);
    GetCurrentLevel().Draw(screen);

    screen.Draw(_levelBoundary.GetAARectangle(), Color::White());



    Circle lifeCircle = { Vec2D(7, App::Singleton().Height() - 10), 4 };
    Line2D cutoff = { Vec2D(0, _yCutoff), Vec2D(App::Singleton().Width(), _yCutoff) };
    screen.Draw(cutoff, Color::White());

    for (int i = 0; i < _lives; ++i) {
        screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
        lifeCircle.MoveBy(Vec2D(17, 0));
    }
}

const std::string& BreakOut::GetName() const {
    static std::string name = "Break Out!";
    return name;
}
