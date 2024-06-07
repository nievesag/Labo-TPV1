#include "../checkML.h"


#include "GameObject.h"
#include "../GameStates/GameState.h"
#include "../GameStates/PlayState.h"

GameObject::GameObject(GameState* game) : game(game), application(game->getApplication()){};

GameObject::GameObject(PlayState* game) : game(game) {};

GameObject::~GameObject() {}

void GameObject::render() const {}

void GameObject::update() {}

void GameObject::save(ostream& out) const {}